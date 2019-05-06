# Cerasus🌸
This Program is a Cerasus DirectX Render Dynamic Link Library Project.

## Abstract
This project is mainly about DX9 playing games, video, wallpaper rendering, music, sound effect, speaker playing, keyboard, mouse, joystick control, and some game related programming. The library is designed for quick and easy development, debugging, testing, and deployment of games, applications, and graphics. The name Cerasus is adopted because it stands for cherry blossom in Latin and is as colorful as our game.

## Constitutions
Cerasus now consists of 4 parts, the **Direct** class responsible for DirectX underlying graphics rendering, the **Cerasus** class for game physics algorithms, the **Sakura** class for GUI interaction interfaces, and the **DXUI** class for rendering management.
* **Direct class s primarily responsible for the underlying part of DirectX, such as graphics rendering, music effects, game interaction, video decoding, particle systems, etc.**
* **Cerasus class is mainly responsible for the core and auxiliary parts of the game, including physical algorithms, basic primitives, fps refresh display, etc.**
* **Sakura class is primarily responsible for game interactions, such as scenes, dialogs, buttons, etc.**
* **DXUI class is mainly responsible for game management, including game scripts, resource decoding, and schedule management, which are currently not completed...**

## Features
  * ### DirectClass
    * #### *`DirectCommon` is a DirectX public header file that contains `DirectX9` and `DirectX11` header files, library files, and some common macros, and also includes functions in the `D3DX` library, including DirectInput, DirectSound, DirectShow, etc.*
    * #### *`DirectTypes` mainly defines the enumeration and structure of DirectX.*
    * #### *`DirectTemplate` mainly defines some commonly used function templates, such as the release of pointer objects and COM interfaces.*
    * #### *`DirectGraphics` class is mainly about DX9 device status, device objects, device parameters, graphics card model, rendering format, buffer format, template depth, resolution and other initialization, rendering parameter display rendering, rendering flow control and related rendering object interface.*
    &nbsp;
  * ### CerasusClass
    &nbsp;
  * ### SakuraClass
    &nbsp;
  * ### DXUIClass
