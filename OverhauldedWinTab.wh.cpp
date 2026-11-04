// ==WindhawkMod==
// @id              overhaulded-win-tab
// @name            OverhauldedWinTab
// @description     Replaces the Windows 11 Task View (Win+Tab) with a modern, focused overview of your windows and virtual desktops.
// @version         0.9.0
// @author          Andres Eufrasio
// @github          https://github.com/Andres-Eufrasio
// @homepage        https://github.com/Andres-Eufrasio/OverhauldedWinTab
// @include         windhawk.exe
// @include         explorer.exe
// @compilerOptions -lshell32 -lole32 -lgdi32 -luser32 -ladvapi32 -lshcore -lversion -ldwmapi -ld2d1 -ldwrite -lwindowscodecs
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# OverhauldedWinTab

OverhauldedWinTab replaces Windows 11 Task View (`Win+Tab`) with a window
overview and a virtual desktop strip. Open windows from live previews, and
search or move windows and desktops without closing the overview.

![Saiki K and Yu-Gi-Oh! card artwork](docs/theme-previews.png)

## Controls

| Action | Keys |
| --- | --- |
| Open or close the overview | `Win+Tab` |
| Navigate | Arrow keys, or `h` `j` `k` `l` with Vim navigation |
| Cycle grid, held dock and desktop strip | `Tab` |
| Open the selected window or switch desktop | `Enter` |
| Search the current / all desktops | `/` / `?` |
| Switch desktop | `1`–`9`, `Ctrl+Left` / `Ctrl+Right` |
| Move the selected window | `Shift+1`–`Shift+9`, `Shift+Left` / `Shift+Right`, or `M` then a number |
| Hold or release a window | `U`, or right-click a window |
| Close a window or desktop | `Delete`, or middle-click a window |
| Rename or create a desktop | `F2` or right-click a tab; `N` or click the create tab |

Click a window to open it, click a desktop tab to switch, and scroll to page
through windows. `Esc` leaves search or the held dock first; a second press
closes the overview.

## Settings

- **Window tabs**: square previews or poker chips showing a live preview, app
  icon or title, in four sizes and several color modes.
- **Desktop strip**: flat or carousel layout with pill, chip or playing-card
  tabs, optional tucked cards, and create/close animations.
- **Card art**: built-in vector themes (Yu-Gi-Oh!, Pokémon, Kakegurui and Saiki
  K) or custom 2:3 portrait PNG/JPG faces.
- **Held windows**: keep windows with you across desktops, in the grid or in a
  left/right dock.
- **Theme**: built-in palettes (Catppuccin, Nord, Dracula) or custom colors,
  with Acrylic, Mica, Blur, solid or transparent backgrounds.
- **Other**: search visibility, shortcut hints, animation speed, wrap-around
  navigation and hover/selection lift.

Search by window title or app. All-desktop results show a `D#` label and use app
icons where live previews are unavailable; selecting one switches to its
desktop first.

## Compatibility

Windows 11 only. The overview appears on the active monitor. Mods that also
replace Task View or intercept `Win+Tab` may conflict.

`build.ps1` performs a local compile check; see
[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for implementation details.

## License

MIT. See [LICENSE](LICENSE).
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
    - Tucked: false
      $name: Tuck playing cards
      $description: Show the upper half of playing-card desktop tabs at the bottom of the screen, like cards held in your hand.
    - DesignPath: ""
      $name: Card design image path
      $description: Optional absolute path to a PNG or JPG used as the playing-card face. Recommended aspect ratio is 2:3 (for example 800x1200).
    - BackDesignPath: ""
      $name: Card back image path
      $description: Optional absolute path to a PNG or JPG used on the face-down create card. Recommended aspect ratio is 2:3.
    - HideSuitsWithDesign: false
      $name: Hide suit symbols with card design
      $description: Hide the default suit symbols when a card design image is loaded.
    - TextX: ""
      $name: Card text X offset
      $description: Optional offset from the card's top-right corner in pixels. Entering X or Y replaces the default centered text position.
    - TextY: ""
      $name: Card text Y offset
      $description: Optional downward offset from the card's top edge in pixels.
    - Theme: "default"
      $name: Card theme
      $description: Built-in vector card artwork and matching chip colors. Optional image paths override the built-in face or back.
      $options:
      - "default": Default
      - "yugioh": Yu-Gi-Oh!
      - "pokemon": Pokémon
      - "kakegurui": Kakegurui
      - "saiki-k": Saiki K
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
#include <wincodec.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <tlhelp32.h>
#include <windowsx.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
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

// Escape and Enter are registered directly on the overlay while it is visible.
// That keeps them working even if the shell briefly takes the foreground during
// a desktop switch, when the overlay is visible but no longer receives
// WM_KEYDOWN. Registering Enter also stops a repeated/new Enter from reaching
// the window that took focus and opening it.
static const int kHotkeyEscape = 0x4F57;
static const int kHotkeyReturn = 0x4F58;

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
    kTimerReturnRelease = 7,
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
static bool g_tuckCards = false;
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
// Active desktop when the overview opened. Closing after navigating elsewhere
// must not foreground a window from that old desktop, even if it was a held
// task that followed the user.
static GUID g_originDesktopId = {};
static bool g_hasOriginDesktopId = false;
static bool g_closingForActivation = false;
// One physical Enter press must produce one action. Windows auto-repeats a held
// Enter, and the key must keep being swallowed until it is released or the
// window that regains focus after a hide will receive the repeat and open.
static bool g_returnKeyLatch = false;
// Enter on a desktop tab asks for a desktop, not a window, so hiding for it
// must not foreground the window that was active before the overview opened.
static bool g_desktopEnterHide = false;

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
// A mouse hover owns the visible window-grid focus until keyboard navigation
// resumes. g_selected remains the navigation anchor, so the first arrow/vim
// move starts at the last window the pointer visited rather than a stale card.
static bool g_pointerWindowSelection = false;
static bool g_hoverCreate = false;
static bool g_hoverSearch = false;
static bool g_hoverSearchClear = false;
// Arrow/vim navigation takes ownership of the grid until the pointer actually
// changes position. This prevents an old WM_MOUSEMOVE at the same coordinates
// from immediately restoring hover focus over the keyboard selection.
static bool g_ignorePointerUntilMoved = false;
static bool g_hasLastPointerPosition = false;
static POINT g_lastPointerPosition = {};
static bool g_createDragging = false;
static POINT g_createDragStart = {};
static float g_createPull = 0.0f;
static int g_windowDragEntry = -1;
static POINT g_windowDragStart = {};
static POINT g_windowDragCursor = {};
static ULONGLONG g_windowDragStarted = 0;
static bool g_windowDragging = false;
static int g_windowDragTargetDesktop = -1;
static bool g_windowDropAnimating = false;
static HWND g_windowDropWindow = nullptr;
static int g_windowDropTargetDesktop = -1;
static ULONGLONG g_windowDropStarted = 0;
static float g_windowDropDuration = 0.34f;

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
static int g_desktopActionStartIndex = -1;
static ULONGLONG g_busySince = 0;
static bool g_keepThumbnailsWhileBusy = false;
static float g_carouselPos = 0.0f;
// Small even carousels keep fixed slots instead of wrapping past each other.
static int g_carouselAnchor = 0;
static ULONGLONG g_lastCarouselTick = 0;

// Direct2D / DirectWrite.
static ID2D1Factory* g_d2dFactory = nullptr;
static ID2D1DCRenderTarget* g_d2dTarget = nullptr;
static ID2D1SolidColorBrush* g_d2dBrush = nullptr;
static ID2D1Layer* g_d2dLayer = nullptr;
static ID2D1Bitmap* g_cardDesignBitmap = nullptr;
static std::wstring g_loadedCardDesignPath;
static std::wstring g_cardDesignPath;
static ID2D1Bitmap* g_cardBackBitmap = nullptr;
static std::wstring g_loadedCardBackPath;
static std::wstring g_cardBackPath;
static bool g_hideCardSuitsWithDesign = false;
static bool g_cardTextPositionCustom = false;
static int g_cardTextX = 0;
static int g_cardTextY = 0;
static std::wstring g_cardTheme = L"default";
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
static CardView g_windowDropCard;

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
    // Capture the presentation at animation start. A settings reload while a
    // card is flying must not make it switch back to the default face.
    std::wstring cardTheme = L"default";
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
static bool MoveWindowEntryToDesktopIndex(HWND window, int index);
static void ToggleHold();
static void StartHeldWatch();
static void StopHeldWatch();
static bool MoveWindowToDesktopInternal(HWND window, const GUID& id);
static void SwitchDesktopBy(int delta);
static void BeginRenameDesktop(int index);
static void CommitRenameDesktop();
static void CancelRenameDesktop();
static void KickCarousel();
static void ResetCarouselPosition(int desktop, int count);
static void ClearWindowDrag();
static void ClearWindowDropAnimation();
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

static void ReleaseCardDesignBitmap()
{
    if (g_cardDesignBitmap)
    {
        g_cardDesignBitmap->Release();
        g_cardDesignBitmap = nullptr;
    }
    g_loadedCardDesignPath.clear();
    if (g_cardBackBitmap)
    {
        g_cardBackBitmap->Release();
        g_cardBackBitmap = nullptr;
    }
    g_loadedCardBackPath.clear();
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
    g_tuckCards = Wh_GetIntSetting(L"Cards.Tucked") != 0;
    const std::wstring designPath = read(L"Cards.DesignPath");
    if (designPath != g_cardDesignPath)
    {
        g_cardDesignPath = designPath;
        ReleaseCardDesignBitmap();
    }
    const std::wstring backDesignPath = read(L"Cards.BackDesignPath");
    if (backDesignPath != g_cardBackPath)
    {
        g_cardBackPath = backDesignPath;
        ReleaseCardDesignBitmap();
    }
    g_hideCardSuitsWithDesign =
        Wh_GetIntSetting(L"Cards.HideSuitsWithDesign") != 0;

    auto parseOffset = [](const std::wstring& value, int& result) {
        if (value.empty())
            return false;
        WCHAR* end = nullptr;
        const long parsed = std::wcstol(value.c_str(), &end, 10);
        if (end == value.c_str() || *end != L'\0')
            return false;
        result = static_cast<int>(std::max(-2000L, std::min(2000L, parsed)));
        return true;
    };
    int textX = 0;
    int textY = 0;
    const bool hasTextX = parseOffset(read(L"Cards.TextX"), textX);
    const bool hasTextY = parseOffset(read(L"Cards.TextY"), textY);
    g_cardTextPositionCustom = hasTextX || hasTextY;
    g_cardTextX = hasTextX ? textX : 0;
    g_cardTextY = hasTextY ? textY : 0;
    g_cardTheme = read(L"Cards.Theme");
    if (g_cardTheme != L"yugioh" && g_cardTheme != L"pokemon" &&
        g_cardTheme != L"kakegurui" && g_cardTheme != L"saiki-k")
        g_cardTheme = L"default";

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
    ReleaseCardDesignBitmap();
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

static void ReleaseVectorCardArt();

static void ReleaseGraphics()
{
    ReleaseDeviceResources();
    ReleaseTextFormats();
    ReleaseVectorCardArt();
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

static ID2D1Bitmap* EnsureBitmapFromPath(const std::wstring& path,
                                         ID2D1Bitmap*& bitmap,
                                         std::wstring& loadedPath)
{
    if (!g_d2dTarget || path.empty())
        return nullptr;
    if (bitmap && loadedPath == path)
        return bitmap;

    if (bitmap)
    {
        bitmap->Release();
        bitmap = nullptr;
    }
    loadedPath = path;

    IWICImagingFactory* factory = nullptr;
    IWICBitmapDecoder* decoder = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICFormatConverter* converter = nullptr;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory))) ||
        FAILED(factory->CreateDecoderFromFilename(
            path.c_str(), nullptr, GENERIC_READ,
            WICDecodeMetadataCacheOnLoad, &decoder)) ||
        FAILED(decoder->GetFrame(0, &frame)) ||
        FAILED(factory->CreateFormatConverter(&converter)) ||
        FAILED(converter->Initialize(
            frame, GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone, nullptr, 0.0f,
            WICBitmapPaletteTypeMedianCut)) ||
        FAILED(g_d2dTarget->CreateBitmapFromWicBitmap(
            converter, nullptr, &bitmap)))
    {
        if (converter) converter->Release();
        if (frame) frame->Release();
        if (decoder) decoder->Release();
        if (factory) factory->Release();
        bitmap = nullptr;
        return nullptr;
    }

    converter->Release();
    frame->Release();
    decoder->Release();
    factory->Release();
    return bitmap;
}

static ID2D1Bitmap* EnsureCardDesignBitmap()
{
    return EnsureBitmapFromPath(g_cardDesignPath, g_cardDesignBitmap,
                                g_loadedCardDesignPath);
}

static ID2D1Bitmap* EnsureCardBackBitmap()
{
    return EnsureBitmapFromPath(g_cardBackPath, g_cardBackBitmap,
                                g_loadedCardBackPath);
}

