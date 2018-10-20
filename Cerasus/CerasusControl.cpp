/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CreasusControl.cpp
* @brief	This File is CreasusControl DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "CerasusControl.h"

// CreasusUI 控件基类(CreasusControl)

//------------------------------------------------------------------
// @Function:	 CCerasusControl()
// @Purpose: CCerasusControl构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl::CCerasusControl()
{
	m_nX = 0;
	m_nY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_bEnabled = true;
	m_bVisible = true;
	m_bMouseOver = false;
	m_bHasFocus = false;
	m_bIsDefault = false;

	m_nID = 0;
	m_nIndex = 0;
	m_pUserData = NULL;
	m_eType = CERASUS_CONTROL_BUTTON;

	m_Element = NULL;

	ZeroMemory(&m_rcBoundingBox, sizeof(m_rcBoundingBox));
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusControl()
// @Purpose: CCerasusControl析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl::~CCerasusControl()
{
	SAFE_DELETE(m_Element);
}

//------------------------------------------------------------------
// @Function:	 OnInit()
// @Purpose: CCerasusControl初始化控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSCONTROL_CALLMODE CCerasusControl::OnInit()
{
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CCerasusControl刷新控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::Refresh()
{
	m_bMouseOver = false;
	m_bHasFocus = false;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CCerasusControl渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::Render()
{
	
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CCerasusControl消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CCerasusControl键盘消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CCerasusControl鼠标消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CCerasusControl是否获取焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::CanHaveFocus()
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 OnFocusIn()
// @Purpose: CCerasusControl设置焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::OnFocusIn()
{
	m_bHasFocus = true;
}

//------------------------------------------------------------------
// @Function:	 OnFocusOut()
// @Purpose: CCerasusControl丢失焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::OnFocusOut()
{
	m_bHasFocus = false;
}

//------------------------------------------------------------------
// @Function:	 OnMouseEnter()
// @Purpose: CCerasusControl鼠标进入
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::OnMouseEnter()
{
	m_bMouseOver = true;
}

//------------------------------------------------------------------
// @Function:	 OnMouseLeave()
// @Purpose: CCerasusControl鼠标离开
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::OnMouseLeave()
{
	m_bMouseOver = false;
}

//------------------------------------------------------------------
// @Function:	 OnHotkey()
// @Purpose: CCerasusControl鼠标进入
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::OnHotkey()
{
	
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CCerasusControl鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CERASUSCONTROL_CALLMODE CCerasusControl::ContainsPoint(POINT pt)
{
	return PtInRect(&m_rcBoundingBox, pt);
}

//------------------------------------------------------------------
// @Function:	 SetEnabled()
// @Purpose: CCerasusControl设置控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

//------------------------------------------------------------------
// @Function:	 GetEnabled()
// @Purpose: CCerasusControl获取控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::GetEnabled()
{
	return m_bEnabled;
}

//------------------------------------------------------------------
// @Function:	 SetVisible()
// @Purpose: CCerasusControl设置控件可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

//------------------------------------------------------------------
// @Function:	 GetVisible()
// @Purpose: CCerasusControl获取控件可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSCONTROL_CALLMODE CCerasusControl::GetVisible()
{
	return m_bVisible;
}

//------------------------------------------------------------------
// @Function:	 GetType()
// @Purpose: CCerasusControl获取类型
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSCONTROL_CALLMODE CCerasusControl::GetType() const
{
	return m_eType;
}

//------------------------------------------------------------------
// @Function:	 GetID()
// @Purpose: CCerasusControl获取控件ID
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CERASUSCONTROL_CALLMODE CCerasusControl::GetID() const
{
	return m_nID;
}

//------------------------------------------------------------------
// @Function:	 SetID()
// @Purpose: CCerasusControl设置控件ID
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetID(int nID)
{
	m_nID = nID;
}

//------------------------------------------------------------------
// @Function:	 SetLocation()
// @Purpose: CCerasusControl设置控件坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetLocation(int x, int y)
{
	m_nX = x;
	m_nY = y;
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 SetSize()
// @Purpose: CCerasusControl设置控件形状
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 SetHotkey()
// @Purpose: CCerasusControl设置虚拟键值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetHotkey(UINT nHotkey)
{
	m_nHotkey = nHotkey;
}

//------------------------------------------------------------------
// @Function:	 GetHotkey()
// @Purpose: CCerasusControl获取虚拟键值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSCONTROL_CALLMODE CCerasusControl::GetHotkey()
{
	return m_nHotkey;
}

//------------------------------------------------------------------
// @Function:	 SetUserData()
// @Purpose: CCerasusControl设置用户数据
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::SetUserData(void * pUserData)
{
	m_pUserData = pUserData;
}

//------------------------------------------------------------------
// @Function:	 GetUserData()
// @Purpose: CCerasusControl获取用户数据
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void *CERASUSCONTROL_CALLMODE CCerasusControl::GetUserData()
{
	return m_pUserData;
}

//------------------------------------------------------------------
// @Function:	 GetElement()
// @Purpose: CCerasusControl获取元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusElement *CERASUSCONTROL_CALLMODE CCerasusControl::GetElement()
{
	return m_Element;
}

//------------------------------------------------------------------
// @Function:	 SetElement()
// @Purpose: CCerasusControl设置元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSCONTROL_CALLMODE CCerasusControl::SetElement(CCerasusElement* pElement)
{
	if (pElement == NULL)
	{
		return E_INVALIDARG;
	}

	m_Element = new CCerasusElement(*pElement);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CCerasusControl更新控件矩形
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSCONTROL_CALLMODE CCerasusControl::UpdateRects()
{
	SetRect(&m_rcBoundingBox, m_nX, m_nY, m_nX + m_nWidth, m_nY + m_nHeight);
}
