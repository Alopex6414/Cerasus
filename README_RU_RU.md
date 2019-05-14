# Вишневый цвет🌸
Эта программа представляет собой проект библиотеки динамических ссылок Cerasus DirectX Render.

## язык
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)

## Аннотация
Этот проект в основном о DX9, играющих в игры, видео, рендеринг обоев, музыку, звуковые эффекты, игру динамиков, клавиатуру, мышь, управление джойстиком и некоторые игры, связанные с программированием. Библиотека предназначена для быстрой и простой разработки, отладки, тестирования и развертывания игр, приложений и графики. Название Cerasus принято потому, что оно обозначает вишневый цвет на латыни и такое же красочное, как и наша игра.

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
    * #### *`DirectGraphics` class is mainly about `DX9` device status, device objects, device parameters, graphics card model, rendering format, buffer format, template depth, resolution and other initialization, rendering parameter display rendering, rendering flow control and related rendering object interface.*
    * #### *`DirectGraphics11` class is a `DX11` version of the `DirectGraphics` class. It is mainly used to boot and initialize DX11 rendering. Compared with the `DX9` initialization process, the difference is relatively large.*
     * #### *`DirectGraphics3D` class is mainly about the rendering of 3D graphics. It needs to fill the vertex buffer and index buffer of 3D graphics, and matrix transform the graphics (stretch, rotate, pan, etc.), rendering settings (light, material, texture, alpha blend), the final output is rendered to the device.*
     * #### *`DirectGraphics2D` class is mainly about the rendering of 2D graphics, which needs to fill the vertex buffer and index buffer of 2D graphics. Relative to 3D rendering, it is easy to do complex matrix transformations due to their unique vertex format. After setting the rendering mode, you can finally render the output to the device.*
     * #### *`DirectInput` class is primarily used for interactive input devices such as keyboards, mice, and joysticks. Provides the ability to interact with the driver layer, including initialization, detection, feedback, and processing.*
     * #### *`DirectSound` class is mainly used for game music effects, and supports Wav and PCM file decoding. Provides the ability to interact with the driver layer, including initialization, detection, feedback, and processing.*
     * #### *`DirectShow` class is mainly used for game animation music playback. The number of decoders supported by itself is not much. The common COM interface is provided, and the corresponding decoding program needs to be written for the development file.*
     * #### *`DirectMesh` is mainly used to draw some collections of D3DX itself, including cubes, spheres, cylinders, torus, polygons and teapots.*
     * #### *`DirectFont` class is used for font rendering, this part is not used by Direct3D, but by GDI, so the rendering efficiency is not very high.*
     * #### *`DirectSprite` is mainly used for particle swarm rendering ❄, such as snowflake deciduous particles rendering 🍂.It can perform particle rendering of simple 2D graphics, such as creation, matrix transformation, and rendering.*
     * #### *`DirectSurface` class is used for simple screen rendering, screen capture, and high efficiency, which can be used to create video players.*
     * #### *`DirectTexture` class is mainly used to draw texture graphics. Texture images can be loaded from file or memory for 3D graphics or 2D graphics vertex index rendering, which is more powerful than the DirectSurface class.*
     * #### *`DirectThreadSafe` class is used for resource security between threads. With CriticalSection, it mainly protects resources within the class and prevents resource competition.*
     * #### *`DirectSafe` class is used for resource security between threads. The same as DirectThread, it is not necessary to delete the CriticalSection after the DirectSafe class exits, can be used multiple times.*
    &nbsp;
  * ### CerasusClass
     * #### *`Cerasusfps` class is mainly used to calculate the frame rate of D3DX rendering, and is drawn on the window to detect whether the game has dropped frames.*
     * #### *`CerasusUnit` class is mainly used to draw 2D primitives in 3D coordinate system, usually rectangular primitives. Textures can be loaded from files or unwrapped through resources. CerasusUnit also has coordinate transformations, materials, lighting, and rendering properties for 3D primitives.*
     * #### *`CerasusAlgorithm` class mainly defines some common algorithms for graphics. These algorithms are generally given in the form of static member functions and can be called in the program.*
     * #### *`CerasusType` class is mainly used to define the type of Cerasus class.*
    &nbsp;
  * ### SakuraClass
    &nbsp;
  * ### DXUIClass
    &nbsp;
