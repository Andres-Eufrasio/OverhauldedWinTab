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
- Search across window titles and applications (press `/` to start typing)
- Optional poker-chip window tabs with a circular live preview, app icon or
  name-only centre, in four sizes
- Optional playing-card, poker-chip and carousel desktop tabs
- Accent-outline or pick-up/lift selection for every desktop tab style
- Held windows can move into a left or right side dock, with full keyboard
  access and an optional floating (background-free) dock
- Optional lift on window hover and keyboard selection
- Animated playing cards: draw one from the deck when creating a desktop and
  throw one away when closing it
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
| `x` | Close the selected window or dock item (Vim) |
| Typing while the search is focused | Filter windows by title or application |
| Left click | Activate a window, or jump straight to a desktop |
| Right click a desktop | Rename that virtual desktop |
| Middle click on a card or dock item | Close that window |
| Click a held dock item | Activate that window |
| Click the create control on the strip | Create a new virtual desktop (a `+`, or the face-down card) |
| Pull the create card down | Create a new virtual desktop (playing-card tabs) |
| Click `x` on the active desktop | Close the current virtual desktop |
| Mouse wheel | Move through grid pages |

The search field is only typed into once it has focus: click it or press `/`
first. With **Always show search** turned off the field stays hidden until you
press `/`. Until the field has focus the letter keys are available to navigation,
so a query that contains `h`, `j`, `k`, `l`, `n` or `x` never collides with a
command. Focusing a field that already has a query selects it, so the next typed
character replaces the old query. Set **Vim navigation** to `off` to disable the
movement keys.

## Settings

| Setting | Description |
| ------- | ----------- |
| Theme | Color palette for the whole overlay (Custom, Catppuccin, Nord, ...) |
| Accent color | Accent color used for highlights, in `#RRGGBB` format (Custom theme) |
| Title text | Text shown in the top-left corner (defaults to `Task View`) |
| Background | Backdrop effect: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent |
| Background color | Tint color of the overview panel, in `#RRGGBB` format (Custom theme) |
| Background opacity | How strong the panel tint is over the backdrop (`0`-`100`) |
| Show window icons | Show each window's application icon in its card header |
| Show hints | Show the keyboard shortcut hints at the bottom left |
| Always show search | Keep the search bar visible; when off, press `/` to reveal it |
| Window tabs | Square previews, or poker chips with the window title curved around the top rim |
| Window chip content | Live window preview, app icon, or name only |
| Window chip size | Small, medium, large or extra-large poker-chip window tabs |
| Chip colors | Theme accent shades, a single color, a custom palette, or classic casino colors |
| Chip color | Single chip color in `#RRGGBB` format (Single color mode) |
| Chip palette | Comma-separated `#RRGGBB` colors cycled across desktop and window chips (Custom palette mode) |
| Desktop selection | Accent outline, or pick-up/lift for the selected and active desktop tabs |
| Held windows | Keep held windows in the grid, or dock them on the left or right |
| Held dock background | Show a panel behind the dock; turn off for a floating dock |
| Lift held windows | Raise windows held with `U` so they look picked up |
| Lift hovered windows | Raise a window while the pointer is over it |
| Lift selected window | Raise the keyboard-selected window in the grid |
| Desktop strip | Flat row or rotating carousel |
| Desktop tabs | Pills, poker chips, or playing cards |
| Card size | Small, medium or large playing cards |
| Desktop strip background | Panel behind the tabs: Auto (flat only), Always show, or Always hide |
| Animation speed | Relative speed of the open, close and playing-card animations |
| Card animations | Animate the playing-card draw and throw when creating or closing a desktop |
| Close when focus is lost | Dismiss the overview when it loses activation |
| Wrap grid navigation | Arrow keys wrap around the edges of the grid |
| Wrap desktop strip | `Left`/`Right` and `h`/`l` wrap from the last desktop to the first |
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

**Desktop strip** chooses how the virtual desktops are laid out at the bottom:

- **Flat row** (default) – every desktop in a single row, with the create button
  after them and the strip panel behind them.
- **Carousel** – the active desktop sits in the centre, its neighbours curve and
  tilt away, and the wheel turns as you switch. Once the strip has focus, `h` /
  `l` or the arrows spin the wheel to a desktop; clicking a side tab jumps
  straight there.

**Desktop tabs** chooses the tab shape for both layouts:

- **Pills** (default) – the wide rounded tabs with the desktop number and name.
- **Poker chips** – each desktop becomes a numbered casino chip with a coloured
  rim, white edge spots and the desktop name on a label underneath. The create
  button becomes a round chip too. The rim colors follow **Chip colors**: by
  default they are shades derived from the theme accent, so the chips change with
  the palette. Choose **Classic casino colors** for the original fixed set, or
  define a single color or your own palette.
- **Playing cards** – each desktop becomes a portrait card with its own suit
  (spades, hearts, diamonds, clubs, then back to spades). **Card size** makes the
  cards small, medium or large. In the carousel the cards float directly over the
  desktop with the panel hidden by default; the flat row keeps the panel. The
  create button is a face-down card: click it, or pull it downward, to create a
  new desktop.

With **Card animations** on, creating a desktop draws a card from the deck onto
the new desktop tab, and closing one throws its card off the strip. The card
animations use the same **Animation speed** as the open and close transitions.

**Desktop selection** changes how the active and selected desktop tabs are
marked. **Accent outline** (default) keeps the current accent border. **Lift**
raises the selected tab, or the active tab when the strip is not focused, and
skips the accent outline so the pick-up is the only selection cue. Lift works
for pills, poker chips and playing cards in both the flat row and the carousel;
the shadow deepens as the tab rises.

**Desktop strip background** controls the panel behind the strip: **Auto**
(default) keeps it for the flat row and hides it for the carousel, **Always show**
brings it back, and **Always hide** makes the flat row float as well.

**Wrap desktop strip** (default on) lets `Left`/`Right` and `h`/`l` loop from the
last desktop back to the first, so a seven-desktop carousel goes from 7 to 1
instead of stopping at the edge.

## Window chips

**Window tabs** can draw each open window as a square preview or as a
poker chip. The window title is curved around the top rim, one character at a
time, and the centre can show:

- **Live window preview** (default) – the real DWM thumbnail, clipped to a
  circle inside the chip.
- **App icon** – the application icon on a light centre disc.
- **Name only** – just the curved title and the coloured chip surface.

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

Press `U` to hold the selected window. Held windows follow you to every desktop
you switch to, and they get a colored frame and corner dot. By default they stay
in the grid. Set **Held windows** to **Dock on the left** or **Dock on the
right** to move them into a side panel instead; the panel uses the same squares
or poker chips as the grid, so the two modes stay visually consistent.

The dock has its own keyboard stage: press `Tab` from the grid to focus it, then
use the arrows (or `h`/`j`/`k`/`l`) to select an item, `Enter` to activate it,
`Delete` to close it and `U` to release it back into the grid. `Tab` continues to
the desktop strip and then back to the grid; `Esc` leaves the dock. Clicking,
middle-clicking or hovering a dock item still works as before. Held dock items
stay visible while a search is active, so a held window is always one click
away. Turn **Held dock background** off to let the dock float without a panel.
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
so clicking a desktop pill or pressing a number goes straight there. Moving a
window to another desktop uses the shell's `IApplicationViewCollection` and
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
