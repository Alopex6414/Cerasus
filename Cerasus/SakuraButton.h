/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraButton.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURABUTTON_H_
#define __SAKURABUTTON_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraStatic.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURABUTTON_API	__declspec(dllexport)
#else
#define SAKURABUTTON_API	__declspec(dllimport)
#endif

#define	SAKURABUTTON_CALLMETHOD	__stdcall

// Class Definition
class SAKURABUTTON_API CSakuraButton : public CSakuraStatic
{
protected:
	bool m_bPressed;			// CSakuraButton 按下状态

public:
	CSakuraButton(CSakuraDialog* pDialog = NULL);							// CSakuraButton 构造函数

	virtual void	SAKURABUTTON_CALLMETHOD	Render();						// CSakuraButton 渲染控件

	virtual bool	SAKURABUTTON_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraButton 键盘消息处理
	virtual bool	SAKURABUTTON_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraButton 鼠标消息处理

	virtual void	SAKURABUTTON_CALLMETHOD OnHotkey();						// CSakuraButton 鼠标热键
	virtual BOOL	SAKURABUTTON_CALLMETHOD ContainsPoint(POINT pt);		// CSakuraButton 鼠标落在控件内
	virtual bool	SAKURABUTTON_CALLMETHOD CanHaveFocus();					// CSakuraButton 是否拥有焦点

};



#endif // !__SAKURABUTTON_H_

