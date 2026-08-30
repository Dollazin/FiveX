local SEGMENT_COUNT = 10

-- DrawHud(cores, tamanho, posicao, texto, icone)
-- texto.value aceita um numero de 0 a 100 e preenche os 10 blocos fixos.
function DrawHud(colors, size, position, text, icon)
    local x = position.x
    local y = position.y
    local width = size.width
    local height = size.height

    local paddingX = width * 0.035714
    local borderY = height * 0.040000
    local iconSpace = width * 0.107143
    local gap = width * 0.035714
    local textSpace = width * 0.178571
    local blockGap = width * 0.007143
    local blockHeight = height * 0.600000
    local shadowX = width * 0.010714
    local shadowY = height * 0.040000
    local glowX = width * 0.010714
    local glowY = height * 0.040000

    HudDraw.RectFromTopLeft(x + shadowX, y + shadowY, width, height, colors.shadow)
    HudDraw.BorderFromTopLeft(
        x - glowX,
        y - glowY,
        width + (glowX * 2.0),
        height + (glowY * 2.0),
        borderY * 2.0,
        colors.glow
    )
    HudDraw.RectFromTopLeft(x, y, width, height, colors.background)
    HudDraw.BorderFromTopLeft(x, y, width, height, borderY, colors.border)

    local centerY = y + (height * 0.5)
    local contentX = x + paddingX
    local iconCenterX = contentX + (iconSpace * 0.5)
    HudDraw.Icon(iconCenterX, centerY, icon, text, colors.icon)

    local barX = contentX + iconSpace + gap
    local barWidth = width
        - (paddingX * 2.0)
        - iconSpace
        - textSpace
        - (gap * 2.0)
    local barY = centerY - (blockHeight * 0.5)
    local totalGaps = blockGap * (SEGMENT_COUNT - 1)
    local blockWidth = (barWidth - totalGaps) / SEGMENT_COUNT
    local numericValue = tonumber(text.value)
    local normalizedValue = numericValue and math.max(0, math.min(100, numericValue)) or 100
    local activeBlocks = math.ceil((normalizedValue / 100.0) * SEGMENT_COUNT)

    for index = 1, SEGMENT_COUNT do
        local blockX = barX + ((index - 1) * (blockWidth + blockGap))
        local blockColor = index <= activeBlocks and colors.filledBlock or colors.emptyBlock
        HudDraw.RectFromTopLeft(blockX, barY, blockWidth, blockHeight, blockColor)
    end

    local textCenterX = x + width - paddingX - (textSpace * 0.5)
    local textY = centerY - (height * 0.290000)
    local content = text.content

    if content == nil then
        if numericValue then
            content = ('%d%s'):format(math.floor(numericValue + 0.5), text.suffix or '')
        else
            content = tostring(text.value or '') .. (text.suffix or '')
        end
    end

    HudDraw.CenteredText(content, textCenterX, textY, text, colors.text)
end

exports('DrawHud', DrawHud)
