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

// Macro Definition
#define UI_WNDSTYLE_CONTAINER	(0)
#define UI_WNDSTYLE_FRAME		(WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD		(WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG		(WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME	(WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG	(WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER (0)
#define UI_CLASSSTYLE_FRAME     (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD		(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG    (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)

#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

// Class Definition
class DXUI_API CDXUIWindow
{
protected:
	HWND m_hWnd;					// CDXUIWindow ���ھ��
	WNDPROC m_OldWndProc;			// CDXUIWindow ������Ϣ����ص�
	bool m_bSubclassed;				// CDXUIWindow �����Ƿ�Ϊ�Ӵ��ڱ�־

public:
	CDXUIWindow();					// CDXUIWindow ���캯��
	~CDXUIWindow();					// CDXUIWindow ��������

	HWND GetHWND() const;			// CDXUIWindow ��ȡ���ھ��
	operator HWND() const;			// CDXUIWindow ��ȡ���ھ��

	bool RegisterWindowClass();		// CDXUIWindow ע�ᴰ����
	bool RegisterSuperclass();		// CDXUIWindow ע�ᴰ����Ex

	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
	HWND CreateDXUIWindow(HWND hwndParent, LPCTSTR pstrWindowName, DWORD dwStyle = 0, DWORD dwExStyle = 0);
	HWND Subclass(HWND hWnd);
	void Unsubclass();
	void ShowWindow(bool bShow = true, bool bTakeFocus = true);
	UINT ShowModal();
	void Close(UINT nRet = IDOK);
	void CenterWindow();
	void SetIcon(UINT nRes);

protected:
	virtual	LPCTSTR	GetWindowClassName() const = 0;			// CDXUIWindow ��ȡ��������
	virtual	LPCTSTR	GetSuperClassName() const;				// CDXUIWindow ��ȡ��������Ex
	virtual	UINT	GetClassStyle() const;					// CDXUIWindow ��ȡ��������

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);							// CDXUIWindow ��Ϣ������
	virtual void	OnFinalMessage(HWND hWnd);														// CDXUIWindow ��Ϣ��������

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CDXUIWindow ������Ϣ������
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		// CDXUIWindow �ؼ���Ϣ������

};

#endif // !__DXUIBASE_H_
