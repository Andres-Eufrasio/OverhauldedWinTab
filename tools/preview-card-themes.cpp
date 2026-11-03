// Development-only harness. Artwork and basic drawing helpers are extracted
// unchanged from the production mod by preview-card-themes.ps1.
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

static ID2D1Factory* g_d2dFactory = nullptr;
static ID2D1RenderTarget* g_d2dTarget = nullptr;
static ID2D1SolidColorBrush* g_d2dBrush = nullptr;
#include "card-art-extracted.inc"

static void Check(HRESULT hr)
{
    if (FAILED(hr))
    {
        std::fprintf(stderr, "Preview failed: HRESULT 0x%08lX\n", hr);
        std::exit(1);
    }
}

static IDWriteFactory* g_write = nullptr;
// Minimal, deterministic scene state for the unchanged production card
// renderers. Image loaders return null to exercise the embedded artwork.
static float g_scale = 1.0f;
static bool g_tuckCards = false, g_createAfterDraw = false, g_focusStrip = false;
static int g_desktopSelected = 0, g_currentDesktop = 0;
static bool g_hideCardSuitsWithDesign = false, g_cardTextPositionCustom = false;
static int g_cardTextX = 0, g_cardTextY = 0, g_renameDesktop = -1;
static std::wstring g_renameText, g_cardTheme;
static IDWriteTextFormat* g_fmtHint = nullptr;
static IDWriteTextFormat* g_fmtPillLarge = nullptr;
static IDWriteTextFormat* g_fmtCardSuit = nullptr;
static IDWriteTextFormat* g_fmtCardSuitBig = nullptr;
static struct { UINT32 accent, pillFill, text; } g_theme = {
    0xFF4CC2FF, 0xFF12151C, 0xFFFFFFFF};
static struct { std::wstring name; } g_desktops[] = {{L"Desktop 1"}};
enum class CardAnimationMode { None, Draw, Throw };
static struct {
    CardAnimationMode mode = CardAnimationMode::None;
    ULONGLONG start = 0;
    float duration = .4f;
    RectF from, to;
} g_cardAnim;
struct PillView {
    int desktop = 0;
    RectF rect, closeRect;
    float alpha = 1.0f, lift = 0.0f;
    bool hasClose = true;
};
static float DesktopHighlightStrength(bool selected, bool active) {
    return selected ? 1.0f : active ? .7f : 0.0f;
}
static bool StripBackgroundVisible() { return false; }
static ID2D1Bitmap* EnsureCardDesignBitmap() { return nullptr; }
static ID2D1Bitmap* EnsureCardBackBitmap() { return nullptr; }
static void DrawBitmapCover(ID2D1Bitmap*, const RectF&, float) {}
static float MeasureTextWidth(const std::wstring&, IDWriteTextFormat*) { return 0; }
#include "card-renderers-extracted.inc"

static void CardFonts(float scale)
{
    for (auto** font : {&g_fmtHint, &g_fmtPillLarge, &g_fmtCardSuit, &g_fmtCardSuitBig})
    {
        if (*font)
            (*font)->Release();
        *font = nullptr;
    }
    const float sizes[] = {12, 15, 15, 44};
    IDWriteTextFormat** fonts[] = {
        &g_fmtHint, &g_fmtPillLarge, &g_fmtCardSuit, &g_fmtCardSuitBig};
    for (int i = 0; i < 4; ++i)
    {
        Check(g_write->CreateTextFormat(i < 2 ? L"Segoe UI Variable Text" : L"Segoe UI Symbol",
            nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL, sizes[i] * scale, L"", fonts[i]));
        (*fonts[i])->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        (*fonts[i])->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    }
}

static void Label(const wchar_t* text, const RectF& rect, float size,
                   UINT32 color = 0xFFEAEAF0)
{
    IDWriteTextFormat* format = nullptr;
    Check(g_write->CreateTextFormat(L"Segoe UI", nullptr,
        DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, size, L"en-US", &format));
    g_d2dBrush->SetColor(ColorOf(color));
    g_d2dTarget->DrawTextW(text, static_cast<UINT32>(wcslen(text)), format,
        D2D1::RectF(rect.l, rect.t, rect.r, rect.b), g_d2dBrush);
    format->Release();
}

