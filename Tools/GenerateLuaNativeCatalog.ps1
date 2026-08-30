param(
    [string]$MetadataPath = (Join-Path $PSScriptRoot "NativeMetadata\natives_fivem.json"),
    [string]$OutputPath = (Join-Path $PSScriptRoot "..\Runtime\Lua\LuaNativeCatalog.inl"),
    [string]$ReportPath = (Join-Path $PSScriptRoot "..\Runtime\Lua\LuaNativeCatalogReport.txt")
)

$ErrorActionPreference = "Stop"

function Convert-ToLuaNativeName([string]$name) {
    if (-not $name -or $name -match '0x' -or $name -notmatch '^[A-Za-z_][A-Za-z0-9_]*$') {
        return $null
    }
    $parts = @($name.Trim('_').Split('_') | Where-Object { $_ })
    if (-not $parts.Count) { return $null }
    $result = ''
    foreach ($part in $parts) {
        $lower = $part.ToLowerInvariant()
        $result += $lower.Substring(0, 1).ToUpperInvariant() + $lower.Substring(1)
    }
    return $result
}

function Get-LuaArgumentKind([string]$type, [bool]$allowAny) {
    $type = ($type -replace '\s+', ' ').Trim()
    if ($type -match '^(const\s+)?(CHAR|char)\s*\*$') {
        return 'FiveXLuaNativeArgumentString'
    }
    if ($type.Contains('*') -or $type.Contains('[')) { return $null }
    if ($type -match '^(BOOL|bool)$') { return 'FiveXLuaNativeArgumentBoolean' }
    if ($type -match '^(FLOAT|float|double)$') { return 'FiveXLuaNativeArgumentFloat' }
    if ($type -eq 'Any' -and -not $allowAny) { return $null }
    if ($type -match '^[A-Za-z_]\w*$') { return 'FiveXLuaNativeArgumentInteger' }
    return $null
}

function Get-LuaReturnKind([string]$type, [bool]$allowAny) {
    $type = ($type -replace '\s+', ' ').Trim()
    if ($type -match '^(VOID|void)$') { return 'FiveXLuaNativeReturnVoid' }
    if ($type -match '^(BOOL|bool)$') { return 'FiveXLuaNativeReturnBoolean' }
    if ($type -match '^(FLOAT|float|double)$') { return 'FiveXLuaNativeReturnFloat' }
    if ($type -eq 'Vector3') { return 'FiveXLuaNativeReturnVector3' }
    if ($type -match '^(const\s+)?(CHAR|char)\s*\*$') { return 'FiveXLuaNativeReturnString' }
    if ($type.Contains('*') -or $type.Contains('[')) { return $null }
    if ($type -eq 'Any' -and -not $allowAny) { return $null }
    if ($type -match '^[A-Za-z_]\w*$') { return 'FiveXLuaNativeReturnInteger' }
    return $null
}

function Test-OutputPointerKind([string]$kind) {
    return $kind -eq 'FiveXLuaNativeArgumentPointerNull' -or
        $kind -match '^FiveXLuaNativeArgumentPointerOut'
}

function New-CatalogEntry([string]$name, [string]$hash,
    [string]$returnKind, [System.Collections.Generic.List[string]]$argumentKinds) {
    $arguments = if ($argumentKinds.Count) { $argumentKinds -join ', ' } else { 'FiveXLuaNativeArgumentNone' }
    $luaArgumentCount = @($argumentKinds | Where-Object { -not (Test-OutputPointerKind $_) }).Count
    return ('    {{ "{0}", {1}, {2}, {3}, {4}, {{ {5} }} }},' -f
        $name, $hash, $returnKind, $argumentKinds.Count, $luaArgumentCount, $arguments)
}

if (-not (Test-Path -LiteralPath $MetadataPath)) { throw "Native metadata not found: $MetadataPath" }

$metadataJson = Get-Content -LiteralPath $MetadataPath -Raw
if ($PSVersionTable.PSVersion.Major -ge 6) {
    $metadata = $metadataJson | ConvertFrom-Json -AsHashtable
} else {
    Add-Type -AssemblyName System.Web.Extensions
    $jsonSerializer = New-Object System.Web.Script.Serialization.JavaScriptSerializer
    $jsonSerializer.MaxJsonLength = [Int32]::MaxValue
    $metadata = $jsonSerializer.DeserializeObject($metadataJson)
}
$metadataByJhash = @{}
foreach ($namespaceName in $metadata.Keys) {
    foreach ($nativeHash in $metadata[$namespaceName].Keys) {
        $definition = $metadata[$namespaceName][$nativeHash]
        if (-not $definition.jhash) { continue }
        $key = ([string]$definition.jhash).ToUpperInvariant()
        if ($metadataByJhash.ContainsKey($key)) { continue }
        $metadataByJhash[$key] = [PSCustomObject]@{
            Namespace = $namespaceName
            Hash64 = $nativeHash
            Definition = $definition
        }
    }
}

