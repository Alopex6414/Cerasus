/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraRadioButton.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-13	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURARADIOBUTTON_H_
#define __SAKURARADIOBUTTON_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraCheckBox.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURARADIOBUTTON_API	__declspec(dllexport)
#else
#define SAKURARADIOBUTTON_API	__declspec(dllimport)
#endif

#define	SAKURARADIOBUTTON_CALLMETHOD	__stdcall

// Class Definition
class SAKURARADIOBUTTON_API CSakuraRadioButton : public CSakuraCheckBox
{
protected:
	UINT m_nButtonGroup;

protected:
	virtual void	SAKURARADIOBUTTON_CALLMETHOD	SetCheckedInternal(bool bChecked, bool bClearGroup, bool bFromInput);			// CSakuraRadioButton 内部选中控件

public:
	CSakuraRadioButton(CSakuraDialog* pDialog = NULL);			// CSakuraRadioButton 构造函数

	virtual bool	SAKURARADIOBUTTON_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraRadioButton 键盘消息处理
	virtual bool    SAKURARADIOBUTTON_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraRadioButton 鼠标消息处理

	virtual void    SAKURARADIOBUTTON_CALLMETHOD	OnHotkey();															// CSakuraRadioButton 鼠标热键
	void			SAKURARADIOBUTTON_CALLMETHOD	SetChecked(bool bChecked, bool bClearGroup = true);					// CSakuraRadioButton 设置控件选中
	void			SAKURARADIOBUTTON_CALLMETHOD	SetButtonGroup(UINT nButtonGroup);									// CSakuraRadioButton 设置控件组别
	UINT			SAKURARADIOBUTTON_CALLMETHOD	GetButtonGroup();													// CSakuraRadioButton 获取控件组别

};



#endif // !__SAKURARADIOBUTTON_H_
