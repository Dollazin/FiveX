local pumpHashes = {}
local electricHashes = {}
local vehicleFuel = {}
local stationBlips = {}
local lastPlayerVehicle = 0

local fuelSession = {
    mode = 'idle', -- idle, holding ou connected
    pump = 0,
    pumpCoords = nil,
    ropeAnchor = nil,
    nozzle = 0,
    rope = 0,
    vehicle = 0,
    tankBone = -1,
    tankCoords = nil,
    full = false
}

local function loadModel(model)
    if HasModelLoaded(model) then
        return true
    end

    RequestModel(model)
    local timeout = GetGameTimer() + 5000
    while not HasModelLoaded(model) and GetGameTimer() < timeout do
        Wait(0)
    end

    return HasModelLoaded(model)
end

local function loadAnimDict(dict)
    if HasAnimDictLoaded(dict) then
        return true
    end

    RequestAnimDict(dict)
    local timeout = GetGameTimer() + 5000
    while not HasAnimDictLoaded(dict) and GetGameTimer() < timeout do
        Wait(0)
    end

    return HasAnimDictLoaded(dict)
end

local function drawText3D(coords, text)
    local visible, screenX, screenY = World3dToScreen2d(coords.x, coords.y, coords.z)
    if not visible then
        return
    end

    SetTextScale(0.45, 0.45)
    SetTextFont(4)
    SetTextProportional(true)
    SetTextCentre(true)
    SetTextColour(255, 255, 255, 235)
    SetTextOutline()
    BeginTextCommandDisplayText('STRING')
    AddTextComponentSubstringPlayerName(text)
    EndTextCommandDisplayText(screenX, screenY, 0)
end

local function notify(message)
    BeginTextCommandThefeedPost('STRING')
    AddTextComponentSubstringPlayerName(message)
    EndTextCommandThefeedPostTicker(false, false)
end

local function drawFuelHud(fuel)
    local hud = Config.Hud
    local percentage = math.max(0.0, math.min(100.0, fuel))
    local barWidth = hud.Width - 0.012
    local barHeight = 0.007
    local barY = hud.Y + hud.BarOffsetY
    local filledWidth = barWidth * (percentage / 100.0)
    local filledX = (hud.X - (barWidth / 2.0)) + (filledWidth / 2.0)

    local red, green, blue = 46, 204, 113
    if percentage <= 15.0 then
        red, green, blue = 231, 76, 60
    elseif percentage <= 35.0 then
        red, green, blue = 241, 196, 15
    end

    DrawRect(hud.X, hud.Y, hud.Width, hud.Height, 8, 12, 16, 205, false)
    DrawRect(hud.X, barY, barWidth, barHeight, 35, 40, 45, 230, false)
    if filledWidth > 0.0 then
        DrawRect(filledX, barY, filledWidth, barHeight, red, green, blue, 245, false)
    end

    SetTextScale(hud.TextScale, hud.TextScale)
    SetTextFont(4)
    SetTextProportional(true)
    SetTextCentre(true)
    SetTextColour(255, 255, 255, 245)
    SetTextOutline()
    BeginTextCommandDisplayText('STRING')
    AddTextComponentSubstringPlayerName(
        ('COMBUSTIVEL  %d%%'):format(math.floor(percentage + 0.5))
    )
    EndTextCommandDisplayText(hud.X, hud.Y + hud.TextOffsetY, 0)
end

local function playInteractionAnimation(ped)
    local dict = 'anim@am_hold_up@male'
    if not loadAnimDict(dict) then
        return
    end

    TaskPlayAnim(ped, dict, 'shoplift_high', 2.0, 2.0, 650, 48, 0.0, false, false, false)
    Wait(350)
end

local function isElectricVehicle(vehicle)
    return electricHashes[GetEntityModel(vehicle)] == true
end

local function canUseFuel(vehicle)
    if vehicle == 0 or not DoesEntityExist(vehicle) then
        return false
    end

    local class = GetVehicleClass(vehicle)
    return class ~= 13 and not isElectricVehicle(vehicle)
end

local function getFuel(vehicle)
    if vehicle == 0 or not DoesEntityExist(vehicle) then
        return 0.0
    end

    local model = GetEntityModel(vehicle)
    local entry = vehicleFuel[vehicle]
    if entry == nil or entry.model ~= model then
        entry = {
            model = model,
            amount = math.random(450, 850) / 10.0
        }
        vehicleFuel[vehicle] = entry
    end

    return math.max(0.0, math.min(100.0, entry.amount))