# These pointer parameters represent a handle passed by address. Lua receives
# the handle normally; the runtime creates the temporary address internally.
$inputPointerNatives = @{
    'CLEAR_SEQUENCE_TASK' = $true
    'DELETE_ENTITY' = $true
    'DELETE_MISSION_TRAIN' = $true
    'DELETE_OBJECT' = $true
    'DELETE_PED' = $true
    'DELETE_ROPE' = $true
    'DELETE_VEHICLE' = $true
    'REMOVE_BLIP' = $true
    'REMOVE_PED_ELEGANTLY' = $true
    'SET_ENTITY_AS_NO_LONGER_NEEDED' = $true
    'SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED' = $true
    'SET_OBJECT_AS_NO_LONGER_NEEDED' = $true
    'SET_PED_AS_NO_LONGER_NEEDED' = $true
    'SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED' = $true
    'SET_VEHICLE_AS_NO_LONGER_NEEDED' = $true
}

# These signatures use pointer parameters as arrays, script structures, or
# arbitrary caller memory. A scalar temporary would be unsafe or misleading.
$unsafePointerNatives = @{
    'CLEAR_BIT' = $true
    'SET_BIT' = $true
    'SET_BITS_IN_RANGE' = $true
    'NETWORK_CLAN_GET_MEMBERSHIP_COUNT' = $true
    'NETWORK_CLAN_GET_MEMBERSHIP_VALID' = $true
    'NETWORK_REGISTER_HOST_BROADCAST_VARIABLES' = $true
    'NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES' = $true
    'PLAY_ENTITY_SCRIPTED_ANIM' = $true
    'TASK_SCRIPTED_ANIMATION' = $true
}

function Get-PointerArgumentKind([string]$type, [string]$nativeName) {
    $type = ($type -replace '\s+', '').Trim()
    if (($nativeName -eq 'ADD_ROPE' -or $nativeName -eq 'ATTACH_ENTITIES_TO_ROPE') -and
        $type -eq 'Any*') {
        return 'FiveXLuaNativeArgumentPointerNull'
    }
    if ($unsafePointerNatives.ContainsKey($nativeName)) { return $null }
    if ($inputPointerNatives.ContainsKey($nativeName)) {
        if ($type -match '^(int|Entity|Vehicle|Ped|Object|Blip)\*$') {
            return 'FiveXLuaNativeArgumentPointerInInteger'
        }
        return $null
    }
    if ($type -eq 'float*') { return 'FiveXLuaNativeArgumentPointerOutFloat' }
    if ($type -eq 'BOOL*') { return 'FiveXLuaNativeArgumentPointerOutBoolean' }
    if ($type -eq 'Vector3*') { return 'FiveXLuaNativeArgumentPointerOutVector3' }
    if ($type -match '^(int|Entity|Vehicle|Ped|Object|Blip|Hash|ScrHandle)\*$') {
        return 'FiveXLuaNativeArgumentPointerOutInteger'
    }
    return $null
}

$primaryEntries = New-Object System.Collections.Generic.List[object]
$aliasCandidates = New-Object System.Collections.Generic.List[object]
$metadataJhashCount = $metadataByJhash.Count
$safeNativeCount = 0
$pointerSkippedCount = 0
$pointerSafeCount = 0
$unsupportedSkippedCount = 0
$tooManyArgumentsCount = 0

# Build the Lua catalog directly from official FiveM definitions that expose a
# legacy 32-bit Xbox jhash. Typed C++ wrappers are deliberately not parsed:
# core code and resource-facing Lua bindings are independent.
foreach ($metadataKey in @($metadataByJhash.Keys | Sort-Object)) {
    $metadataEntry = $metadataByJhash[$metadataKey]
    $definition = $metadataEntry.Definition
    $metadataReturnType = if ($definition.return_type) {
        [string]$definition.return_type
    } else {
        [string]$definition.results
    }
    $returnKind = Get-LuaReturnKind $metadataReturnType $true
    $argumentKinds = New-Object System.Collections.Generic.List[string]
    $valid = $true
    $hasPointer = $false
    $pointerSupported = $true

    if ($metadataReturnType -match '\*' -and
        $metadataReturnType -notmatch '^(const\s+)?char\s*\*$') { $hasPointer = $true }
    foreach ($argument in $definition.params) {
        $argumentType = [string]$argument.type
        if ($argumentType -match '\*' -and $argumentType -notmatch '^(const\s+)?char\s*\*$') {
            $hasPointer = $true
            $kind = Get-PointerArgumentKind $argumentType ([string]$definition.name)
            if (-not $kind) { $pointerSupported = $false }
        } else {
            $kind = Get-LuaArgumentKind $argumentType $true
        }
        if (-not $kind) { $valid = $false; break }
        $argumentKinds.Add($kind)
    }

    if ($hasPointer -and -not $pointerSupported) { $pointerSkippedCount++; continue }
    if (-not $valid -or -not $returnKind) { $unsupportedSkippedCount++; continue }
    if ($argumentKinds.Count -gt 24) { $tooManyArgumentsCount++; continue }

    $modernName = Convert-ToLuaNativeName ([string]$definition.name)
    if (-not $modernName) { $unsupportedSkippedCount++; continue }
    $hash = $metadataKey.ToUpperInvariant().Replace('X', 'x')
    $primaryEntries.Add([PSCustomObject]@{
        Name = $modernName
        Hash = $hash
        ReturnKind = $returnKind
        ArgumentKinds = $argumentKinds
    })
    $safeNativeCount++
    if ($hasPointer) { $pointerSafeCount++ }

    foreach ($metadataAlias in @($definition.aliases)) {
        $aliasName = Convert-ToLuaNativeName ([string]$metadataAlias)
        if (-not $aliasName -or $aliasName -eq $modernName) { continue }
        $aliasCandidates.Add([PSCustomObject]@{
            Name = $aliasName
            Hash = $hash
            ReturnKind = $returnKind
            ArgumentKinds = $argumentKinds
        })
    }
}

