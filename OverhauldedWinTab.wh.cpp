// ==WindhawkMod==
// @id              overhaulded-win-tab
// @name            OverhauldedWin Tab
// @description     Replaces the Windows 11 Task View (Win+Tab) with a modern, focused overview of your windows and virtual desktops.
// @version         0.2.4
// @author          Andres Eufrasio
// @github          https://github.com/Andres-Eufrasio
// @homepage        https://github.com/Andres-Eufrasio/OverhauldedWinTab
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -lshell32 -lole32 -lgdi32 -luser32 -ladvapi32 -lshcore -lversion -ldwmapi -ld2d1 -ldwrite
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
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
- Search across window titles and applications (press `/` to start typing)
- Virtual desktop strip with switching, creating and closing
- Rename virtual desktops inline (saved the same way Windows stores them)
- Move a window to another virtual desktop without leaving the overview
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
| Typing while the search is focused | Filter windows by title or application |
| Left click | Activate a window or switch desktop |
| Right click a desktop | Rename that virtual desktop |
| Middle click on a card | Close that window |
| Click `+` on the strip | Create a new virtual desktop |
| Click `x` on the active desktop | Close the current virtual desktop |
| Mouse wheel | Move through grid pages |

The search field is only typed into once it has focus: click it or press `/`
first. Until then the letter keys are available to navigation, so a query that
contains `h`, `j`, `k`, `l`, `n` or `x` never collides with a command. Set
**Vim navigation** to `off` to disable the movement keys.

## Settings

| Setting | Description |
| ------- | ----------- |
| Theme | Color palette for the whole overlay (Custom, Catppuccin, Nord, ...) |
| Accent color | Accent color used for highlights, in `#RRGGBB` format (Custom theme) |
| Background | Backdrop effect: Acrylic, Mica, Mica Alt, Blur, Solid or Transparent |
| Background color | Tint color of the overview panel, in `#RRGGBB` format (Custom theme) |
| Background opacity | How strong the panel tint is over the backdrop (`0`-`100`) |
| Show window icons | Show each window's application icon in its card header |
| Animation speed | Relative speed of the open and close animations |
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

## Search

Press `/` or click the field to focus the search, then type to filter windows by
title or application. The query is cleared every time the overview opens, so a
new `Win` + `Tab` always starts from the full window list.

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
      $description: Accent color used for highlights, in #RRGGBB format. Used by the "Custom" theme.
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
      $description: Tint color of the overview panel, in #RRGGBB format. Used by the "Custom" theme.
    - BackgroundOpacity: 70
      $name: Background opacity
      $description: Strength of the panel tint drawn over the backdrop (0-100). 0 leaves the backdrop untouched, 100 is fully opaque.
    - ShowWindowIcons: true
      $name: Show window icons
      $description: Show each window's application icon in the card header.
    - AnimationSpeed: "100"
      $name: Animation speed
      $description: Relative speed of the open and close animations.
      $options:
      - "75": 75%
      - "100": 100%
      - "125": 125%
      - "150": 150%
  $name: Appearance
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
#include <cstring>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// COMPILATION-TIME NAMES AND MESSAGES

static const WCHAR kOverlayClass[] = L"OverhauldedWinTabOverlay";
static const WCHAR kControlClass[] = L"OverhauldedWinTabInput";
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

// Settings.
static UINT32 g_accent = 0xFF4CC2FF;
static BackgroundMode g_backgroundMode = BackgroundMode::Acrylic;
static UINT32 g_backgroundColor = 0xFF0A0D12;
static float g_backgroundOpacity = 0.70f;
static bool g_showIcons = true;
static int g_animSpeedPercent = 100;
static bool g_closeOnFocusLoss = true;
static bool g_wrapNavigation = true;
static bool g_vimNavigation = true;

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
static int g_selected = 0;
static int g_page = 0;
static bool g_focusStrip = false;
static int g_desktopSelected = 0;
static bool g_busy = false;
static bool g_trackingMouse = false;
static int g_hoverCard = -1;
static int g_hoverClose = -1;
static int g_hoverPill = -1;
static int g_hoverPillClose = -1;
static bool g_hoverCreate = false;
static bool g_hoverSearch = false;
static bool g_hoverSearchClear = false;

// Inline virtual desktop rename.
static int g_renameDesktop = -1;
static std::wstring g_renameText;

// Data model.
struct WindowEntry
{
    HWND hwnd = nullptr;
    DWORD pid = 0;
    std::wstring title;
    std::wstring titleLower;
    std::wstring app;
    std::wstring appLower;
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
    int entry = -1;
    RectF rect, header, preview, close;
};

struct PillView
{
    int desktop = -1;
    RectF rect, closeRect;
    bool hasClose = false;
};

static LayoutState g_layout;
static std::vector<CardView> g_cards;
static std::vector<PillView> g_pills;
static RectF g_createRect;
static RectF g_searchClearRect;

// DWM thumbnails.
static std::vector<HTHUMBNAIL> g_thumbHandles;
static std::vector<HWND> g_thumbSources;

