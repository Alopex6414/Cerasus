/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectFont.cpp
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
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectThreadSafe.h"

// DirectX9 Font Class(DirectX9 3D/2D文字绘制)

//------------------------------------------------------------------
// @Function:	 DirectFont()
// @Purpose: DirectFont构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont::DirectFont() :
	m_pD3D9Device(NULL),
	m_pD3D9Font(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectFont()
// @Purpose: DirectFont析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont::~DirectFont()
{
	SAFE_RELEASE(m_pD3D9Font);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//---------------------------------------------------------------------
// @Function:	 DirectFont(IDirect3DDevice9 * pD3D9Device, bool bSafe)
// @Purpose: DirectFont构造函数
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device	//D3D9绘制设备
// @Return: None
//---------------------------------------------------------------------
DirectFont::DirectFont(IDirect3DDevice9 * pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3D9Font(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectFont(const DirectFont & Object)
// @Purpose: DirectFont拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont::DirectFont(const DirectFont & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;
	m_pD3D9Font = Object.m_pD3D9Font;
}

//------------------------------------------------------------------
// @Function:	 operator=(const DirectFont & Object)
// @Purpose: DirectFont拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectFont & DirectFont::operator=(const DirectFont & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;
		m_pD3D9Font = Object.m_pD3D9Font;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 DirectFontGetDevice(void) const
// @Purpose: DirectFont获取D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9* DIRECTFONT_CALLMETHOD DirectFont::DirectFontGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectFontGetFont(void) const
// @Purpose: DirectFont获取D3D9字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXFont* DIRECTFONT_CALLMETHOD DirectFont::DirectFontGetFont(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Font;
}

//------------------------------------------------------------------
// @Function:	 DirectFontSetDevice(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectFont设置D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTFONT_CALLMETHOD DirectFont::DirectFontSetDevice(IDirect3DDevice9* pD3D9Device)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectFontSetFont(ID3DXFont* pD3DXFont)
// @Purpose: DirectFont设置D3D9字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTFONT_CALLMETHOD DirectFont::DirectFontSetFont(ID3DXFont* pD3DXFont)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Font = pD3DXFont;
}

//------------------------------------------------------------------
// @Function:	 DirectFontReset(void)
// @Purpose: DirectFont重置D3D9字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTFONT_CALLMETHOD DirectFont::DirectFontReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Font->OnLostDevice();
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(void)
// @Purpose: DirectFont初始化D3D9字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTFONT_CALLMETHOD DirectFont::DirectFontInit(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, 12, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3D9Font));

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(int nFontSize)
// @Purpose: DirectFont初始化D3D9字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTFONT_CALLMETHOD DirectFont::DirectFontInit(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3D9Font));

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: DirectFont初始化D3D9字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTFONT_CALLMETHOD DirectFont::DirectFontInit(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, lpszFontType, &m_pD3D9Font));
	
	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawText(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont绘制字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTFONT_CALLMETHOD DirectFont::DirectFontDrawText(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawText(NULL, lpcszStr, -1, &Rect, Format, Color);
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawTextA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont绘制字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTFONT_CALLMETHOD DirectFont::DirectFontDrawTextA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawTextA(NULL, lpcszStr, -1, &Rect, Format, Color);
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawTextW(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont绘制字体
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTFONT_CALLMETHOD DirectFont::DirectFontDrawTextW(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawTextW(NULL, lpcszStr, -1, &Rect, Format, Color);
}