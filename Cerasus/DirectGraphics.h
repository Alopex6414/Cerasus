/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectGraphics.h
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Alice
* @version	v1.31a
* @date		2017-11-02	v1.00a	alopex	Create Project.
* @date		2017-12-02	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-08	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-11	v1.22a	alopex	Add D3D9 Lost Device Function.
* @date		2018-04-12	v1.23a	alopex	Add Macro Call Mode.
* @date		2018-06-16	v1.24a	alopex	Add StretchRect Function.
* @date		2018-06-17	v1.25a	alopex	Modify Reset Function.
* @date		2018-06-18	v1.26a	alopex	Modify D3D9 Clear Function(Background Color).
* @date		2018-06-21	v1.27a	alopex	Update Function D3DXFont Abort.
* @date		2018-06-23	v1.28a	alopex	Repair Bugs.
* @date		2018-06-23	v1.29a	alopex	Add Draw Function.
* @date		2018-11-23	v1.30a	alopex	Alter Call Method.
* @date		2019-03-30	v1.31a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTGRAPHICS_H_
#define __DIRECTGRAPHICS_H_

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS_CALLMETHOD	__stdcall

// Macro Const
#ifndef USER_SCREENWIDTH
#define USER_SCREENWIDTH	640
#endif

#ifndef USER_SCREENHEIGHT
#define USER_SCREENHEIGHT	480
#endif

#define DX9_GRAPHICS_ADAPTER_ARRAY_SIZE		64
#define DX9_GRAPHICS_FORMAT_ARRAY_SIZE		64
#define DX9_GRAPHICS_SCREEN_ARRAY_SIZE		64

// Class Definition
class DIRECTGRAPHICS_API DirectGraphics
{
private:
	IDirect3D9*	m_pD3D9;											// Direct3D 9 Object(~D3D9对象)
	IDirect3DDevice9*	m_pD3D9Device;								// Direct3D 9 Device Object(~D3D9设备对象)
	D3DCAPS9	m_D3D9Caps;											// Direct3D 9 Caps(~D3D9设备状态)
	D3DPRESENT_PARAMETERS	m_D3D9pp;								// Direct3D 9 Parameters(~D3D9设备参数)

private:
	ID3DXFont*	m_pD3DXFont;														// Direct3D 9 Font(~D3D9字体:显卡型号)
	wchar_t	m_wcD3D9AdapterType[DX9_GRAPHICS_ADAPTER_ARRAY_SIZE];					// Direct3D 9 AdapterType(eg:NVIDIA GeForce GT750M)
	wchar_t m_wcD3D9BackFormat[DX9_GRAPHICS_FORMAT_ARRAY_SIZE];						// Direct3D 9 BackBufferFormat(eg:D3DFMT_A8R8G8B8)
	wchar_t m_wcD3D9AutoDepthStencilFormat[DX9_GRAPHICS_FORMAT_ARRAY_SIZE];			// Direct3D 9 AutoDepthStencilFormat(eg:D3DFMT_D24S8)
	wchar_t m_wcD3D9ScreenInfo[DX9_GRAPHICS_SCREEN_ARRAY_SIZE];						// Direct3D 9 Screen Information(eg:D3D9 Vsync on (640x480))

protected:
	CRITICAL_SECTION m_cs;											// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;												// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

protected:
	UINT m_nWidth;													// Direct3D 9 Suface Width(~D3D9窗口表面宽度)(窗口模式)
	UINT m_nHeight;													// Direct3D 9 Suface Height(~D3D9窗口表面高度)(窗口模式)

public:
	DirectGraphics();												// DirectGraphics Construction Function(~DirectGraphics构造函数)
	~DirectGraphics();												// DirectGraphics Destruction Function(~DirectGraphics析构函数)

	IDirect3D9*						DIRECTGRAPHICS_CALLMETHOD	GetD3D9() const;							// DirectGraphics Get D3D9 Object(~DirectGraphics获取D3D9对象)
	IDirect3DDevice9*				DIRECTGRAPHICS_CALLMETHOD	GetDevice() const;							// DirectGraphics Get Device Object(~DirectGraphics获取D3D9设备对象)
	ID3DXFont*						DIRECTGRAPHICS_CALLMETHOD	GetFont() const;							// DirectGraphics Get Font(~DirectGraphics获取D3D9字体)
	const D3DCAPS9*					DIRECTGRAPHICS_CALLMETHOD	GetCaps() const;							// DirectGraphics Get Caps(~DirectGraphics获取D3D9设备状态)
	const D3DPRESENT_PARAMETERS*	DIRECTGRAPHICS_CALLMETHOD	GetPP() const;								// DirectGraphics Get Present Parameters(~DirectGraphics获取D3D9显卡参数)

	const wchar_t*					DIRECTGRAPHICS_CALLMETHOD	GetAdapterType() const;						// DirectGraphics Get Adapter Type(~DirectGraphics获取D3D9显卡型号)
	const wchar_t*					DIRECTGRAPHICS_CALLMETHOD	GetBackBufferFormat() const;				// DirectGraphics Get BackBuffer Format(~DirectGraphics获取后台缓冲格式)
	const wchar_t*					DIRECTGRAPHICS_CALLMETHOD	GetAutoDepthStencilFormat() const;			// DirectGraphics Get AutoDepthStencil Format(~DirectGraphics深度模板缓冲格式)
	const wchar_t*					DIRECTGRAPHICS_CALLMETHOD	GetScreenInfo() const;						// DirectGraphics Get Screen Infomation(~DirectGraphics屏幕信息)

