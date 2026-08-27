local resourceName = GetCurrentResourceName()

AddEventHandler('onResourceStart', function(startedResource)
    if startedResource == resourceName then
        print(resourceName .. ' started successfully')
    end
end)

AddEventHandler('onResourceStop', function(stoppedResource)
    if stoppedResource == resourceName then
        print(resourceName .. ' stopped')
    end
end)

CreateThread(function()
    while true do
        Wait(1000)
        -- Add your client logic here.
    end
end)
