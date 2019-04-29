# Cerasus~樱花🌸
This Program is a Cerasus DirectX Render Dynamic Link Library Project.  
本程序是采用C++ DirectX开发渲染动态链接库项目。  
このプログラムは、ダイナミックリンクライブラリプロジェクトをレンダリングするC ++ DirectX開発です。  
Ce programme est un projet de bibliothèque de liens dynamiques de rendu de développement C ++ DirectX.  
Эта программа представляет собой проект библиотеки динамических ссылок для визуализации разработки на C ++.  

## Abstruct
This project is mainly about DX9 playing games, video, wallpaper rendering, music, sound effect, speaker playing, keyboard, mouse, joystick control, and some game related programming. The library is designed for quick and easy development, debugging, testing, and deployment of games, applications, and graphics. The name Cerasus is adopted because it stands for cherry blossom in Latin and is as colorful as our game.

这个工程主要是DX9进行游戏、视频、壁纸的渲染，音乐、音效、扬声器的播放，键盘、鼠标、游戏杆的控制，以及部分游戏相关的程式设计。设计这个库的目的是为了快速、方便地进行游戏、应用、图形的开发、调试、测试和部署。采用Cerasus这个名字是因为其拉丁文代表的是"樱花"，正如我们的游戏一样绚丽多彩。

このプロジェクトは主にゲーム、ビデオ、壁紙のレンダリング、音楽、効果音、スピーカーの再生、キーボード、マウス、ジョイスティックコントロール、そしていくつかのゲーム関連のプログラミングのためのDX9です。 このライブラリの目的は、ゲーム、アプリケーション、およびグラフィックを迅速かつ簡単に開発、デバッグ、テスト、および展開することです。 Cerasusという名前はラテン語が "さくら"を表し、私たちのゲームのようにカラフルであることから使われています。  

Ce projet concerne principalement DX9 pour le jeu, la vidéo, le rendu de papier peint, la musique, les effets sonores, la lecture des enceintes, le clavier, la souris, le contrôle par joystick et certaines programmations liées au jeu. Le but de cette bibliothèque est de développer, déboguer, tester et déployer rapidement et facilement des jeux, des applications et des graphiques. Le nom Cerasus est utilisé parce que sa langue latine signifie "sakura" et est aussi coloré que notre jeu.  

Этот проект в основном DX9 для игр, видео, рендеринга обоев, музыки, звуковых эффектов, воспроизведения динамиков, клавиатуры, мыши, управления джойстиком и некоторых игр, связанных с программированием. Цель этой библиотеки - быстро и легко разрабатывать, отлаживать, тестировать и развертывать игры, приложения и графику. Название Cerasus используется потому, что его латинский язык означает «сакура» и такой же красочный, как и наша игра.

## Constitute
  * ### DirectCommon
    * #### *`DirectCommon` is a DirectX public header file that contains `DirectX9` and `DirectX11` header files, library files, and some common macros.*
    * #### *`DirectCommon` also includes functions in the `D3DX` library, including DirectInput, DirectSound, DirectShow, etc.*
    
    DirectCommon是一个DirectX公共头文件，包含DirectX9和DirectX11头文件，库文件和一些常见的宏。DirectCommon还包括D3DX库中的函数，包括DirectInput，DirectSound，DirectShow等。
    
  * ### DirectTypes
    * #### *`DirectTypes` mainly defines the enumeration and structure of DirectX.*
    
    DirectTypes主要定义DirectX的枚举和结构。
  
  * ### DirectTemplate
    * #### *`DirectTemplate` mainly defines some commonly used function templates, such as the release of pointer objects and COM interfaces.*
    
    DirectTemplate主要定义了一些常用的函数模板，例如指针对象和COM接口的释放。
  
  * ### DirectGraphics
    * #### *`DirectGraphics` class is mainly about DX9 device status, device objects, device parameters, graphics card model, rendering format, buffer format, template depth, resolution and other initialization, rendering parameter display rendering, rendering flow control and related rendering object interface.*
    * #### *DX9 render object initialization.*
    * #### *DX9 rendering parameter drawing initialization.*
    * #### *DX9 rendering process control (start drawing, clearing, flipping, ending drawing).*

  * ### DirectGraphics3D
  * ### DirectGraphics2D
  * ### DirectGraphics11
  * ### DirectInput
  * ### DirectSound
  * ### DirectShow
  * ### DirectSurface
  * ### DirectTexture
  * ### DirectSprite
  * ### DirectSafe
  * ### DirectMesh
  * ### DirectFont
  * ### DirectThreadSafe
  * ### Cerasufps
  * ### CerasuUnit
  * ### CerasusAlgorithm
  * ### CerasusTypes
  * ### SakuraBlend
  * ### SakuraButton
  * ### SakuraCheckBox
  * ### SakuraComboBox
  * ### SakuraControl
  * ### SakuraDialog
  * ### SakuraEditBox
  * ### SakuraElement
  * ### SakuraListBox
  * ### SakuraRadioButton
  * ### SakuraResource
  * ### SakuraResourceManager
  * ### SakuraScrollBar
  * ### SakuraSlider
  * ### SakuraStatic
  * ### SakuraUICommon
  * ### SakuraUnit
  * ### DXUICommon
  * ### DXUIManager
  * ### DXUIWindow