static void Sample(bool saiki, float x, float y, float scale,
                    bool tucked = false, bool face = false, bool rotated = false)
{
    const float w = 160.0f * scale;
    const float h = 224.0f * scale;
    const RectF card = {x, y, x + w, y + h};
    g_scale = rotated ? 1.5f : 1.0f;
    g_tuckCards = tucked;
    g_cardTheme = saiki ? L"saiki-k" : L"yugioh";
    CardFonts(g_scale);
    D2D1::Matrix3x2F saved;
    g_d2dTarget->GetTransform(&saved);
    if (rotated)
        g_d2dTarget->SetTransform(D2D1::Matrix3x2F::Rotation(
            -9.0f, D2D1::Point2F(x + w / 2, y + h / 2)) * saved);
    if (tucked)
        g_d2dTarget->PushAxisAlignedClip(
            D2D1::RectF(x - 3, y - 3, x + w + 3, y + h / 2),
            D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    if (face)
    {
        PillView pill;
        pill.rect = card;
        pill.closeRect = {card.r - 32 * g_scale, card.t + 8 * g_scale,
                           card.r - 8 * g_scale, card.t + 32 * g_scale};
        DrawDesktopCard(pill, false, false, false, false);
    }
    else
        DrawCreateCard(card, false, 0.0f);
    if (tucked)
        g_d2dTarget->PopAxisAlignedClip();
    g_d2dTarget->SetTransform(saved);
}

int wmain(int argc, wchar_t** argv)
{
    if (argc != 2)
        return 2;
    Check(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED));
    IWICImagingFactory* wic = nullptr;
    Check(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory, reinterpret_cast<void**>(&wic)));
    IWICBitmap* bitmap = nullptr;
    Check(wic->CreateBitmap(1480, 940, GUID_WICPixelFormat32bppPBGRA,
        WICBitmapCacheOnLoad, &bitmap));
    Check(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_d2dFactory));
    const auto properties = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_SOFTWARE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
                          D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    Check(g_d2dFactory->CreateWicBitmapRenderTarget(bitmap, properties, &g_d2dTarget));
    Check(g_d2dTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &g_d2dBrush));
    Check(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&g_write)));

    g_d2dTarget->BeginDraw();
    g_d2dTarget->Clear(ColorOf(0xFF151820));
    Label(L"WIN+TAB / VECTOR CARD ART", {30, 18, 1400, 55}, 26);
    Label(L"Offscreen Direct2D render of the production artwork, not a mockup",
        {30, 58, 1400, 85}, 15, 0xFF9CA5B8);
    const wchar_t* headings[] = {L"SMALL / 82%", L"MEDIUM / 100%", L"LARGE / 122%",
        L"TUCKED / UPPER HALF", L"DESKTOP FACE", L"150% DPI / ROTATED"};
    const float xs[] = {30, 210, 420, 655, 885, 1120};
    for (int col = 0; col < 6; ++col)
        Label(headings[col], {xs[col], 98, xs[col] + 300, 120}, 12);
    Label(L"SAIKI K. / OFFICIAL TITLE OUTLINES", {30, 126, 1000, 153}, 16);
    for (bool saiki : {true, false})
    {
        const float y = saiki ? 163.0f : 560.0f;
        Sample(saiki, xs[0], y, .82f);
        Sample(saiki, xs[1], y, 1.0f);
        Sample(saiki, xs[2], y, 1.22f);
        Sample(saiki, xs[3], y, 1.18f, true);
        Label(L"TUCKED DESKTOP", {xs[3], y + 158, xs[3] + 220, y + 180}, 12);
        Sample(saiki, xs[3], y + 185, 1.18f, true, true);
        Sample(saiki, xs[4], y, 1.0f, false, true);
        Sample(saiki, xs[5], y, 1.5f, false, false, true);
    }
    Label(L"YU-GI-OH! / ORIGINAL VORTEX CARD BACK", {30, 523, 1000, 550}, 16);
    Check(g_d2dTarget->EndDraw());
    for (auto* path : g_vectorCardArt)
        if (!path)
            Check(E_FAIL);

    IWICStream* stream = nullptr;
    Check(wic->CreateStream(&stream));
    Check(stream->InitializeFromFilename(argv[1], GENERIC_WRITE));
    IWICBitmapEncoder* encoder = nullptr;
    Check(wic->CreateEncoder(GUID_ContainerFormatPng, nullptr, &encoder));
    Check(encoder->Initialize(stream, WICBitmapEncoderNoCache));
    IWICBitmapFrameEncode* frame = nullptr;
    Check(encoder->CreateNewFrame(&frame, nullptr));
    Check(frame->Initialize(nullptr));
    Check(frame->SetSize(1480, 940));
    auto pixelFormat = GUID_WICPixelFormat32bppBGRA;
    Check(frame->SetPixelFormat(&pixelFormat));
    Check(frame->WriteSource(bitmap, nullptr));
    Check(frame->Commit());
    Check(encoder->Commit());
    frame->Release();
    encoder->Release();
    stream->Release();
    ReleaseVectorCardArt();
    for (auto* font : {g_fmtHint, g_fmtPillLarge, g_fmtCardSuit, g_fmtCardSuitBig})
        if (font)
            font->Release();
    g_write->Release();
    g_d2dBrush->Release();
    g_d2dTarget->Release();
    g_d2dFactory->Release();
    bitmap->Release();
    wic->Release();
    CoUninitialize();
    return 0;
}
