# I2Hook
A plugin for Injustice 2

# Installation

####  I2Hook only works with latest Steam version!

You can download binary files from [Releases](https://github.com/ermaccer/I2Hook/) page. Extract **i2hook.zip**
to Binaries\Retail folder of Injustice 2.

If you are not sure how to find your Injustice folder, search for it in your Steam library then right click on the entry and select Manage->Browse local files.

Archive breakdown:

 - dinput8.dll - [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/)
 - I2.asi 
 - I2.ini - configuration file

# Usage

If installed correctly, a notification will appear informing that the plugin was installed
and is ready to use. By default **F1** will open or close in-game menu.

![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/notif.jpg)


## Features
| Feature | Description |
| --- | --- |
|Character Modifier| <ul><li>Play as NPCs - Nightwing, Boss Brainiac.</li><li>Change forced character in story mode or other modes.</li><li>**You need to restart fight after using this modifier to load extra data!**</ul>|
|Speed Modifier| <ul><li>Change game speed, enjoy fights in slowmotion!</li></ul> |
|Camera Control| <ul><li>Freeze camera position & rotation.</li><li>Freely move and rotate camera with keyboard hotkeys.</li><li>Play in predefined custom camera modes: <ul><li>Mortal Kombat 11</li><li>3RD Person</li><li>1ST Person</li></ul> |
|Cheats| All cheats can be toggled for both P1 and P2 <ul><li>Infinite Health</li><li>Zero Health</li></ul> |
|Misc.| <ul><li>Completely disable all HUD elements</li></ul> |

## Features


## NOTE

Since some people might use this plugin for 60 fps patch only, I've added an option in the .ini which activates FPS patch only and ignores all other features. Set **b60FPSModeOnly** in ini to true to enable.

![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/4.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/5.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/2.jpg)



# Building

I2Hook was developed & tested using Visual Studio 2017.


# Credits/Used stuff

https://github.com/CookiePLMonster/ModUtils

https://github.com/ocornut/imgui

https://github.com/Rebzzel/kiero

D3D11 hook based on https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook
