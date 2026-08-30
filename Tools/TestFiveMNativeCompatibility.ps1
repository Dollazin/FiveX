param(
    [string]$CatalogPath = (Join-Path $PSScriptRoot "..\Runtime\Lua\LuaNativeCatalog.inl"),
    [string]$RuntimePath = (Join-Path $PSScriptRoot "..\Runtime\Lua\LuaRuntime.cpp"),
    [string]$GeneratorPath = (Join-Path $PSScriptRoot "GenerateLuaNativeCatalog.ps1"),
    [string]$CoreNativesPath = (Join-Path $PSScriptRoot "..\CoreNatives.h")
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path -LiteralPath $CatalogPath)) { throw "Catalog not found: $CatalogPath" }
if (-not (Test-Path -LiteralPath $RuntimePath)) { throw "Runtime not found: $RuntimePath" }
if (-not (Test-Path -LiteralPath $GeneratorPath)) { throw "Generator not found: $GeneratorPath" }
if (-not (Test-Path -LiteralPath $CoreNativesPath)) { throw "Core native wrappers not found: $CoreNativesPath" }

$catalog = Get-Content -LiteralPath $CatalogPath -Raw
$runtime = Get-Content -LiteralPath $RuntimePath -Raw
$generator = Get-Content -LiteralPath $GeneratorPath -Raw
$coreNatives = Get-Content -LiteralPath $CoreNativesPath -Raw

if ($generator -match '\$InputPath' -or $generator -match 'Get-Content[^\r\n]+Natives\.h') {
    throw 'Lua native generator still depends on a typed C++ native header'
}

$legacyHeader = Join-Path $PSScriptRoot "..\GameNatives.h"
if (Test-Path -LiteralPath $legacyHeader) {
    throw "Legacy monolithic native header still exists: $legacyHeader"
}

$coreWrapperCount = ([Regex]::Matches($coreNatives, '(?m)^inline\s+')).Count
if ($coreWrapperCount -gt 64) {
    throw "Core native wrapper header unexpectedly large: $coreWrapperCount wrappers"
}

$expectedCatalogEntries = @{
    DrawRect = 'FiveXLuaNativeReturnVoid, 8, 8'
    DrawSprite = 'FiveXLuaNativeReturnVoid, 11, 11'
    EndTextCommandDisplayText = 'FiveXLuaNativeReturnVoid, 2, 2'
    SetTextDropshadow = 'FiveXLuaNativeReturnVoid, 5, 5'
    SetVehicleEngineOn = 'FiveXLuaNativeReturnVoid, 4, 4'
}

foreach ($entry in $expectedCatalogEntries.GetEnumerator()) {
    $pattern = '\{\s*"' + [Regex]::Escape($entry.Key) + '"[^\r\n]*' +
        [Regex]::Escape($entry.Value)
    if ($catalog -notmatch $pattern) {
        throw "FiveM signature mismatch for $($entry.Key): expected $($entry.Value)"
    }
}

$requiredRuntimeFragments = @(
    '#define FIVEX_LUA_MAX_RESOURCES 64',
    '#define FIVEX_LUA_MAX_FILE_SIZE (2 * 1024 * 1024)',
    'static INT LuaResolveCatalogNative(lua_State* state)',
    'FiveXNativeAvailable(entry->Hash)',
    'InstallNativeCatalogResolver(state, resource)',
    'static BOOL NormalizeRelativePath(',
    "value = '\\';",
    'source->Root, normalizedScript',
    'g_manifestResource->Root, normalizedScript',
    'RequireLuaArgumentCount(state, "SetEntityCoords", 4, 8)',
    'RequireLuaArgumentCount(state, "GetGroundZFor3dCoord", 3, 4)',
    'RequireLuaArgumentCount(state, "SetVehicleEngineOn", 3, 4)',
    'RequireLuaArgumentCount(state, "SetTextDropshadow", 5, 5)',
    'SetTextDropShadow();'
)

foreach ($fragment in $requiredRuntimeFragments) {
    if (-not $runtime.Contains($fragment)) {
        throw "Runtime compatibility fragment missing: $fragment"
    }
}

$entryCount = ([Regex]::Matches($catalog, '(?m)^\s*\{\s*"')).Count
if ($entryCount -lt 4000) {
    throw "Generated catalog unexpectedly small: $entryCount entries"
}

Write-Host "FiveM native compatibility checks passed: $entryCount catalog entries; $coreWrapperCount core wrappers."
