# OverhauldedWin Tab

A modern replacement for the Windows 11 **Task View** (`Win` + `Tab`).

OverhauldedWin Tab takes over the `Win` + `Tab` hotkey and presents a dark,
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
- Type-to-filter search across window titles and applications
- Virtual desktop strip with switching, creating and closing
- Rename virtual desktops inline (saved the same way Windows stores them)
- Move a window to another virtual desktop without leaving the overview
- Vim-style navigation (`h` `j` `k` `l`, `/`, `x`)
- Customizable background: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent,
  with a configurable tint color and opacity
- Keyboard and mouse navigation
- Smooth open / close animation with resolution-aware UI scaling
- High-DPI aware, per-monitor
- Lightweight: the Explorer hook only forwards the hotkey
- Background execution for instant activation

## Design

OverhauldedWin Tab keeps the visual language of OverhauldedWin: a dark obsidian
panel, rounded cards, subtle downward shadows, an accent highlight for the
selected window, and a configurable backdrop (Acrylic, Mica, Mica Alt, Blur,
Solid or transparent) behind the overview.

The overview is a persistent window prepared in the background, so `Win` + `Tab`
opens immediately instead of building the interface from scratch every time.

## Controls

| Input | Action |
| ----- | ------ |
| `Win` + `Tab` | Open or close the overview |
| `Esc` | Close the overview (or clear the search / cancel a rename) |
| `Enter` | Switch to the selected window / desktop, or save a rename |
| `Delete` | Close the selected window / desktop |
| `Arrows` | Move through the window grid |
| `Tab` | Toggle between the grid and the desktop strip |
| `Ctrl` + `Left` / `Right` | Switch to the previous / next virtual desktop |
| `Shift` + `Left` / `Right` | Move the selected window to the previous / next desktop |
| `F2` | Rename the selected (or current) virtual desktop |
| `N` | Create a new virtual desktop (strip focused) |
| `h` `j` `k` `l` | Vim movement (move through the grid / desktop strip) |
| `/` | Focus the search field |
| `x` | Close the selected window (Vim) |
| Printable keys | Filter windows by title or application |
| Left click | Activate a window or switch desktop |
| Right click a desktop | Rename that virtual desktop |
| Middle click on a card | Close that window |
| Click `+` on the strip | Create a new virtual desktop |
| Click `x` on the active desktop | Close the current virtual desktop |
| Mouse wheel | Move through grid pages |

Vim keys only move the selection while the search field is empty, so a query
that contains `h`, `j`, `k`, `l` or `x` still works once you start typing or
press `/`. Set **Vim navigation** to `off` to disable them.

## Settings

| Setting | Description |
| ------- | ----------- |
| Accent color | Accent color used for highlights, in `#RRGGBB` format |
| Background | Backdrop effect: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent |
| Background color | Tint color of the overview panel, in `#RRGGBB` format |
| Background opacity | How strong the panel tint is over the backdrop (`0`-`100`) |
| Show window icons | Show each window's application icon in its card header |
| Animation speed | Relative speed of the open and close animations |
| Close when focus is lost | Dismiss the overview when it loses activation |
| Wrap grid navigation | Arrow keys wrap around the edges of the grid |
| Vim navigation | Enable `h` `j` `k` `l`, `/` and `x` navigation keys |

**Background** controls what sits behind the panel:

- **Acrylic** – blurred desktop with a translucent tint (default)
- **Mica** – Windows 11 Mica material
- **Mica Alt** – Windows 11 Mica Alt material
- **Blur** – classic blur without the acrylic noise
- **Solid** – opaque panel, ignores the opacity setting
- **Transparent** – no backdrop effect; the live desktop shows through,
  tinted only by the background color and opacity

Lower **Background opacity** to see more of the desktop behind the overview;
`0` is fully transparent and `100` is fully opaque.

## How it works

The mod runs in two places:

1. A small component inside `explorer.exe` watches the `Immersive Shell`
   message queue and forwards the `Win` + `Tab` hotkey to the overview instead
   of letting the native Task View open.
2. A dedicated `windhawk.exe` tool process owns the persistent overlay window,
   the renderer and all input handling.

Virtual desktop names are written to the same per-desktop registry keys Windows
uses (`HKCU\...\Explorer\VirtualDesktops\Desktops\{GUID}\Name`), so renames are
picked up by Windows and other tools. Moving a window to another desktop uses
the documented `IVirtualDesktopManager::MoveWindowToDesktop` API rather than
synthesized hotkeys.

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

OverhauldedWin Tab is a pre-release project.
