/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraButton.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraDialog.h"
#include "SakuraButton.h"
#include "CerasusAlgorithm.h"

// SakuraGUI 按钮控件派生类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraButton()
// @Purpose: CSakuraButton构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraButton::CSakuraButton(CSakuraDialog * pDialog)
{
	m_pDialog = pDialog;
	m_eType = SAKURA_CONTROL_BUTTON;

	m_bPressed = false;
	m_nHotkey = 0;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraButton渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABUTTON_CALLMETHOD CSakuraButton::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	SAKURA_CONTROL_STATE iState = SAKURA_STATE_NORMAL;

	if (m_bIsDefault == true)
	{
		if (m_bPressed == true)
		{
			CCerasusAlgorithm::Increase(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.05f);
		}
		else if (m_bMouseOver == true)
		{
			CCerasusAlgorithm::Increase(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.8f, 0.01f);
		}
		else
		{
			CCerasusAlgorithm::Decrease(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.6f, 0.01f);
		}
	}
	else
	{
		if (m_bEnabled == false)
		{
			iState = SAKURA_STATE_DISABLED;
		}
		else if (m_bPressed == true)
		{
			iState = SAKURA_STATE_PRESSED;
		}
		else if (m_bMouseOver == true)
		{
			iState = SAKURA_STATE_MOUSEOVER;
		}
		else if (m_bHasFocus == true)
		{
			iState = SAKURA_STATE_FOCUS;
		}
	}

	m_vecElements.at(0)->GetTextureBlend().Blend(iState);
	m_vecElements.at(0)->GetFontBlend().Blend(iState, m_strText, &m_rcBoundingBox, m_dwFormat, m_dwColor);
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraButton响应键盘消息
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURABUTTON_CALLMETHOD CSakuraButton::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
						m_pDialog->SendEvent(EVENT_BUTTON_CLICKED, true, this);
					}
					return true;
			}
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraButton响应鼠标消息
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURABUTTON_CALLMETHOD CSakuraButton::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
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

				if (!m_pDialog->m_bKeyboardInput)
				{
					m_pDialog->ClearFocus();
				}

				if (ContainsPoint(pt))
				{
					m_pDialog->SendEvent(EVENT_BUTTON_CLICKED, true, this);
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
// @Purpose: CSakuraButton鼠标热键响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABUTTON_CALLMETHOD CSakuraButton::OnHotkey()
{
	if (m_pDialog->IsKeyboardInputEnabled())
	{
		m_pDialog->RequestFocus(this);
	}

	m_pDialog->SendEvent(EVENT_BUTTON_CLICKED, true, this);
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraButton鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL SAKURABUTTON_CALLMETHOD CSakuraButton::ContainsPoint(POINT pt)
{
	return PtInRect(&m_rcBoundingBox, pt);
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CSakuraButton是否拥有焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURABUTTON_CALLMETHOD CSakuraButton::CanHaveFocus()
{
	return (m_bVisible && m_bEnabled);
}
