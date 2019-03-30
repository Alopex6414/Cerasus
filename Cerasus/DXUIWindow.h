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
	HWND	m_hWnd;			// CDXUIWindow ���ھ��
	WNDPROC	m_WndProc;		// CDXUIWindow ������Ϣ�ص�
	bool	m_bSubClassed;	// CDXUIWindow ������

public:
	CDXUIWindow();
	~CDXUIWindow();

	HWND	DXUIWINDOW_CALLMETHOD	GetHWND() const;								// CDXUIWindow ��ȡ���ھ��

	bool	DXUIWINDOW_CALLMETHOD	RegisterWindowClass(WORD wIcon = NULL);			// CDXUIWindow ע�ᴰ����
	bool	DXUIWINDOW_CALLMETHOD	RegisterWindowClassEx(WORD wIcon = NULL);		// CDXUIWindow ע�ᴰ����(Ex)

	HWND	DXUIWINDOW_CALLMETHOD	Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, const RECT rc, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL, WORD wIcon = NULL);
	HWND	DXUIWINDOW_CALLMETHOD	CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL, WORD wIcon = NULL);

	HWND	DXUIWINDOW_CALLMETHOD	SubClass(HWND hWnd);							// CDXUIWindow �������໯
	void	DXUIWINDOW_CALLMETHOD	UnSubClass();									// CDXUIWindow ���ڷ����໯

	void	DXUIWINDOW_CALLMETHOD	ShowWindow(bool bShow = true, bool bTakeFocus = true);			// CDXUIWindow ��ʾ����(��ģ̬)
	UINT	DXUIWINDOW_CALLMETHOD	ShowModal();													// CDXUIWindow ��ʾ����(ģ̬)

protected:
	virtual	LPCTSTR	DXUIWINDOW_CALLMETHOD	GetWindowClassName() const;				// CDXUIWindow ��ȡ��������
	virtual LPCTSTR	DXUIWINDOW_CALLMETHOD	GetWindowClassNameEx() const;			// CDXUIWindow ��ȡ��������(Ex)
	virtual UINT	DXUIWINDOW_CALLMETHOD	GetClassStyle() const;					// CDXUIWindow ��ȡ������ʽ

	virtual LRESULT DXUIWINDOW_CALLMETHOD	HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CDXUIWindow ������Ϣ������
	virtual void	DXUIWINDOW_CALLMETHOD	OnFinalMessage(HWND hWnd);												// CDXUIWindow �������ٴ�����

	static	LRESULT	DXUIWINDOW_CALLMETHOD	WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CDXUIWindow ������Ϣ����ص�

};

#endif // !__DXUIWINDOW_H_
