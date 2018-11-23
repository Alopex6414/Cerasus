/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics.h
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.30a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-2	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
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
*/
#pragma once

#ifndef __DIRECTGRAPHICS_H_
#define __DIRECTGRAPHICS_H_

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS_CALLMETHOD	__stdcall

#ifndef USER_SCREENWIDTH
#define USER_SCREENWIDTH	640		//UserScreenWidth(~����������)
#endif

#ifndef USER_SCREENHEIGHT
#define USER_SCREENHEIGHT	480		//UserScreenHeight(~��������߶�)
#endif

#define ADAPTERTYPESIZE		64		//AdapterType Size(~�洢�Կ��ͺ�����)
#define D3D9FORMATSIZE		64		//D3D9 Format Size(~�洢������������)
#define D3D9SCREENSIZE		64		//D3D9 Format Size(~�洢��Ļ�ֱ�������)

//Struct Definition

//CallBack Definition

//Class Definition
class DIRECTGRAPHICS_API DirectGraphics
{
private:
	IDirect3D9* m_pD3D9;				//The Direct3D 9 Main Object(~D3D9����)
	IDirect3DDevice9* m_pD3D9Device;	//The Direct3D 9 Render Device(~D3D9�豸����)
	D3DCAPS9 m_D3D9Caps;				//The Direct3D 9 Caps(~D3D9�豸״̬)
	D3DPRESENT_PARAMETERS m_D3D9pp;		//The Direct3D 9 Parameters(~D3D9�豸����)
	ID3DXFont* m_pD3DXFont;				//The Direct3D 9 Font(~D3D9����:�Կ��ͺ���ʾ)
	wchar_t m_wcD3D9AdapterType[ADAPTERTYPESIZE];	//The Direct3D 9 AdapterType(eg:NVIDIA GeForce GT750M)
	wchar_t m_wcD3D9BackFormat[D3D9FORMATSIZE];		//The Direct3D 9 BackBufferFormat(eg:D3DFMT_A8R8G8B8)
	wchar_t m_wcD3D9AutoDepthStencilFormat[D3D9FORMATSIZE];	//The Direct3D 9 AutoDepthStencilFormat(eg:D3DFMT_D24S8)
	wchar_t m_wcD3D9ScreenInfo[D3D9SCREENSIZE];		//The Direct3D 9 Screen Information(eg:D3D9 Vsync on (640x480))

	CRITICAL_SECTION m_cs;				//Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;					//Thread Safe Status(~D3D9�̰߳�ȫ״̬)

protected:
	UINT m_nWidth;						//The Direct3D 9 Suface Width(~D3D9���ڱ�����)(����ģʽ)
	UINT m_nHeight;						//The Direct3D 9 Suface Height(~D3D9���ڱ���߶�)(����ģʽ)

public:
	DirectGraphics();					//DirectGraphics Constructor Function(~DirectGraphics���캯��)
	~DirectGraphics();					//DirectGraphics Destructor	Function(~DirectGraphics��������)

	virtual IDirect3D9* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetObject(void) const;			//DirectGraphics Get Object(~DirectGraphics��ȡD3D9����)
	virtual IDirect3DDevice9* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetDevice(void) const;	//DirectGraphics Get Device(~DirectGraphics��ȡD3D9�豸����)
	virtual const D3DCAPS9* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetCaps(void) const;		//DirectGraphics Get Caps(~DirectGraphics��ȡD3D9�豸״̬)
	virtual const D3DPRESENT_PARAMETERS* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetPresentParameters(void) const;	//DirectGraphics Get Present Parameters(~DirectGraphics��ȡD3D9�Կ�����)
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetAdapterType(void) const;						//DirectGraphics Get Adapter Type(~DirectGraphics��ȡD3D9�Կ��ͺ�)
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetBackBufferFormat(void) const;					//DirectGraphics Get BackBuffer Format(~DirectGraphics��ȡ��̨�����ʽ)
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetAutoDepthStencilFormat(void) const;			//DirectGraphics Get AutoDepthStencil Format(~DirectGraphics���ģ�建���ʽ)
	virtual const ID3DXFont* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetFont(void) const;							//DirectGraphics Get Font(~DirectGraphics��ȡD3D9����)