end

local function setFuel(vehicle, amount)
    if vehicle == 0 or not DoesEntityExist(vehicle) then
        return
    end

    local entry = vehicleFuel[vehicle]
    if entry == nil or entry.model ~= GetEntityModel(vehicle) then
        entry = { model = GetEntityModel(vehicle), amount = 0.0 }
        vehicleFuel[vehicle] = entry
    end
    entry.amount = math.max(0.0, math.min(100.0, amount)) + 0.0
end

local function findNearestPump(coords)
    local closestPump = 0
    local closestDistance = Config.PumpSearchDistance + 0.01

    for _, model in ipairs(Config.PumpModels) do
        local object = GetClosestObjectOfType(
            coords.x, coords.y, coords.z,
            Config.PumpSearchDistance, model,
            false, false, false
        )
        if object ~= 0 and DoesEntityExist(object) then
            local objectCoords = GetEntityCoords(object, true)
            local distance = #(coords - objectCoords)
            if distance < closestDistance then
                closestPump = object
                closestDistance = distance
            end
        end
    end

    if closestPump ~= 0 then
        return closestPump, GetEntityCoords(closestPump, true)
    end

    return 0, nil
end

local function findNearestVehicle(coords, maxDistance)
    -- No Xbox 360, GetClosestVehicle pode ignorar alguns veiculos parados.
    -- O ultimo veiculo usado e a referencia mais confiavel depois que o
    -- jogador desce do carro para abastecer.
    local ped = PlayerPedId()
    if lastPlayerVehicle ~= 0 and canUseFuel(lastPlayerVehicle) then
        local trackedCoords = GetEntityCoords(lastPlayerVehicle, true)
        if #(coords - trackedCoords) <= maxDistance then
            return lastPlayerVehicle
        end
    end

    local lastVehicle = GetVehiclePedIsIn(ped, true)
    if lastVehicle ~= 0 and canUseFuel(lastVehicle) then
        local lastCoords = GetEntityCoords(lastVehicle, true)
        if #(coords - lastCoords) <= maxDistance then
            return lastVehicle
        end
    end

    -- Flags alternativos cobrem carros estacionados, de trafego e de missao.
    local searchFlags = { 70, 71, 127, 0 }
    for _, flags in ipairs(searchFlags) do
        local vehicle = GetClosestVehicle(
            coords.x, coords.y, coords.z,
            maxDistance, 0, flags
        )
        if vehicle ~= 0 and canUseFuel(vehicle) then
            return vehicle
        end
    end

    return 0
end

local function isStationPosition(coords)
    for _, station in ipairs(Config.StationBlips) do
        local dx = coords.x - station.x
        local dy = coords.y - station.y
        if ((dx * dx) + (dy * dy)) <= 9.0 then
            return true
        end
    end

    return false
end

local function removeTrackedBlips()
    for index = #stationBlips, 1, -1 do
        local blip = stationBlips[index]
        if blip ~= 0 and DoesBlipExist(blip) then
            RemoveBlip(blip)
        end
        stationBlips[index] = nil
    end
end

local function removeStaleStationBlips()
    -- Remove handles deixados por versoes anteriores, antes de criar os novos.
    local blip = GetFirstBlipInfoId(361)
    local inspected = 0
    while blip ~= 0 and DoesBlipExist(blip) and inspected < 128 do
        local nextBlip = GetNextBlipInfoId(361)
        local coords = GetBlipInfoIdCoord(blip)
        if isStationPosition(coords) then
            RemoveBlip(blip)
        end
        blip = nextBlip
        inspected = inspected + 1
    end
end


