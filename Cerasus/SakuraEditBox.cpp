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

// SakuraGUI �༭��������(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraEditBox()
// @Purpose: CSakuraEditBox���캯��
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
// @Purpose: CSakuraEditBox��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraEditBox::~CSakuraEditBox()
{
}