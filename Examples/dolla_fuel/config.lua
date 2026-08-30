Config = {}

Config.InteractionKey = 51 -- INPUT_CONTEXT: direcional direito no controle
Config.InteractionLabel = 'D-PAD DIREITA'
Config.PumpSearchDistance = 2.0
Config.VehicleSearchDistance = 4.0
Config.TankInteractionDistance = 2.4
Config.HoseLength = 7.0
Config.HoseMinLength = 1.35
Config.HoseSlack = 0.65
Config.PumpHoseSideOffset = 0.32
Config.RefuelRate = 1.2 -- percentual por segundo
Config.ConsumptionInterval = 1000
Config.ShowStationBlips = true

-- HUD de combustivel. Position usa o canto superior esquerdo; estes valores
-- preservam exatamente a area anterior, que usava X/Y como centro.
Config.Hud = {
    Enabled = true,
    Position = {
        x = 0.222,
        y = 0.893
    },
    Size = {
        width = 0.140,
        height = 0.054
    },
    Icon = {
        dictionary = 'commonmenu',
        name = 'shop_garage_icon_a',
        fallback = 'I',
        width = 0.013,
        height = 0.027
    },
    Text = {
        value = 0,
        font = 4,
        scale = 0.45,
        suffix = '%'
    },
    Colors = {
        background = { 2, 8, 9, 235 },
        border = { 0, 235, 220, 230 },
        glow = { 0, 255, 235, 35 },
        shadow = { 0, 0, 0, 180 },
        emptyBlock = { 0, 46, 38, 210 },
        filledBlock = { 0, 239, 111, 255 },
        text = { 255, 255, 255, 255 },
        icon = { 255, 255, 255, 255 }
    }
}

Config.PumpModels = {
    GetHashKey('prop_gas_pump_1a'),
    GetHashKey('prop_gas_pump_1b'),
    GetHashKey('prop_gas_pump_1c'),
    GetHashKey('prop_gas_pump_1d'),
    GetHashKey('prop_gas_pump_old2'),
    GetHashKey('prop_gas_pump_old3'),
    GetHashKey('prop_vintage_pump')
}

Config.FuelBones = {
    'petrolcap',
    'petroltank_l',
    'petroltank_r',
    'hub_lr',
    'hub_rr',
    'handle_dside_r',
    'handle_pside_r'
}

-- Alguns carros nao possuem petrolcap e usam a roda traseira como referencia.
-- O deslocamento posiciona o bico acima da roda, na altura da tampa do tanque.
Config.FuelBoneOffsets = {
    hub_lr = vector3(0.0, 0.0, 0.36),
    hub_rr = vector3(0.0, 0.0, 0.36)
}

-- Consumo-base por classe. O valor e multiplicado pelo RPM a cada ciclo.
Config.ClassConsumption = {
    [0] = 0.055, -- compactos
    [1] = 0.060, -- sedans
    [2] = 0.075, -- SUVs
    [3] = 0.060, -- coupes
    [4] = 0.085, -- muscle
    [5] = 0.070, -- classicos esportivos
    [6] = 0.075, -- esportivos
    [7] = 0.095, -- super
    [8] = 0.040, -- motos
    [9] = 0.085, -- off-road
    [10] = 0.100, -- industrial
    [11] = 0.090, -- utilitarios
    [12] = 0.080, -- vans
    [13] = 0.000, -- bicicletas
    [14] = 0.080, -- barcos
    [15] = 0.180, -- helicopteros
    [16] = 0.220, -- avioes
    [17] = 0.070, -- servico
    [18] = 0.080, -- emergencia
    [19] = 0.110, -- militar
    [20] = 0.100, -- comercial
    [21] = 0.000  -- trens
}

Config.ElectricVehicles = {
    GetHashKey('airtug'), 
    GetHashKey('caddy'), 
    GetHashKey('caddy2'),
    GetHashKey('caddy3'), 
    GetHashKey('dilettante'),
    GetHashKey('khamelion'),
    GetHashKey('surge'), 
    GetHashKey('voltic'),
}

Config.StationBlips = {
    vector3(49.4187, 2778.793, 58.043),
    vector3(263.894, 2606.463, 44.983),
    vector3(1039.958, 2671.134, 39.550),
    vector3(1207.260, 2660.175, 37.899),
    vector3(2539.685, 2594.192, 37.944),
    vector3(2679.858, 3263.946, 55.240),
    vector3(2005.055, 3773.887, 32.403),
    vector3(1687.156, 4929.392, 42.078),
    vector3(1701.314, 6416.028, 32.763),
    vector3(179.857, 6602.839, 31.868),
    vector3(-94.4619, 6419.594, 31.489),
    vector3(-2554.996, 2334.400, 33.078),
    vector3(-1800.375, 803.661, 138.651),
    vector3(-1437.622, -276.747, 46.207),
    vector3(-2096.243, -320.286, 13.168),
    vector3(-724.619, -935.163, 19.213),
    vector3(-526.019, -1211.003, 18.184),
    vector3(-70.2148, -1761.792, 29.534),
    vector3(265.648, -1261.309, 29.292),
    vector3(819.653, -1028.846, 26.403),
    vector3(1208.951, -1402.567, 35.224),
    vector3(1181.381, -330.847, 69.316),
    vector3(620.843, 269.100, 103.089),
    vector3(2581.321, 362.039, 108.468),
    vector3(176.631, -1562.025, 29.263),
    vector3(-319.292, -1471.715, 30.549),
    vector3(1784.324, 3330.550, 41.253)
}
