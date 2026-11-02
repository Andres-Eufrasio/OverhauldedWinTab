// ==WindhawkMod==
// @id              overhaulded-win-tab
// @name            OverhauldedWinTab
// @description     Replaces the Windows 11 Task View (Win+Tab) with a modern, focused overview of your windows and virtual desktops.
// @version         0.8.2
// @author          Andres Eufrasio
// @github          https://github.com/Andres-Eufrasio
// @homepage        https://github.com/Andres-Eufrasio/OverhauldedWinTab
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -lshell32 -lole32 -lgdi32 -luser32 -ladvapi32 -lshcore -lversion -ldwmapi -ld2d1 -ldwrite
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# OverhauldedWinTab

A modern replacement for the Windows 11 **Task View** (`Win` + `Tab`).

OverhauldedWinTab takes over the `Win` + `Tab` hotkey and presents a dark,
fluid overview of the current virtual desktop: a live grid of window previews
with real DWM thumbnails, a search filter, and a virtual desktop strip that can
switch, create and close desktops.

It is the Task View counterpart of
[OverhauldedWin Alt+Tab](https://github.com/IMiloDev/OverhauldedWin) and is built
from scratch in native C++ on top of Win32, Direct2D, DirectWrite and DWM.

## Screenshot

> Placeholder. Add a screenshot under `assets/` and reference it here.

## Features

- Full-screen Task View overlay for the active monitor
- Live window previews using real DWM thumbnails
- Adaptive card grid that scales with the number of windows
- Search across window titles and applications on the current desktop, or across
  every virtual desktop with `Shift` + `/`
- Optional poker-chip window tabs with a circular live preview, app icon or
  name-only centre, in four sizes
- Optional playing-card, poker-chip and carousel desktop tabs
- Selection styles for desktop tabs: accent outlines for pills and chips, plus
  an optional lift for any tab shape
- Held windows can move into a left or right side dock, with full keyboard
  access and an optional floating (background-free) dock
- Optional lift on window hover and keyboard selection
- Animated playing cards: draw one from the deck before creating a desktop and
  toss one away when closing it
- Optional search bar and shortcut hints, for a cleaner overview
- Virtual desktop strip with switching, creating and closing; clicking a desktop
  jumps straight to it instead of stepping through the ones in between
- Rename virtual desktops inline (saved the same way Windows stores them)
- Move a window to another virtual desktop without leaving the overview
- Hold a window with `U` so it follows you to every desktop you switch to
- Jump straight to a desktop with `1`-`9`, or move the selected window there
  with `Shift` + `1`-`9`
- Vim-style navigation (`h` `j` `k` `l`, `/`, `x`)
- Color themes with a built-in Catppuccin set (Mocha, Macchiato, Frappe, Latte),
  Nord, Dracula, Tokyo Night, Gruvbox and Rose Pine
- Customizable background: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent,
  with a configurable tint color and opacity
- Keyboard and mouse navigation
- Smooth open / close animation with resolution-aware UI scaling
- High-DPI aware, per-monitor
- Lightweight: the Explorer hook only forwards the hotkey
- Background execution for instant activation

## Design

OverhauldedWinTab keeps the visual language of OverhauldedWin: a dark obsidian
panel, rounded cards, subtle downward shadows, an accent highlight for the
selected window, and a configurable backdrop (Acrylic, Mica, Mica Alt, Blur,
Solid or transparent) behind the overview.

The overview is a persistent window prepared in the background, so `Win` + `Tab`
opens immediately instead of building the interface from scratch every time.

The playing-card create button is a real vector card back rather than a flat
placeholder: a double gold frame, a fine diagonal lattice with diamond pips, and
an oval medallion with a ring of ornaments. It is drawn entirely with Direct2D
primitives, so it stays crisp at every DPI and card size.

## Controls

| Input | Action |
| ----- | ------ |
| `Win` + `Tab` | Open or close the overview |
| `Enter` | Switch to the selected window / dock item / desktop, or save a rename |
| `Delete` | Close the selected window or dock item, or the active desktop |
| `Arrows` | Move through the focused grid, held dock or desktop strip |
| `Tab` | Cycle grid → held dock (when present) → desktop strip → grid |
| `Esc` | Leave the held dock, clear the search, or close the overview |
| `Ctrl` + `Left` / `Right` | Switch to the previous / next virtual desktop |
| `Shift` + `Left` / `Right` | Move the selected window or dock item to the previous / next desktop |
| `M` then `1`-`9` | Move the selected window or dock item to that numbered desktop |
| `1`-`9` | Jump to that numbered virtual desktop |
| `Shift` + `1`-`9` | Move the selected window or dock item to that numbered desktop |
| `U` | Hold or release the selected window, or the dock item under the pointer; held windows follow you across desktops |
| `F2` | Rename the selected (or current) virtual desktop |
| `N` | Create a new virtual desktop (strip focused) |
| `h` `j` `k` `l` | Vim movement through the grid, held dock or desktop strip |
| `/` | Focus the search field (reveals it when hidden) |
| `Shift` + `/` (`?`) | Focus the search field and search every virtual desktop |
| `x` | Close the selected window or dock item (Vim) |
| Typing while the search is focused | Filter windows by title or application |
| Left click | Activate a window, or jump straight to a desktop |
| Right click a desktop tab | Rename that virtual desktop |
| Right click a window card or dock item | Hold or release that window |
| Middle click on a card or dock item | Close that window |
| Click a held dock item | Activate that window |
| Click the create control on the strip | Create a new virtual desktop (a `+`, or the face-down card) |
| Pull the create card down | Create a new virtual desktop (playing-card tabs) |
| Click `x` on the active desktop | Close the current virtual desktop |
| Mouse wheel | Move through grid pages |

The search field is only typed into once it has focus: click it or press `/`
first (or `Shift` + `/` for all-desktop search). With **Always show search**
turned off the field stays hidden until you press `/` or `?`. Until the field
has focus the letter keys are available to navigation, so a query that contains
`h`, `j`, `k`, `l`, `n` or `x` never collides with a command. Focusing a field
that already has a query selects it, so the next typed character replaces the
old query. Set **Vim navigation** to `off` to disable the movement keys.

## Settings

### Appearance

| Setting | Description |
| ------- | ----------- |
| Theme | Color palette for the whole overlay (Custom, Catppuccin, Nord, ...) |
| Accent color | Accent color used for highlights, in `#RRGGBB` format (Custom theme) |
| Title text | Text shown in the top-left corner (defaults to `Task View`) |
| Background | Backdrop effect: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent |
| Background color | Tint color of the overview panel, in `#RRGGBB` format (Custom theme) |
| Background opacity | How strong the panel tint is over the backdrop (`0`-`100`) |
| Show hints | Show the keyboard shortcut hints at the bottom left |
| Always show search | Keep the search bar visible; when off, press `/` to reveal it |
| Animation speed | Relative speed of the open, close and playing-card animations |

### Window tabs

| Setting | Description |
| ------- | ----------- |
| Window tab style | Square previews, or poker chips with the window title curved around the centre inlay |
| Window chip content | Live window preview, app icon, or name only |
| Window chip size | Small, medium, large or extra-large poker-chip window tabs |
| Show window icons | Show each window's application icon in its card header |
| Lift hovered windows | Raise a window while the pointer is over it |
| Lift selected window | Raise the keyboard-selected window in the grid |

### Chips

| Setting | Description |
| ------- | ----------- |
| Chip colors | Theme accent shades, a single color, a custom palette, or classic casino colors |
| Chip color | Single chip color in `#RRGGBB` format (Single color mode) |
| Chip palette | Comma-separated `#RRGGBB` colors cycled across desktop and window chips (Custom palette mode) |

### Desktop strip

| Setting | Description |
| ------- | ----------- |
| Desktop strip layout | Flat row or rotating carousel |
| Desktop tabs | Pills, poker chips, or playing cards |
| Desktop strip background | Panel behind the tabs: Auto (flat only), Always show, or Always hide |
| Desktop selection | Accent outline for pills and chips, or pick-up/lift for the selected and active tabs; playing cards keep their printed border |
| Wrap desktop strip | `Left`/`Right` and `h`/`l` wrap from the last desktop to the first |

### Playing cards

| Setting | Description |
| ------- | ----------- |
| Card size | Small, medium or large playing cards |
| Card animations | Animate the playing-card draw and throw when creating or closing a desktop |

### Held windows

| Setting | Description |
| ------- | ----------- |
| Held window placement | Keep held windows in the grid, or dock them on the left or right |
| Held dock background | Show a panel behind the dock; turn off for a floating dock |
| Lift held windows | Raise held windows so they look picked up |

### Behavior

| Setting | Description |
| ------- | ----------- |
| Close when focus is lost | Dismiss the overview when it loses activation |
| Wrap grid navigation | Arrow keys wrap around the edges of the grid |
| Vim navigation | Enable `h` `j` `k` `l`, `/` and `x` navigation keys |

**Background** controls what sits behind the panel:

- **Acrylic** – a frosted, tinted blur of whatever is behind the overview, with
  the panel tint drawn on top (default)
- **Mica** – the Windows 11 Mica material. Mica is a flat, wallpaper-tinted
  surface rather than a blur, so the desktop behind the overview does not show
  through
- **Mica Alt** – the Windows 11 Mica Alt variant, also wallpaper-tinted
- **Blur** – the same blur as Acrylic without the acrylic tint, so more of the
  desktop shows through
- **Solid** – an opaque panel; ignores the opacity setting
- **Transparent** – no backdrop effect; the live desktop shows through

The tint color and opacity are drawn as a single layer on top of the backdrop,
so **Background opacity** works the same way in every mode: `0` is fully
transparent (just the blur or desktop) and `100` is fully opaque. On an opaque
mode such as Solid the setting has no visible effect. Lower it to let more of
the backdrop show through.

**Theme** recolors the entire overlay, not just the accent: the panel tint, the
card and desktop-strip surfaces, the text and the highlight all change together,
so light themes such as Catppuccin Latte stay readable. The built-in palettes
are:

- **Custom** (default) – uses the **Accent color** and **Background color**
  pickers above
- **Catppuccin Mocha**, **Macchiato**, **Frappe**, **Latte**
- **Nord**
- **Dracula**
- **Tokyo Night**
- **Gruvbox Dark**
- **Rose Pine**

Theme and **Background** are independent: pick, for example, Catppuccin Mocha
and keep Acrylic, or switch to a light theme with Mica. **Background opacity**
still controls how strongly the panel tint covers the backdrop in every theme.

## Desktop strip

**Desktop strip layout** chooses how the virtual desktops are laid out at the bottom:

- **Flat row** (default) – every desktop in a single row, with the create button
  after them and the strip panel behind them.
- **Carousel** – the active desktop sits in the centre, its neighbours curve and
  tilt away, and the wheel turns as you switch. Once the strip has focus, `h` /
  `l` or the arrows spin the wheel to a desktop; clicking a side tab jumps
  straight there.

**Desktop tabs** chooses the tab shape for both layouts:

- **Pills** (default) – the wide rounded tabs with the desktop number and name.
- **Poker chips** – each desktop becomes a numbered casino chip: a clay-coloured
  body with pressed cream edge inserts, a recessed ring and the desktop number on
  a cream centre inlay, with the desktop name on a label underneath. The create
  button becomes a matching chip. The chip colors follow **Chip colors**: by
  default they are shades derived from the theme accent, so the chips change with
  the palette. Choose **Classic casino colors** for the original fixed set, or
  define a single color or your own palette.
- **Playing cards** – each desktop becomes a portrait card with its own suit
  (spades, hearts, diamonds, clubs, then back to spades). **Card size** makes the
  cards small, medium or large. In the carousel the cards float directly over the
  desktop with the panel hidden by default; the flat row keeps the panel. The
  create button is a face-down card: click it, or pull it downward, to create a
  new desktop.

With **Card animations** on, creating a desktop first draws a card from the deck
toward the new desktop's place in the strip, then creates the desktop; closing
one tosses its card up and off the strip. The card animations use the same
**Animation speed** as the open and close transitions.

**Desktop selection** changes how the active and selected desktop tabs are
marked. **Accent outline** (default) keeps the current accent border for pills
and chips. **Lift** raises the selected tab, or the active tab when the strip is
not focused, and skips the accent outline so the pick-up is the only selection
cue. Playing cards always keep their printed ink border and never use the accent
outline; a selected card gets a slightly heavier edge. Lift works for pills,
poker chips and playing cards in both the flat row and the carousel; the shadow
deepens as the tab rises.

**Desktop strip background** controls the panel behind the strip: **Auto**
(default) keeps it for the flat row and hides it for the carousel, **Always show**
brings it back, and **Always hide** makes the flat row float as well.

**Wrap desktop strip** (default on) lets `Left`/`Right` and `h`/`l` loop from the
last desktop back to the first, so a seven-desktop carousel goes from 7 to 1
instead of stopping at the edge.

## Window chips

**Window tab style** can draw each open window as a square preview or as a
poker chip. The window title is curved around the top of the centre inlay, one
character at a time, and the centre can show:

- **Live window preview** (default) – the real DWM thumbnail, clipped to a
  circle inside the chip and framed by a pressed ring.
- **App icon** – the application icon on a light centre disc.
- **Name only** – just the curved title and the coloured clay surface.

**Window chip size** makes the chips small, medium, large or extra-large; the
grid and the held dock both scale with it. The circular preview is a real DWM
thumbnail: the thumbnail is hosted on a separate top-level window, and a layered
mask paints the chip foreground with a transparent circular hole over it, so
the square thumbnail corners never show. **Chip colors** is shared by window
chips and desktop chips, so the two styles always match. Theme mode derives a set
of accent shades; Classic keeps the original casino colors; Single color paints
every chip the same; and Custom palette cycles through the comma-separated
colors.

## Held windows

Press `U` to hold the selected window, or right-click any window card or dock
item to toggle its held state. Held windows follow you to every desktop you
switch to, and they get a colored frame and corner dot. By default they stay in
the grid. Set **Held window placement** to **Dock on the left** or **Dock on
the right** to move them into a side panel instead; the panel uses the same
squares or poker chips as the grid, so the two modes stay visually consistent.

The dock has its own keyboard stage: press `Tab` from the grid to focus it, then
use the arrows (or `h`/`j`/`k`/`l`) to select an item, `Enter` to activate it,
`Delete` to close it and `U` to release it back into the grid. `Tab` continues to
the desktop strip and then back to the grid; `Esc` leaves the dock. Clicking or
middle-clicking a dock item still works as before, and right-clicking it
releases the hold. Held dock items stay visible while a search is active, so a
held window is always one click away. Turn **Held dock background** off to let
the dock float without a panel.
**Lift held windows** is on by default so held items look picked up; **Lift
hovered windows** and **Lift selected window** are optional and add the same
raised look to the pointer hover and the keyboard cursor. The lift deepens the
shadow and leaves the item otherwise unchanged.

## Search

Press `/` or click the field to focus the search, then type to filter windows by
title or application. Focusing the field again selects the previous query, so
typing starts a new one. The query is cleared every time the overview opens, so a
new `Win` + `Tab` always starts from the full window list. Turn **Always show
search** off to keep the field hidden until you press `/`.

Press `Shift` + `/` (`?`) instead to search every virtual desktop. Results from
other desktops are prefixed with their desktop number (`D2`, `D3`, ...) and show
the application icon in place of the live thumbnail, because Windows cloaks
windows on inactive desktops. Activating one switches to that desktop first and
then focuses the window. Press `Esc` to leave all-desktop search and return to
the current desktop.

## How it works

The mod runs in two places:

1. A small component inside `explorer.exe` watches the `Immersive Shell`
   message queue and forwards the `Win` + `Tab` hotkey to the overview instead
   of letting the native Task View open.
2. A dedicated `windhawk.exe` tool process owns the persistent overlay window,
   the renderer and all input handling.

Virtual desktop names are written to the same per-desktop registry keys Windows
uses (`HKCU\...\Explorer\VirtualDesktops\Desktops\{GUID}\Name`), so renames are
picked up by Windows and other tools.

Switching desktops calls the shell's internal `IVirtualDesktopManagerInternal`
so clicking a desktop pill or pressing a number goes straight there. The current
cards stay visible while the switch runs, and the grid is rebuilt as soon as
Windows reports the target desktop active. Moving a window to another desktop
uses the shell's `IApplicationViewCollection` and
`MoveViewToDesktop`: the documented `MoveWindowToDesktop` refuses windows owned
by other processes with `E_ACCESSDENIED`, which is always the case for the
separate tool process. Creating or closing a desktop still presses the system
shortcut (`Win` + `Ctrl` + `D` / `F4`), and if the internal interface is
unavailable the switch falls back to `Win` + `Ctrl` + `Left`/`Right`.

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for the full design.

## Compatibility

Designed for Windows 11.

The project is under active development, so behavior may vary depending on:

- Display scaling
- Multiple-monitor configurations
- Windows configuration
- Application window types
- Other Task View / task-switcher modifications

Running multiple mods that replace Task View or the task switcher at the same
time may cause conflicts.

## Development

Requirements:

- [Windhawk](https://windhawk.net/) with the compiler installed
- The `WorkingDirectory` of this repository opened in the Windhawk mod editor

`build.ps1` performs a standalone syntax and link check of the mod with the
compiler bundled by Windhawk:

```powershell
.\build.ps1
```

## License

MIT. The Explorer hotkey forwarding patterns are adapted from **OverhauldedWin**
by [IMiloDev](https://github.com/IMiloDev). See the [LICENSE](LICENSE) file for
the complete license text.

---

OverhauldedWinTab is a pre-release project.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Appearance:
    - Theme: "custom"
      $name: Theme
      $description: Color palette for the whole overlay. "Custom" uses the accent and background colors below.
      $options:
      - "custom": Custom
      - "catppuccin-mocha": Catppuccin Mocha
      - "catppuccin-macchiato": Catppuccin Macchiato
      - "catppuccin-frappe": Catppuccin Frappe
      - "catppuccin-latte": Catppuccin Latte
      - "nord": Nord
      - "dracula": Dracula
      - "tokyo-night": Tokyo Night
      - "gruvbox": Gruvbox Dark
      - "rose-pine": Rose Pine
    - AccentColor: "#4CC2FF"
      $name: Accent color
      $description: 'Accent color used for highlights, in #RRGGBB format. Used by the "Custom" theme.'
    - Title: "Task View"
      $name: Title text
      $description: Text shown in the top-left corner of the overview. Leave empty to use "Task View".
    - Background: "acrylic"
      $name: Background
      $description: Backdrop effect. Acrylic (and Blur) use the Windows 11 acrylic material; Mica is a flat, wallpaper-tinted surface.
      $options:
      - "acrylic": Acrylic
      - "mica": Mica
      - "micaalt": Mica Alt
      - "blur": Blur
      - "solid": Solid
      - "none": Transparent
    - BackgroundColor: "#0A0D12"
      $name: Background color
      $description: 'Tint color of the overview panel, in #RRGGBB format. Used by the "Custom" theme.'
    - BackgroundOpacity: 70
      $name: Background opacity
      $description: Strength of the panel tint drawn over the backdrop (0-100). 0 leaves the backdrop untouched, 100 is fully opaque.
    - ShowHints: true
      $name: Show hints
      $description: Show the keyboard shortcut hints at the bottom left.
    - AlwaysShowSearch: true
      $name: Always show search
      $description: Keep the search bar visible. When off, press / to reveal it.
    - AnimationSpeed: "100"
      $name: Animation speed
      $description: Relative speed of the open, close and playing-card animations.
      $options:
      - "75": 75%
      - "100": 100%
      - "125": 125%
      - "150": 150%
  $name: Appearance
- WindowTabs:
    - Style: "cards"
      $name: Window tab style
      $description: Draw open windows as square previews, or as round poker chips with the title curved around the centre inlay.
      $options:
      - "cards": Squares
      - "chips": Poker chips
    - ChipContent: "preview"
      $name: Window chip content
      $description: What to show in the middle of a poker-chip window. The window name always curves around the top of the centre inlay.
      $options:
      - "preview": Live window preview
      - "icon": App icon
      - "blank": Name only
    - ChipSize: "medium"
      $name: Window chip size
      $description: Size of poker-chip window tabs. Larger chips use more of the grid.
      $options:
      - "small": Small
      - "medium": Medium
      - "large": Large
      - "extra-large": Extra large
    - ShowIcons: true
      $name: Show window icons
      $description: Show each window's application icon in the card header.
    - LiftHovered: false
      $name: Lift hovered windows
      $description: Raise a window while the pointer is over it.
    - LiftSelected: false
      $name: Lift selected window
      $description: Raise the keyboard-selected window in the grid.
  $name: Window tabs
- Chips:
    - Mode: "theme"
      $name: Chip colors
      $description: Palette used by desktop chips and window chips. Theme derives a set of shades from the active accent color; Classic keeps the original casino colors.
      $options:
      - "theme": Theme accent shades
      - "single": Single color
      - "palette": Custom palette
      - "classic": Classic casino colors
    - Color: "#1E5AA8"
      $name: Chip color
      $description: 'Single chip color in #RRGGBB format. Used when Chip colors is set to Single color.'
    - Palette: "#B3261E,#1E5AA8,#1E7A46,#6A3D9A,#B45F06,#26262B"
      $name: Chip palette
      $description: 'Comma-separated #RRGGBB colors, cycled across desktop and window chips. Used when Chip colors is set to Custom palette.'
  $name: Chips
- DesktopStrip:
    - Layout: "flat"
      $name: Desktop strip layout
      $description: Lay the virtual desktops out as a flat row or a rotating carousel.
      $options:
      - "flat": Flat row
      - "carousel": Carousel
    - Tabs: "pill"
      $name: Desktop tabs
      $description: Shape of the desktop tabs. Poker chips show the desktop number on a round chip with the name below; playing cards turn each desktop into a portrait card.
      $options:
      - "pill": Pills
      - "chip": Poker chips
      - "cards": Playing cards
    - Background: "auto"
      $name: Desktop strip background
      $description: Panel behind the virtual desktop tabs. Auto shows it for the flat row and hides it for the floating carousel and card wheel.
      $options:
      - "auto": Auto
      - "show": Always show
      - "hide": Always hide
    - Selection: "highlight"
      $name: Desktop selection
      $description: How selected and active desktop tabs are marked. Lift raises the tab; accent outlines apply to pills and chips, while playing cards keep their printed border.
      $options:
      - "highlight": Accent outline
      - "lift": Pick up / lift
    - Wrap: true
      $name: Wrap desktop strip
      $description: Let Left/Right and h/l wrap from the last desktop back to the first in the strip.
  $name: Desktop strip
- Cards:
    - Size: "medium"
      $name: Card size
      $description: Size of the playing cards when Desktop tabs is set to Playing cards.
      $options:
      - "small": Small
      - "medium": Medium
      - "large": Large
    - Animations: true
      $name: Card animations
      $description: Animate playing cards being drawn from the deck and thrown away when a desktop is created or closed.
  $name: Playing cards
- HeldWindows:
    - Mode: "off"
      $name: Held window placement
      $description: Keep held windows in the grid, or move them into a side dock. The dock works for both window squares and poker chips.
      $options:
      - "off": Keep in the grid
      - "left": Dock on the left
      - "right": Dock on the right
    - DockBackground: true
      $name: Held dock background
      $description: Show a panel behind the held-window dock. Turn off to let the dock float over the desktop.
    - LiftHeld: true
      $name: Lift held windows
      $description: Raise held windows so they look picked up.
  $name: Held windows
- Behavior:
    - CloseOnFocusLoss: true
      $name: Close when focus is lost
      $description: Dismiss the overview when it loses activation.
    - WrapNavigation: true
      $name: Wrap grid navigation
      $description: Arrow keys wrap around the edges of the grid.
    - VimNavigation: true
      $name: Vim navigation
      $description: Use h/j/k/l to move, / to focus the search and x to close the selected window.
  $name: Behavior
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <dwmapi.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <tlhelp32.h>
#include <windowsx.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// COMPILATION-TIME NAMES AND MESSAGES

static const WCHAR kOverlayClass[] = L"OverhauldedWinTabOverlay";
static const WCHAR kControlClass[] = L"OverhauldedWinTabInput";
static const WCHAR kChipLayerClass[] = L"OverhauldedWinTabChipLayer";
static const WCHAR kControlTitleIdle[] = L"Overhaulded Win+Tab";
static const WCHAR kControlTitleReady[] = L"Overhaulded Win+Tab (ready)";
static const WCHAR kHotkeyMessageName[] = L"OverhauldedWinTab_Hotkey";

static const WCHAR kExplorerThreadName[] = L"Immersive Shell";

// Flag forwarded by the Explorer component.
static const WPARAM kHotkeyFlagWinTab = 1;

// Thread messages used by the tool process.
#define WM_UI_QUIT (WM_APP + 1)
#define WM_UI_SETTINGS (WM_APP + 2)

// Overlay timers.
enum
{
    kTimerFrame = 1,
    kTimerIdle = 2,
    kTimerCaret = 3,
    kTimerDesktop = 4,
    kTimerHeldWatch = 5,
    kTimerCarousel = 6,
};

// Manual GUIDs: the tool is compiled without __uuidof support.
static const IID kIidD2D1Factory = {
    0x06152247, 0x6f50, 0x465a, {0x92, 0x45, 0x11, 0x8b, 0xfd, 0x3b, 0x60, 0x07}};
static const IID kIidDWriteFactory = {
    0xb859ee5a, 0xd838, 0x4b5b, {0xa2, 0xe8, 0x1a, 0xdc, 0x7d, 0x93, 0xdb, 0x48}};
static const IID kIidVirtualDesktopManager = {
    0xa5cd92ff, 0x29be, 0x454c, {0x8d, 0x04, 0xd8, 0x28, 0x79, 0xfb, 0x3f, 0x1b}};
static const CLSID kClsidVirtualDesktopManager = {
    0xaa509086, 0x5ca9, 0x4c25, {0x8f, 0x95, 0x58, 0x9d, 0x3c, 0x07, 0xb4, 0x8a}};

// Shell internals used for switching straight to a desktop. The ids are the
// documented-by-reverse-engineering ones that have been stable on Windows 11
// since 21H2; the layout only matters up to SwitchDesktop, which sits before the
// per-build additions, so these offsets are safe across builds.
static const CLSID kClsidImmersiveShell = {
    0xc2f03a33, 0x21f5, 0x47fa, {0xb4, 0xbb, 0x15, 0x63, 0x62, 0xa2, 0xf2, 0x39}};
static const CLSID kClsidVirtualDesktopManagerInternal = {
    0xc5e0cdca, 0x7b6e, 0x41b2, {0x9f, 0xc4, 0xd9, 0x39, 0x75, 0xcc, 0x46, 0x7b}};
static const IID kIidShellServiceProvider = {
    0x6d5140c1, 0x7436, 0x11ce, {0x80, 0x34, 0x00, 0xaa, 0x00, 0x60, 0x09, 0xfa}};
static const IID kIidVirtualDesktopManagerInternal = {
    0x53f5ca0b, 0x158f, 0x4124, {0x90, 0x0c, 0x05, 0x71, 0x58, 0x06, 0x0b, 0x27}};
static const IID kIidVirtualDesktop = {
    0x3f07f4be, 0xb107, 0x441a, {0xaf, 0x0f, 0x39, 0xd8, 0x25, 0x29, 0x07, 0x2c}};
static const IID kIidApplicationViewCollection = {
    0x1841c6d7, 0x4f9d, 0x42c0, {0xaf, 0x41, 0x87, 0x47, 0x53, 0x8f, 0x10, 0xe5}};

////////////////////////////////////////////////////////////////////////////////
// SMALL HELPERS

struct RectF
{
    float l = 0.0f, t = 0.0f, r = 0.0f, b = 0.0f;

    float W() const { return r - l; }
    float H() const { return b - t; }
};

static bool Contains(const RectF& rect, float x, float y)
{
    return x >= rect.l && x < rect.r && y >= rect.t && y < rect.b;
}

// 0xAARRGGBB -> D2D color, optionally multiplied by an extra opacity factor.
static D2D1_COLOR_F ColorOf(UINT32 argb, float multiply = 1.0f)
{
    const float a = static_cast<float>((argb >> 24) & 0xFF) / 255.0f * multiply;
    const float r = static_cast<float>((argb >> 16) & 0xFF) / 255.0f;
    const float g = static_cast<float>((argb >> 8) & 0xFF) / 255.0f;
    const float b = static_cast<float>(argb & 0xFF) / 255.0f;
    return D2D1::ColorF(r, g, b, a);
}

static float EaseOutCubic(float t)
{
    const float inv = 1.0f - t;
    return 1.0f - inv * inv * inv;
}

static RectF ScaleAbout(const RectF& rect, float k, float cx, float cy)
{
    RectF out;
    out.l = cx + (rect.l - cx) * k;
    out.t = cy + (rect.t - cy) * k;
    out.r = cx + (rect.r - cx) * k;
    out.b = cy + (rect.b - cy) * k;
    return out;
}

static RECT ToRect(const RectF& rect)
{
    RECT r;
    r.left = static_cast<LONG>(std::lround(rect.l));
    r.top = static_cast<LONG>(std::lround(rect.t));
    r.right = static_cast<LONG>(std::lround(rect.r));
    r.bottom = static_cast<LONG>(std::lround(rect.b));
    return r;
}

static std::wstring ToLower(const std::wstring& text)
{
    std::wstring out = text;
    for (WCHAR& ch : out)
        ch = static_cast<WCHAR>(towlower(ch));
    return out;
}

static bool ContainsInsensitive(const std::wstring& haystackLower,
                                const std::wstring& needleLower)
{
    return haystackLower.find(needleLower) != std::wstring::npos;
}

////////////////////////////////////////////////////////////////////////////////
// STATE

static HINSTANCE g_hModule = nullptr;

// Background modes.
enum class BackgroundMode
{
    Acrylic,
    Mica,
    MicaAlt,
    Blur,
    Solid,
    None
};

// Desktop strip presentation.
enum class StripStyle
{
    Flat,
    Carousel
};

// Shape of a desktop tab.
enum class TabStyle
{
    Pill,
    Chip,
    Cards
};

// Panel behind the desktop tabs.
enum class StripBackground
{
    Auto,
    Show,
    Hide
};

// Window grid presentation.
enum class WindowTabStyle
{
    Cards,
    Chips
};

enum class WindowChipContent
{
    Preview,
    Icon,
    Blank
};

// Palette used by both desktop and window chips.
enum class ChipColorMode
{
    Theme,
    Single,
    Palette,
    Classic
};

// How the selected and active desktop tabs are marked.
enum class DesktopSelection
{
    Highlight,
    Lift
};

// Where held windows are shown.
enum class HeldDock
{
    Off,
    Left,
    Right
};

// Settings.
static UINT32 g_accent = 0xFF4CC2FF;
static BackgroundMode g_backgroundMode = BackgroundMode::Acrylic;
static UINT32 g_backgroundColor = 0xFF0A0D12;
static float g_backgroundOpacity = 0.70f;
static bool g_showIcons = true;
static bool g_showHints = true;
static bool g_searchAlwaysVisible = true;
static StripStyle g_stripStyle = StripStyle::Flat;
static TabStyle g_tabStyle = TabStyle::Pill;
static StripBackground g_stripBackground = StripBackground::Auto;
static float g_cardScale = 1.0f;
static int g_animSpeedPercent = 100;
static bool g_closeOnFocusLoss = true;
static bool g_wrapNavigation = true;
static bool g_wrapDesktopStrip = true;
static bool g_vimNavigation = true;
static std::wstring g_titleText = L"Task View";
static WindowTabStyle g_windowTabStyle = WindowTabStyle::Cards;
static WindowChipContent g_windowChipContent = WindowChipContent::Preview;
static float g_windowChipScale = 1.0f;
static ChipColorMode g_chipColorMode = ChipColorMode::Theme;
static UINT32 g_chipColor = 0xFF1E5AA8;
static std::vector<UINT32> g_chipPalette;
static std::vector<UINT32> g_themeChipColors;
static DesktopSelection g_desktopSelection = DesktopSelection::Highlight;
static HeldDock g_heldDock = HeldDock::Off;
static bool g_heldDockBackground = true;
static bool g_liftHeldWindows = true;
static bool g_liftHoveredWindows = false;
static bool g_liftSelectedWindow = false;
static bool g_cardAnimations = true;

// Overlay window and presentation.
static HWND g_overlay = nullptr;
static HWND g_control = nullptr;
static bool g_visible = false;
static bool g_glass = false;
static float g_presence = 0.0f;
static float g_targetPresence = 0.0f;
static ULONGLONG g_lastFrameTick = 0;
static ULONGLONG g_shownAtTick = 0;
static HWND g_originWindow = nullptr;
static bool g_closingForActivation = false;

// Monitor geometry, in physical pixels.
static int g_monitorX = 0;
static int g_monitorY = 0;
static int g_monitorW = 0;
static int g_monitorH = 0;
static float g_scale = 1.0f;
static UINT g_dpi = 96;

// Interaction state.
static std::wstring g_search;
static bool g_searchFocused = false;
static bool g_searchSelectAll = false;
static bool g_searchAllDesktops = false;
static int g_selected = 0;
static int g_page = 0;
static bool g_focusStrip = false;
static bool g_focusDock = false;
static int g_dockSelected = 0;
static int g_desktopSelected = 0;
static bool g_busy = false;
static bool g_trackingMouse = false;
static int g_hoverCard = -1;
static int g_hoverClose = -1;
static int g_hoverDock = -1;
static int g_hoverDockClose = -1;
static int g_hoverPill = -1;
static int g_hoverPillClose = -1;
static bool g_hoverCreate = false;
static bool g_hoverSearch = false;
static bool g_hoverSearchClear = false;
static bool g_createDragging = false;
static POINT g_createDragStart = {};
static float g_createPull = 0.0f;

// Inline virtual desktop rename.
static int g_renameDesktop = -1;
static std::wstring g_renameText;

// Tasks the user has "held" with u. A held task is framed in its own colour and
// is carried along when the active desktop changes, so it follows the user until
// it is released with u again.
struct HeldTask
{
    HWND hwnd = nullptr;
    UINT32 color = 0;
};
static std::vector<HeldTask> g_held;
static int g_nextHeldColor = 0;

// True while waiting for the desktop number after pressing m.
static bool g_pendingMove = false;

// Last desktop seen by the background watcher (see ControlWndProc).
static GUID g_watchedDesktop = {};
static bool g_hasWatchedDesktop = false;
static bool g_heldWatchOn = false;

// Data model.
struct WindowEntry
{
    HWND hwnd = nullptr;
    DWORD pid = 0;
    std::wstring title;
    std::wstring titleLower;
    std::wstring app;
    std::wstring appLower;
    GUID desktopId = {};
    int desktopIndex = -1;
    bool onCurrentDesktop = true;
    ID2D1Bitmap* icon = nullptr;
    float iconSize = 0.0f;
};

struct DesktopInfo
{
    GUID id = {};
    std::wstring name;
};

static std::vector<WindowEntry> g_windows;
static std::vector<int> g_filtered;
static std::vector<DesktopInfo> g_desktops;
static int g_currentDesktop = 0;
static IVirtualDesktopManager* g_vdm = nullptr;
static IUnknown* g_vdInternal = nullptr;
static IUnknown* g_viewCollection = nullptr;
static bool g_vdInternalResolved = false;
static int g_pendingDesktopTarget = -1;
static int g_pendingDesktopTries = 0;
static HWND g_pendingActivateWindow = nullptr;
static int g_pendingActivateDesktop = -1;
static bool g_desktopActionCreate = false;
static bool g_desktopActionClose = false;
static int g_desktopActionStartCount = 0;
static ULONGLONG g_busySince = 0;
static bool g_keepThumbnailsWhileBusy = false;
static float g_carouselPos = 0.0f;
static ULONGLONG g_lastCarouselTick = 0;

// Direct2D / DirectWrite.
static ID2D1Factory* g_d2dFactory = nullptr;
static ID2D1DCRenderTarget* g_d2dTarget = nullptr;
static ID2D1SolidColorBrush* g_d2dBrush = nullptr;
static ID2D1Layer* g_d2dLayer = nullptr;
static IDWriteFactory* g_dwrite = nullptr;
static IDWriteTextFormat* g_fmtTitle = nullptr;
static IDWriteTextFormat* g_fmtCard = nullptr;
static IDWriteTextFormat* g_fmtSearch = nullptr;
static IDWriteTextFormat* g_fmtPill = nullptr;
static IDWriteTextFormat* g_fmtPillLarge = nullptr;
static IDWriteTextFormat* g_fmtCardSuit = nullptr;
static IDWriteTextFormat* g_fmtCardSuitBig = nullptr;
static IDWriteTextFormat* g_fmtChipSuit = nullptr;
static IDWriteTextFormat* g_fmtHint = nullptr;
static IDWriteTextFormat* g_fmtEmpty = nullptr;
static IDWriteInlineObject* g_ellipsis = nullptr;
static float g_fontScale = 0.0f;

// Layout results, rebuilt on demand.
struct LayoutState
{
    float w = 0.0f, h = 0.0f, s = 1.0f;
    RectF search, grid, strip;
    float gap = 0.0f, cardW = 0.0f, cardH = 0.0f;
    int cols = 1, rows = 1, perPage = 1;
    int pageCount = 1;
};

struct CardView
{
    int entry = -1;     // Index into g_windows.
    int filtered = -1;  // Index into g_filtered, or -1 when a held dock item is
                        // hidden by the current search.
    bool docked = false;
    float lift = 0.0f;
    RectF rect, hit, header, preview, close;
};

struct PillView
{
    int desktop = -1;
    RectF rect, closeRect, hit, closeHit;
    bool hasClose = false;
    bool visible = true;
    float angle = 0.0f;  // Degrees, around the pill centre.
    float scale = 1.0f;
    float alpha = 1.0f;
    float depth = 0.0f;  // Signed distance from the carousel centre.
    float lift = 0.0f;   // Screen-space lift for the pick-up selection style.
};

static LayoutState g_layout;
static std::vector<CardView> g_cards;
static std::vector<CardView> g_dockCards;
static std::vector<PillView> g_pills;
static std::vector<int> g_display;  // Filtered indices shown in the grid.
static RectF g_dockArea;
static RectF g_createRect;
static RectF g_searchClearRect;

// Playing-card desktop animations. A draw animation lifts a face-down card
// from the create deck before the new desktop is created; a throw animation
// tosses a closing desktop card up and off the strip.
enum class CardAnimationMode
{
    None,
    Draw,
    Throw
};

struct CardAnimation
{
    CardAnimationMode mode = CardAnimationMode::None;
    GUID desktopId = {};
    int number = 0;
    int suit = 0;
    std::wstring name;
    RectF from, to;
    float fromScale = 1.0f;
    float toScale = 1.0f;
    float fromAngle = 0.0f;
    float toAngle = 0.0f;
    ULONGLONG start = 0;
    float duration = 0.4f;
};
static CardAnimation g_cardAnim;
static bool g_createAfterDraw = false;

// DWM thumbnails. Window squares keep their thumbnails on the overlay; window
// chips use a separate top-level host so a full-screen layered mask can cover
// the square thumbnail corners and leave a circular preview.
struct ThumbnailSet
{
    std::vector<HTHUMBNAIL> handles;
    std::vector<HWND> sources;
};
static ThumbnailSet g_overlayThumbs;
static ThumbnailSet g_chipThumbs;
static HWND g_thumbHost = nullptr;
static HWND g_chipMask = nullptr;
static bool g_chipLayersVisible = false;
static HBITMAP g_maskBitmap = nullptr;
static HGDIOBJ g_maskOldBitmap = nullptr;
static HDC g_maskDC = nullptr;
static void* g_maskBits = nullptr;
static int g_maskW = 0;
static int g_maskH = 0;
static uint64_t g_chipRegionHash = 0;

// Hotkey plumbing.
static UINT g_hotkeyMessage = 0;

// Forward declarations.
static void ReleaseThumbnails();
static void BeginDesktopAction(int targetDesktop, bool create, bool closeActive);
static void RebuildWindowList();
static void RefreshDesktops();
static void MoveSelectedWindowToDesktop(int delta);
static void MoveSelectedWindowToDesktopIndex(int index);
static void ToggleHold();
static void StartHeldWatch();
static void StopHeldWatch();
static bool MoveWindowToDesktopInternal(HWND window, const GUID& id);
static void SwitchDesktopBy(int delta);
static void BeginRenameDesktop(int index);
static void CommitRenameDesktop();
static void CancelRenameDesktop();
static void KickCarousel();
static float BackgroundScrimAlpha();
static bool DockExists();
static void ClearCardAnimation();
static void KickCardAnimation();
static void StartDesktopCreateDraw();
static void StartDesktopCardThrow(int desktop);
static void ReleaseChipMaskSurface();
static void SetChipLayersVisible(bool visible);

// Windhawk tool mod callbacks.
BOOL WhTool_ModInit();
void WhTool_ModSettingsChanged();
void WhTool_ModUninit();

// Windhawk tool mod scaffolding.
static bool g_isExplorer = false;
static HANDLE g_uiThread = nullptr;
static DWORD g_uiThreadId = 0;
static HANDLE g_uiReadyEvent = nullptr;
static volatile LONG g_uiInitOk = 0;

////////////////////////////////////////////////////////////////////////////////
// SETTINGS

////////////////////////////////////////////////////////////////////////////////
// THEME

enum class Palette
{
    Custom,
    CatppuccinMocha,
    CatppuccinMacchiato,
    CatppuccinFrappe,
    CatppuccinLatte,
    Nord,
    Dracula,
    TokyoNight,
    Gruvbox,
    RosePine,
};

// Every color the renderer needs, as 0xAARRGGBB.
struct ThemeColors
{
    UINT32 background;
    UINT32 accent;
    UINT32 text;
    UINT32 cardFill;
    UINT32 cardHover;
    UINT32 cardSelected;
    UINT32 previewFill;
    UINT32 searchFill;
    UINT32 stripFill;
    UINT32 pillFill;
    UINT32 pillHover;
    UINT32 pillActive;
    UINT32 pillActiveHover;
    UINT32 onAccent;
    UINT32 danger;
};

static Palette g_palette = Palette::Custom;
static ThemeColors g_theme = {};

// Linear blend between two 0xAARRGGBB colors; t = 0 keeps `a`, t = 1 gives `b`.
static UINT32 MixColor(UINT32 a, UINT32 b, float t)
{
    const float k = std::max(0.0f, std::min(1.0f, t));
    auto channel = [k](unsigned int x, unsigned int y) {
        return static_cast<UINT32>(std::lround(x + (static_cast<float>(y) - x) * k)) & 0xFF;
    };
    return (channel((a >> 24) & 0xFF, (b >> 24) & 0xFF) << 24) |
           (channel((a >> 16) & 0xFF, (b >> 16) & 0xFF) << 16) |
           (channel((a >> 8) & 0xFF, (b >> 8) & 0xFF) << 8) |
           channel(a & 0xFF, b & 0xFF);
}

// Builds a full palette from a few base colors; the hover and selection fills are
// derived so that every theme stays coherent without listing every shade.
static ThemeColors BuildTheme(UINT32 background, UINT32 surface, UINT32 text, UINT32 accent,
                              UINT32 onAccent, UINT32 danger, bool light)
{
    ThemeColors t = {};
    t.background = background;
    t.accent = accent;
    t.text = text;
    t.cardFill = surface;
    t.cardHover = MixColor(surface, text, light ? 0.06f : 0.05f);
    t.cardSelected = MixColor(surface, accent, 0.14f);
    t.previewFill = MixColor(surface, light ? 0xFFFFFFFF : 0xFF000000, light ? 0.06f : 0.55f);
    t.searchFill = MixColor(surface, text, light ? 0.05f : 0.06f);
    t.stripFill = surface;
    t.pillFill = MixColor(surface, text, light ? 0.05f : 0.03f);
    t.pillHover = MixColor(surface, text, light ? 0.09f : 0.07f);
    t.pillActive = MixColor(surface, accent, 0.16f);
    t.pillActiveHover = MixColor(surface, accent, 0.24f);
    t.onAccent = onAccent;
    t.danger = danger;
    return t;
}

static void ResolveTheme()
{
    switch (g_palette)
    {
    case Palette::CatppuccinMocha:
        g_theme = BuildTheme(0xFF1E1E2E, 0xFF181825, 0xFFCDD6F4, 0xFFCBA6F7, 0xFF11111B,
                             0xFFF38BA8, false);
        break;
    case Palette::CatppuccinMacchiato:
        g_theme = BuildTheme(0xFF24273A, 0xFF1E2030, 0xFFCAD3F5, 0xFFC6A0F6, 0xFF181926,
                             0xFFED8796, false);
        break;
    case Palette::CatppuccinFrappe:
        g_theme = BuildTheme(0xFF303446, 0xFF292C3C, 0xFFC6D0F5, 0xFFCA9EE6, 0xFF232634,
                             0xFFE78284, false);
        break;
    case Palette::CatppuccinLatte:
        g_theme = BuildTheme(0xFFEFF1F5, 0xFFE6E9EF, 0xFF4C4F69, 0xFF8839EF, 0xFFFFFFFF,
                             0xFFD20F39, true);
        break;
    case Palette::Nord:
        g_theme = BuildTheme(0xFF2E3440, 0xFF3B4252, 0xFFD8DEE9, 0xFF88C0D0, 0xFF2E3440,
                             0xFFBF616A, false);
        break;
    case Palette::Dracula:
        g_theme = BuildTheme(0xFF282A36, 0xFF343746, 0xFFF8F8F2, 0xFFBD93F9, 0xFF282A36,
                             0xFFFF5555, false);
        break;
    case Palette::TokyoNight:
        g_theme = BuildTheme(0xFF1A1B26, 0xFF24283B, 0xFFC0CAF5, 0xFF7AA2F7, 0xFF1A1B26,
                             0xFFF7768E, false);
        break;
    case Palette::Gruvbox:
        g_theme = BuildTheme(0xFF282828, 0xFF32302F, 0xFFEBDBB2, 0xFFFABD2F, 0xFF282828,
                             0xFFFB4934, false);
        break;
    case Palette::RosePine:
        g_theme = BuildTheme(0xFF191724, 0xFF1F1D2E, 0xFFE0DEF4, 0xFFC4A7E7, 0xFF191724,
                             0xFFEB6F92, false);
        break;
    case Palette::Custom:
    default:
    {
        // The accent and background pickers, with the original dark surfaces so
        // the custom palette renders exactly as it always has.
        ThemeColors t = {};
        t.background = g_backgroundColor;
        t.accent = g_accent;
        t.text = 0xFFFFFFFF;
        t.cardFill = 0xFF0B0E14;
        t.cardHover = 0xFF11151D;
        t.cardSelected = 0xFF141A24;
        t.previewFill = 0xFF04060A;
        t.searchFill = 0xFF141821;
        t.stripFill = 0xFF0B0E14;
        t.pillFill = 0xFF12151C;
        t.pillHover = 0xFF181D26;
        t.pillActive = 0xFF1B2432;
        t.pillActiveHover = 0xFF223046;
        t.onAccent = 0xFF06121C;
        t.danger = 0xFFE81123;
        g_theme = t;
        break;
    }
    }

    // A coherent set of chip colours derived from the active accent. The first
    // entry is the accent itself, so the most important chip always matches the
    // theme; the others are lighter, darker and complementary shades.
    g_themeChipColors.clear();
    g_themeChipColors.push_back(g_theme.accent);
    g_themeChipColors.push_back(MixColor(g_theme.accent, 0xFFFFFFFF, 0.30f));
    g_themeChipColors.push_back(MixColor(g_theme.accent, 0xFF000000, 0.28f));
    g_themeChipColors.push_back(MixColor(g_theme.accent, g_theme.danger, 0.42f));
    g_themeChipColors.push_back(MixColor(g_theme.accent, g_theme.text, 0.24f));
    g_themeChipColors.push_back(MixColor(g_theme.accent, 0xFFFFFFFF, 0.56f));
}

static void LoadSettings()
{
    auto read = [](PCWSTR key) {
        PCWSTR value = Wh_GetStringSetting(key);
        std::wstring result(value ? value : L"");
        Wh_FreeStringSetting(value);
        return result;
    };

    auto clampInt = [](int value, int low, int high) {
        return std::max(low, std::min(high, value));
    };

    // Accepts "#RRGGBB" or "RRGGBB"; anything else falls back to the default.
    auto parseColor = [](const std::wstring& raw, UINT32 fallback) -> UINT32 {
        std::wstring value = raw;
        size_t first = value.find_first_not_of(L" \t");
        if (first == std::wstring::npos)
            return fallback;
        size_t last = value.find_last_not_of(L" \t");
        value = value.substr(first, last - first + 1);
        if (!value.empty() && value[0] == L'#')
            value.erase(0, 1);
        if (value.size() != 6)
            return fallback;
        unsigned long rgb = 0;
        for (WCHAR ch : value)
        {
            unsigned long digit;
            if (ch >= L'0' && ch <= L'9')
                digit = ch - L'0';
            else if (ch >= L'a' && ch <= L'f')
                digit = ch - L'a' + 10;
            else if (ch >= L'A' && ch <= L'F')
                digit = ch - L'A' + 10;
            else
                return fallback;
            rgb = rgb * 16 + digit;
        }
        return 0xFF000000u | static_cast<UINT32>(rgb);
    };

    g_accent = parseColor(read(L"Appearance.AccentColor"), 0xFF4CC2FF);
    g_backgroundColor = parseColor(read(L"Appearance.BackgroundColor"), 0xFF0A0D12);
    g_backgroundOpacity = static_cast<float>(
        clampInt(Wh_GetIntSetting(L"Appearance.BackgroundOpacity"), 0, 100)) / 100.0f;

    const std::wstring background = read(L"Appearance.Background");
    g_backgroundMode = background == L"mica" ? BackgroundMode::Mica
                     : background == L"micaalt" ? BackgroundMode::MicaAlt
                     : background == L"blur" ? BackgroundMode::Blur
                     : background == L"solid" ? BackgroundMode::Solid
                     : background == L"none" ? BackgroundMode::None
                     : BackgroundMode::Acrylic;

    g_showIcons = Wh_GetIntSetting(L"WindowTabs.ShowIcons") != 0;
    g_showHints = Wh_GetIntSetting(L"Appearance.ShowHints") != 0;
    g_searchAlwaysVisible = Wh_GetIntSetting(L"Appearance.AlwaysShowSearch") != 0;

    const std::wstring windowTabs = read(L"WindowTabs.Style");
    g_windowTabStyle = windowTabs == L"chips" ? WindowTabStyle::Chips
                                               : WindowTabStyle::Cards;

    const std::wstring chipContent = read(L"WindowTabs.ChipContent");
    g_windowChipContent = chipContent == L"icon" ? WindowChipContent::Icon
                        : chipContent == L"blank" ? WindowChipContent::Blank
                                                   : WindowChipContent::Preview;

    const std::wstring chipSize = read(L"WindowTabs.ChipSize");
    g_windowChipScale = chipSize == L"small" ? 0.82f
                      : chipSize == L"large" ? 1.22f
                      : chipSize == L"extra-large" ? 1.45f
                                                   : 1.0f;

    const std::wstring chipMode = read(L"Chips.Mode");
    g_chipColorMode = chipMode == L"single" ? ChipColorMode::Single
                    : chipMode == L"palette" ? ChipColorMode::Palette
                    : chipMode == L"classic" ? ChipColorMode::Classic
                                             : ChipColorMode::Theme;
    g_chipColor = parseColor(read(L"Chips.Color"), 0xFF1E5AA8);

    g_chipPalette.clear();
    const std::wstring paletteText = read(L"Chips.Palette");
    size_t paletteStart = 0;
    while (paletteStart <= paletteText.size())
    {
        const size_t comma = paletteText.find(L',', paletteStart);
        const std::wstring token = paletteText.substr(
            paletteStart, comma == std::wstring::npos ? std::wstring::npos
                                                       : comma - paletteStart);
        const UINT32 color = parseColor(token, 0);
        if (color)
            g_chipPalette.push_back(color);
        if (comma == std::wstring::npos)
            break;
        paletteStart = comma + 1;
    }
    if (g_chipPalette.empty())
    {
        g_chipPalette = {0xFFB3261E, 0xFF1E5AA8, 0xFF1E7A46, 0xFF6A3D9A,
                         0xFFB45F06, 0xFF26262B};
    }

    const std::wstring desktopSelection = read(L"DesktopStrip.Selection");
    g_desktopSelection = desktopSelection == L"lift" ? DesktopSelection::Lift
                                                      : DesktopSelection::Highlight;

    const std::wstring heldDock = read(L"HeldWindows.Mode");
    g_heldDock = heldDock == L"left" ? HeldDock::Left
               : heldDock == L"right" ? HeldDock::Right
                                      : HeldDock::Off;
    g_heldDockBackground = Wh_GetIntSetting(L"HeldWindows.DockBackground") != 0;
    g_liftHeldWindows = Wh_GetIntSetting(L"HeldWindows.LiftHeld") != 0;
    g_liftHoveredWindows = Wh_GetIntSetting(L"WindowTabs.LiftHovered") != 0;
    g_liftSelectedWindow = Wh_GetIntSetting(L"WindowTabs.LiftSelected") != 0;

    const std::wstring strip = read(L"DesktopStrip.Layout");
    const std::wstring tabs = read(L"DesktopStrip.Tabs");
    g_stripStyle = strip == L"carousel" ? StripStyle::Carousel
                                        : StripStyle::Flat;
    g_tabStyle = tabs == L"chip" ? TabStyle::Chip
               : tabs == L"cards" ? TabStyle::Cards
                                  : TabStyle::Pill;

    const std::wstring cardSize = read(L"Cards.Size");
    g_cardScale = cardSize == L"small" ? 0.82f
                : cardSize == L"large" ? 1.22f
                                       : 1.0f;

    const std::wstring title = read(L"Appearance.Title");
    g_titleText = title.empty() ? L"Task View" : title;

    const std::wstring stripBackground = read(L"DesktopStrip.Background");
    g_stripBackground = stripBackground == L"show" ? StripBackground::Show
                      : stripBackground == L"hide" ? StripBackground::Hide
                                                   : StripBackground::Auto;

    const std::wstring speed = read(L"Appearance.AnimationSpeed");
    g_animSpeedPercent = speed == L"75" ? 75 : speed == L"125" ? 125
                        : speed == L"150" ? 150 : 100;

    g_cardAnimations = Wh_GetIntSetting(L"Cards.Animations") != 0;

    g_closeOnFocusLoss = Wh_GetIntSetting(L"Behavior.CloseOnFocusLoss") != 0;
    g_wrapNavigation = Wh_GetIntSetting(L"Behavior.WrapNavigation") != 0;
    g_wrapDesktopStrip = Wh_GetIntSetting(L"DesktopStrip.Wrap") != 0;
    g_vimNavigation = Wh_GetIntSetting(L"Behavior.VimNavigation") != 0;

    const std::wstring theme = read(L"Appearance.Theme");
    g_palette = theme == L"catppuccin-mocha" ? Palette::CatppuccinMocha
              : theme == L"catppuccin-macchiato" ? Palette::CatppuccinMacchiato
              : theme == L"catppuccin-frappe" ? Palette::CatppuccinFrappe
              : theme == L"catppuccin-latte" ? Palette::CatppuccinLatte
              : theme == L"nord" ? Palette::Nord
              : theme == L"dracula" ? Palette::Dracula
              : theme == L"tokyo-night" ? Palette::TokyoNight
              : theme == L"gruvbox" ? Palette::Gruvbox
              : theme == L"rose-pine" ? Palette::RosePine
              : Palette::Custom;
    ResolveTheme();
}

static float AnimationSeconds(float baseSeconds)
{
    return baseSeconds * 100.0f / static_cast<float>(g_animSpeedPercent);
}

////////////////////////////////////////////////////////////////////////////////
// DIRECT2D / DIRECTWRITE LIFETIME

static void ReleaseIcons()
{
    for (WindowEntry& entry : g_windows)
    {
        if (entry.icon)
        {
            entry.icon->Release();
            entry.icon = nullptr;
        }
        entry.iconSize = 0.0f;
    }
}

static void ReleaseDeviceResources()
{
    ReleaseIcons();
    if (g_d2dLayer) { g_d2dLayer->Release(); g_d2dLayer = nullptr; }
    if (g_d2dBrush) { g_d2dBrush->Release(); g_d2dBrush = nullptr; }
    if (g_d2dTarget) { g_d2dTarget->Release(); g_d2dTarget = nullptr; }
}

static void ReleaseTextFormats()
{
    auto release = [](IDWriteTextFormat*& format) {
        if (format) { format->Release(); format = nullptr; }
    };
    release(g_fmtTitle);
    release(g_fmtCard);
    release(g_fmtSearch);
    release(g_fmtPill);
    release(g_fmtPillLarge);
    release(g_fmtCardSuit);
    release(g_fmtCardSuitBig);
    release(g_fmtChipSuit);
    release(g_fmtHint);
    release(g_fmtEmpty);
    if (g_ellipsis) { g_ellipsis->Release(); g_ellipsis = nullptr; }
    g_fontScale = 0.0f;
}

static void ReleaseGraphics()
{
    ReleaseDeviceResources();
    ReleaseTextFormats();
    if (g_dwrite) { g_dwrite->Release(); g_dwrite = nullptr; }
    if (g_d2dFactory) { g_d2dFactory->Release(); g_d2dFactory = nullptr; }
}

static bool EnsureFactories()
{
    if (!g_d2dFactory)
    {
        D2D1_FACTORY_OPTIONS options = {};
        if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                     kIidD2D1Factory, &options,
                                     reinterpret_cast<void**>(&g_d2dFactory))))
            g_d2dFactory = nullptr;
    }

    if (!g_dwrite)
    {
        if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, kIidDWriteFactory,
                                       reinterpret_cast<IUnknown**>(&g_dwrite))))
            g_dwrite = nullptr;
    }

    return g_d2dFactory != nullptr && g_dwrite != nullptr;
}

