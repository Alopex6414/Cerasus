/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraStatic.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURASTATIC_H_
#define __SAKURASTATIC_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASTATIC_API	__declspec(dllexport)
#else
#define SAKURASTATIC_API	__declspec(dllimport)
#endif

#define	SAKURASTATIC_CALLMETHOD	__stdcall

// Class Definition
class SAKURASTATIC_API CSakuraStatic : public CSakuraControl
{
protected:
	WCHAR		m_strText[MAX_PATH];			// CSakuraStatic 静态控件文本
	DWORD		m_dwFormat;						// CSakuraStatic 静态控件格式
	D3DCOLOR	m_dwColor;						// CSakuraStatic 静态控件颜色

public:
	CSakuraStatic(CSakuraDialog* pDialog = NULL);							// CSakuraStatic 构造函数

	LPCWSTR			SAKURASTATIC_CALLMETHOD	GetText();						// CSakuraStatic 获取文本
	HRESULT			SAKURASTATIC_CALLMETHOD SetText(LPCWSTR strText);		// CSakuraStatic 设置文本
	DWORD			SAKURASTATIC_CALLMETHOD	GetFormat();					// CSakuraStatic 获取格式
	HRESULT			SAKURASTATIC_CALLMETHOD SetFormat(DWORD dwFormat);		// CSakuraStatic 设置格式
	D3DCOLOR		SAKURASTATIC_CALLMETHOD	GetColor();						// CSakuraStatic 获取颜色
	HRESULT			SAKURASTATIC_CALLMETHOD	SetColor(D3DCOLOR dwColor);		// CSakuraStatic 设置颜色

	virtual BOOL    SAKURASTATIC_CALLMETHOD	ContainsPoint(POINT pt);		// CSakuraStatic 鼠标落在控件内
	virtual void	SAKURASTATIC_CALLMETHOD	Render();						// CSakuraStatic 渲染控件

};


#endif // !__SAKURASTATIC_H_

