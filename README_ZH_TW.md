# 櫻花🌸
本程序是基於DirectX櫻花動態鏈接庫項目。

## 語言
  * [English](https://github.com/Alopex6414/Cerasus/blob/master/README.md)
  * [简体中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_CN.md)
  * [繁體中文](https://github.com/Alopex6414/Cerasus/blob/master/README_ZH_TW.md)
  * [日本語](https://github.com/Alopex6414/Cerasus/blob/master/README_JA_JP.md)
  * [русский](https://github.com/Alopex6414/Cerasus/blob/master/README_RU_RU.md)
  * [Français](https://github.com/Alopex6414/Cerasus/blob/master/README_FR_FR.md)
  * [Deutsch](https://github.com/Alopex6414/Cerasus/blob/master/README_DE_DE.md)

## 摘要
這個項目主要是關於DX9遊戲，視頻，壁紙渲染，音樂，音效，揚聲器播放，鍵盤，鼠標，操縱桿控制，以及壹些遊戲相關的編程。 該庫旨在快速輕松地開發，調試，測試和部署遊戲，應用程序和圖形。 Cerasus這個名字被采用是因為它代表拉丁語中的櫻花，並且與我們的遊戲壹樣豐富多彩。

## 組成
Cerasus現在由4部分組成，**Direct**類負責DirectX底層圖形渲染，**Cerasus**類用於遊戲物理算法，**Sakura**類用於GUI交互界面，以及**DXUI**用於渲染管理的類。
* **Direct class主要負責DirectX的基礎部分，如圖形渲染，音樂效果，遊戲交互，視頻解碼，粒子系統等。**
* **Cerasus類主要負責遊戲的核心和輔助部分，包括物理算法，基本原語，fps刷新顯示等。**
* **Sakura課程主要負責遊戲交互，例如場景，對話框，按鈕等。**
* **DXUI類主要負責遊戲管理，包括遊戲腳本，資源解碼和日程管理，目前尚未完成......**

## 特征
  * ### DirectClass
    * #### *`DirectCommon`是壹個DirectX公共頭文件，包含`DirectX9`和`DirectX11`頭文件，庫文件和壹些常用宏，還包括`D3DX`庫中的函數，包括DirectInput，DirectSound ，DirectShow等。*
    * #### *`DirectTypes`主要定義DirectX的枚舉和結構。*
    * #### *`DirectTemplate`主要定義壹些常用的函數模板，例如指針對象和COM接口的發布。*
    * #### *`DirectGraphics`類主要講述`DX9`設備狀態，設備對象，設備參數，顯卡模型，渲染格式，緩沖格式，模板深度，分辨率等初始化，渲染參數顯示渲染，渲染流程控件和相關的渲染對象接口。*
    * #### *`DirectGraphics11`類是`DirectGraphics`類的`DX11`版本。它主要用於啟動和初始化DX11渲染。與'DX9`初始化過程相比，差異相對較大。*
    * #### *`DirectGraphics3D`類主要是關於3D圖形的渲染。它需要填充3D圖形的頂點緩沖區和索引緩沖區，並對矩陣變換圖形（拉伸，旋轉，平移等），渲染設置（光線，材質，紋理，alpha混合），最終輸出渲染到設備。*
    * #### *`DirectGraphics2D`類主要是關於2D圖形的渲染，它需要填充2D圖形的頂點緩沖區和索引緩沖區。相對於3D渲染，由於其獨特的頂點格式，很容易進行復雜的矩陣變換。設置渲染模式後，您最終可以將輸出渲染到設備。*
    * #### *`DirectInput`類主要用於交互式輸入設備，如鍵盤，鼠標和操縱桿。提供與驅動程序層交互的功能，包括初始化，檢測，反饋和處理。*
    * #### *`DirectSound`類主要用於遊戲音樂效果，並支持Wav和PCM文件解碼。提供與驅動程序層交互的功能，包括初始化，檢測，反饋和處理。*
    * #### *`DirectShow`類主要用於遊戲動畫音樂播放。自身支持的解碼器數量不多。提供了通用的COM接口，需要為開發文件編寫相應的解碼程序。*
    * #### *`DirectMesh`主要用於繪制D3DX本身的壹些集合，包括立方體，球體，圓柱體，圓環面，多邊形和茶壺。*
    * #### *`DirectFont`類用於字體渲染，這部分不是由Direct3D使用，而是由GDI使用，因此渲染效率不是很高。*
    * #### *`DirectSprite`主要用於粒子群渲染❄，例如雪花落葉粒子渲染🍂。它可以執行簡單2D圖形的粒子渲染，如創建，矩陣變換和渲染。*
    * #### *`DirectSurface`類用於簡單的屏幕渲染，屏幕捕獲和高效率，可用於創建視頻播放器。*
    * #### *`DirectTexture`類主要用於繪制紋理圖形。紋理圖像可以從文件或內存加載，用於3D圖形或2D圖形頂點索引渲染，這比DirectSurface類更強大。*
    * #### *`DirectThreadSafe`類用於線程之間的資源安全性。使用CriticalSection，它主要保護課堂內的資源並防止資源競爭。*
    * #### *`DirectSafe`類用於線程之間的資源安全性。與DirectThread相同，在DirectSafe類退出後沒有必要刪除CriticalSection，可以多次使用。*
    &nbsp;
  * ### CerasusClass
    * #### *`Cerasusfps`類主要用於計算D3DX渲染的幀速率，並在窗口上繪製以檢測遊戲是否丟幀。*
    * #### *`CerasusUnit`類主要用於在3D坐標系中繪製2D圖元，通常是矩形圖元。紋理可以從文件加載或通過資源解包。 CerasusUnit還具有3D基元的坐標轉換，材質，光照和渲染屬性。*
    * #### *`CerasusAlgorithm`類主要定義一些常用的圖形算法。這些算法通常以靜態成員函數的形式給出，可以在程序中調用。*
    * #### *`CerasusType`類主要用於定義Cerasus類的類型。*
    &nbsp;
  * ### SakuraClass
    * #### *`SakuraUICommon`是Sakura類的共享頭文件。*
    * #### *`SakuraBlend`類主要用於原始紋理和文本渲染。*
    * #### *`SakuraButton`類主要用於Button控件。*
    * #### *`SakuraCheckBox`類主要用於CheckBox控件。*
    * #### *`SakuraComboBox`類主要用於ComboBox控件。*
    * #### *`SakuraControl`類用於控件類的基類，提供其他控件類派生接口。*
    * #### *`SakuraDialog`類主要用於構建windows。作為控件的容器，您可以添加各種類型的控件和響應。*
    * #### *`SakuraEidtBox`類主要用於EditBox控件。*
    * #### *`SakuraElement`類主要用於控制渲染原語。*
    * #### *`SakuraListBox`類主要用於ListBox控件。*
    * #### *`SakuraRadioButton`類主要用於RadioButton控件。*
    * #### *`SakuraResource`類主要用於Sakura類資源管理。*
    * #### *`SakuraResourceManager`類主要用於Sakura類資源管理類。*
    * #### *`SakuraScrollBar`類主要用於ScrollBar控件。*
    * #### *`SakuraSlider`類主要用於Slider控件。*
    * #### *`SakuraStatic`類主要用於字體繪圖控件。*
    * #### *`SakuraUint`類主要繪製基元。*
    &nbsp;
  * ### DXUIClass
      DXUI類暫時沒有完成，需要更新......
    &nbsp;
    
## 許可
   版權所有（C）2017~2011，Team Gorgeous Bubble，保留所有權利。
