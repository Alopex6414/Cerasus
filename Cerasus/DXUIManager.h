/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIManager.h
* @brief	This File is DXUI Project Header File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-08	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __DXUIMANAGER_H_
#define __DXUIMANAGER_H_

// Include DXUI Common Header File
#include "DXUICommon.h"

// Class Definition
class DXUI_API CDXUIPaintManagerUI
{
private:
	static HINSTANCE m_hInstance;			// CDXUIPaintManagerUI 绘制窗口实例句柄(hInstance)

public:
	CDXUIPaintManagerUI();
	~CDXUIPaintManagerUI();

public:
	static HINSTANCE GetInstance();			// CDXUIPaintManagerUI 获取窗口实例句柄(hInstance)

};

#endif // !__DXUIMANAGER_H_

