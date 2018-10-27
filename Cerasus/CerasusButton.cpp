/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusButton.cpp
* @brief	This File is CerasusButton DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-22	v1.00a	alopex	Create Project.
*/
#include "CerasusButton.h"

// CreasusUI 按钮控件(CCerasusButton)

//------------------------------------------------------------------
// @Function:	 CCerasusButton()
// @Purpose: CCerasusButton构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusButton::CCerasusButton()
{
	m_eType = CERASUS_CONTROL_BUTTON;

	m_bPressed = false;
	m_nHotkey = 0;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CCerasusButton渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSBUTTON_CALLMODE CCerasusButton::Render()
{
	
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CCerasusButton键盘响应函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSBUTTON_CALLMODE CCerasusButton::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CCerasusButton鼠标响应函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSBUTTON_CALLMODE CCerasusButton::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 OnHotkey()
// @Purpose: CCerasusButton鼠标热键
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSBUTTON_CALLMODE CCerasusButton::OnHotkey()
{
	
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CCerasusButton鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CERASUSBUTTON_CALLMODE CCerasusButton::ContainsPoint(POINT pt)
{
	return 0;
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CCerasusButton是否拥有焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSBUTTON_CALLMODE CCerasusButton::CanHaveFocus()
{
	return false;
}
