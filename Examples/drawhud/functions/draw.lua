HudDraw = HudDraw or {}

local loadedDictionaries = {}
local screenAspect

local function color(values)
    return values[1], values[2], values[3], values[4]
end

function HudDraw.RectFromTopLeft(x, y, width, height, values)
    local red, green, blue, alpha = color(values)

    DrawRect(
        x + (width * 0.5),
        y + (height * 0.5),
        width,
        height,
        red,
        green,
        blue,
        alpha
    )
end

local function getScreenAspect()
    if screenAspect then
        return screenAspect
    end

    if type(GetScreenResolution) == 'function' then
        local screenWidth, screenHeight = GetScreenResolution()
        if tonumber(screenWidth) and tonumber(screenHeight) and screenHeight > 0 then
            screenAspect = screenWidth / screenHeight
        end
    end

    screenAspect = screenAspect or (16.0 / 9.0)
    return screenAspect
end

function HudDraw.BorderFromTopLeft(x, y, width, height, thicknessY, values)
    local thicknessX = thicknessY / getScreenAspect()

    HudDraw.RectFromTopLeft(x, y, width, thicknessY, values)
    HudDraw.RectFromTopLeft(x, y + height - thicknessY, width, thicknessY, values)
    HudDraw.RectFromTopLeft(x, y + thicknessY, thicknessX, height - (thicknessY * 2.0), values)
    HudDraw.RectFromTopLeft(
        x + width - thicknessX,
        y + thicknessY,
        thicknessX,
        height - (thicknessY * 2.0),
        values
    )
end

function HudDraw.CenteredText(content, x, y, text, values)
    SetTextFont(text.font or 4)
    SetTextScale(0.0, text.scale or 0.45)
    SetTextColour(color(values))
    SetTextCentre(true)
    SetTextOutline()
    SetTextDropShadow()
    BeginTextCommandDisplayText('STRING')
    AddTextComponentSubstringPlayerName(tostring(content))
    EndTextCommandDisplayText(x, y)
end

function HudDraw.TextWidth(content, text)
    SetTextFont(text.font or 4)
    SetTextScale(0.0, text.scale or 0.45)
    SetTextProportional(true)
    BeginTextCommandGetWidth('STRING')
    AddTextComponentSubstringPlayerName(tostring(content))
    return EndTextCommandGetWidth(true)
end

function HudDraw.LeftText(content, x, y, text, values)
    SetTextFont(text.font or 4)
    SetTextScale(0.0, text.scale or 0.45)
    SetTextProportional(true)
    SetTextCentre(false)
    SetTextColour(color(values))
    SetTextOutline()
    SetTextDropShadow()
    BeginTextCommandDisplayText('STRING')
    AddTextComponentSubstringPlayerName(tostring(content))
    EndTextCommandDisplayText(x, y)
end

local function requestIcon(icon)
    if loadedDictionaries[icon.dictionary] then
        return true
    end

    RequestStreamedTextureDict(icon.dictionary, false)
    loadedDictionaries[icon.dictionary] = HasStreamedTextureDictLoaded(icon.dictionary)
    return loadedDictionaries[icon.dictionary]
end

function HudDraw.Icon(centerX, centerY, icon, text, iconColor)
    if requestIcon(icon) then
        local red, green, blue, alpha = color(iconColor)

        DrawSprite(
            icon.dictionary,
            icon.name,
            centerX,
            centerY,
            icon.width or 0.013,
            icon.height or 0.027,
            icon.rotation or 0.0,
            red,
            green,
            blue,
            alpha
        )
        return
    end

    HudDraw.CenteredText(icon.fallback or 'I', centerX, centerY - 0.014, text, iconColor)
end
