/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusControl.h
* @brief	This File is CerasusControl DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSCONTROL_H_
#define __CERASUSCONTROL_H_

//Include CerasusUI Common Header File
#include "CerasusUICommon.h"
#include "CerasusElement.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSCONTROL_API	__declspec(dllexport)
#else
#define CERASUSCONTROL_API	__declspec(dllimport)
#endif

#define CERASUSCONTROL_CALLMODE	__stdcall

//Class Definition
class CERASUSCONTROL_API CCerasusControl
{
public:
	int m_nX;					// CCerasusControl 控件X坐标
	int m_nY;					// CCerasusControl 控件Y坐标
	int m_nWidth;				// CCerasusControl 控件宽度
	int m_nHeight;				// CCerasusControl 控件高度

	bool m_bVisible;			// CCerasusControl 控件是否可见(true:显示/false:隐藏)
	bool m_bMouseOver;			// CCerasusControl 鼠标指针在控件上(true:是/false:否)
	bool m_bHasFocus;			// CCerasusControl 控件是否拥有输入焦点(true:是/false:否)
	bool m_bIsDefault;			// CCerasusControl 控件是否是默认控件(true:是/false:否)

	//CDXUTDialog* m_pDialog;    // CCerasusControl Parent container
	UINT m_nIndex;              // CCerasusControl 控件列表中控件索引

	CCerasusElement* m_Element;	// CCerasusControl 控件渲染元素

protected:
	int m_nID;						// CCerasusControl 控件序号
	CERASUS_CONTROL_TYPE m_eType;	// CCerasusControl 控件类型

	UINT m_nHotkey;					// CCerasusControl 虚拟按键编码
	LPVOID m_pUserData;				// CCerasusControl 用户数据地址

	bool m_bEnabled;				// CCerasusControl 控件是否使能(true:是/false:否)
	RECT m_rcBoundingBox;			// CCerasusControl 控件使能区域

protected:
	virtual void	CERASUSCONTROL_CALLMODE UpdateRects();				// CCerasusControl 更新控件矩形

public:
	CCerasusControl();				// CCerasusControl 构造函数
	virtual ~CCerasusControl();		// CCerasusControl 析构函数

	virtual HRESULT CERASUSCONTROL_CALLMODE OnInit();					// CCerasusControl 初始化控件
	virtual void	CERASUSCONTROL_CALLMODE Refresh();					// CCerasusControl 刷新控件
	virtual void	CERASUSCONTROL_CALLMODE Render();					// CCerasusControl 渲染控件

	virtual bool	CERASUSCONTROL_CALLMODE MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CCerasusControl 消息处理
	virtual bool	CERASUSCONTROL_CALLMODE HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);	// CCerasusControl 键盘消息处理
	virtual bool	CERASUSCONTROL_CALLMODE HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CCerasusControl 鼠标消息处理

	virtual bool	CERASUSCONTROL_CALLMODE	CanHaveFocus();				// CCerasusControl 是否拥有焦点
	virtual void	CERASUSCONTROL_CALLMODE	OnFocusIn();				// CCerasusControl 设置焦点
	virtual void	CERASUSCONTROL_CALLMODE	OnFocusOut();				// CCerasusControl 丢失焦点
	virtual void	CERASUSCONTROL_CALLMODE	OnMouseEnter();				// CCerasusControl 鼠标进入
	virtual void	CERASUSCONTROL_CALLMODE OnMouseLeave();				// CCerasusControl 鼠标离开
	virtual void	CERASUSCONTROL_CALLMODE OnHotkey();					// CCerasusControl 鼠标热键
	virtual BOOL	CERASUSCONTROL_CALLMODE ContainsPoint(POINT pt);	// CCerasusControl 鼠标落在控件内
	virtual void	CERASUSCONTROL_CALLMODE SetEnabled(bool bEnabled);	// CCerasusControl 设置控件使能
	virtual bool	CERASUSCONTROL_CALLMODE GetEnabled();				// CCerasusControl 获取控件使能
	virtual void	CERASUSCONTROL_CALLMODE SetVisible(bool bVisible);	// CCerasusControl 设置控件可见
	virtual bool	CERASUSCONTROL_CALLMODE GetVisible();				// CCerasusControl 获取控件可见
	UINT			CERASUSCONTROL_CALLMODE GetType() const;			// CCerasusControl 获取控件类型
	int				CERASUSCONTROL_CALLMODE GetID() const;				// CCerasusControl 获取控件ID
	void			CERASUSCONTROL_CALLMODE SetID(int nID);				// CCerasusControl 设置控件ID
	void			CERASUSCONTROL_CALLMODE SetLocation(int x, int y);	// CCerasusControl 设置控件坐标
	void			CERASUSCONTROL_CALLMODE SetSize(int width, int height);			// CCerasusControl 设置控件形状
	void			CERASUSCONTROL_CALLMODE SetHotkey(UINT nHotkey);	// CCerasusControl 设置虚拟键值
	UINT			CERASUSCONTROL_CALLMODE GetHotkey();				// CCerasusControl 获取虚拟键值
	void			CERASUSCONTROL_CALLMODE SetUserData(void* pUserData);			// CCerasusControl 设置用户数据
	void*			CERASUSCONTROL_CALLMODE GetUserData();				// CCerasusControl 获取用户数据
	CCerasusElement*CERASUSCONTROL_CALLMODE GetElement();				// CCerasusControl 获取渲染元素
	HRESULT			CERASUSCONTROL_CALLMODE SetElement(CCerasusElement* pElement);	// CCerasusControl 设置渲染元素

};


#endif // !__CERASUSCONTROL_H_

