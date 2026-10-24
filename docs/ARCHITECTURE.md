# Architecture

OverhauldedWin Tab is a single Windhawk mod that runs in two different processes.
The split exists because of how Windows registers the `Win` + `Tab` hotkey.

```
+---------------------------+          +--------------------------------------+
|  explorer.exe             |          |  windhawk.exe (tool process)         |
|                           |          |                                      |
|  Immersive Shell thread   |          |  UI thread                           |
|  WM_HOTKEY (Win+Tab)      |          |  +-------------------------------+   |
|        |                  |          |  | overlay window (topmost)      |   |
|        v                  |  message |  |  - Direct2D scene             |   |
|  WH_GETMESSAGE hook ------+--------->|  |  - DWM thumbnails             |   |
|  forwards, blanks message  |          |  |  - keyboard / mouse input     |   |
|                           |          |  +-------------------------------+   |
|  (no windows, no globals) |          |  | message-only control window   |   |
+---------------------------+          |  +-------------------------------+   |
                                       +--------------------------------------+
```

## 1. Explorer component

The native Task View is opened by a hotkey that Explorer registers for itself on
its `"Immersive Shell"` thread. The mod hooks that thread with a
`WH_GETMESSAGE` hook (`GetMessageProc`), allowing it to observe the thread's
message queue without installing a global hook.

When a `WM_HOTKEY` with `VK_TAB` and the `MOD_WIN` modifier arrives (and no
`MOD_ALT`, which belongs to Alt+Tab switchers), the hotkey is forwarded to the
tool process:

- The tool process publishes readiness by renaming its message-only control
  window to `Overhaulded Win+Tab (ready)`.
- Explorer finds that window, calls `AllowSetForegroundWindow` for its process
  (so the overview can take focus even when an elevated window had it) and posts
  the registered message `OverhauldedWinTab_Hotkey`.
- Only after the post succeeds is the original message blanked (`WM_NULL`), so
  the native Task View never opens. If forwarding fails, the native Task View
  opens as a safe fallback.

The component creates no windows and installs no global hooks. A watcher thread
re-hooks the thread if Explorer restarts its shell.

## 2. Tool process

Windhawk's "mod as tool" mechanism launches a dedicated `windhawk.exe` with
`-tool-mod overhaulded-win-tab`, which runs only `WhTool_*` callbacks. All UI
work happens on a single UI thread:

- `OverlayWndProc` drives a persistent topmost popup window that covers the
  active monitor.
- `ControlWndProc` handles the message-only window used for hotkey forwarding.
- A single message loop owns both, and `WM_UI_QUIT` / `WM_UI_SETTINGS` thread
  messages handle shutdown and settings changes.

Keeping both windows on one thread removes every cross-thread race around the
renderer, the window list and the DWM thumbnails.

### Persistence

The overlay is created and its renderer pre-warmed at startup, then hidden. The
first `Win` + `Tab` only has to enumerate windows, lay out the scene and show the
window, which keeps activation immediate.

## 3. Rendering

Rendering uses Direct2D on a `ID2D1DCRenderTarget` bound to the overlay's device
context. The render target is kept at 96 DPI so 1 DIP equals 1 pixel and the UI
is scaled manually by the monitor DPI (`GetDpiForMonitor`), which keeps
coordinates simple and the layout resolution aware.

Window previews are real DWM thumbnails:

- Each card registers `DwmRegisterThumbnail(overlay, window)` for the page's
  visible windows.
- `DwmUpdateThumbnailProperties` moves the thumbnail to the animated preview
  rectangle every frame and applies `DWM_TNP_SOURCECLIENTAREAONLY` plus an
  opacity that follows the open / close animation.
- Because DWM composes thumbnails *above* the window, the preview rectangle is
  framed inside the card and window chrome (title, close button) lives in the
  card header, never over the preview.

The panel background is a translucent scrim over DWM glass
(`DwmExtendFrameIntoClientArea` with `-1` margins). The scrim color and alpha are
configurable, and the material underneath is selectable:

