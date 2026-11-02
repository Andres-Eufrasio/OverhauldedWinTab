# build.ps1
#
# Standalone syntax + link check for OverhauldedWinTab.wh.cpp using the compiler
# bundled with Windhawk. This does not install the mod; it only verifies that the
# source compiles and links cleanly.
#
# Usage:
#   .\build.ps1

$ErrorActionPreference = 'Stop'

$root = $PSScriptRoot
$compilerRoot = 'C:\Program Files\Windhawk\Compiler'
$clang = Join-Path $compilerRoot 'bin\clang++.exe'
$includeDir = Join-Path $compilerRoot 'include'
$libDir = Join-Path $compilerRoot 'x86_64-w64-mingw32\lib'

$source = Join-Path $root 'OverhauldedWinTab.wh.cpp'
$output = Join-Path $root 'OverhauldedWinTab.dll'

foreach ($path in @($clang, $includeDir, $libDir, $source)) {
    if (-not (Test-Path $path)) {
        throw "Required path not found: $path"
    }
}

$arguments = @(
    '-x', 'c++',
    '-std=c++23',
    '-target', 'x86_64-w64-mingw32',
    '-DUNICODE', '-D_UNICODE',
    '-DWINVER=0x0A00', '-D_WIN32_WINNT=0x0A00', '-D_WIN32_IE=0x0A00',
    '-DNTDDI_VERSION=0x0A000008',
    '-D__USE_MINGW_ANSI_STDIO=0',
    '-DWH_MOD', '-DWH_EDITING',
    '-I', $includeDir,
    '-include', 'windhawk_api.h',
    '-L', $libDir,
    '-shared', '-O1',
    '-Wno-pragma-pack',
    '-Wno-pragma-system-header-outside-header',
    '-fuse-ld=lld',
    '-o', $output,
    $source,
    '-lshell32', '-lole32', '-lgdi32', '-luser32', '-ladvapi32',
    '-lshcore', '-lversion', '-ldwmapi', '-ld2d1', '-ldwrite', '-lwindowscodecs'
)

& $clang @arguments
if ($LASTEXITCODE -ne 0) {
    throw "Compilation failed with exit code $LASTEXITCODE"
}

Write-Host "Compiled successfully: $output"