static bool EnsureDeviceResources()
{
    if (!g_d2dFactory)
        return false;

    if (!g_d2dTarget)
    {
        // Layout is expressed in physical pixels: keep the render target at
        // 96 DPI so 1 DIP equals 1 pixel, and scale the UI manually.
        D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                              D2D1_ALPHA_MODE_PREMULTIPLIED),
            96.0f, 96.0f, D2D1_RENDER_TARGET_USAGE_NONE,
            D2D1_FEATURE_LEVEL_DEFAULT);
        if (FAILED(g_d2dFactory->CreateDCRenderTarget(&properties, &g_d2dTarget)))
        {
            g_d2dTarget = nullptr;
            return false;
        }
    }

    if (!g_d2dBrush &&
        FAILED(g_d2dTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),
                                                  &g_d2dBrush)))
    {
        g_d2dBrush = nullptr;
        return false;
    }

    if (!g_d2dLayer && FAILED(g_d2dTarget->CreateLayer(nullptr, &g_d2dLayer)))
        g_d2dLayer = nullptr;

    return g_d2dBrush != nullptr;
}

static void EnsureTextFormats()
{
    if (!g_dwrite || g_fontScale == g_scale)
        return;

    ReleaseTextFormats();
    g_fontScale = g_scale;

    auto create = [](IDWriteFactory* factory, DWRITE_FONT_WEIGHT weight, float size,
                     IDWriteTextFormat** out) {
        return factory->CreateTextFormat(L"Segoe UI Variable Text", nullptr, weight,
                                         DWRITE_FONT_STYLE_NORMAL,
                                         DWRITE_FONT_STRETCH_NORMAL, size, L"", out);
    };

    create(g_dwrite, DWRITE_FONT_WEIGHT_SEMI_BOLD, 30.0f * g_scale, &g_fmtTitle);
    create(g_dwrite, DWRITE_FONT_WEIGHT_NORMAL, 13.0f * g_scale, &g_fmtCard);
    create(g_dwrite, DWRITE_FONT_WEIGHT_NORMAL, 15.0f * g_scale, &g_fmtSearch);
    create(g_dwrite, DWRITE_FONT_WEIGHT_MEDIUM, 13.0f * g_scale, &g_fmtPill);
    create(g_dwrite, DWRITE_FONT_WEIGHT_MEDIUM, 15.0f * g_scale, &g_fmtPillLarge);

    auto createSymbol = [](IDWriteFactory* factory, float size,
                           IDWriteTextFormat** out) {
        return factory->CreateTextFormat(L"Segoe UI Symbol", nullptr,
                                         DWRITE_FONT_WEIGHT_NORMAL,
                                         DWRITE_FONT_STYLE_NORMAL,
                                         DWRITE_FONT_STRETCH_NORMAL, size, L"", out);
    };
    createSymbol(g_dwrite, 15.0f * g_scale, &g_fmtCardSuit);
    createSymbol(g_dwrite, 44.0f * g_scale, &g_fmtCardSuitBig);
    createSymbol(g_dwrite, 11.0f * g_scale, &g_fmtChipSuit);
    create(g_dwrite, DWRITE_FONT_WEIGHT_NORMAL, 12.0f * g_scale, &g_fmtHint);
    create(g_dwrite, DWRITE_FONT_WEIGHT_MEDIUM, 17.0f * g_scale, &g_fmtEmpty);

    // Single-line ellipsis trimming for titles.
    if (g_fmtCard)
    {
        g_fmtCard->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        DWRITE_TRIMMING trimming = {};
        trimming.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
        if (SUCCEEDED(g_dwrite->CreateEllipsisTrimmingSign(g_fmtCard, &g_ellipsis)) &&
            g_ellipsis)
            g_fmtCard->SetTrimming(&trimming, g_ellipsis);
    }

    // The carousel gives every pill the same width, so long desktop names need
    // the same ellipsis treatment as window titles.
    if (g_fmtPill && g_ellipsis)
    {
        g_fmtPill->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        DWRITE_TRIMMING trimming = {};
        trimming.granularity = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
        g_fmtPill->SetTrimming(&trimming, g_ellipsis);
        if (g_fmtPillLarge)
        {
            g_fmtPillLarge->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            g_fmtPillLarge->SetTrimming(&trimming, g_ellipsis);
        }
        if (g_fmtHint)
        {
            g_fmtHint->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
            g_fmtHint->SetTrimming(&trimming, g_ellipsis);
        }
    }

    IDWriteTextFormat* formats[] = {
        g_fmtTitle,    g_fmtCard,     g_fmtSearch,   g_fmtPill,
        g_fmtPillLarge, g_fmtHint,    g_fmtEmpty,    g_fmtCardSuit,
        g_fmtCardSuitBig, g_fmtChipSuit};
    for (IDWriteTextFormat* format : formats)
    {
        if (format)
        {
            format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        }
    }
}

// Width in pixels of a single-line string in the given format.
static float MeasureTextWidth(const std::wstring& text, IDWriteTextFormat* format)
{
    if (!g_dwrite || !format || text.empty())
        return 0.0f;

    IDWriteTextLayout* layout = nullptr;
    if (FAILED(g_dwrite->CreateTextLayout(text.c_str(), static_cast<UINT32>(text.size()),
                                          format, 8192.0f, 8192.0f, &layout)) ||
        !layout)
        return 0.0f;

    // Trimming would report an ellipsized width, so measure with a large box and
    // read the full text width.
    DWRITE_TEXT_METRICS metrics = {};
    const HRESULT hr = layout->GetMetrics(&metrics);
    layout->Release();
    if (FAILED(hr))
        return 0.0f;
    return metrics.widthIncludingTrailingWhitespace;
}

////////////////////////////////////////////////////////////////////////////////
// ICONS

static HICON GetWindowIcon(HWND hwnd, const std::wstring& processPath, bool* owned)
{
    if (owned)
        *owned = false;

    if (!hwnd || !IsWindow(hwnd))
        return nullptr;

    ULONG_PTR result = 0;
    if (SendMessageTimeoutW(hwnd, WM_GETICON, ICON_BIG, 0,
                            SMTO_ABORTIFHUNG | SMTO_BLOCK, 15, &result) && result)
        return reinterpret_cast<HICON>(result);

    HICON icon = reinterpret_cast<HICON>(GetClassLongPtrW(hwnd, GCLP_HICON));
    if (icon)
        return icon;

    if (SendMessageTimeoutW(hwnd, WM_GETICON, ICON_SMALL2, 0,
                            SMTO_ABORTIFHUNG | SMTO_BLOCK, 15, &result) && result)
        return reinterpret_cast<HICON>(result);

    if (SendMessageTimeoutW(hwnd, WM_GETICON, ICON_SMALL, 0,
                            SMTO_ABORTIFHUNG | SMTO_BLOCK, 15, &result) && result)
        return reinterpret_cast<HICON>(result);

    icon = reinterpret_cast<HICON>(GetClassLongPtrW(hwnd, GCLP_HICONSM));
    if (icon)
        return icon;

    if (!processPath.empty())
    {
        HICON large = nullptr;
        if (ExtractIconExW(processPath.c_str(), 0, &large, nullptr, 1) > 0 && large)
        {
            if (owned)
                *owned = true;
            return large;
        }
    }

    return nullptr;
}

static ID2D1Bitmap* CreateIconBitmap(HICON icon, int size)
{
    if (!icon || size <= 0 || !g_d2dTarget)
        return nullptr;

    ICONINFO info = {};
    if (!GetIconInfo(icon, &info))
        return nullptr;

    BITMAPV5HEADER header = {};
    header.bV5Size = sizeof(header);
    header.bV5Width = size;
    header.bV5Height = -size;
    header.bV5Planes = 1;
    header.bV5BitCount = 32;
    header.bV5Compression = BI_BITFIELDS;
    header.bV5RedMask = 0x00FF0000;
    header.bV5GreenMask = 0x0000FF00;
    header.bV5BlueMask = 0x000000FF;
    header.bV5AlphaMask = 0xFF000000;

    HDC dc = CreateCompatibleDC(nullptr);
    void* bits = nullptr;
    HBITMAP dib = dc ? CreateDIBSection(dc, reinterpret_cast<BITMAPINFO*>(&header),
                                        DIB_RGB_COLORS, &bits, nullptr, 0)
                     : nullptr;

    ID2D1Bitmap* bitmap = nullptr;
    if (dc && dib && bits)
    {
        HGDIOBJ old = SelectObject(dc, dib);
        memset(bits, 0, static_cast<size_t>(size) * size * 4);
        DrawIconEx(dc, 0, 0, icon, size, size, 0, nullptr, DI_NORMAL);
        SelectObject(dc, old);

        // Direct2D expects premultiplied alpha.
        BYTE* pixels = static_cast<BYTE*>(bits);
        for (int i = 0; i < size * size; i++)
        {
            const BYTE alpha = pixels[i * 4 + 3];
            if (alpha != 0 && alpha != 255)
            {
                pixels[i * 4 + 0] = static_cast<BYTE>(pixels[i * 4 + 0] * alpha / 255);
                pixels[i * 4 + 1] = static_cast<BYTE>(pixels[i * 4 + 1] * alpha / 255);
                pixels[i * 4 + 2] = static_cast<BYTE>(pixels[i * 4 + 2] * alpha / 255);
            }
        }

        D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                              D2D1_ALPHA_MODE_PREMULTIPLIED));
        g_d2dTarget->CreateBitmap(D2D1::SizeU(size, size), bits, size * 4,
                                  properties, &bitmap);
    }

    if (dib)
        DeleteObject(dib);
    if (dc)
        DeleteDC(dc);
    if (info.hbmColor)
        DeleteObject(info.hbmColor);
    if (info.hbmMask)
        DeleteObject(info.hbmMask);
    return bitmap;
}

////////////////////////////////////////////////////////////////////////////////
// WINDOW AND DESKTOP ENUMERATION

static bool IsShellWindow(HWND hwnd)
{
    WCHAR className[128] = {};
    GetClassNameW(hwnd, className, ARRAYSIZE(className));
    return wcscmp(className, L"Progman") == 0 ||
           wcscmp(className, L"WorkerW") == 0 ||
           wcscmp(className, L"Shell_TrayWnd") == 0 ||
           wcscmp(className, L"Shell_SecondaryTrayWnd") == 0 ||
           wcscmp(className, L"Windows.UI.Core.CoreWindow") == 0;
}

static std::wstring GetProcessImagePath(DWORD pid)
{
    std::wstring path;
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process)
        return path;

    WCHAR buffer[MAX_PATH * 2] = {};
    DWORD size = ARRAYSIZE(buffer);
    if (QueryFullProcessImageNameW(process, 0, buffer, &size))
        path.assign(buffer, size);
    CloseHandle(process);
    return path;
}

static std::wstring BaseName(const std::wstring& path)
{
    size_t slash = path.find_last_of(L"\\/");
    std::wstring name = slash == std::wstring::npos ? path : path.substr(slash + 1);
    size_t dot = name.find_last_of(L'.');
    if (dot != std::wstring::npos && dot > 0)
        name = name.substr(0, dot);
    return name;
}

// Recreates the cached icon only when the requested pixel size changes. Window
// cards use a small icon in the header; poker chips can request a much larger
// one for the centre.
static ID2D1Bitmap* EnsureEntryIcon(WindowEntry& entry, int pixels)
{
    if (pixels <= 0)
        return nullptr;
    if (entry.icon && entry.iconSize == static_cast<float>(pixels))
        return entry.icon;

    if (entry.icon)
    {
        entry.icon->Release();
        entry.icon = nullptr;
    }
    entry.iconSize = 0.0f;

    bool owned = false;
    HICON hicon = GetWindowIcon(entry.hwnd, GetProcessImagePath(entry.pid), &owned);
    if (hicon)
    {
        entry.icon = CreateIconBitmap(hicon, pixels);
        entry.iconSize = static_cast<float>(pixels);
        if (owned)
            DestroyIcon(hicon);
    }
    return entry.icon;
}

static int DesktopIndexForId(const GUID& id)
{
    for (int i = 0; i < static_cast<int>(g_desktops.size()); i++)
        if (IsEqualGUID(g_desktops[i].id, id))
            return i;
    return -1;
}