- **Acrylic** – `DWMSBT_TRANSIENTWINDOW` plus the accent policy's acrylic blur
  with a fully transparent gradient
- **Blur** – the accent policy's Aero blur with a fully transparent gradient,
  without DWM's tinted material
- **Mica** / **Mica Alt** – `DWMSBT_MAINWINDOW` / `DWMSBT_TABBEDWINDOW`; these
  are opaque, wallpaper-tinted surfaces, not blur
- **Solid** / **Transparent** – no OS effect; the scrim alone is drawn

Every material application is followed by a `WM_NCACTIVATE` nudge so DWM paints
it. Measured on Windows 11 build 26300 against a real fullscreen overlay:

- `DWMSBT_TRANSIENTWINDOW` on its own paints a **flat, dark fill** that shows no
  trace of the windows behind it.
- The accent policy (`SetWindowCompositionAttribute`,
  `ACCENT_ENABLE_ACRYLICBLURBEHIND` / `ACCENT_ENABLE_BLURBEHIND`) does render the
  blur. Its `gradientColor` is the tint, so a fully transparent gradient
  (`0x00000000`) leaves a clean blur of whatever is behind the window. Passing an
  opaque gradient is what makes it come out as an exact solid fill — that is why
  the accent was previously written off as broken.
- The accent only takes effect when it is applied **while the window is still
  hidden**, i.e. before the `SWP_SHOWWINDOW` in `ShowOverlay()`. Applying it after
  the window is on screen leaves the flat fill.
- `DwmEnableBlurBehindWindow` has no visible effect.
- Mica and Mica Alt use the system backdrop and are conventionally opaque, so
  the desktop behind the overview does not show through them.

The OS material is requested without a tint: DWM supplies the material and the
Direct2D scrim then supplies the color and opacity for every mode through one
linear control. The scrim's alpha is verified to composite correctly over both
the acrylic material and Mica. If DWM glass is unavailable the scrim is forced
nearly opaque as a fallback.

### Palettes

Every color the renderer uses lives in a single `ThemeColors` struct (panel tint,
accent, text, card / strip / pill surfaces, preview fill, "on accent" text and
the close-button red). `ResolveTheme()` fills it from the selected `Appearance.Theme`:

- `Custom` maps the `AccentColor` / `BackgroundColor` settings onto the original
  dark surfaces, so the default look is byte-for-byte unchanged.
- Named palettes (Catppuccin Mocha / Macchiato / Frappe / Latte, Nord, Dracula,
  Tokyo Night, Gruvbox, Rose Pine) are built by `BuildTheme()` from a handful of
  base colors. Hover, selected and active surfaces are derived with a linear
  `MixColor()` toward the text or accent color, so a new palette needs only six
  values. A `light` flag flips the hover direction (darken instead of lighten)
  and the preview fill, which keeps light themes such as Catppuccin Latte
  readable.

The renderer reads `g_theme` everywhere instead of literals, so the selected
palette and the backdrop effect stay independent.

## 4. Window list

`EnumWindows` collects candidates and filters:

- visible top-level windows only,
- no shell surfaces (`Progman`, `WorkerW`, tray windows),
- no tool windows or `WS_EX_NOACTIVATE` windows,
- no DWM-cloaked windows (this is what hides UWP windows on other desktops),
- no windows owned by the tool process itself,
- only windows on the current virtual desktop,
- windows must have a title.

The result is kept in z-order, which closely follows the most-recently-used
order. A search string filters the list by window title or application name.

## 5. Virtual desktops

Desktop data comes from:

- `HKCU\...\Explorer\VirtualDesktops\VirtualDesktopIDs` (binary array of `GUID`s)
  for the ordered desktop list and their names,
- the overlay's own desktop id via the documented `IVirtualDesktopManager`,
  which is authoritative for "current" because the overlay lives on the active
  desktop, with `CurrentVirtualDesktop` as a fallback,
- `IVirtualDesktopManager::IsWindowOnCurrentVirtualDesktop` for filtering.

