/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		Cerasusfps.h
* @brief	This File is Cerasusfps Dynamic Link Library Project.
* @author	Alopex/Alice
* @version	v1.04a
* @date		2018-06-09	v1.00a	alopex	Create This File.
* @date		2018-06-22	v1.01a	alopex	Add Version Information.
* @date		2018-06-26	v1.02a	alopex	Modify Call Mode.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
* @date		2019-04-13	v1.04a	alopex	Add Notes.
*/
#pragma once

#ifndef __CERASUSFPS_H_
#define __CERASUSFPS_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectThreadSafe.h"

// Macro Definition
#ifdef CERASUS_EXPORTS
#define CERASUSFPS_API	__declspec(dllexport)
#else
#define CERASUSFPS_API	__declspec(dllimport)
#endif

#define CERASUSFPS_CALLMETHOD	__stdcall

// Class Definition
class CERASUSFPS_API CCerasusfps
{
private:
	DirectFont* m_pFont;			// Cerasusfps Font(~Cerasusfps字体样式)

private:
	float m_ffps;					// Cerasusfps FPS(~Cerasusfps帧速率)

protected:
	CRITICAL_SECTION m_cs;			// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;				// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	CCerasusfps();																	// Cerasusfps Construction Function(~Cerasusfps构造函数)
	~CCerasusfps();																	// Cerasusfps Destructoion Function(~Cerasusfps析构函数)

	CCerasusfps(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// Cerasusfps Construction Function(~Cerasusfps构造函数)(Overload + 1)
	CCerasusfps(const CCerasusfps&);												// Cerasusfps Construction Function(~Cerasusfps拷贝构造函数)

public:
	const CCerasusfps& operator=(const CCerasusfps&);								// Cerasusfps Operator= Function(~Cerasusfps拷贝构造函数)

public:
	DirectFont*					CERASUSFPS_CALLMETHOD		GetFont() const;		// Cerasusfps Get DirectFont(~Cerasusfps获取DirectFont类)
	float						CERASUSFPS_CALLMETHOD		GetFps() const;			// Cerasusfps Get FPS(~Cerasusfps获取fps帧速率)

public:
	HRESULT						CERASUSFPS_CALLMETHOD		Create();														// Cerasusfps Initialize(~Cerasusfps初始化)
	HRESULT						CERASUSFPS_CALLMETHOD		Create(int nFontSize);											// Cerasusfps Initialize(~Cerasusfps初始化)(Overload + 1)
	HRESULT						CERASUSFPS_CALLMETHOD		Create(int nFontSize, LPWSTR lpszFontType);						// Cerasusfps Initialize(~Cerasusfps初始化)(Overload + 2)

	HRESULT						CERASUSFPS_CALLMETHOD		Reset();														// Cerasusfps Reset Device(~Cerasusfps Reset)

	void						CERASUSFPS_CALLMETHOD		CalculateFps();													// Cerasusfps Calculate Fps(~Cerasusfps fps)
	
	float						CERASUSFPS_CALLMETHOD		CalculateFpsEx();												// Cerasusfps Calculate Fps(~Cerasusfps fps Ex)
	float						CERASUSFPS_CALLMETHOD		CalculateFpsEx(float fTimeDelta);								// Cerasusfps Calculate Fps(~Cerasusfps fps Ex)(Overload + 1)
	void						CERASUSFPS_CALLMETHOD		CalculateFpsEx(float* pfps);									// Cerasusfps Calculate Fps(~Cerasusfps fps Ex)(Overload + 2)
	void						CERASUSFPS_CALLMETHOD		CalculateFpsEx(float fTimeDelta, float* pfps);					// Cerasusfps Calculate Fps(~Cerasusfps fps Ex)(Overload + 3)

	void						CERASUSFPS_CALLMETHOD		DrawFps(HWND hWnd);												// Cerasusfps Draw Fps(~Cerasusfps绘制fps)
	void						CERASUSFPS_CALLMETHOD		DrawFps(HWND hWnd, DWORD Format);								// Cerasusfps Draw Fps(~Cerasusfps绘制fps)(Overload + 1)
	void						CERASUSFPS_CALLMETHOD		DrawFps(HWND hWnd, DWORD Format, D3DCOLOR Color);				// Cerasusfps Draw Fps(~Cerasusfps绘制fps)(Overload + 2)

};


#endif // !__CERASUSFPS_H_

