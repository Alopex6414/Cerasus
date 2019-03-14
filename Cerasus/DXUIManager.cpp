/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIManager.cpp
* @brief	This File is DXUI Project File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-13	v1.00a	alopex	Create Project.
*/
#include "DXUIManager.h"

// CDXUIManager 窗口管理类(UI)
HINSTANCE CDXUIManager::m_hInstance = NULL;

//------------------------------------------------------------------
// @Function:	 CDXUIManager()
// @Purpose: CDXUIManager构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIManager::CDXUIManager()
{
}

//------------------------------------------------------------------
// @Function:	 ~CDXUIManager()
// @Purpose: CDXUIManager析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIManager::~CDXUIManager()
{
}

//------------------------------------------------------------------
// @Function:	 GetInstance()
// @Purpose: CDXUIManager获取窗口实例句柄
// @Since: v1.00a
// @Para: None
// @Return: HINSTANCE(窗口实例句柄)
//------------------------------------------------------------------
HINSTANCE DXUIMANAGER_CALLMETHOD CDXUIManager::GetInstance()
{
	return m_hInstance;
}

//------------------------------------------------------------------
// @Function:	 SetInstance()
// @Purpose: CDXUIManager设置窗口实例句柄
// @Since: v1.00a
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: None
//------------------------------------------------------------------
void DXUIMANAGER_CALLMETHOD CDXUIManager::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}
