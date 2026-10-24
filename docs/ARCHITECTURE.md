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
configurable, and the effect underneath is selectable:

- **Acrylic** – `SetWindowCompositionAttribute` with `ACCENT_ENABLE_ACRYLICBLURBEHIND`
- **Blur** – `ACCENT_ENABLE_BLURBEHIND`
- **Mica** / **Mica Alt** – `DWMWA_SYSTEMBACKDROP_TYPE` (`DWMSBT_MAINWINDOW` /
  `DWMSBT_TABBEDWINDOW`) plus `DWMWA_MICA_EFFECT` for older builds
- **Solid** / **Transparent** – no OS effect; the scrim alone is drawn

The OS effect only supplies the blur/material (its tint is left transparent) so
that the D2D scrim provides one consistent color and opacity across every mode.
If DWM glass is unavailable the scrim is forced nearly opaque as a fallback.

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

Switching, creating and closing desktops use the same system hotkeys a user
would press (`Win` + `Ctrl` + `Left`/`Right`/`D`/`F4`) injected with
`SendInput`. After an action the overlay shows a short busy state, waits for the
shell to settle, and re-enumerates windows and desktops. This avoids relying on
undocumented desktop COM interfaces whose vtable changes between Windows builds.

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
- `g_renameDesktop` / `g_renameText` hold the inline desktop rename editor.

Vim navigation (`h` `j` `k` `l`, `/`, `x`) only engages while the search field is
empty and unfocused, so a search query that contains those letters still works
once typing has started. Unmodified arrow keys keep their original meaning;
`Ctrl` + `Left`/`Right` switches desktops and `Shift` + `Left`/`Right` moves the
selected window to an adjacent desktop.

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