static bool IsWindowOnCurrentDesktop(HWND hwnd)
{
    if (!g_vdm)
        return true;
    BOOL onCurrent = FALSE;
    if (SUCCEEDED(g_vdm->IsWindowOnCurrentVirtualDesktop(hwnd, &onCurrent)))
        return onCurrent != FALSE;
    return true;
}

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM)
{
    if (hwnd == g_overlay || hwnd == g_control)
        return TRUE;
    if (GetAncestor(hwnd, GA_ROOT) != hwnd)
        return TRUE;
    if (!IsWindowVisible(hwnd))
        return TRUE;
    if (IsShellWindow(hwnd))
        return TRUE;

    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    if ((style & WS_CHILD) != 0)
        return TRUE;

    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if ((exStyle & WS_EX_TOOLWINDOW) != 0)
        return TRUE;
    if ((exStyle & WS_EX_NOACTIVATE) != 0)
        return TRUE;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || pid == GetCurrentProcessId())
        return TRUE;

    // A window on an inactive desktop is normally DWM-cloaked, which is also
    // how UWP hides suspended windows. Resolve its desktop first so all-desktop
    // search can include the former without admitting cloaked windows on the
    // current desktop.
    GUID desktopId = {};
    int desktopIndex = -1;
    bool onCurrentDesktop = true;
    if (g_vdm)
    {
        GUID id = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(hwnd, &id)))
        {
            desktopId = id;
            desktopIndex = DesktopIndexForId(id);
        }
        // The documented check is authoritative for "visible here", including
        // windows pinned to every desktop, where the id may name only one of
        // them.
        onCurrentDesktop = IsWindowOnCurrentDesktop(hwnd);
    }
    // A window visible here but tagged with another desktop is pinned to all
    // desktops; it has no single desktop label.
    if (onCurrentDesktop && desktopIndex >= 0 &&
        desktopIndex != g_currentDesktop)
        desktopIndex = -1;

    const bool otherDesktop = !onCurrentDesktop;
    if (!g_searchAllDesktops && otherDesktop)
        return TRUE;

    DWORD cloaked = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked,
                                        sizeof(cloaked))) &&
        cloaked != 0 && !(g_searchAllDesktops && otherDesktop))
        return TRUE;

    int length = GetWindowTextLengthW(hwnd);
    if (length <= 0)
        return TRUE;

    std::wstring title(static_cast<size_t>(length) + 1, L'\0');
    int copied = GetWindowTextW(hwnd, title.data(), length + 1);
    title.resize(copied > 0 ? static_cast<size_t>(copied) : 0);
    if (title.empty())
        return TRUE;

    WindowEntry entry;
    entry.hwnd = hwnd;
    entry.pid = pid;
    entry.title = title;
    entry.titleLower = ToLower(title);
    entry.app = BaseName(GetProcessImagePath(pid));
    entry.appLower = ToLower(entry.app);
    entry.desktopId = desktopId;
    entry.desktopIndex = desktopIndex;
    entry.onCurrentDesktop = onCurrentDesktop;
    g_windows.push_back(std::move(entry));
    return TRUE;
}

static void RebuildFilter()
{
    g_filtered.clear();
    const std::wstring needle = ToLower(g_search);
    for (int i = 0; i < static_cast<int>(g_windows.size()); i++)
    {
        if (needle.empty() ||
            ContainsInsensitive(g_windows[i].titleLower, needle) ||
            ContainsInsensitive(g_windows[i].appLower, needle))
            g_filtered.push_back(i);
    }

    if (g_filtered.empty())
        g_selected = -1;
    else if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = static_cast<int>(g_filtered.size()) - 1;
}

static void RebuildWindowList()
{
    ReleaseIcons();
    g_windows.clear();
    EnumWindows(EnumWindowsProc, 0);
    if (g_searchAllDesktops)
    {
        // Keep z-order within each desktop, but group all-desktop results by
        // desktop so the numbered labels read in a predictable order.
        std::stable_sort(g_windows.begin(), g_windows.end(),
                         [](const WindowEntry& a, const WindowEntry& b) {
                             const int da =
                                 a.desktopIndex < 0 ? 1000000 : a.desktopIndex;
                             const int db =
                                 b.desktopIndex < 0 ? 1000000 : b.desktopIndex;
                             return da < db;
                         });
    }
    RebuildFilter();
    g_page = 0;
    if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = g_filtered.empty() ? -1 : static_cast<int>(g_filtered.size()) - 1;
}

// --- Virtual desktops -------------------------------------------------------

static bool ReadRegistryBinary(HKEY root, PCWSTR subKey, PCWSTR value,
                               std::vector<BYTE>& out)
{
    HKEY key = nullptr;
    if (RegOpenKeyExW(root, subKey, 0, KEY_READ, &key) != ERROR_SUCCESS)
        return false;

    DWORD type = 0;
    DWORD size = 0;
    bool ok = RegQueryValueExW(key, value, nullptr, &type, nullptr, &size) ==
                  ERROR_SUCCESS &&
              type == REG_BINARY && size > 0;
    if (ok)
    {
        out.resize(size);
        ok = RegQueryValueExW(key, value, nullptr, &type, out.data(), &size) ==
             ERROR_SUCCESS;
        if (ok)
            out.resize(size);
    }
    RegCloseKey(key);
    return ok;
}

static bool ReadRegistryString(HKEY root, PCWSTR subKey, PCWSTR value,
                               std::wstring& out)
{
    HKEY key = nullptr;
    if (RegOpenKeyExW(root, subKey, 0, KEY_READ, &key) != ERROR_SUCCESS)
        return false;

    WCHAR buffer[256] = {};
    DWORD size = sizeof(buffer);
    DWORD type = 0;
    bool ok = RegQueryValueExW(key, value, nullptr, &type,
                               reinterpret_cast<LPBYTE>(buffer), &size) ==
                  ERROR_SUCCESS &&
              (type == REG_SZ || type == REG_EXPAND_SZ);
    if (ok)
        out.assign(buffer);
    RegCloseKey(key);
    return ok;
}

static std::wstring DesktopNameFromRegistry(const GUID& id, int index)
{
    WCHAR guidText[64] = {};
    if (StringFromGUID2(id, guidText, ARRAYSIZE(guidText)) <= 0)
        return L"Desktop " + std::to_wstring(index + 1);

    const std::wstring prefix =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops\\Desktops\\";
    const std::wstring key = prefix + guidText;

    std::wstring name;
    if (!ReadRegistryString(HKEY_CURRENT_USER, key.c_str(), L"Name", name) || name.empty())
        ReadRegistryString(HKEY_CURRENT_USER, key.c_str(), L"DesktopName", name);
    if (name.empty())
        name = L"Desktop " + std::to_wstring(index + 1);
    return name;
}

static void RefreshDesktops()
{
    g_desktops.clear();

    std::vector<BYTE> ids;
    const std::wstring base =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops";
    if (ReadRegistryBinary(HKEY_CURRENT_USER, base.c_str(), L"VirtualDesktopIDs", ids) &&
        ids.size() >= sizeof(GUID))
    {
        const size_t count = ids.size() / sizeof(GUID);
        for (size_t i = 0; i < count; i++)
        {
            DesktopInfo info;
            memcpy(&info.id, ids.data() + i * sizeof(GUID), sizeof(GUID));
            info.name = DesktopNameFromRegistry(info.id, static_cast<int>(i));
            g_desktops.push_back(std::move(info));
        }
    }

    if (g_desktops.empty())
    {
        DesktopInfo info;
        info.name = L"Desktop 1";
        g_desktops.push_back(info);
    }

    // The overlay lives on the active desktop, so its own desktop id is
    // authoritative. The registry value is only a fallback.
    int current = -1;
    if (g_vdm && g_overlay)
    {
        GUID id = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(g_overlay, &id)))
        {
            for (int i = 0; i < static_cast<int>(g_desktops.size()); i++)
                if (IsEqualGUID(g_desktops[i].id, id))
                {
                    current = i;
                    break;
                }
        }
    }

    if (current < 0)
    {
        std::vector<BYTE> currentBytes;
        if (ReadRegistryBinary(HKEY_CURRENT_USER, base.c_str(),
                               L"CurrentVirtualDesktop", currentBytes) &&
            currentBytes.size() >= sizeof(GUID))
        {
            GUID id = {};
            memcpy(&id, currentBytes.data(), sizeof(GUID));
            for (int i = 0; i < static_cast<int>(g_desktops.size()); i++)
                if (IsEqualGUID(g_desktops[i].id, id))
                {
                    current = i;
                    break;
                }
        }
    }

    g_currentDesktop = current >= 0 ? current : 0;
    if (g_desktopSelected >= static_cast<int>(g_desktops.size()) || g_desktopSelected < 0)
        g_desktopSelected = g_currentDesktop;
}

// Reads the id of the desktop that is active right now. Used while the overlay
// is hidden, where the overlay window's own desktop id is stale.
static bool ReadActiveDesktopId(GUID* id)
{
    std::vector<BYTE> bytes;
    const std::wstring base =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops";
    if (!ReadRegistryBinary(HKEY_CURRENT_USER, base.c_str(), L"CurrentVirtualDesktop", bytes) ||
        bytes.size() < sizeof(GUID))
        return false;
    memcpy(id, bytes.data(), sizeof(GUID));
    return true;
}

// --- Virtual desktop names --------------------------------------------------

static bool WriteDesktopName(const GUID& id, const std::wstring& name)
{
    WCHAR guidText[64] = {};
    if (StringFromGUID2(id, guidText, ARRAYSIZE(guidText)) <= 0)
        return false;

    const std::wstring prefix =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops\\Desktops\\";
    const std::wstring key = prefix + guidText;

    HKEY handle = nullptr;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, key.c_str(), 0, nullptr, 0, KEY_SET_VALUE,
                        nullptr, &handle, nullptr) != ERROR_SUCCESS)
        return false;

    bool ok = true;
    if (name.empty())
    {
        const LONG result = RegDeleteValueW(handle, L"Name");
        ok = result == ERROR_SUCCESS || result == ERROR_FILE_NOT_FOUND;
    }
    else
    {
        ok = RegSetValueExW(handle, L"Name", 0, REG_SZ,
                            reinterpret_cast<const BYTE*>(name.c_str()),
                            static_cast<DWORD>((name.size() + 1) * sizeof(WCHAR))) ==
             ERROR_SUCCESS;
    }

    RegCloseKey(handle);
    return ok;
}

static void CommitRenameDesktop()
{
    if (g_renameDesktop < 0 || g_renameDesktop >= static_cast<int>(g_desktops.size()))
    {
        g_renameDesktop = -1;
        g_renameText.clear();
        return;
    }

    std::wstring name = g_renameText;
    // Trim surrounding whitespace; empty means "remove the custom name".
    size_t first = name.find_first_not_of(L" \t");
    size_t last = name.find_last_not_of(L" \t");
    name = first == std::wstring::npos ? L"" : name.substr(first, last - first + 1);

    if (WriteDesktopName(g_desktops[g_renameDesktop].id, name))
        g_desktops[g_renameDesktop].name = name.empty()
            ? L"Desktop " + std::to_wstring(g_renameDesktop + 1)
            : name;

    g_renameDesktop = -1;
    g_renameText.clear();
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void CancelRenameDesktop()
{
    g_renameDesktop = -1;
    g_renameText.clear();
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void BeginRenameDesktop(int index)
{
    if (index < 0 || index >= static_cast<int>(g_desktops.size()))
        return;
    g_renameDesktop = index;
    g_renameText = g_desktops[index].name;
    g_focusStrip = true;
    g_desktopSelected = index;
    g_searchFocused = false;
    g_searchSelectAll = false;
    KickCarousel();
    if (g_overlay)
        SetTimer(g_overlay, kTimerCaret, 530, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static bool IsRenamingDesktop()
{
    return g_renameDesktop >= 0;
}

// --- Desktop actions --------------------------------------------------------

// The window that the card actions apply to: the selected one, falling back to
// the window that opened the overview.
static HWND SelectedWindow()
{
    HWND window = nullptr;

    // The dock has its own keyboard cursor, so actions such as U, M and
    // Shift+Left/Right operate on the dock item while the dock has focus.
    if (g_focusDock && g_dockSelected >= 0 &&
        g_dockSelected < static_cast<int>(g_dockCards.size()))
    {
        const int entry = g_dockCards[g_dockSelected].entry;
        if (entry >= 0 && entry < static_cast<int>(g_windows.size()))
            window = g_windows[entry].hwnd;
    }

    if ((!window || !IsWindow(window)) && g_selected >= 0 &&
        g_selected < static_cast<int>(g_filtered.size()))
        window = g_windows[g_filtered[g_selected]].hwnd;
    if (!window || !IsWindow(window))
        window = g_originWindow;
    if (!window || !IsWindow(window))
        return nullptr;
    return window;
}

// --- Held tasks -------------------------------------------------------------

// Colours a held task can take. Successive holds cycle through them so several
// held tasks stay distinguishable.
static const UINT32 kHeldColors[] = {
    0xFFF9E2AF, 0xFF89B4FA, 0xFFA6E3A1, 0xFFF38BA8, 0xFFCBA6F7, 0xFF94E2D5,
};

static UINT32 HeldColorOf(HWND hwnd)
{
    for (const HeldTask& task : g_held)
        if (task.hwnd == hwnd)
            return task.color;
    return 0;
}

static void ReleaseHeldTask(HWND hwnd)
{
    for (size_t i = 0; i < g_held.size(); i++)
        if (g_held[i].hwnd == hwnd)
        {
            g_held.erase(g_held.begin() + static_cast<ptrdiff_t>(i));
            return;
        }
}

// Drops held tasks whose window is gone.
static void PruneHeldTasks()
{
    for (size_t i = g_held.size(); i-- > 0;)
        if (!g_held[i].hwnd || !IsWindow(g_held[i].hwnd))
            g_held.erase(g_held.begin() + static_cast<ptrdiff_t>(i));
}

// Toggles the hold on a specific window: the first press gives it a colour and
// holds it, the next press releases it.
static void ToggleHoldWindow(HWND window)
{
    if (!window)
        return;

    if (HeldColorOf(window))
    {
        ReleaseHeldTask(window);
        if (g_held.empty())
            StopHeldWatch();
    }
    else
    {
        HeldTask task;
        task.hwnd = window;
        task.color = kHeldColors[g_nextHeldColor % ARRAYSIZE(kHeldColors)];
        g_nextHeldColor++;
        g_held.push_back(task);
        StartHeldWatch();
    }
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void ToggleHold()
{
    // With the held dock enabled the grid can be empty while held items are
    // still visible, so there may be no valid grid selection to toggle.
    if (g_selected < 0)
        return;
    ToggleHoldWindow(SelectedWindow());
}

// Carries every held task onto the given desktop, so held tasks follow the user.
// The caller can suppress the rebuild when it is about to rebuild anyway.
static void MoveHeldTasksToDesktop(const GUID& id, bool rebuild = true)
{
    if (g_held.empty())
        return;

    bool changed = false;
    for (size_t i = g_held.size(); i-- > 0;)
    {
        HWND window = g_held[i].hwnd;
        if (!window || !IsWindow(window))
        {
            g_held.erase(g_held.begin() + static_cast<ptrdiff_t>(i));
            continue;
        }

        if (g_vdm)
        {
            GUID current = {};
            if (SUCCEEDED(g_vdm->GetWindowDesktopId(window, &current)) &&
                IsEqualGUID(current, id))
                continue;
        }

        bool moved = MoveWindowToDesktopInternal(window, id);
        if (!moved && g_vdm)
            moved = SUCCEEDED(g_vdm->MoveWindowToDesktop(window, id));
        if (moved)
            changed = true;
    }

    if (changed && rebuild && g_visible && g_overlay)
    {
        ReleaseThumbnails();
        RebuildWindowList();
        g_desktopSelected = g_currentDesktop;
        InvalidateRect(g_overlay, nullptr, FALSE);
    }
}

// Watches the active desktop while tasks are held, so they can follow the user
// even when the overview is closed. The timer lives on the message-only control
// window, which keeps ticking while the overlay is hidden.
static void StartHeldWatch()
{
    if (!g_control || g_heldWatchOn)
        return;

    GUID id = {};
    g_hasWatchedDesktop = ReadActiveDesktopId(&id);
    if (g_hasWatchedDesktop)
        g_watchedDesktop = id;

    SetTimer(g_control, kTimerHeldWatch, 200, nullptr);
    g_heldWatchOn = true;
}

static void StopHeldWatch()
{
    if (g_control && g_heldWatchOn)
        KillTimer(g_control, kTimerHeldWatch);
    g_heldWatchOn = false;
    g_hasWatchedDesktop = false;
}

// Moves the selected window to the given virtual desktop using the documented
// IVirtualDesktopManager API.
static void MoveSelectedWindowToDesktopIndex(int index)
{
    if (g_desktops.empty())
        return;
    if (index < 0 || index >= static_cast<int>(g_desktops.size()))
        return;

    HWND window = SelectedWindow();
    if (!window)
        return;

    // With all-desktop search the selected window need not live on the active
    // desktop, so compare against the window's own desktop rather than
    // assuming the current desktop is already the target.
    if (g_vdm)
    {
        GUID current = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(window, &current)) &&
            IsEqualGUID(current, g_desktops[index].id))
            return;
    }

    ReleaseThumbnails();
    bool moved = MoveWindowToDesktopInternal(window, g_desktops[index].id);
    if (!moved && g_vdm)
        moved = SUCCEEDED(g_vdm->MoveWindowToDesktop(window, g_desktops[index].id));
    Wh_Log(L"Move window %p to desktop %d: %s", static_cast<void*>(window), index,
           moved ? L"ok" : L"failed");
    if (moved)
    {
        RebuildWindowList();
        g_desktopSelected = g_currentDesktop;
    }
    InvalidateRect(g_overlay, nullptr, FALSE);
}

// Moves the selected window (or the window that opened the overview) to an
// adjacent virtual desktop.
static void MoveSelectedWindowToDesktop(int delta)
{
    if (g_desktops.empty())
        return;

    // In all-desktop search the selected window may live elsewhere, so step
    // from its own desktop instead of the active one.
    int base = g_currentDesktop;
    HWND window = SelectedWindow();
    if (window && g_vdm)
    {
        GUID id = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(window, &id)))
        {
            const int index = DesktopIndexForId(id);
            if (index >= 0)
                base = index;
        }
    }
    MoveSelectedWindowToDesktopIndex(base + delta);
}

// Switches to another virtual desktop while keeping the overview open.
static void SwitchDesktopBy(int delta)
{
    if (g_desktops.empty())
        return;
    const int target = g_currentDesktop + delta;
    if (target < 0 || target >= static_cast<int>(g_desktops.size()))
        return;
    g_desktopSelected = target;
    BeginDesktopAction(target, false, false);
}

static void SendChord(WORD vk, bool extended)
{
    INPUT inputs[6] = {};
    int index = 0;

    auto key = [&](WORD virtualKey, DWORD flags) {
        inputs[index].type = INPUT_KEYBOARD;
        inputs[index].ki.wVk = virtualKey;
        inputs[index].ki.wScan =
            static_cast<WORD>(MapVirtualKeyW(virtualKey, MAPVK_VK_TO_VSC));
        inputs[index].ki.dwFlags = flags;
        index++;
    };

    key(VK_LWIN, 0);
    key(VK_LCONTROL, 0);
    key(vk, extended ? KEYEVENTF_EXTENDEDKEY : 0);
    key(vk, (extended ? KEYEVENTF_EXTENDEDKEY : 0) | KEYEVENTF_KEYUP);
    key(VK_LCONTROL, KEYEVENTF_KEYUP);
    key(VK_LWIN, KEYEVENTF_KEYUP);

    SendInput(index, inputs, sizeof(INPUT));
}

// Resolves the shell's internal desktop objects once. Returns
// IVirtualDesktopManagerInternal, or null when the shell cannot be reached.
static IUnknown* DesktopManagerInternal()
{
    if (!g_vdInternalResolved)
    {
        g_vdInternalResolved = true;

        IUnknown* provider = nullptr;
        if (SUCCEEDED(CoCreateInstance(kClsidImmersiveShell, nullptr, CLSCTX_ALL,
                                       kIidShellServiceProvider,
                                       reinterpret_cast<void**>(&provider))) &&
            provider)
        {
            // IServiceProvider::QueryService, vtable slot 3.
            typedef HRESULT(STDMETHODCALLTYPE * QueryServiceFn)(void*, const GUID&,
                                                                const GUID&, void**);
            auto queryService = reinterpret_cast<QueryServiceFn>(
                (*reinterpret_cast<void***>(provider))[3]);
            queryService(provider, kClsidVirtualDesktopManagerInternal,
                         kIidVirtualDesktopManagerInternal,
                         reinterpret_cast<void**>(&g_vdInternal));
            // IApplicationViewCollection is served under its own IID.
            queryService(provider, kIidApplicationViewCollection,
                         kIidApplicationViewCollection,
                         reinterpret_cast<void**>(&g_viewCollection));
            provider->Release();
        }

        if (!g_vdInternal || !g_viewCollection)
            Wh_Log(L"Shell desktop internals unavailable (manager=%p views=%p)",
                   static_cast<void*>(g_vdInternal),
                   static_cast<void*>(g_viewCollection));
    }
    return g_vdInternal;
}

// Returns a ref-counted IVirtualDesktop for the given id, or null.
static IUnknown* FindDesktopObject(const GUID& id)
{
    IUnknown* manager = DesktopManagerInternal();
    if (!manager)
        return nullptr;

    // IVirtualDesktopManagerInternal vtable: GetDesktops is slot 7.
    typedef HRESULT(STDMETHODCALLTYPE * GetDesktopsFn)(void*, IUnknown**);
    typedef HRESULT(STDMETHODCALLTYPE * GetCountFn)(void*, UINT*);
    typedef HRESULT(STDMETHODCALLTYPE * GetAtFn)(void*, UINT, const GUID&, void**);
    typedef HRESULT(STDMETHODCALLTYPE * GetIdFn)(void*, GUID*);

    void** managerVtbl = *reinterpret_cast<void***>(manager);
    IUnknown* desktops = nullptr;
    if (FAILED(reinterpret_cast<GetDesktopsFn>(managerVtbl[7])(manager, &desktops)) ||
        !desktops)
        return nullptr;

    // IObjectArray: GetCount is slot 3, GetAt is slot 4.
    void** array = *reinterpret_cast<void***>(desktops);
    UINT count = 0;
    reinterpret_cast<GetCountFn>(array[3])(desktops, &count);

    IUnknown* found = nullptr;
    for (UINT i = 0; i < count && !found; i++)
    {
        IUnknown* desktop = nullptr;
        if (FAILED(reinterpret_cast<GetAtFn>(array[4])(
                desktops, i, kIidVirtualDesktop, reinterpret_cast<void**>(&desktop))) ||
            !desktop)
            continue;

        // IVirtualDesktop: GetId is slot 4.
        GUID desktopId = {};
        if (SUCCEEDED(reinterpret_cast<GetIdFn>(
                (*reinterpret_cast<void***>(desktop))[4])(desktop, &desktopId)) &&
            IsEqualGUID(desktopId, id))
            found = desktop;
        else
            desktop->Release();
    }

    desktops->Release();
    return found;
}

// Switches straight to a desktop through the shell's undocumented
// IVirtualDesktopManagerInternal instead of stepping with Win+Ctrl+Arrow.
// Returns false when the interface is unavailable, so callers can fall back.
static bool SwitchDesktopDirect(const GUID& id)
{
    IUnknown* manager = DesktopManagerInternal();
    if (!manager)
        return false;

    IUnknown* desktop = FindDesktopObject(id);
    if (!desktop)
        return false;

    // SwitchDesktop is vtable slot 9 on every Windows 11 build.
    typedef HRESULT(STDMETHODCALLTYPE * SwitchFn)(void*, void*);
    const HRESULT hr = reinterpret_cast<SwitchFn>(
        (*reinterpret_cast<void***>(manager))[9])(manager, desktop);
    desktop->Release();
    return SUCCEEDED(hr);
}

// Moves a window that may belong to another process to a desktop. The
// documented IVirtualDesktopManager::MoveWindowToDesktop refuses those with
// E_ACCESSDENIED, so the shell's view collection and MoveViewToDesktop are used.
static bool MoveWindowToDesktopInternal(HWND window, const GUID& id)
{
    IUnknown* manager = DesktopManagerInternal();
    if (!manager || !g_viewCollection || !window)
        return false;

    // IApplicationViewCollection: GetViewForHwnd is vtable slot 6.
    typedef HRESULT(STDMETHODCALLTYPE * GetViewForHwndFn)(void*, HWND, IUnknown**);
    IUnknown* view = nullptr;
    if (FAILED(reinterpret_cast<GetViewForHwndFn>(
            (*reinterpret_cast<void***>(g_viewCollection))[6])(
            g_viewCollection, window, &view)) ||
        !view)
        return false;

    IUnknown* desktop = FindDesktopObject(id);
    if (!desktop)
    {
        view->Release();
        return false;
    }

    // IVirtualDesktopManagerInternal: MoveViewToDesktop is vtable slot 4.
    typedef HRESULT(STDMETHODCALLTYPE * MoveViewFn)(void*, void*, void*);
    const HRESULT hr = reinterpret_cast<MoveViewFn>(
        (*reinterpret_cast<void***>(manager))[4])(manager, view, desktop);
    desktop->Release();
    view->Release();
    return SUCCEEDED(hr);
}

// Signed distance from the carousel position to `value`, wrapped into
// (-count/2, count/2] so the shortest way around the wheel wins.
static float WrapDelta(float value, int count)
{
    if (count <= 1)
        return 0.0f;
    const float n = static_cast<float>(count);
    float d = std::fmod(value, n);
    if (d < 0.0f)
        d += n;
    if (d > n / 2.0f)
        d -= n;
    return d;
}

// The pill the carousel should centre: the strip selection while it has focus,
// otherwise the desktop being switched to, otherwise the active desktop.
static int StripTarget()
{
    if (g_focusStrip)
        return g_desktopSelected;
    if (g_pendingDesktopTarget >= 0)
        return g_pendingDesktopTarget;
    return g_currentDesktop;
}

static bool IsWheel()
{
    return g_stripStyle == StripStyle::Carousel;
}

static bool UsesChips()
{
    return g_tabStyle == TabStyle::Chip;
}

static bool UsesCards()
{
    return g_tabStyle == TabStyle::Cards;
}

static bool UsesWindowChips()
{
    return g_windowTabStyle == WindowTabStyle::Chips;
}

static UINT32 ClassicChipColor(int index)
{
    static const UINT32 colors[] = {0xFFB3261E, 0xFF1E5AA8, 0xFF1E7A46,
                                    0xFF26262B, 0xFF6A3D9A, 0xFFB45F06};
    return colors[index % ARRAYSIZE(colors)];
}

// Colour for the chip at a stable window/desktop index. Theme and palette modes
// cycle so several chips remain distinguishable.
static UINT32 ChipColorForIndex(int index)
{
    switch (g_chipColorMode)
    {
    case ChipColorMode::Single:
        return g_chipColor;
    case ChipColorMode::Palette:
        return g_chipPalette.empty()
                   ? ClassicChipColor(index)
                   : g_chipPalette[static_cast<size_t>(index) % g_chipPalette.size()];
    case ChipColorMode::Classic:
        return ClassicChipColor(index);
    case ChipColorMode::Theme:
    default:
        return g_themeChipColors.empty()
                   ? g_theme.accent
                   : g_themeChipColors[static_cast<size_t>(index) %
                                       g_themeChipColors.size()];
    }
}

static float ColorLuminance(UINT32 color)
{
    const float r = static_cast<float>((color >> 16) & 0xFF) / 255.0f;
    const float g = static_cast<float>((color >> 8) & 0xFF) / 255.0f;
    const float b = static_cast<float>(color & 0xFF) / 255.0f;
    return 0.2126f * r + 0.7152f * g + 0.0722f * b;
}

static UINT32 ChipTextColor(UINT32 color)
{
    return ColorLuminance(color) > 0.56f ? 0xFF11151C : 0xFFF8FAFC;
}

// The desktop-chip number sits on a cream disc, so it needs a dark version of
// the rim colour rather than the white-on-dark contrast used by window chips.
static UINT32 ChipDiscInk(UINT32 color)
{
    return MixColor(color, 0xFF000000,
                    ColorLuminance(color) > 0.55f ? 0.55f : 0.18f);
}

static bool StripBackgroundVisible()
{
    if (g_stripBackground == StripBackground::Show)
        return true;
    if (g_stripBackground == StripBackground::Hide)
        return false;
    return g_stripStyle == StripStyle::Flat;
}

static void KickCarousel()
{
    if (!g_overlay || !IsWheel())
        return;
    g_lastCarouselTick = GetTickCount64();
    SetTimer(g_overlay, kTimerCarousel, 16, nullptr);
}

static void BeginDesktopAction(int targetDesktop, bool create, bool closeActive)
{
    if (g_busy)
        return;

    g_busy = true;
    g_busySince = GetTickCount64();
    g_pendingDesktopTarget = -1;
    g_pendingDesktopTries = 0;
    g_desktopActionCreate = false;
    g_desktopActionClose = false;
    g_desktopActionStartCount = static_cast<int>(g_desktops.size());
    g_keepThumbnailsWhileBusy = false;

    bool direct = false;
    bool waitForCreateDraw = false;
    bool switching = false;
    if (create)
    {
        g_desktopActionCreate = true;
        // Pull a card from the deck first. The shell only creates the desktop
        // when the ghost lands, so the new tab never appears before the draw.
        StartDesktopCreateDraw();
        waitForCreateDraw = g_createAfterDraw;
        if (!waitForCreateDraw)
            SendChord('D', false);
    }
    else if (closeActive)
    {
        if (g_desktops.size() > 1)
        {
            g_desktopActionClose = true;
            StartDesktopCardThrow(g_currentDesktop);
            SendChord(VK_F4, false);
        }
        else
        {
            g_busy = false;
            g_busySince = 0;
            return;
        }
    }
    else if (targetDesktop >= 0 &&
             targetDesktop < static_cast<int>(g_desktops.size()))
    {
        switching = true;
        // Set this before the shell call: any paint during the switch must keep
        // the old thumbnails instead of releasing them.
        g_keepThumbnailsWhileBusy = true;
        direct = SwitchDesktopDirect(g_desktops[targetDesktop].id);
        // Track the target for both the direct and chord fallback paths, so the
        // desktop timer can stop polling as soon as the shell gets there.
        g_pendingDesktopTarget = targetDesktop;
        if (!direct)
        {
            const int delta = targetDesktop - g_currentDesktop;
            const int steps = std::min(std::abs(delta), 8);
            for (int i = 0; i < steps; i++)
                SendChord(delta > 0 ? VK_RIGHT : VK_LEFT, true);
        }
    }
    else
    {
        g_busy = false;
        g_busySince = 0;
        return;
    }

    // A plain tab switch keeps the current cards and thumbnails on screen until
    // the shell reports the new desktop. Creating or closing a desktop still
    // clears them immediately so the card ghost has a clean stage.
    if (!switching)
    {
        SetChipLayersVisible(false);
        ReleaseThumbnails();
    }

    if (g_overlay && !waitForCreateDraw)
        SetTimer(g_overlay, kTimerDesktop, 40, nullptr);
    KickCarousel();
    KickCardAnimation();
}

////////////////////////////////////////////////////////////////////////////////
// LAYOUT

static IDWriteTextFormat* PillFormat()
{
    return (g_stripStyle == StripStyle::Carousel && g_fmtPillLarge) ? g_fmtPillLarge
                                                                    : g_fmtPill;
}

static RectF TransformedBounds(const RectF& rect, float scale, float degrees)
{
    const float cx = (rect.l + rect.r) / 2.0f;
    const float cy = (rect.t + rect.b) / 2.0f;
    const float radians = degrees * 3.14159265f / 180.0f;
    const float c = std::fabs(std::cos(radians));
    const float sn = std::fabs(std::sin(radians));
    const float halfW = rect.W() * scale / 2.0f;
    const float halfH = rect.H() * scale / 2.0f;
    const float extentX = c * halfW + sn * halfH;
    const float extentY = sn * halfW + c * halfH;
    return {cx - extentX, cy - extentY, cx + extentX, cy + extentY};
}

static void RebuildPills()
{
    g_pills.clear();
    const float s = g_scale;
    const bool cards = UsesCards();
    const bool wheel = IsWheel();
    const bool chips = UsesChips();
    const float cardScale = g_cardScale;
    const float cardW = 160.0f * cardScale * s;
    const float cardH = 224.0f * cardScale * s;
    const float chipD = (wheel ? 64.0f : 52.0f) * s;
    const float pillH = cards ? cardH
                       : wheel ? (chips ? 85.0f : 52.0f) * s
                               : (chips ? 71.0f : 42.0f) * s;
    const float gap = 10.0f * s;
    const float createW = cards ? 112.0f * cardScale * s : 42.0f * s;
    const float createH = cards ? createW * 1.4f : 42.0f * s;

    float nameWidths[64] = {};
    float maxWidth = 0.0f;
    const int count = std::min<int>(static_cast<int>(g_desktops.size()),
                                    ARRAYSIZE(nameWidths));

    // Cards use a fixed shape, so only pills and chips measure their labels.
    if (!cards)
    {
        for (int i = 0; i < count; i++)
        {
            const bool renaming = g_renameDesktop == i;
            const std::wstring& shown = renaming ? g_renameText : g_desktops[i].name;
            const bool hasClose = g_desktops.size() > 1 && i == g_currentDesktop;

            if (chips)
            {
                const float textW = MeasureTextWidth(shown, g_fmtHint);
                float w = std::max(chipD + 16.0f * s, textW + 14.0f * s);
                if (renaming)
                    w = std::max(w, 220.0f * s);
                nameWidths[i] = std::min(260.0f * s, w);
            }
            else
            {
                // Badge + gaps + a name measured with the real font, plus caret
                // room while renaming.
                const float textW = MeasureTextWidth(shown, PillFormat());
                float w = 40.0f * s + textW + (hasClose ? 30.0f * s : 14.0f * s);
                if (renaming)
                    w += 18.0f * s;
                const float maxW = renaming ? 460.0f * s : 320.0f * s;
                w = std::max(112.0f * s, std::min(maxW, w));
                nameWidths[i] = w;
            }
            maxWidth = std::max(maxWidth, nameWidths[i]);
        }
    }

    if (count <= 0)
    {
        g_createRect = {};
        return;
    }

    auto setChipClose = [&](PillView& pill, float diameter) {
        const float ccx = (pill.rect.l + pill.rect.r) / 2.0f;
        const float ccy = pill.rect.t + 2.0f * s + diameter / 2.0f;
        const float r = diameter / 2.0f;
        pill.closeRect = {ccx + 0.35f * r, ccy - 0.95f * r,
                          ccx + 0.95f * r, ccy - 0.35f * r};
        pill.closeHit =
            TransformedBounds(pill.closeRect, pill.scale, pill.angle);
    };

    auto setCardClose = [&](PillView& pill, float cardScaleFactor) {
        pill.closeRect = {pill.rect.r - 32.0f * cardScaleFactor * s,
                          pill.rect.t + 8.0f * cardScaleFactor * s,
                          pill.rect.r - 8.0f * cardScaleFactor * s,
                          pill.rect.t + 32.0f * cardScaleFactor * s};
        pill.closeHit =
            TransformedBounds(pill.closeRect, pill.scale, pill.angle);
    };

    auto applyLift = [&]() {
        if (g_desktopSelection != DesktopSelection::Lift)
            return;
        for (PillView& pill : g_pills)
        {
            if (!pill.visible)
                continue;
            const bool active = pill.desktop == g_currentDesktop;
            const bool selected =
                g_focusStrip && pill.desktop == g_desktopSelected;
            if (!active && !selected)
                continue;
            const float lift = (selected ? 10.0f : 6.0f) * s;
            pill.lift = lift;
            pill.hit.t -= lift;
            pill.hit.b -= lift;
            pill.closeHit.t -= lift;
            pill.closeHit.b -= lift;
            pill.closeRect.t -= lift;
            pill.closeRect.b -= lift;
        }
    };

    const float cy = g_layout.strip.t + g_layout.strip.H() / 2.0f;

    if (cards && wheel)
    {
        // Card wheel: every desktop is a portrait playing card.
        const float pitch = cardW + 20.0f * cardScale * s;
        const float cx = g_layout.strip.l + g_layout.strip.W() / 2.0f;

        // Keep the farthest visible card clear of the create card; narrow
        // monitors show fewer neighbours instead of shrinking the wheel.
        const float rightLimit = g_layout.strip.r - createW - 24.0f * s;
        const float maxOffset = std::max(0.0f, rightLimit - cx);
        const float visibleDepth =
            std::max(0.5f, std::min(2.25f, maxOffset / (pitch * 0.82f) - 0.6f));

        for (int i = 0; i < count; i++)
        {
            const float d = WrapDelta(static_cast<float>(i) - g_carouselPos, count);
            const float ad = std::fabs(d);

            PillView pill;
            pill.desktop = i;
            pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
            pill.depth = d;
            pill.visible = ad <= visibleDepth;
            if (pill.visible)
            {
                pill.scale = std::max(0.55f, 1.0f - 0.18f * ad);
                pill.angle = std::max(-12.0f, std::min(12.0f, d * 4.5f));
                pill.alpha =
                    std::max(0.45f, 1.0f - 0.26f * std::max(0.0f, ad - 1.0f));

                const float px = cx + d * pitch * 0.82f;
                const float py = cy + std::min(12.0f * s, 2.5f * s * d * d);
                pill.rect = {px - cardW / 2.0f, py - cardH / 2.0f,
                             px + cardW / 2.0f, py + cardH / 2.0f};
                pill.hit = TransformedBounds(pill.rect, pill.scale, pill.angle);

                if (pill.hasClose)
                    setCardClose(pill, cardScale);
            }
            g_pills.push_back(pill);
        }

        g_createRect = {g_layout.strip.r - createW - 12.0f * s,
                        cy - createH / 2.0f, g_layout.strip.r - 12.0f * s,
                        cy + createH / 2.0f};
        applyLift();
        return;
    }

    if (cards)
    {
        // Flat row of cards: shrink the row if it cannot fit next to the
        // create card.
        const float cardGap = 14.0f * s;
        const float available = g_layout.strip.W() - createW - cardGap;
        const float needed = count * cardW + (count - 1) * cardGap;
        const float fit = needed > available && needed > 0.0f
                              ? std::max(0.18f, available / needed)
                              : 1.0f;
        const float drawW = cardW * fit;
        const float drawH = cardH * fit;
        const float gap = cardGap * fit;
        const float total =
            count * drawW + (count - 1) * gap + createW + cardGap;
        float cursor = g_layout.strip.l + (g_layout.strip.W() - total) / 2.0f;

        for (int i = 0; i < count; i++)
        {
            PillView pill;
            pill.desktop = i;
            pill.rect = {cursor, cy - drawH / 2.0f, cursor + drawW,
                         cy + drawH / 2.0f};
            pill.hit = pill.rect;
            pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
            if (pill.hasClose)
                setCardClose(pill, cardScale * fit);
            g_pills.push_back(pill);
            cursor += drawW + gap;
        }

        g_createRect = {cursor, cy - createH / 2.0f, cursor + createW,
                        cy + createH / 2.0f};
        applyLift();
        return;
    }

    if (wheel)
    {
        // The carousel keeps one tab width so the wheel stays symmetric; long
        // names are ellipsized. Chips use a compact fixed width, while the
        // rename editor gets room because it is always centred while editing.
        const float pillW = chips
            ? (g_renameDesktop >= 0 ? 220.0f * s : 96.0f * s)
            : (g_renameDesktop >= 0
                   ? 380.0f * s
                   : std::max(160.0f * s, std::min(320.0f * s, maxWidth)));
        const float pitch = pillW + (chips ? 20.0f : 16.0f) * s;
        const float cx = g_layout.strip.l + g_layout.strip.W() / 2.0f;

        // Keep the farthest visible tab clear of the create button; narrow
        // monitors show fewer neighbours instead of shrinking the wheel.
        const float rightLimit = g_layout.strip.r - createW - 24.0f * s;
        const float maxOffset = std::max(0.0f, rightLimit - cx);
        const float depthMargin = chips ? 0.4f : 0.15f;
        const float visibleDepth = std::max(
            0.5f, std::min(2.25f, maxOffset / (pitch * 0.82f) - depthMargin));

        for (int i = 0; i < count; i++)
        {
            const float d = WrapDelta(static_cast<float>(i) - g_carouselPos, count);
            const float ad = std::fabs(d);

            PillView pill;
            pill.desktop = i;
            pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
            pill.depth = d;
            pill.visible = ad <= visibleDepth;
            if (pill.visible)
            {
                pill.scale = std::max(0.55f, 1.0f - 0.18f * ad);
                pill.angle = std::max(-12.0f, std::min(12.0f, d * 4.5f));
                pill.alpha =
                    std::max(0.45f, 1.0f - 0.26f * std::max(0.0f, ad - 1.0f));

                const float px = cx + d * pitch * 0.82f;
                const float py = cy + std::min(12.0f * s, 2.5f * s * d * d);
                pill.rect = {px - pillW / 2.0f, py - pillH / 2.0f,
                             px + pillW / 2.0f, py + pillH / 2.0f};
                pill.hit = TransformedBounds(pill.rect, pill.scale, pill.angle);

                if (pill.hasClose)
                {
                    if (chips)
                    {
                        setChipClose(pill, std::min(chipD, pillW - 4.0f * s));
                    }
                    else
                    {
                        pill.closeRect = {pill.rect.r - 28.0f * s,
                                          pill.rect.t + 6.0f * s,
                                          pill.rect.r - 6.0f * s,
                                          pill.rect.b - 6.0f * s};
                        pill.closeHit = TransformedBounds(pill.closeRect,
                                                          pill.scale, pill.angle);
                    }
                }
            }
            g_pills.push_back(pill);
        }

        g_createRect = {g_layout.strip.r - createW - 12.0f * s,
                        cy - createH / 2.0f, g_layout.strip.r - 12.0f * s,
                        cy + createH / 2.0f};
        applyLift();
        return;
    }

    // Flat row (default).
    float totalPills = 0.0f;
    for (int i = 0; i < count; i++)
        totalPills += nameWidths[i];

    const float stripW = g_layout.strip.W();
    const float total = totalPills + createW + gap * count;
    float shrink = 1.0f;
    if (total > stripW && totalPills > 0.0f)
        shrink = std::max(0.55f, (stripW - createW - gap * count) / totalPills);

    float cursor = g_layout.strip.l +
                   (stripW - (totalPills * shrink + createW + gap * count)) / 2.0f;
    const float y = g_layout.strip.t + (g_layout.strip.H() - pillH) / 2.0f;

    for (int i = 0; i < count; i++)
    {
        const float w = nameWidths[i] * shrink;
        PillView pill;
        pill.desktop = i;
        pill.rect = {cursor, y, cursor + w, y + pillH};
        pill.hit = pill.rect;
        pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
        if (pill.hasClose)
        {
            if (chips)
            {
                setChipClose(pill, std::min(chipD, w - 4.0f * s));
            }
            else
            {
                pill.closeRect = {pill.rect.r - 28.0f * s,
                                  pill.rect.t + 6.0f * s,
                                  pill.rect.r - 6.0f * s,
                                  pill.rect.b - 6.0f * s};
                pill.closeHit = pill.closeRect;
            }
        }
        g_pills.push_back(pill);
        cursor += w + gap;
    }

    const float createY = g_layout.strip.t +
                          (g_layout.strip.H() - createH) / 2.0f;
    g_createRect = {cursor, createY, cursor + createW, createY + createH};
    applyLift();
}

// The visible pill under the cursor. Overlapping carousel neighbours resolve to
// the one closest to the centre of the wheel.
static int PillAt(float x, float y)
{
    int best = -1;
    float bestDepth = 1.0e9f;
    for (int i = 0; i < static_cast<int>(g_pills.size()); i++)
    {
        const PillView& pill = g_pills[i];
        if (!pill.visible || !Contains(pill.hit, x, y))
            continue;
        const float depth = std::fabs(pill.depth);
        if (depth < bestDepth)
        {
            best = i;
            bestDepth = depth;
        }
    }
    return best;
}

static bool SearchVisible()
{
    return g_searchAlwaysVisible || g_searchFocused || !g_search.empty() ||
           g_searchAllDesktops;
}

static bool EntryIsHeld(int entry)
{
    return entry >= 0 && entry < static_cast<int>(g_windows.size()) &&
           HeldColorOf(g_windows[entry].hwnd) != 0;
}

static int FindFilteredIndex(int entry)
{
    for (int i = 0; i < static_cast<int>(g_filtered.size()); i++)
        if (g_filtered[i] == entry)
            return i;
    return -1;
}

static int DisplayPosition(int filteredIndex)
{
    for (int i = 0; i < static_cast<int>(g_display.size()); i++)
        if (g_display[i] == filteredIndex)
            return i;
    return -1;
}

// The grid excludes held windows while the side dock is enabled. The display
// list stores filtered indices so search, selection and activation keep using
// the same coordinate space as the rest of the input code.
static void RebuildDisplayList()
{
    g_display.clear();
    for (int i = 0; i < static_cast<int>(g_filtered.size()); i++)
    {
        const int entry = g_filtered[i];
        if (g_heldDock != HeldDock::Off && EntryIsHeld(entry))
            continue;
        g_display.push_back(i);
    }

    if (g_display.empty())
    {
        g_selected = -1;
    }
    else if (DisplayPosition(g_selected) < 0)
    {
        g_selected = g_display.front();
    }
}

static void UpdateLayout()
{
    const float s = g_scale;
    g_layout.w = static_cast<float>(g_monitorW);
    g_layout.h = static_cast<float>(g_monitorH);
    g_layout.s = s;

    const float margin = 56.0f * s;

    const float searchH = 46.0f * s;
    const float searchW = std::min(560.0f * s, g_layout.w - 2.0f * margin);
    const float searchX = (g_layout.w - searchW) / 2.0f;
    if (SearchVisible())
    {
        g_layout.search = {searchX, 44.0f * s, searchX + searchW, 44.0f * s + searchH};
        g_searchClearRect = {g_layout.search.r - 38.0f * s, g_layout.search.t + 6.0f * s,
                             g_layout.search.r - 8.0f * s, g_layout.search.b - 6.0f * s};
    }
    else
    {
        // Collapse the bar so the grid can use the space; pressing / reveals it.
        g_layout.search = {searchX, 44.0f * s, searchX + searchW, 44.0f * s};
        g_searchClearRect = {};
    }

    const float stripH =
        (UsesCards()
             ? 224.0f * g_cardScale + 40.0f
             : g_stripStyle == StripStyle::Carousel
                   ? (UsesChips() ? 112.0f : 96.0f)
                   : (UsesChips() ? 92.0f : 64.0f)) * s;
    const float stripBottom = g_layout.h - 46.0f * s;
    g_layout.strip = {margin, stripBottom - stripH, g_layout.w - margin, stripBottom};
    g_layout.grid = {margin, g_layout.search.b + 42.0f * s, g_layout.w - margin,
                     g_layout.strip.t - 32.0f * s};

    g_cards.clear();
    g_dockCards.clear();
    g_dockArea = {};
    RebuildDisplayList();

    const bool windowChips = UsesWindowChips();
    const int n = static_cast<int>(g_display.size());
    const float gap = 18.0f * s;
    g_layout.gap = gap;

    // Held windows can live in a side dock. Reserve its space before the grid
    // is measured so the remaining cards reflow instead of hiding underneath it.
    std::vector<int> heldEntries;
    if (g_heldDock != HeldDock::Off)
    {
        for (int i = 0; i < static_cast<int>(g_windows.size()); i++)
            if (EntryIsHeld(i))
                heldEntries.push_back(i);
    }

    if (!heldEntries.empty())
    {
        float dockW = (windowChips ? 210.0f * g_windowChipScale : 235.0f) * s;
        dockW = std::min(dockW,
                         std::max(150.0f * s, g_layout.grid.W() * 0.30f));
        const float dockGap = 18.0f * s;
        if (g_heldDock == HeldDock::Left)
        {
            g_dockArea = {g_layout.grid.l, g_layout.grid.t,
                          g_layout.grid.l + dockW, g_layout.grid.b};
            g_layout.grid.l += dockW + dockGap;
        }
        else
        {
            g_dockArea = {g_layout.grid.r - dockW, g_layout.grid.t,
                          g_layout.grid.r, g_layout.grid.b};
            g_layout.grid.r -= dockW + dockGap;
        }
    }

    const float gridW = g_layout.grid.W();
    const float gridH = g_layout.grid.H();
    const float maxCardW =
        (windowChips ? 300.0f * g_windowChipScale : 400.0f) * s;

    int cols = 0;
    float cardW = 0.0f, cardH = 0.0f;
    int rows = 0;
    for (int c = 1; c <= 10; c++)
    {
        const float w = std::min(maxCardW, (gridW - (c - 1) * gap) / c);
        const float h = windowChips ? w : w * 0.62f;
        int totalRows = (n + c - 1) / c;
        if (totalRows < 1)
            totalRows = 1;
        if (totalRows * h + (totalRows - 1) * gap <= gridH + 0.5f)
        {
            cols = c;
            cardW = w;
            cardH = h;
            rows = totalRows;
            break;
        }
    }

    if (cols == 0)
    {
        cols = 10;
        cardW = std::min(maxCardW, (gridW - 9.0f * gap) / 10.0f);
        cardH = windowChips ? cardW : cardW * 0.62f;
        rows = std::max(1, static_cast<int>(std::floor((gridH + gap) / (cardH + gap))));
    }

    const int perPage = std::max(1, cols * rows);
    g_layout.cols = cols;
    g_layout.rows = rows;
    g_layout.cardW = cardW;
    g_layout.cardH = cardH;
    g_layout.perPage = perPage;
    g_layout.pageCount = std::max(1, (n + perPage - 1) / perPage);

    if (g_page >= g_layout.pageCount)
        g_page = g_layout.pageCount - 1;
    if (g_page < 0)
        g_page = 0;

    const int start = g_page * perPage;
    const int visible = std::max(0, std::min(n - start, perPage));
    const int rowsOnPage = std::max(1, (visible + cols - 1) / cols);

    const float usedW = cols * cardW + (cols - 1) * gap;
    const float x0 = g_layout.grid.l + (gridW - usedW) / 2.0f;
    const float usedH = rowsOnPage * cardH + (rowsOnPage - 1) * gap;
    const float y0 = g_layout.grid.t + (gridH - usedH) / 2.0f;

    const float headerH = windowChips ? 26.0f * s : 34.0f * s;
    const float pad = 8.0f * s;

    auto shiftCard = [](CardView& card, float dy) {
        card.rect.t -= dy;
        card.rect.b -= dy;
        card.header.t -= dy;
        card.header.b -= dy;
        card.preview.t -= dy;
        card.preview.b -= dy;
        card.close.t -= dy;
        card.close.b -= dy;
    };

    for (int i = 0; i < visible; i++)
    {
        const int col = i % cols;
        const int row = i / cols;
        const float left = x0 + col * (cardW + gap);
        const float top = y0 + row * (cardH + gap);
        const int filteredIndex = g_display[start + i];
        const int entry = g_filtered[filteredIndex];

        CardView card;
        card.entry = entry;
        card.filtered = filteredIndex;
        card.rect = {left, top, left + cardW, top + cardH};
        card.hit = card.rect;

        if (windowChips)
        {
            const float cx = left + cardW / 2.0f;
            const float cy = top + cardH / 2.0f;
            const float previewD =
                cardW * (cardW >= 180.0f * s ? 0.64f : 0.60f);
            card.header = {left, top, left + cardW, top + headerH};
            card.preview = {cx - previewD / 2.0f, cy - previewD / 2.0f,
                            cx + previewD / 2.0f, cy + previewD / 2.0f};
            const float closeSize = std::min(24.0f * s, cardW * 0.14f);
            const float ccx = cx + cardW * 0.33f;
            const float ccy = cy - cardW * 0.33f;
            card.close = {ccx - closeSize / 2.0f, ccy - closeSize / 2.0f,
                          ccx + closeSize / 2.0f, ccy + closeSize / 2.0f};
        }
        else
        {
            card.header = {left, top, left + cardW, top + headerH};
            card.preview = {left + pad, top + headerH,
                            left + cardW - pad, top + cardH - pad};
            const float closeSize = 24.0f * s;
            card.close = {left + cardW - pad - closeSize,
                          top + (headerH - closeSize) / 2.0f,
                          left + cardW - pad,
                          top + (headerH + closeSize) / 2.0f};
        }

        const bool held = EntryIsHeld(entry);
        const bool hovered = g_hoverCard == i;
        const bool selected = !g_focusStrip && card.filtered == g_selected;
        const bool lifted = (held && g_liftHeldWindows) ||
                            (hovered && g_liftHoveredWindows) ||
                            (selected && g_liftSelectedWindow);
        if (lifted)
        {
            card.lift = (held ? 10.0f : 7.0f) * s;
            shiftCard(card, card.lift);
        }
        g_cards.push_back(card);
    }

    if (!heldEntries.empty())
    {
        const float dockPad = 10.0f * s;
        const float dockHeaderH = 34.0f * s;
        const RectF inner = {g_dockArea.l + dockPad, g_dockArea.t + dockHeaderH,
                             g_dockArea.r - dockPad, g_dockArea.b - dockPad};
        const int count = static_cast<int>(heldEntries.size());
        float itemW = std::max(40.0f * s, inner.W());
        float itemH = windowChips ? itemW : itemW * 0.62f;
        float itemGap = 10.0f * s;
        float totalH = count * itemH + (count - 1) * itemGap;
        if (totalH > inner.H() && totalH > 0.0f)
        {
            float fit = (inner.H() - (count - 1) * itemGap) /
                        (count * itemH);
            fit = std::max(0.30f, std::min(1.0f, fit));
            itemW *= fit;
            itemH *= fit;
            itemGap *= fit;
            totalH = count * itemH + (count - 1) * itemGap;
        }

        float y = inner.t + std::max(0.0f, (inner.H() - totalH) / 2.0f);
        for (int entry : heldEntries)
        {
            CardView card;
            card.entry = entry;
            card.filtered = FindFilteredIndex(entry);
            card.docked = true;
            const float left = inner.l + (inner.W() - itemW) / 2.0f;
            card.rect = {left, y, left + itemW, y + itemH};
            card.hit = card.rect;

            if (windowChips)
            {
                const float cx = left + itemW / 2.0f;
                const float cy = y + itemH / 2.0f;
                const float previewD =
                    itemW * (itemW >= 180.0f * s ? 0.64f : 0.60f);
                card.header = {left, y, left + itemW, y + 24.0f * s};
                card.preview = {cx - previewD / 2.0f, cy - previewD / 2.0f,
                                cx + previewD / 2.0f, cy + previewD / 2.0f};
                const float closeSize = std::min(22.0f * s, itemW * 0.14f);
                const float ccx = cx + itemW * 0.33f;
                const float ccy = cy - itemW * 0.33f;
                card.close = {ccx - closeSize / 2.0f, ccy - closeSize / 2.0f,
                              ccx + closeSize / 2.0f, ccy + closeSize / 2.0f};
            }
            else
            {
                const float dockHeader = std::min(28.0f * s, itemH * 0.30f);
                card.header = {left, y, left + itemW, y + dockHeader};
                card.preview = {left + 5.0f * s, y + dockHeader,
                                left + itemW - 5.0f * s,
                                y + itemH - 5.0f * s};
                const float closeSize = std::min(24.0f * s, itemW * 0.16f);
                card.close = {left + itemW - 5.0f * s - closeSize,
                              y + 3.0f * s,
                              left + itemW - 5.0f * s,
                              y + 3.0f * s + closeSize};
            }

            const bool hovered =
                g_hoverDock == static_cast<int>(g_dockCards.size());
            if (g_liftHeldWindows ||
                (hovered && g_liftHoveredWindows))
            {
                card.lift = 6.0f * s;
                shiftCard(card, card.lift);
            }
            g_dockCards.push_back(card);
            y += itemH + itemGap;
        }
    }

    RebuildPills();

    if (g_dockCards.empty())
    {
        g_focusDock = false;
        g_dockSelected = 0;
    }
    else
    {
        g_dockSelected = std::max(
            0, std::min(g_dockSelected, static_cast<int>(g_dockCards.size()) - 1));
    }
}

////////////////////////////////////////////////////////////////////////////////
// DWM THUMBNAILS

static void ReleaseThumbnailSet(ThumbnailSet& set)
{
    for (HTHUMBNAIL thumbnail : set.handles)
        if (thumbnail)
            DwmUnregisterThumbnail(thumbnail);
    set.handles.clear();
    set.sources.clear();
}

static void ReleaseThumbnails()
{
    ReleaseThumbnailSet(g_overlayThumbs);
    ReleaseThumbnailSet(g_chipThumbs);
}

static void SyncThumbnailSet(HWND destination, ThumbnailSet& set,
                             const std::vector<HWND>& sources,
                             const std::vector<RectF>& rects, float opacity)
{
    if (!destination)
    {
        ReleaseThumbnailSet(set);
        return;
    }

    bool same = sources.size() == set.sources.size();
    if (same)
    {
        for (size_t i = 0; i < sources.size(); i++)
            if (sources[i] != set.sources[i])
            {
                same = false;
                break;
            }
    }

    if (!same)
    {
        ReleaseThumbnailSet(set);
        for (HWND source : sources)
        {
            HTHUMBNAIL thumbnail = nullptr;
            if (SUCCEEDED(DwmRegisterThumbnail(destination, source, &thumbnail)))
                set.handles.push_back(thumbnail);
            else
                set.handles.push_back(nullptr);
        }
        set.sources = sources;
    }

    const BYTE alpha =
        static_cast<BYTE>(std::max(0.0f, std::min(1.0f, opacity)) * 255.0f);
    const size_t count = std::min(set.handles.size(), rects.size());
    for (size_t i = 0; i < count; i++)
    {
        if (!set.handles[i])
            continue;
        DWM_THUMBNAIL_PROPERTIES properties = {};
        properties.dwFlags = DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE |
                             DWM_TNP_OPACITY | DWM_TNP_SOURCECLIENTAREAONLY;
        properties.rcDestination = ToRect(rects[i]);
        properties.fVisible = alpha > 6 ? TRUE : FALSE;
        properties.opacity = alpha;
        properties.fSourceClientAreaOnly = TRUE;
        DwmUpdateThumbnailProperties(set.handles[i], &properties);
    }
}

static void SyncThumbnails(const std::vector<HWND>& sources,
                           const std::vector<RectF>& rects, float opacity)
{
    SyncThumbnailSet(g_overlay, g_overlayThumbs, sources, rects, opacity);
}

static void SyncChipThumbnails(const std::vector<HWND>& sources,
                               const std::vector<RectF>& rects, float opacity)
{
    SyncThumbnailSet(g_thumbHost, g_chipThumbs, sources, rects, opacity);
}

////////////////////////////////////////////////////////////////////////////////
// DRAWING HELPERS

static void FillRound(const RectF& rect, float radius, UINT32 color, float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || rect.W() <= 0.0f || rect.H() <= 0.0f)
        return;
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    const D2D1_ROUNDED_RECT rounded =
        D2D1::RoundedRect(D2D1::RectF(rect.l, rect.t, rect.r, rect.b), radius, radius);
    g_d2dTarget->FillRoundedRectangle(&rounded, g_d2dBrush);
}

