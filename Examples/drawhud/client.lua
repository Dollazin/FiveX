Config = {}

-- Toda a configuracao da HUD fica neste arquivo.
Config.Position = {
    x = 0.0175,
    y = 0.735
}

Config.Size = {
    width = 0.140,
    height = 0.050
}

-- Ative somente para visualizar este componente isoladamente. Resources que
-- usam DrawHud desenham sua propria instancia.
Config.Visible = false

Config.Icon = {
    dictionary = 'commonmenu',
    name = 'shop_garage_icon_a',
    fallback = 'I',
    width = 0.013,
    height = 0.027
}

Config.Text = {
    value = 70,
    font = 4,
    scale = 0.45,
    suffix = '%'
}

Config.Colors = {
    background = { 2, 8, 9, 235 },
    border = { 0, 235, 220, 230 },
    glow = { 0, 255, 235, 35 },
    shadow = { 0, 0, 0, 180 },
    emptyBlock = { 0, 46, 38, 210 },
    filledBlock = { 0, 239, 111, 255 },
    text = { 255, 255, 255, 255 },
    icon = { 255, 255, 255, 255 }
}

CreateThread(function()
    while true do
        if Config.Visible then
            DrawHud(Config.Colors, Config.Size, Config.Position, Config.Text, Config.Icon)
            Wait(0)
        else
            Wait(250)
        end
    end
end)
