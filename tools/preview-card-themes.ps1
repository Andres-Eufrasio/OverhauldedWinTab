param(
    [string]$OutputPath = (Join-Path $PSScriptRoot '..\docs\theme-previews.png')
)

# Offscreen Direct2D preview of the exact artwork functions in the Windhawk mod.
# Does not install the mod, inject into Explorer, or open/change any windows.
$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot
$compilerRoot = 'C:\Program Files\Windhawk\Compiler'
$clang = Join-Path $compilerRoot 'bin\clang++.exe'
$temp = Join-Path $env:LOCALAPPDATA 'Temp\opencode\wintab-art-preview'
New-Item -ItemType Directory -Force $temp | Out-Null
$text = [IO.File]::ReadAllText((Join-Path $root 'OverhauldedWinTab.wh.cpp'))

function Extract([string]$Begin, [string]$End) {
    $start = $text.IndexOf($Begin, [StringComparison]::Ordinal)
    if ($start -lt 0) { throw "Missing preview source boundary: $Begin" }
    $finish = $text.IndexOf($End, $start, [StringComparison]::Ordinal)
    if ($start -lt 0 -or $finish -lt 0) { throw "Missing preview source boundary: $Begin" }
    return $text.Substring($start, $finish - $start)
}

$extracted = @(
    (Extract 'struct RectF' 'static bool Contains('),
    (Extract 'static D2D1_COLOR_F ColorOf(' 'static float EaseOutCubic('),
    (Extract 'static float EaseOutCubic(' 'static RectF ScaleAbout('),
    (Extract 'static UINT32 MixColor(' '// Builds a full palette'),
    (Extract 'static void FillRound(' '// Adds a closed circle to a geometry sink.'),
    (Extract '// BEGIN VECTOR CARD ART' '// END VECTOR CARD ART')
) -join "`n"
$include = Join-Path $temp 'card-art-extracted.inc'
[IO.File]::WriteAllText($include, $extracted)
$renderers = @(
    (Extract 'static void DrawTextBlock(' '// Draws a single line of text along the top arc'),
    (Extract 'static void DrawDesktopCard(' 'static void ClearCardAnimation(')
) -join "`n"
[IO.File]::WriteAllText((Join-Path $temp 'card-renderers-extracted.inc'), $renderers)
$exe = Join-Path $temp 'card-theme-preview.exe'
$arguments = @(
    '-std=c++23', '-target', 'x86_64-w64-mingw32',
    '-DUNICODE', '-D_UNICODE', '-municode', '-O2', '-fuse-ld=lld', '-static',
    '-I', $temp, '-L', (Join-Path $compilerRoot 'x86_64-w64-mingw32\lib'),
    (Join-Path $PSScriptRoot 'preview-card-themes.cpp'),
    '-o', $exe, '-ld2d1', '-ldwrite', '-lole32', '-lwindowscodecs', '-luuid'
)
& $clang @arguments
if ($LASTEXITCODE -ne 0) { throw 'Preview compilation failed' }
$output = [IO.Path]::GetFullPath($OutputPath)
$oldPath = $env:PATH
try {
    $runtime = Join-Path $compilerRoot 'x86_64-w64-mingw32\bin'
    $env:PATH = "$runtime;$oldPath"
    & $exe $output
    if ($LASTEXITCODE -ne 0) { throw "Direct2D preview rendering failed: $LASTEXITCODE" }
} finally {
    $env:PATH = $oldPath
}
Write-Host "Rendered production artwork: $output"