static void StrokeRound(const RectF& rect, float radius, UINT32 color, float width,
                        float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || rect.W() <= 0.0f || rect.H() <= 0.0f)
        return;
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    const D2D1_ROUNDED_RECT rounded =
        D2D1::RoundedRect(D2D1::RectF(rect.l, rect.t, rect.r, rect.b), radius, radius);
    g_d2dTarget->DrawRoundedRectangle(&rounded, g_d2dBrush, width);
}

static void FillEllipse(float cx, float cy, float rx, float ry, UINT32 color,
                        float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || rx <= 0.0f || ry <= 0.0f)
        return;
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    const D2D1_ELLIPSE ellipse =
        D2D1::Ellipse(D2D1::Point2F(cx, cy), rx, ry);
    g_d2dTarget->FillEllipse(&ellipse, g_d2dBrush);
}

static void StrokeEllipse(float cx, float cy, float rx, float ry, UINT32 color,
                          float width, float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || rx <= 0.0f || ry <= 0.0f)
        return;
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    const D2D1_ELLIPSE ellipse =
        D2D1::Ellipse(D2D1::Point2F(cx, cy), rx, ry);
    g_d2dTarget->DrawEllipse(&ellipse, g_d2dBrush, width);
}

// Adds a closed circle to a geometry sink.
static void AddCircleGeometry(ID2D1GeometrySink* sink, float cx, float cy,
                              float radius)
{
    const D2D1_POINT_2F top = D2D1::Point2F(cx, cy - radius);
    sink->BeginFigure(top, D2D1_FIGURE_BEGIN_FILLED);
    sink->AddArc(D2D1::ArcSegment(
        D2D1::Point2F(cx + radius, cy), D2D1::SizeF(radius, radius), 0.0f,
        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
    sink->AddArc(D2D1::ArcSegment(
        D2D1::Point2F(cx, cy + radius), D2D1::SizeF(radius, radius), 0.0f,
        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
    sink->AddArc(D2D1::ArcSegment(
        D2D1::Point2F(cx - radius, cy), D2D1::SizeF(radius, radius), 0.0f,
        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
    sink->AddArc(D2D1::ArcSegment(
        top, D2D1::SizeF(radius, radius), 0.0f,
        D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
}

// Builds an annulus as a single path. Filled with the alternate rule, the inner
// circle becomes a hole, which lets the window-chip preview show through the
// layered mask.
static ID2D1PathGeometry* CreateDonutGeometry(float cx, float cy, float outerR,
                                              float innerR)
{
    if (!g_d2dFactory || outerR <= 0.0f || innerR >= outerR)
        return nullptr;

    ID2D1PathGeometry* geometry = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&geometry)) || !geometry)
        return nullptr;

    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(geometry->Open(&sink)) || !sink)
    {
        geometry->Release();
        return nullptr;
    }

    sink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);
    AddCircleGeometry(sink, cx, cy, outerR);
    AddCircleGeometry(sink, cx, cy, innerR);
    sink->Close();
    sink->Release();
    return geometry;
}

// Fills an annulus. The inner circle is left transparent, which lets the
// window-chip preview show through the layered mask.
static void FillDonut(float cx, float cy, float outerR, float innerR,
                      UINT32 color, float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || outerR <= 0.0f)
        return;
    if (innerR <= 0.0f)
    {
        FillEllipse(cx, cy, outerR, outerR, color, multiply);
        return;
    }
    if (innerR >= outerR)
        return;

    ID2D1PathGeometry* geometry = CreateDonutGeometry(cx, cy, outerR, innerR);
    if (!geometry)
        return;
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    g_d2dTarget->FillGeometry(geometry, g_d2dBrush);
    geometry->Release();
}

static void DrawTextBlock(const std::wstring& text, IDWriteTextFormat* format,
                          const RectF& rect, UINT32 color, DWRITE_TEXT_ALIGNMENT align,
                          float multiply = 1.0f)
{
    if (!g_d2dTarget || !g_d2dBrush || !format || text.empty() || rect.W() <= 0.0f)
        return;
    format->SetTextAlignment(align);
    g_d2dBrush->SetColor(ColorOf(color, multiply));
    g_d2dTarget->DrawTextW(text.c_str(), static_cast<UINT32>(text.size()), format,
                           D2D1::RectF(rect.l, rect.t, rect.r, rect.b), g_d2dBrush,
                           D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

static void DrawRotatedTextBlock(const std::wstring& text, IDWriteTextFormat* format,
                                 const RectF& rect, UINT32 color,
                                 DWRITE_TEXT_ALIGNMENT align, float multiply,
                                 float degrees)
{
    if (!g_d2dTarget)
        return;
    D2D1::Matrix3x2F saved;
    g_d2dTarget->GetTransform(&saved);
    const D2D1_POINT_2F centre =
        D2D1::Point2F((rect.l + rect.r) / 2.0f, (rect.t + rect.b) / 2.0f);
    g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Rotation(degrees, centre) * saved);
    DrawTextBlock(text, format, rect, color, align, multiply);
    g_d2dTarget->SetTransform(saved);
}

// Draws a single line of text along the top arc of a circle. Characters are
// measured individually so the baseline follows the rim instead of forming a
// straight chord. Long titles are trimmed with an ellipsis.
static void DrawArcText(const std::wstring& text, IDWriteTextFormat* format,
                        float cx, float cy, float radius, UINT32 color,
                        float maxDegrees, float multiply = 1.0f)
{
    if (!g_d2dTarget || !format || text.empty() || radius <= 0.0f)
        return;

    const float maxWidth =
        radius * maxDegrees * 3.14159265f / 180.0f;
    std::wstring shown;
    float width = 0.0f;
    for (WCHAR ch : text)
    {
        const std::wstring one(1, ch);
        const float charWidth = MeasureTextWidth(one, format);
        if (width + charWidth > maxWidth)
            break;
        shown.push_back(ch);
        width += charWidth;
    }

    if (shown.size() < text.size())
    {
        const std::wstring ellipsis = L"\u2026";
        const float ellipsisWidth = MeasureTextWidth(ellipsis, format);
        while (!shown.empty() &&
               MeasureTextWidth(shown, format) + ellipsisWidth > maxWidth)
            shown.pop_back();
        if (!shown.empty())
        {
            shown += ellipsis;
            width = MeasureTextWidth(shown, format);
        }
    }

    if (shown.empty())
        return;

    const float fontHeight = format->GetFontSize() * 1.15f;
    float angle = -width / radius / 2.0f;
    for (WCHAR ch : shown)
    {
        const std::wstring one(1, ch);
        const float charWidth = MeasureTextWidth(one, format);
        const float mid = angle + charWidth / radius / 2.0f;
        const float x = cx + std::sin(mid) * radius;
        const float y = cy - std::cos(mid) * radius;
        const RectF charRect = {x - charWidth / 2.0f - 1.0f * g_scale,
                                y - fontHeight / 2.0f,
                                x + charWidth / 2.0f + 1.0f * g_scale,
                                y + fontHeight / 2.0f};
        DrawRotatedTextBlock(one, format, charRect, color,
                             DWRITE_TEXT_ALIGNMENT_CENTER, multiply,
                             mid * 180.0f / 3.14159265f);
        angle += charWidth / radius;
    }
}

// A real clay chip is one colour with lighter or darker inlaid edge spots.
// `face` is the slightly lit clay, `edge` the moulded side, `spot` the pressed
// insert colour and `groove` the recess where the rim meets the centre.
struct ChipPaint
{
    UINT32 face;
    UINT32 edge;
    UINT32 spot;
    UINT32 groove;
    UINT32 inlay;
};

static ChipPaint ChipPaintFor(UINT32 base)
{
    ChipPaint paint;
    const bool pale = ColorLuminance(base) > 0.58f;
    paint.face = MixColor(base, 0xFFFFFFFF, pale ? 0.02f : 0.07f);
    paint.edge = MixColor(base, 0xFF000000, 0.42f);
    paint.groove = MixColor(base, 0xFF000000, 0.30f);
    // Cream inserts are the casino standard. Pale chips need dark inserts to
    // keep the edge pattern readable.
    paint.spot = pale ? MixColor(base, 0xFF000000, 0.50f) : 0xFFF2E9D6;
    paint.inlay = 0xFFF6EEDC;
    return paint;
}

static void FillChipDisc(float cx, float cy, float radius, float holeR,
                         UINT32 color, float multiply)
{
    if (holeR > 0.0f)
        FillDonut(cx, cy, radius, holeR, color, multiply);
    else
        FillEllipse(cx, cy, radius, radius, color, multiply);
}

// Builds every edge insert for one chip into a single geometry. The inserts
// are wide radial blocks inlaid into the rim, not thin painted ticks. The
// pattern is rotated half a step so the top of the rim and the upper-right
// close affordance both fall in bare clay.
static void FillChipEdgeSpots(float cx, float cy, float outerR, float innerR,
                              int count, float halfAngle, UINT32 color,
                              float multiply)
{
    if (!g_d2dFactory || !g_d2dTarget || !g_d2dBrush || count <= 0 ||
        outerR <= innerR)
        return;

    ID2D1PathGeometry* geometry = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&geometry)) || !geometry)
        return;

    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(geometry->Open(&sink)) || !sink)
    {
        geometry->Release();
        return;
    }

    sink->SetFillMode(D2D1_FILL_MODE_WINDING);
    const float step = 6.2831853f / static_cast<float>(count);
    const float start = step * 0.5f - 1.5707963f;
    for (int i = 0; i < count; i++)
    {
        const float angle = start + step * static_cast<float>(i);
        const float a0 = angle - halfAngle;
        const float a1 = angle + halfAngle;
        const D2D1_POINT_2F outer0 = D2D1::Point2F(
            cx + std::cos(a0) * outerR, cy + std::sin(a0) * outerR);
        const D2D1_POINT_2F outer1 = D2D1::Point2F(
            cx + std::cos(a1) * outerR, cy + std::sin(a1) * outerR);
        const D2D1_POINT_2F inner1 = D2D1::Point2F(
            cx + std::cos(a1) * innerR, cy + std::sin(a1) * innerR);
        const D2D1_POINT_2F inner0 = D2D1::Point2F(
            cx + std::cos(a0) * innerR, cy + std::sin(a0) * innerR);

        sink->BeginFigure(outer0, D2D1_FIGURE_BEGIN_FILLED);
        sink->AddLine(outer1);
        sink->AddLine(inner1);
        sink->AddLine(inner0);
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    }
    sink->Close();
    sink->Release();

    g_d2dBrush->SetColor(ColorOf(color, multiply));
    g_d2dTarget->FillGeometry(geometry, g_d2dBrush);
    geometry->Release();
}

