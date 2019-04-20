/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraCheckBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-10	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURACHECKBOX_H_
#define __SAKURACHECKBOX_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraButton.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACHECKBOX_API	__declspec(dllexport)
#else
#define SAKURACHECKBOX_API	__declspec(dllimport)
#endif

#define	SAKURACHECKBOX_CALLMETHOD	__stdcall

// Class Definition
class SAKURACHECKBOX_API CSakuraCheckBox : public CSakuraButton
{
protected:
	bool	m_bChecked;
	RECT	m_rcButton;
	RECT	m_rcText;

protected:
	virtual	void	SAKURACHECKBOX_CALLMETHOD	SetCheckedInternal(bool bChecked, bool bFromInput);			// CSakuraCheckBox 设置内部复选

public:
	CSakuraCheckBox(CSakuraDialog* pDialog = NULL);							// CSakuraCheckBox 构造函数

	virtual void	SAKURACHECKBOX_CALLMETHOD	Render();					// CSakuraCheckBox 渲染控件

	virtual bool	SAKURACHECKBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraCheckBox 键盘消息处理
	virtual bool    SAKURACHECKBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraCheckBox 鼠标消息处理

	virtual void    SAKURACHECKBOX_CALLMETHOD	OnHotkey();					// CSakuraCheckBox 鼠标热键
	virtual BOOL    SAKURACHECKBOX_CALLMETHOD	ContainsPoint(POINT pt);	// CSakuraCheckBox 鼠标在控件区域
	virtual void    SAKURACHECKBOX_CALLMETHOD	UpdateRects();				// CSakuraCheckBox 更新控件区域

	bool			SAKURACHECKBOX_CALLMETHOD	GetChecked();				// CSakuraCheckBox 获取控件选中状态
	void			SAKURACHECKBOX_CALLMETHOD	SetChecked(bool bChecked);	// CSakuraCheckBox 设置控件选中状态

};

#endif // !__SAKURACHECKBOX_H_
