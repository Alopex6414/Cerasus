/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Cerasusfps.cpp
* @brief	This File is Cerasusfps Dynamic Link Library Project.
* @author	alopex
* @version	v1.03a
* @date		2018-06-09	v1.00a	alopex	Create This File.
* @date		2018-06-22	v1.01a	alopex	Add Version Information.
* @date		2018-06-26	v1.02a	alopex	Modify Call Mode.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
*/
#include "Cerasusfps.h"

//Cerasusfps类用于绘制和显示当前游戏帧速率(fps)

//------------------------------------------------------------------
// @Function:	 Cerasusfps()
// @Purpose: Cerasusfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusfps::CCerasusfps()
{
	m_bThreadSafe = true;
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);

	m_pFont = NULL;
	m_ffps = 0.0f;
}

//------------------------------------------------------------------
// @Function:	 Cerasusfps()
// @Purpose: Cerasusfps析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusfps::~CCerasusfps()
{
	SAFE_DELETE(m_pFont);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);
}

//------------------------------------------------------------------
// @Function:	 Cerasusfps()
// @Purpose: Cerasusfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusfps::CCerasusfps(IDirect3DDevice9* pD3D9Device)
{
	m_bThreadSafe = true;
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);

	m_pFont = new DirectFont(pD3D9Device);
	m_ffps = 0.0f;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetFont()
// @Purpose: Cerasusfps获取字体类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont* CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetFont() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pFont;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetFps()
// @Purpose: Cerasusfps获取fps
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetFps() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_ffps;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsSetFont()
// @Purpose: Cerasusfps设置字体类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsSetFont(DirectFont* pFont)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pFont = pFont;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsReset()
// @Purpose: Cerasusfps重置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsReset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->DirectFontReset();
	return hr;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsInit()
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsInit(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->DirectFontInit(nFontSize);

	return hr;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsInit()
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsInit(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->DirectFontInit(nFontSize, lpszFontType);
	
	return hr;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetfps()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetfps()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		m_ffps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}

}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetfpsEx()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetfpsEx(float fTimeDelta, float * pfps)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;

	FrameCount++;
	TimeElapsed += fTimeDelta;

	if (TimeElapsed >= 1.0f)
	{
		*pfps = (float)(FrameCount * 1.0f / TimeElapsed);
		FrameCount = 0;
		TimeElapsed = 0.0f;
	}

}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetfpsEx()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetfpsEx(float * pfps)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		*pfps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}

}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetfpsEx()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetfpsEx(float fTimeDelta)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;
	float fps = 0.0f;

	FrameCount++;
	TimeElapsed += fTimeDelta;

	if (TimeElapsed >= 1.0f)
	{
		fps = (float)(FrameCount * 1.0f / TimeElapsed);
		FrameCount = 0;
		TimeElapsed = 0.0f;
	}

	return fps;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsGetfpsEx()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsGetfpsEx()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;
	float fps;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		fps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}

	return fps;
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsDrawfps()
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsDrawfps(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, DIRECTFONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsDrawfps()
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsDrawfps(HWND hWnd, DWORD Format)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, Format, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------
// @Function:	 CCerasusfpsDrawfps()
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSFPS_CALLMETHOD CCerasusfps::CCerasusfpsDrawfps(HWND hWnd, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, Format, Color);
}