// A soft top-light over the clay: the upper half catches the light while the
// lower half rolls into shade. In mask mode the sheen is painted as a donut so
// the live preview hole stays fully transparent.
static void FillChipSheen(float cx, float cy, float outerR, float holeR,
                          float alpha)
{
    if (!g_d2dTarget || alpha <= 0.0f)
        return;

    D2D1_GRADIENT_STOP stops[] = {
        {0.00f, ColorOf(0xFFFFFFFF, 0.15f * alpha)},
        {0.34f, ColorOf(0xFFFFFFFF, 0.05f * alpha)},
        {0.52f, ColorOf(0xFF000000, 0.00f)},
        {1.00f, ColorOf(0xFF000000, 0.16f * alpha)},
    };
    ID2D1GradientStopCollection* collection = nullptr;
    if (FAILED(g_d2dTarget->CreateGradientStopCollection(
            stops, ARRAYSIZE(stops), D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP,
            &collection)) ||
        !collection)
        return;

    ID2D1LinearGradientBrush* brush = nullptr;
    if (SUCCEEDED(g_d2dTarget->CreateLinearGradientBrush(
            D2D1::LinearGradientBrushProperties(
                D2D1::Point2F(cx, cy - outerR),
                D2D1::Point2F(cx, cy + outerR)),
            collection, &brush)) &&
        brush)
    {
        if (holeR > 0.0f)
        {
            ID2D1PathGeometry* geometry =
                CreateDonutGeometry(cx, cy, outerR, holeR);
            if (geometry)
            {
                g_d2dTarget->FillGeometry(geometry, brush);
                geometry->Release();
            }
        }
        else
        {
            const D2D1_ELLIPSE ellipse =
                D2D1::Ellipse(D2D1::Point2F(cx, cy), outerR, outerR);
            g_d2dTarget->FillEllipse(&ellipse, brush);
        }
        brush->Release();
    }
    collection->Release();
}

// Paints the clay body shared by desktop chips, window chips and the create
// chip: a thin moulded edge, inset edge spots, the pressed rim groove and a
// soft sheen. `holeR` keeps the centre transparent for the window preview.
static void DrawChipBody(float cx, float cy, float r, UINT32 base, float holeR,
                         float alpha, int spotCount = 8)
{
    const float s = g_scale;
    const ChipPaint paint = ChipPaintFor(base);

    const float edge = std::max(1.0f, 1.0f * s);
    FillChipDisc(cx, cy, r, holeR, paint.edge, alpha);
    FillChipDisc(cx, cy, r - edge, holeR, paint.face, alpha);

    // Inserts stop at the pressed groove. They sit close to the moulded edge so
    // the wide clay band inside them has room for a printed title.
    const float spotInner = r * 0.86f;
    FillChipEdgeSpots(cx, cy, r - edge * 0.5f, spotInner, spotCount, 0.23f,
                      paint.spot, 0.95f * alpha);
    StrokeEllipse(cx, cy, spotInner, spotInner, paint.groove, 1.0f * s,
                  0.55f * alpha);
    StrokeEllipse(cx, cy, spotInner - 1.2f * s, spotInner - 1.2f * s,
                  0xFFFFFFFF, 0.7f * s, 0.10f * alpha);

    FillChipSheen(cx, cy, r, holeR, alpha);
}

// Four suit pips printed around the clay band, one every 90 degrees. They stay
// upright so they read at any position instead of rotating with the arc.
static void DrawChipSuitRing(float cx, float cy, float radius,
                             float startDegrees, UINT32 color, float multiply)
{
    if (!g_d2dTarget || !g_d2dBrush || radius <= 0.0f)
        return;
    IDWriteTextFormat* format = g_fmtChipSuit ? g_fmtChipSuit : g_fmtHint;
    if (!format)
        return;

    static const WCHAR* glyphs[] = {L"\u2660", L"\u2665", L"\u2666", L"\u2663"};
    const float fontHeight = format->GetFontSize() * 1.2f;
    const float boxWidth = format->GetFontSize() * 1.7f;
    for (int i = 0; i < 4; i++)
    {
        const float degrees = startDegrees + static_cast<float>(i) * 90.0f;
        const float angle = degrees * 3.14159265f / 180.0f;
        const float x = cx + std::cos(angle) * radius;
        const float y = cy + std::sin(angle) * radius;
        const RectF rect = {x - boxWidth / 2.0f, y - fontHeight / 2.0f,
                            x + boxWidth / 2.0f, y + fontHeight / 2.0f};
        DrawTextBlock(glyphs[i], format, rect, color,
                      DWRITE_TEXT_ALIGNMENT_CENTER, multiply);
    }
}

