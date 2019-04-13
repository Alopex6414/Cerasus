/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		Cerasusfps.cpp
* @brief	This File is Cerasusfps Dynamic Link Library Project.
* @author	Alopex/Alice
* @version	v1.04a
* @date		2018-06-09	v1.00a	alopex	Create This File.
* @date		2018-06-22	v1.01a	alopex	Add Version Information.
* @date		2018-06-26	v1.02a	alopex	Modify Call Mode.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
* @date		2019-04-13	v1.04a	alopex	Add Notes.
*/
#include "Cerasusfps.h"

// Cerasusfps类用于绘制和显示当前游戏帧速率(fps)

//------------------------------------------------------------------
// @Function:	 Cerasusfps()
// @Purpose: Cerasusfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusfps::CCerasusfps() :
	m_pFont(NULL),
	m_ffps(0.0f)
{
	m_bThreadSafe = true;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section
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

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);				// Delete Critical Section
}

//---------------------------------------------------------------------
// @Function:	 Cerasusfps(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: Cerasusfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
CCerasusfps::CCerasusfps(IDirect3DDevice9* pD3D9Device, bool bSafe) :
	m_ffps(0.0f)
{
	m_bThreadSafe = true;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	m_pFont = new DirectFont(pD3D9Device);							// New DirectFont Object
}

//---------------------------------------------------------------------
// @Function:	 CCerasusfps(const CCerasusfps& Object)
// @Purpose: Cerasusfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
CCerasusfps::CCerasusfps(const CCerasusfps& Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	m_pFont = Object.m_pFont;
	m_ffps = Object.m_ffps;
}

//---------------------------------------------------------------------
// @Function:	 operator=(const CCerasusfps& Object)
// @Purpose: Cerasusfps运算符重载
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
const CCerasusfps& CCerasusfps::operator=(const CCerasusfps& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

		m_pFont = Object.m_pFont;
		m_ffps = Object.m_ffps;
	}

	return *this;
}

//---------------------------------------------------------------------
// @Function:	 GetFont() const
// @Purpose: Cerasusfps获取DirectFont类
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
DirectFont* CERASUSFPS_CALLMETHOD CCerasusfps::GetFont() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pFont;
}

//------------------------------------------------------------------
// @Function:	 GetFps() const
// @Purpose: Cerasusfps获取fps帧速率
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::GetFps() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_ffps;
}

//---------------------------------------------------------------------
// @Function:	Create()
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::Create()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->Create();

	return hr;
}

//---------------------------------------------------------------------
// @Function:	Create(int nFontSize)
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::Create(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->Create(nFontSize);

	return hr;
}

//---------------------------------------------------------------------
// @Function:	Create(int nFontSize, LPWSTR lpszFontType)
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::Create(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->Create(nFontSize, lpszFontType);

	return hr;
}

//------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: Cerasusfps初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSFPS_CALLMETHOD CCerasusfps::Reset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	hr = m_pFont->Reset();

	return hr;
}

//------------------------------------------------------------------
// @Function:	 CalculateFps()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::CalculateFps()
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
// @Function:	 CalculateFpsEx()
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::CalculateFpsEx()
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
// @Function:	 CalculateFpsEx(float fTimeDelta)
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSFPS_CALLMETHOD CCerasusfps::CalculateFpsEx(float fTimeDelta)
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
// @Function:	 CalculateFpsEx(float* pfps)
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::CalculateFpsEx(float* pfps)
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
// @Function:	 CalculateFpsEx(float fTimeDelta, float* pfps)
// @Purpose: Cerasusfps计算FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::CalculateFpsEx(float fTimeDelta, float* pfps)
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
// @Function:	 DrawFps(HWND hWnd)
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::DrawFps(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->Draw(hWnd, fpsArr, DX_FONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------
// @Function:	 DrawFps(HWND hWnd, DWORD Format)
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::DrawFps(HWND hWnd, DWORD Format)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->Draw(hWnd, fpsArr, Format, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------
// @Function:	 DrawFps(HWND hWnd, DWORD Format, D3DCOLOR Color)
// @Purpose: Cerasusfps绘制FPS
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSFPS_CALLMETHOD CCerasusfps::DrawFps(HWND hWnd, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_ffps);
	m_pFont->Draw(hWnd, fpsArr, Format, Color);
}
