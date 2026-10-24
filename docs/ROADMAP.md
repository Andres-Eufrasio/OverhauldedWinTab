# Customization roadmap

Planning notes for the `experimental` branch. Nothing here is committed to a
release yet; each item lists the settings it would add, how it fits the current
renderer, and the main risk.

Guiding rules:

- Existing settings keep their current defaults, so an upgrade never changes the
  look or behavior of an existing install.
- All colors stay in the `ThemeColors` structure and every palette is still
  built by `BuildTheme`, so new themes cannot drift from the hover/selection
  derivation.
- Layout values stay in `UpdateLayout`; new visual options should not scatter
  magic numbers through `RenderScene`.
- Each feature gets its own commit and a README + readme-block sync.

## Implemented on `experimental`

- `Appearance.DesktopStrip` (`flat` / `carousel`) - the carousel centres the
  active desktop and rotates as you switch (v0.4.0).
- `Appearance.StripBackground` (`auto` / `show` / `hide`) - the carousel floats
  by default with larger pills and no panel (v0.4.1).

## Phase 1 - Visual customization pack

Low risk, high payoff, and mostly confined to `UpdateLayout`, `ResolveTheme` and
the card rendering block.

| Setting | Values | Notes |
| ------- | ------ | ----- |
| `Appearance.CardScale` | Compact / Comfortable / Large | Scales max card width, gap and header height; fonts stay at the DPI scale so text remains legible |
| `Appearance.CardAspect` | 16:9 / 16:10 / 4:3 | Replaces the hardcoded `w * 0.62f` |
| `Appearance.GridMargin` | Narrow / Normal / Wide | 40 / 56 / 80 px at 100% scaling |
| `Appearance.MaxColumns` | Auto / 3 / 4 / 5 / 6 | Caps the adaptive column search |
| `Appearance.CornerRadius` | 0-20 | Centralize the card/pill radii first; the shadow radius follows |
| `Appearance.ShowTitles` | on/off | Thumbnail-only cards; hide the header and give the preview the full card |
| `Appearance.AccentSource` | Custom / Windows | Read `HKCU\Software\Microsoft\Windows\DWM\AccentColor` (ABGR), fall back to `DwmGetColorizationColor` |
| `Appearance.Theme` = `system` | - | Light/dark from `AppsUseLightTheme`, mapped to Latte or a dark palette; accent follows Windows unless overridden |

Extra palettes, all one switch case each: Solarized Dark/Light, Kanagawa,
Everforest, One Dark, GitHub Dark/Light, Rosé Pine Moon/Dawn, Ayu Mirage.

Acceptance: toggling each setting redraws immediately; a 1-window and a
20-window desktop both lay out sanely at every scale; Compact + MaxColumns=3 does
not clip titles (ellipsis already handles long names).

## Phase 2 - Interaction pack

| Setting | Values | Notes |
| ------- | ------ | ----- |
| `Behavior.OpenOnMonitor` | Active window / Cursor | Cursor is the common multi-monitor preference |
| `Behavior.SortOrder` | Recent / Title / App | Recent is the current `EnumWindows` order; Title/App use a stable sort on the existing lowercased fields |
| `Behavior.WheelAction` | Pages / Desktops | When the cursor is over the strip, the wheel should always switch desktops |
| `Behavior.WrapDesktopStrip` | on/off | `h`/`l` and arrows currently clamp at the ends |

**Drag a card onto a desktop pill** to move the window there. This is the most
natural complement to the number-key moves:

- `WM_LBUTTONDOWN` on a card starts a potential drag; a move beyond ~6 px turns
  it into a drag so a plain click still activates.
- `SetCapture`, draw a translucent card ghost following the cursor, highlight the
  pill underneath.
- Dropping reuses `MoveWindowToDesktopInternal`; dropping outside the strip
  cancels.
- Held windows and the `1`-`9` move path stay unchanged.

**Right-click context menu on a card**: Activate, Move to desktop (submenu),
Hold/Release, Close. A small D2D popup keeps the visual language; a native
`TrackPopupMenu` is cheaper but looks out of place. Decide before building.

## Phase 3 - Search and desktop awareness

| Setting | Values | Notes |
| ------- | ------ | ----- |
| `Behavior.SearchAllDesktops` | on/off | Enumerate via `IApplicationViewCollection` instead of only the current desktop |
| `Appearance.ShowDesktopBadges` | on/off | Small "Desktop 2" badge on cards found on another desktop |
| `Appearance.ShowWindowCounts` | on/off | Window count on each desktop pill |

Searching other desktops needs activation to switch to that window's desktop
first, which is a natural extension of `SwitchDesktopDirect` +
`MoveViewToDesktop`; the main risk is enumerating views reliably without
blocking the UI thread.

## Phase 4 - Larger or riskier ideas

- **Multi-monitor overview**: one overlay per monitor, or move a single overlay
  to the cursor monitor. Needs per-monitor DPI and focus handling; the current
  code assumes one overlay.
- **Drag pills to reorder desktops**: requires shell internals not used yet;
  no known stable slot on build 26300.
- **Custom hotkey**: `RegisterHotKey` on the tool process (for example
  `Ctrl+Alt+Space`) alongside the intercepted `Win`+`Tab`. Conflicts with other
  apps are the main concern.
- **Per-desktop wallpapers/previews** in the strip: Windows does not expose
  per-desktop wallpapers; a rendered desktop snapshot is expensive.
- **Animation styles**: fade/scale (current), slide, or instant; add a
  `Reduce motion` switch that also respects the system animation setting.
- **Custom palette editor**: text color + surface color in the Custom theme.
  Useful, but easy to produce unreadable combinations; needs contrast clamping.

## Suggested order

1. Phase 1 visual pack as one release (v0.5.0), split into 2-3 commits.
2. Drag-to-move as the headline of Phase 2 (v0.5.x), then the menu.
3. Re-evaluate cross-desktop search after the shell enumeration probe.
