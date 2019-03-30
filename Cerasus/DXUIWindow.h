/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIWindow.h
* @brief	This File is DXUI Project File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-13	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __DXUIWINDOW_H_
#define __DXUIWINDOW_H_

// Include DXUI Common Header File
#include "DXUICommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DXUIWINDOW_API	__declspec(dllexport)
#else
#define DXUIWINDOW_API	__declspec(dllimport)
#endif

#define DXUIWINDOW_CALLMETHOD	__stdcall

// Class Definition
class DXUIWINDOW_API CDXUIWindow
{
protected:
	HWND	m_hWnd;			// CDXUIWindow 窗口句柄
	WNDPROC	m_WndProc;		// CDXUIWindow 窗口消息回调
	bool	m_bSubClassed;	// CDXUIWindow 窗口类

public:
	CDXUIWindow();
	~CDXUIWindow();

	HWND	DXUIWINDOW_CALLMETHOD	GetHWND() const;								// CDXUIWindow 获取窗口句柄

	bool	DXUIWINDOW_CALLMETHOD	RegisterWindowClass(WORD wIcon = NULL);			// CDXUIWindow 注册窗口类
	bool	DXUIWINDOW_CALLMETHOD	RegisterWindowClassEx(WORD wIcon = NULL);		// CDXUIWindow 注册窗口类(Ex)

	HWND	DXUIWINDOW_CALLMETHOD	Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, const RECT rc, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL, WORD wIcon = NULL);

	HWND	DXUIWINDOW_CALLMETHOD	SubClass(HWND hWnd);							// CDXUIWindow 窗口子类化
	void	DXUIWINDOW_CALLMETHOD	UnSubClass();									// CDXUIWindow 窗口非子类化

	void	DXUIWINDOW_CALLMETHOD	ShowWindow(bool bShow = true, bool bTakeFocus = true);			// CDXUIWindow 显示窗口(非模态)
	UINT	DXUIWINDOW_CALLMETHOD	ShowModal();													// CDXUIWindow 显示窗口(模态)

protected:
	virtual	LPCTSTR	DXUIWINDOW_CALLMETHOD	GetWindowClassName() const;				// CDXUIWindow 获取窗口类名
	virtual LPCTSTR	DXUIWINDOW_CALLMETHOD	GetWindowClassNameEx() const;			// CDXUIWindow 获取窗口类名(Ex)
	virtual UINT	DXUIWINDOW_CALLMETHOD	GetClassStyle() const;					// CDXUIWindow 获取窗口样式

	virtual LRESULT DXUIWINDOW_CALLMETHOD	HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CDXUIWindow 窗口消息处理函数
	virtual void	DXUIWINDOW_CALLMETHOD	OnFinalMessage(HWND hWnd);												// CDXUIWindow 窗口销毁处理函数

	static	LRESULT	DXUIWINDOW_CALLMETHOD	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CDXUIWindow 窗口消息处理回调

};

#endif // !__DXUIWINDOW_H_
