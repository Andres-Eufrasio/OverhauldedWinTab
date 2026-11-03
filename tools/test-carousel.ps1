# Regression tests for the production carousel positioning and animation math.
# Does not install the mod or interact with Explorer.
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot
$compilerRoot = 'C:\Program Files\Windhawk\Compiler'
$text = [IO.File]::ReadAllText((Join-Path $root 'OverhauldedWinTab.wh.cpp'))
$begin = $text.IndexOf('static float CarouselDesktopPosition(')
if ($begin -lt 0) { throw 'Missing carousel test source boundaries' }
$end = $text.IndexOf('// The pill the carousel should centre:', $begin)
if ($end -lt 0) { throw 'Missing carousel test source boundaries' }
$math = $text.Substring($begin, $end - $begin)

$test = @'
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

static float g_carouselPos = 0.0f;
static int g_carouselAnchor = 0;
'@ + "`n" + $math + @'

static void Check(bool ok, const char* message)
{
    if (!ok) {
        std::fprintf(stderr, "%s\n", message);
        std::exit(1);
    }
}

static float Depth(int desktop, int count = 2)
{
    return WrapDelta(CarouselDesktopPosition(desktop, count) - g_carouselPos, count);
}

static void Frame(int target, float blend, int count = 2)
{
    float before[4] = {};
    for (int i = 0; i < count; ++i)
        before[i] = Depth(i, count);
    AdvanceCarousel(target, count, blend);
    for (int i = 0; i < count; ++i) {
        Check(std::fabs(Depth(i, count) - before[i]) <= (count - 1) * blend + 0.002f,
              "Desktop jumped to the opposite side during animation");
        Check(std::fabs((Depth(i, count) - Depth(0, count)) -
                        (before[i] - before[0])) < 0.0001f,
              "Desktops changed their left/right order");
    }
}

int main()
{
    for (int initial = 0; initial < 2; ++initial) {
        for (float blend : {0.08f, 0.16f, 0.5f, 1.0f}) {
            ResetCarouselPosition(initial, 2);
            Check(Depth(initial) == 0.0f && Depth(1 - initial) == 1.0f,
                  "Initial desktop must be centred with its neighbour on the right");
            // For initial desktop 2: 021 -> 210 -> 021, repeatedly.
            for (int cycle = 0; cycle < 20; ++cycle) {
                for (int target : {1 - initial, initial}) {
                    for (int frame = 0; frame < 200; ++frame)
                        Frame(target, blend);
                    Check(Depth(target) == 0.0f, "Target did not reach the centre");
                    Check(Depth(1 - target) == (target == initial ? 1.0f : -1.0f),
                          "Neighbour settled on the wrong side");
                }
            }
            // Reverse direction before settling, like rapid arrow-key presses.
            for (int frame = 0; frame < 1000; ++frame)
                Frame((frame / 3) % 2, blend);
        }
    }
    for (int initial = 0; initial < 4; ++initial) {
        for (float blend : {0.08f, 0.16f, 0.5f, 1.0f}) {
            ResetCarouselPosition(initial, 4);
            Check(Depth(initial, 4) == 0.0f &&
                  Depth((initial + 3) % 4, 4) == -1.0f &&
                  Depth((initial + 1) % 4, 4) == 1.0f &&
                  Depth((initial + 2) % 4, 4) == 2.0f,
                  "Four-desktop initial wheel order changed");
            // Exercise every source/target combination, including wrapped keys.
            for (int cycle = 0; cycle < 5; ++cycle) {
                for (int from = 0; from < 4; ++from) {
                    for (int target = 0; target < 4; ++target) {
                        for (int frame = 0; frame < 200; ++frame)
                            Frame(from, blend, 4);
                        for (int frame = 0; frame < 200; ++frame)
                            Frame(target, blend, 4);
                        Check(Depth(target, 4) == 0.0f,
                              "Four-desktop target did not reach the centre");
                    }
                }
            }
            for (int frame = 0; frame < 1000; ++frame)
                Frame((frame / 3) % 4, blend, 4);
        }
    }
    Check(WrapDelta(1.0f, 1) == 0.0f, "Single-desktop regression");
    for (int count : {3, 5, 8}) {
        ResetCarouselPosition(0, count);
        Check(CarouselDesktopPosition(1, count) == 1.0f,
              "Other carousel inherited the fixed slot order");
        Check(WrapDelta(static_cast<float>(count - 1), count) == -1.0f,
              "Larger carousel no longer takes the shortest wrapped path");
    }
    std::puts("Carousel tests passed: two/four desktops, all starting selections, continuous frames, repeated switches, rapid reversals, other wheels.");
}
'@

$temp = Join-Path $env:LOCALAPPDATA 'Temp\opencode'
$name = 'wintab-carousel-test-' + [guid]::NewGuid().ToString('N')
$source = Join-Path $temp "$name.cpp"
$exe = Join-Path $temp "$name.exe"
$oldPath = $env:PATH
try {
    [IO.File]::WriteAllText($source, $test)
    & (Join-Path $compilerRoot 'bin\clang++.exe') '-std=c++23' '-target' 'x86_64-w64-mingw32' '-O2' '-fuse-ld=lld' '-static' $source '-o' $exe
    if ($LASTEXITCODE -ne 0) { throw 'Carousel test compilation failed' }
    $env:PATH = (Join-Path $compilerRoot 'x86_64-w64-mingw32\bin') + ";$oldPath"
    & $exe
    if ($LASTEXITCODE -ne 0) { throw 'Carousel regression tests failed' }
} finally {
    $env:PATH = $oldPath
    Remove-Item -LiteralPath $source, $exe -ErrorAction SilentlyContinue
}