Switching a desktop calls the shell's internal
`IVirtualDesktopManagerInternal` (obtained from `CLSID_ImmersiveShell` through
`IServiceProvider::QueryService`) so that clicking any desktop pill jumps
straight to it instead of stepping through the desktops in between. Only
`GetDesktops` (vtable slot 7), `IObjectArray::GetAt` (slot 4),
`IVirtualDesktop::GetId` (slot 4) and `SwitchDesktop` (slot 9) are used; those
slots sit before the per-build additions of the interface, and the interface id
has been stable on Windows 11 since 21H2. The shell animates the switch, so the
overlay keeps its busy state and polls its own desktop id (up to roughly 1.2 s)
before re-enumerating. If the internal interface cannot be created, switching
falls back to injected `Win` + `Ctrl` + `Left`/`Right` chords. Creating and
closing desktops still use injected `Win` + `Ctrl` + `D` / `F4`.

Held tasks (`U`) are stored in `g_held` as window handle plus colour. A 200 ms
timer on the message-only control window reads `CurrentVirtualDesktop`; when it
changes, each held window is moved with `MoveWindowToDesktop`, so a held task
follows the user even while the overview is closed. After an in-overview switch
the same carry happens immediately from the desktop timer, and handles that
closed in the meantime are pruned.

Desktop names are read from
`HKCU\...\Explorer\VirtualDesktops\Desktops\{GUID}\Name` and written back to the
same key when the user renames a desktop, so renames are picked up by Windows
and other tools. Moving a window between desktops uses the documented
`IVirtualDesktopManager::MoveWindowToDesktop`, which needs no synthesized input.

## 6. Interaction model

State is intentionally small:

- `g_filtered` is the visible index list, `g_selected` the cursor into it and
  `g_page` the current grid page.
- `Tab` toggles focus between the grid and the desktop strip.
- `UpdateLayout` computes both the scene geometry and the per-card / per-pill hit
  rectangles in physical pixels, so mouse hit testing and rendering always agree.
- `g_renameDesktop` / `g_renameText` hold the inline desktop rename editor. The
  pill width and the caret position are measured with DirectWrite
  (`MeasureTextWidth`) instead of an estimated per-character advance, so long
  names are not clipped and the caret sits where the text ends.

The search field is never typed into until it has focus: click it, or press `/`.
Until then `WM_CHAR` only routes the navigation keys (`h` `j` `k` `l` `x`), so a
query that contains those letters can never collide with a command. While the
field is focused, `OnKeyDown` handles only `Esc`, `Enter` and `Backspace` so that
keys such as `Delete` or `N` cannot trigger an action mid-query.

`ShowOverlay` clears the transient state (query, page, selection, focus, rename,
hover) *before* it calls `RebuildWindowList`. That order matters: the rebuild
filters the window list with the current `g_search`, so clearing the query
afterwards would leave the list filtered by the previous query while the search
box looked empty. Every `Win` + `Tab` now opens on the full, unfiltered list.

Vim navigation (`h` `j` `k` `l`, `/`, `x`) is gated on `Behavior.VimNavigation`.
Unmodified arrow keys keep their original meaning; `Ctrl` + `Left`/`Right`
switches desktops and `Shift` + `Left`/`Right` moves the selected window to an
adjacent desktop. `M` sets `g_pendingMove`; the next `1`-`9` moves the selected
window to that desktop index and any other key cancels. `U` toggles the hold on
the selected window, and held cards are framed in their hold colour.

Activating a window hides the overlay immediately (no reverse animation) and
then restores and foregrounds the target. Closing a window posts `WM_CLOSE`,
removes it from the list right away and keeps the overview open.

## 7. Files

| File | Purpose |
| ---- | ------- |
| `OverhauldedWinTab.wh.cpp` | The complete mod: Explorer hook, tool process, renderer, input |
| `build.ps1` | Standalone compile / link check against the Windhawk compiler |
| `.github/workflows/sync-windhawk-readme.yml` | Syncs `README.md` into the mod's readme block |
| `docs/ARCHITECTURE.md` | This document |
