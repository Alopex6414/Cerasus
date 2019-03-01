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
	HWND m_hWnd;					// CDXUIWindow ���ھ��
	WNDPROC m_OldWndProc;			// CDXUIWindow ������Ϣ����ص�
	bool m_bSubclassed;				// CDXUIWindow �����Ƿ�Ϊ�Ӵ��ڱ�־

public:
	CDXUIWindow();					// CDXUIWindow ���캯��
	~CDXUIWindow();					// CDXUIWindow ��������

	HWND GetHWND() const;			// CDXUIWindow ��ȡ���ھ��
	operator HWND() const;			// CDXUIWindow ��ȡ���ھ��

	bool RegisterWindowClass();		// CDXUIWindow ע�ᴰ����

protected:
	virtual	LPCTSTR	GetWindowClassName() const = 0;			// CDXUIWindow ��ȡ��������
	virtual	LPCTSTR	GetSuperClassName() const;				// CDXUIWindow ��ȡ��������Ex
	virtual	UINT	GetClassStyle() const;					// CDXUIWindow ��ȡ��������

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);							// CDXUIWindow ��Ϣ������
	virtual void	OnFinalMessage(HWND hWnd);														// CDXUIWindow ��Ϣ��������

	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CDXUIWindow ������Ϣ������
	static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		// CDXUIWindow �ؼ�

};

#endif // !__DXUIBASE_H_
