param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Source,
    [string]$Compiler = 'C:\1mingw\mingw64\bin\g++.exe'
)

# Use an explicit GCC path: the g++.exe on PATH may actually be LLVM-MinGW.
$ErrorActionPreference = 'Stop'
if (-not (Test-Path -LiteralPath $Compiler -PathType Leaf)) {
    throw "GCC not found: $Compiler"
}
$sourceFile = Get-Item -LiteralPath $Source
if ($sourceFile.PSIsContainer) {
    throw "Expected a C++ source file: $Source"
}
$binDirectory = Join-Path $sourceFile.DirectoryName 'bin'
New-Item -ItemType Directory -Path $binDirectory -Force | Out-Null
$executable = Join-Path $binDirectory ($sourceFile.BaseName + '.exe')
$previousPath = $env:PATH
$resultCode = 0
Push-Location -LiteralPath $sourceFile.DirectoryName
try {
    # Load GCC's runtime DLLs, rather than similarly named LLVM/Conda DLLs.
    $env:PATH = (Split-Path -Parent $Compiler) + ';' + $previousPath
    & $Compiler -std=c++20 -O2 -Wall -Wextra $sourceFile.FullName -o $executable
    $resultCode = $LASTEXITCODE
    if ($resultCode -eq 0) {
        & $executable
        $resultCode = $LASTEXITCODE
    }
} finally {
    $env:PATH = $previousPath
    Pop-Location
}
exit $resultCode
