-- DrawTextHud(cores, posicao, texto, layout)
-- A largura do fundo acompanha automaticamente a largura real do texto.
function DrawTextHud(colors, position, text, layout)
    layout = layout or {}

    local content = tostring(text.content or '')
    local paddingX = layout.paddingX or 0.006
    local height = layout.height or 0.036
    local borderThickness = layout.borderThickness or 0.002
    local textOffsetY = layout.textOffsetY or 0.002
    local width = HudDraw.TextWidth(content, text) + (paddingX * 2.0)

    if layout.minWidth and width < layout.minWidth then
        width = layout.minWidth
    end

    if layout.maxWidth and width > layout.maxWidth then
        width = layout.maxWidth
    end

    HudDraw.RectFromTopLeft(
        position.x,
        position.y,
        width,
        height,
        colors.background
    )
    HudDraw.BorderFromTopLeft(
        position.x,
        position.y,
        width,
        height,
        borderThickness,
        colors.border
    )
    HudDraw.LeftText(
        content,
        position.x + paddingX,
        position.y + textOffsetY,
        text,
        colors.text
    )

    return width, height
end

exports('DrawTextHud', DrawTextHud)
