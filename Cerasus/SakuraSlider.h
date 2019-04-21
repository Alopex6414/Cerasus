/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraSlider.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-30	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURASLIDER_H_
#define __SAKURASLIDER_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASLIDER_API	__declspec(dllexport)
#else
#define SAKURASLIDER_API	__declspec(dllimport)
#endif

#define	SAKURASLIDER_CALLMETHOD	__stdcall

// Class Definition
class SAKURASLIDER_API CSakuraSlider : public CSakuraControl
{
protected:
	int	m_nValue;			// CSakuraSlider 当前值

	int m_nMin;				// CSakuraSlider 最小值
	int m_nMax;				// CSakuraSlider 最大值

	int m_nDragX;			// CSakuraSlider 拖拽X坐标
	int m_nDragOffset;		// CSakuraSlider 拖拽位置偏移
	int m_nButtonX;			// CSakuraSlider 按钮X坐标

	bool m_bPressed;		// CSakuraSlider 滑块是否被按压
	RECT m_rcButton;		// CSakuraSlider 滑块按钮区域

protected:
	void	SAKURASLIDER_CALLMETHOD	SetValueInternal(int nValue, bool bFromInput);			// CSakuraSlider 设置值
	int		SAKURASLIDER_CALLMETHOD	ValueFromPos(int x);									// CSakuraSlider 坐标值

public:
	CSakuraSlider(CSakuraDialog* pDialog = NULL);																// CSakuraSlider 构造函数

	virtual BOOL	SAKURASLIDER_CALLMETHOD	ContainsPoint(POINT pt);											// CSakuraSlider 鼠标是否落在控件内部
	virtual bool    SAKURASLIDER_CALLMETHOD	CanHaveFocus();														// CSakuraSlider 是否拥有焦点

	virtual bool    SAKURASLIDER_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraSlider 键盘消息响应
	virtual bool    SAKURASLIDER_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraSlider 鼠标消息响应

	virtual void    SAKURASLIDER_CALLMETHOD	UpdateRects();														// CSakuraSlider 更新控件区域
	virtual void    SAKURASLIDER_CALLMETHOD	Render();															// CSakuraSlider 渲染控件

	void            SAKURASLIDER_CALLMETHOD	SetValue(int nValue);												// CSakuraSlider 设置滑块当前值
	int             SAKURASLIDER_CALLMETHOD	GetValue() const;													// CSakuraSlider 获取滑块当前值
	void            SAKURASLIDER_CALLMETHOD	GetRange(int& nMin, int& nMax) const;								// CSakuraSlider 获取滑块范围
	void            SAKURASLIDER_CALLMETHOD	SetRange(int nMin, int nMax);										// CSakuraSlider 设置滑块范围

};


#endif // !__SAKURASLIDER_H_
