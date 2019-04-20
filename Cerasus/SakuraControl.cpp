/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraControl.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraControl.h"

// SakuraGUI 控件基类(UI)

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraControl更新控件矩形
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::UpdateRects()
{
	SetRect(&m_rcBoundingBox, m_nX, m_nY, m_nX + m_nWidth, m_nY + m_nHeight);
}

//------------------------------------------------------------------
// @Function:	 CSakuraControl()
// @Purpose: CSakuraControl构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraControl::CSakuraControl(CSakuraDialog * pDialog)
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
	m_pDialog = pDialog;
	m_eType = SAKURA_CONTROL_BUTTON;

	m_vecElements.clear();

	ZeroMemory(&m_rcBoundingBox, sizeof(m_rcBoundingBox));
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraControl()
// @Purpose: CSakuraControl析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraControl::~CSakuraControl()
{
	for (auto iter = m_vecElements.begin(); iter != m_vecElements.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecElements.clear();
}

//------------------------------------------------------------------
// @Function:	 OnInit()
// @Purpose: CSakuraControl初始化控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACONTROL_CALLMETHOD CSakuraControl::OnInit()
{
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CSakuraControl刷新控件状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::Refresh()
{
	m_bMouseOver = false;
	m_bHasFocus = false;

	for (auto iter = m_vecElements.begin(); iter != m_vecElements.end(); ++iter)
	{
		(*iter)->Refresh();
	}

}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraControl初始化控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::Render()
{
	
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraControl消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraControl键盘消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraControl鼠标消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 GetElements()
// @Purpose: CSakuraControl获取控件渲染元素向量
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
vector<CSakuraElement*>&SAKURACONTROL_CALLMETHOD CSakuraControl::GetElements()
{
	return m_vecElements;
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CSakuraControl是否获取焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::CanHaveFocus()
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 OnFocusIn()
// @Purpose: CSakuraControl设置焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnFocusIn()
{
	m_bHasFocus = true;
}

//------------------------------------------------------------------
// @Function:	 OnFocusOut()
// @Purpose: CSakuraControl丢失焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnFocusOut()
{
	m_bHasFocus = false;
}

//------------------------------------------------------------------
// @Function:	 OnMouseEnter()
// @Purpose: CSakuraControl鼠标进入
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnMouseEnter()
{
	m_bMouseOver = true;
}

//------------------------------------------------------------------
// @Function:	 OnMouseLeave()
// @Purpose: CSakuraControl鼠标离开
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnMouseLeave()
{
	m_bMouseOver = false;
}

//------------------------------------------------------------------
// @Function:	 OnHotkey()
// @Purpose: CSakuraControl鼠标热键
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnHotkey()
{
	
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraControl鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL SAKURACONTROL_CALLMETHOD CSakuraControl::ContainsPoint(POINT pt)
{
	return PtInRect(&m_rcBoundingBox, pt);
}

//------------------------------------------------------------------
// @Function:	 SetEnabled()
// @Purpose: CSakuraControl设置控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

//------------------------------------------------------------------
// @Function:	 GetEnabled()
// @Purpose: CSakuraControl获取控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::GetEnabled()
{
	return m_bEnabled;
}

//------------------------------------------------------------------
// @Function:	 SetVisible()
// @Purpose: CSakuraControl设置控件可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

//------------------------------------------------------------------
// @Function:	 GetVisible()
// @Purpose: CSakuraControl获取控件可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::GetVisible()
{
	return m_bVisible;
}

//------------------------------------------------------------------
// @Function:	 GetType()
// @Purpose: CSakuraControl获取类型
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT SAKURACONTROL_CALLMETHOD CSakuraControl::GetType() const
{
	return m_eType;
}

//------------------------------------------------------------------
// @Function:	 GetID()
// @Purpose: CSakuraControl获取控件ID
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURACONTROL_CALLMETHOD CSakuraControl::GetID() const
{
	return m_nID;
}

//------------------------------------------------------------------
// @Function:	 SetID()
// @Purpose: CSakuraControl设置控件ID
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetID(int nID)
{
	m_nID = nID;
}

//------------------------------------------------------------------
// @Function:	 SetLocation()
// @Purpose: CSakuraControl设置控件坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetLocation(int x, int y)
{
	m_nX = x;
	m_nY = y;
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 SetSize()
// @Purpose: CSakuraControl设置控件形状
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 SetHotkey()
// @Purpose: CSakuraControl设置虚拟键值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetHotkey(UINT nHotkey)
{
	m_nHotkey = nHotkey;
}

//------------------------------------------------------------------
// @Function:	 GetHotkey()
// @Purpose: CSakuraControl获取虚拟键值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT SAKURACONTROL_CALLMETHOD CSakuraControl::GetHotkey()
{
	return m_nHotkey;
}

//------------------------------------------------------------------
// @Function:	 SetUserData()
// @Purpose: CSakuraControl设置用户数据
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetUserData(void * pUserData)
{
	m_pUserData = pUserData;
}

//------------------------------------------------------------------
// @Function:	 GetUserData()
// @Purpose: CSakuraControl获取用户数据
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void *SAKURACONTROL_CALLMETHOD CSakuraControl::GetUserData()
{
	return m_pUserData;
}

//------------------------------------------------------------------
// @Function:	 GetElement()
// @Purpose: CSakuraControl获取渲染元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement *&SAKURACONTROL_CALLMETHOD CSakuraControl::GetElement(UINT iElement)
{
	for (auto i = m_vecElements.size(); i <= iElement; ++i)
	{
		m_vecElements.push_back(NULL);
	}

	return m_vecElements.at(iElement);
}