	virtual const UINT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetSufaceWidth(void) const;							//DirectGraphics Get Surface Widht(~DirectGraphics��ȡD3D9�豸������)
	virtual const UINT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetSufaceHeight(void) const;							//DirectGraphics Get Surface Height(~DirectGraphics��ȡD3D9�豸����߶�)

	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9AdapterType(void) const;
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9BackFormat(void) const;
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9AutoDepthStencilFormat(void) const;
	virtual const wchar_t* DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9ScreenInfo(void) const;

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsResetDevice(void);					//DirectGraphics Reset Direct3D 9 Device(~DirectGraphics����D3D9�豸)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsResetFont(void);					//DirectGraphics Reset Direct3D 9 Font(~DirectGraphics����D3D9����)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsReset(void);						//DirectGraphics Reset Direct3D 9 All(~DirectGraphics����DirectGraphics��)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsTestCooperativeLevel(void) const;	//DirectGraphics Get TestCooperativeLevel(~DirectGraphics��ȡD3D9��ǰ״̬)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9** ppD3D9Surface);							//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics������������)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, IDirect3DSurface9** ppD3D9Surface);																	//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics������������)(����+1)(Ĭ�Ϻ�̨�����ʽD3DFMT_A8R8G8B8)(Ĭ��D3D�ڴ��D3DPOOL_DEFAULT)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsCreateOffscreenPlainSurface(IDirect3DSurface9** ppD3D9Surface);																								//DirectGraphics Create Off-Screen Plain Surface(~DirectGraphics������������)(����+2)(Ĭ����Ļ�ߴ�(W:640 H:480 Windowed))(Ĭ�Ϻ�̨�����ʽD3DFMT_A8R8G8B8)(Ĭ��D3D�ڴ��D3DPOOL_DEFAULT)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetBackBuffer(IDirect3DSurface9** ppD3D9BackBuffer);	//DirectGraphics Get BackBuffer(~DirectGraphics��ȡD3D9����Surface)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter);	//DirectGraphics StretchRect(~DirectGraphics���Ʊ���)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect);								//DirectGraphics StretchRect(~DirectGraphics���Ʊ���)(����+1)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestSurface);																				//DirectGraphics StretchRect(~DirectGraphics���Ʊ���)(����+2)(Ĭ�ϻ�����������)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect);																						//DirectGraphics StretchRect(~DirectGraphics���Ʊ���)(����+3)(Ĭ�ϻ��Ʊ���Ϊ��̨����)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface);																													//DirectGraphics StretchRect(~DirectGraphics���Ʊ���)(����+4)(Ĭ�ϻ�����������)(Ĭ�ϻ��Ʊ���Ϊ��̨����)(Ĭ�ϲ����������˲�)

	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd);					//DirectGraphics Initialization(W:640 H:480 Windowed)(~DirectGraphics��ʼ��:���ڿ��:640,���ڸ߶�:480)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd, bool bIsWindowed);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)(����+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)(����+2)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� D3DPRESENT_PARAMETERS�ṹ���������)(����+3)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBeginScene(void);					//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����������Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsEndScene(void);						//DirectGraphics End Render(~DirectGraphics������Ⱦ:�����з�ת��ʾ)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBegin(void);						//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����Ļ->��ʼ��Ⱦ)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsBegin(D3DCOLOR Color);				//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����Ļ->��ʼ��Ⱦ)(����+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsEnd(void);							//DirectGraphics End Render(~DirectGraphics������Ⱦ:������Ⱦ->��ת��Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsPresent(void);						//DirectGraphics Present Render(~DirectGraphics��ת��Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsClear(void);						//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:��ɫ���)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsClear(D3DCOLOR Color);				//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:ѡ����ɫ���)(����+1)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(void);						//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(int Height);				//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:nFontSize:�����С)(����+1)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(int Height, LPWSTR lpszFontType);	//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:<nFontSize>:�����С <lpszFontType>:������ʽ)(����+2)
	virtual HRESULT DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontInit(INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCWSTR pFaceName);	//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��)(����+3)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawText(HWND hWnd);							//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor);		//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�:<dwColor>:������ɫ)(����+1)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextW(LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);	//DirectGraphicsFont Draw Text(~DirectGraphics����)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextA(LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color);	//DirectGraphicsFont Draw Text(~DirectGraphics����)

	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextAdapterType(LPRECT pRect, DWORD Format, D3DCOLOR Color);
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextFormat(LPRECT pRect, DWORD Format, D3DCOLOR Color);
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsFontDrawTextScreen(LPRECT pRect, DWORD Format, D3DCOLOR Color);

	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9Screen(UINT nWidth, UINT nHeight, LPWSTR pString);			//DirectGraphics Get D3D9 Screen(~DirectGraphics D3D9�ֱ���)
	virtual void DIRECTGRAPHICS_CALLMETHOD DirectGraphicsGetD3D9Format(D3DFORMAT Format, LPWSTR pString);					//DirectGraphics Get D3D9 Format(~DirectGraphics D3D9��ʽ)
};

//Variable Definition

//Function Definition

#endif