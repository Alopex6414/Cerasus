/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraEditBox.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-12-04	v1.00a	alopex	Create Project.
*/
#include "SakuraEditBox.h"

// SakuraGUI 编辑框派生类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraEditBox()
// @Purpose: CSakuraEditBox构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraEditBox::CSakuraEditBox(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_EDITBOX;
	m_pDialog = pDialog;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraEditBox()
// @Purpose: CSakuraEditBox析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraEditBox::~CSakuraEditBox()
{
}