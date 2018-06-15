/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics.h
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.24a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-2	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-11	v1.22a	alopex	Add D3D9 Lost Device Function.
* @date		2018-04-12	v1.23a	alopex	Add Macro Call Mode.
* @date		2018-06-16	v1.24a	alopex	Add StretchRect Function.
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

#define DIRECTGRAPHICS_CALLMODE	__stdcall

#ifndef USER_SCREENWIDTH
#define USER_SCREENWIDTH	640		//UserScreenWidth(~����������)
#endif

#ifndef USER_SCREENHEIGHT
#define USER_SCREENHEIGHT	480		//UserScreenHeight(~��������߶�)
#endif

#define ADAPTERTYPESIZE		50		//AdapterType Size(~�洢�Կ��ͺ�����)

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

	CRITICAL_SECTION m_cs;				//Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;					//Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectGraphics();					//DirectGraphics Constructor Function(~DirectGraphics���캯��)
	~DirectGraphics();					//DirectGraphics Destructor	Function(~DirectGraphics��������)

	virtual IDirect3D9* DIRECTGRAPHICS_CALLMODE DirectGraphicsGetObject(void) const;		//DirectGraphics Get Object(~DirectGraphics��ȡD3D9����)
	virtual IDirect3DDevice9* DIRECTGRAPHICS_CALLMODE DirectGraphicsGetDevice(void) const;	//DirectGraphics Get Device(~DirectGraphics��ȡD3D9�豸����)
	virtual const D3DCAPS9* DIRECTGRAPHICS_CALLMODE DirectGraphicsGetCaps(void) const;		//DirectGraphics Get Caps(~DirectGraphics��ȡD3D9�豸״̬)
	virtual const D3DPRESENT_PARAMETERS* DIRECTGRAPHICS_CALLMODE DirectGraphicsGetPresentParameters(void) const;	//DirectGraphics Get Present Parameters(~DirectGraphics��ȡD3D9�Կ�����)
	virtual const wchar_t* DIRECTGRAPHICS_CALLMODE DirectGraphicsAdapterType(void) const;	//DirectGraphics Get Adapter Type(~DirectGraphics��ȡD3D9�Կ��ͺ�)
	virtual const ID3DXFont* DIRECTGRAPHICS_CALLMODE DirectGraphicsGetFont(void) const;		//DirectGraphics Get Font(~DirectGraphics��ȡD3D9����)

	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsTestCooperativeLevel(void) const;	//DirectGraphics Get TestCooperativeLevel��ȡD3D9��ǰ״̬
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsResetDevice(void);				//DirectGraphics Reset Direct3D 9 Device����D3D9�豸
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsGetBackBuffer(IDirect3DSurface9** ppD3D9BackBuffer);	//DirectGraphics Get BackBuffer��ȡD3D9����
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsReset(void);						//DirectGraphics Reset & Init����DirectGraphics�����³�ʼ��

	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9** ppD3D9Surface);//DirectGraphics Create Off-Screen Plain Surface������������
	
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter);	//DirectGraphics StretchRect���Ʊ���
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect);								//DirectGraphics StretchRect���Ʊ���(����+1)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestSurface);																				//DirectGraphics StretchRect���Ʊ���(����+2)(Ĭ�ϻ�����������)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect);																						//DirectGraphics StretchRect���Ʊ���(����+3)(Ĭ�ϻ��Ʊ���Ϊ��̨����)(Ĭ�ϲ����������˲�)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface);																												//DirectGraphics StretchRect���Ʊ���(����+4)(Ĭ�ϻ�����������)(Ĭ�ϻ��Ʊ���Ϊ��̨����)(Ĭ�ϲ����������˲�)

	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsInit(HWND hWnd);					//DirectGraphics Initialization(W:640 H:480 Windowed)(~DirectGraphics��ʼ��:���ڿ��:640,���ڸ߶�:480)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsInit(HWND hWnd, bool bIsWindowed);//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp);//DirectGraphics Initialization(~DirectGraphics��ʼ�� D3DPRESENT_PARAMETERS�ṹ���������)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsBeginScene(void);					//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����������Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsEndScene(void);					//DirectGraphics End Render(~DirectGraphics������Ⱦ:�����з�ת��ʾ)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsBegin(void);						//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����Ļ->��ʼ��Ⱦ)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsEnd(void);						//DirectGraphics End Render(~DirectGraphics������Ⱦ:������Ⱦ->��ת��Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsPresent(void);					//DirectGraphics Present Render(~DirectGraphics��ת��Ļ)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsClear(void);						//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:��ɫ���)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsClear(DWORD dwColor);				//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:ѡ����ɫ���)
	
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsFontInit();						//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsFontInit(int nFontSize);			//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:nFontSize:�����С)
	virtual HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType);	//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:<nFontSize>:�����С <lpszFontType>:������ʽ)
	virtual void DIRECTGRAPHICS_CALLMODE DirectGraphicsFontDrawText(HWND hWnd);							//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�)
	virtual void DIRECTGRAPHICS_CALLMODE DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor);		//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�:<dwColor>:������ɫ)
};

//Variable Definition

//Function Definition

#endif