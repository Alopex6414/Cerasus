/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraControl.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraControl.h"

// SakuraGUI �ؼ�����(UI)

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraControl���¿ؼ�����
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
// @Purpose: CSakuraControl���캯��
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

	m_pD3D9Device = NULL;
	m_vecElements.clear();

	ZeroMemory(&m_rcBoundingBox, sizeof(m_rcBoundingBox));
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraControl()
// @Purpose: CSakuraControl��������
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
// @Purpose: CSakuraControl��ʼ���ؼ�
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
// @Purpose: CSakuraControlˢ�¿ؼ�״̬
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
// @Purpose: CSakuraControl��ʼ���ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::Render()
{
	
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraControl��Ϣ����
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
// @Purpose: CSakuraControl������Ϣ����
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
// @Purpose: CSakuraControl�����Ϣ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACONTROL_CALLMETHOD CSakuraControl::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 SetDevice()
// @Purpose: CSakuraControl����D3D9��Ⱦ�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::SetDevice(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraControl��ȡD3D9��Ⱦ�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURACONTROL_CALLMETHOD CSakuraControl::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetElements()
// @Purpose: CSakuraControl��ȡ�ؼ���ȾԪ������
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
// @Purpose: CSakuraControl�Ƿ��ȡ����
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
// @Purpose: CSakuraControl���ý���
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
// @Purpose: CSakuraControl��ʧ����
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
// @Purpose: CSakuraControl������
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
// @Purpose: CSakuraControl����뿪
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
// @Purpose: CSakuraControl����ȼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACONTROL_CALLMETHOD CSakuraControl::OnHotkey()
{
	
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraControl������ڿؼ���
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
// @Purpose: CSakuraControl���ÿؼ�ʹ��
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
// @Purpose: CSakuraControl��ȡ�ؼ�ʹ��
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
// @Purpose: CSakuraControl���ÿؼ��ɼ�
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
// @Purpose: CSakuraControl��ȡ�ؼ��ɼ�
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
// @Purpose: CSakuraControl��ȡ����
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
// @Purpose: CSakuraControl��ȡ�ؼ�ID
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
// @Purpose: CSakuraControl���ÿؼ�ID
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
// @Purpose: CSakuraControl���ÿؼ�����
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
// @Purpose: CSakuraControl���ÿؼ���״
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
// @Purpose: CSakuraControl���������ֵ
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
// @Purpose: CSakuraControl��ȡ�����ֵ
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
// @Purpose: CSakuraControl�����û�����
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
// @Purpose: CSakuraControl��ȡ�û�����
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
// @Purpose: CSakuraControl��ȡ��ȾԪ��
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