	UINT							DIRECTGRAPHICS_CALLMETHOD	GetWidth() const;							// DirectGraphics Get Surface Widht(~DirectGraphics获取D3D9设备表面宽度)
	UINT							DIRECTGRAPHICS_CALLMETHOD	GetHeight() const;							// DirectGraphics Get Surface Height(~DirectGraphics获取D3D9设备表面高度)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsResetDevice(void);					//DirectGraphics Reset Direct3D 9 Device(~DirectGraphics重置D3D9设备)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsResetFont(void);					//DirectGraphics Reset Direct3D 9 Font(~DirectGraphics重置D3D9字体)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsReset(void);						//DirectGraphics Reset Direct3D 9 All(~DirectGraphics重置DirectGraphics类)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsTestCooperativeLevel(void) const;	//DirectGraphics Get TestCooperativeLevel(~DirectGraphics获取D3D9当前状态)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9** ppD3D9Surface);							//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics创建离屏表面)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, IDirect3DSurface9** ppD3D9Surface);																	//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics创建离屏表面)(重载+1)(默认后台缓冲格式D3DFMT_A8R8G8B8)(默认D3D内存池D3DPOOL_DEFAULT)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(IDirect3DSurface9** ppD3D9Surface);																								//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics创建离屏表面)(重载+2)(默认屏幕尺寸(W:640 H:480 Windowed))(默认后台缓冲格式D3DFMT_A8R8G8B8)(默认D3D内存池D3DPOOL_DEFAULT)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetBackBuffer(IDirect3DSurface9** ppD3D9BackBuffer);	//DirectGraphics Get BackBuffer(~DirectGraphics获取D3D9表面Surface)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter);	//DirectGraphics StretchRect(~DirectGraphics绘制表面)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect);								//DirectGraphics StretchRect(~DirectGraphics绘制表面)(重载+1)(默认不进行纹理滤波)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestSurface);																				//DirectGraphics StretchRect(~DirectGraphics绘制表面)(重载+2)(默认绘制整个表面)(默认不进行纹理滤波)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect);																						//DirectGraphics StretchRect(~DirectGraphics绘制表面)(重载+3)(默认绘制表面为后台缓冲)(默认不进行纹理滤波)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface);																													//DirectGraphics StretchRect(~DirectGraphics绘制表面)(重载+4)(默认绘制整个表面)(默认绘制表面为后台缓冲)(默认不进行纹理滤波)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd);					//DirectGraphics Initialization(W:640 H:480 Windowed)(~DirectGraphics初始化:窗口宽度:640,窗口高度:480)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd, bool bIsWindowed);	//DirectGraphics Initialization(~DirectGraphics初始化 <窗口模式>bIsWindowed = true, <全屏模式>bIsWindowed = false)(重载+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight);	//DirectGraphics Initialization(~DirectGraphics初始化 <窗口模式>bIsWindowed = true, <全屏模式>bIsWindowed = false)(重载+2)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp);	//DirectGraphics Initialization(~DirectGraphics初始化 D3DPRESENT_PARAMETERS结构体参数传入)(重载+3)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBeginScene(void);					//DirectGraphics Begin Render(~DirectGraphics开始渲染:不进行清除屏幕)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsEndScene(void);						//DirectGraphics End Render(~DirectGraphics结束渲染:不进行翻转显示)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBegin(void);						//DirectGraphics Begin Render(~DirectGraphics开始渲染:清除屏幕->开始渲染)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBegin(D3DCOLOR Color);				//DirectGraphics Begin Render(~DirectGraphics开始渲染:清除屏幕->开始渲染)(重载+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsEnd(void);							//DirectGraphics End Render(~DirectGraphics结束渲染:结束渲染->翻转屏幕)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsPresent(void);						//DirectGraphics Present Render(~DirectGraphics翻转屏幕)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsClear(void);						//DirectGraphics Clear Screen(~DirectGraphics清除屏幕:黑色填充)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsClear(D3DCOLOR Color);				//DirectGraphics Clear Screen(~DirectGraphics清除屏幕:选定颜色填充)(重载+1)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(void);						//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(int Height);				//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化:nFontSize:字体大小)(重载+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(int Height, LPWSTR lpszFontType);	//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化:<nFontSize>:字体大小 <lpszFontType>:字体样式)(重载+2)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCWSTR pFaceName);	//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化)(重载+3)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawText(HWND hWnd);							//DirectGraphicsFont Draw Text(~DirectGraphics绘制显卡型号)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor);		//DirectGraphicsFont Draw Text(~DirectGraphics绘制显卡型号:<dwColor>:字体颜色)(重载+1)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextW(LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);	//DirectGraphicsFont Draw Text(~DirectGraphics绘制)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextA(LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);	//DirectGraphicsFont Draw Text(~DirectGraphics绘制)

	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextAdapterType(LPRECT pRect, DWORD Format, D3DCOLOR Color);
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextFormat(LPRECT pRect, DWORD Format, D3DCOLOR Color);
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextScreen(LPRECT pRect, DWORD Format, D3DCOLOR Color);

	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9Screen(UINT nWidth, UINT nHeight, LPWSTR pString);			//DirectGraphics Get D3D9 Screen(~DirectGraphics D3D9分辨率)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9Format(D3DFORMAT Format, LPWSTR pString);					//DirectGraphics Get D3D9 Format(~DirectGraphics D3D9格式)
};

#endif