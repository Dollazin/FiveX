param(
    [string]$InputPath = (Join-Path $PSScriptRoot "..\GameNatives.h"),
    [string]$MetadataPath = (Join-Path $PSScriptRoot "NativeMetadata\natives.json"),
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

function Get-SourceArgumentType([string]$declaration) {
    $declaration = $declaration.Trim()
    return ($declaration -replace '\s+[A-Za-z_]\w*\s*$', '').Trim()
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

if (-not (Test-Path -LiteralPath $InputPath)) { throw "Game native header not found: $InputPath" }
if (-not (Test-Path -LiteralPath $MetadataPath)) { throw "Native metadata not found: $MetadataPath" }

$metadata = Get-Content -LiteralPath $MetadataPath -Raw | ConvertFrom-Json
$metadataByJhash = @{}
foreach ($namespace in $metadata.PSObject.Properties) {
    foreach ($native in $namespace.Value.PSObject.Properties) {
        $definition = $native.Value
        if (-not $definition.jhash) { continue }
        $key = ([string]$definition.jhash).ToUpperInvariant()
        if ($metadataByJhash.ContainsKey($key)) { throw "Duplicate jhash $key in natives.json" }
        $metadataByJhash[$key] = [PSCustomObject]@{
            Namespace = $namespace.Name
            Hash64 = $native.Name
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
$seenSourceNames = @{}
$sourceCount = 0
$matchedCount = 0
$metadataSafeCount = 0
$fallbackSafeCount = 0
$pointerSkippedCount = 0
$pointerSafeCount = 0
$unsupportedSkippedCount = 0
$unmatchedCount = 0
$tooManyArgumentsCount = 0

foreach ($line in Get-Content -LiteralPath $InputPath) {
    if ($line -notmatch '^inline\s+(.+?)\s+([A-Za-z_]\w*)\((.*?)\)\s*\{(.*)\}\s*(?://.*)?$') { continue }

    $sourceCount++
    $sourceReturnType = $Matches[1]
    $sourceName = $Matches[2]
    $sourceArgumentList = $Matches[3]
    $body = $Matches[4]
    if ($seenSourceNames.ContainsKey($sourceName) -or $body -notmatch '0x[0-9A-Fa-f]{8}') { continue }
    $seenSourceNames[$sourceName] = $true
    $hash = $Matches[0].ToUpperInvariant().Replace('X', 'x')
    $metadataEntry = $metadataByJhash[$hash.ToUpperInvariant()]
    $argumentKinds = New-Object System.Collections.Generic.List[string]
    $returnKind = $null
    $modernName = $null
    $valid = $true
    $hasPointer = $false
    $pointerSupported = $true

    if ($metadataEntry) {
        $matchedCount++
        $definition = $metadataEntry.Definition
        $returnKind = Get-LuaReturnKind ([string]$definition.return_type) $true
        if ([string]$definition.return_type -match '\*' -and
            [string]$definition.return_type -notmatch '^(const\s+)?char\s*\*$') { $hasPointer = $true }
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
        $modernName = Convert-ToLuaNativeName ([string]$definition.name)
        if ($hasPointer -and -not $pointerSupported) { $pointerSkippedCount++; continue }
        if ($hasPointer) { $pointerSafeCount++ }
    } else {
        $unmatchedCount++
        $returnKind = Get-LuaReturnKind $sourceReturnType $false
        if ($sourceArgumentList.Trim()) {
            foreach ($argument in $sourceArgumentList.Split(',')) {
                $kind = Get-LuaArgumentKind (Get-SourceArgumentType $argument) $false
                if (-not $kind) { $valid = $false; break }
                $argumentKinds.Add($kind)
            }
        }
    }

    if (-not $valid -or -not $returnKind) { $unsupportedSkippedCount++; continue }
    if ($argumentKinds.Count -gt 24) { $tooManyArgumentsCount++; continue }

    $entry = [PSCustomObject]@{
        Name = $sourceName
        Hash = $hash
        ReturnKind = $returnKind
        ArgumentKinds = $argumentKinds
    }
    $primaryEntries.Add($entry)
    if ($metadataEntry) { $metadataSafeCount++ } else { $fallbackSafeCount++ }
    if ($modernName -and $modernName -ne $sourceName) {
        $aliasCandidates.Add([PSCustomObject]@{
            Name = $modernName
            Hash = $hash
            ReturnKind = $returnKind
            ArgumentKinds = $argumentKinds
        })
    }
}

$catalogLines = New-Object System.Collections.Generic.List[string]
$catalogNames = @{}
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
    '// Xbox hashes come from GameNatives.h; signatures and modern names come from natives.json jhash matches.',
    '// Safe scalar/output pointers are converted to Lua values; arrays and arbitrary pointers remain excluded.',
    ('// Source natives: {0}; metadata matches: {1}; callable entries: {2}; modern aliases: {3}; pointer natives: {4}.' -f
        $sourceCount, $matchedCount, $catalogLines.Count, $aliasCount, $pointerSafeCount),
    ''
)
[System.IO.File]::WriteAllText($OutputPath, (($header + $catalogLines) -join "`r`n") + "`r`n",
    (New-Object System.Text.UTF8Encoding($false)))

$report = @(
    'FiveX Lua native catalog report',
    ('Generated: {0:u}' -f [DateTime]::UtcNow),
    '',
    ('Source natives: {0}' -f $sourceCount),
    ('Matched to natives.json by jhash: {0}' -f $matchedCount),
    ('Unmatched source natives: {0}' -f $unmatchedCount),
    ('Safe matched natives: {0}' -f $metadataSafeCount),
    ('Safe unmatched fallback natives: {0}' -f $fallbackSafeCount),
    ('Modern FiveM-style aliases added: {0}' -f $aliasCount),
    ('Final callable Lua globals: {0}' -f $catalogLines.Count),
    ('Safe pointer natives added: {0}' -f $pointerSafeCount),
    ('Pointer signatures skipped: {0}' -f $pointerSkippedCount),
    ('Unsupported signatures skipped: {0}' -f $unsupportedSkippedCount),
    ('Signatures over 24 arguments skipped: {0}' -f $tooManyArgumentsCount),
    ('Alias name conflicts skipped: {0}' -f $aliasConflictCount),
    '',
    'Hashes from the 64-bit PC field are not emitted. Only 32-bit Xbox hashes already present in GameNatives.h are used.'
)
[System.IO.File]::WriteAllText($ReportPath, ($report -join "`r`n") + "`r`n",
    (New-Object System.Text.UTF8Encoding($false)))

Write-Host ("FiveX Lua native catalog: {0} callable globals ({1} modern aliases, {2} pointer natives, {3} unsafe pointers skipped) -> {4}" -f
    $catalogLines.Count, $aliasCount, $pointerSafeCount, $pointerSkippedCount, $OutputPath)