// Hotkey plumbing.
static UINT g_hotkeyMessage = 0;

// Forward declarations.
static void ReleaseThumbnails();
static void BeginDesktopAction(int targetDesktop, bool create, bool closeActive);
static void RebuildWindowList();
static void RefreshDesktops();
static void MoveSelectedWindowToDesktop(int delta);
static void SwitchDesktopBy(int delta);
static void BeginRenameDesktop(int index);
static void CommitRenameDesktop();
static void CancelRenameDesktop();
static float BackgroundScrimAlpha();

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

    g_showIcons = Wh_GetIntSetting(L"Appearance.ShowWindowIcons") != 0;

    const std::wstring speed = read(L"Appearance.AnimationSpeed");
    g_animSpeedPercent = speed == L"75" ? 75 : speed == L"125" ? 125
                        : speed == L"150" ? 150 : 100;

    g_closeOnFocusLoss = Wh_GetIntSetting(L"Behavior.CloseOnFocusLoss") != 0;
    g_wrapNavigation = Wh_GetIntSetting(L"Behavior.WrapNavigation") != 0;
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

    IDWriteTextFormat* formats[] = {g_fmtTitle, g_fmtCard, g_fmtSearch,
                                    g_fmtPill, g_fmtHint, g_fmtEmpty};
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

    DWORD cloaked = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked,
                                        sizeof(cloaked))) &&
        cloaked != 0)
        return TRUE;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || pid == GetCurrentProcessId())
        return TRUE;

    if (!IsWindowOnCurrentDesktop(hwnd))
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
        g_selected = 0;
    else if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = static_cast<int>(g_filtered.size()) - 1;
    if (g_selected < 0)
        g_selected = 0;
}

