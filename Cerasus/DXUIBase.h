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

};

#endif // !__DXUIBASE_H_