local function getFuelPort(vehicle)
    local pedCoords = GetEntityCoords(PlayerPedId(), true)
    local bestBone = -1
    local bestCoords = nil
    local bestBoneName = nil
    local bestDistance = 9999.0

    -- Usa apenas bones laterais reais. O bone petroltank generico costuma
    -- ficar no centro/embaixo do carro na versao Xbox e nao representa a tampa.
    for _, boneName in ipairs(Config.FuelBones) do
        local bone = GetEntityBoneIndexByName(vehicle, boneName)
        if bone ~= -1 then
            local boneCoords = GetWorldPositionOfEntityBone(vehicle, bone)
            local offset = Config.FuelBoneOffsets[boneName]
            if offset then
                local localBoneCoords = GetOffsetFromEntityGivenWorldCoords(
                    vehicle, boneCoords.x, boneCoords.y, boneCoords.z
                )
                boneCoords = GetOffsetFromEntityInWorldCoords(
                    vehicle,
                    localBoneCoords.x + offset.x,
                    localBoneCoords.y + offset.y,
                    localBoneCoords.z + offset.z
                )
            end

            local distance = #(pedCoords - boneCoords)
            if distance < bestDistance then
                bestBone = bone
                bestCoords = boneCoords
                bestBoneName = boneName
                bestDistance = distance
            end
        end
    end

    if bestCoords then
        return bestBone, bestCoords, bestBoneName
    end

    -- Modelos do Xbox sem bones laterais recebem dois pontos candidatos na
    -- traseira. O lado mais perto do jogador vira o bocal de combustivel.
    local minDim, maxDim = GetModelDimensions(GetEntityModel(vehicle))
    local rearY = minDim.y + ((maxDim.y - minDim.y) * 0.20)
    local heightZ = minDim.z + ((maxDim.z - minDim.z) * 0.68)
    local leftFallback = GetOffsetFromEntityInWorldCoords(
        vehicle,
        minDim.x - 0.05,
        rearY,
        heightZ
    )
    local rightFallback = GetOffsetFromEntityInWorldCoords(
        vehicle,
        maxDim.x + 0.05,
        rearY,
        heightZ
    )

    local fallback = leftFallback
    if #(pedCoords - rightFallback) < #(pedCoords - leftFallback) then
        fallback = rightFallback
    end

    return 0, fallback, 'fallback'
end

local function attachNozzleToHand()
    local ped = PlayerPedId()
    DetachEntity(fuelSession.nozzle, true, true)
    AttachEntityToEntity(
        fuelSession.nozzle,
        ped,
        GetPedBoneIndex(ped, 0x49D9),
        0.11, 0.02, 0.02,
        -80.0, -90.0, 15.0,
        true, true, false, true, 1, true, 0
    )
    fuelSession.mode = 'holding'
    fuelSession.vehicle = 0
    fuelSession.tankBone = -1
    fuelSession.tankCoords = nil
    fuelSession.full = false
end

local function getNozzleRopePoint()
    if fuelSession.nozzle == 0 or not DoesEntityExist(fuelSession.nozzle) then
        return nil
    end

    return GetOffsetFromEntityInWorldCoords(fuelSession.nozzle, 0.0, -0.033, -0.195)
end

local function updateHoseLength()
    if fuelSession.rope == 0 or not fuelSession.ropeAnchor then
        return
    end

    local nozzlePoint = getNozzleRopePoint()
    if not nozzlePoint then
        return
    end

    -- Mantem uma pequena barriga na mangueira sem deixa-la totalmente solta
    -- ou esticada como um elastico entre a bomba e o bico.
    local requiredLength = #(fuelSession.ropeAnchor - nozzlePoint) + Config.HoseSlack
    local ropeLength = math.max(Config.HoseMinLength, math.min(Config.HoseLength, requiredLength))
    RopeForceLength(fuelSession.rope, ropeLength)
end

local function cleanupFuelSession(showMessage)
    local ped = PlayerPedId()
    ClearPedSecondaryTask(ped)

    if fuelSession.rope ~= 0 then
        DeleteRope(fuelSession.rope)
        fuelSession.rope = 0
    end

    if fuelSession.nozzle ~= 0 and DoesEntityExist(fuelSession.nozzle) then
        DetachEntity(fuelSession.nozzle, true, true)
        DeleteEntity(fuelSession.nozzle)
    end

    RopeUnloadTextures()

    fuelSession.mode = 'idle'
    fuelSession.pump = 0
    fuelSession.pumpCoords = nil
    fuelSession.ropeAnchor = nil
    fuelSession.nozzle = 0
    fuelSession.vehicle = 0
    fuelSession.tankBone = -1
    fuelSession.tankCoords = nil
    fuelSession.full = false

    if showMessage then
        notify('Mangueira devolvida.')
    end
end

