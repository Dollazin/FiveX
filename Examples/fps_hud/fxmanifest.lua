fx_version 'cerulean'
game 'gta5'

author 'Dolla'
description 'HUD client-side de FPS para FiveX/Xbox 360'
version '1.0.0'

dependency 'drawhud'

client_scripts {
    '@drawhud/functions/draw.lua',
    '@drawhud/functions/textbox.lua',
    'config.lua',
    'client.lua'
}
