# 樱花🌸
本程序是基于DirectX樱花动态链接库项目。

## 语言
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)
  * [Français](https://github.com/Alopex6414/Cerasus/blob/master/README_FR_FR.md)
  * [Deutsch](https://github.com/Alopex6414/Cerasus/blob/master/README_DE_DE.md)

## 摘要
这个项目主要是关于DX9游戏，视频，壁纸渲染，音乐，音效，扬声器播放，键盘，鼠标，操纵杆控制，以及一些游戏相关的编程。 该库旨在快速轻松地开发，调试，测试和部署游戏，应用程序和图形。 Cerasus这个名字被采用是因为它代表拉丁语中的樱花，并且与我们的游戏一样丰富多彩。

## 组成
Cerasus现在由4部分组成，**Direct**类负责DirectX底层图形渲染，**Cerasus**类用于游戏物理算法，**Sakura**类用于GUI交互界面，以及**DXUI**用于渲染管理的类。
* **Direct class主要负责DirectX的基础部分，如图形渲染，音乐效果，游戏交互，视频解码，粒子系统等。**
* **Cerasus类主要负责游戏的核心和辅助部分，包括物理算法，基本原语，fps刷新显示等。**
* **Sakura课程主要负责游戏交互，例如场景，对话框，按钮等。**
* **DXUI类主要负责游戏管理，包括游戏脚本，资源解码和日程管理，目前尚未完成......**

## 特征
  * ### DirectClass
    * #### *`DirectCommon`是一个DirectX公共头文件，包含`DirectX9`和`DirectX11`头文件，库文件和一些常用宏，还包括`D3DX`库中的函数，包括DirectInput，DirectSound ，DirectShow等。*
    * #### *`DirectTypes`主要定义DirectX的枚举和结构。*
    * #### *`DirectTemplate`主要定义一些常用的函数模板，例如指针对象和COM接口的发布。*
    * #### *`DirectGraphics`类主要讲述`DX9`设备状态，设备对象，设备参数，显卡模型，渲染格式，缓冲格式，模板深度，分辨率等初始化，渲染参数显示渲染，渲染流程控件和相关的渲染对象接口。*
    * #### *`DirectGraphics11`类是`DirectGraphics`类的`DX11`版本。它主要用于启动和初始化DX11渲染。与'DX9`初始化过程相比，差异相对较大。*
    * #### *`DirectGraphics3D`类主要是关于3D图形的渲染。它需要填充3D图形的顶点缓冲区和索引缓冲区，并对矩阵变换图形（拉伸，旋转，平移等），渲染设置（光线，材质，纹理，alpha混合），最终输出渲染到设备。*
    * #### *`DirectGraphics2D`类主要是关于2D图形的渲染，它需要填充2D图形的顶点缓冲区和索引缓冲区。相对于3D渲染，由于其独特的顶点格式，很容易进行复杂的矩阵变换。设置渲染模式后，您最终可以将输出渲染到设备。*
    * #### *`DirectInput`类主要用于交互式输入设备，如键盘，鼠标和操纵杆。提供与驱动程序层交互的功能，包括初始化，检测，反馈和处理。*
    * #### *`DirectSound`类主要用于游戏音乐效果，并支持Wav和PCM文件解码。提供与驱动程序层交互的功能，包括初始化，检测，反馈和处理。*
    * #### *`DirectShow`类主要用于游戏动画音乐播放。自身支持的解码器数量不多。提供了通用的COM接口，需要为开发文件编写相应的解码程序。*
    * #### *`DirectMesh`主要用于绘制D3DX本身的一些集合，包括立方体，球体，圆柱体，圆环面，多边形和茶壶。*
    * #### *`DirectFont`类用于字体渲染，这部分不是由Direct3D使用，而是由GDI使用，因此渲染效率不是很高。*
    * #### *`DirectSprite`主要用于粒子群渲染❄，例如雪花落叶粒子渲染🍂。它可以执行简单2D图形的粒子渲染，如创建，矩阵变换和渲染。*
    * #### *`DirectSurface`类用于简单的屏幕渲染，屏幕捕获和高效率，可用于创建视频播放器。*
    * #### *`DirectTexture`类主要用于绘制纹理图形。纹理图像可以从文件或内存加载，用于3D图形或2D图形顶点索引渲染，这比DirectSurface类更强大。*
    * #### *`DirectThreadSafe`类用于线程之间的资源安全性。使用CriticalSection，它主要保护课堂内的资源并防止资源竞争。*
    * #### *`DirectSafe`类用于线程之间的资源安全性。与DirectThread相同，在DirectSafe类退出后没有必要删除CriticalSection，可以多次使用。*
    &nbsp;
  * ### CerasusClass
    * #### *`Cerasusfps`类主要用于计算D3DX渲染的帧速率，并在窗口上绘制以检测游戏是否丢帧。*
    * #### *`CerasusUnit`类主要用于在3D坐标系中绘制2D图元，通常是矩形图元。 纹理可以从文件加载或通过资源解包。 CerasusUnit还具有3D基元的坐标转换，材质，光照和渲染属性。*
    * #### *`CerasusAlgorithm`类主要定义一些常用的图形算法。 这些算法通常以静态成员函数的形式给出，可以在程序中调用。*
    * #### *`CerasusType`类主要用于定义Cerasus类的类型。*
    &nbsp;
  * ### SakuraClass
    &nbsp;
  * ### DXUIClass
    &nbsp;