local function takeNozzle(pump, pumpCoords)
    local ped = PlayerPedId()
    local nozzleModel = GetHashKey('prop_cs_fuel_nozle')
    if not loadModel(nozzleModel) then
        notify('Nao foi possivel carregar o bico de combustivel.')
        return
    end

    playInteractionAnimation(ped)

    local nozzle = CreateObject(nozzleModel, pumpCoords.x, pumpCoords.y, pumpCoords.z + 1.0, false, false, false)
    if nozzle == 0 then
        notify('Nao foi possivel criar o bico de combustivel.')
        return
    end

    fuelSession.pump = pump
    fuelSession.pumpCoords = pumpCoords
    fuelSession.nozzle = nozzle

    attachNozzleToHand()
    SetModelAsNoLongerNeeded(nozzleModel)

    RopeLoadTextures()
    local timeout = GetGameTimer() + 3000
    while not RopeAreTexturesLoaded() and GetGameTimer() < timeout do
        Wait(0)
    end

    -- Seleciona automaticamente o lado da bomba voltado para o jogador. Isso
    -- evita que a mangueira atravesse o corpo da bomba em modelos rotacionados.
    local playerCoords = GetEntityCoords(ped, true)
    local leftAnchor = GetOffsetFromEntityInWorldCoords(pump, -Config.PumpHoseSideOffset, 0.0, 1.20)
    local rightAnchor = GetOffsetFromEntityInWorldCoords(pump, Config.PumpHoseSideOffset, 0.0, 1.20)
    local ropeStart = leftAnchor
    if #(playerCoords - rightAnchor) < #(playerCoords - leftAnchor) then
        ropeStart = rightAnchor
    end
    fuelSession.ropeAnchor = ropeStart

    local nozzleEnd = GetOffsetFromEntityInWorldCoords(nozzle, 0.0, -0.033, -0.195)
    local initialLength = math.max(
        Config.HoseMinLength,
        math.min(Config.HoseLength, #(ropeStart - nozzleEnd) + Config.HoseSlack)
    )
    local rope = AddRope(
        ropeStart.x, ropeStart.y, ropeStart.z,
        0.0, 0.0, 0.0,
        initialLength, 4, Config.HoseLength, 0.5, 0.5,
        false, false, false, 1.0, false
    )

    if rope ~= 0 then
        fuelSession.rope = rope
        ActivatePhysics(rope)
        AttachEntitiesToRope(
            rope, pump, nozzle,
            ropeStart.x, ropeStart.y, ropeStart.z,
            nozzleEnd.x, nozzleEnd.y, nozzleEnd.z,
            initialLength, false, false
        )
        RopeForceLength(rope, initialLength)
    else
        cleanupFuelSession(false)
        notify('Nao foi possivel criar a mangueira.')
        return
    end

    notify('Leve o bico ate o tanque do veiculo.')
end

local function connectNozzle(vehicle, bone, tankCoords, boneName)
    local ped = PlayerPedId()
    playInteractionAnimation(ped)
    DetachEntity(fuelSession.nozzle, true, true)

    local class = GetVehicleClass(vehicle)
    if bone == 0 then
        local localCoords = GetOffsetFromEntityGivenWorldCoords(vehicle, tankCoords.x, tankCoords.y, tankCoords.z)
        AttachEntityToEntity(
            fuelSession.nozzle, vehicle, 0,
            localCoords.x, localCoords.y, localCoords.z,
            -105.0, -90.0, -90.0,
            true, true, false, false, 1, true, 0
        )
    elseif class == 8 then
        AttachEntityToEntity(
            fuelSession.nozzle, vehicle, bone,
            0.0, -0.12, 0.10,
            -80.0, 0.0, 0.0,
            true, true, false, false, 1, true, 0
        )
    else
        local boneOffset = Config.FuelBoneOffsets[boneName] or vector3(0.0, 0.0, 0.0)
        AttachEntityToEntity(
            fuelSession.nozzle, vehicle, bone,
            -0.12 + boneOffset.x, boneOffset.y, 0.05 + boneOffset.z,
            -105.0, -90.0, -90.0,
            true, true, false, false, 1, true, 0
        )
    end

    fuelSession.mode = 'connected'
    fuelSession.vehicle = vehicle
    fuelSession.tankBone = bone
    fuelSession.tankCoords = tankCoords
    fuelSession.full = getFuel(vehicle) >= 99.95

    if fuelSession.full then
        notify('O tanque ja esta cheio. Retire o bico.')
    else
        notify('Abastecimento iniciado.')
    end
end

local function disconnectNozzle()
    local ped = PlayerPedId()
    playInteractionAnimation(ped)
    attachNozzleToHand()
    notify('Devolva a mangueira na mesma bomba.')
end

local function returnNozzle()
    playInteractionAnimation(PlayerPedId())
    cleanupFuelSession(true)
end

CreateThread(function()
    for _, model in ipairs(Config.PumpModels) do
        pumpHashes[model] = true
    end

    for _, model in ipairs(Config.ElectricVehicles) do
        electricHashes[model] = true
    end
end)

CreateThread(function()
    while true do
        local waitTime = 500
        local ped = PlayerPedId()
        local pedCoords = GetEntityCoords(ped, true)
        local currentVehicle = GetVehiclePedIsIn(ped, false)
        if currentVehicle ~= 0 and canUseFuel(currentVehicle) then
            lastPlayerVehicle = currentVehicle
        end

        if fuelSession.mode == 'idle' then
            local pump, pumpCoords = findNearestPump(pedCoords)
            if pump ~= 0 then
                waitTime = 0
                drawText3D(
                    pumpCoords + vector3(0.0, 0.0, 1.25),
                    ('~g~[%s]~s~ Pegar mangueira'):format(Config.InteractionLabel)
                )
                if IsControlJustPressed(0, Config.InteractionKey) then
                    takeNozzle(pump, pumpCoords)
                end
            end
        else
            waitTime = 0

            if fuelSession.pump == 0 or not DoesEntityExist(fuelSession.pump) or
                fuelSession.nozzle == 0 or not DoesEntityExist(fuelSession.nozzle) then
                cleanupFuelSession(false)
                notify('Abastecimento cancelado: bomba ou mangueira indisponivel.')
            else
                local currentPumpCoords = GetEntityCoords(fuelSession.pump, true)
                fuelSession.pumpCoords = currentPumpCoords
                local distanceFromPump = #(pedCoords - currentPumpCoords)

                updateHoseLength()

                if distanceFromPump > Config.HoseLength + 1.0 then
                    cleanupFuelSession(false)
                    notify('A mangueira foi esticada alem do limite.')
                elseif fuelSession.mode == 'holding' then
                    local vehicle = findNearestVehicle(pedCoords, Config.VehicleSearchDistance)
                    local nearTank = false

                    if vehicle ~= 0 then
                        local bone, tankCoords, boneName = getFuelPort(vehicle)
                        local tankDistance = #(pedCoords - tankCoords)
                        if tankDistance <= Config.VehicleSearchDistance then
                            nearTank = true
                            local fuel = getFuel(vehicle)
                            if tankDistance <= Config.TankInteractionDistance then
                                drawText3D(
                                    tankCoords + vector3(0.0, 0.0, 0.22),
                                    ('~g~[%s]~s~ Colocar mangueira  ~b~%d%%'):format(
                                        Config.InteractionLabel, math.floor(fuel + 0.5)
                                    )
                                )
                            else
                                drawText3D(
                                    tankCoords + vector3(0.0, 0.0, 0.22),
                                    '~y~Aproxime-se da tampa do tanque'
                                )
                            end
                            if tankDistance <= Config.TankInteractionDistance and
                                IsControlJustPressed(0, Config.InteractionKey) then
                                connectNozzle(vehicle, bone, tankCoords, boneName)
                            end
                        end
                    end

                    if not nearTank and distanceFromPump <= Config.PumpSearchDistance then
                        drawText3D(
                            currentPumpCoords + vector3(0.0, 0.0, 1.25),
                            ('~g~[%s]~s~ Devolver mangueira'):format(Config.InteractionLabel)
                        )
                        if IsControlJustPressed(0, Config.InteractionKey) then
                            returnNozzle()
                        end
                    end
                elseif fuelSession.mode == 'connected' then
                    local vehicle = fuelSession.vehicle
                    if vehicle == 0 or not DoesEntityExist(vehicle) then
                        attachNozzleToHand()
                        notify('O veiculo nao esta mais disponivel.')
                    else
                        local _, tankCoords = getFuelPort(vehicle)
                        fuelSession.tankCoords = tankCoords
                        local fuel = getFuel(vehicle)
                        local label
                        if fuel >= 99.95 then
                            label = ('~g~Tanque cheio~s~  [%s] Retirar mangueira'):format(
                                Config.InteractionLabel
                            )
                        else
                            label = ('~b~Abastecendo: %d%%~s~  [%s] Retirar'):format(
                                math.floor(fuel + 0.5), Config.InteractionLabel
                            )
                        end
                        drawText3D(tankCoords + vector3(0.0, 0.0, 0.22), label)

                        if #(pedCoords - tankCoords) <= Config.TankInteractionDistance and
                            IsControlJustPressed(0, Config.InteractionKey) then
                            disconnectNozzle()
                        end
                    end
                end
            end
        end

        Wait(waitTime)
    end
end)

CreateThread(function()
    local stepMs = 250
    while true do
        Wait(stepMs)

        if fuelSession.mode == 'connected' then
            local vehicle = fuelSession.vehicle
            if vehicle ~= 0 and DoesEntityExist(vehicle) and not fuelSession.full then
                local fuel = getFuel(vehicle)
                local amount = Config.RefuelRate * (stepMs / 1000.0)
                local nextFuel = math.min(100.0, fuel + amount)
                setFuel(vehicle, nextFuel)

                if nextFuel >= 99.95 then
                    fuelSession.full = true
                    SetVehicleEngineOn(vehicle, false, true)
                    notify('Tanque cheio. Pegue a mangueira e devolva na bomba.')
                end
            end
        end
    end
end)

CreateThread(function()
    while true do
        Wait(Config.ConsumptionInterval)

        local ped = PlayerPedId()
        local vehicle = GetVehiclePedIsIn(ped, false)
        if vehicle ~= 0 and canUseFuel(vehicle) then
            lastPlayerVehicle = vehicle
        end
        if vehicle ~= 0 and GetPedInVehicleSeat(vehicle, -1, false) == ped and canUseFuel(vehicle) then
            local fuel = getFuel(vehicle)
            if GetIsVehicleEngineRunning(vehicle) then
                local class = GetVehicleClass(vehicle)
                local baseConsumption = Config.ClassConsumption[class] or 0.07
                local speedFactor = math.min(GetEntitySpeed(vehicle) / 45.0, 1.0)
                local throttleFactor = IsControlPressed(0, 71) and 0.55 or 0.0
                local engineLoad = math.min(1.25, 0.20 + speedFactor + throttleFactor)
                local nextFuel = math.max(0.0, fuel - (baseConsumption * engineLoad))
                setFuel(vehicle, nextFuel)

                if nextFuel <= 0.05 then
                    SetVehicleEngineOn(vehicle, false, true)
                    SetVehicleUndriveable(vehicle, true)
                else
                    SetVehicleUndriveable(vehicle, false)
                end
            elseif fuel > 0.05 and not IsEntityDead(vehicle, false) then
                SetVehicleUndriveable(vehicle, false)
            end
        end
    end
end)

CreateThread(function()
    while true do
        local waitTime = 250

        if Config.Hud.Enabled then
            local ped = PlayerPedId()
            local vehicle = GetVehiclePedIsIn(ped, false)
            if vehicle ~= 0 and canUseFuel(vehicle) then
                waitTime = 0
                drawFuelHud(getFuel(vehicle))
            end
        end

        Wait(waitTime)
    end
end)

CreateThread(function()
    if not Config.ShowStationBlips then
        return
    end

    removeStaleStationBlips()

    for _, coords in ipairs(Config.StationBlips) do
        local blip = AddBlipForCoord(coords.x, coords.y, coords.z)
        SetBlipSprite(blip, 361)
        SetBlipScale(blip, 0.72)
        SetBlipColour(blip, 4)
        SetBlipDisplay(blip, 4)
        SetBlipAsShortRange(blip, true)
        BeginTextCommandSetBlipName('STRING')
        AddTextComponentString('Posto de combustivel')
        EndTextCommandSetBlipName(blip)
        stationBlips[#stationBlips + 1] = blip
    end
end)

AddEventHandler('onResourceStop', function(resourceName)
    if resourceName == GetCurrentResourceName() then
        cleanupFuelSession(false)
        removeTrackedBlips()

        for vehicle in pairs(vehicleFuel) do
            if vehicle ~= 0 and DoesEntityExist(vehicle) then
                SetVehicleUndriveable(vehicle, false)
            end
        end
        vehicleFuel = {}
        lastPlayerVehicle = 0

        if HasAnimDictLoaded('anim@am_hold_up@male') then
            RemoveAnimDict('anim@am_hold_up@male')
        end
    end
end)
