/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIBase.h
* @brief	This File is DXUI Project Header File.
* @author	alopex
* @version	v1.00a
* @date		2019-02-15	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __DXUIBASE_H_
#define __DXUIBASE_H_

// Include DXUI Common Header File
#include "DXUICommon.h"

// Class Definition
class DXUI_API CDXUIWindow
{
protected:
	HWND m_hWnd;					// CDXUIWindow 窗口句柄
	WNDPROC m_OldWndProc;			// CDXUIWindow 窗口消息处理回调
	bool m_bSubclassed;				// CDXUIWindow 窗口是否为子窗口标志

public:
	CDXUIWindow();					// CDXUIWindow 构造函数
	~CDXUIWindow();					// CDXUIWindow 析构函数

	HWND GetHWND() const;			// CDXUIWindow 获取窗口句柄
	operator HWND() const;			// CDXUIWindow 获取窗口句柄

	bool RegisterWindowClass();		// CDXUIWindow 注册窗口类

protected:
	virtual	LPCTSTR	GetWindowClassName() const = 0;			// CDXUIWindow 获取窗口类名
	virtual	LPCTSTR	GetSuperClassName() const;				// CDXUIWindow 获取窗口类名Ex
	virtual	UINT	GetClassStyle() const;					// CDXUIWindow 获取窗口类型

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CDXUIWindow 消息处理函数
	virtual void	OnFinalMessage(HWND hWnd);										// CDXUIWindow 消息结束函数

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !__DXUIBASE_H_