// A desktop rendered as a playing card: rank in the corners, suit pip, and the
// desktop name where a court card would put its label.
static void DrawDesktopCard(const PillView& pill, bool active, bool hovered,
                            bool selected, bool closeHovered)
{
    const float s = g_scale;
    const float alpha = pill.alpha;
    const RectF face = {pill.rect.l, pill.rect.t - pill.lift, pill.rect.r,
                        pill.rect.b - pill.lift};
    const float radius = 12.0f * s;

    const UINT32 faceColor = 0xFFF8F5EC;
    const UINT32 ink = 0xFF1C1B20;
    const UINT32 red = 0xFFC62828;
    const int suit = pill.desktop & 3;
    const UINT32 suitColor = (suit == 1 || suit == 2) ? red : ink;
    const WCHAR* glyph = suit == 0 ? L"\u2660"
                        : suit == 1 ? L"\u2665"
                        : suit == 2 ? L"\u2666"
                                    : L"\u2663";

    if (!StripBackgroundVisible() || pill.lift > 0.0f)
    {
        const RectF shadow = {face.l, face.t + 8.0f * s + pill.lift * 0.25f,
                              face.r, face.b + 14.0f * s + pill.lift};
        FillRound(shadow, radius + 2.0f * s, 0xFF000000,
                  0.32f * alpha + (pill.lift > 0.0f ? 0.08f : 0.0f));
    }

    FillRound(face, radius,
              hovered ? MixColor(faceColor, 0xFFE4DCC8, 0.55f) : faceColor,
              alpha);
    // Playing cards keep their printed ink border; selection never repaints it
    // with the accent color. A selected card gets a slightly heavier edge.
    const bool marked = selected || active;
    StrokeRound(face, radius, ink,
                (selected ? 2.0f : marked ? 1.3f : 1.0f) * s,
                (selected ? 0.55f : marked ? 0.40f : 0.30f) * alpha);
    const RectF inner = {face.l + 5.0f * s, face.t + 5.0f * s,
                         face.r - 5.0f * s, face.b - 5.0f * s};
    StrokeRound(inner, std::max(2.0f * s, radius - 4.0f * s), ink, 1.0f * s,
                0.12f * alpha);

    const float pad = 9.0f * s;
    const float idxW = 34.0f * s;
    const std::wstring rank = std::to_wstring(pill.desktop + 1);
    const RectF rankRect = {face.l + pad, face.t + 5.0f * s,
                            face.l + pad + idxW, face.t + 27.0f * s};
    const RectF suitRect = {face.l + pad, face.t + 24.0f * s,
                            face.l + pad + idxW, face.t + 44.0f * s};
    IDWriteTextFormat* suitFmt = g_fmtCardSuit ? g_fmtCardSuit : g_fmtPillLarge;
    DrawTextBlock(rank, g_fmtPillLarge, rankRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    DrawTextBlock(glyph, suitFmt, suitRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    const RectF bRankRect = {face.r - pad - idxW, face.b - 27.0f * s,
                             face.r - pad, face.b - 5.0f * s};
    const RectF bSuitRect = {face.r - pad - idxW, face.b - 44.0f * s,
                             face.r - pad, face.b - 24.0f * s};
    DrawRotatedTextBlock(rank, g_fmtPillLarge, bRankRect, suitColor,
                         DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    DrawRotatedTextBlock(glyph, suitFmt, bSuitRect, suitColor,
                         DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);

    const float h = face.H();
    const RectF bigSuit = {face.l + 18.0f * s, face.t + h * 0.27f,
                           face.r - 18.0f * s, face.t + h * 0.63f};
    DrawTextBlock(glyph, g_fmtCardSuitBig ? g_fmtCardSuitBig : suitFmt, bigSuit,
                  suitColor, DWRITE_TEXT_ALIGNMENT_CENTER, 0.14f * alpha);

    const bool renaming = g_renameDesktop == pill.desktop;
    const std::wstring& name =
        renaming ? g_renameText : g_desktops[pill.desktop].name;
    const RectF nameRect = {face.l + 8.0f * s, face.t + h * 0.64f,
                            face.r - 8.0f * s, face.t + h * 0.80f};
    DrawTextBlock(name, g_fmtHint, nameRect, ink,
                  DWRITE_TEXT_ALIGNMENT_CENTER, 0.78f * alpha);

    if (renaming && ((GetTickCount64() / 530) % 2) == 0)
    {
        const float textW = MeasureTextWidth(g_renameText, g_fmtHint);
        const float startX = nameRect.l + (nameRect.W() - textW) / 2.0f;
        const float caretX = std::min(nameRect.r, startX + textW + 1.0f * s);
        g_d2dBrush->SetColor(ColorOf(ink, 0.85f * alpha));
        g_d2dTarget->DrawLine(
            D2D1::Point2F(caretX, nameRect.t + 2.0f * s),
            D2D1::Point2F(caretX, nameRect.b - 2.0f * s), g_d2dBrush,
            1.4f * s);
    }

    if (pill.hasClose && !renaming)
    {
        g_d2dBrush->SetColor(
            ColorOf(ink, (closeHovered ? 0.95f : 0.45f) * alpha));
        const float ccx = pill.closeRect.l + pill.closeRect.W() / 2.0f;
        const float ccy = pill.closeRect.t + pill.closeRect.H() / 2.0f;
        const float arm = 4.4f * s;
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                              D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                              D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
    }
}

// A face-down playing card used as the create-desktop button. Clicking it or
// pulling it downward creates a new desktop.
static void DrawCreateCard(const RectF& rect, bool hovered, float pull)
{
    const float s = g_scale;
    const float lift = pull * 16.0f * s;
    const RectF card = {rect.l, rect.t + lift, rect.r, rect.b + lift};
    const float radius = 12.0f * s;
    const UINT32 gold = MixColor(0xFFD8B45A, g_theme.accent, 0.18f);

    const RectF shadow = {card.l, card.t + 8.0f * s, card.r,
                          card.b + 14.0f * s};
    FillRound(shadow, radius + 2.0f * s, 0xFF000000, 0.34f + 0.18f * pull);

    const UINT32 back =
        MixColor(g_theme.pillFill, g_theme.accent, hovered ? 0.30f : 0.20f);
    const UINT32 panel = MixColor(back, 0xFF000000, 0.18f);
    FillRound(card, radius, back, 1.0f);

    // Double border, like the frame printed on a real card back.
    StrokeRound(card, radius, gold, 2.2f * s, 0.90f);
    const RectF border = {card.l + 7.0f * s, card.t + 7.0f * s,
                          card.r - 7.0f * s, card.b - 7.0f * s};
    StrokeRound(border, std::max(3.0f * s, radius - 4.0f * s), gold,
                1.0f * s, 0.45f);

    const RectF inner = {card.l + 13.0f * s, card.t + 13.0f * s,
                         card.r - 13.0f * s, card.b - 13.0f * s};
    FillRound(inner, std::max(3.0f * s, radius - 6.0f * s), panel, 1.0f);
    StrokeRound(inner, std::max(3.0f * s, radius - 6.0f * s), gold,
                0.8f * s, 0.30f);

    // Fine diagonal lattice and small diamonds, clipped inside the frame.
    g_d2dTarget->PushAxisAlignedClip(
        D2D1::RectF(inner.l, inner.t, inner.r, inner.b),
        D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_d2dBrush->SetColor(ColorOf(gold, 0.12f));
    const float step = 14.0f * s;
    for (float x = inner.l - inner.H(); x < inner.r; x += step)
    {
        g_d2dTarget->DrawLine(D2D1::Point2F(x, inner.b),
                              D2D1::Point2F(x + inner.H(), inner.t),
                              g_d2dBrush, 1.0f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(x, inner.t),
                              D2D1::Point2F(x + inner.H(), inner.b),
                              g_d2dBrush, 1.0f * s);
    }

    D2D1::Matrix3x2F saved;
    g_d2dTarget->GetTransform(&saved);
    g_d2dBrush->SetColor(ColorOf(gold, 0.22f));
    const float diamondStep = 28.0f * s;
    for (float y = inner.t + diamondStep / 2.0f; y < inner.b;
         y += diamondStep)
    {
        for (float x = inner.l + diamondStep / 2.0f; x < inner.r;
             x += diamondStep)
        {
            g_d2dTarget->SetTransform(
                D2D1::Matrix3x2F::Rotation(45.0f, D2D1::Point2F(x, y)) *
                saved);
            const D2D1_RECT_F diamond =
                D2D1::RectF(x - 1.7f * s, y - 1.7f * s, x + 1.7f * s,
                            y + 1.7f * s);
            g_d2dTarget->FillRectangle(&diamond, g_d2dBrush);
        }
    }
    g_d2dTarget->SetTransform(saved);
    g_d2dTarget->PopAxisAlignedClip();

    // Central medallion with a ring of small ornaments.
    const float cx = (card.l + card.r) / 2.0f;
    const float cy = (card.t + card.b) / 2.0f - 6.0f * s;
    const float medRx = card.W() * 0.27f;
    const float medRy = card.H() * 0.31f;
    FillEllipse(cx, cy, medRx, medRy, MixColor(back, 0xFF000000, 0.12f),
                0.95f);
    StrokeEllipse(cx, cy, medRx, medRy, gold, 1.4f * s, 0.75f);
    StrokeEllipse(cx, cy, medRx * 0.80f, medRy * 0.80f, gold, 0.8f * s,
                  0.45f);

    g_d2dBrush->SetColor(ColorOf(gold, 0.70f));
    for (int k = 0; k < 12; k++)
    {
        const float angle = static_cast<float>(k) * 6.2831853f / 12.0f;
        const float x = cx + std::cos(angle) * medRx * 1.10f;
        const float y = cy + std::sin(angle) * medRy * 1.10f;
        g_d2dTarget->SetTransform(
            D2D1::Matrix3x2F::Rotation(45.0f, D2D1::Point2F(x, y)) * saved);
        const D2D1_RECT_F ornament =
            D2D1::RectF(x - 1.5f * s, y - 1.5f * s, x + 1.5f * s,
                        y + 1.5f * s);
        g_d2dTarget->FillRectangle(&ornament, g_d2dBrush);
    }
    g_d2dTarget->SetTransform(saved);

    const RectF label = {card.l + 18.0f * s, card.b - 36.0f * s,
                         card.r - 18.0f * s, card.b - 12.0f * s};
    FillRound(label, 7.0f * s, MixColor(back, 0xFF000000, 0.22f), 0.90f);
    StrokeRound(label, 7.0f * s, gold, 0.8f * s, 0.40f);
    DrawTextBlock(L"New desktop", g_fmtHint, label, g_theme.text,
                  DWRITE_TEXT_ALIGNMENT_CENTER, 0.78f);
}

static void ClearCardAnimation()
{
    g_cardAnim = CardAnimation();
    g_createAfterDraw = false;
}

static void KickCardAnimation()
{
    if (!g_overlay)
        return;
    g_lastFrameTick = GetTickCount64();
    SetTimer(g_overlay, kTimerFrame, 16, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

// Picks the card-sized slot where the new desktop will appear. The desktop does
// not exist yet, so this is derived from the current layout: the slot before the
// create card in the flat row, or the centred card in the carousel.
static RectF FutureDesktopCardRect()
{
    const float s = g_scale;
    const bool validCreate = g_createRect.W() > 0.0f && g_createRect.H() > 0.0f;
    if (validCreate && IsWheel())
    {
        for (const PillView& pill : g_pills)
        {
            if (pill.visible && pill.desktop == g_currentDesktop)
            {
                const float cx =
                    (g_layout.strip.l + g_layout.strip.r) / 2.0f;
                const float w = pill.rect.W();
                const float top = pill.rect.t - pill.lift;
                const float bottom = pill.rect.b - pill.lift;
                return {cx - w / 2.0f, top, cx + w / 2.0f, bottom};
            }
        }
    }
    else if (validCreate && !g_pills.empty())
    {
        // Adding a desktop recentres the flat row, which puts the new last card
        // almost exactly at the create card's left edge, less half a gap.
        const float gap =
            std::max(0.0f, g_createRect.l - g_pills.back().rect.r);
        const float w = g_pills.back().rect.W();
        const float h = g_pills.back().rect.H();
        const float cx = g_createRect.l - gap / 2.0f;
        const float cy = (g_createRect.t + g_createRect.b) / 2.0f;
        return {cx - w / 2.0f, cy - h / 2.0f, cx + w / 2.0f, cy + h / 2.0f};
    }

    // Fallback: a card-sized rectangle centred on the strip.
    const float cardW = 160.0f * g_cardScale * s;
    const float cardH = 224.0f * g_cardScale * s;
    const float cx = (g_layout.strip.l + g_layout.strip.r) / 2.0f;
    const float cy = (g_layout.strip.t + g_layout.strip.b) / 2.0f;
    return {cx - cardW / 2.0f, cy - cardH / 2.0f,
            cx + cardW / 2.0f, cy + cardH / 2.0f};
}

// Draws a card from the create deck before the shell creates the desktop. The
// frame timer sends Win+Ctrl+D when the ghost reaches its landing slot.
static void StartDesktopCreateDraw()
{
    if (!g_cardAnimations || !UsesCards() || !g_overlay)
        return;

    CardAnimation anim;
    anim.mode = CardAnimationMode::Draw;
    anim.number = static_cast<int>(g_desktops.size()) + 1;
    anim.suit = static_cast<int>(g_desktops.size()) & 3;
    anim.name = L"Desktop " + std::to_wstring(g_desktops.size() + 1);
    anim.from = g_createRect;
    anim.to = FutureDesktopCardRect();
    anim.fromScale = 0.88f;
    anim.toScale = 1.0f;
    anim.fromAngle = -8.0f;
    anim.toAngle = 0.0f;
    anim.start = GetTickCount64();
    anim.duration = AnimationSeconds(0.52f);
    g_cardAnim = anim;
    g_createAfterDraw = true;
    KickCardAnimation();
}

static void FinishDesktopCreateAfterDraw()
{
    if (!g_createAfterDraw)
        return;

    g_createAfterDraw = false;
    ClearCardAnimation();
    SendChord('D', false);
    if (g_overlay)
    {
        SetTimer(g_overlay, kTimerDesktop, 40, nullptr);
        InvalidateRect(g_overlay, nullptr, FALSE);
    }
    KickCarousel();
}

// Tosses a closing desktop card up and off the right edge. The caller invokes
// this before the desktop action, while the desktop and its pill still exist.
static void StartDesktopCardThrow(int desktop)
{
    const GUID noDesktop = {};
    if (!g_cardAnimations || !UsesCards() || desktop < 0 ||
        desktop >= static_cast<int>(g_desktops.size()) ||
        IsEqualGUID(g_desktops[desktop].id, noDesktop))
        return;

    RectF from = g_createRect;
    for (const PillView& pill : g_pills)
    {
        if (pill.desktop == desktop && pill.visible)
        {
            from = pill.rect;
            from.t -= pill.lift;
            from.b -= pill.lift;
            break;
        }
    }

    CardAnimation anim;
    anim.mode = CardAnimationMode::Throw;
    anim.desktopId = g_desktops[desktop].id;
    anim.number = desktop + 1;
    anim.suit = desktop & 3;
    anim.name = g_desktops[desktop].name;
    anim.from = from;
    const float dx = g_layout.w - from.l + 80.0f * g_scale;
    anim.to = {from.l + dx, from.t - 180.0f * g_scale,
               from.r + dx, from.b - 180.0f * g_scale};
    anim.fromScale = 1.0f;
    anim.toScale = 0.72f;
    anim.fromAngle = 0.0f;
    anim.toAngle = 75.0f;
    anim.start = GetTickCount64();
    anim.duration = AnimationSeconds(0.42f);
    g_cardAnim = anim;
    KickCardAnimation();
}

// A compact playing-card face used by the draw and throw ghosts. It mirrors the
// desktop-card language but takes its rank, suit and name from the animation,
// so it can outlive the desktop it represents.
static void DrawGhostCardFace(const RectF& face, int number, int suit,
                              const std::wstring& name, float alpha)
{
    if (face.W() <= 0.0f || face.H() <= 0.0f || alpha <= 0.01f)
        return;

    const float s = g_scale;
    const float radius = 12.0f * s;
    const UINT32 faceColor = 0xFFF8F5EC;
    const UINT32 ink = 0xFF1C1B20;
    const UINT32 red = 0xFFC62828;
    const UINT32 suitColor = (suit == 1 || suit == 2) ? red : ink;
    const WCHAR* glyph = suit == 0 ? L"\u2660"
                        : suit == 1 ? L"\u2665"
                        : suit == 2 ? L"\u2666"
                                    : L"\u2663";

    const RectF shadow = {face.l, face.t + 8.0f * s, face.r,
                          face.b + 14.0f * s};
    FillRound(shadow, radius + 2.0f * s, 0xFF000000, 0.28f * alpha);
    FillRound(face, radius, faceColor, alpha);
    StrokeRound(face, radius, ink, 1.0f * s, 0.55f * alpha);
    const RectF inner = {face.l + 5.0f * s, face.t + 5.0f * s,
                         face.r - 5.0f * s, face.b - 5.0f * s};
    StrokeRound(inner, std::max(2.0f * s, radius - 4.0f * s), ink,
                1.0f * s, 0.14f * alpha);

    const float pad = 9.0f * s;
    const float idxW = 34.0f * s;
    const std::wstring rank = std::to_wstring(number);
    IDWriteTextFormat* suitFmt = g_fmtCardSuit ? g_fmtCardSuit : g_fmtPillLarge;
    const RectF rankRect = {face.l + pad, face.t + 5.0f * s,
                            face.l + pad + idxW, face.t + 27.0f * s};
    const RectF suitRect = {face.l + pad, face.t + 24.0f * s,
                            face.l + pad + idxW, face.t + 44.0f * s};
    DrawTextBlock(rank, g_fmtPillLarge, rankRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    DrawTextBlock(glyph, suitFmt, suitRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    const RectF bRankRect = {face.r - pad - idxW, face.b - 27.0f * s,
                             face.r - pad, face.b - 5.0f * s};
    const RectF bSuitRect = {face.r - pad - idxW, face.b - 44.0f * s,
                             face.r - pad, face.b - 24.0f * s};
    DrawRotatedTextBlock(rank, g_fmtPillLarge, bRankRect, suitColor,
                         DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    DrawRotatedTextBlock(glyph, suitFmt, bSuitRect, suitColor,
                         DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);

    const float h = face.H();
    const RectF bigSuit = {face.l + 18.0f * s, face.t + h * 0.27f,
                           face.r - 18.0f * s, face.t + h * 0.63f};
    DrawTextBlock(glyph, g_fmtCardSuitBig ? g_fmtCardSuitBig : suitFmt, bigSuit,
                  suitColor, DWRITE_TEXT_ALIGNMENT_CENTER, 0.14f * alpha);

    if (!name.empty())
    {
        const RectF nameRect = {face.l + 8.0f * s, face.t + h * 0.64f,
                                face.r - 8.0f * s, face.t + h * 0.80f};
        DrawTextBlock(name, g_fmtHint, nameRect, ink,
                      DWRITE_TEXT_ALIGNMENT_CENTER, 0.78f * alpha);
    }
}

// While a throw ghost is in flight, the real desktop tab is hidden so the card
// does not appear twice. A pre-create draw has no tab yet, so its zero GUID
// never matches. The check uses the elapsed time rather than just the mode, so
// the tab reappears on the same frame the ghost leaves.
static bool CardAnimationHidesDesktop(int desktop)
{
    const GUID noDesktop = {};
    if (g_cardAnim.mode == CardAnimationMode::None || desktop < 0 ||
        desktop >= static_cast<int>(g_desktops.size()) ||
        IsEqualGUID(g_cardAnim.desktopId, noDesktop) ||
        !IsEqualGUID(g_cardAnim.desktopId, g_desktops[desktop].id))
        return false;
    const float duration = std::max(0.05f, g_cardAnim.duration);
    const float elapsed =
        static_cast<float>(GetTickCount64() - g_cardAnim.start) / 1000.0f;
    return elapsed < duration;
}

static void DrawCardAnimation()
{
    if (g_cardAnim.mode == CardAnimationMode::None)
        return;

    const float duration = std::max(0.05f, g_cardAnim.duration);
    const float elapsed =
        static_cast<float>(GetTickCount64() - g_cardAnim.start) / 1000.0f;
    if (elapsed >= duration)
    {
        // A pre-create draw is completed by the frame timer, which sends the
        // create chord; leave the ghost at its landing slot until then.
        if (!g_createAfterDraw)
            ClearCardAnimation();
        return;
    }

    const float t = std::max(0.0f, std::min(1.0f, elapsed / duration));
    const float eased = EaseOutCubic(t);
    RectF rect = {g_cardAnim.from.l + (g_cardAnim.to.l - g_cardAnim.from.l) * eased,
                  g_cardAnim.from.t + (g_cardAnim.to.t - g_cardAnim.from.t) * eased,
                  g_cardAnim.from.r + (g_cardAnim.to.r - g_cardAnim.from.r) * eased,
                  g_cardAnim.from.b + (g_cardAnim.to.b - g_cardAnim.from.b) * eased};

    // A small arc makes the card feel lifted while it travels.
    const float arc = std::sin(t * 3.14159265f);
    if (g_cardAnim.mode == CardAnimationMode::Draw)
    {
        const float lift = arc * 18.0f * g_scale;
        rect.t -= lift;
        rect.b -= lift;
    }
    else
    {
        // A throw arcs upward while it drifts to the right, like a card being
        // tossed away, instead of dropping below the strip.
        const float lift = arc * 30.0f * g_scale;
        const float drift = arc * 10.0f * g_scale;
        rect.t -= lift;
        rect.b -= lift;
        rect.l += drift;
        rect.r += drift;
    }

    const float scale = g_cardAnim.fromScale +
                        (g_cardAnim.toScale - g_cardAnim.fromScale) * eased;
    const float angle = g_cardAnim.fromAngle +
                        (g_cardAnim.toAngle - g_cardAnim.fromAngle) * eased;
    float alpha = 1.0f;
    if (g_cardAnim.mode == CardAnimationMode::Throw)
    {
        const float fade = std::max(0.0f, std::min(1.0f, (t - 0.55f) / 0.45f));
        alpha = 1.0f - EaseOutCubic(fade);
    }

    const float cx = (rect.l + rect.r) / 2.0f;
    const float cy = (rect.t + rect.b) / 2.0f;
    D2D1::Matrix3x2F saved;
    g_d2dTarget->GetTransform(&saved);
    g_d2dTarget->SetTransform(
        D2D1::Matrix3x2F::Scale(scale, scale, D2D1::Point2F(cx, cy)) *
        D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(cx, cy)) * saved);
    DrawGhostCardFace(rect, g_cardAnim.number, g_cardAnim.suit, g_cardAnim.name,
                      alpha);
    g_d2dTarget->SetTransform(saved);
}

// A desktop tab rendered as a poker chip: coloured rim with edge spots, the
// desktop number on the centre disc, and the name on a small label below.
static void DrawChipTab(const PillView& pill, bool active, bool hovered,
                        bool selected, bool closeHovered)
{
    const float s = g_scale;
    const float alpha = pill.alpha;
    const RectF tab = {pill.rect.l, pill.rect.t - pill.lift, pill.rect.r,
                       pill.rect.b - pill.lift};
    const float baseD = (g_stripStyle == StripStyle::Carousel ? 64.0f : 52.0f) * s;
    const float chipD = std::max(24.0f * s, std::min(baseD, tab.W() - 4.0f * s));
    const float r = chipD / 2.0f;
    const float cx = tab.l + tab.W() / 2.0f;
    const float cy = tab.t + 2.0f * s + r;

    UINT32 chipColor = ChipColorForIndex(pill.desktop);
    if (hovered)
        chipColor = MixColor(chipColor, 0xFFFFFFFF, 0.12f);

    if (!StripBackgroundVisible() || pill.lift > 0.0f)
    {
        const RectF shadow = {cx - r, cy - r + 5.0f * s + pill.lift * 0.25f,
                              cx + r, cy + r + 8.0f * s + pill.lift};
        FillRound(shadow, r, 0xFF000000,
                  0.30f * alpha + (pill.lift > 0.0f ? 0.08f : 0.0f));
    }

    DrawChipBody(cx, cy, r, chipColor, 0.0f, alpha);

    // Cream inlay for the desktop number, framed by a pressed ring and a ring
    // of suit pips, like the centre of a real casino chip.
    const ChipPaint paint = ChipPaintFor(chipColor);
    const float discR = r * 0.58f;
    FillEllipse(cx, cy, discR + 1.6f * s, discR + 1.6f * s, paint.edge,
                0.55f * alpha);
    FillEllipse(cx, cy, discR, discR, paint.inlay, alpha);
    StrokeEllipse(cx, cy, discR * 0.86f, discR * 0.86f,
                  MixColor(paint.inlay, chipColor, 0.42f), 0.8f * s,
                  0.55f * alpha);
    DrawChipSuitRing(cx, cy, r * 0.72f, 0.0f, paint.spot, 0.62f * alpha);

    const RectF disc = {cx - discR, cy - discR, cx + discR, cy + discR};
    DrawTextBlock(std::to_wstring(pill.desktop + 1), g_fmtPillLarge, disc,
                  ChipDiscInk(chipColor), DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    if (g_desktopSelection == DesktopSelection::Highlight && (selected || active))
    {
        StrokeEllipse(cx, cy, r, r, g_theme.accent,
                      (selected ? 2.6f : 2.0f) * s, 0.95f * alpha);
        StrokeEllipse(cx, cy, r - 2.0f * s, r - 2.0f * s,
                      ChipTextColor(chipColor), 1.0f * s, 0.55f * alpha);
    }
    else if (hovered)
        StrokeEllipse(cx, cy, r, r, ChipTextColor(chipColor), 1.5f * s,
                      0.65f * alpha);
    else if (g_desktopSelection == DesktopSelection::Lift && (selected || active))
        StrokeEllipse(cx, cy, r, r, ChipTextColor(chipColor), 1.2f * s,
                      0.28f * alpha);

    const bool renaming = g_renameDesktop == pill.desktop;
    const std::wstring& name =
        renaming ? g_renameText : g_desktops[pill.desktop].name;
    const RectF label = {tab.l + 2.0f * s, cy + r + 2.0f * s,
                         tab.r - 2.0f * s, tab.b};
    if (!StripBackgroundVisible())
        FillRound(label, 8.0f * s, g_theme.pillFill, 0.85f * alpha);
    DrawTextBlock(name, g_fmtHint, label, g_theme.text,
                  DWRITE_TEXT_ALIGNMENT_CENTER, 0.85f * alpha);

    if (renaming && ((GetTickCount64() / 530) % 2) == 0)
    {
        const float textW = MeasureTextWidth(g_renameText, g_fmtHint);
        const float startX = label.l + (label.W() - textW) / 2.0f;
        const float caretX = std::min(label.r, startX + textW + 1.0f * s);
        g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.85f * alpha));
        g_d2dTarget->DrawLine(
            D2D1::Point2F(caretX, label.t + 2.0f * s),
            D2D1::Point2F(caretX, label.b - 2.0f * s), g_d2dBrush, 1.4f * s);
    }

    if (pill.hasClose && !renaming)
    {
        g_d2dBrush->SetColor(ColorOf(
            ChipTextColor(chipColor), (closeHovered ? 0.95f : 0.55f) * alpha));
        const float ccx = pill.closeRect.l + pill.closeRect.W() / 2.0f;
        const float ccy = pill.closeRect.t + pill.closeRect.H() / 2.0f;
        const float arm = 3.8f * s;
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                              D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                              D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
    }
}

// In all-desktop search, prefix every result with its desktop number so the
// mixed list is readable even though live thumbnails are only available for the
// active desktop.
static std::wstring WindowDisplayTitle(const WindowEntry& entry)
{
    if (!g_searchAllDesktops || entry.desktopIndex < 0)
        return entry.title;
    return L"D" + std::to_wstring(entry.desktopIndex + 1) + L"  \u00B7  " +
           entry.title;
}

// A window rendered as a regular preview card.
static void DrawWindowCard(const CardView& card, bool selected, bool hovered,
                           bool closeHovered)
{
    const float s = g_scale;
    const RectF rect = card.rect;
    const RectF header = card.header;
    const RectF preview = card.preview;
    const RectF closeRect = card.close;
    const float radius = 10.0f * s;
    const float lift = card.lift;

    const RectF shadow = {rect.l, rect.t + 5.0f * s + lift * 0.25f, rect.r,
                          rect.b + 7.0f * s + lift};
    FillRound(shadow, radius + 2.0f * s, 0xFF000000,
              0.28f + (lift > 0.0f ? 0.07f : 0.0f));

    const UINT32 fill =
        selected ? g_theme.cardSelected
                 : (hovered ? g_theme.cardHover : g_theme.cardFill);
    FillRound(rect, radius, fill, 1.0f);
    // Keep card selection in the fill and a neutral edge; cards do not use the
    // accent outline that pills and chips use.
    StrokeRound(rect, radius, g_theme.text, 1.4f * s,
                selected ? 0.32f : (hovered ? 0.16f : 0.08f));

    const UINT32 heldColor =
        (card.entry >= 0 && card.entry < static_cast<int>(g_windows.size()))
            ? HeldColorOf(g_windows[card.entry].hwnd)
            : 0;
    if (heldColor)
    {
        StrokeRound(rect, radius, heldColor, 2.2f * s, 0.95f);
        FillEllipse(rect.r - 14.0f * s, rect.b - 14.0f * s, 4.0f * s,
                    4.0f * s, heldColor, 1.0f);
    }

    if (card.entry < 0 || card.entry >= static_cast<int>(g_windows.size()))
        return;

    WindowEntry& entry = g_windows[card.entry];
    const bool iconFallback = !entry.onCurrentDesktop;
    float fallbackIconSize = 0.0f;
    ID2D1Bitmap* fallbackIcon = nullptr;
    if (iconFallback)
    {
        const float iconMax = std::min(preview.W(), preview.H()) * 0.42f;
        fallbackIconSize = std::max(8.0f * s, std::min(48.0f * s, iconMax));
        fallbackIcon = EnsureEntryIcon(
            entry, static_cast<int>(std::lround(fallbackIconSize)));
    }

    float textX = header.l + 14.0f * s;
    if (g_showIcons)
    {
        // Off-desktop cards reuse the larger preview icon for the header so the
        // per-entry icon cache does not thrash between two sizes every frame.
        ID2D1Bitmap* icon = fallbackIcon;
        if (!icon && !iconFallback)
            icon = EnsureEntryIcon(
                entry, static_cast<int>(std::lround(18.0f * s)));
        if (icon)
        {
            const float iconSize =
                std::min(18.0f * s, std::max(8.0f * s, header.H() - 4.0f * s));
            const float iconTop = header.t + (header.H() - iconSize) / 2.0f;
            const D2D1_RECT_F dest =
                D2D1::RectF(header.l + 12.0f * s, iconTop,
                            header.l + 12.0f * s + iconSize, iconTop + iconSize);
            g_d2dTarget->DrawBitmap(icon, &dest, 1.0f,
                                    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
            textX = header.l + 12.0f * s + iconSize + 8.0f * s;
        }
    }

    const RectF titleRect = {
        textX, header.t,
        header.r - (closeHovered ? 34.0f * s : 12.0f * s), header.b};
    IDWriteTextFormat* titleFormat =
        header.H() >= 28.0f * s ? g_fmtCard : g_fmtHint;
    DrawTextBlock(WindowDisplayTitle(entry), titleFormat, titleRect, g_theme.text,
                  DWRITE_TEXT_ALIGNMENT_LEADING, 0.94f);

    if (closeHovered)
    {
        FillRound(closeRect, std::min(5.0f * s, closeRect.W() / 2.0f),
                  g_theme.danger, 0.9f);
        g_d2dBrush->SetColor(ColorOf(0xFFFFFFFF, 0.95f));
        const float arm = std::min(4.6f * s, closeRect.W() * 0.30f);
        const float bcx = closeRect.l + closeRect.W() / 2.0f;
        const float bcy = closeRect.t + closeRect.H() / 2.0f;
        g_d2dTarget->DrawLine(D2D1::Point2F(bcx - arm, bcy - arm),
                              D2D1::Point2F(bcx + arm, bcy + arm), g_d2dBrush,
                              1.4f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(bcx + arm, bcy - arm),
                              D2D1::Point2F(bcx - arm, bcy + arm), g_d2dBrush,
                              1.4f * s);
    }

    FillRound(preview, 6.0f * s, g_theme.previewFill, 1.0f);
    StrokeRound(preview, 6.0f * s, g_theme.text, 1.0f * s, 0.07f);

    // Inactive desktops are cloaked, so DWM cannot provide a live thumbnail.
    // Show the application icon in the preview instead of an empty rectangle.
    if (iconFallback && fallbackIcon)
    {
        const float centerX = (preview.l + preview.r) / 2.0f;
        const float centerY = (preview.t + preview.b) / 2.0f;
        const D2D1_RECT_F dest = D2D1::RectF(
            centerX - fallbackIconSize / 2.0f,
            centerY - fallbackIconSize / 2.0f,
            centerX + fallbackIconSize / 2.0f,
            centerY + fallbackIconSize / 2.0f);
        g_d2dTarget->DrawBitmap(fallbackIcon, &dest, 0.90f,
                                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    }
}

// A window rendered as a poker chip. The DWM preview, app icon or an empty
// centre is framed by the rim, and the title follows the top arc. In mask mode
// the chip is painted into the top-level layered mask with a circular hole: the
// DWM thumbnail below shows through the hole while the opaque ring hides the
// square corners of the thumbnail.
static void DrawWindowChip(const CardView& card, bool selected, bool hovered,
                           bool closeHovered, bool mask = false)
{
    if (card.entry < 0 || card.entry >= static_cast<int>(g_windows.size()))
        return;

    const float s = g_scale;
    const RectF rect = card.rect;
    const float diameter = std::min(rect.W(), rect.H());
    const float r = diameter / 2.0f;
    const float cx = (rect.l + rect.r) / 2.0f;
    const float cy = (rect.t + rect.b) / 2.0f;
    const float lift = card.lift;
    const float previewR = card.preview.W() / 2.0f;

    WindowEntry& entry = g_windows[card.entry];
    UINT32 base = ChipColorForIndex(card.entry);
    if (hovered)
        base = MixColor(base, 0xFFFFFFFF, 0.10f);
    const UINT32 textColor = ChipTextColor(base);
    const bool donut = mask && previewR > 0.0f;

    if (!mask)
    {
        FillEllipse(cx, cy + 7.0f * s + lift * 0.35f, r * 1.01f, r * 0.98f,
                    0xFF000000, 0.30f + (lift > 0.0f ? 0.08f : 0.0f));
    }

    const ChipPaint paint = ChipPaintFor(base);
    const float holeR = donut ? previewR : 0.0f;
    DrawChipBody(cx, cy, r, base, holeR, 1.0f);

    // The centre inlay: on a real chip the live thumbnail (or the icon disc)
    // sits inside a pressed ring, with a thin printed ring just outside it.
    if (!mask && g_windowChipContent == WindowChipContent::Preview)
    {
        FillEllipse(cx, cy, previewR, previewR, g_theme.previewFill, 1.0f);
    }
    StrokeEllipse(cx, cy, previewR + 0.8f * s, previewR + 0.8f * s,
                  paint.groove, 1.2f * s, 0.75f);
    StrokeEllipse(cx, cy, previewR + 2.4f * s, previewR + 2.4f * s,
                  paint.inlay, 0.8f * s, 0.32f);

    if (!mask && (g_windowChipContent == WindowChipContent::Icon ||
                  (g_windowChipContent == WindowChipContent::Preview &&
                   !entry.onCurrentDesktop)))
    {
        if (g_windowChipContent == WindowChipContent::Icon)
            FillEllipse(cx, cy, r * 0.34f, r * 0.34f,
                        MixColor(base, 0xFFFFFFFF, 0.16f), 1.0f);
        ID2D1Bitmap* icon = EnsureEntryIcon(
            entry, static_cast<int>(std::lround(64.0f * s)));
        if (icon)
        {
            const float iconSize = r * 0.44f;
            const D2D1_RECT_F dest = D2D1::RectF(
                cx - iconSize / 2.0f, cy - iconSize / 2.0f,
                cx + iconSize / 2.0f, cy + iconSize / 2.0f);
            g_d2dTarget->DrawBitmap(icon, &dest, 0.92f,
                                    D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        }
    }
    // Blank content: the curved title is the only thing in the centre.

    // Keep the title in the clay band between the centre inlay and the edge
    // inserts, where a real chip prints its text, instead of on top of the
    // preview or the inlaid spots. Centring it in the clear band keeps both
    // rings from crowding the glyphs.
    IDWriteTextFormat* titleFormat =
        r >= 120.0f * s ? g_fmtPillLarge
        : r >= 80.0f * s ? g_fmtPill
                         : g_fmtHint;
    const float titleInner = previewR + 3.6f * s;
    const float titleOuter = r * 0.86f - 1.6f * s;
    const float titleRadius = (titleInner + titleOuter) * 0.5f;
    DrawChipSuitRing(cx, cy, titleRadius, 22.5f, paint.spot, 0.62f);
    DrawArcText(WindowDisplayTitle(entry), titleFormat, cx, cy, titleRadius,
                textColor, 170.0f, 0.95f);

    const UINT32 heldColor = HeldColorOf(entry.hwnd);
    if (selected)
    {
        StrokeEllipse(cx, cy, r + 1.0f * s, r + 1.0f * s, g_theme.accent,
                      2.4f * s, 0.95f);
        StrokeEllipse(cx, cy, r - 1.5f * s, r - 1.5f * s,
                      ChipTextColor(base), 1.2f * s, 0.65f);
    }
    else if (heldColor)
    {
        StrokeEllipse(cx, cy, r + 1.0f * s, r + 1.0f * s,
                      MixColor(heldColor, textColor, 0.30f), 2.2f * s, 0.95f);
    }
    else if (hovered)
    {
        StrokeEllipse(cx, cy, r + 1.0f * s, r + 1.0f * s,
                      ChipTextColor(base), 1.4f * s, 0.60f);
    }

    if (heldColor)
        FillEllipse(cx + r * 0.62f, cy + r * 0.62f, 4.0f * s, 4.0f * s,
                    heldColor, 1.0f);

    if (closeHovered)
    {
        const float closeR = card.close.W() / 2.0f;
        const float ccx = card.close.l + closeR;
        const float ccy = card.close.t + closeR;
        FillEllipse(ccx, ccy, closeR, closeR, g_theme.danger, 0.92f);
        g_d2dBrush->SetColor(ColorOf(0xFFFFFFFF, 0.96f));
        const float arm = closeR * 0.38f;
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                              D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                              D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush,
                              1.4f * s);
    }
}

////////////////////////////////////////////////////////////////////////////////
// WINDOW-CHIP LAYERS
//
// DWM thumbnails are composed above normal window content and are not clipped
// by a window region. A window chip therefore uses two extra top-level windows:
// a host that owns the thumbnail and a layered mask above it. The mask paints
// the chip foreground as a donut, leaving a transparent circular hole over the
// thumbnail. The host region is the union of the preview squares, so the mask's
// transparent area cannot reveal the host's black background.

static void ReleaseChipMaskSurface()
{
    if (g_maskDC)
    {
        if (g_maskOldBitmap)
            SelectObject(g_maskDC, g_maskOldBitmap);
        DeleteDC(g_maskDC);
    }
    if (g_maskBitmap)
        DeleteObject(g_maskBitmap);
    g_maskDC = nullptr;
    g_maskBitmap = nullptr;
    g_maskOldBitmap = nullptr;
    g_maskBits = nullptr;
    g_maskW = 0;
    g_maskH = 0;
}

static bool EnsureChipMaskSurface()
{
    if (!g_chipMask || g_monitorW <= 0 || g_monitorH <= 0)
        return false;
    if (g_maskBitmap && g_maskW == g_monitorW && g_maskH == g_monitorH)
        return true;

    ReleaseChipMaskSurface();

    BITMAPINFO info = {};
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = g_monitorW;
    info.bmiHeader.biHeight = -g_monitorH;  // Top-down: row 0 is the top.
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HBITMAP bitmap = CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, &bits,
                                      nullptr, 0);
    if (!bitmap)
        return false;

    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc)
    {
        DeleteObject(bitmap);
        return false;
    }

    HGDIOBJ old = SelectObject(dc, bitmap);
    g_maskBitmap = bitmap;
    g_maskDC = dc;
    g_maskOldBitmap = old;
    g_maskBits = bits;
    g_maskW = g_monitorW;
    g_maskH = g_monitorH;
    return true;
}

static void SetChipLayersVisible(bool visible)
{
    if (!visible)
    {
        if (!g_chipLayersVisible && g_chipThumbs.handles.empty())
            return;
        ReleaseThumbnailSet(g_chipThumbs);
        if (g_thumbHost)
            ShowWindow(g_thumbHost, SW_HIDE);
        if (g_chipMask)
            ShowWindow(g_chipMask, SW_HIDE);
        g_chipLayersVisible = false;
        g_chipRegionHash = 0;
        return;
    }

    if (g_chipLayersVisible)
        return;
    if (!g_thumbHost || !g_chipMask)
        return;

    // Keep both windows hidden until the host region, thumbnails and mask have
    // all been prepared, otherwise a black square can flash for one frame.
    SetWindowPos(g_thumbHost, HWND_TOPMOST, g_monitorX, g_monitorY, g_monitorW,
                 g_monitorH, SWP_NOACTIVATE);
    SetWindowPos(g_chipMask, HWND_TOPMOST, g_monitorX, g_monitorY, g_monitorW,
                 g_monitorH, SWP_NOACTIVATE);
    g_chipLayersVisible = true;
    g_chipRegionHash = 0;
}

static void UpdateChipHostRegion(const std::vector<RectF>& rects)
{
    if (!g_thumbHost)
        return;

    uint64_t hash = 1469598103934665603ull;
    auto mix = [&hash](long long value) {
        hash ^= static_cast<uint64_t>(value);
        hash *= 1099511628211ull;
    };
    for (const RectF& rect : rects)
    {
        mix(std::lround(rect.l));
        mix(std::lround(rect.t));
        mix(std::lround(rect.r));
        mix(std::lround(rect.b));
    }
    if (hash == g_chipRegionHash)
        return;

    HRGN region = CreateRectRgn(0, 0, 0, 0);
    for (const RectF& rect : rects)
    {
        HRGN piece = CreateRectRgn(std::lround(rect.l), std::lround(rect.t),
                                   std::lround(rect.r), std::lround(rect.b));
        if (piece)
        {
            CombineRgn(region, region, piece, RGN_OR);
            DeleteObject(piece);
        }
    }
    // SetWindowRgn takes ownership of the region on success. Delete it if the
    // call fails so a display change cannot leak a region every frame, and
    // leave the hash unset so the region is retried on the next frame.
    if (!SetWindowRgn(g_thumbHost, region, TRUE))
    {
        DeleteObject(region);
        return;
    }
    g_chipRegionHash = hash;
}

static bool RenderChipMask(float sceneScale, float cx, float cy)
{
    if (!g_chipMask || !EnsureChipMaskSurface())
        return false;
    if (!EnsureFactories() || !EnsureDeviceResources())
        return false;
    EnsureTextFormats();

    RECT rc = {0, 0, g_maskW, g_maskH};
    if (FAILED(g_d2dTarget->BindDC(g_maskDC, &rc)))
        return false;

    if (g_maskBits)
        std::memset(g_maskBits, 0,
                    static_cast<size_t>(g_maskW) * g_maskH * 4);

    g_d2dTarget->BeginDraw();
    g_d2dTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    g_d2dTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
    g_d2dTarget->PushAxisAlignedClip(
        D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_maskW),
                    static_cast<float>(g_maskH)),
        D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

    auto scaledCard = [&](const CardView& card) {
        CardView view = card;
        view.rect = ScaleAbout(card.rect, sceneScale, cx, cy);
        view.header = ScaleAbout(card.header, sceneScale, cx, cy);
        view.preview = ScaleAbout(card.preview, sceneScale, cx, cy);
        view.close = ScaleAbout(card.close, sceneScale, cx, cy);
        view.lift = card.lift * sceneScale;
        return view;
    };

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        const CardView view = scaledCard(g_cards[i]);
        const bool isSelected = !g_focusStrip && !g_focusDock &&
                                g_cards[i].filtered == g_selected;
        DrawWindowChip(view, isSelected, g_hoverCard == i, g_hoverClose == i,
                       true);
    }
    for (int i = 0; i < static_cast<int>(g_dockCards.size()); i++)
    {
        const CardView view = scaledCard(g_dockCards[i]);
        const bool isSelected = g_focusDock && i == g_dockSelected;
        DrawWindowChip(view, isSelected, g_hoverDock == i,
                       g_hoverDockClose == i, true);
    }

    g_d2dTarget->PopAxisAlignedClip();
    if (g_d2dTarget->EndDraw() == static_cast<HRESULT>(0x8899000C))
    {
        ReleaseDeviceResources();
        return false;
    }

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;
    POINT source = {0, 0};
    SIZE size = {g_maskW, g_maskH};
    POINT destination = {g_monitorX, g_monitorY};
    return UpdateLayeredWindow(g_chipMask, nullptr, &destination, &size,
                               g_maskDC, &source, 0, &blend, ULW_ALPHA) != FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// RENDER

static void RenderScene(HDC dc)
{
    RECT client = {};
    GetClientRect(g_overlay, &client);

    if (!EnsureFactories() || !EnsureDeviceResources())
    {
        SetChipLayersVisible(false);
        return;
    }
    EnsureTextFormats();

    if (FAILED(g_d2dTarget->BindDC(dc, &client)))
    {
        SetChipLayersVisible(false);
        return;
    }

    UpdateLayout();

    // Opening / closing animation: fade plus a slight scale about the centre.
    const float presence = g_presence;
    const float eased = EaseOutCubic(std::max(0.0f, std::min(1.0f, presence)));
    const float sceneScale = 0.965f + 0.035f * eased;
    const float cx = g_layout.w / 2.0f;
    const float cy = g_layout.h / 2.0f;
    const float contentAlpha = eased;

    // DWM thumbnails are composed above the window, so they are not part of the
    // D2D scene: their rectangles are animated manually to match the cards.
    // Window squares keep their thumbnails on the overlay. Window chips use the
    // separate host so the circular mask can hide the square corners.
    std::vector<HWND> overlaySources;
    std::vector<RectF> overlayRects;
    std::vector<HWND> chipSources;
    std::vector<RectF> chipRects;
    if ((!g_busy || g_keepThumbnailsWhileBusy) && contentAlpha > 0.02f)
    {
        auto addThumbnails = [&](const std::vector<CardView>& cards,
                                 std::vector<HWND>& sources,
                                 std::vector<RectF>& rects, bool inset) {
            for (const CardView& card : cards)
            {
                if (card.entry < 0 ||
                    card.entry >= static_cast<int>(g_windows.size()))
                    continue;
                // Windows on inactive desktops are cloaked, so a DWM thumbnail
                // would be black. Their cards draw an icon fallback instead.
                if (!g_windows[card.entry].onCurrentDesktop)
                    continue;
                HWND source = g_windows[card.entry].hwnd;
                if (!source || !IsWindow(source))
                    continue;
                RectF preview = ScaleAbout(card.preview, sceneScale, cx, cy);
                if (inset)
                {
                    preview.l += 1.0f;
                    preview.t += 1.0f;
                    preview.r -= 1.0f;
                    preview.b -= 1.0f;
                }
                sources.push_back(source);
                rects.push_back(preview);
            }
        };

        if (!UsesWindowChips())
        {
            addThumbnails(g_cards, overlaySources, overlayRects, true);
            addThumbnails(g_dockCards, overlaySources, overlayRects, true);
        }
        else if (g_windowChipContent == WindowChipContent::Preview)
        {
            addThumbnails(g_cards, chipSources, chipRects, false);
            addThumbnails(g_dockCards, chipSources, chipRects, false);
        }
    }
    SyncThumbnails(overlaySources, overlayRects, contentAlpha);

    g_d2dTarget->BeginDraw();
    g_d2dTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_d2dTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
    g_d2dTarget->PushAxisAlignedClip(D2D1::RectF(0.0f, 0.0f, g_layout.w, g_layout.h),
                                     D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

    const bool useLayer = g_d2dLayer && contentAlpha < 0.999f;
    if (useLayer)
    {
        D2D1_LAYER_PARAMETERS parameters = D2D1::LayerParameters(
            D2D1::InfiniteRect(), nullptr, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
            D2D1::Matrix3x2F::Identity(), contentAlpha, nullptr, D2D1_LAYER_OPTIONS_NONE);
        g_d2dTarget->PushLayer(&parameters, g_d2dLayer);
    }

    const float s = g_scale;

    // Backdrop scrim. The tint color and how strongly it covers the backdrop are
    // configurable; the OS material (acrylic / mica / blur) sits underneath.
    const RectF full = {0.0f, 0.0f, g_layout.w, g_layout.h};
    const float baseScrim = BackgroundScrimAlpha();
    if (baseScrim > 0.001f)
        FillRound(full, 0.0f, g_theme.background, baseScrim);

    // Header title.
    const float titleRight =
        std::max(56.0f * s + 1.0f, g_layout.search.l - 24.0f * s);
    const RectF titleRect = {56.0f * s, 40.0f * s, titleRight, 40.0f * s + 46.0f * s};
    DrawTextBlock(g_titleText, g_fmtTitle, titleRect, g_theme.text,
                  DWRITE_TEXT_ALIGNMENT_LEADING, 0.92f);

    // Search field (hidden unless activated when "Always show search" is off).
    if (SearchVisible())
    {
        const float searchRadius = g_layout.search.H() / 2.0f;
        const bool searchAccent = g_searchFocused || g_searchAllDesktops;
        FillRound(g_layout.search, searchRadius, g_theme.searchFill, 0.95f);
        StrokeRound(g_layout.search, searchRadius,
                    searchAccent ? g_theme.accent : g_theme.text, 1.25f * s,
                    searchAccent ? 0.85f : 0.10f);

        // Magnifier glyph.
        {
            const float glyphX = g_layout.search.l + 22.0f * s;
            const float glyphY = g_layout.search.t + g_layout.search.H() / 2.0f;
            g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.55f));
            const D2D1_ELLIPSE circle = D2D1::Ellipse(
                D2D1::Point2F(glyphX, glyphY - 1.0f * s), 6.0f * s, 6.0f * s);
            g_d2dTarget->DrawEllipse(&circle, g_d2dBrush, 1.4f * s);
            g_d2dTarget->DrawLine(D2D1::Point2F(glyphX + 4.5f * s, glyphY + 3.5f * s),
                                  D2D1::Point2F(glyphX + 9.0f * s, glyphY + 8.0f * s),
                                  g_d2dBrush, 1.6f * s);
        }

        const std::wstring allDesktopsLabel = L"All desktops";
        const float allDesktopsW =
            (g_searchAllDesktops && !g_search.empty())
                ? MeasureTextWidth(allDesktopsLabel, g_fmtHint) + 18.0f * s
                : 0.0f;
        const float textLeft = g_layout.search.l + 42.0f * s;
        const float textRight =
            g_layout.search.r - (g_search.empty() ? 16.0f * s : 44.0f * s) -
            (allDesktopsW > 0.0f ? allDesktopsW + 8.0f * s : 0.0f);
        const RectF searchTextRect = {textLeft, g_layout.search.t, textRight,
                                      g_layout.search.b};
        if (g_search.empty())
        {
            DrawTextBlock(g_searchAllDesktops ? L"Search all desktops"
                                              : L"Search windows",
                          g_fmtSearch, searchTextRect, g_theme.text,
                          DWRITE_TEXT_ALIGNMENT_LEADING, 0.40f);
        }
        else
        {
            const float textW = MeasureTextWidth(g_search, g_fmtSearch);
            if (g_searchSelectAll)
            {
                const RectF selection = {
                    textLeft - 2.0f * s,
                    g_layout.search.t + 9.0f * s,
                    std::min(textRight, textLeft + textW + 2.0f * s),
                    g_layout.search.b - 9.0f * s};
                FillRound(selection, 4.0f * s, g_theme.accent, 0.35f);
            }

            DrawTextBlock(g_search, g_fmtSearch, searchTextRect, g_theme.text,
                          DWRITE_TEXT_ALIGNMENT_LEADING, 0.96f);
            g_d2dBrush->SetColor(
                ColorOf(g_theme.text, g_hoverSearchClear ? 0.85f : 0.45f));
            const float ccx = g_searchClearRect.l + g_searchClearRect.W() / 2.0f;
            const float ccy = g_searchClearRect.t + g_searchClearRect.H() / 2.0f;
            const float arm = 5.0f * s;
            g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                                  D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush,
                                  1.5f * s);
            g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                                  D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush,
                                  1.5f * s);
        }

        if (g_searchAllDesktops && !g_search.empty())
        {
            const float badgeRight = g_layout.search.r - 44.0f * s;
            const float badgeLeft = badgeRight - allDesktopsW;
            const RectF badge = {badgeLeft, g_layout.search.t + 7.0f * s,
                                 badgeRight, g_layout.search.b - 7.0f * s};
            FillRound(badge, badge.H() / 2.0f, g_theme.accent, 0.16f);
            DrawTextBlock(allDesktopsLabel, g_fmtHint, badge, g_theme.accent,
                          DWRITE_TEXT_ALIGNMENT_CENTER, 0.92f);
        }

        // Caret.
        if (g_searchFocused && !g_searchSelectAll &&
            ((GetTickCount64() / 530) % 2) == 0)
        {
            const float textW = MeasureTextWidth(g_search, g_fmtSearch);
            const float caretX = std::min(textRight, textLeft + textW + 1.0f * s);
            g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.85f));
            g_d2dTarget->DrawLine(D2D1::Point2F(caretX, g_layout.search.t + 12.0f * s),
                                  D2D1::Point2F(caretX, g_layout.search.b - 12.0f * s),
                                  g_d2dBrush, 1.4f * s);
        }
    }

    // The scene scales slightly while opening; the DWM thumbnails are scaled
    // separately, so every card is passed through the same transform here.
    auto scaledCard = [&](const CardView& card) {
        CardView view = card;
        view.rect = ScaleAbout(card.rect, sceneScale, cx, cy);
        view.header = ScaleAbout(card.header, sceneScale, cx, cy);
        view.preview = ScaleAbout(card.preview, sceneScale, cx, cy);
        view.close = ScaleAbout(card.close, sceneScale, cx, cy);
        view.lift = card.lift * sceneScale;
        return view;
    };

    // Window grid.
    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        const CardView view = scaledCard(g_cards[i]);
        const bool isSelected = !g_focusStrip && !g_focusDock &&
                                g_cards[i].filtered == g_selected;
        const bool isHovered = g_hoverCard == i;
        const bool closeHovered = g_hoverClose == i;
        if (UsesWindowChips())
            DrawWindowChip(view, isSelected, isHovered, closeHovered);
        else
            DrawWindowCard(view, isSelected, isHovered, closeHovered);
    }

    // Held-window side dock. It uses the same chip/card renderers, so held
    // windows look identical whether they stay inline or move to the side.
    if (!g_dockCards.empty())
    {
        if (g_heldDockBackground)
        {
            FillRound(g_dockArea, 14.0f * s, g_theme.stripFill, 0.78f);
            StrokeRound(g_dockArea, 14.0f * s, g_theme.text, 1.0f * s, 0.08f);
        }
        const RectF dockLabel = {g_dockArea.l + 12.0f * s,
                                 g_dockArea.t + 6.0f * s,
                                 g_dockArea.r - 12.0f * s,
                                 g_dockArea.t + 28.0f * s};
        DrawTextBlock(L"Held", g_fmtHint, dockLabel,
                      g_focusDock ? g_theme.accent : g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING, g_focusDock ? 0.95f : 0.55f);

        for (int i = 0; i < static_cast<int>(g_dockCards.size()); i++)
        {
            const CardView view = scaledCard(g_dockCards[i]);
            const bool isSelected = g_focusDock && i == g_dockSelected;
            const bool isHovered = g_hoverDock == i;
            const bool closeHovered = g_hoverDockClose == i;
            if (UsesWindowChips())
                DrawWindowChip(view, isSelected, isHovered, closeHovered);
            else
                DrawWindowCard(view, isSelected, isHovered, closeHovered);
        }
    }

    // Empty state.
    if (g_cards.empty() && g_dockCards.empty() && !g_busy)
    {
        const std::wstring message = g_search.empty()
            ? (g_searchAllDesktops ? L"No windows on any desktop"
                                   : L"No windows on this desktop")
            : L"No windows match your search";
        DrawTextBlock(message, g_fmtEmpty, g_layout.grid, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_CENTER, 0.55f);
    }

    // Page indicator.
    if (g_layout.pageCount > 1)
    {
        const std::wstring page =
            std::to_wstring(g_page + 1) + L" / " + std::to_wstring(g_layout.pageCount);
        const RectF pageRect = {g_layout.grid.r - 200.0f * s,
                                g_layout.grid.b + 4.0f * s, g_layout.grid.r,
                                g_layout.grid.b + 30.0f * s};
        DrawTextBlock(page, g_fmtHint, pageRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_TRAILING, 0.55f);
    }

    // Desktop strip. The panel is optional so the tabs can float over the
    // desktop, which is the default for the carousel and card wheel.
    if (StripBackgroundVisible())
    {
        FillRound(g_layout.strip, 14.0f * s, g_theme.stripFill, 0.90f);
        StrokeRound(g_layout.strip, 14.0f * s, g_theme.text, 1.0f * s, 0.07f);
    }

    // Farthest tabs first so the centred one stays on top as the wheel turns.
    int drawOrder[64] = {};
    int drawCount = 0;
    for (int i = 0; i < static_cast<int>(g_pills.size()) && drawCount < 64; i++)
        if (g_pills[i].visible)
            drawOrder[drawCount++] = i;
    if (IsWheel())
        std::sort(drawOrder, drawOrder + drawCount, [](int a, int b) {
            return std::fabs(g_pills[a].depth) > std::fabs(g_pills[b].depth);
        });

    for (int order = 0; order < drawCount; order++)
    {
        const int i = drawOrder[order];
        const PillView& pill = g_pills[i];
        if (CardAnimationHidesDesktop(pill.desktop))
            continue;
        const bool active = pill.desktop == g_currentDesktop;
        const bool hovered = g_hoverPill == i;
        const bool selected = g_focusStrip && pill.desktop == g_desktopSelected;

        if (IsWheel())
        {
            const D2D1_POINT_2F centre =
                D2D1::Point2F((pill.rect.l + pill.rect.r) / 2.0f,
                              (pill.rect.t + pill.rect.b) / 2.0f - pill.lift);
            g_d2dTarget->SetTransform(
                D2D1::Matrix3x2F::Scale(pill.scale, pill.scale, centre) *
                D2D1::Matrix3x2F::Rotation(pill.angle, centre));
        }

        if (UsesCards())
        {
            DrawDesktopCard(pill, active, hovered, selected,
                            g_hoverPillClose == i);
            if (IsWheel())
                g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            continue;
        }

        if (UsesChips())
        {
            DrawChipTab(pill, active, hovered, selected, g_hoverPillClose == i);
            if (IsWheel())
                g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            continue;
        }

        const RectF face = {pill.rect.l, pill.rect.t - pill.lift,
                            pill.rect.r, pill.rect.b - pill.lift};
        UINT32 fill = active ? g_theme.pillActive : g_theme.pillFill;
        if (hovered)
            fill = active ? g_theme.pillActiveHover : g_theme.pillHover;

        if (!StripBackgroundVisible() || pill.lift > 0.0f)
        {
            const RectF shadow = {face.l,
                                  face.t + 5.0f * s + pill.lift * 0.25f,
                                  face.r, face.b + 9.0f * s + pill.lift};
            FillRound(shadow, 12.0f * s, 0xFF000000,
                      0.30f * pill.alpha +
                          (pill.lift > 0.0f ? 0.08f : 0.0f));
        }

        FillRound(face, 10.0f * s, fill, pill.alpha);

        if (g_desktopSelection == DesktopSelection::Highlight && selected)
            StrokeRound(face, 10.0f * s, g_theme.accent, 2.0f * s,
                        0.95f * pill.alpha);
        else if (g_desktopSelection == DesktopSelection::Highlight && active)
            StrokeRound(face, 10.0f * s, g_theme.accent, 1.2f * s,
                        0.75f * pill.alpha);
        else
            StrokeRound(face, 10.0f * s, g_theme.text, 1.2f * s,
                        (active ? 0.32f : 0.08f) * pill.alpha);

        const RectF badge = {face.l + 10.0f * s, face.t + 9.0f * s,
                             face.l + 34.0f * s, face.b - 9.0f * s};
        FillRound(badge, 6.0f * s, active ? g_theme.accent : g_theme.text,
                  (active ? 0.9f : 0.12f) * pill.alpha);
        DrawTextBlock(std::to_wstring(pill.desktop + 1), PillFormat(), badge,
                      active ? g_theme.onAccent : g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_CENTER, 0.95f * pill.alpha);

        const bool renaming = g_renameDesktop == pill.desktop;
        const RectF nameRect = {face.l + 40.0f * s, face.t,
                                face.r - (pill.hasClose && !renaming ? 30.0f * s
                                                                    : 12.0f * s),
                                face.b};
        const std::wstring& shownName =
            renaming ? g_renameText : g_desktops[pill.desktop].name;
        DrawTextBlock(shownName, PillFormat(), nameRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING,
                      ((active || renaming) ? 0.95f : 0.72f) * pill.alpha);

        if (renaming && ((GetTickCount64() / 530) % 2) == 0)
        {
            const float textW = MeasureTextWidth(g_renameText, PillFormat());
            const float caretX = std::min(nameRect.r, nameRect.l + textW + 1.0f * s);
            g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.85f * pill.alpha));
            g_d2dTarget->DrawLine(D2D1::Point2F(caretX, face.t + 11.0f * s),
                                  D2D1::Point2F(caretX, face.b - 11.0f * s),
                                  g_d2dBrush, 1.4f * s);
        }

        if (pill.hasClose && !renaming)
        {
            g_d2dBrush->SetColor(ColorOf(
                g_theme.text,
                (g_hoverPillClose == i ? 0.95f : 0.45f) * pill.alpha));
            const float ccx = pill.closeRect.l + pill.closeRect.W() / 2.0f;
            const float ccy = pill.closeRect.t + pill.closeRect.H() / 2.0f;
            const float arm = 4.4f * s;
            g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                                  D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush,
                                  1.4f * s);
            g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                                  D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush,
                                  1.4f * s);
        }

        if (IsWheel())
            g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    // Create-desktop button. Playing-card mode gets a face-down card; chip
    // mode gets a round chip; everything else gets a rounded square.
    if (UsesCards())
    {
        DrawCreateCard(g_createRect, g_hoverCreate, g_createPull);
    }
    else if (UsesChips())
    {
        const float r = g_createRect.W() / 2.0f;
        const float cx = g_createRect.l + g_createRect.W() / 2.0f;
        const float cy = g_createRect.t + g_createRect.H() / 2.0f;
        if (!StripBackgroundVisible())
        {
            FillEllipse(cx, cy + 6.0f * s, r * 1.01f, r * 0.98f, 0xFF000000,
                        0.30f);
        }

        const UINT32 base =
            g_hoverCreate ? g_theme.pillActiveHover : g_theme.pillFill;
        DrawChipBody(cx, cy, r, base, 0.0f, 1.0f);

        const ChipPaint paint = ChipPaintFor(base);
        const float discR = r * 0.58f;
        FillEllipse(cx, cy, discR + 1.4f * s, discR + 1.4f * s, paint.edge,
                    0.55f);
        FillEllipse(cx, cy, discR, discR, paint.inlay, 1.0f);

        g_d2dBrush->SetColor(ColorOf(ChipDiscInk(base), 0.92f));
        const float arm = discR * 0.46f;
        g_d2dTarget->DrawLine(D2D1::Point2F(cx - arm, cy),
                              D2D1::Point2F(cx + arm, cy), g_d2dBrush,
                              1.8f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(cx, cy - arm),
                              D2D1::Point2F(cx, cy + arm), g_d2dBrush,
                              1.8f * s);
    }
    else
    {
        const float createR = 10.0f * s;
        if (!StripBackgroundVisible())
        {
            const RectF shadow = {g_createRect.l, g_createRect.t + 5.0f * s,
                                  g_createRect.r, g_createRect.b + 9.0f * s};
            FillRound(shadow, 12.0f * s, 0xFF000000, 0.30f);
        }
        FillRound(g_createRect, createR,
                  g_hoverCreate ? g_theme.pillActive : g_theme.pillFill, 1.0f);
        StrokeRound(g_createRect, createR, g_theme.text, 1.2f * s, 0.10f);
        g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.80f));
        const float pcx = g_createRect.l + g_createRect.W() / 2.0f;
        const float pcy = g_createRect.t + g_createRect.H() / 2.0f;
        const float arm = 7.0f * s;
        g_d2dTarget->DrawLine(D2D1::Point2F(pcx - arm, pcy),
                              D2D1::Point2F(pcx + arm, pcy), g_d2dBrush,
                              1.6f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(pcx, pcy - arm),
                              D2D1::Point2F(pcx, pcy + arm), g_d2dBrush,
                              1.6f * s);
    }

    DrawCardAnimation();

    // Hint line.
    const RectF hintRect = {56.0f * s, g_layout.strip.b + 10.0f * s,
                            g_layout.w - 56.0f * s, g_layout.strip.b + 34.0f * s};
    std::wstring hint;
    if (IsRenamingDesktop())
        hint = L"Rename desktop  \u00B7  Enter save  \u00B7  Esc cancel";
    else if (g_pendingMove)
        hint = L"Move to desktop 1\u2013" +
               std::to_wstring(std::max<size_t>(g_desktops.size(), 1)) +
               L"  \u00B7  Esc cancel";
    else if (g_focusDock)
        hint = L"Enter switch  \u00B7  U release  \u00B7  Delete close  \u00B7  "
               L"Up/Down select  \u00B7  Tab desktops";
    else if (g_focusStrip)
        hint = L"Enter switch  \u00B7  F2 rename  \u00B7  N new  \u00B7  Delete close  "
               L"\u00B7  Ctrl+Left/Right switch  \u00B7  Tab windows";
    else
        hint = L"Enter switch  \u00B7  Delete close  \u00B7  1-9 desktop  \u00B7  "
               L"Shift+1-9 move  \u00B7  U hold  \u00B7  "
               + std::wstring(DockExists() ? L"Tab dock/desktops" : L"Tab desktops")
               + L"  \u00B7  / search";
    if (g_showHints)
        DrawTextBlock(hint, g_fmtHint, hintRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING, 0.42f);

    // Busy indicator (desktop switching). Suppress it for fast switches, while
    // a card animation is running, and while the overlay is fading out.
    if (g_busy && !g_createAfterDraw &&
        g_cardAnim.mode == CardAnimationMode::None &&
        g_targetPresence > 0.0f && g_busySince != 0 &&
        GetTickCount64() - g_busySince > 500)
    {
        const float pcx = g_layout.w / 2.0f;
        const float pcy = g_layout.h / 2.0f;
        const float phase = static_cast<float>(GetTickCount64() % 900) / 900.0f;
        for (int i = 0; i < 8; i++)
        {
            const float angle = (static_cast<float>(i) / 8.0f) * 6.2831853f;
            const float alpha =
                0.15f + 0.85f * std::fmod(phase + static_cast<float>(i) / 8.0f, 1.0f);
            g_d2dBrush->SetColor(ColorOf(g_theme.accent, alpha));
            const D2D1_ELLIPSE dot = D2D1::Ellipse(
                D2D1::Point2F(pcx + std::cos(angle) * 20.0f * s,
                              pcy + std::sin(angle) * 20.0f * s),
                3.0f * s, 3.0f * s);
            g_d2dTarget->FillEllipse(&dot, g_d2dBrush);
        }
    }

    if (useLayer)
        g_d2dTarget->PopLayer();
    g_d2dTarget->PopAxisAlignedClip();

    if (g_d2dTarget->EndDraw() == static_cast<HRESULT>(0x8899000C))  // D2DERR_RECREATE_TARGET
        ReleaseDeviceResources();

    // The chip thumbnail host and mask sit above the overlay. They are shown
    // only once the open animation is essentially complete, so the square
    // thumbnail corners never peek through during the fade.
    const bool showChipLayers =
        UsesWindowChips() && g_windowChipContent == WindowChipContent::Preview &&
        (!g_busy || g_keepThumbnailsWhileBusy) &&
        contentAlpha > 0.98f && !chipSources.empty();
    if (showChipLayers)
    {
        SetChipLayersVisible(true);
        SyncChipThumbnails(chipSources, chipRects, contentAlpha);
        UpdateChipHostRegion(chipRects);
        if (RenderChipMask(sceneScale, cx, cy))
        {
            // Keep the host directly below the mask and both above the overlay.
            // The overlay is activated by input, which can otherwise reorder the
            // topmost group and hide the live thumbnail behind the chip fill.
            SetWindowPos(g_thumbHost, g_chipMask, g_monitorX, g_monitorY,
                         g_monitorW, g_monitorH,
                         SWP_NOACTIVATE | SWP_SHOWWINDOW);
            SetWindowPos(g_chipMask, HWND_TOPMOST, g_monitorX, g_monitorY,
                         g_monitorW, g_monitorH,
                         SWP_NOACTIVATE | SWP_SHOWWINDOW);
        }
        else
        {
            // Never leave a stale mask above newly positioned thumbnails.
            SetChipLayersVisible(false);
        }
    }
    else
    {
        SetChipLayersVisible(false);
    }
}

