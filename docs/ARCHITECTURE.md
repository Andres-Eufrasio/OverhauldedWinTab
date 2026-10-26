# Architecture

OverhauldedWinTab is a single Windhawk mod that runs in two different processes.
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

When `Appearance.WindowTabs` is `chips`, the same thumbnail is clipped to a
circle inside the chip. DWM thumbnails are composed above normal window content
and are not clipped by `SetWindowRgn`, so a window region cannot round them off.
The renderer therefore uses two extra top-level windows:

- `g_thumbHost` is a top-level thumbnail destination with a region equal to the
  union of the preview squares. It owns the `DwmRegisterThumbnail` handles for
  the visible chips and paints a black background; DWM composes the live
  thumbnail above that background.
- `g_chipMask` is a full-screen layered window above the host. Its Direct2D scene
  is rendered into a top-down 32-bpp DIB and presented with
  `UpdateLayeredWindow()`. The mask paints each chip foreground as a donut with
  a transparent circular hole over the preview. The opaque ring hides the square
  thumbnail corners and the hole reveals only the circular centre.

Both helper windows are `WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT |
WS_EX_NOACTIVATE` and return `HTTRANSPARENT` from `WM_NCHITTEST`, so input still
reaches the overlay. They are shown only when the open animation is essentially
complete, which avoids square corners peeking through during the fade, and they
are hidden while the overlay is busy or closing. `WindowChipContent` can replace
the thumbnail with a large application icon or with no center content at all.
The title is drawn one character at a time along the top arc by `DrawArcText()`:
each character is measured with `MeasureTextWidth()`, positioned on the arc, and
rotated by `DrawRotatedTextBlock()`. The title radius places the text in the clay
band between the centre inlay and the edge inserts. `DrawChipBody()` paints the
chip: a moulded outer edge, eight wide inlaid edge spots, the pressed groove and
a vertical light-to-dark sheen, with an optional transparent hole for the live
preview. The centre inlay gets its own pressed ring and a subtle printed ring,
and the title uses a contrast-aware color from `ChipTextColor()`.

`Appearance.WindowChipSize` scales `maxCardW` and the dock width, so the grid,
the dock and the circular preview all grow together. The internal
`WindowTabs` value remains `cards` for settings compatibility, but the UI calls
that style **Squares**.

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

`ResolveTheme()` also rebuilds `g_themeChipColors`, a six-entry set derived from
the accent (accent, lighter, darker, danger-tinted, text-tinted and a pale
highlight). `ChipColorForIndex()` resolves the shared **Chip colors** setting for
both desktop and window chips: `theme` cycles those derived shades, `single`
uses `ChipColor`, `palette` cycles the comma-separated `ChipPalette`, and
`classic` keeps the original fixed casino set.

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

`g_filtered` is the search result, while `g_display` is the subset shown in the
grid. With **Held windows** set to a side dock, `RebuildDisplayList()` removes
held entries from `g_display` and `UpdateLayout()` reserves a left or right dock
column before measuring the grid. `g_dockCards` stores the held entries in the
same `CardView` shape as the grid, so the dock can use either window cards or
poker chips and the same activation, close and hover paths. Held dock entries
carry a `filtered` index of `-1` when the current search hides them; activation
and closing use the stable window index (`entry`) instead.

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
`IServiceProvider::QueryService`) so that clicking any desktop pill, or pressing
its number, jumps straight to it instead of stepping through the desktops in
between. Only
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
changes, each held window is moved to the new desktop, so a held task follows the
user even while the overview is closed. After an in-overview switch the same
carry happens immediately from the desktop timer, and handles that closed in the
meantime are pruned.

Desktop names are read from
`HKCU\...\Explorer\VirtualDesktops\Desktops\{GUID}\Name` and written back to the
same key when the user renames a desktop, so renames are picked up by Windows
and other tools.

Moving a window to another desktop cannot use the documented
`IVirtualDesktopManager::MoveWindowToDesktop`: measured from the tool process it
returns `E_ACCESSDENIED` (`0x80070005`) for every window the caller does not own,
which is all of them. Instead the mod resolves the shell's
`IApplicationViewCollection` (same `QueryService` on `CLSID_ImmersiveShell`),
gets an `IApplicationView` with `GetViewForHwnd` (slot 6), finds the target
`IVirtualDesktop` and calls `IVirtualDesktopManagerInternal::MoveViewToDesktop`
(slot 4). That path is cross-process safe and was verified to move a window to
another desktop and back. The documented API is kept as a fallback.

## 6. Interaction model

State is intentionally small:

