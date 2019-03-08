/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIManager.cpp
* @brief	This File is DXUI Project Header File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-08	v1.00a	alopex	Create Project.
*/
#include "DXUIManager.h"

// CDXUIPaintManagerUI ��Ⱦ������

// Variable Definition
HINSTANCE CDXUIPaintManagerUI::m_hInstance = NULL;

//------------------------------------------------------------------
// @Function:	 CDXUIPaintManagerUI()
// @Purpose: CDXUIPaintManagerUI ���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIPaintManagerUI::CDXUIPaintManagerUI()
{
}

//------------------------------------------------------------------
// @Function:	 ~CDXUIPaintManagerUI()
// @Purpose: CDXUIPaintManagerUI ��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIPaintManagerUI::~CDXUIPaintManagerUI()
{
}

//------------------------------------------------------------------
// @Function:	 GetInstance()
// @Purpose: CDXUIPaintManagerUI ��ȡ����ʵ�����(hInstance)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HINSTANCE CDXUIPaintManagerUI::GetInstance()
{
	return m_hInstance;
}
