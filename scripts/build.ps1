$ErrorActionPreference = 'Stop'
$root = Split-Path $PSScriptRoot -Parent
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vs = & $vswhere -latest -property installationPath
& "$vs\MSBuild\Current\Bin\MSBuild.exe" "$root\CP_Main_10.sln" /t:Restore /p:RestorePackagesConfig=true /p:Configuration=Release /p:Platform=x64 /nologo
if ($LASTEXITCODE -ne 0) { throw 'Restore failed' }
& "$vs\MSBuild\Current\Bin\MSBuild.exe" "$root\CP_Main_10.sln" /p:Configuration=Release /p:Platform=x64 "/p:ForceImportBeforeCppTargets=$root\local\mfc.props" /m:2 /nologo
if ($LASTEXITCODE -ne 0) { throw 'Build failed' }
