/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraRadioButton.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-13	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraDialog.h"
#include "SakuraRadioButton.h"

// SakuraGUI ��ѡ��ؼ�������(UI)

//------------------------------------------------------------------
// @Function:	 SetCheckedInternal()
// @Purpose: CSakuraRadioButton���ÿؼ��ڲ�ѡ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::SetCheckedInternal(bool bChecked, bool bClearGroup, bool bFromInput)
{
	if (bChecked && bClearGroup)
	{
		m_pDialog->ClearRadioButtonGroup(m_nButtonGroup);
	}

	m_bChecked = bChecked;
	m_pDialog->SendEvent(EVENT_RADIOBUTTON_CHANGED, bFromInput, this);
}

//------------------------------------------------------------------
// @Function:	 CSakuraRadioButton()
// @Purpose: CSakuraRadioButton���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraRadioButton::CSakuraRadioButton(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_RADIOBUTTON;
	m_pDialog = pDialog;
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraRadioButton���������Ӧ��Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!m_bEnabled || !m_bVisible)
	{
		return false;
	}

	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_SPACE:
					m_bPressed = true;
					return true;
			}
		}

		case WM_KEYUP:
		{
			switch (wParam)
			{
				case VK_SPACE:
					if (m_bPressed == true)
					{
						m_bPressed = false;

						m_pDialog->ClearRadioButtonGroup(m_nButtonGroup);
						m_bChecked = !m_bChecked;

						m_pDialog->SendEvent(EVENT_RADIOBUTTON_CHANGED, true, this);
					}
					return true;
			}
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraRadioButton���������Ӧ��Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	if (!m_bEnabled || !m_bVisible)
	{
		return false;
	}

	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		{
			if (ContainsPoint(pt))
			{
				m_bPressed = true;

				if (!m_bHasFocus)
				{
					m_pDialog->RequestFocus(this);
				}

				return true;
			}

			break;
		}

		case WM_LBUTTONUP:
		{
			if (m_bPressed)
			{
				m_bPressed = false;

				if (ContainsPoint(pt))
				{
					m_pDialog->ClearRadioButtonGroup(m_nButtonGroup);
					m_bChecked = !m_bChecked;

					m_pDialog->SendEvent(EVENT_RADIOBUTTON_CHANGED, true, this);
				}

				return true;
			}

			break;
		}
	};

	return false;
}

//------------------------------------------------------------------
// @Function:	 OnHotkey()
// @Purpose: CSakuraRadioButton����ȼ���Ӧ��Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::OnHotkey()
{
	if (m_pDialog->IsKeyboardInputEnabled())
	{
		m_pDialog->RequestFocus(this);
	}

	SetCheckedInternal(true, true, true);
}

//------------------------------------------------------------------
// @Function:	 SetChecked()
// @Purpose: CSakuraRadioButton���ÿؼ�ѡ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::SetChecked(bool bChecked, bool bClearGroup)
{
	SetCheckedInternal(bChecked, bClearGroup, false);
}

//------------------------------------------------------------------
// @Function:	 SetButtonGroup()
// @Purpose: CSakuraRadioButton���ÿؼ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::SetButtonGroup(UINT nButtonGroup)
{
	m_nButtonGroup = nButtonGroup;
}

//------------------------------------------------------------------
// @Function:	 GetButtonGroup()
// @Purpose: CSakuraRadioButton��ȡ�ؼ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT SAKURARADIOBUTTON_CALLMETHOD CSakuraRadioButton::GetButtonGroup()
{
	return m_nButtonGroup;
}