static void DrawBitmapCover(ID2D1Bitmap* bitmap, const RectF& bounds, float alpha)
{
    if (!bitmap)
        return;

    const D2D1_SIZE_F source = bitmap->GetSize();
    const RectF image = bounds;
    const float scale = std::max(image.W() / source.width,
                                 image.H() / source.height);
    const float drawW = source.width * scale;
    const float drawH = source.height * scale;
    const float cx = (image.l + image.r) / 2.0f;
    const float cy = (image.t + image.b) / 2.0f;
    const D2D1_RECT_F destination = D2D1::RectF(
        cx - drawW / 2.0f, cy - drawH / 2.0f,
        cx + drawW / 2.0f, cy + drawH / 2.0f);
    g_d2dTarget->PushAxisAlignedClip(
        D2D1::RectF(image.l, image.t, image.r, image.b),
        D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_d2dTarget->DrawBitmap(bitmap, &destination, alpha,
                            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
    g_d2dTarget->PopAxisAlignedClip();
}

static void DrawCardDesign(const RectF& face, float alpha)
{
    const RectF image = {face.l + 2.0f * g_scale, face.t + 2.0f * g_scale,
                         face.r - 2.0f * g_scale, face.b - 2.0f * g_scale};
    DrawBitmapCover(EnsureCardDesignBitmap(), image, alpha);
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
    const size_t previousCount = g_desktops.size();
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
    if (g_desktops.size() != previousCount)
        ResetCarouselPosition(g_currentDesktop, static_cast<int>(g_desktops.size()));
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
static bool MoveWindowEntryToDesktopIndex(HWND window, int index)
{
    if (!window || !IsWindow(window) || g_desktops.empty() ||
        index < 0 || index >= static_cast<int>(g_desktops.size()))
        return false;

    if (g_vdm)
    {
        GUID current = {};
        if (SUCCEEDED(g_vdm->GetWindowDesktopId(window, &current)) &&
            IsEqualGUID(current, g_desktops[index].id))
            return false;
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
    return moved;
}

static void MoveSelectedWindowToDesktopIndex(int index)
{
    if (g_desktops.empty())
        return;
    if (index < 0 || index >= static_cast<int>(g_desktops.size()))
        return;
    // While the desktop strip owns the keyboard, number keys switch desktops.
    // Never move a window from a desktop-tab interaction.
    if (g_focusStrip)
        return;

    HWND window = SelectedWindow();
    if (!window)
        return;

    MoveWindowEntryToDesktopIndex(window, index);
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

// Create a desktop without the Win+Ctrl+D transition. The shell's internal
// CreateDesktop method adds the desktop without switching; the existing
// SwitchDesktop method is the non-animated switch (the animated variant is a
// later vtable method). Keep the shortcut as a fallback for older builds.
static bool CreateDesktopWithoutSlide()
{
    IUnknown* manager = DesktopManagerInternal();
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    if (!manager || !ntdll)
        return false;

    typedef LONG(WINAPI * RtlGetVersionFn)(OSVERSIONINFOW*);
    auto getVersion = reinterpret_cast<RtlGetVersionFn>(
        GetProcAddress(ntdll, "RtlGetVersion"));
    OSVERSIONINFOW version = {};
    version.dwOSVersionInfoSize = sizeof(version);
    if (!getVersion || getVersion(&version) < 0)
        return false;

    // 24H2 inserted SwitchDesktopAndMoveForegroundView before CreateDesktop.
    const int createSlot = version.dwBuildNumber >= 26100 ? 11 :
                           version.dwBuildNumber >= 22621 ? 10 : -1;
    if (createSlot < 0)
        return false;

    typedef HRESULT(STDMETHODCALLTYPE * CreateFn)(void*, IUnknown**);
    typedef HRESULT(STDMETHODCALLTYPE * SwitchFn)(void*, void*);
    void** vtbl = *reinterpret_cast<void***>(manager);
    IUnknown* desktop = nullptr;
    const HRESULT createHr =
        reinterpret_cast<CreateFn>(vtbl[createSlot])(manager, &desktop);
    if (FAILED(createHr) || !desktop)
        return false;

    const HRESULT switchHr =
        reinterpret_cast<SwitchFn>(vtbl[9])(manager, desktop);
    desktop->Release();
    if (FAILED(switchHr))
    {
        // The desktop was created, so don't send Win+Ctrl+D again. Move to the
        // new adjacent desktop as a best-effort fallback.
        SendChord(VK_RIGHT, true);
    }
    return true;
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

// Keep two- and four-desktop carousels in stable slots for the entire session.
// Preserve the initial wheel order around the active desktop; navigation only
// moves the centre, never a neighbour to the other side of the wheel.
static float CarouselDesktopPosition(int desktop, int count)
{
    if (count != 2 && count != 4)
        return static_cast<float>(desktop);
    int slot = (desktop - g_carouselAnchor + count) % count;
    if (slot > count / 2)
        slot -= count;
    return static_cast<float>(slot);
}

static void ResetCarouselPosition(int desktop, int count)
{
    g_carouselAnchor = desktop;
    g_carouselPos = CarouselDesktopPosition(desktop, count);
}

// Signed distance from the carousel position to a desktop or animation target.
// Two and four desktops must not wrap: tabs keep their left/right order
// throughout the animation, including its final frame. Other wheels take the
// shortest path, wrapped into (-count/2, count/2].
static float WrapDelta(float value, int count)
{
    if (count <= 1)
        return 0.0f;
    if (count == 2 || count == 4)
        return value;
    const float n = static_cast<float>(count);
    float d = std::fmod(value, n);
    if (d < 0.0f)
        d += n;
    if (d > n / 2.0f)
        d -= n;
    return d;
}

static bool AdvanceCarousel(int desktop, int count, float blend)
{
    const float targetPos = CarouselDesktopPosition(desktop, count);
    const float delta = WrapDelta(targetPos - g_carouselPos, count);
    g_carouselPos += delta * std::min(1.0f, blend);
    if (std::fabs(delta) >= 0.002f)
        return false;
    g_carouselPos = targetPos;
    return true;
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
    if (g_cardTheme != L"default")
    {
        static const UINT32 yugioh[] = {0xFF6B2817, 0xFFD99A35,
                                         0xFF32130D, 0xFFB84E25};
        static const UINT32 pokemon[] = {0xFFD62828, 0xFF244F9A,
                                          0xFFF0B429, 0xFF3A8D5D};
        static const UINT32 kakegurui[] = {0xFF171717, 0xFF8E1B2A,
                                            0xFFD4AF37, 0xFF5A0F1B};
        static const UINT32 saikiK[] = {0xFFE60012, 0xFF221815,
                                        0xFF5AC8A8, 0xFFEF6F9F};
        const UINT32* colors = g_cardTheme == L"yugioh" ? yugioh
                             : g_cardTheme == L"pokemon" ? pokemon
                             : g_cardTheme == L"kakegurui" ? kakegurui : saikiK;
        const size_t count = g_cardTheme == L"yugioh"
                                 ? ARRAYSIZE(yugioh)
                                 : g_cardTheme == L"pokemon"
                                       ? ARRAYSIZE(pokemon)
                                  : g_cardTheme == L"kakegurui"
                                        ? ARRAYSIZE(kakegurui)
                                        : ARRAYSIZE(saikiK);
        return colors[static_cast<size_t>(index) % count];
    }

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
    return g_stripStyle == StripStyle::Flat && !(UsesCards() && g_tuckCards);
}

static float DesktopHighlightStrength(bool selected, bool active)
{
    if (g_desktopSelection != DesktopSelection::Highlight)
        return 0.0f;
    return selected ? 1.0f : (active ? 0.70f : 0.0f);
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
    g_desktopActionStartIndex = g_currentDesktop;
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
    if (switching && g_overlay && !g_createAfterDraw)
    {
        // Keep the last composed frame on screen while Explorer performs the
        // switch. Repainting thumbnails and the carousel during the shell
        // transition is the main source of visible stutter.
        KillTimer(g_overlay, kTimerFrame);
        KillTimer(g_overlay, kTimerCarousel);
    }
    else
    {
        KickCarousel();
        KickCardAnimation();
    }
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
    const float cardScale = g_cardScale * (g_tuckCards ? 1.18f : 1.0f);
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
            const float d = WrapDelta(CarouselDesktopPosition(i, count) -
                                          g_carouselPos, count);
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
                const float py = (g_tuckCards ? g_layout.h : cy) +
                                 std::min(12.0f * s, 2.5f * s * d * d);
                pill.rect = {px - cardW / 2.0f, py - cardH / 2.0f,
                             px + cardW / 2.0f, py + cardH / 2.0f};
                pill.hit = TransformedBounds(pill.rect, pill.scale, pill.angle);

                if (pill.hasClose)
                    setCardClose(pill, cardScale);
            }
            g_pills.push_back(pill);
        }

        const float createCy = g_tuckCards ? g_layout.h : cy;
        g_createRect = {g_layout.strip.r - createW - 12.0f * s,
                        createCy - createH / 2.0f,
                        g_layout.strip.r - 12.0f * s, createCy + createH / 2.0f};
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
            const float cardCy = g_tuckCards ? g_layout.h : cy;
            pill.rect = {cursor, cardCy - drawH / 2.0f, cursor + drawW,
                         cardCy + drawH / 2.0f};
            pill.hit = pill.rect;
            pill.hasClose = g_desktops.size() > 1 && i == g_currentDesktop;
            if (pill.hasClose)
                setCardClose(pill, cardScale * fit);
            g_pills.push_back(pill);
            cursor += drawW + gap;
        }

        const float createCy = g_tuckCards ? g_layout.h : cy;
        g_createRect = {cursor, createCy - createH / 2.0f, cursor + createW,
                        createCy + createH / 2.0f};
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
            const float d = WrapDelta(CarouselDesktopPosition(i, count) -
                                          g_carouselPos, count);
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

    const bool tuckedCards = UsesCards() && g_tuckCards;
    const float stripH =
        (UsesCards()
             ? (tuckedCards ? 112.0f * g_cardScale * 1.18f + 24.0f
                            : 224.0f * g_cardScale + 40.0f)
             : g_stripStyle == StripStyle::Carousel
                   ? (UsesChips() ? 112.0f : 96.0f)
                   : (UsesChips() ? 92.0f : 64.0f)) * s;
    const float stripBottom = g_layout.h - (tuckedCards ? 0.0f : 46.0f * s);
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
        const bool selected = !g_focusStrip && !g_pointerWindowSelection &&
                              card.filtered == g_selected;
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
        sink->AddArc(D2D1::ArcSegment(
            outer1, D2D1::SizeF(outerR, outerR), 0.0f,
            D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
        sink->AddLine(inner1);
        sink->AddArc(D2D1::ArcSegment(
            inner0, D2D1::SizeF(innerR, innerR), 0.0f,
            D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
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
// chip: a thin moulded edge, edge spots, the pressed rim groove and a
// soft sheen. `holeR` keeps the centre transparent for the window preview.
static void DrawChipBody(float cx, float cy, float r, UINT32 base, float holeR,
                         float alpha, int spotCount = 8)
{
    const float s = g_scale;
    const ChipPaint paint = ChipPaintFor(base);

    const float edge = std::max(1.0f, 1.0f * s);
    FillChipDisc(cx, cy, r, holeR, paint.edge, alpha);
    FillChipDisc(cx, cy, r - edge, holeR, paint.face, alpha);

    // Inserts run from the pressed groove to the outside edge. Their curved
    // ends follow the chip outline instead of leaving a bare clay gap.
    const float spotInner = r * 0.86f;
    FillChipEdgeSpots(cx, cy, r, spotInner, spotCount, 0.23f,
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

// BEGIN VECTOR CARD ART
// These helpers are also compiled by tools/preview-card-themes.ps1. Keep this
// section self-contained so the previews exercise the exact production paths.

struct CardArtLayer
{
    UINT32 color;
    const short* contours; // point count, then x/y pairs, repeated per contour
    size_t count;
};

// BEGIN GENERATED CARD ART DATA
// Generated by tools/trace-card-art.py; do not edit the contour arrays.
// References (viewed before tracing):
// https://www.saikikusuo.com/image/index/logoMain.png (552 x 195)
// https://images.ygoprodeck.com/images/cards/back_high.jpg (428 x 614)
// Logo: original black Japanese title, white keyline, and red wide Psi.
// Back: original copper frame and full-height amber/black vortex.
static const short kSaikiOutline0[] = {
    9,3,181,3,191,7,194,547,194,549,193,551,190,551,183,548,179,5,179,16,312,143,310,145,
    310,148,309,149,309,170,310,171,310,173,313,176,328,176,329,175,331,176,341,176,344,173,344,147,
    343,145,341,143,22,64,143,62,145,62,173,64,175,67,175,68,176,76,176,80,174,82,175,93,
    175,96,171,96,148,95,147,95,145,93,143,82,143,80,145,80,160,79,161,78,160,78,145,76,
    143,31,514,141,512,143,511,145,511,148,510,149,510,153,509,154,509,157,508,158,508,161,507,162,
    507,165,506,166,506,174,508,176,540,176,542,174,542,158,540,156,533,156,532,155,532,153,530,151,
    528,151,527,150,527,147,528,145,526,141,524,141,523,140,516,140,34,460,144,458,146,458,156,460,
    158,460,160,458,164,458,172,460,174,467,174,469,176,488,176,490,174,490,168,492,166,492,164,493,
    163,493,159,492,158,492,156,490,154,490,152,488,150,483,149,482,148,482,146,480,144,479,144,476,
    141,474,141,473,140,468,140,467,141,465,141,462,144,38,364,141,362,143,362,145,358,148,358,150,
    357,151,357,156,358,157,358,159,362,162,362,166,364,168,371,168,372,169,372,174,374,176,388,176,
    390,174,390,162,394,159,394,157,395,156,395,151,394,150,394,148,390,145,390,143,388,141,386,141,
    385,140,384,141,381,141,380,140,376,142,375,141,368,141,367,140,366,141,23,263,143,260,146,260,
    148,259,149,260,150,260,173,263,176,291,176,294,173,294,158,296,156,296,151,295,150,295,144,293,
    142,290,142,289,141,282,142,279,140,273,140,272,141,270,141,268,143,21,212,143,210,145,210,155,
    213,158,213,169,215,171,225,171,226,172,226,174,228,176,239,176,242,172,242,157,244,155,244,145,
    239,140,228,140,225,143,216,143,215,142,214,143,24,114,143,112,145,112,147,111,148,111,160,113,
    162,113,173,116,176,142,176,144,174,144,172,145,171,145,166,144,165,144,162,146,160,146,148,145,
    147,145,145,143,143,135,143,131,140,122,140,119,143,24,15,144,12,147,12,156,16,159,14,161,
    14,174,16,176,43,176,45,174,45,160,44,158,47,154,47,149,46,148,46,146,44,144,38,144,
    35,141,32,141,31,140,26,140,25,141,23,141,20,144,22,440,139,435,139,418,148,416,148,410,
    151,408,153,408,166,410,168,414,168,418,166,419,167,419,174,421,176,433,176,435,174,435,158,436,
    157,438,157,441,154,441,152,442,151,442,141,27,185,139,183,141,181,142,179,142,177,144,164,150,
    162,152,162,164,164,166,182,175,184,175,187,177,191,177,193,175,193,162,191,160,189,160,187,159,
    186,157,190,154,191,154,193,152,193,145,194,144,193,143,193,141,191,139,87,0,10,0,45,1,
    46,1,82,3,84,8,84,9,85,9,104,11,106,389,106,392,108,392,117,393,118,393,120,392,
    121,7,121,3,124,3,134,5,136,548,136,551,133,551,125,549,122,547,122,546,121,442,121,441,
    120,442,118,442,108,446,106,548,106,551,103,551,12,547,8,547,3,543,0,492,0,491,1,490,
    0,467,0,466,1,465,0,370,0,369,1,367,1,365,3,365,26,364,27,337,27,336,26,336,
    11,332,8,332,3,328,0,251,0,249,1,246,4,242,4,239,1,237,0,163,0,159,3,159,
    9,158,10,155,10,153,12,152,11,152,3,148,0,109,0,105,3,105,10,104,11,103,10,103,
    8,101,6,76,6,75,5,75,3,71,0,33,0,32,1,30,1,29,2,29,4,27,6,3,
    6,
};
static const short kSaikiOutline1[] = {
    4,8,184,8,189,546,189,546,184,7,476,164,477,163,479,163,480,164,480,166,478,168,476,166,
    6,118,164,118,171,139,171,139,166,124,166,123,164,6,19,164,19,171,40,171,40,166,26,166,
    25,164,6,271,160,273,161,273,166,272,167,270,166,270,161,6,222,160,223,159,230,159,231,161,
    230,162,223,162,11,324,153,325,155,324,156,324,160,323,161,323,164,321,166,320,166,319,165,319,
    154,320,153,16,315,148,315,171,326,171,326,169,327,168,327,164,328,163,328,159,329,158,329,155,
    331,153,333,153,334,154,334,171,338,171,338,148,6,90,148,89,149,85,149,85,170,91,170,91,
    149,7,67,148,67,170,76,170,76,166,74,166,73,165,73,148,6,286,147,286,152,287,153,291,
    153,290,151,290,147,18,17,150,17,153,29,153,34,162,40,162,36,154,37,153,42,153,42,150,
    41,149,40,150,35,150,32,147,32,146,26,146,27,147,27,149,26,150,34,517,145,516,146,516,
    150,515,151,515,154,514,155,514,159,513,160,513,164,512,165,512,168,511,169,511,171,516,171,517,
    170,518,163,520,161,521,161,523,163,523,171,537,171,537,161,532,161,532,165,531,166,528,166,527,
    165,527,156,521,156,520,155,521,153,521,150,522,149,522,145,41,463,149,463,153,465,153,466,154,
    466,158,465,159,465,162,464,163,464,166,463,167,463,169,468,169,469,167,469,163,471,161,472,162,
    472,171,485,171,485,164,486,163,488,163,488,159,486,159,485,158,485,155,480,155,480,158,479,159,
    472,159,471,158,471,155,473,153,477,153,477,149,474,149,473,148,473,145,472,146,468,146,468,148,
    467,149,26,265,149,265,152,272,152,273,153,273,155,272,156,265,156,265,171,278,171,278,161,279,
    160,283,160,284,161,284,171,289,171,289,156,280,156,278,154,280,152,282,152,282,149,280,149,278,
    147,278,145,274,145,272,149,19,215,148,215,152,230,152,231,153,231,155,230,156,218,156,218,166,
    230,166,231,167,231,171,237,171,237,153,239,152,239,148,237,147,237,145,232,145,230,148,24,117,
    148,117,151,127,151,128,153,127,154,116,154,116,157,129,157,134,163,139,163,137,158,138,157,141,
    157,141,154,135,154,134,152,135,151,140,151,140,148,132,148,130,145,125,145,125,147,124,148,17,
    188,144,183,146,181,148,167,155,167,161,168,162,186,171,188,171,188,165,184,163,182,163,177,160,
    175,160,173,158,177,155,187,150,188,149,5,8,127,8,131,546,131,546,126,9,126,8,511,74,
    513,72,518,72,519,73,519,77,518,78,513,78,511,76,8,297,73,298,72,303,72,304,73,304,
    77,303,78,298,78,297,77,8,40,69,41,68,62,68,63,69,63,73,62,74,41,74,40,73,
    12,338,57,344,57,345,58,345,61,344,62,344,67,343,68,343,73,341,76,338,76,337,75,337,
    58,8,511,56,512,55,518,55,519,56,519,59,518,60,512,60,511,59,8,297,56,298,55,303,
    55,304,56,304,59,303,60,298,60,297,59,12,40,58,40,56,41,55,45,53,50,52,51,51,
    53,51,59,54,61,54,64,57,62,59,41,59,46,211,51,211,56,212,57,212,60,211,61,209,
    61,209,68,212,68,214,70,214,71,212,73,210,72,209,73,209,80,213,80,214,81,214,90,224,
    90,224,81,225,80,228,80,228,73,226,73,224,71,224,69,225,68,228,68,228,61,227,61,225,
    59,226,58,227,51,226,52,223,52,222,51,221,52,221,56,220,57,220,60,219,61,217,58,217,
    54,216,53,216,51,215,52,212,52,20,326,43,326,90,352,90,352,88,353,87,353,82,354,81,
    354,76,355,75,355,70,356,69,356,65,357,64,357,59,359,57,363,57,364,58,364,90,375,90,
    375,43,8,483,41,484,41,486,43,486,45,484,47,483,47,481,45,481,43,7,469,41,471,41,
    472,42,472,45,470,47,468,46,468,42,8,511,38,512,37,518,37,519,38,519,41,518,42,512,
    42,511,41,8,297,38,298,37,303,37,304,38,304,41,303,42,298,42,297,41,8,40,34,41,
    33,62,33,63,34,61,36,59,36,54,39,50,39,8,473,30,474,29,479,29,480,30,480,32,
    478,34,475,34,473,32,111,531,16,519,16,519,24,518,25,514,25,513,24,513,21,514,20,514,
    16,502,16,501,17,501,19,500,20,500,23,499,24,499,27,498,28,498,30,496,34,492,34,490,
    32,492,29,495,29,495,20,492,20,491,19,491,17,480,17,480,19,479,20,474,20,473,19,473,
    17,463,17,463,18,461,20,459,20,459,29,462,29,463,30,463,32,461,34,459,34,459,54,471,
    54,472,55,472,57,471,58,459,58,459,67,469,67,470,68,470,69,468,71,460,71,459,70,459,
    80,465,80,466,81,464,84,464,86,462,90,473,90,473,88,477,80,479,82,483,90,493,90,489,
    81,490,80,494,80,495,79,495,71,494,70,493,71,482,71,480,69,482,67,495,67,495,58,483,
    58,481,56,481,55,482,54,495,54,495,46,496,45,500,45,501,46,501,90,535,90,535,78,532,
    78,531,77,531,73,532,72,535,72,535,60,532,60,531,59,531,56,535,54,535,42,532,42,531,
    41,531,38,532,37,535,37,535,25,532,25,531,24,118,249,23,249,35,253,35,254,36,254,40,
    253,41,252,48,250,52,250,55,249,56,248,63,255,63,256,64,255,66,255,69,254,70,254,73,
    252,77,252,80,251,81,251,84,250,85,250,88,249,90,283,90,283,84,282,83,282,79,281,78,
    281,73,280,72,280,68,269,68,270,69,270,74,271,75,271,77,270,78,264,78,263,77,263,75,
    264,74,264,71,265,70,265,68,266,67,266,64,267,63,267,60,269,56,269,53,270,52,271,45,
    272,44,264,44,263,43,264,41,264,39,265,38,265,36,266,35,280,35,281,36,281,39,280,40,
    280,43,279,45,285,45,286,46,286,90,320,90,320,78,318,78,316,76,316,74,318,72,320,72,
    320,60,317,60,316,59,316,56,317,55,320,55,320,42,317,42,316,41,316,38,317,37,320,37,
    320,25,318,25,316,23,316,16,304,16,304,24,303,25,300,25,298,23,300,16,287,16,286,17,
    286,20,285,21,285,24,284,25,283,32,281,34,280,33,280,23,273,23,272,22,272,19,273,18,
    273,16,260,16,259,18,259,21,257,23,77,175,16,175,24,173,26,169,26,169,39,172,39,173,
    40,173,43,172,44,172,46,171,47,171,49,170,50,170,52,169,53,169,55,167,59,167,62,166,
    63,166,66,171,66,172,64,172,62,174,60,175,61,175,90,188,90,188,61,189,60,190,61,190,
    63,192,66,195,66,196,67,196,90,206,90,206,50,208,48,230,48,231,49,231,90,241,90,241,
    37,226,37,225,36,225,33,226,32,240,32,240,21,227,21,225,19,225,16,212,16,212,20,211,
    21,197,21,197,32,211,32,212,33,212,36,211,37,196,37,196,56,195,57,193,54,193,52,192,
    51,192,49,190,45,190,42,189,41,190,39,193,39,193,26,189,26,188,25,188,16,87,93,29,
    93,43,104,43,105,44,104,45,104,48,103,49,103,51,101,55,100,62,99,63,99,65,97,69,
    97,72,95,76,95,79,93,83,93,86,91,90,106,90,107,88,107,86,108,85,108,83,109,82,
    109,79,111,75,111,72,113,68,113,65,115,61,115,58,117,54,117,51,118,50,118,48,120,44,
    121,45,121,90,136,90,136,45,137,44,138,45,138,47,139,48,139,51,140,52,140,54,142,58,
    143,65,144,66,144,68,146,72,146,75,148,79,148,82,150,86,150,89,151,90,165,90,164,83,
    163,82,163,80,161,76,161,73,159,69,159,66,157,62,157,59,156,58,156,56,155,55,155,52,
    154,51,154,49,153,48,153,45,152,44,153,43,164,43,164,29,137,29,136,28,136,16,121,16,
    121,28,120,29,55,16,22,16,33,19,33,20,34,20,38,30,43,32,43,33,44,32,46,30,
    47,28,47,25,49,20,50,17,52,17,63,19,63,23,61,25,62,25,90,40,90,40,84,41,
    83,62,83,63,84,63,90,78,90,78,62,80,61,81,62,84,62,85,63,87,63,86,62,86,
    53,87,52,86,51,81,50,78,48,73,47,70,45,72,43,82,39,83,38,83,34,84,33,87,
    33,87,22,60,22,59,21,59,16,45,16,44,17,45,18,45,20,43,22,140,10,17,11,16,
    38,16,38,11,39,10,64,10,65,11,65,16,93,16,94,17,94,23,114,23,115,22,115,11,
    116,10,141,10,142,11,142,23,163,23,163,21,165,19,169,19,168,18,168,12,170,10,193,10,
    194,11,194,14,206,14,206,11,207,10,230,10,231,11,231,14,245,14,247,16,254,16,254,13,
    256,10,280,10,281,11,280,13,280,16,281,14,281,12,283,10,322,10,323,11,323,18,325,18,
    326,19,326,36,327,37,374,37,375,36,375,11,376,10,495,10,496,11,497,10,536,10,537,11,
    537,18,540,18,541,19,541,95,540,96,479,96,478,94,476,96,454,96,453,95,454,94,454,92,
    457,86,454,86,454,87,446,95,440,98,438,98,437,99,434,99,432,100,432,112,431,113,404,113,
    402,111,402,100,400,99,397,99,396,98,394,98,390,96,388,94,387,94,382,89,381,87,381,95,
    380,96,147,96,145,94,145,91,144,90,144,88,142,84,142,81,142,95,141,96,116,96,115,95,
    115,81,115,83,114,84,114,87,112,91,112,94,110,96,58,96,57,95,57,89,56,90,48,90,
    47,89,46,90,46,95,45,96,20,96,19,95,19,69,13,72,11,71,11,48,13,46,15,46,
    19,44,16,43,14,41,14,39,11,39,10,38,75,5,11,5,44,6,45,6,79,8,78,10,
    78,13,76,14,77,14,101,386,101,387,99,394,103,396,103,398,105,398,117,437,117,437,104,438,
    103,440,103,444,101,546,101,546,14,543,14,542,13,542,5,493,5,492,6,438,6,437,5,397,
    5,396,6,370,6,370,31,369,32,332,32,331,31,331,14,329,14,327,12,327,5,252,5,251,
    6,251,8,249,10,238,10,236,8,236,5,201,5,201,8,200,9,199,8,199,5,164,5,164,
    13,162,15,158,15,159,16,157,18,148,18,147,17,147,5,110,5,110,17,109,18,99,18,98,
    17,98,11,71,11,70,10,70,5,34,5,33,6,34,7,34,9,32,11,
};
static const short kSaikiOutline2[] = {
    35,367,146,367,149,365,151,362,151,363,152,363,155,362,156,366,156,367,157,367,163,372,163,372,
    157,373,156,379,156,380,157,380,165,379,166,377,166,377,171,385,171,385,157,386,156,390,156,389,
    155,389,152,390,151,387,151,385,149,385,146,380,146,380,149,378,151,374,151,372,149,372,146,12,
    436,145,426,150,424,150,413,156,413,162,415,162,423,158,424,159,424,171,430,171,430,155,436,152,
    49,381,16,381,72,382,73,382,76,383,77,383,79,385,83,387,85,387,86,392,90,396,92,398,
    92,399,93,403,93,404,94,407,94,409,96,409,105,408,106,426,106,426,95,427,94,436,93,444,
    89,450,82,451,80,451,78,452,77,452,75,453,74,453,16,436,16,436,71,435,73,431,77,429,
    77,428,78,426,77,426,16,409,16,409,76,407,78,406,77,404,77,402,76,399,73,399,71,398,
    70,398,16,
};
static const CardArtLayer kSaikiLogoLayers[] = {
    {0xFFFFFFFF, kSaikiOutline0, ARRAYSIZE(kSaikiOutline0)},
    {0xFF221815, kSaikiOutline1, ARRAYSIZE(kSaikiOutline1)},
    {0xFFE60012, kSaikiOutline2, ARRAYSIZE(kSaikiOutline2)},
};
static const short kVortexOutline1[] = {
    4,21,593,22,592,25,593,24,594,4,188,592,190,591,191,593,189,594,9,328,589,327,591,324,
    591,316,595,308,595,300,593,303,591,308,591,320,587,5,159,587,162,592,161,594,159,594,156,591,
    14,250,588,249,589,247,588,250,590,246,593,243,592,236,594,228,594,215,591,216,589,221,588,222,
    589,239,589,247,585,20,363,593,366,589,375,588,383,583,386,583,392,586,394,585,396,587,395,589,
    397,588,404,590,401,593,398,591,391,593,390,592,391,590,388,589,386,591,377,592,372,594,18,86,
    592,81,596,71,592,64,591,45,591,40,592,38,594,30,595,27,594,25,591,29,588,39,587,46,
    583,62,583,63,582,76,586,81,590,85,590,4,188,576,193,575,194,577,190,579,13,365,578,361,
    581,354,583,354,585,349,589,346,587,340,590,332,589,333,586,342,580,346,580,356,575,360,574,8,
    383,573,382,574,384,575,380,579,377,580,371,579,376,573,378,572,18,142,572,144,574,144,578,145,
    576,146,577,145,581,150,583,152,586,151,588,150,587,150,589,147,591,146,594,137,593,140,590,140,
    580,141,579,140,574,4,301,572,303,571,304,573,302,574,36,263,590,263,586,266,582,267,577,269,
    575,279,574,278,573,279,571,282,574,280,576,277,576,278,577,275,579,278,580,279,582,288,583,296,
    580,313,578,316,576,317,577,329,571,332,573,332,575,329,578,328,576,327,579,317,584,316,583,301,
    584,299,587,289,590,279,591,275,590,273,591,270,589,267,591,15,207,576,222,572,224,573,223,572,
    226,571,227,575,232,576,235,573,243,578,241,579,244,580,245,584,243,585,241,582,223,581,13,166,
    571,168,573,167,576,168,574,170,575,176,583,177,587,175,589,172,588,168,584,169,583,163,578,165,
    576,4,190,572,192,570,196,571,193,573,5,343,570,342,573,338,574,337,572,340,569,4,212,565,
    217,564,218,567,215,568,20,105,564,106,569,109,574,108,576,109,578,106,580,107,581,105,582,103,
    586,101,587,96,583,89,585,82,581,87,576,98,580,101,577,100,575,102,570,101,563,103,562,5,
    193,563,195,560,200,560,202,566,195,568,4,39,561,41,560,44,562,41,563,7,403,559,406,564,
    404,569,402,571,394,570,393,569,394,564,11,332,557,332,561,328,565,322,568,319,568,311,574,306,
    573,306,571,309,568,323,562,329,556,4,299,557,301,556,302,558,300,559,4,334,554,335,556,333,
    558,331,556,4,30,556,33,554,37,555,32,559,13,170,554,176,553,180,556,179,561,181,563,186,
    564,188,566,188,569,185,571,182,571,179,565,174,565,173,558,4,167,553,170,556,169,559,166,557,
    30,220,554,223,552,225,554,232,552,255,553,256,556,263,557,271,553,279,554,281,558,275,562,268,
    563,263,566,256,564,255,566,250,568,245,567,244,563,246,561,256,561,255,559,242,558,242,561,239,
    563,237,563,236,561,229,562,225,560,223,556,222,557,10,28,552,30,555,30,559,26,561,25,564,
    22,564,21,560,23,558,24,559,24,556,4,351,548,354,547,355,550,352,551,20,144,547,148,548,
    153,553,153,555,156,556,154,561,156,563,157,566,156,567,158,568,157,573,155,572,155,570,149,567,
    146,564,146,560,142,558,143,556,146,557,143,551,4,347,545,348,546,347,549,346,548,4,106,545,
    107,546,106,549,105,548,4,140,545,142,544,144,547,142,548,8,60,543,58,544,60,545,53,550,
    49,551,47,549,51,547,55,542,4,349,541,350,542,346,545,345,543,25,330,542,329,544,330,549,
    325,551,321,556,317,558,315,557,313,562,307,562,305,560,306,559,304,557,309,552,310,555,308,556,
    308,558,312,555,308,551,311,548,318,547,319,549,318,547,319,545,322,545,328,541,9,19,541,22,
    540,23,543,28,541,31,544,30,550,29,551,21,550,19,548,28,92,544,92,559,89,567,76,571,
    64,571,53,573,39,579,28,581,23,584,19,581,22,575,31,574,34,572,38,572,37,571,38,570,
    44,570,59,565,61,566,68,563,73,563,75,561,78,561,78,559,83,553,87,551,88,539,89,538,
    25,405,541,405,547,403,550,398,550,394,554,391,555,389,554,387,556,381,557,376,562,373,562,367,
    565,357,566,347,571,342,569,349,560,353,560,360,554,364,553,368,548,375,547,378,543,380,543,392,
    535,398,535,4,203,533,206,531,208,534,206,535,4,101,530,104,532,103,538,99,534,12,379,530,
    380,532,379,534,372,537,369,540,366,540,362,545,357,547,355,546,361,538,374,532,377,529,13,46,
    533,44,537,38,536,27,537,24,534,22,535,21,534,22,532,26,530,37,531,39,529,40,531,42,
    530,5,193,531,196,527,198,527,202,532,198,534,4,19,528,20,527,23,531,20,532,4,191,522,
    192,523,191,526,190,525,6,41,522,43,525,39,529,36,526,39,523,40,524,4,180,520,182,519,
    184,522,182,523,4,96,519,97,518,99,521,97,522,4,303,516,307,515,308,517,305,519,47,133,
    519,136,515,140,516,145,521,144,523,145,522,151,523,152,525,150,526,154,530,161,530,165,533,165,
    536,174,537,175,538,174,539,177,540,176,542,179,540,180,543,181,541,187,547,191,547,192,549,193,
    548,198,551,197,552,200,553,202,557,201,558,189,551,184,552,179,548,174,547,173,545,168,545,166,
    548,168,552,165,555,162,552,162,549,153,542,148,532,144,532,142,529,135,527,135,523,13,71,514,
    73,518,72,529,70,534,67,535,68,537,65,538,62,535,67,531,64,526,64,523,67,517,70,516,
    4,168,513,172,512,173,514,170,515,67,208,537,209,534,214,532,215,527,219,528,220,531,224,531,
    228,534,235,531,241,536,243,535,244,536,251,535,254,536,255,534,247,533,240,534,238,532,239,531,
    234,531,228,527,224,519,229,510,231,512,230,522,233,525,232,526,240,525,241,527,247,526,248,529,
    246,531,254,532,260,531,262,529,264,530,277,528,279,529,283,527,285,524,290,527,290,524,293,520,
    296,522,298,525,297,526,301,523,304,524,306,522,311,523,312,522,314,524,310,529,306,529,297,535,
    294,536,292,535,285,540,284,538,282,538,281,540,276,540,271,542,232,541,230,539,229,540,216,540,
    9,208,510,212,512,214,520,213,522,211,522,209,520,210,519,208,520,207,519,10,386,510,384,513,
    382,514,380,513,380,515,375,519,373,517,374,514,377,513,379,509,14,325,511,326,513,320,516,321,
    518,318,523,316,522,314,524,313,519,315,516,312,512,313,511,319,512,320,509,324,512,27,81,509,
    84,513,84,517,86,519,87,524,84,528,82,541,78,545,77,549,69,556,62,558,60,557,54,561,
    48,562,47,559,49,557,55,555,56,556,60,552,66,549,68,550,71,547,71,544,77,532,80,530,
    80,520,78,510,40,113,507,116,507,121,512,122,516,127,519,133,525,134,528,132,529,131,538,129,
    540,125,540,124,544,125,549,135,568,131,575,133,580,132,586,133,591,127,595,111,593,111,589,115,
    587,113,580,117,574,118,567,117,565,120,554,118,541,115,538,115,533,119,532,120,535,123,537,123,
    531,121,529,122,527,121,524,116,521,112,516,111,509,6,163,507,164,506,166,509,167,506,168,510,
    165,511,6,295,504,296,505,295,508,291,509,289,507,290,505,11,43,500,45,503,40,509,41,512,
    38,515,29,517,27,515,29,510,30,511,35,505,39,504,6,332,499,333,501,331,506,326,508,324,
    506,325,502,6,206,497,207,496,212,497,214,500,211,501,207,499,4,78,495,80,496,79,500,76,
    498,4,284,495,285,493,288,494,286,496,4,151,490,152,491,151,494,150,493,4,148,487,150,489,
    149,492,147,490,9,29,484,32,488,26,495,23,496,22,499,18,491,22,488,25,488,25,486,6,
    401,480,403,481,402,490,399,489,400,486,396,485,4,160,480,162,479,165,483,161,484,11,364,477,
    367,480,367,483,364,485,361,492,356,496,353,492,357,485,361,481,363,482,362,480,6,136,474,140,
    480,138,484,134,480,135,479,133,477,8,152,471,154,472,153,475,154,478,157,477,158,478,154,482,
    151,478,21,108,473,112,471,114,475,116,476,115,477,116,479,118,480,118,484,123,488,127,489,128,
    488,133,493,129,494,128,492,125,494,124,491,121,491,120,489,117,488,119,487,109,479,14,93,466,
    98,470,100,475,107,482,107,484,111,487,111,490,107,493,104,492,100,488,100,485,98,482,99,481,
    92,470,6,107,465,109,467,109,471,107,473,105,471,105,467,4,386,465,387,463,390,464,387,466,
    6,131,463,136,469,134,475,131,472,132,468,130,467,4,90,464,91,463,93,466,92,467,4,154,
    463,156,462,158,466,156,467,9,382,459,384,462,378,474,375,476,372,476,371,473,375,470,376,464,
    380,462,14,59,457,61,459,62,470,64,469,70,477,70,484,68,489,65,492,62,488,63,487,61,
    483,62,478,61,479,57,469,9,28,454,30,459,28,464,28,469,25,472,20,474,19,467,22,465,
    23,460,4,146,454,149,453,151,458,148,459,39,353,449,354,451,352,454,355,456,354,457,356,461,
    354,463,355,465,351,467,346,474,339,473,338,474,339,479,336,481,332,480,331,481,333,482,327,490,
    318,493,312,499,308,499,307,494,317,486,322,485,326,481,325,479,328,478,330,473,336,467,338,463,
    346,466,351,464,349,462,349,464,346,465,341,464,340,462,345,457,345,455,4,97,447,98,448,97,
    452,96,451,4,60,447,61,448,60,455,59,454,7,141,444,143,446,141,447,143,448,142,450,140,
    450,138,447,17,69,442,72,445,71,452,72,453,73,451,75,453,77,460,77,467,80,471,80,476,
    83,480,81,483,74,473,71,457,67,451,68,449,67,446,4,317,436,318,437,315,439,314,438,8,
    312,436,315,437,313,439,315,440,313,443,309,441,311,440,309,439,17,259,440,255,437,241,448,235,
    448,232,449,231,451,230,450,224,452,222,451,216,456,222,460,231,459,236,453,242,450,247,450,253,
    445,257,444,6,25,436,27,440,26,444,23,441,24,440,23,438,9,402,435,403,439,400,440,397,
    444,394,441,394,439,396,438,397,435,399,436,18,365,433,367,438,361,445,359,445,360,447,359,448,
    360,450,359,448,361,447,362,451,358,452,355,449,356,447,354,444,357,442,360,435,362,433,364,434,
    6,198,433,197,434,198,436,201,437,201,433,200,434,4,371,431,372,440,370,441,369,436,4,318,
    431,320,432,319,438,317,436,8,379,426,380,427,378,430,379,432,374,437,373,432,376,429,375,428,
    5,329,425,330,427,325,434,320,431,327,425,15,348,418,349,421,345,425,345,429,346,431,349,431,
    350,434,345,439,343,436,343,431,342,432,340,430,340,427,344,423,345,419,4,382,415,384,422,380,
    424,379,418,4,337,415,338,418,334,422,333,420,7,204,414,208,421,210,422,231,421,220,420,215,
    418,212,415,4,389,411,390,414,388,415,387,413,11,76,411,81,413,83,422,89,431,89,434,87,
    437,86,436,84,438,77,430,75,422,75,412,9,21,411,24,413,26,417,26,429,23,432,21,431,
    20,427,21,424,19,414,9,329,409,330,410,329,414,326,416,324,415,325,417,323,418,322,414,326,
    410,4,353,407,354,408,353,412,352,411,25,311,399,313,402,312,408,311,409,310,408,311,415,313,
    417,316,416,320,418,322,421,317,422,312,427,306,430,298,438,296,438,293,442,290,442,288,445,280,
    446,279,444,297,425,298,419,301,414,308,408,308,405,4,349,397,350,399,347,403,346,400,25,279,
    396,274,399,271,404,266,406,263,410,262,409,257,413,254,412,253,414,244,416,240,419,239,418,236,
    419,234,422,239,422,244,424,247,419,253,415,257,417,262,412,269,410,270,407,276,403,276,400,279,
    398,4,351,392,352,395,350,396,349,394,8,341,392,342,395,334,404,334,406,331,408,330,406,337,
    398,339,393,14,58,390,62,396,63,411,67,414,68,421,67,422,69,427,68,428,61,423,62,422,
    61,418,58,415,58,401,57,400,11,319,382,321,385,319,387,318,394,317,395,316,394,315,400,313,
    401,310,397,310,394,314,387,8,295,380,292,381,290,383,290,386,284,390,284,393,293,386,295,383,
    4,369,373,370,376,368,378,366,376,5,359,364,364,368,361,372,358,370,356,366,6,23,362,26,
    363,26,373,24,375,21,374,21,368,52,403,360,405,363,405,367,403,368,404,378,401,387,400,386,
    402,389,395,396,395,402,392,406,388,400,389,394,390,393,392,394,391,393,392,390,388,395,386,395,
    388,404,383,409,382,415,379,416,379,419,373,425,371,431,369,432,368,440,366,437,367,432,365,430,
    365,427,367,423,371,421,373,413,379,408,379,404,384,396,383,393,385,390,387,390,388,383,391,379,
    394,381,395,379,394,376,397,375,394,370,397,369,398,372,400,369,399,364,17,335,348,339,351,339,
    356,341,358,344,356,348,358,347,363,343,367,342,366,344,368,342,374,336,380,335,379,336,375,331,
    368,335,360,334,353,9,378,333,379,334,378,350,375,354,372,353,373,350,372,341,376,335,377,337,
    10,60,332,61,333,60,338,61,353,60,359,58,361,56,358,55,344,56,336,59,335,9,342,331,
    343,336,341,337,339,346,336,348,335,347,336,341,341,335,339,333,77,78,327,81,329,81,331,79,
    332,80,338,81,337,83,339,82,341,84,343,85,349,84,352,87,362,86,371,89,383,88,387,92,
    398,90,400,90,404,93,409,94,416,98,423,99,431,106,442,106,446,112,458,111,460,113,461,112,
    464,107,457,104,457,105,461,103,464,100,461,100,458,104,455,102,452,104,450,103,446,101,444,97,
    445,93,442,95,440,96,435,97,437,97,432,95,433,93,432,91,422,87,418,84,405,84,397,78,
    386,79,382,77,381,75,377,77,376,74,373,71,373,71,376,69,378,68,377,67,379,66,378,66,
    365,69,351,68,347,72,342,75,344,76,343,78,346,79,345,78,341,79,340,78,341,76,340,77,
    335,76,330,4,380,324,381,325,380,330,379,329,5,378,320,379,327,377,331,375,329,375,325,9,
    378,315,379,316,380,314,382,318,384,319,380,321,379,318,378,319,377,318,52,141,309,138,314,137,
    323,138,346,140,353,139,354,140,359,136,361,136,376,140,385,143,398,148,404,154,407,156,412,156,
    417,170,434,181,439,186,440,194,438,193,437,191,438,183,433,181,430,181,427,176,422,175,417,168,
    410,164,402,162,401,162,399,159,397,159,395,157,395,156,393,152,394,151,393,152,392,150,394,144,
    385,143,374,138,368,139,365,141,366,145,372,147,371,148,372,149,363,147,354,147,338,146,337,147,
    320,144,309,4,352,300,353,301,352,304,351,303,8,44,299,45,302,43,303,45,304,45,308,42,
    314,40,312,41,302,4,330,298,332,301,329,305,328,299,34,303,287,304,288,301,290,300,299,296,
    306,297,307,291,323,290,332,288,337,284,341,283,347,280,351,279,350,280,352,274,360,274,362,269,
    367,266,368,255,384,256,386,262,385,267,379,269,379,278,367,279,363,283,359,295,338,297,330,299,
    328,298,327,301,320,301,313,305,303,305,289,4,46,283,49,287,46,293,45,292,22,360,273,362,
    276,361,297,364,307,364,317,361,321,360,329,358,331,357,325,355,322,355,314,352,312,353,311,351,
    305,352,304,353,306,354,300,353,301,352,300,352,296,354,293,358,274,8,380,271,382,287,380,289,
    381,292,378,295,375,288,379,281,378,272,9,371,255,374,256,374,278,373,279,370,275,370,264,369,
    263,370,261,369,260,10,153,244,150,244,147,250,144,250,141,252,142,260,144,260,149,256,150,253,
    149,247,16,292,239,294,250,297,253,301,265,304,266,302,272,302,276,304,279,305,269,303,268,305,
    267,306,252,303,247,306,244,303,245,297,240,7,60,238,63,240,57,250,54,246,56,245,55,244,
    56,240,4,381,233,383,239,380,242,379,235,5,353,219,352,220,353,231,356,231,356,221,9,59,
    216,60,220,57,226,53,229,50,237,48,235,48,231,52,226,55,218,5,38,207,41,210,40,213,
    36,215,34,213,7,243,199,245,207,254,217,258,218,260,215,257,209,246,199,9,29,194,31,196,
    31,199,27,208,22,212,21,211,22,206,24,205,26,196,6,328,194,327,196,326,195,325,196,328,
    199,330,195,4,172,192,173,191,176,192,175,193,4,176,190,178,188,184,189,183,191,9,49,188,
    50,193,47,196,43,205,39,208,38,206,40,201,44,197,45,192,37,144,188,143,189,141,187,138,
    188,126,200,124,199,112,200,111,198,108,197,107,198,109,199,104,208,102,207,99,213,94,212,94,
    218,89,223,86,234,92,230,93,224,99,219,100,216,104,212,109,212,111,214,108,220,104,222,106,
    227,110,229,114,225,115,221,122,210,128,206,127,204,130,203,135,198,140,196,15,373,185,376,188,
    377,193,376,195,378,198,377,199,379,210,384,222,384,225,381,228,378,226,374,215,375,207,371,197,
    371,187,6,36,183,38,186,34,195,32,196,31,193,34,184,5,98,181,99,182,98,185,90,192,
    89,189,14,81,180,82,182,80,187,72,197,70,202,68,204,67,203,67,207,62,214,61,207,65,
    204,70,193,76,187,77,182,5,272,180,276,179,279,183,279,186,275,187,9,323,179,321,183,326,
    191,325,192,327,192,326,191,328,183,326,182,325,179,14,169,177,166,176,160,179,159,178,155,180,
    155,183,160,185,161,183,164,182,165,184,167,184,166,183,169,182,168,181,5,269,175,270,174,273,
    175,274,177,271,179,4,103,174,104,177,101,179,100,177,8,87,170,90,174,87,176,85,180,82,
    181,81,177,83,175,84,176,4,265,170,267,169,269,171,267,172,4,105,170,108,168,111,169,109,
    172,4,260,167,264,166,266,168,263,170,6,360,164,362,168,363,186,361,191,359,188,357,169,5,
    97,163,98,166,92,169,91,168,92,165,29,401,162,404,168,404,180,403,181,404,185,402,189,401,
    187,401,191,404,194,403,197,404,215,402,228,402,252,398,261,395,247,395,222,397,220,395,218,396,
    217,395,213,396,196,394,193,394,185,395,184,396,185,396,191,394,168,397,162,398,163,25,186,160,
    182,159,180,156,164,158,162,160,151,163,135,171,128,177,123,179,114,189,112,194,128,189,130,186,
    144,179,146,176,149,175,151,176,152,174,154,175,157,172,168,166,174,166,175,164,176,165,186,162,
    11,108,151,109,152,108,155,103,159,103,161,100,164,97,162,99,157,101,158,100,156,104,152,5,
    369,147,371,150,372,156,367,158,366,149,5,332,148,336,147,342,153,339,156,336,155,24,81,146,
    83,148,83,151,81,152,78,158,74,161,74,163,67,169,66,172,57,181,56,186,52,189,50,187,
    50,184,52,181,55,179,57,174,60,173,62,169,67,165,67,163,72,158,76,151,80,149,4,114,
    145,115,149,109,152,108,150,4,367,143,369,145,367,148,365,145,5,122,144,117,146,116,149,114,
    145,118,142,16,229,142,232,141,238,144,240,147,241,146,245,148,248,152,252,153,258,158,258,162,
    261,163,260,166,258,167,247,158,243,153,236,150,4,155,141,156,142,153,144,152,143,8,29,141,
    30,150,27,157,24,155,20,156,19,153,25,145,25,142,4,366,139,367,140,366,144,365,143,4,
    329,139,332,143,331,146,328,144,4,159,139,160,141,157,144,155,141,6,129,138,128,141,125,143,
    119,142,122,138,127,137,457,261,134,279,152,281,157,280,158,281,157,294,173,297,181,301,186,303,
    194,304,193,305,194,308,207,310,208,313,216,313,222,316,231,319,232,320,254,321,255,320,256,322,
    262,321,267,323,271,322,272,323,273,323,283,320,294,319,305,322,312,324,310,327,312,326,338,320,
    347,320,357,314,364,313,371,306,380,305,385,302,391,300,392,293,407,290,410,282,413,277,418,274,
    424,274,426,278,427,287,424,289,427,286,430,283,430,283,433,278,436,277,439,267,447,266,451,270,
    454,277,451,279,447,287,448,293,444,298,445,291,451,285,452,280,457,269,462,262,464,247,463,245,
    466,240,467,239,466,224,467,220,466,219,464,217,465,214,463,211,463,207,459,198,457,183,445,176,
    444,175,442,174,444,176,445,176,448,192,463,193,462,200,468,201,467,207,470,213,475,218,477,219,
    479,224,480,228,483,238,482,240,484,248,485,262,484,266,480,269,479,271,480,274,478,284,476,285,
    473,291,472,304,462,312,463,309,459,315,456,319,452,320,453,325,449,324,445,332,438,332,436,336,
    431,339,433,340,436,339,442,341,445,337,447,329,457,327,456,314,469,309,471,305,475,302,473,300,
    477,287,485,283,484,271,490,245,494,244,493,223,492,222,490,210,488,206,484,203,483,201,481,202,
    480,197,479,194,480,190,474,184,472,168,461,148,437,147,432,143,428,144,425,143,427,141,426,131,
    405,131,402,127,397,126,392,127,388,125,385,126,384,124,378,121,376,120,373,121,376,117,378,112,
    368,108,366,107,369,109,373,109,382,113,399,123,419,128,425,129,428,127,431,129,428,131,434,139,
    442,138,446,136,443,136,445,134,446,134,449,139,452,139,457,145,459,148,465,150,466,150,475,149,
    476,146,473,145,474,144,473,146,469,144,472,143,471,144,465,140,464,138,460,133,459,131,463,129,
    464,129,466,126,467,125,463,127,458,126,461,123,459,124,458,123,453,117,450,115,447,115,444,113,
    441,113,438,115,437,114,436,112,438,109,435,109,429,105,421,103,404,101,401,103,392,103,383,99,
    370,99,359,97,348,99,340,98,326,101,313,100,305,102,302,101,301,102,295,105,293,108,300,106,
    317,109,320,105,328,106,338,109,339,108,340,108,351,110,352,109,337,111,335,115,342,114,346,117,
    349,116,357,120,365,120,368,119,348,118,347,119,337,115,330,115,333,114,334,113,333,113,319,109,
    318,110,315,109,300,113,293,115,278,121,266,121,262,124,258,125,252,144,226,148,225,150,220,164,
    212,166,208,171,207,175,203,186,202,190,198,195,196,200,197,202,195,205,195,208,192,207,190,203,
    191,194,190,192,192,186,191,184,189,186,186,194,184,204,184,218,187,223,190,224,185,219,180,212,
    177,203,177,200,179,199,177,198,179,196,177,187,177,182,175,178,177,179,178,176,182,173,182,169,
    184,168,186,165,186,149,199,145,200,140,204,129,219,125,223,122,224,120,232,116,240,112,244,110,
    252,101,268,99,277,94,287,94,293,92,296,93,297,92,308,86,318,85,317,85,312,86,311,87,
    312,86,302,87,296,90,291,90,285,93,274,93,265,96,261,97,255,99,254,100,246,98,244,92,
    245,80,256,78,256,75,264,72,266,73,268,70,274,72,277,73,275,77,273,78,268,82,266,83,
    264,84,265,84,279,82,284,82,293,77,300,71,305,68,311,68,314,64,318,65,320,64,324,61,
    328,59,328,56,336,54,333,57,328,57,325,55,322,57,301,59,298,63,283,62,282,62,272,64,
    264,63,262,66,258,68,259,67,255,68,248,73,243,73,240,76,238,78,231,81,227,81,224,88,
    213,89,209,99,195,108,186,109,183,118,176,124,169,140,160,141,161,143,158,150,156,157,152,164,
    151,167,149,173,149,176,147,188,147,189,146,192,147,193,145,199,144,200,146,205,147,207,149,208,
    148,211,151,214,150,216,152,225,153,230,157,234,158,240,164,242,164,244,167,249,170,248,171,249,
    170,251,171,263,185,270,191,270,193,273,193,274,196,278,196,280,194,284,196,290,204,295,215,295,
    222,299,227,303,241,305,242,306,241,305,233,306,224,301,212,299,200,290,184,286,173,277,160,277,
    158,273,154,270,146,259,138,259,135,4,248,135,252,134,254,138,249,139,8,162,138,167,133,171,
    133,172,135,174,134,176,136,169,140,165,140,8,404,131,405,136,402,144,402,149,399,155,397,151,
    398,134,401,131,4,254,132,257,131,260,134,256,135,4,137,131,138,134,133,137,132,134,4,20,
    130,21,131,20,134,19,133,4,22,127,23,128,22,131,21,130,7,239,131,240,129,244,129,245,
    126,251,129,245,131,243,134,20,111,127,106,131,104,131,104,133,97,140,92,142,89,147,84,149,
    83,148,84,143,95,133,97,135,98,132,99,133,100,130,102,131,103,129,102,128,104,126,108,125,
    4,22,127,26,125,28,129,24,130,8,234,124,240,123,243,125,242,128,240,126,236,126,237,127,
    235,128,4,363,122,365,126,363,130,361,128,4,159,120,164,118,166,122,161,123,4,168,118,169,
    117,172,118,170,120,22,173,118,175,115,191,115,192,112,195,112,200,115,204,115,208,117,210,115,
    221,120,229,120,233,126,231,128,227,125,223,125,222,123,218,123,213,120,192,119,186,121,183,118,
    175,119,21,339,111,342,111,344,113,341,116,341,121,345,130,344,131,347,133,346,134,349,141,348,
    144,345,144,343,142,345,138,342,135,343,134,340,132,338,119,339,118,337,116,337,113,11,57,110,
    49,119,46,119,40,124,38,124,37,126,31,125,40,116,51,113,52,111,56,109,4,322,108,326,
    111,325,117,321,115,4,371,106,372,107,371,111,370,110,168,255,105,258,105,260,107,260,109,257,
    111,262,109,266,115,269,115,271,117,272,120,270,122,277,124,276,129,279,129,281,127,291,138,290,
    140,292,140,295,143,297,149,300,151,300,153,302,152,304,154,306,159,310,163,309,164,316,173,315,
    175,316,178,319,175,321,175,320,172,321,169,320,165,318,165,315,162,315,160,318,159,318,157,321,
    154,317,156,315,160,314,159,314,155,316,154,316,152,314,151,316,147,314,144,313,145,314,148,313,
    155,310,152,311,150,308,149,309,142,303,138,302,134,297,128,298,126,286,118,285,116,287,113,291,
    114,296,120,300,121,304,120,305,113,304,110,305,109,306,111,308,111,312,118,319,123,319,126,318,
    127,316,124,327,136,326,139,320,137,320,142,323,148,334,158,342,154,346,154,348,156,347,158,349,
    161,348,163,349,175,348,176,350,180,349,183,352,194,352,199,354,202,355,214,358,217,362,216,364,
    218,362,239,358,244,359,251,358,261,356,262,351,257,346,263,342,253,343,252,343,246,341,241,342,
    239,338,227,339,222,344,226,345,216,347,213,349,213,351,217,352,213,351,207,349,204,351,202,352,
    203,349,201,348,197,343,193,340,193,340,200,338,205,333,205,328,202,325,204,326,225,324,227,322,
    225,323,222,319,215,318,206,319,204,316,202,315,198,313,197,311,192,311,186,305,179,305,176,302,
    174,299,168,300,167,288,151,282,146,280,141,275,137,274,134,268,130,263,124,257,121,258,119,260,
    119,258,115,256,117,255,116,251,117,247,114,251,113,249,111,8,31,105,32,109,30,111,28,111,
    23,115,20,113,20,110,23,106,14,152,105,135,114,127,116,125,119,120,122,119,121,112,127,109,
    124,112,120,120,115,128,113,131,110,141,105,150,103,5,374,102,375,104,372,107,371,106,372,103,
    10,81,101,83,103,82,106,73,112,72,109,77,105,76,104,78,102,80,103,79,102,4,34,104,
    36,101,38,102,36,105,5,160,101,159,104,153,103,154,101,158,100,4,305,98,308,97,310,100,
    308,101,4,55,100,59,97,63,98,60,101,10,403,96,405,98,405,101,393,108,385,118,383,114,
    383,110,388,106,388,104,391,101,4,377,97,378,96,381,97,380,98,21,142,97,112,112,105,118,
    102,118,96,123,93,124,91,122,92,119,94,120,96,116,100,116,102,112,106,111,111,107,112,108,
    119,103,122,104,129,99,133,99,132,98,136,96,4,234,97,237,95,239,98,237,99,4,143,97,
    145,95,147,96,146,98,10,321,91,325,97,322,100,323,102,322,108,318,110,315,107,315,104,319,
    100,319,92,4,229,91,230,94,228,96,227,92,12,331,90,332,95,335,96,336,101,335,104,338,
    110,335,113,333,110,333,106,330,102,331,97,329,94,5,167,91,159,95,155,95,153,93,161,90,
    10,48,90,45,94,34,96,32,98,22,97,23,95,26,95,30,92,41,88,46,88,18,107,89,
    104,93,99,96,96,101,88,107,85,103,86,101,84,103,83,102,84,96,87,96,89,98,91,97,
    89,95,90,93,94,91,98,91,105,87,4,47,87,51,86,52,88,51,89,31,167,90,178,86,
    187,85,207,87,221,91,223,93,221,97,225,95,231,99,234,97,236,100,242,104,248,102,252,102,
    253,104,249,109,249,111,245,112,239,108,232,106,231,104,223,102,218,98,214,98,208,94,195,93,
    190,90,183,89,177,90,176,89,171,91,4,53,86,55,84,58,85,55,87,5,23,83,26,86,
    24,89,21,88,21,85,9,405,83,405,86,403,88,395,90,385,96,381,94,381,92,391,84,400,
    82,12,373,79,374,80,373,86,366,96,366,99,362,107,359,101,359,98,366,85,368,83,370,84,
    370,81,4,327,80,328,77,330,79,328,81,4,32,74,23,80,20,78,25,73,20,69,75,65,
    76,64,81,60,82,63,83,59,85,57,84,58,81,57,80,56,81,51,80,47,84,44,83,39,
    85,31,84,32,81,40,81,47,77,59,76,66,72,44,232,73,239,71,249,76,254,77,260,83,
    268,83,271,80,271,77,276,73,278,73,282,77,284,83,288,83,293,88,297,89,305,95,302,98,
    296,94,292,94,291,96,292,101,290,105,288,105,283,100,272,95,274,99,278,101,286,109,286,113,
    284,114,283,113,284,112,282,111,283,109,278,107,272,101,270,96,267,94,268,93,266,94,264,91,
    257,89,254,85,252,86,4,226,71,229,70,231,73,229,74,16,154,70,155,73,152,75,149,75,
    149,80,147,82,144,82,139,85,135,84,136,82,138,82,135,81,136,79,139,78,143,73,151,69,
    24,157,78,160,74,169,72,167,70,171,69,170,68,171,67,179,67,187,71,197,70,204,73,207,
    73,210,71,216,74,215,76,213,75,211,77,200,77,193,75,175,78,164,78,163,79,160,78,159,
    80,32,116,67,114,70,106,72,99,76,98,78,96,76,91,82,85,84,83,87,81,87,66,97,
    64,96,65,93,67,94,71,88,75,87,79,82,80,83,79,82,80,81,83,81,82,80,83,77,
    89,71,92,72,93,70,94,71,96,69,105,68,111,65,113,67,114,65,5,277,63,279,62,282,
    63,283,65,280,66,12,63,63,60,68,53,69,42,74,36,75,32,73,33,71,40,68,47,69,
    53,63,58,63,59,61,19,286,68,287,67,291,69,299,65,300,63,299,62,302,60,305,65,306,
    74,310,79,309,80,310,86,306,87,303,84,301,84,296,80,295,75,292,72,288,71,22,351,58,
    353,59,352,61,353,63,350,66,350,73,354,72,358,68,358,65,362,60,366,66,365,69,361,72,
    358,77,358,82,355,87,356,89,352,99,350,97,350,84,348,82,345,66,9,196,58,197,57,206,
    58,207,60,211,60,212,63,209,65,206,62,198,61,10,48,57,46,61,44,60,43,62,34,65,
    31,63,34,62,35,60,42,59,46,56,10,404,54,406,69,403,72,392,75,386,79,377,73,378,
    68,382,64,392,60,402,53,15,269,61,264,63,262,67,256,71,247,70,233,63,239,60,240,54,
    242,52,254,49,262,55,261,56,263,56,264,58,265,57,12,93,51,88,54,83,60,82,58,80,
    61,74,61,71,58,73,55,79,55,85,52,87,49,91,49,4,23,49,25,53,23,55,21,53,
    7,62,47,60,48,58,55,55,57,51,57,50,54,59,46,5,37,50,40,46,43,46,45,48,
    41,52,4,65,44,66,46,63,48,62,46,10,319,43,322,51,319,59,318,56,318,61,320,62,
    318,71,314,65,313,53,314,48,13,207,48,206,49,204,48,188,49,180,51,176,51,174,49,175,
    47,178,47,180,45,191,44,195,42,199,42,10,342,39,345,42,342,51,338,55,335,56,333,54,
    332,47,333,46,337,47,336,46,5,145,39,146,43,143,45,140,45,139,43,11,405,40,399,47,
    392,49,387,55,385,56,379,55,381,50,389,46,394,41,400,38,403,38,7,27,37,29,41,23,
    49,19,45,19,40,21,38,25,39,4,365,36,360,43,355,41,361,35,15,302,35,301,43,297,
    47,297,50,294,51,287,57,273,52,269,48,274,43,276,43,280,38,284,36,293,35,296,33,300,
    33,11,184,37,175,40,174,39,168,40,165,43,160,42,163,40,162,39,164,36,175,33,182,35,
    5,140,34,138,38,132,37,134,34,137,33,16,251,39,249,41,229,40,221,43,215,37,208,36,
    207,34,209,32,215,32,216,33,215,34,222,36,225,34,234,34,244,31,251,37,9,91,33,91,
    38,89,40,81,42,75,48,70,47,79,35,81,36,86,31,9,311,26,314,32,312,36,309,39,
    307,39,308,40,305,42,302,36,309,30,14,355,25,353,29,352,28,351,30,347,30,345,33,340,
    34,331,40,327,39,327,35,330,32,334,31,336,28,354,24,10,160,25,158,28,155,28,149,33,
    145,35,142,34,143,32,142,30,145,27,155,24,7,99,26,101,22,103,23,108,22,110,24,105,
    29,102,29,11,404,23,404,26,400,29,392,30,391,32,383,33,379,32,381,29,387,28,393,23,
    400,21,14,166,23,170,21,184,21,185,22,235,21,236,22,233,26,212,27,211,28,198,28,193,
    27,192,25,191,26,169,25,14,137,23,126,32,124,32,116,41,112,42,105,41,105,39,109,35,
    112,34,117,28,124,23,127,22,129,23,133,21,4,108,22,109,21,112,22,111,23,17,37,38,
    41,30,48,22,52,21,66,21,67,22,79,21,80,22,79,24,75,24,77,25,65,33,60,33,
    56,35,54,34,43,40,39,40,14,298,22,293,25,273,29,266,36,264,40,260,36,260,34,255,
    31,255,26,260,21,263,22,264,21,295,21,296,20,4,0,0,0,613,427,613,427,0,
};
static const short kVortexOutline2[] = {
    8,138,571,135,572,135,582,136,583,135,586,137,585,137,581,139,579,13,402,556,405,556,407,558,
    407,567,405,572,404,571,406,574,405,579,403,578,402,579,397,573,390,569,392,563,31,201,544,207,
    543,208,545,217,546,219,548,226,547,230,550,232,549,233,550,257,550,262,553,271,551,279,551,282,
    549,288,548,289,551,282,561,267,566,266,568,263,568,258,572,257,571,255,574,251,573,248,570,237,
    564,222,561,216,553,208,550,206,547,203,547,7,69,542,67,545,62,547,64,548,60,550,63,550,
    68,547,10,86,539,83,543,84,544,71,557,52,564,60,564,62,562,75,559,84,550,86,546,3,
    28,539,28,540,38,540,31,133,533,134,539,142,541,144,544,156,553,159,565,174,575,180,588,194,
    592,202,592,207,588,208,585,222,587,238,585,229,583,220,583,211,580,201,581,199,580,198,582,189,
    581,185,578,185,576,183,577,178,575,174,567,165,558,158,554,157,549,146,535,138,531,116,408,543,
    404,551,392,557,379,560,378,562,372,564,366,569,362,567,355,569,349,573,344,573,341,576,334,575,
    325,584,323,583,323,584,330,586,338,581,340,578,346,577,348,575,352,575,358,572,361,573,364,571,
    369,576,376,572,385,571,387,573,386,575,387,582,391,583,392,582,400,587,404,587,407,590,404,594,
    391,596,385,593,361,597,360,595,365,588,379,583,374,582,368,585,365,581,362,581,357,584,351,593,
    346,594,344,592,345,591,341,591,338,593,324,592,319,596,291,596,287,594,268,592,266,594,261,589,
    264,578,269,573,281,568,291,559,295,558,297,555,307,549,329,539,333,541,331,550,316,562,322,560,
    324,557,329,555,332,551,335,552,337,555,334,563,331,566,329,566,318,573,324,572,332,568,338,569,
    343,565,345,558,348,555,347,554,348,551,345,552,341,551,340,549,350,537,354,538,355,535,357,537,
    356,540,357,541,358,538,375,530,376,528,385,525,388,528,384,533,375,537,363,546,358,548,354,553,
    352,553,350,558,363,551,366,547,381,540,391,533,400,534,3,76,523,74,532,76,528,4,254,511,
    256,510,258,512,255,513,8,208,503,212,507,215,507,221,510,226,509,222,505,218,505,216,503,6,
    197,488,199,491,207,493,207,490,204,489,203,487,16,174,487,179,492,183,492,184,495,192,500,194,
    499,197,502,206,503,204,503,202,500,199,500,196,497,188,493,181,491,178,487,175,486,25,304,479,
    297,481,287,487,285,486,281,487,270,495,268,493,260,493,247,496,236,496,225,493,214,494,219,498,
    226,498,241,501,253,500,257,498,264,498,272,494,274,495,279,494,286,490,289,490,290,488,298,485,
    33,407,473,408,476,405,484,407,489,403,493,401,493,398,497,393,499,392,502,391,501,395,503,394,
    504,395,506,392,510,386,515,375,520,371,520,370,519,373,513,376,512,375,509,380,504,382,504,388,
    498,390,494,387,492,385,493,384,491,389,486,390,487,395,481,403,476,405,473,17,40,473,41,474,
    40,482,41,485,39,494,38,495,33,488,31,493,19,505,18,504,19,497,17,493,18,489,29,482,
    34,486,37,481,37,476,49,327,471,326,470,320,471,317,473,318,476,317,477,316,476,306,486,292,
    493,286,498,284,498,279,503,276,504,271,502,269,504,267,503,257,506,253,509,244,512,240,511,232,
    517,232,521,238,524,243,524,248,522,252,523,255,520,256,521,255,520,256,519,260,519,261,521,265,
    521,269,524,274,521,275,518,274,516,271,515,261,520,258,517,257,513,266,512,271,509,278,510,284,
    507,285,505,297,500,303,493,318,483,5,267,466,272,465,275,468,271,469,268,468,7,66,459,65,
    463,66,466,68,466,69,468,69,461,67,461,4,292,457,293,458,290,460,289,459,4,275,446,271,
    447,272,451,275,449,6,320,425,312,430,313,431,310,433,317,428,319,428,42,401,420,403,422,402,
    424,406,426,407,432,405,456,401,458,399,461,398,460,392,467,389,468,388,470,389,472,393,469,395,
    470,394,473,387,480,384,481,382,484,377,487,376,486,368,488,361,493,359,496,350,500,349,498,355,
    484,357,483,357,480,374,460,382,454,385,448,388,447,387,443,391,441,391,437,393,436,391,434,395,
    428,398,429,398,424,400,423,4,402,417,403,418,402,421,401,420,41,351,405,347,408,333,427,320,
    440,308,450,295,458,292,457,300,449,297,449,294,452,284,457,279,458,271,463,251,466,245,470,224,
    469,190,454,183,448,181,448,181,450,190,459,199,465,207,468,208,470,222,479,252,479,254,481,260,
    481,271,476,277,476,283,472,294,468,299,463,301,463,314,454,316,451,319,450,322,445,342,423,347,
    413,350,410,18,21,404,27,416,27,428,31,450,30,451,31,459,29,470,22,476,19,477,17,474,
    17,467,25,452,23,453,19,452,19,436,17,424,19,408,18,406,4,51,400,54,402,53,406,49,
    405,17,155,397,158,406,158,416,160,420,169,430,176,434,181,434,184,436,182,435,183,434,179,431,
    179,429,175,425,174,420,168,412,166,407,157,397,4,370,393,372,396,370,398,369,397,6,144,387,
    143,394,145,398,149,401,148,393,146,392,16,354,377,352,381,348,384,340,400,336,404,328,417,324,
    420,322,425,325,425,330,421,332,416,340,409,341,405,351,390,352,382,355,379,5,138,373,139,381,
    143,385,142,376,140,373,22,111,373,111,385,114,392,114,396,135,433,141,440,142,443,145,445,146,
    449,152,456,167,470,172,470,155,449,140,427,132,411,129,401,123,400,120,397,119,391,114,385,114,
    375,113,373,7,23,355,27,362,27,380,25,383,20,377,19,372,20,360,8,140,314,138,322,139,
    342,143,350,144,365,146,367,144,316,143,314,18,373,305,370,307,371,311,369,313,367,320,369,331,
    362,338,362,347,364,349,367,347,368,348,368,342,372,331,371,326,374,322,376,315,374,307,375,306,
    10,77,303,72,306,65,323,64,357,65,357,66,344,72,339,74,327,79,313,79,305,28,302,296,
    302,299,300,301,301,303,298,307,297,313,292,325,292,329,285,344,285,347,281,352,278,360,265,372,
    261,377,261,380,258,383,262,382,275,368,277,363,283,356,285,350,287,349,297,328,298,319,300,317,
    299,316,300,309,303,301,6,111,279,111,284,108,289,109,294,113,287,114,280,20,95,249,91,252,
    87,252,80,259,82,260,85,257,88,259,85,269,86,282,84,286,85,288,83,290,84,298,85,298,
    86,291,89,288,88,287,91,278,92,264,96,256,4,376,247,375,256,376,253,378,254,5,41,227,
    42,233,37,237,36,236,37,232,125,330,209,327,213,328,231,326,236,324,238,323,237,322,240,324,
    285,322,291,322,303,321,304,323,306,327,298,328,283,330,280,330,276,332,275,335,280,334,298,337,
    302,338,301,343,302,342,306,343,309,340,313,335,309,336,308,335,306,330,310,329,336,326,343,322,
    348,322,357,315,366,312,376,309,378,307,385,298,399,296,404,297,405,291,411,283,414,278,419,277,
    425,281,425,295,419,305,409,308,404,309,393,319,378,323,380,324,382,317,399,315,400,313,412,314,
    414,316,414,325,409,335,398,343,384,345,383,347,379,346,377,350,374,352,370,352,363,357,359,358,
    360,357,359,358,357,360,358,361,355,358,355,357,352,354,351,352,353,352,356,350,357,350,361,338,
    383,332,387,331,384,333,381,333,376,329,374,329,368,333,359,332,353,338,331,337,329,340,325,342,
    326,344,332,343,341,341,342,340,345,341,353,342,354,349,351,349,347,351,344,349,342,350,338,349,
    334,350,329,352,327,353,320,352,315,347,305,347,296,345,293,345,289,347,288,351,290,353,288,356,
    274,353,261,350,261,346,268,343,264,341,255,340,237,336,224,331,214,333,210,8,123,204,120,205,
    112,215,109,222,110,225,112,224,113,220,120,212,6,245,202,248,208,255,215,258,215,254,209,248,
    203,10,344,196,342,197,341,210,338,213,339,218,341,220,343,219,344,211,348,205,347,200,5,181,
    192,180,193,181,197,184,197,186,194,4,140,191,136,192,127,202,134,198,4,80,167,81,169,79,
    171,78,169,17,183,161,179,159,168,159,164,160,163,162,157,162,155,164,152,164,133,174,123,182,
    118,190,127,187,144,176,152,172,155,172,168,164,173,164,5,385,151,386,152,385,161,383,158,383,
    153,4,384,146,385,147,384,150,383,149,5,322,141,322,144,328,151,332,152,325,141,4,194,130,
    198,129,199,131,195,132,29,406,127,408,129,405,144,407,154,406,158,407,188,406,189,406,217,403,
    231,404,232,403,234,403,254,399,263,399,272,398,273,397,272,397,279,393,287,391,282,393,271,395,
    270,395,260,394,259,395,253,393,243,394,235,393,163,397,132,401,128,14,199,101,201,99,204,99,
    209,103,216,104,219,108,223,109,226,112,226,114,222,116,216,110,210,108,206,104,200,103,42,199,
    100,198,102,188,102,187,103,168,102,162,104,161,106,152,107,117,124,108,130,94,142,88,149,85,
    150,72,167,64,174,57,186,53,190,51,196,47,200,46,204,42,209,41,214,38,217,36,217,33,
    214,43,192,57,172,65,164,69,157,76,149,99,127,105,125,110,120,121,113,141,103,149,102,156,
    98,167,100,170,98,172,99,175,97,184,96,30,293,98,294,103,290,111,297,117,302,118,301,114,
    303,108,308,109,312,113,314,118,319,122,320,126,326,132,333,143,343,151,346,151,342,143,342,139,
    335,120,334,113,328,101,324,100,324,105,327,110,328,119,326,122,311,104,306,103,299,97,296,96,
    6,26,91,28,91,30,88,34,89,38,87,31,87,4,59,71,48,73,44,75,57,74,5,228,
    66,231,66,234,69,235,68,230,65,52,128,63,126,65,123,65,115,71,104,75,100,79,86,85,
    74,93,65,101,65,105,63,108,50,120,41,124,40,126,34,129,25,130,22,134,22,140,20,141,
    18,139,17,129,19,123,23,120,27,124,29,124,42,112,52,110,55,107,57,107,59,104,61,105,
    63,103,62,102,54,104,47,108,42,107,46,102,66,92,71,86,73,86,80,79,81,74,89,69,
    105,65,109,62,108,58,114,54,118,54,119,56,112,62,119,63,126,61,16,101,52,100,56,96,
    56,92,54,88,56,86,59,78,63,73,63,69,61,70,55,73,53,79,53,80,51,85,49,89,
    45,95,47,6,142,39,141,38,134,40,133,42,137,42,140,39,22,157,40,164,34,180,33,184,
    35,192,36,203,44,211,46,214,50,212,52,205,50,187,50,180,53,174,53,171,49,175,43,177,
    44,182,42,181,41,173,42,167,45,161,46,157,43,4,319,22,320,21,326,22,325,23,42,369,
    20,370,21,369,23,355,27,356,28,348,32,348,34,344,37,349,41,362,33,367,33,368,36,364,
    40,364,46,354,53,351,49,352,47,347,45,345,46,342,53,337,58,334,58,332,56,330,48,331,
    45,338,41,340,38,333,41,331,45,323,41,325,38,326,32,331,27,332,24,335,21,337,23,336,
    24,340,25,343,23,350,23,357,20,365,21,1228,406,21,407,22,406,28,402,31,395,32,388,35,
    387,40,382,43,382,46,386,45,390,41,402,35,407,36,406,45,395,52,393,52,387,58,384,58,
    381,60,381,61,384,61,383,60,384,59,388,59,398,53,400,50,405,48,407,52,406,74,403,76,
    400,75,399,77,398,76,394,77,385,83,380,78,377,78,374,87,374,92,371,94,364,107,364,118,
    368,125,368,129,370,132,369,135,371,143,372,136,370,133,370,120,369,119,369,104,371,98,381,91,
    386,82,387,83,394,82,401,79,402,77,405,77,407,79,407,86,404,90,392,94,377,104,374,120,
    377,133,380,133,381,132,380,130,381,129,381,114,383,109,382,107,389,99,403,92,406,93,408,98,
    404,105,400,106,399,108,397,108,392,112,387,122,389,123,393,121,402,111,406,111,407,115,392,129,
    390,133,390,143,387,149,384,146,384,142,382,140,380,149,376,158,377,160,373,167,374,179,378,189,
    379,200,385,216,385,243,384,244,385,282,384,283,384,294,380,300,381,310,383,309,386,310,386,320,
    384,326,385,327,383,331,382,341,380,344,378,356,375,360,371,377,364,391,363,397,357,407,357,412,
    354,414,351,423,354,416,357,415,357,413,363,405,363,402,369,398,370,400,368,403,368,406,362,418,
    359,421,357,428,355,429,353,434,342,448,338,451,332,461,331,466,333,466,351,447,351,445,357,438,
    376,407,377,402,381,396,385,385,385,382,387,380,387,377,390,375,390,363,389,362,387,363,389,365,
    387,368,386,367,382,373,381,372,382,363,387,357,387,352,389,350,392,351,390,349,391,347,390,343,
    392,341,397,340,398,341,401,334,400,325,402,323,406,324,405,332,407,349,407,376,406,377,407,380,
    404,389,397,400,396,407,391,417,367,453,361,459,360,457,361,460,347,476,341,479,337,485,322,494,
    319,498,315,499,313,502,311,502,307,507,310,506,311,507,329,498,332,495,338,494,340,498,336,501,
    330,510,329,514,323,521,313,529,288,540,277,541,268,544,239,543,238,542,237,543,212,542,202,536,
    194,535,187,529,182,527,176,522,174,522,166,513,163,512,159,508,160,507,159,505,157,506,140,489,
    127,473,127,470,121,462,109,438,107,430,103,424,103,414,99,401,99,396,102,390,102,383,99,376,
    98,362,96,357,96,328,100,295,102,293,108,277,109,270,113,267,116,273,118,270,120,261,134,236,
    137,234,139,230,149,219,161,211,164,207,171,204,172,202,171,200,173,196,169,197,152,208,151,207,
    151,209,137,221,136,220,141,213,151,205,156,198,158,198,163,193,172,190,175,186,178,187,187,185,
    190,183,197,182,198,180,210,182,215,185,221,186,221,184,214,179,204,179,200,181,196,179,183,177,
    184,179,180,183,168,187,163,191,156,194,148,201,143,203,123,228,101,272,100,280,96,287,94,295,
    94,304,89,319,90,320,86,325,84,320,82,325,82,332,85,339,87,351,86,352,89,370,90,387,
    94,397,94,409,99,421,100,429,106,439,107,445,112,456,118,465,118,468,122,477,135,493,139,500,
    137,502,119,493,117,493,116,495,110,494,108,498,109,501,113,503,114,502,120,508,125,516,128,518,
    135,511,137,511,163,530,170,533,171,535,172,534,173,536,181,539,185,543,202,550,212,561,215,561,
    222,566,242,575,251,586,252,590,249,593,241,595,227,595,216,593,198,597,182,596,177,592,173,591,
    165,583,159,581,157,576,149,568,144,567,137,551,127,541,126,543,132,559,139,567,142,567,145,571,
    144,572,150,582,161,588,161,590,163,591,163,595,158,596,154,592,150,592,145,596,138,596,136,594,
    133,594,131,596,111,596,107,592,112,585,111,579,114,576,116,566,115,562,117,554,117,544,113,536,
    112,528,113,527,114,529,120,531,120,529,117,523,112,523,113,524,111,527,109,524,104,525,103,527,
    106,532,106,540,108,543,108,546,112,551,109,552,104,550,102,546,102,541,98,533,98,529,91,516,
    91,513,93,511,96,514,99,512,98,503,100,502,104,511,108,515,108,507,110,504,106,502,103,493,
    100,490,96,482,96,479,91,473,87,463,87,458,89,457,93,460,96,467,106,479,107,476,96,456,
    95,451,89,442,86,441,83,449,79,446,80,439,74,424,72,398,73,397,76,400,81,410,82,410,
    82,406,80,402,80,397,78,392,79,391,74,378,72,377,69,391,65,395,66,400,65,404,70,415,
    71,436,75,444,76,453,78,455,77,456,81,467,81,471,86,483,89,485,82,488,82,505,86,512,
    89,533,94,544,93,565,90,569,79,573,58,574,43,580,30,583,26,586,28,587,33,585,38,585,
    48,580,63,579,73,582,82,587,85,587,75,577,77,575,90,574,95,577,98,577,100,571,101,561,
    100,556,101,555,104,556,107,569,111,573,112,577,103,591,100,591,97,585,93,585,88,588,89,593,
    85,597,52,593,42,594,32,597,28,596,22,597,19,594,19,589,22,587,18,584,17,581,19,575,
    27,571,25,568,22,568,18,563,19,553,17,543,19,537,18,533,19,522,24,517,24,512,38,502,
    41,496,43,496,46,499,45,506,41,513,42,515,37,519,28,519,28,520,38,520,42,518,45,519,
    46,523,43,528,48,530,49,533,48,538,55,536,60,531,61,525,64,519,65,510,62,503,60,481,
    56,468,56,448,59,443,59,440,56,431,57,415,55,408,56,406,55,405,55,386,54,385,55,380,
    54,365,55,364,53,353,51,349,51,333,54,328,53,316,55,309,55,301,60,287,60,274,62,269,
    62,261,67,252,67,247,72,241,74,233,78,228,79,222,83,217,87,209,86,208,88,207,94,197,
    110,180,134,161,158,150,170,147,174,143,188,144,194,142,203,144,208,148,212,148,215,150,223,151,
    231,154,253,171,261,179,263,183,271,189,270,187,271,186,269,184,270,183,266,180,260,170,245,157,
    230,146,226,145,222,140,215,136,216,135,214,137,211,136,208,137,202,133,204,131,211,131,221,136,
    230,138,241,144,256,155,270,169,279,181,284,190,285,195,290,201,297,218,297,223,300,226,304,234,
    304,223,298,207,297,199,294,195,292,188,285,174,271,154,271,152,270,153,268,152,269,151,267,148,
    264,147,261,149,238,132,212,122,168,123,161,125,154,129,150,129,140,134,134,139,122,145,121,147,
    112,152,93,172,72,200,72,202,64,214,61,224,58,228,57,234,58,234,59,229,63,225,64,221,
    72,212,73,208,82,196,82,194,85,192,92,181,97,177,98,174,106,167,108,167,114,161,126,153,
    129,153,133,150,142,147,144,144,149,143,154,138,162,133,171,131,173,129,180,128,188,129,189,128,
    190,130,186,131,185,134,182,135,179,139,173,143,166,142,158,146,152,146,147,150,137,152,132,157,
    127,158,126,161,120,164,116,169,115,168,101,182,101,184,94,193,94,195,84,206,79,213,76,221,
    73,222,73,224,70,227,65,238,65,242,58,254,58,262,53,270,52,283,46,299,47,303,46,314,
    44,315,45,317,43,319,41,328,38,334,37,333,37,317,39,301,41,296,41,284,44,278,44,272,
    37,278,36,283,30,290,28,295,26,294,24,296,25,304,23,306,22,315,19,317,18,316,19,290,
    22,289,26,277,24,277,22,280,19,279,18,274,19,265,22,259,25,257,28,249,31,247,33,240,
    36,236,37,245,32,249,31,253,32,254,30,255,29,261,24,267,23,271,27,275,28,271,30,271,
    32,274,36,269,35,265,33,264,34,263,31,262,30,260,32,257,35,256,37,257,41,254,43,250,
    45,232,51,224,53,218,56,215,62,203,66,199,76,181,83,172,104,151,107,150,119,139,128,135,
    128,133,131,132,133,128,146,124,149,121,153,121,159,114,164,111,179,108,192,108,200,111,211,112,
    223,117,232,116,245,124,254,127,264,134,273,143,292,168,297,178,300,181,304,189,304,192,309,200,
    313,213,315,215,315,221,319,231,321,230,321,221,317,215,316,204,312,198,310,190,305,180,289,155,
    270,132,244,113,220,102,217,99,203,95,199,96,189,92,177,91,157,97,150,97,147,99,142,99,
    126,108,119,110,84,134,83,137,64,155,57,165,55,166,54,169,43,181,42,185,23,215,21,222,
    22,223,21,228,23,229,22,234,19,236,17,233,19,231,18,226,19,225,18,219,19,218,18,217,
    19,176,21,175,19,174,18,150,21,145,21,141,22,140,23,142,31,140,34,137,44,132,65,115,
    67,115,72,106,78,100,80,100,84,95,93,89,98,89,104,86,110,87,109,90,103,95,102,98,
    92,106,86,115,93,115,100,110,105,109,111,105,114,105,120,101,128,99,134,95,144,93,154,88,
    155,89,167,88,170,86,179,84,199,84,200,85,212,84,220,89,231,88,234,92,242,93,248,98,
    249,97,255,100,283,126,299,147,307,153,308,151,305,142,301,138,298,132,286,120,279,109,268,98,
    256,90,250,91,247,90,243,92,241,89,239,89,238,87,234,85,238,84,240,87,244,88,247,86,
    249,89,251,87,249,87,244,82,231,76,230,77,233,83,232,85,216,80,214,78,203,79,196,77,
    165,80,159,83,155,83,153,85,146,84,135,90,128,89,127,84,131,81,133,77,137,76,145,69,
    149,68,158,68,162,66,180,66,194,69,202,69,204,71,209,69,206,64,188,62,187,59,189,57,
    202,56,222,61,223,62,222,66,224,66,223,63,224,61,230,63,237,57,237,54,239,51,248,47,
    254,47,258,49,264,55,269,57,271,60,279,58,273,55,267,47,267,45,254,33,253,26,256,21,
    267,19,299,19,300,20,300,23,295,28,290,27,280,29,269,35,266,40,267,43,273,42,281,35,
    294,33,296,30,303,33,311,24,314,24,315,25,315,37,313,41,310,44,303,43,301,45,300,50,
    284,61,283,59,281,59,287,64,288,63,295,66,297,60,300,57,304,59,307,64,307,72,313,85,
    313,88,309,91,305,89,304,87,301,87,294,80,292,75,282,67,277,67,270,64,266,65,258,73,
    249,72,252,75,255,75,263,81,266,80,274,71,278,71,289,83,302,91,309,93,312,99,316,100,
    317,99,316,92,320,88,321,85,319,83,317,73,313,66,311,52,317,40,324,42,323,44,324,60,
    325,59,330,62,332,89,336,95,338,104,340,105,342,98,346,106,346,109,349,113,347,116,344,117,
    344,125,347,129,351,143,350,147,351,172,352,173,351,187,358,213,360,212,361,207,359,202,359,193,
    357,189,356,180,356,164,358,153,363,164,363,172,366,182,364,190,364,203,365,209,368,215,366,220,
    365,240,360,249,360,259,361,260,360,266,364,277,363,293,365,303,367,306,370,303,373,295,372,294,
    373,289,368,277,368,265,369,264,368,263,369,254,368,246,370,243,372,245,375,241,376,229,375,223,
    371,216,372,208,369,200,370,199,368,191,369,167,363,158,364,146,360,139,360,135,358,131,359,125,
    358,123,357,126,355,125,355,129,358,130,358,134,356,135,353,133,355,132,353,131,353,125,349,117,
    352,112,354,113,353,114,357,113,355,111,356,110,358,111,358,104,357,101,352,103,349,100,347,88,
    348,87,345,75,345,64,348,58,351,57,352,55,354,55,356,59,353,69,357,65,358,60,361,58,
    368,63,367,68,363,72,360,78,357,91,358,93,368,81,368,79,374,74,379,64,373,58,377,54,
    378,51,376,42,379,41,383,35,376,34,374,32,378,29,385,27,393,21,398,20,40,252,35,252,
    40,250,44,246,43,232,44,232,46,230,47,232,48,231,49,224,47,211,38,208,38,199,34,198,
    31,192,28,191,29,186,26,163,26,154,30,149,36,150,41,146,46,142,46,134,50,131,45,125,
    43,123,40,139,28,145,25,164,20,203,20,204,21,205,20,237,19,240,22,235,28,215,30,221,
    30,227,32,244,30,12,144,22,123,36,120,42,114,42,105,46,103,45,102,42,105,35,108,32,
    113,30,123,21,140,19,6,117,22,105,31,98,30,96,28,97,21,115,19,91,91,19,92,20,
    89,22,85,22,76,26,67,34,62,35,57,38,48,39,43,42,43,43,47,43,49,40,55,42,
    51,47,41,53,40,55,47,53,49,50,51,50,61,41,65,41,68,44,70,43,78,34,87,29,
    92,29,95,32,93,39,89,44,83,43,71,52,67,50,63,50,58,59,59,58,61,61,66,63,
    65,70,69,71,72,75,67,79,63,85,46,94,41,100,41,104,31,111,27,116,25,116,24,118,
    20,117,18,114,19,106,24,103,29,103,32,100,21,102,19,99,18,89,19,80,18,78,24,72,
    25,69,19,66,18,56,20,48,18,46,17,39,20,36,29,36,32,39,30,40,26,48,28,53,
    25,55,21,62,24,65,27,65,28,62,34,57,38,57,37,56,33,57,30,53,38,45,33,38,
    47,21,63,19,67,21,73,21,77,19,5,33,21,29,25,23,25,21,22,29,19,4,0,0,
    0,613,427,613,427,0,
};
static const short kVortexOutline3[] = {
    6,338,577,335,576,329,580,328,583,329,585,332,584,6,176,576,178,582,182,587,195,591,203,590,
    201,586,7,145,568,147,576,150,581,156,584,158,582,155,576,149,570,11,158,556,159,562,162,567,
    164,567,173,573,174,575,175,574,173,573,173,568,169,563,162,557,8,343,552,340,552,336,557,335,
    567,337,568,340,567,344,560,345,554,7,105,552,107,566,110,571,113,573,115,570,114,559,111,555,
    6,203,549,206,551,211,558,215,560,218,559,214,553,4,219,544,221,545,235,544,229,543,5,127,
    543,133,559,138,564,141,565,137,553,4,198,538,201,542,206,541,205,539,5,139,534,140,538,148,
    546,154,549,149,539,5,109,533,108,542,110,546,115,550,115,542,76,409,541,407,549,409,565,407,
    569,408,577,405,580,401,581,398,578,398,575,396,573,393,573,388,569,392,560,391,558,377,562,371,
    566,368,570,368,574,372,574,380,570,387,570,388,571,387,579,389,581,397,582,399,585,405,586,408,
    589,408,593,404,596,396,597,373,596,360,598,358,596,365,586,364,582,360,583,349,597,332,596,327,
    592,319,597,275,597,265,596,260,592,260,587,262,584,263,577,272,570,280,567,290,558,299,554,307,
    548,318,543,321,543,327,539,335,537,336,538,332,549,337,551,339,550,343,543,357,531,358,532,358,
    536,362,536,367,532,373,530,376,527,384,525,389,522,391,524,390,526,391,531,401,532,403,536,407,
    538,7,398,513,399,516,393,521,391,519,392,515,395,513,396,514,8,250,516,247,514,237,515,234,
    517,234,521,236,522,247,521,250,519,4,265,494,254,496,261,497,265,496,5,222,496,231,497,231,
    496,225,496,223,494,24,84,489,83,491,84,507,86,509,89,518,88,521,90,532,95,546,94,564,
    92,572,93,574,97,576,99,571,100,562,99,552,101,549,101,542,94,522,89,518,91,509,92,508,
    96,509,96,503,89,489,9,320,477,299,492,294,493,282,501,275,507,275,509,296,499,306,489,317,
    481,24,407,471,409,473,407,483,409,489,407,492,403,493,400,495,399,498,396,499,396,501,398,502,
    396,508,390,514,367,524,366,522,369,519,372,511,387,497,387,494,380,496,379,495,390,483,393,482,
    394,480,7,282,459,279,459,274,463,272,463,274,465,277,465,282,461,22,78,449,78,454,83,466,
    84,474,88,482,94,489,94,492,97,495,96,496,104,503,103,504,104,507,106,507,105,503,103,502,
    102,494,97,488,98,487,96,481,85,465,83,453,81,450,9,86,446,90,456,96,461,97,467,103,
    473,102,468,98,463,94,452,89,446,37,109,440,108,445,116,461,119,464,123,475,129,485,132,487,
    141,500,150,509,148,510,142,505,130,499,121,497,124,506,122,508,120,505,126,513,126,515,129,515,
    133,510,137,509,165,530,183,539,187,543,197,547,199,544,198,542,194,540,192,536,186,530,181,528,
    168,518,135,485,122,467,117,455,114,452,114,448,4,102,426,102,431,106,436,106,430,6,72,425,
    71,431,77,443,78,436,75,431,74,426,48,346,413,344,416,342,416,334,428,322,438,313,448,302,
    456,293,460,287,465,281,466,276,471,272,470,264,471,263,470,265,468,264,467,258,466,255,467,254,
    469,260,470,262,472,256,475,255,474,249,475,242,471,220,469,212,464,208,464,192,456,191,458,195,
    460,197,463,203,466,206,466,222,478,245,477,248,475,252,475,256,479,262,479,270,475,278,474,282,
    471,289,469,295,466,303,459,311,455,337,428,9,37,409,39,411,39,423,40,424,38,434,35,432,
    36,431,35,430,35,414,23,405,406,407,409,406,418,408,425,408,452,407,453,408,460,407,463,398,
    470,382,486,377,489,370,489,365,491,357,498,345,505,344,504,351,493,355,480,377,454,380,447,398,
    421,398,418,401,415,10,157,400,161,408,160,411,161,420,168,428,178,434,177,430,172,423,172,420,
    169,414,16,119,400,120,405,128,414,131,424,139,437,151,453,158,460,165,464,161,461,160,457,158,
    456,140,428,138,422,131,412,128,403,125,404,18,20,399,23,402,23,407,28,416,28,427,30,441,
    32,446,32,458,30,469,27,473,18,480,16,475,17,443,18,442,16,435,16,418,17,417,17,403,
    3,113,387,117,399,118,393,10,350,386,348,387,345,394,335,407,332,414,329,416,329,418,338,410,
    341,403,345,399,7,73,381,71,385,71,390,74,393,76,398,78,399,78,393,29,386,372,382,375,
    381,381,376,387,374,395,370,401,368,409,358,429,341,451,341,453,338,455,339,456,338,458,342,456,
    344,452,347,450,347,448,349,447,352,441,356,437,364,423,369,418,370,413,373,410,380,395,381,388,
    383,386,385,377,387,375,15,350,365,347,368,340,382,331,390,329,388,332,377,330,377,325,382,314,
    406,315,412,325,407,334,398,345,380,345,377,349,371,8,22,345,25,347,25,353,28,360,29,388,
    27,391,18,376,18,349,5,367,336,364,339,364,344,367,343,368,340,8,399,330,397,330,394,335,
    395,336,393,337,394,338,399,334,400,332,35,332,319,331,320,333,323,332,334,329,337,323,352,324,
    355,322,359,318,363,313,376,310,378,304,392,300,397,298,405,293,411,283,415,279,419,278,424,285,
    423,293,419,304,409,307,403,305,397,317,379,317,375,320,373,322,376,325,376,328,373,329,364,332,
    358,332,349,336,333,336,325,332,321,6,140,319,139,334,142,343,144,340,142,331,143,325,14,346,
    312,341,318,341,322,344,327,345,339,341,346,342,351,345,350,347,344,347,336,351,323,351,319,349,
    317,350,316,4,373,310,369,319,370,324,374,315,4,405,306,406,307,405,310,404,309,11,77,306,
    74,306,71,309,70,315,66,324,65,335,68,338,71,336,74,323,76,321,78,311,7,368,283,366,
    284,365,287,366,299,368,298,370,293,370,287,3,392,271,388,270,388,274,7,351,263,348,270,347,
    280,351,288,354,279,354,267,353,264,9,94,255,90,256,90,262,87,266,86,273,88,277,90,275,
    91,262,93,260,4,115,251,118,255,117,258,114,255,5,64,248,60,254,59,258,62,259,66,250,
    7,367,247,365,247,362,251,362,269,366,279,368,266,366,248,5,70,237,68,238,66,243,69,243,
    71,240,4,77,224,73,227,74,229,77,226,5,317,219,317,224,319,226,320,223,319,219,32,329,
    216,329,240,327,248,324,252,325,293,323,296,324,295,325,297,327,292,326,287,328,283,329,263,330,
    262,329,258,330,257,332,258,333,264,334,263,339,271,338,272,339,282,342,294,344,292,343,290,345,
    279,343,266,340,257,340,246,339,245,340,242,338,232,333,220,3,71,206,68,212,72,208,69,151,
    200,147,202,139,210,133,219,126,226,125,231,122,233,119,242,116,244,110,258,107,261,106,266,104,
    268,103,275,96,291,95,304,91,315,90,327,88,329,84,327,84,335,86,339,90,369,92,390,96,
    395,95,396,95,407,97,409,98,415,100,418,101,416,100,409,98,406,97,396,101,388,98,370,96,
    366,95,356,95,330,96,329,98,297,103,288,106,279,106,271,110,265,113,263,116,266,116,270,117,
    269,118,260,121,258,132,237,138,231,143,223,155,213,155,211,159,207,155,208,142,218,131,233,125,
    237,124,234,126,229,130,225,133,219,147,205,146,203,147,202,149,204,4,366,194,366,205,367,205,
    368,198,5,194,180,192,179,186,180,184,184,191,183,8,354,178,352,185,353,191,355,195,356,194,
    357,196,356,192,357,186,5,365,165,364,170,367,176,368,170,367,166,12,178,161,170,160,164,163,
    158,163,150,166,133,175,125,182,123,187,132,183,148,173,159,169,165,163,15,157,148,151,148,148,
    151,140,152,136,156,122,164,107,177,98,191,114,175,131,163,132,161,137,158,140,158,151,151,154,
    151,22,183,140,183,141,187,141,194,139,202,142,208,147,217,148,232,153,260,175,256,171,256,169,
    247,160,233,150,226,147,216,138,215,139,216,142,214,143,204,135,195,133,190,134,187,138,25,396,
    130,392,133,393,143,388,152,387,172,386,173,384,170,383,160,381,158,376,173,376,182,379,189,379,
    196,386,216,387,226,386,266,387,264,388,268,389,268,388,265,393,262,392,165,394,149,393,142,395,
    138,54,73,201,73,205,77,201,81,193,90,183,91,180,104,167,123,152,135,149,141,146,142,144,
    148,142,160,132,168,131,175,126,176,127,192,126,198,127,204,130,215,131,223,135,224,134,231,137,
    250,149,264,161,276,175,287,195,290,198,293,208,298,214,298,221,302,226,302,223,299,217,297,203,
    292,190,284,174,276,164,255,145,243,136,224,128,223,129,213,124,205,125,200,123,191,123,181,125,
    175,124,167,125,140,135,131,142,129,142,116,150,91,176,13,346,120,349,133,351,136,353,151,356,
    150,358,147,362,151,363,149,357,143,357,140,351,134,352,127,350,123,3,366,107,365,115,368,119,
    8,39,107,32,111,27,116,26,120,28,123,38,115,38,113,41,111,14,309,106,315,118,320,122,
    321,126,334,143,341,146,340,135,331,110,328,107,329,123,327,124,322,121,318,113,311,106,8,381,
    105,376,107,377,128,379,128,380,126,380,115,381,114,380,106,9,295,98,296,106,298,107,294,111,
    295,114,298,114,298,109,302,105,302,101,29,211,98,209,100,212,103,219,103,231,115,233,115,239,
    120,244,121,258,128,268,136,274,144,279,148,279,150,281,151,296,172,305,187,305,191,310,199,312,
    207,316,208,311,200,308,189,305,186,293,162,274,138,263,128,242,113,219,103,215,99,8,179,93,
    177,94,175,93,165,97,167,98,170,96,172,97,176,96,14,254,92,251,95,252,96,253,95,259,
    102,271,112,303,149,306,149,305,145,297,132,286,121,276,107,264,96,257,92,6,212,81,218,86,
    222,87,226,86,218,81,214,80,7,379,79,376,81,375,86,376,92,378,92,383,86,383,82,10,
    210,81,195,78,188,78,181,80,166,81,158,84,155,87,166,87,177,83,205,83,4,337,69,340,
    71,339,75,335,72,8,279,68,280,72,286,79,293,85,298,86,293,80,293,78,283,69,10,271,
    68,267,68,266,72,262,76,263,77,264,75,265,76,267,70,269,69,270,71,6,162,57,161,60,
    158,61,154,60,155,57,159,56,5,296,56,292,61,289,62,293,63,293,59,5,31,57,26,56,
    23,59,23,62,27,63,22,105,59,97,58,92,55,80,63,68,63,67,64,68,70,72,71,74,
    74,70,77,66,85,46,95,43,101,50,100,65,92,70,86,79,79,80,77,79,74,82,71,93,
    66,104,63,6,64,51,61,54,61,59,63,61,67,61,68,52,10,303,45,301,53,307,62,308,
    72,317,88,318,87,316,82,317,77,310,57,310,47,3,238,46,241,48,245,45,22,325,44,324,
    54,331,61,332,86,338,99,340,97,340,87,345,85,345,75,343,70,344,64,347,58,351,55,351,
    51,349,48,346,47,341,56,338,59,334,59,331,56,330,47,328,44,6,35,41,30,42,27,47,
    28,51,32,50,36,46,3,274,37,272,36,270,41,5,254,35,253,45,268,57,273,58,264,43,
    9,97,32,94,37,93,43,96,47,100,47,100,44,103,40,103,34,101,32,113,235,55,233,52,
    228,51,221,47,212,39,200,36,199,37,203,43,211,45,216,49,215,53,209,53,204,51,188,51,
    180,54,172,54,170,52,171,50,169,47,167,46,160,47,155,43,155,40,164,33,177,32,188,35,
    196,34,196,32,192,29,180,26,162,27,154,31,150,37,151,42,148,46,139,48,131,52,128,51,
    129,46,127,44,119,43,111,44,104,48,104,53,106,54,122,53,123,54,117,61,129,60,132,61,
    133,63,117,70,112,74,105,76,96,82,83,87,80,91,74,94,70,98,68,104,50,121,34,130,
    25,131,23,133,23,138,28,140,34,137,54,122,60,119,63,115,67,113,69,107,93,88,97,88,
    110,84,114,85,104,98,94,106,89,113,95,112,111,104,114,104,122,99,131,96,134,93,140,93,
    148,90,149,87,152,86,141,87,136,92,127,91,124,94,123,93,127,82,133,76,146,68,168,64,
    176,65,179,64,189,67,205,69,205,67,202,64,198,63,186,64,184,62,185,58,188,56,206,56,
    230,61,235,57,234,56,11,96,24,93,22,85,23,75,28,65,37,65,40,67,42,71,41,77,
    34,86,28,95,28,10,36,20,35,23,30,26,20,26,18,24,18,22,23,19,28,18,33,19,
    34,18,476,46,19,56,18,75,19,87,17,93,17,95,19,117,18,123,20,131,18,148,18,159,
    20,160,19,240,18,242,20,240,28,243,28,252,32,253,22,256,19,301,18,302,22,300,25,300,
    30,304,31,310,24,316,23,317,24,316,25,316,36,322,39,324,37,325,31,321,25,316,23,319,
    18,329,19,335,18,368,19,370,18,373,20,371,23,358,27,348,35,348,39,350,39,363,32,367,
    32,371,34,365,40,365,48,362,51,359,51,357,54,358,57,364,57,369,61,367,69,362,76,362,
    79,360,82,361,84,363,84,375,71,376,64,372,60,372,58,377,50,373,44,380,37,377,35,372,
    35,371,33,375,29,385,26,394,19,406,19,409,23,407,28,407,33,409,37,407,45,409,53,408,
    55,409,56,408,58,409,68,407,72,409,84,407,91,409,99,406,106,409,112,409,115,400,125,401,
    127,407,125,409,128,409,133,407,138,409,150,408,158,408,175,409,176,408,179,409,180,407,192,408,
    211,404,232,404,256,400,263,399,283,400,284,399,286,403,282,404,276,407,270,409,272,409,275,404,
    290,405,295,405,306,404,307,400,304,399,291,395,297,392,298,390,295,390,288,386,286,385,298,388,
    303,386,328,380,347,379,356,376,360,374,371,369,383,369,387,365,394,365,397,373,385,376,375,381,
    368,381,364,389,344,389,339,392,334,393,319,397,311,399,312,400,317,399,319,400,320,404,319,408,
    323,407,327,408,382,399,400,399,407,367,455,347,477,319,499,320,500,324,499,331,494,340,493,342,
    495,340,501,336,504,325,521,311,531,286,541,280,541,264,546,263,545,262,546,252,545,252,548,255,
    547,258,550,262,551,292,548,293,549,287,557,288,560,287,561,283,561,265,568,256,575,251,574,243,
    568,234,564,222,562,224,565,230,569,243,575,249,581,249,583,253,587,254,590,246,595,242,596,213,
    595,199,598,181,597,172,592,164,584,160,584,165,593,163,597,157,597,154,596,153,594,146,597,137,
    596,103,597,102,594,100,595,98,593,98,590,95,586,90,588,90,596,88,598,87,597,84,598,83,
    597,59,597,58,596,19,597,17,594,16,578,18,573,18,567,16,561,18,554,16,549,16,541,18,
    535,16,531,16,526,18,520,22,516,23,510,31,507,37,498,35,494,33,493,23,502,22,508,20,
    510,16,508,17,504,16,490,18,487,24,485,30,480,32,480,34,484,38,471,39,458,41,456,42,
    457,42,492,47,497,46,506,43,511,43,516,47,518,45,527,47,528,49,527,51,529,50,536,52,
    536,60,529,61,523,63,521,63,508,60,498,59,481,56,472,55,451,54,447,50,444,48,437,50,
    436,53,439,54,444,57,441,55,429,56,425,53,415,50,412,48,407,46,391,47,390,46,387,52,
    383,51,372,49,368,50,360,49,354,47,353,47,339,54,308,54,300,57,295,57,290,59,288,60,
    266,59,264,54,271,53,284,47,301,48,303,46,318,44,319,41,335,38,341,36,338,35,322,37,
    314,39,289,33,295,25,308,23,313,23,323,17,333,16,332,17,291,19,285,17,284,16,279,17,
    267,26,250,30,246,32,242,32,238,35,236,38,228,42,223,43,217,47,214,49,206,54,201,54,
    197,58,194,60,197,58,202,55,203,54,205,54,209,48,219,47,224,44,226,45,228,58,210,72,
    185,81,173,79,173,77,177,72,181,64,192,59,195,58,193,62,186,66,183,75,170,90,156,91,
    158,89,159,84,169,90,162,107,149,118,138,116,137,108,142,106,145,101,147,100,145,124,129,138,
    125,143,120,150,119,153,117,153,115,150,112,151,110,159,111,162,109,168,109,174,107,193,107,194,
    108,202,107,201,105,197,104,174,104,173,103,166,104,161,109,154,110,152,109,149,111,150,112,149,
    113,146,112,131,118,109,130,95,142,89,149,84,152,82,156,62,179,52,194,52,196,48,200,47,
    204,43,208,42,214,36,219,32,214,36,206,36,203,50,179,69,155,68,154,59,163,56,169,46,
    180,35,199,31,203,27,212,24,215,23,221,25,228,23,231,23,234,20,238,17,239,16,238,16,
    220,17,219,16,208,17,207,18,176,16,164,17,159,16,152,19,143,16,138,16,126,19,119,16,
    113,17,109,17,88,16,87,17,84,16,83,17,77,23,71,23,68,18,69,16,66,17,65,16,
    56,18,51,18,48,16,45,16,38,19,35,30,35,31,36,35,35,43,26,4,0,0,0,613,
    427,613,427,0,
};
static const short kVortexOutline4[] = {
    4,335,578,332,579,329,582,329,584,8,178,577,180,584,182,586,193,590,201,590,201,587,186,580,
    180,579,6,388,574,388,579,390,581,398,580,398,576,394,573,7,147,571,147,574,151,581,155,583,
    156,581,155,577,149,571,9,389,560,382,561,375,564,370,568,369,573,372,573,377,570,387,569,389,
    566,6,159,558,162,566,173,572,172,568,167,562,162,558,7,107,554,106,561,110,570,113,572,115,
    568,115,563,113,559,7,343,553,339,554,337,557,336,561,337,567,341,564,344,558,5,210,553,210,
    556,213,558,216,557,215,555,7,131,550,131,553,134,559,137,560,138,559,137,555,133,550,4,109,
    540,110,543,113,546,111,539,5,143,536,142,538,145,543,152,547,149,541,4,336,526,333,529,329,
    528,334,525,6,411,522,410,528,405,530,404,529,405,524,408,521,14,91,522,90,530,97,549,95,
    554,93,571,94,573,97,574,99,568,97,550,100,546,100,542,97,535,96,528,93,522,5,235,521,
    243,521,245,517,238,516,235,518,7,33,495,29,497,23,503,24,508,28,508,33,504,35,499,6,
    298,494,293,495,287,499,284,503,294,499,298,496,5,97,490,97,493,99,497,101,498,101,495,10,
    85,490,84,492,85,505,88,511,92,506,93,507,95,506,95,503,91,494,87,490,5,90,477,89,
    479,91,483,95,484,93,479,35,125,474,127,479,130,481,128,482,131,484,136,492,149,506,152,511,
    156,514,154,515,137,504,136,505,126,498,123,498,123,501,127,507,126,511,127,513,130,509,138,508,
    143,513,156,521,167,530,172,532,178,537,184,539,187,542,195,545,196,544,192,541,190,536,185,531,
    171,522,133,485,132,482,4,270,473,269,472,260,477,263,477,4,281,470,285,469,286,467,282,467,
    7,209,465,209,468,222,477,241,474,234,471,221,470,212,465,5,296,461,290,464,288,467,291,464,
    293,465,18,52,450,52,488,51,491,48,493,46,508,44,510,44,515,48,517,47,526,52,527,51,
    535,59,529,63,517,61,503,59,500,59,486,55,471,55,458,13,35,440,34,440,33,446,33,459,
    31,468,29,472,20,480,19,485,22,485,30,479,35,478,38,462,38,445,8,130,416,131,421,139,
    436,150,450,155,454,139,428,136,420,133,416,4,164,411,162,420,170,428,174,430,9,304,404,301,
    404,293,412,283,416,280,419,280,422,283,423,291,419,303,409,7,381,384,376,390,362,424,368,417,
    369,413,375,405,380,392,12,344,378,341,380,340,384,331,391,328,389,330,379,325,384,316,403,317,
    409,321,408,333,398,338,391,6,315,374,309,382,309,385,305,394,315,380,316,375,4,320,365,318,
    365,317,371,319,370,16,25,339,28,340,27,354,30,359,29,360,30,362,29,364,30,389,27,393,
    24,391,24,387,22,383,18,380,16,368,17,367,16,348,13,332,338,329,341,326,348,327,353,324,
    358,325,369,323,374,327,372,328,368,327,365,331,358,330,352,333,344,4,346,324,345,326,346,334,
    347,331,15,94,313,91,320,90,331,86,333,87,336,87,347,91,365,92,387,95,391,97,391,99,
    388,99,380,94,357,94,329,95,328,5,401,310,400,314,403,317,402,316,403,311,8,76,308,72,
    309,70,318,67,324,68,335,74,324,74,320,76,316,21,398,299,393,303,391,301,390,302,387,328,
    380,349,380,357,376,363,376,369,373,380,371,381,371,384,375,376,374,374,380,368,381,361,386,351,
    388,338,392,329,393,314,398,303,7,58,280,55,280,53,288,49,296,50,306,52,305,57,290,5,
    104,279,102,284,101,282,99,286,99,292,3,341,272,342,283,343,275,4,57,268,56,270,57,276,
    58,273,6,351,267,349,274,349,282,351,285,352,283,352,268,6,404,261,402,262,400,267,400,281,
    402,280,404,275,5,364,256,363,263,364,266,366,267,366,257,11,128,241,125,244,121,246,119,245,
    117,247,118,250,121,252,121,254,123,249,124,250,124,247,4,32,225,34,224,35,227,34,228,12,
    329,220,331,232,331,239,329,242,330,247,339,265,338,260,339,252,338,244,339,243,337,232,331,220,
    5,46,208,43,211,44,214,46,213,47,210,9,69,188,68,191,61,196,59,202,56,204,55,210,
    58,208,60,202,64,198,8,161,165,160,164,155,165,136,174,126,184,145,175,150,171,153,171,26,
    391,150,389,153,388,160,389,161,387,179,385,180,383,177,382,162,381,162,380,168,377,173,377,182,
    380,189,380,197,384,204,387,216,387,250,389,255,391,254,392,250,392,224,393,223,392,222,393,214,
    392,213,392,153,7,105,148,96,153,95,155,96,156,94,157,98,155,98,153,4,353,140,353,147,
    355,147,356,142,7,197,136,197,139,204,142,209,146,214,146,206,138,200,135,17,222,130,223,133,
    234,137,253,150,268,164,277,175,291,198,294,207,296,208,296,203,291,190,283,174,277,167,259,150,
    241,136,238,136,234,133,21,168,128,163,127,157,131,153,131,147,133,144,136,139,137,123,148,121,
    148,120,150,116,151,99,169,102,168,104,165,123,150,124,151,126,149,137,147,152,137,158,131,166,
    130,9,195,125,201,126,203,128,219,130,218,128,214,126,211,128,208,128,207,126,13,143,117,138,
    117,126,121,106,133,76,163,69,173,67,174,55,193,68,178,69,175,98,145,116,132,137,124,4,
    315,114,317,118,320,120,320,117,11,329,112,329,120,331,123,328,126,321,122,321,125,330,137,336,
    143,339,143,340,138,332,116,7,229,110,238,119,254,124,256,126,253,122,242,114,233,110,7,38,
    109,35,110,29,116,28,121,30,121,37,114,39,110,5,378,108,376,119,377,123,379,124,380,111,
    13,68,107,65,108,43,127,34,131,25,132,24,138,29,139,36,135,41,130,59,118,61,115,63,
    115,66,112,10,255,93,261,103,269,109,287,128,301,146,304,146,296,132,284,120,277,109,264,97,
    4,146,88,145,87,141,91,145,90,8,67,87,61,87,58,90,50,93,45,98,45,100,53,98,
    67,90,4,160,86,165,86,167,84,162,84,6,380,81,377,81,376,83,377,91,382,86,382,83,
    6,333,74,333,86,338,94,339,88,335,80,335,75,5,78,74,70,78,69,85,72,84,79,78,
    5,342,73,340,79,341,83,344,84,344,75,4,281,70,289,80,293,82,291,78,6,191,65,192,
    66,194,65,197,67,202,66,199,64,10,375,63,369,64,367,70,365,71,363,75,363,81,366,80,
    369,75,374,71,376,66,9,103,60,91,57,78,64,68,64,68,68,72,71,79,72,95,64,101,
    63,5,28,57,25,58,24,60,25,63,28,60,7,167,56,163,60,156,63,151,61,155,56,165,
    56,166,55,5,64,52,61,57,63,60,67,60,68,53,12,347,48,345,49,343,54,338,60,332,
    61,333,70,337,66,338,67,343,66,346,59,350,55,350,51,10,303,48,302,51,303,55,309,65,
    309,73,315,80,316,76,311,65,309,50,308,48,5,325,45,324,47,325,53,330,58,329,47,7,
    105,51,108,53,126,51,128,47,123,45,114,44,107,47,54,209,54,204,52,186,52,181,55,170,
    55,168,49,158,48,154,43,151,43,147,47,138,49,120,58,127,60,138,57,139,58,131,66,123,
    68,114,74,103,78,96,83,87,87,84,87,72,97,69,103,71,104,76,101,87,91,89,91,92,
    87,115,83,116,86,92,111,99,108,103,108,111,103,114,103,120,98,127,97,131,94,131,93,127,
    93,123,97,120,96,120,93,124,88,127,80,146,67,157,66,161,64,179,63,187,55,202,55,203,
    54,209,55,5,34,42,32,42,29,45,29,49,35,46,12,202,38,204,43,211,44,218,50,215,
    57,216,56,226,60,232,59,234,57,232,53,220,48,214,41,5,255,37,254,44,264,53,271,57,
    263,43,15,376,36,372,35,367,39,366,41,367,49,364,52,359,53,359,55,363,55,368,59,370,
    59,374,55,376,50,370,45,377,38,7,97,33,94,40,95,45,97,46,99,45,103,37,102,34,
    11,152,39,158,38,165,32,182,32,187,34,193,34,193,32,190,29,183,27,162,28,153,33,6,
    318,25,316,30,317,34,320,37,323,37,323,28,11,95,24,87,23,83,26,76,28,68,35,67,
    40,68,41,71,40,76,34,85,28,94,28,7,38,18,33,26,22,27,16,24,16,22,19,19,
    28,17,388,19,34,33,35,43,25,44,19,46,17,56,18,58,16,66,16,71,18,86,16,94,
    16,98,18,99,17,107,18,114,16,122,18,140,16,164,17,165,18,168,17,169,18,240,17,243,
    19,242,26,248,30,252,29,252,20,254,18,261,17,292,17,293,16,297,17,300,16,303,18,303,
    22,301,24,301,30,303,30,312,22,315,22,319,17,327,16,332,18,335,17,358,17,359,18,372,
    17,376,19,371,24,364,25,355,29,349,35,349,38,358,33,370,32,375,28,382,27,392,18,398,
    17,406,18,409,20,410,22,409,27,410,34,409,43,410,101,408,106,410,110,410,115,402,124,403,
    125,407,124,410,126,409,136,410,182,408,194,409,213,405,229,405,252,408,257,407,260,409,259,410,
    260,410,279,406,287,407,288,406,296,408,300,408,318,410,337,410,381,405,390,404,396,401,399,405,
    395,409,396,408,400,409,408,408,419,410,435,409,462,379,490,368,491,348,504,342,509,340,508,340,
    505,344,502,349,495,352,484,357,475,375,454,395,424,400,413,400,410,396,413,393,419,387,426,387,
    428,382,433,375,445,361,463,339,486,324,496,326,497,330,493,333,493,339,490,343,494,341,501,332,
    511,329,518,314,530,304,535,288,541,279,542,261,548,262,550,276,550,294,546,295,548,289,555,289,
    558,298,554,310,546,319,543,328,538,334,537,351,524,352,526,348,531,336,540,333,549,337,550,343,
    542,355,531,358,530,360,534,363,534,377,526,380,526,389,520,389,516,386,516,368,525,364,523,368,
    518,369,513,386,496,380,498,378,494,390,482,408,469,410,471,409,480,410,490,401,496,399,505,394,
    511,396,512,405,509,406,511,392,524,392,529,394,531,402,530,404,535,410,539,409,547,410,556,409,
    574,410,576,407,580,399,583,400,585,404,586,406,585,409,588,409,594,407,596,397,598,373,597,359,
    599,357,595,362,589,364,585,363,583,361,583,356,588,354,593,349,598,332,598,329,597,327,593,319,
    598,269,598,261,596,258,589,260,587,262,577,269,572,271,569,274,569,281,565,282,563,279,565,275,
    565,267,569,264,569,256,576,247,573,239,567,226,564,230,568,243,574,256,589,250,594,241,597,223,
    597,222,596,215,597,213,596,208,598,199,599,180,598,174,595,165,585,162,585,162,588,167,595,164,
    598,154,597,98,598,96,596,95,587,92,587,90,590,91,595,90,598,77,598,76,599,70,598,64,
    599,50,597,19,598,17,596,15,582,16,577,15,526,16,520,19,518,21,513,15,509,16,503,15,
    499,16,400,18,398,23,399,24,407,29,415,29,427,32,431,31,433,32,434,34,425,33,400,36,
    393,39,398,39,405,41,412,41,435,42,436,41,439,43,452,42,456,43,457,42,459,43,492,47,
    491,47,478,48,477,47,474,48,473,48,451,49,449,46,433,47,430,49,429,53,435,55,434,54,
    423,49,414,46,405,44,387,44,372,43,371,45,342,47,337,48,320,50,318,51,309,48,310,48,
    316,44,324,41,340,36,347,34,331,36,313,35,305,37,298,36,296,30,302,25,311,24,317,25,
    319,23,326,19,333,18,340,16,341,14,339,15,310,16,309,15,271,19,260,30,244,32,237,35,
    235,36,231,34,228,37,227,42,220,42,217,38,220,33,219,31,214,35,206,35,203,33,203,29,
    211,24,217,26,228,23,232,23,236,16,243,15,242,15,208,16,207,16,191,15,190,16,187,16,
    166,15,165,15,152,16,151,16,139,15,138,16,88,15,87,16,79,15,78,22,71,22,69,19,
    70,15,69,16,63,15,61,16,53,15,37,4,0,0,0,613,427,613,427,0,
};
static const short kVortexOutline5[] = {
    5,92,588,91,590,92,596,95,595,96,589,7,179,579,181,584,185,587,191,589,199,589,197,586,
    187,581,6,390,573,388,578,392,581,396,580,397,576,395,574,4,149,573,150,578,154,581,155,578,
    12,230,566,245,574,251,583,257,588,260,585,261,576,268,571,268,570,264,570,258,576,254,577,236,
    567,6,388,562,383,561,378,563,370,570,370,572,387,568,5,160,560,162,565,171,569,165,561,162,
    559,7,107,556,107,563,112,571,114,570,115,566,114,562,109,556,4,97,556,94,569,96,572,98,
    569,6,342,554,339,555,337,559,337,565,340,564,343,558,3,144,538,144,540,150,544,6,92,523,
    91,531,95,542,98,545,99,541,94,525,8,343,522,334,530,321,536,318,535,323,529,329,527,330,
    525,339,521,5,356,504,357,506,354,509,351,508,352,506,5,369,500,371,503,365,510,362,506,366,
    500,29,146,501,150,505,150,507,164,520,161,522,156,519,153,515,151,515,147,511,142,509,146,514,
    148,514,156,521,161,523,162,525,176,535,182,537,188,542,191,541,190,537,186,533,181,531,176,526,
    169,522,164,516,162,517,161,516,162,514,148,501,6,124,499,126,505,129,508,132,508,133,504,129,
    500,7,32,497,29,498,24,503,24,507,28,507,32,504,33,502,50,378,492,365,493,361,497,351,
    503,345,509,340,511,335,510,329,519,323,525,314,531,299,538,295,538,286,542,271,545,269,547,266,
    547,265,549,280,549,298,544,299,545,290,555,291,556,297,554,310,545,320,542,326,538,334,536,343,
    528,354,521,355,524,351,529,336,541,334,548,337,549,351,533,361,527,363,528,362,533,366,531,369,
    531,387,520,387,518,384,518,364,527,362,526,366,517,364,515,371,510,381,499,377,497,6,86,492,
    85,494,87,499,93,505,94,503,90,495,4,408,467,406,467,399,472,397,476,5,210,467,211,469,
    222,476,229,474,212,466,30,53,459,52,463,53,464,52,471,53,490,48,497,47,506,44,513,50,
    516,48,525,51,525,54,527,53,533,59,528,61,518,61,512,60,512,61,516,57,519,56,516,51,
    511,52,506,55,502,57,505,58,503,59,504,59,507,58,485,53,467,54,465,8,35,452,34,463,
    29,473,22,479,21,484,24,483,35,474,36,470,7,44,431,43,432,44,435,43,483,44,488,46,
    489,47,446,3,135,425,142,437,141,432,14,396,416,365,459,342,483,341,488,345,495,344,498,347,
    496,350,490,352,481,357,473,374,454,376,449,386,437,395,421,7,293,414,288,414,284,416,281,419,
    281,422,285,422,292,417,3,302,406,295,413,301,410,9,378,391,376,394,377,397,375,399,374,398,
    375,399,369,410,372,408,376,400,13,337,389,335,389,330,393,328,391,328,384,326,385,316,405,317,
    407,321,406,322,403,326,399,329,400,334,395,12,20,384,18,387,17,393,19,396,24,397,25,407,
    29,411,31,411,33,392,31,391,25,397,22,384,4,379,361,377,363,377,369,380,364,9,92,358,
    93,365,92,381,95,388,98,384,97,383,98,381,97,374,93,366,4,331,342,329,343,328,346,330,
    350,7,92,331,88,338,88,345,91,353,93,352,92,351,93,349,25,45,327,44,330,45,334,42,
    338,41,345,37,349,31,362,31,370,33,376,32,378,33,384,35,386,34,388,38,390,40,396,42,
    417,44,422,49,424,53,431,53,425,46,410,44,391,41,381,41,355,46,329,10,390,320,390,324,
    388,325,385,340,381,348,381,357,383,356,387,345,387,338,391,330,6,74,310,71,314,68,325,68,
    330,71,328,75,316,5,392,308,391,308,390,313,391,316,393,312,20,31,308,29,317,28,318,27,
    316,27,319,25,321,22,331,19,336,19,340,21,341,25,335,28,333,29,334,28,344,29,355,34,
    344,34,330,33,329,34,312,31,310,3,402,268,401,268,401,275,4,18,255,19,256,18,259,17,
    258,4,17,251,18,252,17,256,16,255,5,331,225,332,245,335,251,336,234,333,226,7,155,167,
    150,168,136,175,133,179,137,178,142,174,145,174,4,272,165,290,194,288,186,281,173,19,390,161,
    390,173,388,182,389,184,386,186,383,182,382,177,380,175,378,176,381,197,387,208,388,244,390,247,
    392,236,392,200,390,181,391,180,390,179,391,177,3,88,152,78,163,81,162,7,141,138,129,144,
    125,148,127,146,131,147,139,144,141,142,5,38,131,25,133,25,138,30,138,36,134,6,322,125,
    335,141,339,140,339,137,334,125,329,127,6,284,124,301,144,299,143,300,140,295,132,286,124,9,
    139,119,131,120,113,129,112,131,106,134,90,151,102,140,114,132,138,122,4,233,112,240,119,249,
    121,242,115,4,35,112,32,114,31,118,35,114,6,258,95,261,101,281,121,284,122,277,110,263,
    97,8,89,87,85,87,84,89,76,94,71,100,71,102,73,102,89,89,9,66,88,63,87,58,
    91,53,92,47,98,51,98,55,96,58,93,64,91,5,379,82,377,83,376,86,377,89,381,86,
    7,78,76,75,75,72,77,70,80,70,83,75,81,78,78,5,310,68,310,72,314,76,314,73,
    312,69,7,373,63,369,65,367,71,364,74,364,79,374,70,375,65,9,99,60,95,58,90,58,
    83,63,69,64,70,69,74,71,79,71,99,62,5,162,62,176,63,183,58,182,56,170,56,4,
    190,53,195,54,196,52,190,52,4,66,52,62,56,63,59,67,58,12,347,49,345,50,340,60,
    338,62,335,61,334,62,335,65,338,64,342,65,345,59,350,54,350,52,4,304,49,304,54,307,
    59,308,51,8,219,50,220,57,226,59,230,59,232,57,232,55,229,52,221,49,8,373,48,370,
    48,367,50,365,53,367,57,371,57,374,54,375,51,3,328,47,325,48,327,54,7,106,51,109,
    52,123,51,126,49,126,47,114,45,107,48,36,167,50,166,49,156,49,154,44,151,44,146,48,
    140,49,122,58,129,59,136,55,140,56,141,58,133,66,128,69,121,70,114,75,108,76,100,81,
    100,84,108,84,110,82,117,81,118,86,106,97,98,107,104,106,114,101,118,93,124,86,123,81,
    128,76,146,66,149,66,147,62,155,55,167,54,3,34,44,31,44,30,48,5,255,39,255,44,
    261,50,269,54,260,40,6,204,40,206,43,213,44,216,46,211,40,208,39,6,375,38,372,36,
    367,40,367,43,370,44,373,42,6,100,34,96,36,95,39,96,44,98,44,102,37,9,186,28,
    179,27,164,28,156,31,153,37,156,38,165,31,179,31,190,33,7,82,27,77,28,71,33,68,
    40,73,37,76,33,82,30,6,318,26,317,33,319,35,322,35,323,30,321,27,5,86,25,87,
    27,94,27,94,24,92,23,13,387,20,386,19,378,20,371,25,360,27,356,29,351,34,351,36,
    362,31,370,31,374,28,381,27,386,23,234,18,18,34,15,36,16,38,15,48,15,49,16,54,
    15,56,16,57,15,71,15,72,16,80,15,223,16,228,15,229,16,243,16,244,17,243,25,244,
    27,250,29,251,18,253,16,305,15,306,18,304,19,302,28,305,28,308,24,313,22,319,16,322,
    15,404,16,411,21,411,33,412,34,411,41,411,55,412,56,411,57,412,67,411,69,411,116,404,
    122,412,126,411,131,411,147,412,148,411,154,412,174,411,175,412,178,410,184,410,216,409,217,409,
    231,412,239,411,240,412,242,412,271,411,272,412,273,408,288,411,297,410,332,412,342,411,382,408,
    387,408,391,410,391,412,394,410,400,411,406,410,411,411,491,402,497,402,501,398,509,399,510,403,
    509,410,504,412,505,412,508,408,512,402,515,393,524,394,529,401,529,404,526,405,522,410,518,412,
    520,413,525,409,531,405,532,405,534,412,539,411,577,408,581,401,583,401,584,408,584,410,586,411,
    589,410,594,407,597,403,599,358,600,356,596,357,592,362,587,362,584,358,587,357,591,353,596,348,
    600,334,600,333,599,330,600,326,597,327,596,326,595,320,599,310,600,272,600,271,599,266,600,261,
    598,257,592,254,592,248,596,240,598,188,600,178,599,163,585,163,588,168,594,169,597,168,599,116,
    599,115,600,112,599,111,600,110,599,101,600,100,599,99,600,97,599,96,600,95,599,91,600,45,
    600,44,599,29,600,26,599,25,600,24,599,23,600,19,599,14,593,14,521,19,516,20,513,16,
    512,13,509,14,504,14,485,13,484,13,463,14,462,14,442,13,441,13,424,14,423,13,406,14,
    403,13,401,14,400,13,399,15,397,14,394,16,386,15,377,13,372,13,357,12,356,12,331,14,
    312,13,280,16,260,19,259,19,257,23,253,23,251,18,248,18,245,20,244,24,249,26,248,30,
    243,31,237,34,235,35,231,30,226,32,219,30,214,28,213,25,217,25,220,28,226,24,232,24,
    237,19,241,18,245,15,246,13,244,14,236,13,231,14,230,14,216,13,215,14,209,14,70,13,
    69,14,66,14,35,17,33,34,34,43,23,43,20,40,19,34,26,17,27,15,25,15,21,4,
    0,0,0,613,427,613,427,0,
};
static const short kVortexOutline6[] = {
    5,94,589,92,590,92,595,94,594,95,591,6,181,581,184,586,194,589,197,588,188,582,182,580,
    8,248,575,252,583,255,586,258,586,260,584,260,576,253,580,252,577,3,150,575,151,578,154,579,
    7,389,575,389,578,391,580,395,580,397,578,396,575,394,574,7,387,563,381,562,375,566,373,569,
    374,570,385,568,387,566,4,162,561,162,563,168,567,165,562,5,108,557,107,559,110,568,113,569,
    114,563,14,314,543,311,542,312,543,311,544,307,543,305,545,301,545,295,549,292,554,293,555,299,
    552,305,547,306,544,310,545,9,173,528,173,531,176,534,190,541,190,538,188,536,180,532,177,528,
    175,527,4,92,526,91,529,93,533,94,527,7,382,521,375,522,365,527,364,531,368,531,374,526,
    381,523,10,363,521,357,522,346,535,339,539,336,542,335,548,339,547,342,541,350,533,361,526,8,
    52,515,48,523,53,524,56,530,59,527,59,523,55,519,54,515,8,410,513,402,516,394,524,394,
    527,397,529,402,527,405,521,409,517,26,348,515,342,512,340,515,337,513,334,513,330,520,322,527,
    320,527,317,531,312,532,301,538,297,538,289,542,280,543,268,548,277,549,285,546,290,546,300,542,
    305,542,313,535,316,534,321,528,327,527,330,524,341,520,24,366,511,361,510,360,507,358,508,361,
    511,360,514,358,514,355,511,351,511,350,515,351,518,334,531,329,532,324,536,317,538,315,541,318,
    542,326,537,332,536,345,525,356,520,360,516,361,513,363,514,5,126,500,125,501,126,504,131,507,
    132,504,6,32,499,29,499,24,505,25,506,30,505,32,502,6,51,497,48,499,46,512,49,512,
    51,510,52,503,12,371,493,369,495,366,494,362,497,376,499,374,500,368,509,371,509,379,501,378,
    499,375,498,376,494,5,54,481,54,497,56,497,58,490,55,481,5,35,467,23,479,23,482,27,
    480,34,473,3,45,453,44,481,46,485,19,389,428,383,434,377,443,376,447,370,453,369,456,346,
    480,343,486,345,493,348,492,349,484,356,473,375,451,375,448,379,445,380,442,385,437,387,433,386,
    432,5,290,416,289,415,284,417,282,421,285,421,6,29,396,25,400,25,405,28,407,31,402,31,
    399,7,326,389,324,389,320,399,318,400,319,404,327,396,328,393,5,21,386,19,388,20,395,23,
    394,23,389,7,38,353,32,365,37,370,37,367,39,365,38,362,39,354,6,32,334,31,335,32,
    340,30,341,31,344,33,341,6,33,316,31,316,26,322,20,338,22,338,31,328,6,74,313,72,
    315,71,319,72,320,74,318,73,317,13,29,226,25,232,27,242,25,243,22,239,20,242,24,246,
    26,246,26,244,29,243,30,237,34,234,34,231,4,28,216,26,219,29,221,30,218,9,382,187,
    381,193,387,204,388,231,390,239,392,228,391,197,390,193,389,194,5,35,133,34,132,26,134,26,
    137,28,138,6,327,129,329,134,337,140,338,137,335,128,331,127,4,237,115,240,118,243,118,242,
    116,7,263,100,272,109,271,105,269,103,268,104,265,100,264,101,4,56,93,53,93,49,97,53,
    96,6,87,88,79,93,72,101,79,97,82,92,86,91,9,122,85,120,84,118,88,113,91,101,
    105,109,102,114,97,117,90,121,88,7,113,78,108,77,104,79,102,82,104,84,108,83,113,80,
    5,77,77,75,76,72,78,71,81,75,80,6,374,65,371,64,369,66,365,74,365,77,373,70,
    10,97,61,92,58,81,64,77,65,72,64,70,66,74,70,79,70,84,67,90,66,6,180,58,
    173,56,170,57,167,60,167,62,176,62,3,132,56,125,58,129,58,4,64,54,63,58,66,58,
    66,54,5,347,50,345,51,341,59,341,62,349,54,6,220,51,220,55,222,57,231,58,228,52,
    223,50,7,373,49,370,49,367,51,367,55,369,57,373,54,374,52,6,108,51,119,51,124,49,
    118,46,112,46,108,49,27,165,50,155,50,153,48,153,45,151,45,148,48,135,52,133,54,139,
    55,143,59,140,60,135,66,128,71,117,74,116,78,119,79,126,74,130,73,131,74,137,71,146,
    64,144,62,145,60,150,59,154,55,164,54,166,53,5,256,40,256,44,262,50,266,52,260,41,
    5,206,40,207,42,209,43,210,42,209,40,5,372,37,368,40,368,43,370,43,373,40,5,100,
    36,97,36,96,39,97,42,100,39,5,162,31,156,32,154,36,155,37,158,36,4,164,29,177,
    31,185,30,184,28,4,81,29,79,28,75,31,77,32,4,318,27,318,33,321,34,322,31,3,
    87,25,93,26,92,24,11,385,21,382,20,371,26,365,26,359,28,352,35,360,31,369,31,374,
    27,378,27,382,25,8,42,20,39,21,34,27,17,28,16,30,19,33,34,33,42,24,6,247,
    18,245,19,244,25,248,28,250,27,250,19,6,317,16,315,14,309,15,305,20,303,26,313,21,
    212,17,16,22,16,26,14,37,12,40,13,41,12,44,13,50,12,52,13,55,12,75,13,80,
    11,95,13,96,12,105,13,107,11,111,13,112,12,116,13,147,12,159,14,173,14,189,12,239,
    13,240,14,242,13,248,14,249,13,250,14,299,13,301,14,304,12,314,11,319,13,347,13,348,
    14,397,13,407,15,412,19,414,22,413,24,414,25,414,55,415,56,413,76,413,115,414,117,408,
    121,412,120,414,124,414,152,413,153,414,163,413,166,416,192,413,203,413,216,412,217,414,221,414,
    250,413,251,413,268,414,269,412,280,412,294,413,295,412,317,414,333,416,335,415,336,416,347,418,
    350,416,352,416,364,414,369,415,376,414,377,415,393,413,407,413,440,414,441,413,447,414,448,412,
    462,414,478,413,481,414,483,413,492,414,493,412,495,409,494,404,496,404,499,399,507,399,509,405,
    507,413,499,415,501,413,510,415,516,414,527,416,529,414,536,413,578,412,579,413,582,412,592,409,
    598,406,600,399,601,373,601,372,602,359,602,356,604,350,603,328,604,324,602,323,603,319,602,285,
    603,265,601,254,602,252,600,257,597,257,594,254,593,247,598,223,599,211,602,179,602,174,598,174,
    600,171,602,140,602,139,601,84,602,67,605,60,603,56,604,46,602,21,602,13,596,13,592,11,
    588,11,578,12,577,11,573,12,570,11,567,12,565,12,547,11,546,12,523,11,522,12,519,15,
    516,17,516,16,513,12,516,11,515,11,485,8,480,8,468,10,465,11,457,10,452,11,444,10,
    438,11,416,10,413,11,410,9,404,10,403,9,394,11,392,11,384,9,380,10,376,9,369,10,
    368,8,361,9,358,7,356,8,347,7,344,9,343,8,325,10,323,11,315,11,274,12,273,12,
    263,11,262,12,254,11,250,11,181,12,180,11,175,12,103,11,100,12,96,11,95,12,91,10,
    77,11,75,10,67,11,64,11,30,12,29,11,26,13,24,14,19,4,0,0,0,613,427,613,
    427,0,
};
static const short kVortexOutline7[] = {
    5,183,581,183,584,185,586,194,588,194,586,4,258,580,254,583,255,585,259,584,6,390,574,389,
    577,392,580,394,580,396,576,393,574,6,386,564,383,562,376,566,375,568,384,568,386,567,6,109,
    558,108,563,110,567,113,568,114,566,113,563,3,303,548,297,549,293,554,4,317,540,320,541,323,
    538,319,538,4,345,537,337,542,336,548,339,546,8,307,537,295,539,290,542,280,544,282,544,283,
    546,292,545,305,540,5,334,532,332,533,330,532,326,536,329,537,4,376,523,365,527,365,530,368,
    530,5,361,522,358,522,350,532,352,532,360,526,6,406,516,399,519,396,523,396,527,402,526,405,
    521,6,337,516,333,517,332,519,333,522,337,518,336,517,7,53,516,52,520,54,521,55,527,57,
    529,58,524,54,521,4,353,512,354,516,353,520,358,516,4,126,501,127,504,131,506,131,504,4,
    50,500,48,504,48,509,51,506,5,31,500,27,501,25,505,26,506,29,505,7,409,496,405,497,
    405,500,400,508,402,508,408,503,410,498,3,45,460,44,472,46,477,5,29,400,27,400,26,402,
    27,405,28,405,4,325,391,322,394,322,398,325,395,4,20,388,19,391,22,394,22,388,14,0,
    373,0,479,3,455,1,452,3,449,3,429,2,428,3,418,1,415,3,404,2,398,3,396,2,
    384,3,383,6,31,319,29,319,29,321,26,324,22,335,30,326,4,28,232,30,231,34,233,32,
    230,5,390,199,388,204,387,202,390,231,391,228,6,328,130,329,133,333,137,336,138,335,129,332,
    128,4,107,79,104,80,105,83,108,81,6,372,65,370,65,369,70,366,74,372,70,373,68,4,
    144,64,140,62,132,70,135,71,7,94,61,91,59,82,64,71,65,74,69,79,69,90,65,5,
    168,61,174,62,177,60,177,58,172,57,5,347,51,345,52,345,55,342,59,349,53,6,221,52,
    221,54,226,58,230,57,228,53,224,51,4,155,53,163,54,164,51,157,51,6,372,50,368,51,
    367,53,369,56,372,54,373,52,6,109,49,110,51,116,51,121,49,118,47,112,47,10,152,46,
    148,49,141,50,135,53,141,55,145,59,148,59,151,56,150,54,147,53,4,257,41,257,44,262,
    48,260,42,4,159,32,156,33,155,36,158,35,3,173,29,182,30,181,28,8,370,29,369,27,
    361,28,359,30,358,29,353,34,359,30,369,30,3,382,22,376,25,380,25,8,41,22,38,23,
    33,28,19,28,18,30,19,32,33,33,40,25,5,247,19,245,22,245,26,248,27,250,22,6,
    314,16,308,17,304,24,307,24,312,19,314,19,248,0,0,0,371,0,348,3,342,3,326,5,
    322,6,264,9,250,7,246,8,243,6,240,7,239,6,238,7,223,5,212,8,183,7,181,8,
    166,6,162,9,138,8,135,9,134,8,131,9,127,8,125,9,118,8,106,9,104,8,97,6,
    96,8,95,6,92,6,87,4,82,4,65,3,64,5,53,5,37,7,32,6,29,8,27,7,
    24,14,13,21,11,26,6,29,5,36,6,37,5,40,6,42,5,67,5,71,6,78,4,84,
    5,91,2,94,3,104,1,110,3,112,2,113,4,115,3,116,5,120,5,123,7,131,5,154,
    5,156,7,157,6,162,9,167,10,172,8,175,9,183,6,184,7,195,4,202,4,216,7,217,
    6,218,7,231,6,247,10,253,9,255,11,288,10,293,6,296,6,298,8,304,6,311,6,317,
    8,319,7,344,10,399,8,416,17,415,19,418,21,419,24,419,34,421,44,419,59,419,76,418,
    77,419,79,417,90,418,105,416,108,418,110,419,123,421,127,420,129,422,135,420,147,424,162,422,
    164,422,173,424,175,423,176,424,185,422,192,418,198,418,225,419,226,418,233,419,235,418,243,416,
    244,416,249,418,251,416,261,417,262,416,266,417,288,414,301,416,306,416,316,421,329,426,351,425,
    352,426,353,425,363,426,369,423,373,422,379,419,385,419,391,421,396,419,401,418,415,416,416,415,
    426,418,440,416,443,418,446,415,457,417,468,416,475,417,474,419,479,418,483,419,494,423,499,420,
    509,420,518,422,522,422,526,419,538,419,552,418,557,416,559,418,561,416,564,417,565,415,571,416,
    572,415,576,416,583,414,586,413,595,407,602,391,604,386,603,380,604,379,603,371,606,366,606,363,
    608,359,607,358,609,320,609,313,607,296,608,295,607,280,607,265,604,246,606,236,609,227,609,223,
    606,211,606,210,607,196,607,195,606,183,607,181,606,178,608,171,607,164,608,162,606,157,607,153,
    605,131,605,130,606,103,605,88,607,77,612,71,613,62,612,55,608,50,609,44,607,27,607,26,
    608,22,607,13,601,9,595,7,584,8,580,6,578,6,569,9,559,8,558,9,551,7,536,8,
    535,7,527,8,518,6,514,8,510,6,506,5,498,6,493,4,492,4,488,2,487,0,482,0,
    613,427,613,427,0,
};
static const short kVortexOutline8[] = {
    13,199,613,195,612,194,610,188,609,182,610,179,612,169,612,168,613,167,612,153,612,151,610,95,
    610,90,613,10,206,613,312,613,309,611,297,612,271,608,253,608,233,613,220,611,219,612,213,611,
    5,402,518,397,523,398,526,400,526,403,523,17,427,507,425,510,426,522,424,527,423,560,420,571,
    421,576,420,583,421,584,419,591,416,594,416,599,407,606,397,608,372,609,364,613,427,613,20,0,
    499,0,613,54,613,45,610,32,610,24,612,11,605,5,598,0,574,2,567,1,560,4,554,4,
    544,3,543,4,542,3,533,4,526,2,512,3,508,2,501,17,426,380,425,383,426,386,424,391,
    425,399,423,402,423,415,420,422,422,438,420,463,421,473,423,478,423,488,425,490,425,493,427,494,
    427,381,13,426,192,423,199,424,200,422,218,423,261,422,262,422,285,421,291,419,294,419,303,423,
    328,427,334,427,192,14,0,164,0,285,1,269,3,266,5,255,2,243,3,241,2,240,2,228,
    3,227,2,203,4,188,3,182,1,179,4,329,131,332,135,335,135,334,129,4,0,90,0,156,
    4,144,4,103,4,92,61,88,61,80,65,86,65,5,224,52,223,54,225,57,228,57,228,55,
    6,35,28,20,29,20,30,21,29,28,30,32,32,4,248,21,246,22,246,25,248,25,29,308,
    0,311,0,316,3,329,5,367,5,368,4,406,3,418,12,423,20,422,21,423,31,425,35,426,
    51,424,63,425,64,423,70,424,72,423,76,425,78,425,91,424,92,424,107,423,108,424,112,423,
    113,425,116,425,124,427,126,427,0,8,254,0,256,3,262,5,281,3,282,4,294,0,299,1,
    299,0,5,211,0,231,1,236,3,250,1,250,0,6,161,4,169,5,171,3,177,3,182,0,
    158,0,8,17,0,0,0,0,46,2,41,1,35,5,15,12,6,16,4,
};
static const CardArtLayer kYugiohVortexLayers[] = {
    {0xFF180303, kVortexOutline1, ARRAYSIZE(kVortexOutline1)},
    {0xFF2F0C06, kVortexOutline2, ARRAYSIZE(kVortexOutline2)},
    {0xFF4B1D0D, kVortexOutline3, ARRAYSIZE(kVortexOutline3)},
    {0xFF6D3114, kVortexOutline4, ARRAYSIZE(kVortexOutline4)},
    {0xFF92481B, kVortexOutline5, ARRAYSIZE(kVortexOutline5)},
    {0xFFB76225, kVortexOutline6, ARRAYSIZE(kVortexOutline6)},
    {0xFFCC7E3D, kVortexOutline7, ARRAYSIZE(kVortexOutline7)},
    {0xFFD99C66, kVortexOutline8, ARRAYSIZE(kVortexOutline8)},
};
// END GENERATED CARD ART DATA

static ID2D1PathGeometry* g_vectorCardArt[11] = {};

static void ReleaseVectorCardArt()
{
    for (auto& geometry : g_vectorCardArt)
    {
        if (geometry)
            geometry->Release();
        geometry = nullptr;
    }
}

static ID2D1PathGeometry* CardArtGeometry(const CardArtLayer& layer, size_t slot)
{
    if (g_vectorCardArt[slot])
        return g_vectorCardArt[slot];
    ID2D1PathGeometry* path = nullptr;
    if (FAILED(g_d2dFactory->CreatePathGeometry(&path)))
        return nullptr;
    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(path->Open(&sink)))
    {
        path->Release();
        return nullptr;
    }
    sink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);
    size_t offset = 0;
    while (offset < layer.count)
    {
        const int points = layer.contours[offset++];
        sink->BeginFigure(D2D1::Point2F(layer.contours[offset],
                                       layer.contours[offset + 1]),
                          D2D1_FIGURE_BEGIN_FILLED);
        offset += 2;
        for (int i = 1; i < points; ++i, offset += 2)
            sink->AddLine(D2D1::Point2F(layer.contours[offset],
                                       layer.contours[offset + 1]));
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    }
    const HRESULT hr = sink->Close();
    sink->Release();
    if (FAILED(hr))
    {
        path->Release();
        return nullptr;
    }
    g_vectorCardArt[slot] = path;
    return path;
}

static void DrawCardArtLayers(const CardArtLayer* layers, size_t count,
                              size_t firstSlot, const RectF& destination,
                              float sourceW, float sourceH, float alpha)
{
    if (!g_d2dFactory || !g_d2dTarget || !g_d2dBrush ||
        destination.W() <= 0.0f || destination.H() <= 0.0f)
        return;
    D2D1::Matrix3x2F saved;
    g_d2dTarget->GetTransform(&saved);
    g_d2dTarget->SetTransform(
        D2D1::Matrix3x2F::Scale(destination.W() / sourceW,
                               destination.H() / sourceH) *
        D2D1::Matrix3x2F::Translation(destination.l, destination.t) * saved);
    for (size_t i = 0; i < count; ++i)
    {
        if (auto* geometry = CardArtGeometry(layers[i], firstSlot + i))
        {
            g_d2dBrush->SetColor(ColorOf(layers[i].color, alpha));
            g_d2dTarget->FillGeometry(geometry, g_d2dBrush);
        }
    }
    g_d2dTarget->SetTransform(saved);
}

static void DrawSaikiCardArt(const RectF& card, float alpha, bool tucked,
                             bool desktopFace)
{
    const float w = card.W();
    const float h = card.H();
    const float unit = w / 160.0f;
    const UINT32 ink = 0xFF221815;
    const UINT32 red = 0xFFE60012;
    FillRound(card, 9.0f * unit, 0xFFFFFCF5, alpha);
    const RectF frame = {card.l + w * 0.035f, card.t + w * 0.035f,
                          card.r - w * 0.035f, card.b - w * 0.035f};
    StrokeRound(frame, 5.0f * unit, ink, 1.5f * unit, alpha);
    // Red comic-print corner bars, not the unrelated mint halo/glasses badge.
    FillRound({card.l + w * (desktopFace ? 0.35f : 0.09f), card.t + h * 0.08f,
               card.r - w * (desktopFace ? 0.25f : 0.09f), card.t + h * 0.10f},
               0.0f, red, alpha);
    FillRound({card.l + w * 0.09f, card.b - h * 0.10f,
               card.r - w * (desktopFace ? 0.35f : 0.09f), card.b - h * 0.08f},
               0.0f, red, alpha);
    // Large, faint print texture in the lower field leaves the title itself
    // clean. All spacings scale with the card, not the monitor's font size.
    const float dotStep = w * 0.055f;
    for (int row = 0; row < 6; ++row)
        for (int col = 0; col < 15; ++col)
            FillEllipse(card.l + w * 0.11f + col * dotStep,
                        card.t + h * 0.57f + row * dotStep,
                        unit * 0.65f, unit * 0.65f, ink, 0.11f * alpha);
    // Preserve the official horizontal logo's 552:195 proportions. In tucked
    // mode the entire logo is moved above the half-card screen clipping edge.
    const float logoW = w * 0.88f;
    const float logoH = logoW * 195.0f / 552.0f;
    const float logoY = card.t + h * (tucked ? (desktopFace ? 0.12f : 0.17f)
                                                           : desktopFace ? 0.28f : 0.33f);
    const RectF logo = {card.l + (w - logoW) * 0.5f, logoY,
                        card.r - (w - logoW) * 0.5f, logoY + logoH};
    DrawCardArtLayers(kSaikiLogoLayers, ARRAYSIZE(kSaikiLogoLayers), 0,
                      logo, 552.0f, 195.0f, alpha);
}

static void DrawYugiohCardBack(const RectF& card, float alpha)
{
    const float unit = card.W() / 160.0f;
    // The reference is the original full-card vortex: no medallion, eye,
    // accent tint or generic double-gold border. Rounded clipping follows the
    // card through carousel rotation, draw/throw animation and DPI changes.
    ID2D1RoundedRectangleGeometry* mask = nullptr;
    const auto rounded = D2D1::RoundedRect(
        D2D1::RectF(card.l, card.t, card.r, card.b),
        8.0f * unit, 8.0f * unit);
    if (FAILED(g_d2dFactory->CreateRoundedRectangleGeometry(rounded, &mask)))
    {
        FillRound(card, 8.0f * unit, 0xFFCE8747, alpha);
        return;
    }
    const auto parameters = D2D1::LayerParameters(
        D2D1::InfiniteRect(), mask, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
        D2D1::Matrix3x2F::Identity(), alpha);
    g_d2dTarget->PushLayer(parameters, nullptr);
    // Dark base + eight cumulative copper/amber contour layers.
    FillRound(card, 0.0f, 0xFF050102, 1.0f);
    DrawCardArtLayers(kYugiohVortexLayers, ARRAYSIZE(kYugiohVortexLayers), 3,
                      card, 428.0f, 614.0f, 1.0f);
    g_d2dTarget->PopLayer();
    mask->Release();
}

// END VECTOR CARD ART

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
    const float emphasis = DesktopHighlightStrength(selected, active);

    D2D1::Matrix3x2F savedTransform;
    bool movingForCreate = false;
    if (g_createAfterDraw && g_cardAnim.mode == CardAnimationMode::Draw)
    {
        const int movedDesktop =
            g_focusStrip ? g_desktopSelected : g_currentDesktop;
        movingForCreate = pill.desktop == movedDesktop;
        if (movingForCreate)
        {
            const float duration = std::max(0.05f, g_cardAnim.duration);
            const float elapsed = static_cast<float>(GetTickCount64() -
                                                      g_cardAnim.start) /
                                  1000.0f;
            const float progress = std::max(0.0f,
                                            std::min(1.0f, elapsed / duration));
            const float angle = -7.0f * EaseOutCubic(progress);
            // The new card is drawn into the insertion slot. Existing cards
            // make room on the opposite side, so use the corner facing that
            // movement as the hinge.
            const bool movesRight = g_cardAnim.to.l < g_cardAnim.from.l;
            const float pivotX = movesRight ? face.r : face.l;
            g_d2dTarget->GetTransform(&savedTransform);
            g_d2dTarget->SetTransform(
                D2D1::Matrix3x2F::Rotation(
                    angle, D2D1::Point2F(pivotX, face.b)) * savedTransform);
        }
    }

    UINT32 faceColor = 0xFFF8F5EC;
    UINT32 ink = 0xFF1C1B20;
    UINT32 red = 0xFFC62828;
    if (g_cardTheme == L"yugioh")
    {
        faceColor = 0xFF6B2817;
        ink = 0xFFFFE9C2;
        red = 0xFFFFE9C2;
    }
    else if (g_cardTheme == L"pokemon")
    {
        faceColor = 0xFFEAF2FF;
        ink = 0xFF244F9A;
        red = 0xFFD62828;
    }
    else if (g_cardTheme == L"kakegurui")
    {
        faceColor = 0xFF241B24;
        ink = 0xFFD4AF37;
        red = 0xFFC33A4A;
    }
    else if (g_cardTheme == L"saiki-k")
    {
        faceColor = 0xFFFFFCF5;
        ink = 0xFF221815;
        red = 0xFFE60012;
    }
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

    const bool kakegurui = g_cardTheme == L"kakegurui";
    // Kakegurui's print stays in its black, wine-red and gold family. Do not
    // wash it toward the app palette (often blue/cyan) on hover or selection.
    const UINT32 paper = hovered
        ? MixColor(faceColor, kakegurui ? 0xFF4A263E : 0xFFE4DCC8,
                   kakegurui ? 0.52f : 0.55f)
        : faceColor;
    const UINT32 cardAccent = kakegurui ? 0xFFC33A4A : g_theme.accent;
    FillRound(face, radius, MixColor(paper, cardAccent, 0.12f * emphasis),
               alpha);
    ID2D1Bitmap* customDesign = EnsureCardDesignBitmap();
    const bool builtInArt = !customDesign &&
        (g_cardTheme == L"saiki-k" || g_cardTheme == L"yugioh");
    if (builtInArt)
    {
        if (g_cardTheme == L"saiki-k")
            DrawSaikiCardArt(face, alpha, g_tuckCards, true);
        else
            DrawYugiohCardBack(face, alpha);
    }
    if (customDesign)
    {
        const RectF image = {face.l + 2.0f * s, face.t + 2.0f * s,
                             face.r - 2.0f * s, face.b - 2.0f * s};
        DrawBitmapCover(customDesign, image, alpha);
    }
    const bool hideSuits = builtInArt || (customDesign && g_hideCardSuitsWithDesign);
    // Playing cards keep their printed ink border; selection never repaints it
    // with the accent color. A selected card gets a slightly heavier edge.
    const bool marked = selected || active;
    StrokeRound(face, radius, ink,
                 (selected ? 2.2f : marked ? 1.5f : 1.0f) * s,
                 (builtInArt ? 0.0f : selected ? 0.68f : marked ? 0.46f : 0.30f) * alpha);
    const RectF inner = {face.l + 5.0f * s, face.t + 5.0f * s,
                         face.r - 5.0f * s, face.b - 5.0f * s};
    StrokeRound(inner, std::max(2.0f * s, radius - 4.0f * s), ink, 1.0f * s,
                 (builtInArt ? 0.0f : 0.12f) * alpha);
    if (emphasis > 0.0f)
    {
        const float mx = (face.l + face.r) / 2.0f;
        const float halfW = std::min(18.0f * s, face.W() * 0.18f);
        FillRound({mx - halfW, face.t + 6.0f * s,
                   mx + halfW, face.t + 10.0f * s},
                  2.0f * s, cardAccent, emphasis * alpha);
    }

    const float pad = 9.0f * s;
    const float idxW = 34.0f * s;
    const std::wstring rank = std::to_wstring(pill.desktop + 1);
    const RectF rankRect = {face.l + pad, face.t + 5.0f * s,
                             face.l + pad + idxW, face.t + 27.0f * s};
    if (builtInArt && g_cardTheme == L"yugioh")
        FillRound(rankRect, 3.0f * s, 0xFF090302, 0.85f * alpha);
    const RectF suitRect = {face.l + pad, face.t + 24.0f * s,
                            face.l + pad + idxW, face.t + 44.0f * s};
    IDWriteTextFormat* suitFmt = g_fmtCardSuit ? g_fmtCardSuit : g_fmtPillLarge;
    DrawTextBlock(rank, g_fmtPillLarge, rankRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    if (g_cardTheme == L"saiki-k" && builtInArt)
        // The full title is printed in the card centre. At corner-suit size,
        // the red Ψ is the recognizable, legible part of that official mark.
        DrawTextBlock(L"Ψ", suitFmt, suitRect, 0xFFE60012,
                      DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    else if (!hideSuits)
        DrawTextBlock(glyph, suitFmt, suitRect, suitColor,
                      DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    const RectF bRankRect = {face.r - pad - idxW, face.b - 27.0f * s,
                             face.r - pad, face.b - 5.0f * s};
    const RectF bSuitRect = {face.r - pad - idxW, face.b - 44.0f * s,
                             face.r - pad, face.b - 24.0f * s};
    if (builtInArt && g_cardTheme == L"yugioh")
        FillRound(bRankRect, 3.0f * s, 0xFF090302, 0.85f * alpha);
    DrawRotatedTextBlock(rank, g_fmtPillLarge, bRankRect, suitColor,
                         DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    if (g_cardTheme == L"saiki-k" && builtInArt)
        DrawRotatedTextBlock(L"Ψ", suitFmt, bSuitRect, 0xFFE60012,
                             DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    else if (!hideSuits)
        DrawRotatedTextBlock(glyph, suitFmt, bSuitRect, suitColor,
                             DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);

    const float h = face.H();
    const RectF bigSuit = {face.l + 18.0f * s, face.t + h * 0.27f,
                           face.r - 18.0f * s, face.t + h * 0.63f};
    if (!hideSuits)
        DrawTextBlock(glyph, g_fmtCardSuitBig ? g_fmtCardSuitBig : suitFmt,
                      bigSuit, suitColor, DWRITE_TEXT_ALIGNMENT_CENTER,
                      0.14f * alpha);

    const bool renaming = g_renameDesktop == pill.desktop;
    const std::wstring& name =
        renaming ? g_renameText : g_desktops[pill.desktop].name;
    RectF nameRect;
    if (g_cardTextPositionCustom)
    {
        const float textW = face.W() * 0.62f;
        const float textRight = face.r - static_cast<float>(g_cardTextX) * s;
        const float textTop = face.t + static_cast<float>(g_cardTextY) * s;
        nameRect = {textRight - textW, textTop, textRight,
                    textTop + 22.0f * s};
    }
    else
    {
        const bool tuckedLogo = builtInArt && g_cardTheme == L"saiki-k" && g_tuckCards;
        const float nameTop = tuckedLogo ? 0.37f : g_tuckCards ? 0.32f : 0.64f;
        const float nameBottom = tuckedLogo ? 0.49f : g_tuckCards ? 0.47f : 0.80f;
        nameRect = {face.l + 8.0f * s, face.t + h * nameTop,
                    face.r - 8.0f * s, face.t + h * nameBottom};
    }
    if (builtInArt)
        FillRound(nameRect, 4.0f * s,
                  g_cardTheme == L"yugioh" ? 0xFF090302 : 0xFFFFFCF5,
                  0.90f * alpha);
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

    if (movingForCreate)
        g_d2dTarget->SetTransform(savedTransform);
}

// A face-down playing card used as the create-desktop button. Clicking it or
// pulling it downward creates a new desktop.
static void DrawCreateCard(const RectF& rect, bool hovered, float pull)
{
    const float s = g_scale;
    const float lift = pull * 16.0f * s;
    const RectF card = {rect.l, rect.t + lift, rect.r, rect.b + lift};
    const float radius = 12.0f * s;
    UINT32 themeBack = g_theme.pillFill;
    UINT32 themeGold = 0xFFD8B45A;
    if (g_cardTheme == L"yugioh")
    {
        themeBack = 0xFF6B2817;
        themeGold = 0xFFD99A35;
    }
    else if (g_cardTheme == L"pokemon")
    {
        themeBack = 0xFF244F9A;
        themeGold = 0xFFF0B429;
    }
    else if (g_cardTheme == L"kakegurui")
    {
        themeBack = 0xFF171717;
        themeGold = 0xFFD4AF37;
    }
    else if (g_cardTheme == L"saiki-k")
    {
        themeBack = 0xFF1B5560;
        themeGold = 0xFFEF6F9F;
    }
    const bool kakegurui = g_cardTheme == L"kakegurui";
    const UINT32 gold = kakegurui ? themeGold : MixColor(themeGold, g_theme.accent, 0.18f);

    const RectF shadow = {card.l, card.t + 8.0f * s, card.r,
                          card.b + 14.0f * s};
    FillRound(shadow, radius + 2.0f * s, 0xFF000000, 0.34f + 0.18f * pull);

    const UINT32 back = kakegurui
        ? MixColor(themeBack, hovered ? 0xFF4A263E : 0xFF241B24,
                   hovered ? 0.58f : 0.30f)
        : MixColor(themeBack, g_theme.accent, hovered ? 0.30f : 0.20f);
    const UINT32 panel = MixColor(back, 0xFF000000, 0.18f);
    FillRound(card, radius, back, 1.0f);
    ID2D1Bitmap* customBack = EnsureCardBackBitmap();
    if (customBack)
    {
        const RectF image = {card.l + 2.0f * s, card.t + 2.0f * s,
                             card.r - 2.0f * s, card.b - 2.0f * s};
        DrawBitmapCover(customBack, image, 1.0f);
    }

    // Complete printed designs bypass the generic accent-tinted gold frame.
    // Custom image paths still take precedence over either built-in design.
    if (!customBack && (g_cardTheme == L"saiki-k" || g_cardTheme == L"yugioh"))
    {
        if (g_cardTheme == L"saiki-k")
            DrawSaikiCardArt(card, 1.0f, g_tuckCards, false);
        else
            DrawYugiohCardBack(card, 1.0f);
        if (hovered)
            StrokeRound(card, 8.0f * card.W() / 160.0f, 0xFFFFFFFF,
                        1.4f * s, 0.65f);
        return;
    }

    // Double border, like the frame printed on a real card back.
    StrokeRound(card, radius, gold, 2.2f * s, 0.90f);
    const RectF border = {card.l + 7.0f * s, card.t + 7.0f * s,
                          card.r - 7.0f * s, card.b - 7.0f * s};
    StrokeRound(border, std::max(3.0f * s, radius - 4.0f * s), gold,
                1.0f * s, 0.45f);

    if (customBack)
        return;

    // The named themes are complete, standalone vector backs. Do not layer
    // them over the default lattice, medallion or "New desktop" artwork.
    if (g_cardTheme != L"default")
    {
        const RectF inner = {card.l + 13.0f * s, card.t + 13.0f * s,
                             card.r - 13.0f * s, card.b - 13.0f * s};
        const float cx = (inner.l + inner.r) / 2.0f;
        const float cy = g_tuckCards ? inner.t + inner.H() * 0.34f
                                     : (inner.t + inner.b) / 2.0f;
        const float motifR = std::min(inner.W(), inner.H()) * 0.30f;
        FillRound(inner, std::max(3.0f * s, radius - 6.0f * s), panel, 1.0f);
        StrokeRound(inner, std::max(3.0f * s, radius - 6.0f * s), gold,
                    1.0f * s, 0.55f);

        g_d2dTarget->PushAxisAlignedClip(
            D2D1::RectF(inner.l, inner.t, inner.r, inner.b),
            D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
        if (g_cardTheme == L"pokemon")
        {
            // Royal-blue field with the high-contrast red/white capture-ball
            // geometry associated with the classic card-back layout.
            FillEllipse(cx, cy, motifR, motifR, 0xFFF8F5EC, 1.0f);
            g_d2dTarget->PushAxisAlignedClip(
                D2D1::RectF(cx - motifR, cy - motifR,
                            cx + motifR, cy),
                D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
            FillEllipse(cx, cy, motifR, motifR, 0xFFD62828, 1.0f);
            g_d2dTarget->PopAxisAlignedClip();
            g_d2dBrush->SetColor(ColorOf(0xFF142D63, 0.98f));
            g_d2dTarget->DrawLine(D2D1::Point2F(cx - motifR, cy),
                                  D2D1::Point2F(cx + motifR, cy), g_d2dBrush,
                                  2.0f * s);
            FillEllipse(cx, cy, motifR * 0.25f, motifR * 0.25f, 0xFFF8F5EC,
                        1.0f);
            StrokeEllipse(cx, cy, motifR * 0.25f, motifR * 0.25f, 0xFF171A3A,
                          1.6f * s, 0.95f);
            StrokeEllipse(cx, cy, motifR, motifR, 0xFFF0B429, 1.8f * s, 0.95f);
            StrokeEllipse(cx, cy, motifR * 1.18f, motifR * 1.18f,
                           0xFFB9D7FF, 1.0f * s, 0.65f);
        }
        else
        {
            // Black/crimson/gold roulette geometry with a faceted diamond.
            for (int i = 0; i < 12; i++)
            {
                const float angle = static_cast<float>(i) * 6.2831853f / 12.0f;
                const float x = cx + std::cos(angle) * motifR * 1.55f;
                const float y = cy + std::sin(angle) * motifR * 1.55f;
                g_d2dBrush->SetColor(ColorOf(0xFFD4AF37, 0.45f));
                g_d2dTarget->DrawLine(D2D1::Point2F(cx, cy),
                                      D2D1::Point2F(x, y), g_d2dBrush,
                                      1.0f * s);
            }
            const D2D1_POINT_2F points[] = {
                D2D1::Point2F(cx, cy - motifR),
                D2D1::Point2F(cx + motifR, cy),
                D2D1::Point2F(cx, cy + motifR),
                D2D1::Point2F(cx - motifR, cy)};
            FillEllipse(cx, cy, motifR * 0.82f, motifR * 0.82f, 0xFF8E1B2A,
                        0.95f);
            g_d2dBrush->SetColor(ColorOf(0xFFD4AF37, 0.95f));
            for (int i = 0; i < 4; i++)
                g_d2dTarget->DrawLine(points[i], points[(i + 1) % 4],
                                      g_d2dBrush, 1.8f * s);
            StrokeEllipse(cx, cy, motifR * 0.82f, motifR * 0.82f,
                          0xFFD4AF37, 1.2f * s, 0.9f);
        }
        g_d2dTarget->PopAxisAlignedClip();
        return;
    }

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

    if (!g_tuckCards)
    {
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
    }

    if (!g_tuckCards)
    {
        const RectF label = {card.l + 18.0f * s, card.b - 36.0f * s,
                             card.r - 18.0f * s, card.b - 12.0f * s};
        FillRound(label, 7.0f * s, MixColor(back, 0xFF000000, 0.22f), 0.90f);
        StrokeRound(label, 7.0f * s, gold, 0.8f * s, 0.40f);
        DrawTextBlock(L"New desktop", g_fmtHint, label, g_theme.text,
                      DWRITE_TEXT_ALIGNMENT_CENTER, 0.78f);
    }
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
    const float cardScale = g_cardScale * (g_tuckCards ? 1.18f : 1.0f);
    const float cardW = 160.0f * cardScale * s;
    const float cardH = 224.0f * cardScale * s;
    const float cx = (g_layout.strip.l + g_layout.strip.r) / 2.0f;
    const float cy = g_tuckCards ? g_layout.h
                                 : (g_layout.strip.t + g_layout.strip.b) / 2.0f;
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
    anim.cardTheme = g_cardTheme;
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
    if (!CreateDesktopWithoutSlide())
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
    anim.cardTheme = g_cardTheme;
    anim.from = from;
    // Toss the card in a broad arc: up and right first, then down past the
    // screen edge. It remains lighter than the old throw because the motion is
    // curved and the scale barely changes while the card spins.
    const float tossX = g_layout.w - from.l + 48.0f * g_scale;
    const float tossY = g_layout.h + 120.0f * g_scale - from.t;
    anim.to = {from.l + tossX, from.t - tossY,
               from.r + tossX, from.b - tossY};
    anim.fromScale = 1.0f;
    anim.toScale = 0.90f;
    anim.fromAngle = 0.0f;
    anim.toAngle = (desktop & 1) ? -264.0f : 264.0f;
    anim.start = GetTickCount64();
    anim.duration = AnimationSeconds(0.62f);
    g_cardAnim = anim;
    KickCardAnimation();
}

// A compact playing-card face used by the draw and throw ghosts. It mirrors the
// desktop-card language but takes its rank, suit and name from the animation,
// so it can outlive the desktop it represents.
static void DrawGhostCardFace(const RectF& face, int number, int suit,
                              const std::wstring& name,
                              const std::wstring& cardTheme, float alpha)
{
    if (face.W() <= 0.0f || face.H() <= 0.0f || alpha <= 0.01f)
        return;

    const float s = g_scale;
    const float radius = 12.0f * s;
    UINT32 faceColor = 0xFFF8F5EC;
    UINT32 ink = 0xFF1C1B20;
    UINT32 red = 0xFFC62828;
    if (cardTheme == L"yugioh")
    {
        faceColor = 0xFF6B2817;
        ink = red = 0xFFFFE9C2;
    }
    else if (cardTheme == L"pokemon")
    {
        faceColor = 0xFFEAF2FF;
        ink = 0xFF244F9A;
        red = 0xFFD62828;
    }
    else if (cardTheme == L"kakegurui")
    {
        faceColor = 0xFF241B24;
        ink = 0xFFD4AF37;
        red = 0xFFC33A4A;
    }
    else if (cardTheme == L"saiki-k")
    {
        faceColor = 0xFFFFFCF5;
        ink = 0xFF221815;
        red = 0xFFE60012;
    }
    const UINT32 suitColor = (suit == 1 || suit == 2) ? red : ink;
    const WCHAR* glyph = suit == 0 ? L"\u2660"
                        : suit == 1 ? L"\u2665"
                        : suit == 2 ? L"\u2666"
                                    : L"\u2663";

    const RectF shadow = {face.l, face.t + 8.0f * s, face.r,
                          face.b + 14.0f * s};
    FillRound(shadow, radius + 2.0f * s, 0xFF000000, 0.28f * alpha);
    ID2D1Bitmap* customDesign = EnsureCardDesignBitmap();
    const bool builtInArt = !customDesign &&
        (cardTheme == L"saiki-k" || cardTheme == L"yugioh");
    if (builtInArt)
    {
        if (cardTheme == L"saiki-k")
            DrawSaikiCardArt(face, alpha, g_tuckCards, true);
        else
            DrawYugiohCardBack(face, alpha);
    }
    else
    {
        FillRound(face, radius, faceColor, alpha);
        if (customDesign)
        {
            const RectF image = {face.l + 2.0f * s, face.t + 2.0f * s,
                                 face.r - 2.0f * s, face.b - 2.0f * s};
            DrawBitmapCover(customDesign, image, alpha);
        }
    }
    StrokeRound(face, radius, ink, 1.0f * s,
                (builtInArt ? 0.0f : 0.55f) * alpha);
    const RectF inner = {face.l + 5.0f * s, face.t + 5.0f * s,
                         face.r - 5.0f * s, face.b - 5.0f * s};
    StrokeRound(inner, std::max(2.0f * s, radius - 4.0f * s), ink,
                1.0f * s, (builtInArt ? 0.0f : 0.14f) * alpha);

    const float pad = 9.0f * s;
    const float idxW = 34.0f * s;
    const std::wstring rank = std::to_wstring(number);
    IDWriteTextFormat* suitFmt = g_fmtCardSuit ? g_fmtCardSuit : g_fmtPillLarge;
    const RectF rankRect = {face.l + pad, face.t + 5.0f * s,
                            face.l + pad + idxW, face.t + 27.0f * s};
    const RectF suitRect = {face.l + pad, face.t + 24.0f * s,
                            face.l + pad + idxW, face.t + 44.0f * s};
    if (builtInArt && cardTheme == L"yugioh")
        FillRound(rankRect, 3.0f * s, 0xFF090302, 0.85f * alpha);
    DrawTextBlock(rank, g_fmtPillLarge, rankRect, suitColor,
                  DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    if (builtInArt && cardTheme == L"saiki-k")
        DrawTextBlock(L"Ψ", suitFmt, suitRect, 0xFFE60012,
                      DWRITE_TEXT_ALIGNMENT_CENTER, alpha);
    else if (!builtInArt)
        DrawTextBlock(glyph, suitFmt, suitRect, suitColor,
                      DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    const RectF bRankRect = {face.r - pad - idxW, face.b - 27.0f * s,
                             face.r - pad, face.b - 5.0f * s};
    const RectF bSuitRect = {face.r - pad - idxW, face.b - 44.0f * s,
                             face.r - pad, face.b - 24.0f * s};
    if (builtInArt && cardTheme == L"yugioh")
        FillRound(bRankRect, 3.0f * s, 0xFF090302, 0.85f * alpha);
    DrawRotatedTextBlock(rank, g_fmtPillLarge, bRankRect, suitColor,
                          DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    if (builtInArt && cardTheme == L"saiki-k")
        DrawRotatedTextBlock(L"Ψ", suitFmt, bSuitRect, 0xFFE60012,
                             DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);
    else if (!builtInArt)
        DrawRotatedTextBlock(glyph, suitFmt, bSuitRect, suitColor,
                             DWRITE_TEXT_ALIGNMENT_CENTER, alpha, 180.0f);

    const float h = face.H();
    const RectF bigSuit = {face.l + 18.0f * s, face.t + h * 0.27f,
                           face.r - 18.0f * s, face.t + h * 0.63f};
    if (!builtInArt)
        DrawTextBlock(glyph, g_fmtCardSuitBig ? g_fmtCardSuitBig : suitFmt,
                      bigSuit, suitColor, DWRITE_TEXT_ALIGNMENT_CENTER,
                      0.14f * alpha);

    if (!name.empty())
    {
        const float nameTop = g_tuckCards ? 0.32f : 0.64f;
        const float nameBottom = g_tuckCards ? 0.47f : 0.80f;
        const RectF nameRect = {face.l + 8.0f * s, face.t + h * nameTop,
                                face.r - 8.0f * s, face.t + h * nameBottom};
        if (builtInArt)
            FillRound(nameRect, 4.0f * s,
                      cardTheme == L"yugioh" ? 0xFF090302 : 0xFFFFFCF5,
                      0.90f * alpha);
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
        // Follow a high arc before falling below the screen. The rise is based
        // on the total vertical travel, so it stays natural at every DPI.
        const float rise = std::max(
            120.0f * g_scale,
            (g_layout.h + 120.0f * g_scale - g_cardAnim.from.t) * 0.85f);
        const float lift = arc * rise;
        const float drift = std::sin(t * 6.2831853f) * 5.0f * g_scale;
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
        const float fade = std::max(0.0f, std::min(1.0f, (t - 0.68f) / 0.32f));
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
                      g_cardAnim.cardTheme, alpha);
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
    const float emphasis = DesktopHighlightStrength(selected, active);

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
    FillEllipse(cx, cy, discR, discR,
                MixColor(paint.inlay, g_theme.accent, 0.15f * emphasis), alpha);
    StrokeEllipse(cx, cy, discR * 0.86f, discR * 0.86f,
                  MixColor(paint.inlay, chipColor, 0.42f), 0.8f * s,
                  0.55f * alpha);
    DrawChipSuitRing(cx, cy, r * 0.72f, 0.0f, paint.spot, 0.62f * alpha);

    const RectF disc = {cx - discR, cy - discR, cx + discR, cy + discR};
    DrawTextBlock(std::to_wstring(pill.desktop + 1), g_fmtPillLarge, disc,
                  ChipDiscInk(chipColor), DWRITE_TEXT_ALIGNMENT_CENTER, alpha);

    if (emphasis > 0.0f)
    {
        StrokeEllipse(cx, cy, r, r, g_theme.accent,
                      (selected ? 3.0f : 1.8f) * s, emphasis * alpha);
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
        selected ? MixColor(g_theme.cardSelected, g_theme.accent, 0.10f)
                 : (hovered ? g_theme.cardHover : g_theme.cardFill);
    FillRound(rect, radius, fill, 1.0f);
    // Keep card selection in the fill and a neutral edge; cards do not use the
    // accent outline that pills and chips use.
    StrokeRound(rect, radius, g_theme.text, (selected ? 1.8f : 1.4f) * s,
                selected ? 0.52f : (hovered ? 0.16f : 0.08f));

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
                  selected ? g_theme.accent : paint.inlay,
                  (selected ? 1.6f : 0.8f) * s, selected ? 0.85f : 0.32f);

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
                      2.8f * s, 0.98f);
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

static bool BuildDraggedCardView(float sceneScale, float cx, float cy,
                                 CardView* result)
{
    if (!result || !g_windowDragging || g_windowDragEntry < 0)
        return false;

    CardView source;
    bool found = false;
    for (const CardView& card : g_cards)
        if (card.entry == g_windowDragEntry)
        {
            source = card;
            found = true;
            break;
        }
    if (!found)
        for (const CardView& card : g_dockCards)
            if (card.entry == g_windowDragEntry)
            {
                source = card;
                found = true;
                break;
            }
    if (!found)
        return false;

    CardView ghost = source;
    ghost.rect = ScaleAbout(source.rect, sceneScale, cx, cy);
    ghost.header = ScaleAbout(source.header, sceneScale, cx, cy);
    ghost.preview = ScaleAbout(source.preview, sceneScale, cx, cy);
    ghost.close = ScaleAbout(source.close, sceneScale, cx, cy);
    ghost.lift = source.lift * sceneScale;

    const float sourceCx = (ghost.rect.l + ghost.rect.r) / 2.0f;
    const float sourceCy = (ghost.rect.t + ghost.rect.b) / 2.0f;
    const float dx = static_cast<float>(g_windowDragCursor.x) - sourceCx;
    const float dy = static_cast<float>(g_windowDragCursor.y) - sourceCy;
    for (RectF* rect : {&ghost.rect, &ghost.header, &ghost.preview,
                        &ghost.close})
    {
        rect->l += dx;
        rect->r += dx;
        rect->t += dy;
        rect->b += dy;
    }

    const float elapsed = static_cast<float>(
        GetTickCount64() - g_windowDragStarted) / 1000.0f;
    const float dragLift =
        (1.0f - EaseOutCubic(std::min(1.0f, elapsed / 0.14f))) *
        14.0f * g_scale;
    for (RectF* rect : {&ghost.rect, &ghost.header, &ghost.preview,
                        &ghost.close})
    {
        rect->t -= dragLift;
        rect->b -= dragLift;
    }
    ghost.lift += dragLift;

    // The live thumbnail host is above the overlay. Keep the dragged card above
    // the desktop strip while a tab is being targeted so the strip remains
    // visible and the drop destination is never covered by the preview.
    if (ghost.rect.b > g_layout.strip.t - 8.0f * g_scale)
    {
        const float dy = g_layout.strip.t - 8.0f * g_scale - ghost.rect.b;
        for (RectF* rect : {&ghost.rect, &ghost.header, &ghost.preview,
                            &ghost.close})
        {
            rect->t += dy;
            rect->b += dy;
        }
    }
    *result = ghost;
    return true;
}

static bool BuildWindowDropCardView(float sceneScale, float cx, float cy,
                                    CardView* result, float* progress)
{
    if (!result || !g_windowDropAnimating || g_windowDropTargetDesktop < 0)
        return false;

    int targetIndex = -1;
    for (int i = 0; i < static_cast<int>(g_pills.size()); i++)
        if (g_pills[i].desktop == g_windowDropTargetDesktop)
        {
            targetIndex = i;
            break;
        }
    if (targetIndex < 0)
        return false;

    CardView ghost = g_windowDropCard;
    ghost.rect = ScaleAbout(ghost.rect, sceneScale, cx, cy);
    ghost.header = ScaleAbout(ghost.header, sceneScale, cx, cy);
    ghost.preview = ScaleAbout(ghost.preview, sceneScale, cx, cy);
    ghost.close = ScaleAbout(ghost.close, sceneScale, cx, cy);
    ghost.lift *= sceneScale;

    const float raw = static_cast<float>(GetTickCount64() - g_windowDropStarted) /
                      1000.0f;
    const float p = std::max(0.0f, std::min(1.0f, raw / g_windowDropDuration));
    if (progress)
        *progress = p;
    const float eased = p * p;
    const float sourceCx = (ghost.rect.l + ghost.rect.r) / 2.0f;
    const float sourceCy = (ghost.rect.t + ghost.rect.b) / 2.0f;
    const PillView& target = g_pills[targetIndex];
    const float targetCx = (target.rect.l + target.rect.r) / 2.0f;
    const float targetCy = (target.rect.t + target.rect.b) / 2.0f - target.lift;
    const float scale = 1.0f - 0.78f * eased;
    const float centreX = sourceCx + (targetCx - sourceCx) * eased;
    const float centreY = sourceCy + (targetCy - sourceCy) * eased;
    for (RectF* rect : {&ghost.rect, &ghost.header, &ghost.preview,
                        &ghost.close})
    {
        rect->l = centreX + (rect->l - sourceCx) * scale;
        rect->r = centreX + (rect->r - sourceCx) * scale;
        rect->t = centreY + (rect->t - sourceCy) * scale;
        rect->b = centreY + (rect->b - sourceCy) * scale;
    }
    *result = ghost;
    return true;
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
    const bool maskLivePreviews = true;

    for (int i = 0; i < static_cast<int>(g_cards.size()); i++)
    {
        if ((g_windowDragging && g_cards[i].entry == g_windowDragEntry) ||
            (g_windowDropAnimating &&
             g_cards[i].entry == g_windowDropCard.entry))
            continue;
        const CardView view = scaledCard(g_cards[i]);
        const bool isHovered = g_hoverCard == i;
        const bool isSelected = isHovered ||
                                (!g_focusStrip && !g_focusDock &&
                                 !g_pointerWindowSelection &&
                                 g_cards[i].filtered == g_selected);
        DrawWindowChip(view, isSelected, isHovered, g_hoverClose == i,
                       maskLivePreviews);
    }
    for (int i = 0; i < static_cast<int>(g_dockCards.size()); i++)
    {
        if ((g_windowDragging && g_dockCards[i].entry == g_windowDragEntry) ||
            (g_windowDropAnimating &&
             g_dockCards[i].entry == g_windowDropCard.entry))
            continue;
        const CardView view = scaledCard(g_dockCards[i]);
        const bool isHovered = g_hoverDock == i;
        const bool isSelected = isHovered || (g_focusDock && i == g_dockSelected);
        DrawWindowChip(view, isSelected, isHovered,
                       g_hoverDockClose == i, maskLivePreviews);
    }
    CardView dragged;
    if (BuildDraggedCardView(sceneScale, cx, cy, &dragged))
        DrawWindowChip(dragged, true, true, false, true);
    CardView dropping;
    float dropProgress = 0.0f;
    if (BuildWindowDropCardView(sceneScale, cx, cy, &dropping, &dropProgress) &&
        dropProgress < 0.45f)
        DrawWindowChip(dropping, true, false, false, true);

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

static void RenderDragBorderOverlay(float sceneScale, float cx, float cy)
{
    // Window thumbnails are composed above the normal overlay. Reuse the
    // transparent topmost mask window for square-card borders so another live
    // thumbnail cannot paint over the dragged card's outline.
    if (UsesWindowChips())
        return;
    if (!g_windowDragging && !g_windowDropAnimating)
    {
        if (g_chipMask)
            ShowWindow(g_chipMask, SW_HIDE);
        return;
    }
    if (!g_chipMask || !EnsureChipMaskSurface() || !EnsureFactories() ||
        !EnsureDeviceResources())
        return;

    RECT rc = {0, 0, g_maskW, g_maskH};
    if (FAILED(g_d2dTarget->BindDC(g_maskDC, &rc)))
        return;
    g_d2dTarget->BeginDraw();
    g_d2dTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    g_d2dTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
    g_d2dTarget->PushAxisAlignedClip(
        D2D1::RectF(0.0f, 0.0f, static_cast<float>(g_maskW),
                    static_cast<float>(g_maskH)),
        D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

    CardView card;
    float dropProgress = 0.0f;
    const bool hasCard = BuildDraggedCardView(sceneScale, cx, cy, &card) ||
        (BuildWindowDropCardView(sceneScale, cx, cy, &card, &dropProgress) &&
         dropProgress < 0.28f);
    if (hasCard)
    {
        StrokeRound(card.rect, 10.0f * g_scale, g_theme.accent,
                    3.0f * g_scale, 0.98f);
        StrokeRound(card.preview, 6.0f * g_scale, g_theme.accent,
                    1.6f * g_scale, 0.78f);
    }

    g_d2dTarget->PopAxisAlignedClip();
    g_d2dTarget->EndDraw();

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;
    POINT source = {0, 0};
    SIZE size = {g_maskW, g_maskH};
    POINT destination = {g_monitorX, g_monitorY};
    UpdateLayeredWindow(g_chipMask, nullptr, &destination, &size, g_maskDC,
                        &source, 0, &blend, ULW_ALPHA);
    SetWindowPos(g_chipMask, HWND_TOPMOST, g_monitorX, g_monitorY, g_monitorW,
                 g_monitorH, SWP_NOACTIVATE | SWP_SHOWWINDOW);
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
    CardView draggedCard;
    const bool hasDraggedCard = BuildDraggedCardView(sceneScale, cx, cy,
                                                     &draggedCard);
    CardView droppingCard;
    float dropProgress = 0.0f;
    const bool hasDroppingCard = BuildWindowDropCardView(
        sceneScale, cx, cy, &droppingCard, &dropProgress);

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
                if ((g_windowDragging && card.entry == g_windowDragEntry) ||
                    (g_windowDropAnimating &&
                     card.entry == g_windowDropCard.entry))
                    continue;
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
        if (UsesWindowChips() && hasDraggedCard &&
            g_windowDragEntry < static_cast<int>(g_windows.size()) &&
            g_windows[g_windowDragEntry].onCurrentDesktop &&
            g_windows[g_windowDragEntry].hwnd &&
            IsWindow(g_windows[g_windowDragEntry].hwnd))
        {
            std::vector<HWND>& sources = UsesWindowChips() ? chipSources : overlaySources;
            std::vector<RectF>& rects = UsesWindowChips() ? chipRects : overlayRects;
            sources.push_back(g_windows[g_windowDragEntry].hwnd);
            rects.push_back(draggedCard.preview);
        }
        if (UsesWindowChips() && hasDroppingCard && dropProgress < 0.28f &&
            g_windowDropWindow &&
            IsWindow(g_windowDropWindow))
        {
            std::vector<HWND>& sources = UsesWindowChips() ? chipSources : overlaySources;
            std::vector<RectF>& rects = UsesWindowChips() ? chipRects : overlayRects;
            sources.push_back(g_windowDropWindow);
            rects.push_back(droppingCard.preview);
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
        if ((g_windowDragging && g_cards[i].entry == g_windowDragEntry) ||
            (g_windowDropAnimating &&
             g_cards[i].entry == g_windowDropCard.entry))
            continue;
        const CardView view = scaledCard(g_cards[i]);
        const bool isHovered = g_hoverCard == i;
        const bool isSelected = isHovered ||
                                (!g_focusStrip && !g_focusDock &&
                                 !g_pointerWindowSelection &&
                                 g_cards[i].filtered == g_selected);
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
            if ((g_windowDragging && g_dockCards[i].entry == g_windowDragEntry) ||
                (g_windowDropAnimating &&
                 g_dockCards[i].entry == g_windowDropCard.entry))
                continue;
            const CardView view = scaledCard(g_dockCards[i]);
            const bool isHovered = g_hoverDock == i;
            const bool isSelected = isHovered || (g_focusDock && i == g_dockSelected);
            const bool closeHovered = g_hoverDockClose == i;
            if (UsesWindowChips())
                DrawWindowChip(view, isSelected, isHovered, closeHovered);
            else
                DrawWindowCard(view, isSelected, isHovered, closeHovered);
        }
    }

    // Lift the dragged card out of the grid and let it follow the pointer. The
    // original thumbnail is omitted above, so this ghost remains readable over
    // the live preview instead of leaving a second card behind.
    if (hasDraggedCard)
    {
        if (UsesWindowChips())
            DrawWindowChip(draggedCard, true, true, false);
        else
            DrawWindowCard(draggedCard, true, true, false);
    }
    if (hasDroppingCard)
    {
        if (UsesWindowChips())
            DrawWindowChip(droppingCard, true, false, false);
        else
            DrawWindowCard(droppingCard, true, false, false);
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
        const bool dropTarget = g_windowDragging &&
                                pill.desktop == g_windowDragTargetDesktop;
        const bool selected = (g_focusStrip && pill.desktop == g_desktopSelected) ||
                              dropTarget;

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
        const float emphasis = DesktopHighlightStrength(selected, active);
        UINT32 fill = active ? g_theme.pillActive : g_theme.pillFill;
        if (hovered)
            fill = active ? g_theme.pillActiveHover : g_theme.pillHover;
        if (emphasis > 0.0f)
            fill = MixColor(fill, g_theme.accent, 0.18f * emphasis);

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

        if (emphasis > 0.0f)
            StrokeRound(face, 10.0f * s, g_theme.accent,
                        (selected ? 2.4f : 1.6f) * s,
                        emphasis * pill.alpha);
        else
            StrokeRound(face, 10.0f * s, g_theme.text, 1.2f * s,
                        (active ? 0.32f : 0.08f) * pill.alpha);

        const RectF badge = {face.l + 10.0f * s, face.t + 9.0f * s,
                             face.l + 34.0f * s, face.b - 9.0f * s};
        // Keyboard selection can move to an inactive desktop before Enter
        // switches to it. Keep that pill highlighted without turning its
        // number into an active, white-on-accent badge.
        const bool badgeAccent = active;
        FillRound(badge, 6.0f * s,
                  badgeAccent ? g_theme.accent : g_theme.text,
                  (badgeAccent ? 0.85f : selected ? 0.20f : 0.12f) * pill.alpha);
        DrawTextBlock(std::to_wstring(pill.desktop + 1), PillFormat(), badge,
                      badgeAccent ? g_theme.onAccent : g_theme.text,
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
                       ((active || selected || renaming) ? 0.95f : 0.72f) * pill.alpha);

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

    // Tucked cards reach the bottom edge, so keep hints above the visible cards.
    const float hintTop = UsesCards() && g_tuckCards
                              ? g_layout.strip.t - 29.0f * s
                              : g_layout.strip.b + 10.0f * s;
    const RectF hintRect = {56.0f * s, hintTop,
                            g_layout.w - 56.0f * s, hintTop + 24.0f * s};
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
    const bool showSquareDragLayer = !UsesWindowChips() && contentAlpha > 0.98f &&
        (hasDraggedCard || (hasDroppingCard && dropProgress < 0.28f));
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
    else if (showSquareDragLayer)
    {
        const HWND source = hasDraggedCard
            ? (g_windowDragEntry >= 0 &&
               g_windowDragEntry < static_cast<int>(g_windows.size())
                   ? g_windows[g_windowDragEntry].hwnd : nullptr)
            : g_windowDropWindow;
        const RectF& preview = hasDraggedCard ? draggedCard.preview
                                               : droppingCard.preview;
        if (source && IsWindow(source))
        {
            const std::vector<HWND> sources = {source};
            const std::vector<RectF> rects = {preview};
            SetChipLayersVisible(true);
            SyncChipThumbnails(sources, rects, contentAlpha);
            UpdateChipHostRegion(rects);
            // The dedicated host is above the regular overlay thumbnails; the
            // mask is raised again below with the drag border over its preview.
            SetWindowPos(g_thumbHost, g_chipMask, g_monitorX, g_monitorY,
                         g_monitorW, g_monitorH,
                         SWP_NOACTIVATE | SWP_SHOWWINDOW);
        }
        else
        {
            SetChipLayersVisible(false);
        }
    }
    else
    {
        SetChipLayersVisible(false);
    }
    RenderDragBorderOverlay(sceneScale, cx, cy);
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
    g_desktopActionStartIndex = -1;
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

// The overlay can briefly lose the foreground while the shell switches
// desktops. Focus-loss closing is intentionally suppressed during that window,
// so once the action settles take the keyboard back. Without this the overlay
// can stay on screen while key presses (including Escape) go to another
// window.
static void ReclaimOverlayForeground()
{
    if (!g_overlay || !g_visible || !g_closeOnFocusLoss || g_busy ||
        g_closingForActivation || g_targetPresence <= 0.0f)
        return;
    if (GetForegroundWindow() != g_overlay)
        ForceForeground(g_overlay);
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
    g_hasOriginDesktopId = ReadActiveDesktopId(&g_originDesktopId);

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
    g_pointerWindowSelection = false;
    g_ignorePointerUntilMoved = false;
    g_hasLastPointerPosition = false;
    g_desktopEnterHide = false;
    // Reopening while Enter is still down must not replay the press on the new
    // overview; the release timer clears the latch.
    if (!(GetAsyncKeyState(VK_RETURN) & 0x8000))
        g_returnKeyLatch = false;
    g_createDragging = false;
    g_createPull = 0.0f;
    ClearWindowDrag();
    ClearWindowDropAnimation();
    g_busy = false;
    g_busySince = 0;
    g_desktopActionCreate = false;
    g_desktopActionClose = false;
    g_desktopActionStartCount = 0;
    g_desktopActionStartIndex = -1;
    g_pendingDesktopTarget = -1;
    g_pendingDesktopTries = 0;
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;
    g_keepThumbnailsWhileBusy = false;
    g_pendingMove = false;

    RefreshDesktops();
    RebuildWindowList();
    g_desktopSelected = g_currentDesktop;
    ResetCarouselPosition(g_currentDesktop, static_cast<int>(g_desktops.size()));
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

    // Keep Escape and Enter working even while another window owns the
    // keyboard (which happens briefly during desktop switches).
    RegisterHotKey(g_overlay, kHotkeyEscape, 0, VK_ESCAPE);
    RegisterHotKey(g_overlay, kHotkeyReturn, 0, VK_RETURN);

    // If the hotkey survived a hide because Enter was still held, keep polling
    // for its release so it is not unregistered too early.
    if (g_returnKeyLatch)
        SetTimer(g_overlay, kTimerReturnRelease, 15, nullptr);

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
    {
        UnregisterHotKey(g_overlay, kHotkeyEscape);
        // Keep Enter registered while the physical key is still down. This is
        // what stops a held or repeated Enter from reaching the window that is
        // about to regain focus and opening it. The release timer removes it.
        if (!g_returnKeyLatch)
            UnregisterHotKey(g_overlay, kHotkeyReturn);
        ShowWindow(g_overlay, SW_HIDE);
    }
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

// Hiding normally returns focus to the window that was active when the
// overview opened. That must not pull the user back to another virtual desktop:
// foregrounding a window that lives elsewhere (or was deliberately left behind
// by an Enter-on-desktop action) looks like the window opened and its desktop
// moved. Let the shell pick a window on the active desktop instead.
static void RestoreOriginWindow()
{
    if (g_closingForActivation || g_desktopEnterHide)
        return;
    if (!g_originWindow || !IsWindow(g_originWindow))
        return;
    if (!IsWindowOnCurrentDesktop(g_originWindow))
        return;
    // The overview may have been used to visit another desktop (including a
    // held task that followed). Returning focus to the opening window would
    // then yank the user back or open a window they deliberately left behind.
    GUID current = {};
    if (g_hasOriginDesktopId && ReadActiveDesktopId(&current) &&
        !IsEqualGUID(current, g_originDesktopId))
        return;
    SetForegroundWindow(g_originWindow);
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
    if (g_windowDragEntry >= 0)
    {
        ClearWindowDrag();
        if (GetCapture() == g_overlay)
            ReleaseCapture();
    }
    ClearWindowDropAnimation();

    if (immediate)
    {
        g_presence = 0.0f;
        g_targetPresence = 0.0f;
        FinishHide();
        RestoreOriginWindow();
        g_desktopEnterHide = false;
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
    // Desktop-tab interactions are desktop-only. This is the final guard: a
    // duplicate, queued or delayed activation must never open a window while
    // the strip owns the keyboard.
    if (g_focusStrip)
        return;
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

// Keyboard navigation owns the highlight until the pointer physically moves.
// The current cursor position is captured so the WM_MOUSEMOVE messages Windows
// synthesizes after a key press (identical coordinates) cannot steal it back.
static void TakeKeyboardPointerOwnership()
{
    g_pointerWindowSelection = false;
    g_ignorePointerUntilMoved = true;
    g_hoverCard = g_hoverClose = g_hoverPill = g_hoverPillClose = -1;
    g_hoverDock = g_hoverDockClose = -1;
    g_hoverCreate = g_hoverSearch = g_hoverSearchClear = false;

    POINT pt = {};
    if (g_overlay && GetCursorPos(&pt))
    {
        ScreenToClient(g_overlay, &pt);
        g_lastPointerPosition = pt;
        g_hasLastPointerPosition = true;
    }
}

static void MoveSelection(int dx, int dy)
{
    // The pointer updated g_selected to its last hovered card but deliberately
    // suppressed the keyboard highlight. The first arrow/h/j/k/l now advances
    // from that card and restores normal keyboard focus.
    TakeKeyboardPointerOwnership();
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

// Leaves the search field and returns to the current desktop's windows. Esc
// uses this first; a second Esc then closes the overview.
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
    // Keyboard navigation keeps control while the pointer is stationary. Only
    // a different coordinate hands focus back to the mouse.
    if (g_ignorePointerUntilMoved && g_hasLastPointerPosition &&
        x == g_lastPointerPosition.x && y == g_lastPointerPosition.y)
        return;
    if (g_ignorePointerUntilMoved)
        g_ignorePointerUntilMoved = false;
    g_lastPointerPosition = {x, y};
    g_hasLastPointerPosition = true;
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
            // Hovering a window clears the visual keyboard selection while
            // preserving this card as the next keyboard-navigation origin.
            // That prevents arrow/vim moves from jumping back to an old card.
            g_selected = card.filtered;
            g_pointerWindowSelection = true;
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

static void ClearWindowDrag()
{
    g_windowDragEntry = -1;
    g_windowDragStarted = 0;
    g_windowDragging = false;
    g_windowDragTargetDesktop = -1;
}

static void ClearWindowDropAnimation()
{
    g_windowDropAnimating = false;
    g_windowDropWindow = nullptr;
    g_windowDropTargetDesktop = -1;
    g_windowDropCard = CardView();
    g_windowDropStarted = 0;
}

static bool BeginWindowDropAnimation(int entry, int targetDesktop)
{
    if (entry < 0 || entry >= static_cast<int>(g_windows.size()) ||
        targetDesktop < 0 || targetDesktop >= static_cast<int>(g_desktops.size()))
        return false;

    CardView source;
    bool found = false;
    for (const CardView& card : g_cards)
        if (card.entry == entry)
        {
            source = card;
            found = true;
            break;
        }
    if (!found)
        for (const CardView& card : g_dockCards)
            if (card.entry == entry)
            {
                source = card;
                found = true;
                break;
            }
    if (!found || !g_windows[entry].hwnd || !IsWindow(g_windows[entry].hwnd))
        return false;

    g_windowDropCard = source;
    g_windowDropWindow = g_windows[entry].hwnd;
    g_windowDropTargetDesktop = targetDesktop;
    g_windowDropStarted = GetTickCount64();
    g_windowDropAnimating = true;
    g_lastFrameTick = g_windowDropStarted;
    SetTimer(g_overlay, kTimerFrame, 16, nullptr);
    InvalidateRect(g_overlay, nullptr, FALSE);
    return true;
}

static int WindowEntryAt(int x, int y)
{
    const float fx = static_cast<float>(x);
    const float fy = static_cast<float>(y);
    for (const CardView& card : g_cards)
    {
        if ((Contains(card.hit, fx, fy) || Contains(card.rect, fx, fy)) &&
            card.entry >= 0 && card.entry < static_cast<int>(g_windows.size()))
            return card.entry;
    }
    for (const CardView& card : g_dockCards)
    {
        if ((Contains(card.hit, fx, fy) || Contains(card.rect, fx, fy)) &&
            card.entry >= 0 && card.entry < static_cast<int>(g_windows.size()))
            return card.entry;
    }
    return -1;
}

static void UpdateWindowDragTarget(int x, int y)
{
    g_windowDragTargetDesktop = -1;
    const int pillIndex = PillAt(static_cast<float>(x), static_cast<float>(y));
    if (pillIndex >= 0 && pillIndex < static_cast<int>(g_pills.size()))
        g_windowDragTargetDesktop = g_pills[pillIndex].desktop;
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
    // A click on a window, dock item or empty space hands keyboard focus back to
    // the grid. Without this a previous desktop-tab focus would make Enter
    // switch desktops even though the user just clicked a window card.
    g_focusStrip = false;

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
    TakeKeyboardPointerOwnership();
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
    TakeKeyboardPointerOwnership();
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

// Enter on a desktop tab is a desktop-only action. It must never fall through
// to ActivateEntry(), which would open the selected window (and can switch back
// to that window's desktop instead of the chosen one).
static void ActivateDesktopSelection(int desktop)
{
    if (desktop < 0 || desktop >= static_cast<int>(g_desktops.size()))
        return;

    // A queued window activation or move must not survive a desktop Enter.
    g_pendingMove = false;
    g_pendingActivateWindow = nullptr;
    g_pendingActivateDesktop = -1;

    g_focusDock = false;
    g_focusStrip = true;
    g_desktopSelected = desktop;
    if (desktop != g_currentDesktop)
    {
        BeginDesktopAction(desktop, false, false);
    }
    else
    {
        // Enter on the desktop that is already active closes the overview, as
        // before; it still never activates the window selection. Suppress the
        // usual origin-window restore as well: the user chose a desktop, and
        // that window may belong to a desktop they just left.
        g_desktopEnterHide = true;
        HideOverlay(false);
    }
}

static void OnKeyDown(WPARAM key)
{
    // A held Enter auto-repeats, and the latch survives the hide so the repeat
    // cannot land on the window that regains focus. One press = one action.
    if (key == VK_RETURN)
    {
        if (g_returnKeyLatch)
            return;
        g_returnKeyLatch = true;
        if (g_overlay)
            SetTimer(g_overlay, kTimerReturnRelease, 15, nullptr);
    }

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
        {
            CancelRenameDesktop();
        }
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
            // Leave the search first; Esc from the normal view closes.
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
            ActivateDesktopSelection(g_desktopSelected);
        }
        else if (g_focusDock)
        {
            // The dock owns the keyboard; a pill under the pointer must not
            // steal Enter from the selected dock item.
            ActivateDockSelection();
        }
        else
        {
            // A desktop tab under the pointer is the obvious Enter target even
            // when the window grid still owns keyboard focus. Resolve it from
            // the live cursor position: opening the overview with the pointer
            // already parked on a tab produces no WM_MOUSEMOVE, so the cached
            // hover index can still be -1 (or stale after a desktop switch).
            // Arrow/vim navigation owns the selection until the pointer moves,
            // so it deliberately skips this lookup.
            int pill = -1;
            if (!g_ignorePointerUntilMoved && g_overlay)
            {
                POINT pt = {};
                if (GetCursorPos(&pt) && ScreenToClient(g_overlay, &pt))
                    pill = PillAt(static_cast<float>(pt.x), static_cast<float>(pt.y));
            }
            if (pill >= 0 && pill < static_cast<int>(g_pills.size()))
                ActivateDesktopSelection(g_pills[pill].desktop);
            else
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
        g_windowDragEntry = WindowEntryAt(x, y);
        g_windowDragStart = {x, y};
        g_windowDragging = false;
        g_windowDragTargetDesktop = -1;
        if (g_windowDragEntry >= 0)
            SetCapture(hwnd);
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

        if (g_windowDragEntry >= 0)
        {
            const int dx = x - g_windowDragStart.x;
            const int dy = y - g_windowDragStart.y;
            const int threshold = std::max(4, static_cast<int>(6.0f * g_scale));
            if (!g_windowDragging && dx * dx + dy * dy >= threshold * threshold)
            {
                g_windowDragging = true;
                g_windowDragStarted = GetTickCount64();
                g_lastFrameTick = g_windowDragStarted;
                SetTimer(hwnd, kTimerFrame, 16, nullptr);
            }
            g_windowDragCursor = {x, y};
            if (g_windowDragging)
            {
                UpdateHover(x, y);
                UpdateWindowDragTarget(x, y);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
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
        // Leaving the overlay is real pointer movement, so the mouse may take
        // hover back the next time it enters.
        g_ignorePointerUntilMoved = false;
        g_hasLastPointerPosition = false;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_CAPTURECHANGED:
        g_createDragging = false;
        g_createPull = 0.0f;
        ClearWindowDrag();
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_LBUTTONUP:
    {
        if (g_createAfterDraw)
            return 0;
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);
        if (g_windowDragEntry >= 0)
        {
            const int entry = g_windowDragEntry;
            const bool dragged = g_windowDragging;
            const int targetDesktop = g_windowDragTargetDesktop;
            bool dropStarted = false;
            if (dragged && targetDesktop >= 0)
                dropStarted = BeginWindowDropAnimation(entry, targetDesktop);
            ClearWindowDrag();
            if (GetCapture() == hwnd)
                ReleaseCapture();
            if (dragged)
            {
                if (!dropStarted && targetDesktop >= 0 &&
                    entry < static_cast<int>(g_windows.size()))
                    MoveWindowEntryToDesktopIndex(g_windows[entry].hwnd,
                                                  targetDesktop);
                InvalidateRect(hwnd, nullptr, FALSE);
                return 0;
            }
            UpdateHover(x, y);
            OnLeftClick(x, y);
            return 0;
        }
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

        if (g_windowDragging)
        {
            SetCursor(LoadCursorW(nullptr, IDC_SIZEALL));
            return TRUE;
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

    case WM_HOTKEY:
        // These keys are registered while the overlay is visible so they still
        // reach it if focus was temporarily taken by a desktop switch.
        if (wParam == kHotkeyEscape)
        {
            OnKeyDown(VK_ESCAPE);
            return 0;
        }
        if (wParam == kHotkeyReturn)
        {
            // The Return hotkey stays registered after a hide while the key is
            // still held; swallow those repeats instead of acting on a hidden
            // overlay (or letting them reach the window that regained focus).
            if (g_visible)
                OnKeyDown(VK_RETURN);
            return 0;
        }
        break;

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
        if (wParam == kTimerReturnRelease)
        {
            // Keep the Return hotkey until the physical key is up. If the
            // overlay is visible again, leave the registration alone; FinishHide
            // will remove it when the overview next closes.
            if ((GetAsyncKeyState(VK_RETURN) & 0x8000) == 0)
            {
                g_returnKeyLatch = false;
                KillTimer(hwnd, kTimerReturnRelease);
                if (!g_visible)
                    UnregisterHotKey(hwnd, kHotkeyReturn);
            }
            return 0;
        }
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
                RestoreOriginWindow();
                g_desktopEnterHide = false;
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

            if (g_windowDropAnimating &&
                now - g_windowDropStarted >=
                    static_cast<ULONGLONG>(g_windowDropDuration * 1000.0f))
            {
                HWND window = g_windowDropWindow;
                const int target = g_windowDropTargetDesktop;
                ClearWindowDropAnimation();
                if (window && target >= 0)
                    MoveWindowEntryToDesktopIndex(window, target);
            }

            if (g_presence >= 1.0f && !g_busy && !g_createAfterDraw &&
                !g_windowDragging &&
                !g_windowDropAnimating &&
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
            ReclaimOverlayForeground();
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

            const float rate =
                10.0f * 100.0f / static_cast<float>(std::max(50, g_animSpeedPercent));
            if (AdvanceCarousel(StripTarget(), static_cast<int>(g_desktops.size()),
                                dt * rate))
                KillTimer(hwnd, kTimerCarousel);
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
            const bool switching = !g_desktopActionCreate &&
                                   !g_desktopActionClose &&
                                   g_pendingDesktopTarget >= 0 &&
                                   g_pendingDesktopTarget <
                                       static_cast<int>(g_desktops.size());
            bool done = true;
            if (switching)
            {
                GUID active = {};
                bool found = g_vdm && g_overlay &&
                             SUCCEEDED(g_vdm->GetWindowDesktopId(g_overlay,
                                                                  &active));
                if (!found)
                    found = ReadActiveDesktopId(&active);
                done = found && IsEqualGUID(
                                    active, g_desktops[g_pendingDesktopTarget].id);
            }
            else
            {
                RefreshDesktops();
            }

            // The shell animates desktop changes, so poll quickly until the
            // action has actually landed instead of waiting a fixed delay.
            if (g_desktopActionCreate)
                done = static_cast<int>(g_desktops.size()) >
                           g_desktopActionStartCount &&
                       g_currentDesktop != g_desktopActionStartIndex;
            else if (g_desktopActionClose)
                done = static_cast<int>(g_desktops.size()) <
                       g_desktopActionStartCount;

            const int maxTries =
                (g_desktopActionCreate || g_desktopActionClose) ? 25 : 50;
            if (!done && ++g_pendingDesktopTries < maxTries)
            {
                SetTimer(hwnd, kTimerDesktop, 40, nullptr);
                return 0;
            }

            if (switching)
                RefreshDesktops();
            KillTimer(hwnd, kTimerDesktop);
            const bool createdDesktop = g_desktopActionCreate;
            g_busy = false;
            g_busySince = 0;
            g_desktopActionCreate = false;
            g_desktopActionClose = false;
            g_desktopActionStartCount = 0;
            g_desktopActionStartIndex = -1;
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

            // The desktop switch is finished; take the keyboard back if the
            // shell left the foreground elsewhere.
            ReclaimOverlayForeground();
            RebuildWindowList();
            g_desktopSelected = g_currentDesktop;
            if (createdDesktop)
            {
                KillTimer(hwnd, kTimerCarousel);
                g_carouselPos = CarouselDesktopPosition(
                    g_currentDesktop, static_cast<int>(g_desktops.size()));
            }
            else
            {
                KickCarousel();
            }
            if (g_presence >= 1.0f && g_cardAnim.mode == CardAnimationMode::None)
                SetTimer(hwnd, kTimerFrame, 16, nullptr);
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
        UnregisterHotKey(g_overlay, kHotkeyEscape);
        UnregisterHotKey(g_overlay, kHotkeyReturn);
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
                        g_desktopActionStartIndex = -1;
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
                g_carouselPos = CarouselDesktopPosition(
                    StripTarget(), static_cast<int>(g_desktops.size()));
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
