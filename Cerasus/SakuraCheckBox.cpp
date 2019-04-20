/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraCheckBox.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-10	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraDialog.h"
#include "SakuraCheckBox.h"
#include "CerasusAlgorithm.h"

// SakuraGUI 复选框控件派生类(UI)

//------------------------------------------------------------------
// @Function:	 SetCheckedInternal()
// @Purpose: CSakuraCheckBox设置内部复选
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::SetCheckedInternal(bool bChecked, bool bFromInput)
{
	m_bChecked = bChecked;

	m_pDialog->SendEvent(EVENT_CHECKBOX_CHANGED, bFromInput, this);
}

//------------------------------------------------------------------
// @Function:	 CSakuraCheckBox()
// @Purpose: CSakuraCheckBox构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraCheckBox::CSakuraCheckBox(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_CHECKBOX;
	m_pDialog = pDialog;

	m_bChecked = false;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraCheckBox渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	SAKURA_CONTROL_STATE iState = SAKURA_STATE_NORMAL;

	if (m_bIsDefault == true)
	{
		if (m_bChecked == false)
		{
			if (m_bPressed == true)
			{
				iState = SAKURA_STATE_PRESSED;
			}
			else if (m_bMouseOver == true)
			{
				iState = SAKURA_STATE_NORMAL;
				CCerasusAlgorithm::Increase(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 1.0f, 0.02f);
			}
			else
			{
				iState = SAKURA_STATE_NORMAL;
				CCerasusAlgorithm::Decrease(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->GetAlpha(), 0.6f, 0.02f);
			}
		}
		else
		{
			if (m_bPressed == true)
			{
				iState = SAKURA_STATE_NORMAL;
			}
			else if (m_bMouseOver == true)
			{
				iState = SAKURA_STATE_PRESSED;
				CCerasusAlgorithm::Increase(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->GetAlpha(), 1.0f, 0.02f);
			}
			else
			{
				iState = SAKURA_STATE_PRESSED;
				CCerasusAlgorithm::Decrease(m_vecElements.at(0)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->GetAlpha(), 0.6f, 0.02f);
			}
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
	m_vecElements.at(0)->GetFontBlend().Blend(iState, m_strText, &m_rcText, m_dwFormat, m_dwColor);
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraCheckBox键盘消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
						SetCheckedInternal(!m_bChecked, true);
					}
					return true;
			}
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraCheckBox鼠标消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
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
					SetCheckedInternal(!m_bChecked, true);
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
// @Purpose: CSakuraCheckBox鼠标热键
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::OnHotkey()
{
	if (m_pDialog->IsKeyboardInputEnabled())
	{
		m_pDialog->RequestFocus(this);
	}

	SetCheckedInternal(!m_bChecked, true);
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraCheckBox鼠标在控件区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::ContainsPoint(POINT pt)
{
	return (PtInRect(&m_rcBoundingBox, pt) || PtInRect(&m_rcButton, pt));
}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraCheckBox更新控件矩形区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::UpdateRects()
{
	CSakuraButton::UpdateRects();

	m_rcButton = m_rcBoundingBox;
	m_rcButton.right = m_rcButton.left + (m_rcButton.bottom - m_rcButton.top);

	m_rcText = m_rcBoundingBox;
	m_rcText.left += (int)(1.25f * (m_rcButton.right - m_rcButton.left));
}

//------------------------------------------------------------------
// @Function:	 GetChecked()
// @Purpose: CSakuraCheckBox获取控件选中状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::GetChecked()
{
	return m_bChecked;
}

//------------------------------------------------------------------
// @Function:	 SetChecked()
// @Purpose: CSakuraCheckBox设置控件选中状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACHECKBOX_CALLMETHOD CSakuraCheckBox::SetChecked(bool bChecked)
{
	SetCheckedInternal(bChecked, false);
}