- `g_filtered` is the search result, `g_display` the filtered indices shown in
  the grid, `g_selected` the cursor into `g_display` (stored as a filtered index)
  and `g_page` the current grid page. Keeping the cursor in filtered space means
  activation and close keep working when a search is active. `g_selected` is
  `-1` when the display list is empty, so Enter/Delete are no-ops instead of
  acting on a held window that only exists in the dock.
- `g_cards` holds the visible grid cards and `g_dockCards` the held side-dock
  items; both use `CardView` with `entry`, `filtered`, `hit` and `lift` fields.
  `CardView::hit` keeps the unlifted area while `rect` follows the lift; hover
  tests both, so neither edge flickers when the visual card moves under the
  pointer.
- `Tab` cycles focus between the grid, the held dock (when it has items) and
  the desktop strip.
- `UpdateLayout` computes both the scene geometry and the per-card / per-pill hit
  rectangles in physical pixels, so mouse hit testing and rendering always agree.
- `Appearance.DesktopSelection` is resolved in `RebuildPills()`: `lift` raises
  the selected tab (or the active tab when the strip is not focused) by 6-10 px,
  shifts its hit and close rectangles with it, and suppresses the accent outline
  in all three desktop renderers.
- `Appearance.LiftHeldWindows`, `LiftHoveredWindows` and `LiftSelectedWindow`
  add the same lift to window cards and chips. Held dock items use the held lift
  when it is enabled, and the hover lift when that option is enabled.
- `g_renameDesktop` / `g_renameText` hold the inline desktop rename editor. The
  pill width and the caret position are measured with DirectWrite
  (`MeasureTextWidth`) instead of an estimated per-character advance, so long
  names are not clipped and the caret sits where the text ends.
- `g_carouselPos` is the animated centre of the carousel strip; `StripTarget()`
  is where it is heading and `WrapDelta` measures the shortest way around the
  wheel.

The search field is never typed into until it has focus: click it, or press `/`.
Until then `WM_CHAR` only routes the navigation keys (`h` `j` `k` `l` `x`), so a
query that contains those letters can never collide with a command. While the
field is focused, `OnKeyDown` handles only `Esc`, `Enter`, `Backspace` and
selection dismissal so that keys such as `Delete` or `N` cannot trigger an action
mid-query. Focusing a field that already holds a query sets `g_searchSelectAll`,
which makes the next typed character replace the query. With
`Appearance.AlwaysShowSearch` off, `SearchVisible()` collapses the field in
`UpdateLayout` until it is focused or non-empty; `Appearance.ShowHints` hides only
the hint line.

`Appearance.DesktopStrip` selects the strip layout: `flat` or `carousel`.
`Appearance.StripTabs` selects the tab shape: `pill`, `chip` or `cards`. The old
`DesktopStrip=cards` value was removed; `StripTabs` is the single source of
truth for the tab shape. `UsesChips()` and `UsesCards()` resolve the tab style, and
`IsWheel()` marks the carousel layout. In carousel mode every tab is placed by
its wrapped distance `d` from `g_carouselPos`, with `scale = 1 - 0.18|d|`, a
`4.5d` degree tilt, a small vertical arc and an alpha fade. `DrawChipTab` paints
a poker chip: a clay body with eight wide inlaid edge spots, a pressed rim groove,
the desktop number on a cream centre inlay, a ring of small pressed marks, the
desktop name on a label below, and the close button on the rim. Pill tabs keep
their 42 px flat-row and 52 px carousel heights. Chips are 52 px in the flat row
and 64 px in the carousel, with the name on a label underneath (15 px and 17 px
respectively).

