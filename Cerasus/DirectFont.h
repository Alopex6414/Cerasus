/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectFont.h
* @brief	This File is DirectFont DLL Project.
* @author	Alopex/Alice
* @version	v1.15a
* @date		2017-12-16	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.10a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-12	v1.11a	alopex	Add Reset Device & Definion of DirectFont Colors.
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-11-23	v1.14a	alopex	Alter Call Method.
* @date		2019-04-09	v1.15a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTFONT_H_
#define __DIRECTFONT_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTFONT_API	__declspec(dllexport)
#else
#define DIRECTFONT_API	__declspec(dllimport)
#endif

#define DIRECTFONT_CALLMETHOD	__stdcall

#define	DX_FONT_FORMAT_CENTER			(DT_CENTER)
#define DX_FONT_FORMAT_TOPLEFT			(DT_TOP | DT_LEFT)
#define DX_FONT_FORMAT_TOPRIGHT			(DT_TOP | DT_RIGHT)
#define DX_FONT_FORMAT_BOTTOMLEFT		(DT_BOTTOM | DT_LEFT)
#define DX_FONT_FORMAT_BOTTOMRIGHT		(DT_BOTTOM | DT_RIGHT)

#define DX_FONT_D3DXCOLOR_WHITE			(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define DX_FONT_D3DXCOLOR_RED			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
#define DX_FONT_D3DXCOLOR_GREEN			(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))
#define DX_FONT_D3DXCOLOR_BLUE			(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))
#define DX_FONT_D3DXCOLOR_YELLOW		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))

// Class Definition
class DIRECTFONT_API DirectFont
{
private:
	IDirect3DDevice9* m_pD3D9Device;			// Direct3D 9 Device Object(~D3D9�豸����)
	ID3DXFont* m_pD3D9Font;						// Direct3D 9 Font Object(~D3D9�������)

protected:
	CRITICAL_SECTION m_cs;						// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;							// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectFont();															// DirectFont Construction Function(~DirectFont���캯��)
	~DirectFont();															// DirectFont Destruction  Function(~DirectFont��������)

	DirectFont(IDirect3DDevice9* pD3D9Device, bool bSafe = true);			// DirectFont Construction Function(~DirectFont���캯��)(Overload + 1)
	DirectFont(const DirectFont&);											// DirectFont Construction Function(~DirectFont�������캯��)

public:
	const DirectFont& operator=(const DirectFont&);							// DirectFont Operator= Function(~DirectFont�������캯��)

public:
	IDirect3DDevice9*					DIRECTFONT_CALLMETHOD		GetDevice() const;															// DirectFont Get D3D9 Device(~DirectFont��ȡD3D9�豸)
	ID3DXFont*							DIRECTFONT_CALLMETHOD		GetFont() const;															// DirectFont Get D3D9 Font(~DirectFont��ȡD3D9����)

public:
	HRESULT								DIRECTFONT_CALLMETHOD		Create();																	// DirectFont Create Font(~DirectFont��ʼ��)
	HRESULT								DIRECTFONT_CALLMETHOD		Create(int nFontSize);														// DirectFont Create Font(~DirectFont��ʼ��)(Overload + 1)
	HRESULT								DIRECTFONT_CALLMETHOD		Create(int nFontSize, LPWSTR lpszFontType);									// DirectFont Create Font(~DirectFont��ʼ��)(Overload + 2)

	HRESULT								DIRECTFONT_CALLMETHOD		Reset();																	// DirectFont Reset D3DX Font(~DirectFont����D3DX����)(��ʧ�豸����)

	void								DIRECTFONT_CALLMETHOD		Draw(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color);			// DirectFont Draw Text(DirectFont����)
	void								DIRECTFONT_CALLMETHOD		DrawA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color);			// DirectFont Draw Text(DirectFont����)
	void								DIRECTFONT_CALLMETHOD		DrawW(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color);			// DirectFont Draw Text(DirectFont����)

};

#endif