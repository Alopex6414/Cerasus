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
#include "CerasusDialog.h"
#include "CerasusButton.h"

// CreasusUI 按钮控件(CCerasusButton)

//extern HWND g_hWnd;

//------------------------------------------------------------------
// @Function:	 CCerasusButton()
// @Purpose: CCerasusButton构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusButton::CCerasusButton(CCerasusDialog* pDialog)
{
	m_eType = CERASUS_CONTROL_BUTTON;
	m_pDialog = pDialog;

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
void CERASUSBUTTON_CALLMODE CCerasusButton::Render(float fElapsedTime)
{
	int nOffsetX = 0;
	int nOffsetY = 0;

	CERASUS_CONTROL_STATE iState = CERASUS_STATE_NORMAL;

	if (m_bVisible == false)
	{
		iState = CERASUS_STATE_HIDDEN;
	}
	else if (m_bEnabled == false)
	{
		iState = CERASUS_STATE_DISABLED;
	}
	else if (m_bPressed)
	{
		iState = CERASUS_STATE_PRESSED;

		nOffsetX = 1;
		nOffsetY = 2;
	}
	else if (m_bMouseOver)
	{
		iState = CERASUS_STATE_MOUSEOVER;

		nOffsetX = -1;
		nOffsetY = -2;
	}
	else if (m_bHasFocus)
	{
		iState = CERASUS_STATE_FOCUS;
	}

	CCerasusElement* pElement = m_vecElements[0];

	float fBlendRate = (iState == CERASUS_STATE_PRESSED) ? 0.0f : 0.8f;

	RECT rcWindow = m_rcBoundingBox;
	OffsetRect(&rcWindow, nOffsetX, nOffsetY);


	pElement->m_TextureColor.Blend(iState, fElapsedTime, fBlendRate);
	pElement->m_FontColor.Blend(iState, fElapsedTime, fBlendRate);

	//m_pDialog->DrawSprite(pElement, &rcWindow, DXUT_FAR_BUTTON_DEPTH);
	//m_pDialog->DrawText(m_strText, pElement, &rcWindow);

	// Main button
	pElement = m_vecElements[1];

	// Blend current color
	pElement->m_TextureColor.Blend(iState, fElapsedTime, fBlendRate);
	pElement->m_FontColor.Blend(iState, fElapsedTime, fBlendRate);

	//m_pDialog->DrawSprite(pElement, &rcWindow, DXUT_NEAR_BUTTON_DEPTH);
	//m_pDialog->DrawText(m_strText, pElement, &rcWindow);
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
// @Purpose: CCerasusButton鼠标响应函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSBUTTON_CALLMODE CCerasusButton::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
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
				//SetCapture(g_hWnd);

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
				ReleaseCapture();

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
// @Purpose: CCerasusButton鼠标热键
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSBUTTON_CALLMODE CCerasusButton::OnHotkey()
{
	if (m_pDialog->IsKeyboardInputEnabled())
	{
		m_pDialog->RequestFocus(this);
	}

	m_pDialog->SendEvent(EVENT_BUTTON_CLICKED, true, this);
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
	return PtInRect(&m_rcBoundingBox, pt);
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
	return (m_bVisible && m_bEnabled);
}