////////////////////////////////////////////////////////////////////////////////
// SHOW / HIDE

static void SetControlReady(bool ready)
{
    if (g_control)
        SetWindowTextW(g_control, ready ? kControlTitleReady : kControlTitleIdle);
}

static void StopOverlayTimers()
{
    if (!g_overlay)
        return;
    KillTimer(g_overlay, kTimerFrame);
    KillTimer(g_overlay, kTimerIdle);
    KillTimer(g_overlay, kTimerCaret);
    KillTimer(g_overlay, kTimerDesktop);
    KillTimer(g_overlay, kTimerCarousel);
    g_pendingDesktopTarget = -1;
    g_pendingDesktopTries = 0;
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;
    g_desktopActionCreate = false;
    g_desktopActionClose = false;
    g_desktopActionStartCount = 0;
    g_busySince = 0;
    g_keepThumbnailsWhileBusy = false;
}

static void ForceForeground(HWND hwnd)
{
    HWND foreground = GetForegroundWindow();
    DWORD foregroundThread = foreground ? GetWindowThreadProcessId(foreground, nullptr) : 0;
    DWORD thisThread = GetCurrentThreadId();
    const bool attached = foregroundThread != 0 && foregroundThread != thisThread &&
                          AttachThreadInput(foregroundThread, thisThread, TRUE);

    BringWindowToTop(hwnd);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    if (attached)
        AttachThreadInput(foregroundThread, thisThread, FALSE);
}

static void UpdateMonitorForWindow(HWND window)
{
    HMONITOR monitor = MonitorFromWindow(window ? window : GetForegroundWindow(),
                                         MONITOR_DEFAULTTONEAREST);
    MONITORINFO info = {};
    info.cbSize = sizeof(info);
    if (!monitor || !GetMonitorInfoW(monitor, &info))
    {
        info.rcMonitor.left = 0;
        info.rcMonitor.top = 0;
        info.rcMonitor.right = GetSystemMetrics(SM_CXSCREEN);
        info.rcMonitor.bottom = GetSystemMetrics(SM_CYSCREEN);
    }

    g_monitorX = info.rcMonitor.left;
    g_monitorY = info.rcMonitor.top;
    g_monitorW = info.rcMonitor.right - info.rcMonitor.left;
    g_monitorH = info.rcMonitor.bottom - info.rcMonitor.top;

    UINT dpiX = 96, dpiY = 96;
    HMODULE shcore = GetModuleHandleW(L"shcore.dll");
    typedef HRESULT(WINAPI * GetDpiForMonitorFn)(HMONITOR, int, UINT*, UINT*);
    GetDpiForMonitorFn getDpi = shcore ? reinterpret_cast<GetDpiForMonitorFn>(
        GetProcAddress(shcore, "GetDpiForMonitor")) : nullptr;
    if (getDpi && SUCCEEDED(getDpi(monitor, 0 /* MDT_EFFECTIVE_DPI */, &dpiX, &dpiY)) &&
        dpiX > 0)
        g_dpi = dpiX;
    else
        g_dpi = 96;

    g_scale = static_cast<float>(g_dpi) / 96.0f;
}

struct AccentPolicy
{
    int state;
    int flags;
    DWORD gradientColor;
    int animationId;
};

struct WindowCompositionAttributeData
{
    int attribute;
    void* data;
    SIZE_T sizeOfData;
};

static bool SetAccentPolicy(HWND hwnd, int state, int flags, DWORD gradientColor)
{
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    typedef BOOL(WINAPI * SetWindowCompositionAttributeFn)(HWND,
                                                           WindowCompositionAttributeData*);
    SetWindowCompositionAttributeFn setComposition = user32
        ? reinterpret_cast<SetWindowCompositionAttributeFn>(
              GetProcAddress(user32, "SetWindowCompositionAttribute"))
        : nullptr;
    if (!setComposition)
        return false;

    AccentPolicy policy = {};
    policy.state = state;
    policy.flags = flags;
    policy.gradientColor = gradientColor;
    WindowCompositionAttributeData data = {};
    data.attribute = 19;  // WCA_ACCENT_POLICY
    data.data = &policy;
    data.sizeOfData = sizeof(policy);
    return setComposition(hwnd, &data) != FALSE;
}

// DWM only paints the system backdrop on windows it considers active, so nudge
// it after the window is shown.
static void TriggerWindowNCRendering(HWND hwnd)
{
    DefWindowProcW(hwnd, WM_NCACTIVATE, TRUE, 0);
}

// Applies the configured backdrop effect.
//
// Measured on Windows 11 build 26300 against a real fullscreen overlay:
//
//  * DWMWA_SYSTEMBACKDROP_TYPE = DWMSBT_TRANSIENTWINDOW (3) on its own paints a
//    flat, dark fill that shows no trace of what is behind the window.
//  * The legacy accent policy does render the blur. Its gradient colour is the
//    tint, so a fully transparent one (0x00000000) gives a clean blur with no
//    tint of its own. An opaque gradient colour is what makes it come out as an
//    exact solid fill, which is why the accent was previously written off as
//    broken.
//  * The accent only takes effect when it is applied while the window is still
//    hidden. Applying it after the window is on screen leaves the flat fill.
//  * DWMSBT_MAINWINDOW (2) and DWMSBT_TABBEDWINDOW (4) do work, but they are
//    opaque, wallpaper-derived materials, so Mica and Mica Alt use them.
//  * DwmEnableBlurBehindWindow has no visible effect.
//
// The OS only supplies the material; the Direct2D scrim supplies the color and
// opacity for every mode through one linear control.
static void ApplyBackdrop(HWND hwnd)
{
    MARGINS margins = {-1, -1, -1, -1};
    g_glass = SUCCEEDED(DwmExtendFrameIntoClientArea(hwnd, &margins));

    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    DWORD corner = 1 /* DWMWCP_DONOTROUND */;
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner,
                          sizeof(corner));
    DWORD border = 0xFFFFFFFE /* DWMWA_COLOR_NONE */;
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &border, sizeof(border));

    // Reset any previously applied effect before applying the configured one.
    DWORD noBackdrop = 1 /* DWMSBT_NONE */;
    DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &noBackdrop,
                          sizeof(noBackdrop));
    BOOL micaDisabled = FALSE;
    DwmSetWindowAttribute(hwnd, 1029 /* DWMWA_MICA_EFFECT */, &micaDisabled,
                          sizeof(micaDisabled));
    SetAccentPolicy(hwnd, 0 /* ACCENT_DISABLED */, 0, 0);

    bool accentOk = false;
    HRESULT backdropHr = E_FAIL;
    DWORD sysType = 1 /* DWMSBT_NONE */;

    switch (g_backgroundMode)
    {
    case BackgroundMode::Acrylic:
    {
        // DWM's transient-window material plus the untinted accent blur, which
        // is what actually blurs the desktop (see the note above).
        sysType = 3 /* DWMSBT_TRANSIENTWINDOW (Windows 11 acrylic) */;
        backdropHr = DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &sysType,
                                           sizeof(sysType));
        accentOk = SetAccentPolicy(hwnd, 4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 0,
                                   0x00000000);
        TriggerWindowNCRendering(hwnd);
        break;
    }
    case BackgroundMode::Blur:
    {
        // Plain blur: the accent on its own, without DWM's tinted material.
        accentOk = SetAccentPolicy(hwnd, 3 /* ACCENT_ENABLE_BLURBEHIND */, 0, 0x00000000);
        TriggerWindowNCRendering(hwnd);
        break;
    }
    case BackgroundMode::Mica:
    case BackgroundMode::MicaAlt:
    {
        sysType = g_backgroundMode == BackgroundMode::Mica
                      ? 2 /* DWMSBT_MAINWINDOW */
                      : 4 /* DWMSBT_TABBEDWINDOW (Mica Alt) */;
        backdropHr = DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &sysType,
                                           sizeof(sysType));
        TriggerWindowNCRendering(hwnd);
        break;
    }
    case BackgroundMode::Solid:
    case BackgroundMode::None:
        break;
    }

    Wh_Log(L"Backdrop applied: mode=%d sysType=%lu opacity=%.2f color=0x%08X glass=%d "
           L"scrim=%.2f accent=%d backdropHr=0x%08lX",
           static_cast<int>(g_backgroundMode), static_cast<unsigned long>(sysType),
           g_backgroundOpacity, g_theme.background, g_glass ? 1 : 0, BackgroundScrimAlpha(),
           accentOk ? 1 : 0, static_cast<unsigned long>(backdropHr));
}

// Opacity (0..1) of the color scrim drawn over the OS backdrop. The scrim is
// what the "Background opacity" setting controls, so it applies to every mode:
// at 0 the acrylic blur shows through untouched, at 1 the panel is solid.
static float BackgroundScrimAlpha()
{
    if (!g_glass)
        return 0.94f;  // Without glass a low alpha would expose the desktop raw.

    switch (g_backgroundMode)
    {
    case BackgroundMode::Solid:
        return 1.0f;
    case BackgroundMode::Acrylic:
    case BackgroundMode::Blur:
    case BackgroundMode::Mica:
    case BackgroundMode::MicaAlt:
    case BackgroundMode::None:
    default:
        return std::max(0.0f, std::min(1.0f, g_backgroundOpacity));
    }
}

