# OverhauldedWinTab

OverhauldedWinTab replaces Windows 11 Task View (`Win+Tab`) with a window grid
and a virtual desktop strip. Switch to a window from its live preview, search
by title or app, or jump to another desktop without closing the overview.

## Controls

| Key or action | What it does |
| --- | --- |
| `Win+Tab` | Open or close the overview |
| Arrow keys | Move through windows, the held dock or desktops |
| `Tab` | Cycle between the window grid, held dock (if enabled) and desktop strip |
| `Enter` | Open the selected window or switch to the selected desktop |
| `Esc` | Leave the dock or search; press again to close the overview |
| `/` | Search windows on the current desktop |
| `Shift+/` (`?`) | Search windows on every desktop |
| `1`–`9` | Switch to a numbered desktop |
| `Shift+1`–`Shift+9`, or `M` then `1`–`9` | Move the selected window to that desktop |
| `Ctrl+Left` / `Ctrl+Right` | Switch to the previous or next desktop |
| `Shift+Left` / `Shift+Right` | Move the selected window to an adjacent desktop |
| `U`, or right-click a window | Hold or release a window |
| `Delete`, or middle-click a window | Close a window; `Delete` closes the active desktop when the strip is focused |
| `F2`, or right-click a desktop tab | Rename a desktop |
| `N` (strip focused), or click the create tab | Create a desktop |

Click a window to open it or a desktop tab to switch straight to it. Use the
mouse wheel to page through windows. With **Vim navigation** enabled, `h`/`j`/`k`/`l`
move the selection and `x` closes a window.

## Search

Press `/` for the current desktop or `Shift+/` (`?`) for all desktops, then type
to filter by window title or app. You can also click the search field. If it
already contains a query, focusing it selects that query so you can replace it.

In all-desktop search, titles show a desktop number (`D1`, `D2`, etc.). Windows
doesn't provide live previews for inactive desktops, so preview cards and chips
show an app icon there instead. Selecting one switches desktops first, then
focuses the window. `Esc` clears the search and returns to the current
desktop's windows. A new `Win+Tab` session starts with an empty query on the
current desktop.

## Appearance and layout

The mod's **Settings** tab covers the layout and colors:

- **Window tabs:** Choose square previews or poker chips. Chips can show a
  circular live preview, an app icon or just the window name, and come in four
  sizes. Pick theme-based, classic casino, single or custom chip colors.
- **Desktop strip:** Use a flat row or a carousel, with pill, poker-chip or
  playing-card tabs. **Tuck playing cards** shows just their upper half at the
  bottom of the screen; turn it off for full cards. Card size, create/close
  animations, the strip background and highlight or lift selection are
  configurable.
- **Held windows:** Press `U` or right-click a window to keep it with you as you
  change desktops. Leave held windows in the grid or put them in a dock on either
  side. The dock can have a panel or float on its own.
- **Theme and background:** Choose a built-in palette (including Catppuccin,
  Nord and Dracula) or set your own colors. Background options include Acrylic,
  Mica, Blur, Solid and Transparent, with adjustable tint opacity.
- **Other options:** Hide the search bar until you use it, turn off shortcut
  hints, adjust animation speed, enable wraparound navigation, or lift hovered,
  selected and held windows.

## Compatibility

- Windows 11 only. The overview appears on the active monitor; it doesn't draw
  a separate overview on every monitor.
- Mods that also replace Task View or intercept `Win+Tab` may conflict with this
  one.

## Building from source

`build.ps1` uses the compiler bundled with Windhawk for a local compile and
link check. It doesn't install the mod:

```powershell
.\build.ps1
```

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for implementation details.

## License

MIT. See [LICENSE](LICENSE).
