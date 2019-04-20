/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraControl.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURACONTROL_H_
#define __SAKURACONTROL_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraElement.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACONTROL_API	__declspec(dllexport)
#else
#define SAKURACONTROL_API	__declspec(dllimport)
#endif

#define	SAKURACONTROL_CALLMETHOD	__stdcall

// Class Definition
class SAKURACONTROL_API CSakuraControl
{
public:
	int m_nX;					// CSakuraControl 控件X坐标
	int m_nY;					// CSakuraControl 控件Y坐标
	int m_nWidth;				// CSakuraControl 控件宽度
	int m_nHeight;				// CSakuraControl 控件高度

	bool m_bVisible;			// CSakuraControl 控件是否可见(true:显示/false:隐藏)
	bool m_bMouseOver;			// CSakuraControl 鼠标指针在控件上(true:是/false:否)
	bool m_bHasFocus;			// CSakuraControl 控件是否拥有输入焦点(true:是/false:否)
	bool m_bIsDefault;			// CSakuraControl 控件是否是默认控件(true:是/false:否)

	CSakuraDialog* m_pDialog;	// CSakuraControl 窗口控件容器
	UINT m_nIndex;              // CSakuraControl 控件列表中控件索引

	vector<CSakuraElement*> m_vecElements;								// CSakuraControl 控件渲染元素

protected:
	int m_nID;						// CSakuraControl 控件序号
	SAKURA_CONTROL_TYPE m_eType;	// CSakuraControl 控件类型

	UINT m_nHotkey;					// CSakuraControl 虚拟按键编码
	LPVOID m_pUserData;				// CSakuraControl 用户数据地址

	bool m_bEnabled;				// CSakuraControl 控件是否使能(true:是/false:否)
	RECT m_rcBoundingBox;			// CSakuraControl 控件使能区域

protected:
	virtual void	SAKURACONTROL_CALLMETHOD UpdateRects();				// CSakuraControl 更新控件矩形

public:
	CSakuraControl(CSakuraDialog* pDialog = NULL);						// CSakuraControl 构造函数
	virtual ~CSakuraControl();											// CSakuraControl 析构函数

	virtual HRESULT SAKURACONTROL_CALLMETHOD	OnInit();					// CSakuraControl 初始化控件
	virtual void	SAKURACONTROL_CALLMETHOD	Refresh();					// CSakuraControl 刷新控件
	virtual void	SAKURACONTROL_CALLMETHOD	Render();					// CSakuraControl 渲染控件

	virtual bool	SAKURACONTROL_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraControl 消息处理
	virtual bool	SAKURACONTROL_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraControl 键盘消息处理
	virtual bool	SAKURACONTROL_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraControl 鼠标消息处理

	vector<CSakuraElement*>&	SAKURACONTROL_CALLMETHOD	GetElements();	// CSakuraControl 获取控件渲染元素

	virtual bool	SAKURACONTROL_CALLMETHOD	CanHaveFocus();				// CSakuraControl 是否拥有焦点
	virtual void	SAKURACONTROL_CALLMETHOD	OnFocusIn();				// CSakuraControl 设置焦点
	virtual void	SAKURACONTROL_CALLMETHOD	OnFocusOut();				// CSakuraControl 丢失焦点
	virtual void	SAKURACONTROL_CALLMETHOD	OnMouseEnter();				// CSakuraControl 鼠标进入
	virtual void	SAKURACONTROL_CALLMETHOD	OnMouseLeave();				// CSakuraControl 鼠标离开
	virtual void	SAKURACONTROL_CALLMETHOD	OnHotkey();					// CSakuraControl 鼠标热键
	virtual BOOL	SAKURACONTROL_CALLMETHOD	ContainsPoint(POINT pt);	// CSakuraControl 鼠标落在控件内
	virtual void	SAKURACONTROL_CALLMETHOD	SetEnabled(bool bEnabled);	// CSakuraControl 设置控件使能
	virtual bool	SAKURACONTROL_CALLMETHOD	GetEnabled();				// CSakuraControl 获取控件使能
	virtual void	SAKURACONTROL_CALLMETHOD	SetVisible(bool bVisible);	// CSakuraControl 设置控件可见
	virtual bool	SAKURACONTROL_CALLMETHOD	GetVisible();				// CSakuraControl 获取控件可见
	UINT			SAKURACONTROL_CALLMETHOD	GetType() const;			// CSakuraControl 获取控件类型
	int				SAKURACONTROL_CALLMETHOD	GetID() const;				// CSakuraControl 获取控件ID
	void			SAKURACONTROL_CALLMETHOD	SetID(int nID);				// CSakuraControl 设置控件ID
	void			SAKURACONTROL_CALLMETHOD	SetLocation(int x, int y);	// CSakuraControl 设置控件坐标
	void			SAKURACONTROL_CALLMETHOD	SetSize(int width, int height);			// CSakuraControl 设置控件形状
	void			SAKURACONTROL_CALLMETHOD	SetHotkey(UINT nHotkey);	// CSakuraControl 设置虚拟键值
	UINT			SAKURACONTROL_CALLMETHOD	GetHotkey();				// CSakuraControl 获取虚拟键值
	void			SAKURACONTROL_CALLMETHOD	SetUserData(void* pUserData);			// CSakuraControl 设置用户数据
	void*			SAKURACONTROL_CALLMETHOD	GetUserData();				// CSakuraControl 获取用户数据
	CSakuraElement*&SAKURACONTROL_CALLMETHOD	GetElement(UINT iElement);	// CSakuraControl 获取渲染元素

};


#endif // !__SAKURACONTROL_H_