static void ShowOverlay()
{
    if (!g_overlay || g_visible)
        return;

    if (!g_closingForActivation)
        g_originWindow = GetForegroundWindow();
    if (g_originWindow == g_overlay)
        g_originWindow = nullptr;

    UpdateMonitorForWindow(g_originWindow);
    ApplyBackdrop(g_overlay);

    // Reset transient UI state *before* rebuilding: RebuildWindowList() filters
    // the window list with the current g_search, so clearing it afterwards
    // would keep showing results for the previous query.
    g_selected = 0;
    g_page = 0;
    g_focusStrip = false;
    g_focusDock = false;
    g_dockSelected = 0;
    g_search.clear();
    g_searchFocused = false;
    g_searchSelectAll = false;
    g_searchAllDesktops = false;
    g_renameDesktop = -1;
    g_renameText.clear();
    g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
    g_hoverDock = g_hoverDockClose = -1;
    g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;
    g_createDragging = false;
    g_createPull = 0.0f;
    g_busy = false;
    g_busySince = 0;
    g_desktopActionCreate = false;
    g_desktopActionClose = false;
    g_desktopActionStartCount = 0;
    g_pendingDesktopTarget = -1;
    g_pendingDesktopTries = 0;
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;
    g_keepThumbnailsWhileBusy = false;
    g_pendingMove = false;

    RefreshDesktops();
    RebuildWindowList();
    g_desktopSelected = g_currentDesktop;
    g_carouselPos = static_cast<float>(g_currentDesktop);
    if (g_overlay)
        KillTimer(g_overlay, kTimerCarousel);

    g_presence = 0.0f;
    g_targetPresence = 1.0f;
    g_lastFrameTick = GetTickCount64();
    g_visible = true;
    g_shownAtTick = GetTickCount64();

    UpdateLayout();

    SetWindowPos(g_overlay, HWND_TOPMOST, g_monitorX, g_monitorY, g_monitorW, g_monitorH,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW);
    ForceForeground(g_overlay);

    SetTimer(g_overlay, kTimerFrame, 16, nullptr);
    SetTimer(g_overlay, kTimerIdle, 700, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void FinishHide()
{
    SetChipLayersVisible(false);
    ReleaseThumbnails();
    StopOverlayTimers();
    if (g_overlay)
        ShowWindow(g_overlay, SW_HIDE);
    g_visible = false;
    g_presence = 0.0f;
    g_targetPresence = 0.0f;
    g_busy = false;
    g_pendingMove = false;
    g_focusDock = false;
    g_searchAllDesktops = false;
    g_pendingDesktopTarget = -1;
    g_pendingDesktopTries = 0;
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;
    ClearCardAnimation();
    SetControlReady(true);
}

static void HideOverlay(bool immediate)
{
    if (!g_visible)
        return;

    // A hide cancels a pending cross-desktop activation; the timer path copies
    // the target before calling this when it is about to activate it.
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;

    if (g_createDragging)
    {
        g_createDragging = false;
        g_createPull = 0.0f;
        if (GetCapture() == g_overlay)
            ReleaseCapture();
    }

    if (immediate)
    {
        g_presence = 0.0f;
        g_targetPresence = 0.0f;
        FinishHide();
        if (!g_closingForActivation && g_originWindow && IsWindow(g_originWindow))
            SetForegroundWindow(g_originWindow);
        return;
    }

    g_targetPresence = 0.0f;
    SetTimer(g_overlay, kTimerFrame, 16, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void ToggleOverlay()
{
    if (g_visible)
        HideOverlay(false);
    else
        ShowOverlay();
}

////////////////////////////////////////////////////////////////////////////////
// ACTIONS

static void ActivateWindowEntry(int entry)
{
    if (entry < 0 || entry >= static_cast<int>(g_windows.size()))
        return;
    HWND target = g_windows[entry].hwnd;
    if (!target || !IsWindow(target))
        return;

    // The window may have moved since the list was built, so resolve its
    // desktop again. A result from another desktop switches there first and
    // lets kTimerDesktop finish the activation once the shell has landed.
    if (g_vdm)
    {
        GUID id = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(target, &id)))
        {
            const int desktopIndex = DesktopIndexForId(id);
            if (desktopIndex >= 0 && desktopIndex != g_currentDesktop &&
                !IsWindowOnCurrentDesktop(target))
            {
                if (g_busy)
                    return;
                g_pendingActivateWindow = target;
                g_pendingActivateDesktop = desktopIndex;
                g_desktopSelected = desktopIndex;
                BeginDesktopAction(desktopIndex, false, false);
                return;
            }
        }
    }

    g_closingForActivation = true;
    HideOverlay(true);
    g_closingForActivation = false;

    if (IsIconic(target))
        ShowWindow(target, SW_RESTORE);

    if (!SetForegroundWindow(target))
        SwitchToThisWindow(target, TRUE);
}

static void ActivateEntry(int filteredIndex)
{
    if (filteredIndex < 0 || filteredIndex >= static_cast<int>(g_filtered.size()))
        return;
    ActivateWindowEntry(g_filtered[filteredIndex]);
}

static void CloseWindowEntry(int entry)
{
    if (entry < 0 || entry >= static_cast<int>(g_windows.size()))
        return;
    HWND target = g_windows[entry].hwnd;
    if (!target || !IsWindow(target))
        return;

    PostMessageW(target, WM_CLOSE, 0, 0);

    // Remove the entry immediately and keep the overlay open.
    SetChipLayersVisible(false);
    ReleaseThumbnails();
    g_windows.erase(g_windows.begin() + entry);
    RebuildFilter();
    if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = g_filtered.empty() ? -1 : static_cast<int>(g_filtered.size()) - 1;
    // The dock list is rebuilt on the next layout; drop the cursor now so it
    // cannot act on the entry that was just removed.
    if (g_focusDock)
    {
        g_focusDock = false;
        g_dockSelected = 0;
    }
    g_hoverCard = g_hoverClose = g_hoverDock = g_hoverDockClose = -1;

    if (g_overlay)
        SetTimer(g_overlay, kTimerIdle, 700, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void CloseEntry(int filteredIndex)
{
    if (filteredIndex < 0 || filteredIndex >= static_cast<int>(g_filtered.size()))
        return;
    CloseWindowEntry(g_filtered[filteredIndex]);
}

static void MoveSelection(int dx, int dy)
{
    RebuildDisplayList();
    const int count = static_cast<int>(g_display.size());
    if (count == 0)
        return;

    const int cols = std::max(1, g_layout.cols);
    int index = DisplayPosition(g_selected);
    if (index < 0)
        index = 0;

    if (dx != 0)
    {
        index += dx;
        if (index < 0)
            index = g_wrapNavigation ? count - 1 : 0;
        if (index >= count)
            index = g_wrapNavigation ? 0 : count - 1;
    }
    else if (dy != 0)
    {
        const int previous = index;
        index += dy * cols;
        if (index < 0 || index >= count)
        {
            if (!g_wrapNavigation)
                index = previous;
        }
    }

    index = std::max(0, std::min(count - 1, index));
    g_selected = g_display[index];
    g_page = index / std::max(1, g_layout.perPage);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void SetSearch(const std::wstring& text)
{
    g_search = text;
    g_searchSelectAll = false;
    RebuildFilter();
    g_selected = 0;
    RebuildDisplayList();
    if (!g_display.empty())
        g_selected = g_display.front();
    g_page = 0;
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void SetSearchAllDesktops(bool all)
{
    if (g_searchAllDesktops == all || g_busy)
        return;

    g_searchAllDesktops = all;
    SetChipLayersVisible(false);
    ReleaseThumbnails();
    RebuildWindowList();
    g_selected = 0;
    RebuildDisplayList();
    g_selected = g_display.empty() ? -1 : g_display.front();
    g_page = 0;
    g_hoverCard = g_hoverClose = g_hoverDock = g_hoverDockClose = -1;
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void ExitSearch()
{
    const bool hadAllDesktops = g_searchAllDesktops;
    // Leaving all-desktop mode re-enumerates the window list; defer that while a
    // desktop action is in flight. Current-desktop search can still be cleared.
    if (g_busy && hadAllDesktops)
        return;

    g_searchFocused = false;
    g_searchSelectAll = false;
    g_search.clear();
    g_searchAllDesktops = false;

    if (hadAllDesktops)
    {
        SetChipLayersVisible(false);
        ReleaseThumbnails();
        RebuildWindowList();
    }
    else
    {
        RebuildFilter();
    }

    g_selected = 0;
    RebuildDisplayList();
    g_selected = g_display.empty() ? -1 : g_display.front();
    g_page = 0;
    g_hoverCard = g_hoverClose = g_hoverDock = g_hoverDockClose = -1;
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void FocusSearch()
{
    g_searchFocused = true;
    // Focusing a field that already has a query selects it, so the next typed
    // character replaces the old query instead of appending to it.
    g_searchSelectAll = !g_search.empty();
    g_focusStrip = false;
    g_focusDock = false;
    if (g_overlay)
        SetTimer(g_overlay, kTimerCaret, 530, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

////////////////////////////////////////////////////////////////////////////////
// INPUT

static void UpdateHover(int x, int y)
{
    g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
    g_hoverDock = g_hoverDockClose = -1;
    g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;

    if (SearchVisible() &&
        Contains(g_layout.search, static_cast<float>(x), static_cast<float>(y)))
        g_hoverSearch = true;
    if (!g_search.empty() &&
        Contains(g_searchClearRect, static_cast<float>(x), static_cast<float>(y)))
        g_hoverSearchClear = true;

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        const CardView& card = g_cards[i];
        if (Contains(card.hit, static_cast<float>(x), static_cast<float>(y)) ||
            Contains(card.rect, static_cast<float>(x), static_cast<float>(y)))
        {
            g_hoverCard = i;
            if (Contains(card.close, static_cast<float>(x), static_cast<float>(y)))
                g_hoverClose = i;
            break;
        }
    }

    for (int i = 0; i < static_cast<int>(g_dockCards.size()); i++)
    {
        const CardView& card = g_dockCards[i];
        if (Contains(card.hit, static_cast<float>(x), static_cast<float>(y)) ||
            Contains(card.rect, static_cast<float>(x), static_cast<float>(y)))
        {
            g_hoverDock = i;
            if (Contains(card.close, static_cast<float>(x),
                         static_cast<float>(y)))
                g_hoverDockClose = i;
            break;
        }
    }

    const int pillIndex = PillAt(static_cast<float>(x), static_cast<float>(y));
    if (pillIndex >= 0)
    {
        g_hoverPill = pillIndex;
        const PillView& pill = g_pills[pillIndex];
        if (pill.hasClose &&
            Contains(pill.closeHit, static_cast<float>(x), static_cast<float>(y)))
            g_hoverPillClose = pillIndex;
    }

    if (Contains(g_createRect, static_cast<float>(x), static_cast<float>(y)))
        g_hoverCreate = true;
}

static void OnLeftClick(int x, int y)
{
    if (g_createAfterDraw)
        return;

    const float fx = static_cast<float>(x);
    const float fy = static_cast<float>(y);

    if (IsRenamingDesktop())
    {
        const int pillIndex = PillAt(fx, fy);
        if (pillIndex >= 0 && g_pills[pillIndex].desktop == g_renameDesktop)
            return;  // Clicking the field keeps editing.
        CommitRenameDesktop();
        return;
    }

    if (!g_search.empty() && Contains(g_searchClearRect, fx, fy))
    {
        SetSearch(L"");
        FocusSearch();
        return;
    }

    if (Contains(g_layout.search, fx, fy))
    {
        FocusSearch();
        return;
    }

    // Clicking anywhere else takes the field out of focus, so the letter keys
    // go back to navigation; all-desktop mode stays active until Esc or '/'.
    if (g_searchFocused)
    {
        g_searchFocused = false;
        g_searchSelectAll = false;
        InvalidateRect(g_overlay, nullptr, FALSE);
    }
    g_focusDock = false;

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        const CardView& card = g_cards[i];
        if (!Contains(card.hit, fx, fy) && !Contains(card.rect, fx, fy))
            continue;
        if (Contains(card.close, fx, fy))
            CloseEntry(card.filtered);
        else
        {
            g_selected = card.filtered;
            ActivateEntry(card.filtered);
        }
        return;
    }

    for (int i = 0; i < static_cast<int>(g_dockCards.size()); i++)
    {
        const CardView& card = g_dockCards[i];
        if (!Contains(card.hit, fx, fy) && !Contains(card.rect, fx, fy))
            continue;
        if (Contains(card.close, fx, fy))
            CloseWindowEntry(card.entry);
        else
        {
            if (card.filtered >= 0)
                g_selected = card.filtered;
            ActivateWindowEntry(card.entry);
        }
        return;
    }

    const int pillIndex = PillAt(fx, fy);
    if (pillIndex >= 0)
    {
        const PillView& pill = g_pills[pillIndex];
        if (pill.hasClose && Contains(pill.closeHit, fx, fy))
        {
            BeginDesktopAction(-1, false, true);
            return;
        }

        g_focusDock = false;
        g_focusStrip = true;
        g_desktopSelected = pill.desktop;
        if (pill.desktop != g_currentDesktop)
            BeginDesktopAction(pill.desktop, false, false);
        else
        {
            KickCarousel();
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        return;
    }

    if (Contains(g_createRect, fx, fy))
    {
        BeginDesktopAction(-1, true, false);
        return;
    }
}

static bool DockExists()
{
    return !g_dockCards.empty();
}

static void MoveDockSelection(int delta)
{
    const int count = static_cast<int>(g_dockCards.size());
    if (count <= 0)
    {
        g_focusDock = false;
        g_dockSelected = 0;
        InvalidateRect(g_overlay, nullptr, FALSE);
        return;
    }

    int next = g_dockSelected + delta;
    if (g_wrapNavigation)
        next = ((next % count) + count) % count;
    else
        next = std::max(0, std::min(count - 1, next));
    if (next == g_dockSelected)
        return;

    g_dockSelected = next;
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void ActivateDockSelection()
{
    if (!g_focusDock || g_dockSelected < 0 ||
        g_dockSelected >= static_cast<int>(g_dockCards.size()))
        return;
    ActivateWindowEntry(g_dockCards[g_dockSelected].entry);
}

static void CloseDockSelection()
{
    if (!g_focusDock || g_dockSelected < 0 ||
        g_dockSelected >= static_cast<int>(g_dockCards.size()))
        return;
    CloseWindowEntry(g_dockCards[g_dockSelected].entry);
}

// Tab cycles grid -> held dock -> desktop strip -> grid. The dock stage is
// skipped when no held windows are docked, which keeps the original two-stage
// behaviour for users who leave the dock off.
static void CycleFocus()
{
    if (DockExists())
    {
        if (!g_focusStrip && !g_focusDock)
        {
            g_focusDock = true;
            g_focusStrip = false;
            g_dockSelected = std::max(
                0, std::min(g_dockSelected,
                            static_cast<int>(g_dockCards.size()) - 1));
        }
        else if (g_focusDock)
        {
            g_focusDock = false;
            g_focusStrip = true;
            g_desktopSelected = g_currentDesktop;
        }
        else
        {
            g_focusStrip = false;
            g_focusDock = false;
            if (g_selected < 0 && !g_display.empty())
                g_selected = g_display.front();
        }
    }
    else
    {
        g_focusDock = false;
        g_focusStrip = !g_focusStrip;
        if (g_focusStrip)
            g_desktopSelected = g_currentDesktop;
    }

    KickCarousel();
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void MoveStripSelection(int delta)
{
    const int count = static_cast<int>(g_desktops.size());
    if (count <= 0)
        return;

    int next = g_desktopSelected + delta;
    if (g_wrapDesktopStrip)
        next = ((next % count) + count) % count;
    else
        next = std::max(0, std::min(count - 1, next));

    if (next == g_desktopSelected)
        return;

    g_desktopSelected = next;
    KickCarousel();
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void OnKeyDown(WPARAM key)
{
    // The pre-create card draw owns the keyboard briefly. Escape cancels it;
    // every other key is ignored so the pending desktop is not lost mid-flight.
    if (g_createAfterDraw)
    {
        if (key == VK_ESCAPE)
        {
            g_createAfterDraw = false;
            ClearCardAnimation();
            HideOverlay(false);
        }
        return;
    }

    if (IsRenamingDesktop())
    {
        if (key == VK_RETURN)
            CommitRenameDesktop();
        else if (key == VK_ESCAPE)
            CancelRenameDesktop();
        else if (key == VK_BACK)
        {
            if (!g_renameText.empty())
                g_renameText.pop_back();
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        // Everything else is ignored; printable input arrives via WM_CHAR.
        return;
    }

    // A desktop number follows m; anything else cancels the pending move.
    if (g_pendingMove)
    {
        if (key == VK_ESCAPE)
        {
            g_pendingMove = false;
            InvalidateRect(g_overlay, nullptr, FALSE);
            return;
        }
        if ((key >= '1' && key <= '9') || (key >= VK_NUMPAD1 && key <= VK_NUMPAD9))
        {
            const int index = key >= VK_NUMPAD1 ? static_cast<int>(key - VK_NUMPAD1)
                                                : static_cast<int>(key - '1');
            g_pendingMove = false;
            MoveSelectedWindowToDesktopIndex(index);
            InvalidateRect(g_overlay, nullptr, FALSE);
            return;
        }
        g_pendingMove = false;
        InvalidateRect(g_overlay, nullptr, FALSE);
    }

    const bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    const bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;

    // While the search field has focus, only editing keys are meaningful; this
    // keeps Delete/arrows/etc. from triggering actions mid-query.
    if (g_searchFocused)
    {
        if (key == VK_ESCAPE)
        {
            ExitSearch();
        }
        else if (key == VK_RETURN)
        {
            ActivateEntry(g_selected);
        }
        else if (key == VK_BACK)
        {
            if (g_searchSelectAll)
                SetSearch(L"");
            else if (!g_search.empty())
                SetSearch(g_search.substr(0, g_search.size() - 1));
        }
        else if (g_searchSelectAll &&
                 (key == VK_DELETE || key == VK_LEFT || key == VK_RIGHT ||
                  key == VK_HOME || key == VK_END))
        {
            // The selection goes away as soon as the user reaches for the
            // caret; there is no caret movement to model in this field.
            g_searchSelectAll = false;
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        return;
    }

    // Bare 1-9 jump to that desktop; Shift+1-9 move the selected window there.
    if ((key >= '1' && key <= '9') || (key >= VK_NUMPAD1 && key <= VK_NUMPAD9))
    {
        const int index = key >= VK_NUMPAD1 ? static_cast<int>(key - VK_NUMPAD1)
                                            : static_cast<int>(key - '1');
        if (index >= 0 && index < static_cast<int>(g_desktops.size()))
        {
            if (shift)
            {
                MoveSelectedWindowToDesktopIndex(index);
            }
            else if (index != g_currentDesktop)
            {
                g_desktopSelected = index;
                BeginDesktopAction(index, false, false);
            }
        }
        return;
    }

    switch (key)
    {
    case VK_ESCAPE:
        if (g_focusDock)
        {
            g_focusDock = false;
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        else if (g_searchFocused || !g_search.empty() || g_searchAllDesktops)
        {
            ExitSearch();
        }
        else
        {
            HideOverlay(false);
        }
        return;

    case VK_RETURN:
        if (g_focusStrip)
        {
            if (g_desktopSelected != g_currentDesktop)
                BeginDesktopAction(g_desktopSelected, false, false);
            else
                HideOverlay(false);
        }
        else if (g_focusDock)
        {
            ActivateDockSelection();
        }
        else
        {
            ActivateEntry(g_selected);
        }
        return;

    case VK_DELETE:
        if (g_focusStrip)
            BeginDesktopAction(-1, false, true);
        else if (g_focusDock)
            CloseDockSelection();
        else
            CloseEntry(g_selected);
        return;

    case VK_F2:
        BeginRenameDesktop(g_focusStrip ? g_desktopSelected : g_currentDesktop);
        return;

    case VK_TAB:
        CycleFocus();
        return;

    case VK_BACK:
        if (!g_search.empty())
            SetSearch(g_search.substr(0, g_search.size() - 1));
        return;

    case VK_LEFT:
        if (shift && !g_focusStrip)
        {
            MoveSelectedWindowToDesktop(-1);
            return;
        }
        if (ctrl)
        {
            SwitchDesktopBy(-1);
            return;
        }
        if (g_focusStrip)
        {
            MoveStripSelection(-1);
        }
        else if (g_focusDock)
        {
            MoveDockSelection(-1);
        }
        else
        {
            MoveSelection(-1, 0);
        }
        return;

    case VK_RIGHT:
        if (shift && !g_focusStrip)
        {
            MoveSelectedWindowToDesktop(1);
            return;
        }
        if (ctrl)
        {
            SwitchDesktopBy(1);
            return;
        }
        if (g_focusStrip)
        {
            MoveStripSelection(1);
        }
        else if (g_focusDock)
        {
            MoveDockSelection(1);
        }
        else
        {
            MoveSelection(1, 0);
        }
        return;

    case VK_UP:
        if (g_focusDock)
            MoveDockSelection(-1);
        else if (!g_focusStrip)
            MoveSelection(0, -1);
        return;

    case VK_DOWN:
        if (g_focusDock)
            MoveDockSelection(1);
        else if (!g_focusStrip)
            MoveSelection(0, 1);
        return;

    case VK_NEXT:
        g_page = std::min(g_layout.pageCount - 1, g_page + 1);
        InvalidateRect(g_overlay, nullptr, FALSE);
        return;

    case VK_PRIOR:
        g_page = std::max(0, g_page - 1);
        InvalidateRect(g_overlay, nullptr, FALSE);
        return;

    case 'N':
    case VK_INSERT:
        if (g_focusStrip)
            BeginDesktopAction(-1, true, false);
        return;

    case 'U':
        if (!g_focusStrip)
        {
            if (g_focusDock && g_dockSelected >= 0 &&
                g_dockSelected < static_cast<int>(g_dockCards.size()))
            {
                const int entry = g_dockCards[g_dockSelected].entry;
                if (entry >= 0 && entry < static_cast<int>(g_windows.size()))
                    ToggleHoldWindow(g_windows[entry].hwnd);
            }
            else if (g_hoverDock >= 0 &&
                     g_hoverDock < static_cast<int>(g_dockCards.size()))
            {
                const int entry = g_dockCards[g_hoverDock].entry;
                if (entry >= 0 && entry < static_cast<int>(g_windows.size()))
                    ToggleHoldWindow(g_windows[entry].hwnd);
            }
            else
            {
                ToggleHold();
            }
        }
        return;

    case 'M':
        if (!g_focusStrip)
        {
            g_pendingMove = true;
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        return;

    default:
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////
// WINDOW PROCEDURES

static LRESULT CALLBACK ChipLayerWndProc(HWND hwnd, UINT message, WPARAM wParam,
                                         LPARAM lParam)
{
    switch (message)
    {
    case WM_NCHITTEST:
        return HTTRANSPARENT;

    case WM_MOUSEACTIVATE:
        return MA_NOACTIVATE;

    case WM_ERASEBKGND:
        if (hwnd == g_thumbHost && wParam)
        {
            RECT rc = {};
            GetClientRect(hwnd, &rc);
            FillRect(reinterpret_cast<HDC>(wParam), &rc,
                     reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
        }
        return 1;

    case WM_PAINT:
        if (hwnd == g_thumbHost)
        {
            PAINTSTRUCT ps = {};
            HDC dc = BeginPaint(hwnd, &ps);
            RECT rc = {};
            GetClientRect(hwnd, &rc);
            FillRect(dc, &rc,
                     reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
            EndPaint(hwnd, &ps);
        }
        else
        {
            // The layered mask is painted with UpdateLayeredWindow(), but the
            // update region still has to be validated or WM_PAINT repeats.
            PAINTSTRUCT ps = {};
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        return 0;

    default:
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }
}

static LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT message, WPARAM wParam,
                                       LPARAM lParam)
{
    switch (message)
    {
    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
    {
        PAINTSTRUCT ps = {};
        HDC dc = BeginPaint(hwnd, &ps);
        RenderScene(dc);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_LBUTTONDOWN:
    {
        if (g_createAfterDraw)
            return 0;
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        if (UsesCards() &&
            Contains(g_createRect, static_cast<float>(x), static_cast<float>(y)))
        {
            g_createDragging = true;
            g_createDragStart = {x, y};
            g_createPull = 0.0f;
            SetCapture(hwnd);
            return 0;
        }
        return 0;
    }

    case WM_MOUSEMOVE:
    {
        if (!g_trackingMouse)
        {
            TRACKMOUSEEVENT track = {sizeof(track)};
            track.dwFlags = TME_LEAVE;
            track.hwndTrack = hwnd;
            TrackMouseEvent(&track);
            g_trackingMouse = true;
        }

        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        if (g_createDragging)
        {
            const float dy = static_cast<float>(
                std::max(0, static_cast<int>(y - g_createDragStart.y)));
            g_createPull = std::min(1.0f, dy / (70.0f * g_scale));
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }

        UpdateHover(x, y);
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

    case WM_MOUSELEAVE:
        g_trackingMouse = false;
        g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
        g_hoverDock = g_hoverDockClose = -1;
        g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_CAPTURECHANGED:
        g_createDragging = false;
        g_createPull = 0.0f;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_LBUTTONUP:
    {
        if (g_createAfterDraw)
            return 0;
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        if (g_createDragging)
        {
            const bool pulled = g_createPull >= 0.45f;
            const bool inside =
                Contains(g_createRect, static_cast<float>(x), static_cast<float>(y));
            g_createDragging = false;
            g_createPull = 0.0f;
            if (GetCapture() == hwnd)
                ReleaseCapture();
            InvalidateRect(hwnd, nullptr, FALSE);
            if (pulled || inside)
                BeginDesktopAction(-1, true, false);
            return 0;
        }
        UpdateHover(x, y);
        OnLeftClick(x, y);
        return 0;
    }

    case WM_RBUTTONUP:
    {
        if (g_createAfterDraw)
            return 0;
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        const float fx = static_cast<float>(x);
        const float fy = static_cast<float>(y);

        if (IsRenamingDesktop())
        {
            const int pillIndex = PillAt(fx, fy);
            if (pillIndex >= 0 && g_pills[pillIndex].desktop == g_renameDesktop)
                return 0;  // Already editing this desktop.
            CommitRenameDesktop();
        }

        // Right-clicking a window card or dock item toggles its held state
        // without activating it. Desktop pills keep their rename gesture.
        for (const CardView& card : g_cards)
        {
            if (!Contains(card.hit, fx, fy) && !Contains(card.rect, fx, fy))
                continue;
            if (card.filtered >= 0)
                g_selected = card.filtered;
            if (card.entry >= 0 &&
                card.entry < static_cast<int>(g_windows.size()))
                ToggleHoldWindow(g_windows[card.entry].hwnd);
            return 0;
        }

        for (const CardView& card : g_dockCards)
        {
            if (!Contains(card.hit, fx, fy) && !Contains(card.rect, fx, fy))
                continue;
            if (card.filtered >= 0)
                g_selected = card.filtered;
            if (card.entry >= 0 &&
                card.entry < static_cast<int>(g_windows.size()))
                ToggleHoldWindow(g_windows[card.entry].hwnd);
            return 0;
        }

        const int pillIndex = PillAt(fx, fy);
        if (pillIndex >= 0)
            BeginRenameDesktop(g_pills[pillIndex].desktop);
        return 0;
    }

    case WM_MBUTTONUP:
    {
        if (g_createAfterDraw)
            return 0;
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        for (const CardView& card : g_cards)
        {
            if (Contains(card.hit, static_cast<float>(x), static_cast<float>(y)) ||
                Contains(card.rect, static_cast<float>(x), static_cast<float>(y)))
            {
                CloseEntry(card.filtered);
                break;
            }
        }
        for (const CardView& card : g_dockCards)
        {
            if (Contains(card.hit, static_cast<float>(x), static_cast<float>(y)) ||
                Contains(card.rect, static_cast<float>(x), static_cast<float>(y)))
            {
                CloseWindowEntry(card.entry);
                break;
            }
        }
        return 0;
    }

    case WM_MOUSEWHEEL:
    {
        if (g_createAfterDraw)
            return 0;
        const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta < 0)
            g_page = std::min(g_layout.pageCount - 1, g_page + 1);
        else
            g_page = std::max(0, g_page - 1);
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

    case WM_SETCURSOR:
    {
        // Text cursor over the search field and over a desktop being renamed.
        POINT pt = {};
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);
        const float fx = static_cast<float>(pt.x);
        const float fy = static_cast<float>(pt.y);

        bool overText =
            SearchVisible() && Contains(g_layout.search, fx, fy) && !g_search.empty();
        if (!overText && IsRenamingDesktop())
        {
            const int pillIndex = PillAt(fx, fy);
            if (pillIndex >= 0 && g_pills[pillIndex].desktop == g_renameDesktop)
                overText = true;
        }

        const bool interactive = g_hoverCard >= 0 || g_hoverPill >= 0 ||
                                 g_hoverDock >= 0 || g_hoverCreate ||
                                 g_hoverSearch || g_hoverClose >= 0 ||
                                 g_hoverDockClose >= 0 ||
                                 g_hoverPillClose >= 0 || g_hoverSearchClear;
        SetCursor(LoadCursorW(nullptr, overText ? IDC_IBEAM
                                                : (interactive ? IDC_HAND : IDC_ARROW)));
        return TRUE;
    }

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        OnKeyDown(wParam);
        return 0;

    case WM_CHAR:
    {
        if (g_createAfterDraw)
            return 0;
        const WCHAR ch = static_cast<WCHAR>(wParam);
        if (ch < 32 || ch == 127)
            return 0;

        if (IsRenamingDesktop())
        {
            if (g_renameText.size() < 48)
                g_renameText.push_back(ch);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }

        // The search field has to be focused first (click it, press '/' for the
        // current desktop, or '?' for every desktop); until then, printable keys
        // are available to navigation commands only.
        if (!g_searchFocused)
        {
            // Shift+/ produces '?' on most layouts. '/' searches the current
            // desktop; '?' switches the same field to every virtual desktop.
            const bool shiftDown = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
            if (ch == L'?' || (ch == L'/' && shiftDown))
            {
                // Switching modes re-enumerates the window list, which must wait
                // for an in-flight desktop action to finish.
                if (g_busy)
                    return 0;
                SetSearchAllDesktops(true);
                FocusSearch();
                return 0;
            }

            if (ch == L'/')
            {
                if (g_busy && g_searchAllDesktops)
                    return 0;
                SetSearchAllDesktops(false);
                FocusSearch();
                return 0;
            }

            if (!g_vimNavigation)
                return 0;

            WCHAR lower = ch;
            if (lower >= L'A' && lower <= L'Z')
                lower = static_cast<WCHAR>(lower - L'A' + L'a');

            switch (lower)
            {
            case L'h':
                if (g_focusStrip)
                    MoveStripSelection(-1);
                else if (g_focusDock)
                    MoveDockSelection(-1);
                else
                    MoveSelection(-1, 0);
                return 0;
            case L'l':
                if (g_focusStrip)
                    MoveStripSelection(1);
                else if (g_focusDock)
                    MoveDockSelection(1);
                else
                    MoveSelection(1, 0);
                return 0;
            case L'j':
                if (g_focusDock)
                    MoveDockSelection(1);
                else if (!g_focusStrip)
                    MoveSelection(0, 1);
                return 0;
            case L'k':
                if (g_focusDock)
                    MoveDockSelection(-1);
                else if (!g_focusStrip)
                    MoveSelection(0, -1);
                return 0;
            case L'x':
                if (g_focusDock)
                    CloseDockSelection();
                else if (!g_focusStrip)
                    CloseEntry(g_selected);
                return 0;
            default:
                return 0;
            }
        }

        SetSearch(g_searchSelectAll ? std::wstring(1, ch) : g_search + ch);
        return 0;
    }

    case WM_MOUSEACTIVATE:
        return MA_ACTIVATE;

    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE && g_visible && g_closeOnFocusLoss &&
            !g_closingForActivation && !g_busy)
            HideOverlay(false);
        return 0;

    case WM_DISPLAYCHANGE:
    case 0x02E0:  // WM_DPICHANGED
        SetChipLayersVisible(false);
        ReleaseDeviceResources();
        ReleaseChipMaskSurface();
        UpdateMonitorForWindow(g_originWindow);
        SetWindowPos(g_overlay, HWND_TOPMOST, g_monitorX, g_monitorY, g_monitorW,
                     g_monitorH, SWP_NOACTIVATE);
        InvalidateRect(g_overlay, nullptr, FALSE);
        return 0;

    case WM_TIMER:
        if (wParam == kTimerFrame)
        {
            const ULONGLONG now = GetTickCount64();
            const float dt = g_lastFrameTick
                ? static_cast<float>(now - g_lastFrameTick) / 1000.0f
                : 0.016f;
            g_lastFrameTick = now;

            if (g_presence < g_targetPresence)
                g_presence = std::min(g_targetPresence,
                                      g_presence + dt / AnimationSeconds(0.17f));
            else if (g_presence > g_targetPresence)
                g_presence = std::max(g_targetPresence,
                                      g_presence - dt / AnimationSeconds(0.13f));

            if (g_targetPresence <= 0.0f && g_presence <= 0.0f)
            {
                FinishHide();
                if (!g_closingForActivation && g_originWindow && IsWindow(g_originWindow))
                    SetForegroundWindow(g_originWindow);
                return 0;
            }

            if (g_createAfterDraw)
            {
                const bool landed =
                    g_cardAnim.mode == CardAnimationMode::None ||
                    now - g_cardAnim.start >=
                        static_cast<ULONGLONG>(g_cardAnim.duration * 1000.0f);
                if (landed)
                    FinishDesktopCreateAfterDraw();
            }
            else if (g_cardAnim.mode != CardAnimationMode::None &&
                     now - g_cardAnim.start >=
                         static_cast<ULONGLONG>(g_cardAnim.duration * 1000.0f))
            {
                ClearCardAnimation();
            }

            if (g_presence >= 1.0f && !g_busy && !g_createAfterDraw &&
                g_cardAnim.mode == CardAnimationMode::None)
                KillTimer(hwnd, kTimerFrame);

            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }
        if (wParam == kTimerIdle)
        {
            // Prune windows that closed behind our back.
            bool changed = false;
            for (size_t i = g_windows.size(); i-- > 0;)
            {
                if (!IsWindow(g_windows[i].hwnd) || !IsWindowVisible(g_windows[i].hwnd))
                {
                    ReleaseThumbnails();
                    g_windows.erase(g_windows.begin() + static_cast<ptrdiff_t>(i));
                    changed = true;
                }
            }
            if (changed)
            {
                RebuildFilter();
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            PruneHeldTasks();
            if (g_held.empty())
                StopHeldWatch();
            return 0;
        }
        if (wParam == kTimerCarousel)
        {
            if (!IsWheel() || g_desktops.empty())
            {
                KillTimer(hwnd, kTimerCarousel);
                return 0;
            }

            const ULONGLONG now = GetTickCount64();
            float dt = g_lastCarouselTick
                ? static_cast<float>(now - g_lastCarouselTick) / 1000.0f
                : 0.016f;
            g_lastCarouselTick = now;
            dt = std::min(dt, 0.05f);

            const int target = StripTarget();
            const float delta = WrapDelta(
                static_cast<float>(target) - g_carouselPos,
                static_cast<int>(g_desktops.size()));
            const float rate =
                10.0f * 100.0f / static_cast<float>(std::max(50, g_animSpeedPercent));
            g_carouselPos += delta * std::min(1.0f, dt * rate);
            if (std::fabs(delta) < 0.002f)
            {
                g_carouselPos = static_cast<float>(target);
                KillTimer(hwnd, kTimerCarousel);
            }
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }
        if (wParam == kTimerCaret)
        {
            if (g_searchFocused || IsRenamingDesktop())
                InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }
        if (wParam == kTimerDesktop)
        {
            RefreshDesktops();
            // The shell animates desktop changes, so poll quickly until the
            // action has actually landed instead of waiting a fixed 400-700 ms.
            bool done = true;
            if (g_desktopActionCreate)
                done = static_cast<int>(g_desktops.size()) >
                       g_desktopActionStartCount;
            else if (g_desktopActionClose)
                done = static_cast<int>(g_desktops.size()) <
                       g_desktopActionStartCount;
            else if (g_pendingDesktopTarget >= 0)
                done = g_currentDesktop == g_pendingDesktopTarget;

            const int maxTries =
                (g_desktopActionCreate || g_desktopActionClose) ? 25 : 50;
            if (!done && ++g_pendingDesktopTries < maxTries)
            {
                SetTimer(hwnd, kTimerDesktop, 40, nullptr);
                return 0;
            }

            KillTimer(hwnd, kTimerDesktop);
            g_busy = false;
            g_busySince = 0;
            g_desktopActionCreate = false;
            g_desktopActionClose = false;
            g_desktopActionStartCount = 0;
            g_pendingDesktopTarget = -1;
            g_pendingDesktopTries = 0;
            g_keepThumbnailsWhileBusy = false;

            // Carry held tasks right away instead of waiting for the watcher.
            GUID active = {};
            if (ReadActiveDesktopId(&active))
            {
                g_watchedDesktop = active;
                g_hasWatchedDesktop = true;
                MoveHeldTasksToDesktop(active, false);
            }

            // A window chosen from an all-desktop search is activated only
            // after its desktop is actually active. The overlay stays up until
            // the shell finishes the switch, then closes onto the window.
            HWND activateTarget = g_pendingActivateWindow;
            const int activateDesktop = g_pendingActivateDesktop;
            g_pendingActivateWindow = nullptr;
            g_pendingActivateDesktop = -1;
            if (activateTarget && IsWindow(activateTarget) &&
                (activateDesktop < 0 || IsWindowOnCurrentDesktop(activateTarget)))
            {
                g_closingForActivation = true;
                HideOverlay(true);
                g_closingForActivation = false;
                if (IsIconic(activateTarget))
                    ShowWindow(activateTarget, SW_RESTORE);
                if (!SetForegroundWindow(activateTarget))
                    SwitchToThisWindow(activateTarget, TRUE);
                return 0;
            }

            RebuildWindowList();
            g_desktopSelected = g_currentDesktop;
            KickCarousel();
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        }
        return 0;

    case WM_DESTROY:
        ReleaseThumbnails();
        return 0;
    }

    return DefWindowProcW(hwnd, message, wParam, lParam);
}

static LRESULT CALLBACK ControlWndProc(HWND hwnd, UINT message, WPARAM wParam,
                                       LPARAM lParam)
{
    if (message == WM_TIMER && wParam == kTimerHeldWatch)
    {
        // Carry held tasks across whenever the active desktop changes.
        GUID id = {};
        if (ReadActiveDesktopId(&id) &&
            (!g_hasWatchedDesktop || !IsEqualGUID(id, g_watchedDesktop)))
        {
            g_watchedDesktop = id;
            g_hasWatchedDesktop = true;
            MoveHeldTasksToDesktop(id);
        }
        if (g_held.empty())
            StopHeldWatch();
        return 0;
    }
    if (g_hotkeyMessage != 0 && message == g_hotkeyMessage &&
        wParam == kHotkeyFlagWinTab)
    {
        // Ignore the toggle while the pre-create card is still in flight.
        if (g_createAfterDraw)
            return 0;
        // Ignore auto-repeat / rapid toggles while a held Win+Tab repeats.
        const ULONGLONG now = GetTickCount64();
        if (!g_visible || now - g_shownAtTick > 280)
            ToggleOverlay();
        return 0;
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

////////////////////////////////////////////////////////////////////////////////
// UI THREAD

static void SetThreadPerMonitorAwareV2()
{
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    typedef HANDLE(WINAPI * SetThreadDpiAwarenessContextFn)(HANDLE);
    SetThreadDpiAwarenessContextFn setContext = user32
        ? reinterpret_cast<SetThreadDpiAwarenessContextFn>(
              GetProcAddress(user32, "SetThreadDpiAwarenessContext"))
        : nullptr;
    if (setContext)
        setContext(reinterpret_cast<HANDLE>(static_cast<INT_PTR>(-4)));
}

static bool RegisterWindowClasses()
{
    WNDCLASSEXW overlayClass = {sizeof(overlayClass)};
    overlayClass.style = CS_HREDRAW | CS_VREDRAW;
    overlayClass.lpfnWndProc = OverlayWndProc;
    overlayClass.hInstance = g_hModule;
    overlayClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    overlayClass.lpszClassName = kOverlayClass;
    if (!RegisterClassExW(&overlayClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return false;

    WNDCLASSEXW controlClass = {sizeof(controlClass)};
    controlClass.lpfnWndProc = ControlWndProc;
    controlClass.hInstance = g_hModule;
    controlClass.lpszClassName = kControlClass;
    if (!RegisterClassExW(&controlClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return false;

    WNDCLASSEXW chipClass = {sizeof(chipClass)};
    chipClass.lpfnWndProc = ChipLayerWndProc;
    chipClass.hInstance = g_hModule;
    chipClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    chipClass.lpszClassName = kChipLayerClass;
    if (!RegisterClassExW(&chipClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return false;

    return true;
}

static void UnregisterWindowClasses()
{
    UnregisterClassW(kOverlayClass, g_hModule);
    UnregisterClassW(kControlClass, g_hModule);
    UnregisterClassW(kChipLayerClass, g_hModule);
}

static bool InitializeUi()
{
    LoadSettings();

    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
        return false;

    if (FAILED(CoCreateInstance(kClsidVirtualDesktopManager, nullptr,
                                CLSCTX_INPROC_SERVER, kIidVirtualDesktopManager,
                                reinterpret_cast<void**>(&g_vdm))))
        g_vdm = nullptr;

    if (!RegisterWindowClasses())
        return false;

    g_overlay = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, kOverlayClass, L"",
                                WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, g_hModule,
                                nullptr);
    if (!g_overlay)
    {
        Wh_Log(L"Overlay window creation failed: %lu", GetLastError());
        return false;
    }

    // Top-level thumbnail host for window chips. The region is set per frame to
    // the union of the preview squares; the layered mask above it hides the
    // square corners.
    g_thumbHost = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
        kChipLayerClass, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, g_hModule,
        nullptr);
    if (!g_thumbHost)
        Wh_Log(L"Window-chip thumbnail host creation failed: %lu", GetLastError());

    g_chipMask = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT |
            WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kChipLayerClass, L"", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, g_hModule,
        nullptr);
    if (!g_chipMask)
        Wh_Log(L"Window-chip mask creation failed: %lu", GetLastError());

    g_control = CreateWindowExW(0, kControlClass, kControlTitleIdle, 0, 0, 0, 0, 0,
                                HWND_MESSAGE, nullptr, g_hModule, nullptr);
    if (!g_control)
    {
        Wh_Log(L"Control window creation failed: %lu", GetLastError());
        return false;
    }

    if (g_hotkeyMessage)
        ChangeWindowMessageFilterEx(g_control, g_hotkeyMessage, MSGFLT_ALLOW, nullptr);

    // Prewarm the renderer so the first Win+Tab is instant.
    UpdateMonitorForWindow(nullptr);
    EnsureFactories();
    EnsureDeviceResources();
    EnsureTextFormats();

    SetControlReady(true);
    return true;
}

static void ShutdownUi()
{
    SetChipLayersVisible(false);
    ReleaseThumbnails();
    StopOverlayTimers();
    ReleaseGraphics();
    ReleaseChipMaskSurface();

    if (g_control)
    {
        SetWindowTextW(g_control, kControlTitleIdle);
        DestroyWindow(g_control);
        g_control = nullptr;
    }
    if (g_chipMask)
    {
        DestroyWindow(g_chipMask);
        g_chipMask = nullptr;
    }
    if (g_thumbHost)
    {
        DestroyWindow(g_thumbHost);
        g_thumbHost = nullptr;
    }
    if (g_overlay)
    {
        DestroyWindow(g_overlay);
        g_overlay = nullptr;
    }

    UnregisterWindowClasses();

    if (g_vdm)
    {
        g_vdm->Release();
        g_vdm = nullptr;
    }
    if (g_vdInternal)
    {
        g_vdInternal->Release();
        g_vdInternal = nullptr;
    }
    if (g_viewCollection)
    {
        g_viewCollection->Release();
        g_viewCollection = nullptr;
    }
    g_vdInternalResolved = false;

    g_windows.clear();
    g_filtered.clear();
    g_desktops.clear();
    g_held.clear();
    g_heldWatchOn = false;
    CoUninitialize();
}

static DWORD WINAPI UiThreadProc(LPVOID)
{
    SetThreadPerMonitorAwareV2();

    MSG message = {};
    PeekMessageW(&message, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    const bool ok = InitializeUi();
    InterlockedExchange(&g_uiInitOk, ok ? 1 : 0);
    SetEvent(g_uiReadyEvent);

    if (ok)
    {
        while (GetMessageW(&message, nullptr, 0, 0) > 0)
        {
            if (message.hwnd == nullptr && message.message == WM_UI_QUIT)
                break;
            if (message.hwnd == nullptr && message.message == WM_UI_SETTINGS)
            {
                LoadSettings();
                // A settings change can switch the strip out of card mode while
                // the create card is being pulled; drop the stale drag state.
                g_createDragging = false;
                g_createPull = 0.0f;
                if (g_overlay && GetCapture() == g_overlay)
                    ReleaseCapture();
                if (!g_cardAnimations || !UsesCards())
                {
                    const bool hadPendingCreate = g_createAfterDraw;
                    ClearCardAnimation();
                    if (hadPendingCreate)
                    {
                        g_busy = false;
                        g_busySince = 0;
                        g_desktopActionCreate = false;
                        g_desktopActionClose = false;
                        g_desktopActionStartCount = 0;
                        g_pendingDesktopTarget = -1;
                        g_pendingDesktopTries = 0;
                        g_keepThumbnailsWhileBusy = false;
                    }
                }
                // The accent blur only takes effect while the overlay is hidden
                // (see ApplyBackdrop), so re-applying it to a visible overlay
                // would leave the flat fill behind it. It is applied on the next
                // ShowOverlay() instead.
                if (g_overlay && !g_visible)
                    ApplyBackdrop(g_overlay);
                g_carouselPos = static_cast<float>(StripTarget());
                if (g_overlay)
                {
                    KillTimer(g_overlay, kTimerCarousel);
                    InvalidateRect(g_overlay, nullptr, FALSE);
                }
                continue;
            }
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }

    ShutdownUi();
    return 0;
}

static bool StartUiThread()
{
    g_uiReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_uiReadyEvent)
        return false;

    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (!g_uiThread)
    {
        CloseHandle(g_uiReadyEvent);
        g_uiReadyEvent = nullptr;
        return false;
    }

    HANDLE waits[2] = {g_uiReadyEvent, g_uiThread};
    const DWORD result = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
    const bool ok = result == WAIT_OBJECT_0 &&
                    InterlockedCompareExchange(&g_uiInitOk, 0, 0) == 1;
    if (!ok)
    {
        WaitForSingleObject(g_uiThread, INFINITE);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
        CloseHandle(g_uiReadyEvent);
        g_uiReadyEvent = nullptr;
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// EXPLORER COMPONENT
//
// The native Task View is opened by a hotkey that Explorer registers for itself
// on its "Immersive Shell" thread. This component observes that thread's
// message queue with a WH_GETMESSAGE hook and forwards Win+Tab to the overview
// instead of letting the native Task View open. It creates no windows and
// installs no global hooks.

static HHOOK g_messageHook = nullptr;
static HANDLE g_messageHookThread = nullptr;
static volatile LONG g_messageHookCalls = 0;
static HANDLE g_explorerStopEvent = nullptr;
static HANDLE g_explorerThread = nullptr;

static void InitHotkeyMessage()
{
    if (!g_hotkeyMessage)
        g_hotkeyMessage = RegisterWindowMessageW(kHotkeyMessageName);
}

static bool ForwardHotkey(WPARAM flags)
{
    if (!g_hotkeyMessage)
        return false;

    HWND control = FindWindowExW(HWND_MESSAGE, nullptr, kControlClass,
                                 kControlTitleReady);
    if (!control)
        return false;

    // Explorer is handling the hotkey right now, so it can hand the foreground
    // to the overview process (needed when an elevated window had focus).
    DWORD processId = 0;
    GetWindowThreadProcessId(control, &processId);
    if (processId)
        AllowSetForegroundWindow(processId);

    return PostMessageW(control, g_hotkeyMessage, flags, 0) != FALSE;
}

static LRESULT CALLBACK GetMessageProc(int code, WPARAM wParam, LPARAM lParam)
{
    InterlockedIncrement(&g_messageHookCalls);

    MSG* msg = reinterpret_cast<MSG*>(lParam);
    if (code == HC_ACTION && wParam == PM_REMOVE && msg &&
        msg->message == WM_HOTKEY && HIWORD(msg->lParam) == VK_TAB)
    {
        const UINT modifiers = LOWORD(msg->lParam);
        // Win+Tab is ours; Alt+Tab stays with the native/other switchers.
        if ((modifiers & MOD_WIN) != 0 && (modifiers & MOD_ALT) == 0)
        {
            if (ForwardHotkey(kHotkeyFlagWinTab))
                msg->message = WM_NULL;
        }
    }

    const LRESULT result = CallNextHookEx(nullptr, code, wParam, lParam);
    InterlockedDecrement(&g_messageHookCalls);
    return result;
}

static DWORD FindImmersiveShellThread()
{
    DWORD found = 0;
    const DWORD processId = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return found;

    THREADENTRY32 entry = {};
    entry.dwSize = sizeof(entry);
    for (BOOL more = Thread32First(snapshot, &entry); more && !found;
         more = Thread32Next(snapshot, &entry))
    {
        if (entry.th32OwnerProcessID != processId)
            continue;
        HANDLE thread = OpenThread(THREAD_QUERY_LIMITED_INFORMATION, FALSE,
                                   entry.th32ThreadID);
        if (!thread)
            continue;
        PWSTR name = nullptr;
        if (SUCCEEDED(GetThreadDescription(thread, &name)) && name &&
            wcscmp(name, kExplorerThreadName) == 0)
            found = entry.th32ThreadID;
        if (name)
            LocalFree(name);
        CloseHandle(thread);
    }

    CloseHandle(snapshot);
    return found;
}

static bool HookImmersiveShellThread()
{
    const DWORD threadId = FindImmersiveShellThread();
    if (!threadId)
        return false;
    HANDLE thread = OpenThread(SYNCHRONIZE, FALSE, threadId);
    if (!thread)
        return false;
    // Same-process thread: no module handle is needed.
    HHOOK hook = SetWindowsHookExW(WH_GETMESSAGE, GetMessageProc, nullptr, threadId);
    if (!hook)
    {
        Wh_Log(L"SetWindowsHookEx(WH_GETMESSAGE) failed: %lu", GetLastError());
        CloseHandle(thread);
        return false;
    }
    Wh_Log(L"Hooked explorer thread %lu (\"%s\")", threadId, kExplorerThreadName);
    g_messageHook = hook;
    g_messageHookThread = thread;
    return true;
}

static void UnhookImmersiveShellThread()
{
    if (g_messageHook)
    {
        UnhookWindowsHookEx(g_messageHook);
        g_messageHook = nullptr;
    }
    if (g_messageHookThread)
    {
        CloseHandle(g_messageHookThread);
        g_messageHookThread = nullptr;
    }

    // Wait for in-flight callbacks to leave the module before it is unloaded.
    while (InterlockedCompareExchange(&g_messageHookCalls, 0, 0) > 0)
        Sleep(1);
}

static DWORD WINAPI ExplorerThreadProc(LPVOID)
{
    // Only the shell process (the taskbar owner) receives the hotkey.
    for (;;)
    {
        if (HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr))
        {
            DWORD processId = 0;
            GetWindowThreadProcessId(taskbar, &processId);
            if (processId != GetCurrentProcessId())
            {
                Wh_Log(L"Not the shell process, nothing to do");
                return 0;
            }
            break;
        }
        if (WaitForSingleObject(g_explorerStopEvent, 1000) != WAIT_TIMEOUT)
            return 0;
    }

    DWORD interval = 2000;
    bool loggedMissing = false;
    for (;;)
    {
        if (!g_messageHook && !HookImmersiveShellThread() && !loggedMissing)
        {
            Wh_Log(L"Explorer thread \"%s\" not found yet", kExplorerThreadName);
            loggedMissing = true;
        }

        const HANDLE events[] = {g_explorerStopEvent, g_messageHookThread};
        const DWORD result = WaitForMultipleObjects(g_messageHook ? 2 : 1, events, FALSE,
                                                    g_messageHook ? INFINITE : interval);
        if (result == WAIT_TIMEOUT)
        {
            interval = std::min<DWORD>(interval * 2, 60000);
        }
        else if (result == WAIT_OBJECT_0 + 1)
        {
            UnhookImmersiveShellThread();
            interval = 2000;
            loggedMissing = false;
        }
        else
        {
            break;
        }
    }

    UnhookImmersiveShellThread();
    return 0;
}

static void StopExplorerPart()
{
    if (g_explorerThread)
    {
        SetEvent(g_explorerStopEvent);
        WaitForSingleObject(g_explorerThread, INFINITE);
        CloseHandle(g_explorerThread);
        g_explorerThread = nullptr;
    }
    if (g_explorerStopEvent)
    {
        CloseHandle(g_explorerStopEvent);
        g_explorerStopEvent = nullptr;
    }
}

static void StartExplorerPart()
{
    if (g_explorerThread)
        return;

    g_explorerStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_explorerStopEvent)
        return;
    g_explorerThread = CreateThread(nullptr, 0, ExplorerThreadProc, nullptr, 0, nullptr);
    if (!g_explorerThread)
        StopExplorerPart();
}

static bool IsExplorerProcess()
{
    WCHAR path[MAX_PATH];
    const DWORD length = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!length || length == ARRAYSIZE(path))
        return false;
    PCWSTR name = wcsrchr(path, L'\\');
    name = name ? name + 1 : path;
    return _wcsicmp(name, L"explorer.exe") == 0;
}

////////////////////////////////////////////////////////////////////////////////
// WINDHAWK TOOL MOD IMPLEMENTATION
//
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook()
{
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit()
{
    // explorer.exe: only the hotkey forwarding component.
    if (IsExplorerProcess())
    {
        g_isExplorer = true;
        InitHotkeyMessage();
        StartExplorerPart();
        return TRUE;
    }

    DWORD sessionId = 0;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) && sessionId == 0)
        return FALSE;

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv)
    {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++)
    {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0)
        {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++)
    {
        if (wcscmp(argv[i], L"-tool-mod") == 0)
        {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0)
                isCurrentToolModProcess = true;
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded)
        return FALSE;

    if (isCurrentToolModProcess)
    {
        g_toolModProcessMutex = CreateMutex(nullptr, TRUE,
                                            L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex)
        {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit())
            ExitProcess(1);

        IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);
        DWORD entryPointRva = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRva;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess)
        return FALSE;

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit()
{
    if (!g_isToolModProcessLauncher)
        return;

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath, ARRAYSIZE(currentProcessPath)))
    {
    case 0:
    case ARRAYSIZE(currentProcessPath):
        Wh_Log(L"GetModuleFileName failed");
        return;
    }

    WCHAR commandLine[MAX_PATH + 2 +
                      (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath, WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule)
    {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule)
        {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t createProcess =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule, "CreateProcessInternalW");
    if (!createProcess)
    {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!createProcess(nullptr, currentProcessPath, commandLine, nullptr, nullptr, FALSE,
                       NORMAL_PRIORITY_CLASS, nullptr, nullptr, &si, &pi, nullptr))
    {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged()
{
    if (g_isExplorer)
        return;
    if (g_isToolModProcessLauncher)
        return;

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit()
{
    if (g_isExplorer)
    {
        StopExplorerPart();
        return;
    }

    if (g_isToolModProcessLauncher)
        return;

    WhTool_ModUninit();
    ExitProcess(0);
}

////////////////////////////////////////////////////////////////////////////////
// TOOL MOD CALLBACKS

BOOL WhTool_ModInit()
{
    // The module handle is required to register the overlay and control classes.
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCWSTR>(&OverlayWndProc), &g_hModule);
    if (!g_hModule)
        return FALSE;

    InitHotkeyMessage();
    return StartUiThread() ? TRUE : FALSE;
}

void WhTool_ModSettingsChanged()
{
    if (g_uiThreadId)
        PostThreadMessageW(g_uiThreadId, WM_UI_SETTINGS, 0, 0);
}

void WhTool_ModUninit()
{
    if (g_uiThread)
    {
        PostThreadMessageW(g_uiThreadId, WM_UI_QUIT, 0, 0);
        WaitForSingleObject(g_uiThread, INFINITE);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }

    if (g_uiReadyEvent)
    {
        CloseHandle(g_uiReadyEvent);
        g_uiReadyEvent = nullptr;
    }

    g_uiThreadId = 0;
}