Playing cards are a tab style, so they work in both layouts. `RebuildPills`
uses a fixed 160 x 224 card multiplied by `Appearance.CardSize`
(small 0.82, medium 1.0, large 1.22) and the strip is `224 * scale + 40` px tall
(264 px at medium) so the rotated cards stay inside it. The carousel positions
cards on the wheel; the flat row shrinks them if the row cannot fit. The create
button becomes a face-down card: `DrawCreateCard` paints a vector card back with
a double gold frame, a clipped diagonal lattice with diamond pips, an oval
medallion and ornament ring, and a `New desktop` banner. The old centered plus
was removed so the back reads as a card rather than an add button.
`WM_LBUTTONDOWN`/`WM_MOUSEMOVE`/`WM_LBUTTONUP` turn a downward pull into the same
create action as a click. `DrawDesktopCard` paints the ivory face,
corner rank and suit (rotated 180 degrees in the bottom corner), a large suit
pip, and the desktop name; the suit is `desktop & 3`, so desktops cycle through
spades, hearts, diamonds and clubs. `Appearance.CardAnimations` adds two ghost
cards drawn by `DrawCardAnimation()`: creating a desktop pulls a card from the
create deck to the slot where the new tab will appear and only then sends
Win+Ctrl+D, while closing one tosses the card up and off the right edge. The
ghost stores its own rank, suit and name so it can outlive the desktop it
represents. The draw target is computed before creation from the current layout
(just left of the create card in the flat row, centred in the carousel), so no
real tab needs to be hidden. A throw hides the closing tab until the ghost
leaves. Both animations use `AnimationSeconds()`, so
`Appearance.AnimationSpeed` controls them.
`Appearance.StripBackground` controls the panel: `Auto` keeps it in the flat row
and hides it for the carousel, `StripBackgroundVisible()` resolves the three
modes, and floating tabs get a soft drop shadow. `kTimerCarousel` eases
`g_carouselPos` towards `StripTarget()`
(strip selection, pending desktop switch, or active desktop) by the shortest
route around the wheel, and `KickCarousel()` restarts the timer when the target
changes. Rendering sorts visible tabs farthest-first and applies a
scale/rotation transform about each tab centre; hit testing uses the transformed
bounding box and prefers the tab closest to the centre.

`Appearance.WindowTabs` selects `DrawWindowCard()` or `DrawWindowChip()` for
grid and dock items. `Appearance.WindowChipContent` selects the live DWM
thumbnail, a large app icon or a name-only center. The circular thumbnail path
uses `g_thumbHost` / `g_chipMask`; thumbnails are skipped when the chip content is
icon or blank, because the center does not show a preview. `DrawWindowChip()`
takes a `mask` flag: in mask mode it skips the shadow and preview fill, draws the
chip surface (including the clay sheen) as donuts with a transparent hole at
`card.preview`, and still paints the title, selection ring, held dot and close
affordance. The mask scene is rendered after the overlay scene into `g_maskDC`,
then presented with `UpdateLayeredWindow()`. `DrawArcText()` lays the title in the
band between the centre inlay and the edge inserts and trims it with an ellipsis
when it exceeds the 170-degree arc. Hover and close rectangles
are tracked separately for the grid (`g_hoverCard` / `g_hoverClose`) and the dock
(`g_hoverDock` / `g_hoverDockClose`), and `OnLeftClick()` uses the stable
`CardView::entry` for dock activation and closing.

`Appearance.HeldDockBackground` toggles only the dock panel fill and stroke; the
dock label and items stay visible either way.

`Behavior.WrapDesktopStrip` controls `MoveStripSelection()`, the shared handler
for `Left`/`Right` and `h`/`l` while the strip has focus. With it on, the
selection wraps modulo the desktop count (7 to 1 and back); with it off it clamps
at the ends. The title in the top-left is `Appearance.Title`, defaulting to
`Task View`, and is laid out up to the search field so longer labels fit.

`ShowOverlay` clears the transient state (query, page, selection, focus, rename,
hover) *before* it calls `RebuildWindowList`. That order matters: the rebuild
filters the window list with the current `g_search`, so clearing the query
afterwards would leave the list filtered by the previous query while the search
box looked empty. Every `Win` + `Tab` now opens on the full, unfiltered list.

Vim navigation (`h` `j` `k` `l`, `/`, `x`) is gated on `Behavior.VimNavigation`.
Unmodified arrow keys keep their original meaning; `Ctrl` + `Left`/`Right`
switches desktops and `Shift` + `Left`/`Right` moves the selected window to an
adjacent desktop. Bare `1`-`9` jump to that desktop and `Shift` + `1`-`9` move
the selected window there; `M` also sets `g_pendingMove`, after which the next
`1`-`9` moves the selected window and any other key cancels. `U` toggles the
hold on the selected window, on the keyboard-selected dock item, or on the held
dock item under the pointer, and held cards are framed in their hold colour.

The held dock is a third keyboard stage. `CycleFocus()` implements `Tab` as
grid -> dock -> strip -> grid, skipping the dock when `g_dockCards` is empty.
`g_focusDock` and `g_dockSelected` drive a separate cursor; `SelectedWindow()`
returns the dock item while that cursor is active, so `U`, `M`, `Shift`+arrows
and the close action operate on the dock without changing the grid selection.
`MoveDockSelection()` wraps or clamps according to `Behavior.WrapNavigation`.
`Enter` activates, `Delete` closes, `U` releases, and `Esc` leaves the dock. With
the dock enabled, held windows are removed from `g_display`, so they are not part
of the grid page; the dock cursor is the keyboard route to them.

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
