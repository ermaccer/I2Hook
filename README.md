# I2Hook
A plugin for Injustice 2.

# Installation

####  I2Hook only works with latest Steam version!

You can download binary files from [Releases](https://github.com/ermaccer/I2Hook/) page. Extract **i2hook.zip**
to Binaries\Retail folder of Injustice 2.

If you are not sure how to find your Injustice folder, search for it in your Steam library then right click on the entry and select Manage->Browse local files.

Archive breakdown:

 - dinput8.dll - [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/)
 - I2Hook.asi 
 - I2Hook.ini - configuration file


## NOTE

Since some people might use this plugin for 60 fps patch only, I've added an option in the .ini which activates FPS patch only and ignores all other features. Set **b60FPSModeOnly** in ini to true to enable.

Alternatively, download the `_60only.zip` archive.

# Controller Support
Any XInput compatible gamepad should work.

## Gamepad Controls
| Button | Effect |
| --- | --- |
| L3 + R3 | Open/Close menu|
| X | Adjust menu|
| A | Select |
| B | Back |
| D-Pad | Move/ Scale menu in adjust mode |
| Left Stick | Move menu in adjust mode |

Gamepad support can be disabled in the .ini file by setting **bEnableGamepadSupport** to false.

# Usage

If installed correctly, a notification will appear informing that the plugin was installed
and is ready to use. By default **F1** will open or close in-game menu.

![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/notif.jpg)


## Features
| Feature | Description |
| --- | --- |
|60 FPS Patch| <ul><li>Removes 30 fps lock from supermoves, intros and menus.</li><li>**If your PC does not have required hardware, turning this option on might have negative impact on perfomance!**</li> <li>**You might need to turn off in-game V-Sync if 60 fps is not applied**</li></ul> |
| | **Menu Features**| 
|Character Modifier| <ul><li>Play as NPCs - Nightwing, Boss Brainiac.</li><li>Change forced character in story mode or other modes.</li><li>**You need to restart fight after using this modifier to load extra data!**</ul>|
|Speed Modifier| <ul><li>Change game speed, enjoy fights in slowmotion!</li></ul> |
|Stage Modifier| <ul><li>Change stage to anything in any game mode.</li></ul> |
|Player Control| <ul><li>Change speed and scale of players.</li><li> Scale setting is *visual* only!</li></ul> |
|Camera Control| <ul><li>Freeze camera position & rotation.</li><li>Freely move and rotate camera with keyboard hotkeys.</li><li>Play in predefined custom camera modes: <ul><li>Mortal Kombat 11</li><li>3RD Person</li><li>1ST Person</li></ul> |
|Cheats| All cheats can be toggled for both P1 and P2 <ul><li>Infinite Health</li><li>Zero Health</li><li>Infinite Meter</li><li>Zero Meter</li><li>Infinite Clashes</li></ul> |
|Misc.| <ul><li>Completely disable all HUD elements</li></ul> |

## Features


![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/4.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/5.jpg)
![Preview](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/dcf2/i2hook/2.jpg)

## Online Compatibility
Needless to say, any cheats will **NOT** work online.

Playing as NPCs online is possible only if both players
have the plugin installed and synchronize settings with each other on select
screen before selecting anyone. In short, do everything on select screen
and do it in private games only. You cannot use any menu stuff against
random players.

# Building

I2Hook was developed & tested using Visual Studio 2017.


# Credits/Used stuff

https://github.com/CookiePLMonster/ModUtils

https://github.com/ocornut/imgui

https://github.com/Rebzzel/kiero

D3D11 hook based on https://github.com/rdbo/ImGui-DirectX-11-Kiero-Hook
