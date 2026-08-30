local currentFps = 0
local sampledFrames = 0
local sampleStartedAt = GetGameTimer()

local function drawFps()
    DrawTextHud(
        Config.Colors,
        Config.Position,
        {
            content = ('FPS: %d'):format(currentFps),
            font = 4,
            scale = Config.TextScale
        },
        Config.Layout
    )
end

CreateThread(function()
    while true do
        Wait(0)

        sampledFrames = sampledFrames + 1
        local now = GetGameTimer()
        local elapsed = now - sampleStartedAt

        if elapsed >= Config.UpdateInterval then
            currentFps = math.floor(
                ((sampledFrames * 1000.0) / elapsed) + 0.5
            )
            sampledFrames = 0
            sampleStartedAt = now
        end

        drawFps()
    end
end)