static void RebuildWindowList()
{
    ReleaseIcons();
    g_windows.clear();
    EnumWindows(EnumWindowsProc, 0);
    RebuildFilter();
    g_page = 0;
    if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = g_filtered.empty() ? 0 : static_cast<int>(g_filtered.size()) - 1;
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
    if (g_overlay)
        SetTimer(g_overlay, kTimerCaret, 530, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static bool IsRenamingDesktop()
{
    return g_renameDesktop >= 0;
}

// --- Desktop actions --------------------------------------------------------

// Moves the selected window (or the window that opened the overview) to an
// adjacent virtual desktop using the documented IVirtualDesktopManager API.
static void MoveSelectedWindowToDesktop(int delta)
{
    if (!g_vdm || g_desktops.empty())
        return;

    const int target = g_currentDesktop + delta;
    if (target < 0 || target >= static_cast<int>(g_desktops.size()))
        return;

    HWND window = nullptr;
    if (g_selected >= 0 && g_selected < static_cast<int>(g_filtered.size()))
        window = g_windows[g_filtered[g_selected]].hwnd;
    if (!window || !IsWindow(window))
        window = g_originWindow;
    if (!window || !IsWindow(window))
        return;

    ReleaseThumbnails();
    if (SUCCEEDED(g_vdm->MoveWindowToDesktop(window, g_desktops[target].id)))
    {
        RebuildWindowList();
        g_desktopSelected = g_currentDesktop;
    }
    InvalidateRect(g_overlay, nullptr, FALSE);
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

static void BeginDesktopAction(int targetDesktop, bool create, bool closeActive)
{
    if (g_busy)
        return;

    ReleaseThumbnails();
    g_busy = true;

    if (create)
    {
        SendChord('D', false);
    }
    else if (closeActive)
    {
        if (g_desktops.size() > 1)
            SendChord(VK_F4, false);
    }
    else
    {
        const int delta = targetDesktop - g_currentDesktop;
        const int steps = std::min(std::abs(delta), 8);
        for (int i = 0; i < steps; i++)
            SendChord(delta > 0 ? VK_RIGHT : VK_LEFT, true);
    }

    if (g_overlay)
        SetTimer(g_overlay, kTimerDesktop, 700, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

////////////////////////////////////////////////////////////////////////////////
// LAYOUT

static void RebuildPills()
{
    g_pills.clear();
    const float s = g_scale;
    const float pillH = 42.0f * s;
    const float gap = 10.0f * s;
    const float createW = 42.0f * s;

    float nameWidths[64] = {};
    float totalPills = 0.0f;
    const int count = std::min<int>(static_cast<int>(g_desktops.size()),
                                    ARRAYSIZE(nameWidths));
    for (int i = 0; i < count; i++)
    {
        const bool renaming = g_renameDesktop == i;
        const std::wstring& shown = renaming ? g_renameText : g_desktops[i].name;
        const bool hasClose = g_desktops.size() > 1 && i == g_currentDesktop;

        // Badge + gaps + a name measured with the real font, plus caret room
        // while renaming.
        const float textW = MeasureTextWidth(shown, g_fmtPill);
        float w = 40.0f * s + textW + (hasClose ? 30.0f * s : 14.0f * s);
        if (renaming)
            w += 18.0f * s;
        const float maxW = renaming ? 460.0f * s : 320.0f * s;
        w = std::max(112.0f * s, std::min(maxW, w));
        nameWidths[i] = w;
        totalPills += w;
    }

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
        pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
        if (pill.hasClose)
            pill.closeRect = {pill.rect.r - 28.0f * s, pill.rect.t + 6.0f * s,
                              pill.rect.r - 6.0f * s, pill.rect.b - 6.0f * s};
        g_pills.push_back(pill);
        cursor += w + gap;
    }

    g_createRect = {cursor, y, cursor + createW, y + pillH};
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
    g_layout.search = {searchX, 44.0f * s, searchX + searchW, 44.0f * s + searchH};
    g_searchClearRect = {g_layout.search.r - 38.0f * s, g_layout.search.t + 6.0f * s,
                         g_layout.search.r - 8.0f * s, g_layout.search.b - 6.0f * s};

    const float stripH = 64.0f * s;
    const float stripBottom = g_layout.h - 46.0f * s;
    g_layout.strip = {margin, stripBottom - stripH, g_layout.w - margin, stripBottom};
    g_layout.grid = {margin, g_layout.search.b + 42.0f * s, g_layout.w - margin,
                     g_layout.strip.t - 32.0f * s};

    g_cards.clear();

    const int n = static_cast<int>(g_filtered.size());
    const float gap = 18.0f * s;
    g_layout.gap = gap;
    const float gridW = g_layout.grid.W();
    const float gridH = g_layout.grid.H();
    const float maxCardW = 400.0f * s;

    int cols = 0;
    float cardW = 0.0f, cardH = 0.0f;
    int rows = 0;
    for (int c = 1; c <= 10; c++)
    {
        const float w = std::min(maxCardW, (gridW - (c - 1) * gap) / c);
        const float h = w * 0.62f;
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
        cardH = cardW * 0.62f;
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

    const float headerH = 34.0f * s;
    const float pad = 8.0f * s;

    for (int i = 0; i < visible; i++)
    {
        const int col = i % cols;
        const int row = i / cols;
        const float left = x0 + col * (cardW + gap);
        const float top = y0 + row * (cardH + gap);

        CardView card;
        card.entry = g_filtered[start + i];
        card.rect = {left, top, left + cardW, top + cardH};
        card.header = {left, top, left + cardW, top + headerH};
        card.preview = {left + pad, top + headerH, left + cardW - pad, top + cardH - pad};

        const float closeSize = 24.0f * s;
        card.close = {left + cardW - pad - closeSize,
                      top + (headerH - closeSize) / 2.0f,
                      left + cardW - pad,
                      top + (headerH + closeSize) / 2.0f};
        g_cards.push_back(card);
    }

    RebuildPills();
}

////////////////////////////////////////////////////////////////////////////////
// DWM THUMBNAILS

static void ReleaseThumbnails()
{
    for (HTHUMBNAIL thumbnail : g_thumbHandles)
        if (thumbnail)
            DwmUnregisterThumbnail(thumbnail);
    g_thumbHandles.clear();
    g_thumbSources.clear();
}

static void SyncThumbnails(const std::vector<HWND>& sources,
                           const std::vector<RectF>& rects, float opacity)
{
    bool same = sources.size() == g_thumbSources.size();
    if (same)
    {
        for (size_t i = 0; i < sources.size(); i++)
            if (sources[i] != g_thumbSources[i])
            {
                same = false;
                break;
            }
    }

    if (!same)
    {
        ReleaseThumbnails();
        for (HWND source : sources)
        {
            HTHUMBNAIL thumbnail = nullptr;
            if (SUCCEEDED(DwmRegisterThumbnail(g_overlay, source, &thumbnail)))
                g_thumbHandles.push_back(thumbnail);
            else
                g_thumbHandles.push_back(nullptr);
        }
        g_thumbSources = sources;
    }

    const BYTE alpha =
        static_cast<BYTE>(std::max(0.0f, std::min(1.0f, opacity)) * 255.0f);
    const size_t count = std::min(g_thumbHandles.size(), rects.size());
    for (size_t i = 0; i < count; i++)
    {
        if (!g_thumbHandles[i])
            continue;
        DWM_THUMBNAIL_PROPERTIES properties = {};
        properties.dwFlags = DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE |
                             DWM_TNP_OPACITY | DWM_TNP_SOURCECLIENTAREAONLY;
        properties.rcDestination = ToRect(rects[i]);
        properties.fVisible = alpha > 6 ? TRUE : FALSE;
        properties.opacity = alpha;
        properties.fSourceClientAreaOnly = TRUE;
        DwmUpdateThumbnailProperties(g_thumbHandles[i], &properties);
    }
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

////////////////////////////////////////////////////////////////////////////////
// RENDER

static void RenderScene(HDC dc)
{
    RECT client = {};
    GetClientRect(g_overlay, &client);

    if (!EnsureFactories() || !EnsureDeviceResources())
        return;
    EnsureTextFormats();

    if (FAILED(g_d2dTarget->BindDC(dc, &client)))
        return;

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
    std::vector<HWND> thumbSources;
    std::vector<RectF> thumbRects;
    if (!g_busy && contentAlpha > 0.02f)
    {
        for (const CardView& card : g_cards)
        {
            if (card.entry < 0 || card.entry >= static_cast<int>(g_windows.size()))
                continue;
            HWND source = g_windows[card.entry].hwnd;
            if (!source || !IsWindow(source))
                continue;
            RectF preview = ScaleAbout(card.preview, sceneScale, cx, cy);
            preview.l += 1.0f;
            preview.t += 1.0f;
            preview.r -= 1.0f;
            preview.b -= 1.0f;
            thumbSources.push_back(source);
            thumbRects.push_back(preview);
        }
    }
    SyncThumbnails(thumbSources, thumbRects, contentAlpha);

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
    const RectF titleRect = {56.0f * s, 40.0f * s, 340.0f * s, 40.0f * s + 46.0f * s};
    DrawTextBlock(L"Task View", g_fmtTitle, titleRect, g_theme.text,
                  DWRITE_TEXT_ALIGNMENT_LEADING, 0.92f);

    // Search field.
    const float searchRadius = g_layout.search.H() / 2.0f;
    FillRound(g_layout.search, searchRadius, g_theme.searchFill, 0.95f);
    StrokeRound(g_layout.search, searchRadius,
                g_searchFocused ? g_theme.accent : g_theme.text, 1.25f * s,
                g_searchFocused ? 0.85f : 0.10f);

    // Magnifier glyph.
    {
        const float glyphX = g_layout.search.l + 22.0f * s;
        const float glyphY = g_layout.search.t + g_layout.search.H() / 2.0f;
        g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.55f));
        const D2D1_ELLIPSE circle =
            D2D1::Ellipse(D2D1::Point2F(glyphX, glyphY - 1.0f * s), 6.0f * s, 6.0f * s);
        g_d2dTarget->DrawEllipse(&circle, g_d2dBrush, 1.4f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(glyphX + 4.5f * s, glyphY + 3.5f * s),
                              D2D1::Point2F(glyphX + 9.0f * s, glyphY + 8.0f * s),
                              g_d2dBrush, 1.6f * s);
    }

    const float textLeft = g_layout.search.l + 42.0f * s;
    const float textRight = g_layout.search.r - (g_search.empty() ? 16.0f * s : 44.0f * s);
    const RectF searchTextRect = {textLeft, g_layout.search.t, textRight, g_layout.search.b};
    if (g_search.empty())
    {
        DrawTextBlock(L"Search windows", g_fmtSearch, searchTextRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING, 0.40f);
    }
    else
    {
        DrawTextBlock(g_search, g_fmtSearch, searchTextRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING, 0.96f);
        g_d2dBrush->SetColor(ColorOf(g_theme.text, g_hoverSearchClear ? 0.85f : 0.45f));
        const float ccx = g_searchClearRect.l + g_searchClearRect.W() / 2.0f;
        const float ccy = g_searchClearRect.t + g_searchClearRect.H() / 2.0f;
        const float arm = 5.0f * s;
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx - arm, ccy - arm),
                              D2D1::Point2F(ccx + arm, ccy + arm), g_d2dBrush, 1.5f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(ccx + arm, ccy - arm),
                              D2D1::Point2F(ccx - arm, ccy + arm), g_d2dBrush, 1.5f * s);
    }

    // Caret.
    if (g_searchFocused && ((GetTickCount64() / 530) % 2) == 0)
    {
        const float textW = MeasureTextWidth(g_search, g_fmtSearch);
        const float caretX = std::min(textRight, textLeft + textW + 1.0f * s);
        g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.85f));
        g_d2dTarget->DrawLine(D2D1::Point2F(caretX, g_layout.search.t + 12.0f * s),
                              D2D1::Point2F(caretX, g_layout.search.b - 12.0f * s),
                              g_d2dBrush, 1.4f * s);
    }

    // Window grid.
    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        const CardView& card = g_cards[i];
        const RectF rect = ScaleAbout(card.rect, sceneScale, cx, cy);
        const RectF header = ScaleAbout(card.header, sceneScale, cx, cy);
        const RectF preview = ScaleAbout(card.preview, sceneScale, cx, cy);
        const RectF closeRect = ScaleAbout(card.close, sceneScale, cx, cy);

        const bool isSelected = !g_focusStrip && card.entry == g_selected;
        const bool isHovered = g_hoverCard == i;
        const float radius = 10.0f * s;

        const RectF shadow = {rect.l, rect.t + 5.0f * s, rect.r, rect.b + 7.0f * s};
        FillRound(shadow, radius + 2.0f * s, 0xFF000000, 0.28f);

        const UINT32 fill =
            isSelected ? g_theme.cardSelected : (isHovered ? g_theme.cardHover : g_theme.cardFill);
        FillRound(rect, radius, fill, 1.0f);
        StrokeRound(rect, radius, isSelected ? g_theme.accent : g_theme.text, 1.4f * s,
                    isSelected ? 0.95f : (isHovered ? 0.16f : 0.08f));

        if (card.entry >= 0 && card.entry < static_cast<int>(g_windows.size()))
        {
            WindowEntry& entry = g_windows[card.entry];

            float textX = header.l + 14.0f * s;
            if (g_showIcons)
            {
                const int iconPixels = static_cast<int>(std::lround(18.0f * s));
                if (!entry.icon || entry.iconSize != static_cast<float>(iconPixels))
                {
                    if (entry.icon)
                    {
                        entry.icon->Release();
                        entry.icon = nullptr;
                    }
                    bool owned = false;
                    HICON hicon =
                        GetWindowIcon(entry.hwnd, GetProcessImagePath(entry.pid), &owned);
                    if (hicon)
                    {
                        entry.icon = CreateIconBitmap(hicon, iconPixels);
                        entry.iconSize = static_cast<float>(iconPixels);
                        if (owned)
                            DestroyIcon(hicon);
                    }
                }

                if (entry.icon)
                {
                    const float iconSize = 18.0f * s;
                    const float iconTop = header.t + (header.H() - iconSize) / 2.0f;
                    const D2D1_RECT_F dest =
                        D2D1::RectF(header.l + 12.0f * s, iconTop,
                                    header.l + 12.0f * s + iconSize, iconTop + iconSize);
                    g_d2dTarget->DrawBitmap(entry.icon, &dest, 1.0f,
                                            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
                    textX = header.l + 38.0f * s;
                }
            }

            const RectF titleRect = {textX, header.t,
                                     header.r - (g_hoverClose == i ? 34.0f * s : 12.0f * s),
                                     header.b};
            DrawTextBlock(entry.title, g_fmtCard, titleRect, g_theme.text,
                          DWRITE_TEXT_ALIGNMENT_LEADING, 0.94f);

            // Close button: header only, never over the DWM preview.
            if (g_hoverClose == i)
            {
                FillRound(closeRect, 5.0f * s, g_theme.danger, 0.9f);
                g_d2dBrush->SetColor(ColorOf(0xFFFFFFFF, 0.95f));
                const float arm = 4.6f * s;
                const float bcx = closeRect.l + closeRect.W() / 2.0f;
                const float bcy = closeRect.t + closeRect.H() / 2.0f;
                g_d2dTarget->DrawLine(D2D1::Point2F(bcx - arm, bcy - arm),
                                      D2D1::Point2F(bcx + arm, bcy + arm), g_d2dBrush,
                                      1.4f * s);
                g_d2dTarget->DrawLine(D2D1::Point2F(bcx + arm, bcy - arm),
                                      D2D1::Point2F(bcx - arm, bcy + arm), g_d2dBrush,
                                      1.4f * s);
            }

            // Preview frame; the DWM thumbnail is composed on top of it.
            FillRound(preview, 6.0f * s, g_theme.previewFill, 1.0f);
            StrokeRound(preview, 6.0f * s, g_theme.text, 1.0f * s, 0.07f);
        }
    }

    // Empty state.
    if (g_cards.empty() && !g_busy)
    {
        const std::wstring message = g_search.empty()
            ? L"No windows on this desktop"
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

    // Desktop strip.
    FillRound(g_layout.strip, 14.0f * s, g_theme.stripFill, 0.90f);
    StrokeRound(g_layout.strip, 14.0f * s, g_theme.text, 1.0f * s, 0.07f);

    for (int i = 0; i < static_cast<int>(g_pills.size()); i++)
    {
        const PillView& pill = g_pills[i];
        const bool active = pill.desktop == g_currentDesktop;
        const bool hovered = g_hoverPill == i;
        const bool selected = g_focusStrip && pill.desktop == g_desktopSelected;

        UINT32 fill = active ? g_theme.pillActive : g_theme.pillFill;
        if (hovered)
            fill = active ? g_theme.pillActiveHover : g_theme.pillHover;
        FillRound(pill.rect, 10.0f * s, fill, 1.0f);

        if (selected)
            StrokeRound(pill.rect, 10.0f * s, g_theme.accent, 2.0f * s, 0.95f);
        else
            StrokeRound(pill.rect, 10.0f * s,
                        active ? g_theme.accent : g_theme.text, 1.2f * s,
                        active ? 0.75f : 0.08f);

        const RectF badge = {pill.rect.l + 10.0f * s, pill.rect.t + 9.0f * s,
                             pill.rect.l + 34.0f * s, pill.rect.b - 9.0f * s};
        FillRound(badge, 6.0f * s, active ? g_theme.accent : g_theme.text,
                  active ? 0.9f : 0.12f);
        DrawTextBlock(std::to_wstring(pill.desktop + 1), g_fmtPill, badge,
                      active ? g_theme.onAccent : g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_CENTER, 0.95f);

        const bool renaming = g_renameDesktop == pill.desktop;
        const RectF nameRect = {pill.rect.l + 40.0f * s, pill.rect.t,
                                pill.rect.r - (pill.hasClose && !renaming ? 30.0f * s
                                                                         : 12.0f * s),
                                pill.rect.b};
        const std::wstring& shownName =
            renaming ? g_renameText : g_desktops[pill.desktop].name;
        DrawTextBlock(shownName, g_fmtPill, nameRect, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_LEADING,
                      (active || renaming) ? 0.95f : 0.72f);

        if (renaming && ((GetTickCount64() / 530) % 2) == 0)
        {
            const float textW = MeasureTextWidth(g_renameText, g_fmtPill);
            const float caretX = std::min(nameRect.r, nameRect.l + textW + 1.0f * s);
            g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.85f));
            g_d2dTarget->DrawLine(D2D1::Point2F(caretX, pill.rect.t + 11.0f * s),
                                  D2D1::Point2F(caretX, pill.rect.b - 11.0f * s),
                                  g_d2dBrush, 1.4f * s);
        }

        if (pill.hasClose && !renaming)
        {
            g_d2dBrush->SetColor(
                ColorOf(g_theme.text, g_hoverPillClose == i ? 0.95f : 0.45f));
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

    // Create-desktop button.
    FillRound(g_createRect, 10.0f * s,
              g_hoverCreate ? g_theme.pillActive : g_theme.pillFill, 1.0f);
    StrokeRound(g_createRect, 10.0f * s, g_theme.text, 1.2f * s, 0.10f);
    {
        g_d2dBrush->SetColor(ColorOf(g_theme.text, 0.80f));
        const float pcx = g_createRect.l + g_createRect.W() / 2.0f;
        const float pcy = g_createRect.t + g_createRect.H() / 2.0f;
        const float arm = 7.0f * s;
        g_d2dTarget->DrawLine(D2D1::Point2F(pcx - arm, pcy), D2D1::Point2F(pcx + arm, pcy),
                              g_d2dBrush, 1.6f * s);
        g_d2dTarget->DrawLine(D2D1::Point2F(pcx, pcy - arm), D2D1::Point2F(pcx, pcy + arm),
                              g_d2dBrush, 1.6f * s);
    }

    // Hint line.
    const RectF hintRect = {56.0f * s, g_layout.strip.b + 10.0f * s,
                            g_layout.w - 56.0f * s, g_layout.strip.b + 34.0f * s};
    std::wstring hint;
    if (IsRenamingDesktop())
        hint = L"Rename desktop  \u00B7  Enter save  \u00B7  Esc cancel";
    else if (g_focusStrip)
        hint = L"Enter switch  \u00B7  F2 rename  \u00B7  N new  \u00B7  Delete close  "
               L"\u00B7  Ctrl+Left/Right switch  \u00B7  Tab windows";
    else
        hint = L"Enter switch  \u00B7  Delete close  \u00B7  Shift+Left/Right move to "
               L"desktop  \u00B7  Tab desktops  \u00B7  / search";
    DrawTextBlock(hint, g_fmtHint, hintRect, g_theme.text, DWRITE_TEXT_ALIGNMENT_LEADING,
                  0.42f);

    // Busy indicator (desktop switching).
    if (g_busy)
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
    g_search.clear();
    g_searchFocused = false;
    g_renameDesktop = -1;
    g_renameText.clear();
    g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
    g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;
    g_busy = false;

    RefreshDesktops();
    RebuildWindowList();
    g_desktopSelected = g_currentDesktop;

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
    ReleaseThumbnails();
    StopOverlayTimers();
    if (g_overlay)
        ShowWindow(g_overlay, SW_HIDE);
    g_visible = false;
    g_presence = 0.0f;
    g_targetPresence = 0.0f;
    g_busy = false;
    SetControlReady(true);
}

static void HideOverlay(bool immediate)
{
    if (!g_visible)
        return;

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

static void ActivateEntry(int filteredIndex)
{
    if (filteredIndex < 0 || filteredIndex >= static_cast<int>(g_filtered.size()))
        return;
    HWND target = g_windows[g_filtered[filteredIndex]].hwnd;
    if (!target || !IsWindow(target))
        return;

    g_closingForActivation = true;
    HideOverlay(true);
    g_closingForActivation = false;

    if (IsIconic(target))
        ShowWindow(target, SW_RESTORE);

    if (!SetForegroundWindow(target))
        SwitchToThisWindow(target, TRUE);
}

static void CloseEntry(int filteredIndex)
{
    if (filteredIndex < 0 || filteredIndex >= static_cast<int>(g_filtered.size()))
        return;
    HWND target = g_windows[g_filtered[filteredIndex]].hwnd;
    if (!target || !IsWindow(target))
        return;

    PostMessageW(target, WM_CLOSE, 0, 0);

    // Remove the entry immediately and keep the overlay open.
    ReleaseThumbnails();
    const int removed = g_filtered[filteredIndex];
    g_windows.erase(g_windows.begin() + removed);
    RebuildFilter();
    if (g_selected >= static_cast<int>(g_filtered.size()))
        g_selected = g_filtered.empty() ? 0 : static_cast<int>(g_filtered.size()) - 1;

    if (g_overlay)
        SetTimer(g_overlay, kTimerIdle, 700, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void MoveSelection(int dx, int dy)
{
    const int count = static_cast<int>(g_filtered.size());
    if (count == 0)
        return;

    const int cols = std::max(1, g_layout.cols);
    int index = g_selected;

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
        index += dy * cols;
        if (index < 0 || index >= count)
        {
            if (!g_wrapNavigation)
                index = g_selected;
        }
    }

    g_selected = std::max(0, std::min(count - 1, index));
    g_page = g_selected / std::max(1, g_layout.perPage);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void SetSearch(const std::wstring& text)
{
    g_search = text;
    RebuildFilter();
    g_selected = 0;
    g_page = 0;
    InvalidateRect(g_overlay, nullptr, FALSE);
}

static void FocusSearch()
{
    g_searchFocused = true;
    g_focusStrip = false;
    if (g_overlay)
        SetTimer(g_overlay, kTimerCaret, 530, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
}

////////////////////////////////////////////////////////////////////////////////
// INPUT

static void UpdateHover(int x, int y)
{
    g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
    g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;

    if (Contains(g_layout.search, static_cast<float>(x), static_cast<float>(y)))
        g_hoverSearch = true;
    if (!g_search.empty() &&
        Contains(g_searchClearRect, static_cast<float>(x), static_cast<float>(y)))
        g_hoverSearchClear = true;

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        if (Contains(g_cards[i].rect, static_cast<float>(x), static_cast<float>(y)))
        {
            g_hoverCard = i;
            if (Contains(g_cards[i].close, static_cast<float>(x), static_cast<float>(y)))
                g_hoverClose = i;
            break;
        }
    }

    for (int i = 0; i < static_cast<int>(g_pills.size()); i++)
    {
        if (Contains(g_pills[i].rect, static_cast<float>(x), static_cast<float>(y)))
        {
            g_hoverPill = i;
            if (g_pills[i].hasClose &&
                Contains(g_pills[i].closeRect, static_cast<float>(x), static_cast<float>(y)))
                g_hoverPillClose = i;
            break;
        }
    }

    if (Contains(g_createRect, static_cast<float>(x), static_cast<float>(y)))
        g_hoverCreate = true;
}

static void OnLeftClick(int x, int y)
{
    const float fx = static_cast<float>(x);
    const float fy = static_cast<float>(y);

    if (IsRenamingDesktop())
    {
        for (const PillView& pill : g_pills)
        {
            if (pill.desktop == g_renameDesktop && Contains(pill.rect, fx, fy))
                return;  // Clicking the field keeps editing.
        }
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

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        if (!Contains(g_cards[i].rect, fx, fy))
            continue;
        if (g_hoverClose == i)
            CloseEntry(g_cards[i].entry);
        else
        {
            g_selected = g_cards[i].entry;
            ActivateEntry(g_cards[i].entry);
        }
        return;
    }

    for (int i = 0; i < static_cast<int>(g_pills.size()); i++)
    {
        if (!Contains(g_pills[i].rect, fx, fy))
            continue;

        if (g_pills[i].hasClose && Contains(g_pills[i].closeRect, fx, fy))
        {
            BeginDesktopAction(-1, false, true);
            return;
        }

        g_focusStrip = true;
        g_desktopSelected = g_pills[i].desktop;
        if (g_pills[i].desktop != g_currentDesktop)
            BeginDesktopAction(g_pills[i].desktop, false, false);
        else
            InvalidateRect(g_overlay, nullptr, FALSE);
        return;
    }

    if (Contains(g_createRect, fx, fy))
    {
        BeginDesktopAction(-1, true, false);
        return;
    }
}

static void OnKeyDown(WPARAM key)
{
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

    const bool shift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    const bool ctrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;

    // While the search field has focus, only editing keys are meaningful; this
    // keeps Delete/arrows/etc. from triggering actions mid-query.
    if (g_searchFocused)
    {
        if (key == VK_ESCAPE)
        {
            SetSearch(L"");
            g_searchFocused = false;
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        else if (key == VK_RETURN)
        {
            ActivateEntry(g_selected);
        }
        else if (key == VK_BACK && !g_search.empty())
        {
            SetSearch(g_search.substr(0, g_search.size() - 1));
        }
        return;
    }

    switch (key)
    {
    case VK_ESCAPE:
        if (g_searchFocused || !g_search.empty())
        {
            SetSearch(L"");
            g_searchFocused = false;
            InvalidateRect(g_overlay, nullptr, FALSE);
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
        else
        {
            ActivateEntry(g_selected);
        }
        return;

    case VK_DELETE:
        if (g_focusStrip)
            BeginDesktopAction(-1, false, true);
        else
            CloseEntry(g_selected);
        return;

    case VK_F2:
        BeginRenameDesktop(g_focusStrip ? g_desktopSelected : g_currentDesktop);
        return;

    case VK_TAB:
        g_focusStrip = !g_focusStrip;
        if (g_focusStrip)
            g_desktopSelected = g_currentDesktop;
        InvalidateRect(g_overlay, nullptr, FALSE);
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
            g_desktopSelected = std::max(0, g_desktopSelected - 1);
            InvalidateRect(g_overlay, nullptr, FALSE);
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
            g_desktopSelected = std::min(static_cast<int>(g_desktops.size()) - 1,
                                         g_desktopSelected + 1);
            InvalidateRect(g_overlay, nullptr, FALSE);
        }
        else
        {
            MoveSelection(1, 0);
        }
        return;

    case VK_UP:
        if (!g_focusStrip)
            MoveSelection(0, -1);
        return;

    case VK_DOWN:
        if (!g_focusStrip)
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

    default:
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////
// WINDOW PROCEDURES

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
        UpdateHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }

    case WM_MOUSELEAVE:
        g_trackingMouse = false;
        g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
        g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_LBUTTONUP:
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        UpdateHover(x, y);
        OnLeftClick(x, y);
        return 0;
    }

    case WM_RBUTTONUP:
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        for (const PillView& pill : g_pills)
        {
            if (!Contains(pill.rect, static_cast<float>(x), static_cast<float>(y)))
                continue;
            if (IsRenamingDesktop())
            {
                if (pill.desktop == g_renameDesktop)
                    return 0;  // Already editing this desktop.
                CommitRenameDesktop();
            }
            BeginRenameDesktop(pill.desktop);
            break;
        }
        return 0;
    }

    case WM_MBUTTONUP:
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        for (const CardView& card : g_cards)
        {
            if (Contains(card.rect, static_cast<float>(x), static_cast<float>(y)))
            {
                CloseEntry(card.entry);
                break;
            }
        }
        return 0;
    }

    case WM_MOUSEWHEEL:
    {
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

        bool overText = Contains(g_layout.search, fx, fy) && !g_search.empty();
        if (!overText && IsRenamingDesktop())
        {
            for (const PillView& pill : g_pills)
            {
                if (pill.desktop == g_renameDesktop && Contains(pill.rect, fx, fy))
                {
                    overText = true;
                    break;
                }
            }
        }

        const bool interactive = g_hoverCard >= 0 || g_hoverPill >= 0 || g_hoverCreate ||
                                 g_hoverSearch || g_hoverClose >= 0 ||
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

        // The search field has to be focused first (click it or press '/'); until
        // then, printable keys are available to navigation commands only.
        if (!g_searchFocused)
        {
            if (ch == L'/')
            {
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
                {
                    g_desktopSelected = std::max(0, g_desktopSelected - 1);
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
                else
                    MoveSelection(-1, 0);
                return 0;
            case L'l':
                if (g_focusStrip)
                {
                    g_desktopSelected =
                        std::min(static_cast<int>(g_desktops.size()) - 1,
                                 g_desktopSelected + 1);
                    InvalidateRect(hwnd, nullptr, FALSE);
                }
                else
                    MoveSelection(1, 0);
                return 0;
            case L'j':
                if (!g_focusStrip)
                    MoveSelection(0, 1);
                return 0;
            case L'k':
                if (!g_focusStrip)
                    MoveSelection(0, -1);
                return 0;
            case L'x':
                if (!g_focusStrip)
                    CloseEntry(g_selected);
                return 0;
            default:
                return 0;
            }
        }

        SetSearch(g_search + ch);
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

            if (g_presence >= 1.0f && !g_busy)
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
            KillTimer(hwnd, kTimerDesktop);
            g_busy = false;
            RefreshDesktops();
            RebuildWindowList();
            g_desktopSelected = g_currentDesktop;
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
    if (g_hotkeyMessage != 0 && message == g_hotkeyMessage &&
        wParam == kHotkeyFlagWinTab)
    {
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

    return true;
}

static void UnregisterWindowClasses()
{
    UnregisterClassW(kOverlayClass, g_hModule);
    UnregisterClassW(kControlClass, g_hModule);
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
    ReleaseThumbnails();
    StopOverlayTimers();
    ReleaseGraphics();

    if (g_control)
    {
        SetWindowTextW(g_control, kControlTitleIdle);
        DestroyWindow(g_control);
        g_control = nullptr;
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

    g_windows.clear();
    g_filtered.clear();
    g_desktops.clear();
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
                // The accent blur only takes effect while the overlay is hidden
                // (see ApplyBackdrop), so re-applying it to a visible overlay
                // would leave the flat fill behind it. It is applied on the next
                // ShowOverlay() instead.
                if (g_overlay && !g_visible)
                    ApplyBackdrop(g_overlay);
                if (g_overlay)
                    InvalidateRect(g_overlay, nullptr, FALSE);
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