$catalogLines = New-Object System.Collections.Generic.List[string]
$catalogNames = [System.Collections.Generic.Dictionary[string, string]]::new(
    [System.StringComparer]::Ordinal)
foreach ($entry in $primaryEntries) {
    if ($catalogNames.ContainsKey($entry.Name)) { continue }
    $catalogNames[$entry.Name] = $entry.Hash
    $catalogLines.Add((New-CatalogEntry $entry.Name $entry.Hash $entry.ReturnKind $entry.ArgumentKinds))
}

$aliasCount = 0
$aliasConflictCount = 0
foreach ($entry in $aliasCandidates) {
    if ($catalogNames.ContainsKey($entry.Name)) {
        if ($catalogNames[$entry.Name] -ne $entry.Hash) { $aliasConflictCount++ }
        continue
    }
    $catalogNames[$entry.Name] = $entry.Hash
    $catalogLines.Add((New-CatalogEntry $entry.Name $entry.Hash $entry.ReturnKind $entry.ArgumentKinds))
    $aliasCount++
}

$header = @(
    '// Generated by Tools/GenerateLuaNativeCatalog.ps1.',
    '// FiveM signatures and names come from natives_fivem.json; calls use legacy 32-bit Xbox jhash values.',
    '// The catalog is independent from the typed wrappers used by the C++ core.',
    '// Every candidate is filtered by the Xbox native registration table at runtime.',
    '// Safe scalar/output pointers are converted to Lua values; arrays and arbitrary pointers remain excluded.',
    ('// Metadata jhashes: {0}; safe natives: {1}; callable entries: {2}; aliases: {3}; pointer natives: {4}.' -f
        $metadataJhashCount, $safeNativeCount, $catalogLines.Count, $aliasCount, $pointerSafeCount),
    ''
)
[System.IO.File]::WriteAllText($OutputPath, (($header + $catalogLines) -join "`r`n") + "`r`n",
    (New-Object System.Text.UTF8Encoding($false)))

$report = @(
    'FiveX Lua native catalog report',
    ('Generated: {0:u}' -f [DateTime]::UtcNow),
    '',
    ('Official metadata entries with Xbox jhash: {0}' -f $metadataJhashCount),
    ('Safe metadata natives added: {0}' -f $safeNativeCount),
    ('Official aliases added: {0}' -f $aliasCount),
    ('Final callable Lua globals: {0}' -f $catalogLines.Count),
    ('Safe pointer natives added: {0}' -f $pointerSafeCount),
    ('Pointer signatures skipped: {0}' -f $pointerSkippedCount),
    ('Unsupported signatures skipped: {0}' -f $unsupportedSkippedCount),
    ('Signatures over 24 arguments skipped: {0}' -f $tooManyArgumentsCount),
    ('Alias name conflicts skipped: {0}' -f $aliasConflictCount),
    '',
    'Typed C++ wrapper headers are not inputs to this generator.',
    'Hashes from the 64-bit PC field are not emitted. Only legacy 32-bit Xbox jhash values are used.',
    'Candidates not present in the running Xbox native registration table are not exposed to Lua.'
)
[System.IO.File]::WriteAllText($ReportPath, ($report -join "`r`n") + "`r`n",
    (New-Object System.Text.UTF8Encoding($false)))

Write-Host ("FiveX Lua native catalog: {0} callable globals ({1} official aliases, {2} pointer natives, {3} unsafe pointers skipped) -> {4}" -f
    $catalogLines.Count, $aliasCount, $pointerSafeCount, $pointerSkippedCount, $OutputPath)
