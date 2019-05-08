# 樱花🌸
本程序是基于DirectX樱花动态链接库项目。

## 语言
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)

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
    &nbsp;
  * ### CerasusClass
    &nbsp;
  * ### SakuraClass
    &nbsp;
  * ### DXUIClass
    &nbsp;
