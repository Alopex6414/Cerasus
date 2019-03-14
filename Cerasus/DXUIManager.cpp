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

// CDXUIManager ���ڹ�����(UI)
HINSTANCE CDXUIManager::m_hInstance = NULL;

//------------------------------------------------------------------
// @Function:	 CDXUIManager()
// @Purpose: CDXUIManager���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIManager::CDXUIManager()
{
}

//------------------------------------------------------------------
// @Function:	 ~CDXUIManager()
// @Purpose: CDXUIManager��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIManager::~CDXUIManager()
{
}

//------------------------------------------------------------------
// @Function:	 GetInstance()
// @Purpose: CDXUIManager��ȡ����ʵ�����
// @Since: v1.00a
// @Para: None
// @Return: HINSTANCE(����ʵ�����)
//------------------------------------------------------------------
HINSTANCE DXUIMANAGER_CALLMETHOD CDXUIManager::GetInstance()
{
	return m_hInstance;
}

//------------------------------------------------------------------
// @Function:	 SetInstance()
// @Purpose: CDXUIManager���ô���ʵ�����
// @Since: v1.00a
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Return: None
//------------------------------------------------------------------
void DXUIMANAGER_CALLMETHOD CDXUIManager::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}
