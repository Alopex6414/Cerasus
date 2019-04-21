/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraSlider.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-30	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraDialog.h"
#include "SakuraSlider.h"

// SakuraGUI 滑块派生类(UI)

//------------------------------------------------------------------
// @Function:	 SetValueInternal()
// @Purpose: CSakuraSlider设置值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::SetValueInternal(int nValue, bool bFromInput)
{
	nValue = __max(m_nMin, nValue);
	nValue = __min(m_nMax, nValue);

	if (nValue == m_nValue)
	{
		return;
	}

	m_nValue = nValue;
	UpdateRects();

	m_pDialog->SendEvent(EVENT_SLIDER_VALUE_CHANGED, bFromInput, this);
}

//------------------------------------------------------------------
// @Function:	 ValueFromPos()
// @Purpose: CSakuraSlider坐标值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURASLIDER_CALLMETHOD CSakuraSlider::ValueFromPos(int x)
{
	float fValuePerPixel = (float)(m_nMax - m_nMin) / (m_rcBoundingBox.right - m_rcBoundingBox.left);
	return (int)(0.5f + m_nMin + fValuePerPixel * (x - m_rcBoundingBox.left));
}

//------------------------------------------------------------------
// @Function:	 CSakuraSlider()
// @Purpose: CSakuraSlider构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraSlider::CSakuraSlider(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_SLIDER;
	m_pDialog = pDialog;

	m_nMin = 0;
	m_nMax = 100;
	m_nValue = 50;

	m_bPressed = false;
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraSlider鼠标落在控件内部
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL SAKURASLIDER_CALLMETHOD CSakuraSlider::ContainsPoint(POINT pt)
{
	return (PtInRect(&m_rcBoundingBox, pt) || PtInRect(&m_rcButton, pt));
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CSakuraSlider是否拥有焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASLIDER_CALLMETHOD CSakuraSlider::CanHaveFocus()
{
	return (m_bVisible && m_bEnabled);
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraSlider键盘消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASLIDER_CALLMETHOD CSakuraSlider::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
				case VK_HOME:
					SetValueInternal(m_nMin, true);
					return true;

				case VK_END:
					SetValueInternal(m_nMax, true);
					return true;

				case VK_LEFT:
				case VK_DOWN:
					SetValueInternal(m_nValue - 1, true);
					return true;

				case VK_RIGHT:
				case VK_UP:
					SetValueInternal(m_nValue + 1, true);
					return true;

				case VK_NEXT:
					SetValueInternal(m_nValue - (10 > (m_nMax - m_nMin) / 10 ? 10 : (m_nMax - m_nMin) / 10), true);
					return true;

				case VK_PRIOR:
					SetValueInternal(m_nValue + (10 > (m_nMax - m_nMin) / 10 ? 10 : (m_nMax - m_nMin) / 10), true);
					return true;
			}
			break;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraSlider鼠标消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASLIDER_CALLMETHOD CSakuraSlider::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
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
			if (PtInRect(&m_rcButton, pt))
			{
				m_bPressed = true;

				m_nDragX = pt.x;
				m_nDragOffset = m_nButtonX - m_nDragX;

				if (!m_bHasFocus)
				{
					m_pDialog->RequestFocus(this);
				}

				return true;
			}

			if (PtInRect(&m_rcBoundingBox, pt))
			{
				m_nDragX = pt.x;
				m_nDragOffset = 0;
				m_bPressed = true;

				if (!m_bHasFocus)
				{
					m_pDialog->RequestFocus(this);
				}

				if (pt.x > m_nButtonX + m_nX)
				{
					SetValueInternal(m_nValue + 1, true);
					return true;
				}

				if (pt.x < m_nButtonX + m_nX)
				{
					SetValueInternal(m_nValue - 1, true);
					return true;
				}
			}

			break;
		}

		case WM_LBUTTONUP:
		{
			if (m_bPressed)
			{
				m_bPressed = false;
				m_pDialog->SendEvent(EVENT_SLIDER_VALUE_CHANGED, true, this);

				return true;
			}

			break;
		}

		case WM_MOUSEMOVE:
		{
			if (m_bPressed)
			{
				SetValueInternal(ValueFromPos(m_nX + pt.x + m_nDragOffset), true);
				return true;
			}

			break;
		}

		case WM_MOUSEWHEEL:
		{
			int nScrollAmount = int((short)HIWORD(wParam)) / WHEEL_DELTA;
			SetValueInternal(m_nValue - nScrollAmount, true);
			return true;
		}
	};

	return false;
}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraSlider更新控件区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::UpdateRects()
{
	CSakuraControl::UpdateRects();

	m_rcButton = m_rcBoundingBox;
	m_rcButton.right = m_rcButton.left + (m_rcButton.bottom - m_rcButton.top);
	OffsetRect(&m_rcButton, -(m_rcButton.right - m_rcButton.left) / 2, 0);

	m_nButtonX = (int)((m_nValue - m_nMin) * (float)(m_rcBoundingBox.right - m_rcBoundingBox.left) / (m_nMax - m_nMin));
	OffsetRect(&m_rcButton, m_nButtonX, 0);
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraSlider渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	SAKURA_CONTROL_STATE iState = SAKURA_STATE_NORMAL;

	if (m_bEnabled == false)
	{
		iState = SAKURA_STATE_DISABLED;
	}
	else if (m_bPressed)
	{
		iState = SAKURA_STATE_PRESSED;
	}
	else if (m_bMouseOver)
	{
		iState = SAKURA_STATE_MOUSEOVER;
	}
	else if (m_bHasFocus)
	{
		iState = SAKURA_STATE_FOCUS;
	}
	
	m_vecElements.at(0)->GetTextureBlend().Blend(iState);
	m_vecElements.at(1)->GetTextureBlend().Blend(iState);
}

//------------------------------------------------------------------
// @Function:	 SetValue()
// @Purpose: CSakuraSlider设置滑块当前值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::SetValue(int nValue)
{
	SetValueInternal(nValue, false);
}

//------------------------------------------------------------------
// @Function:	 GetValue()
// @Purpose: CSakuraSlider获取滑块当前值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURASLIDER_CALLMETHOD CSakuraSlider::GetValue() const
{
	return m_nValue;
}

//------------------------------------------------------------------
// @Function:	 GetRange()
// @Purpose: CSakuraSlider获取滑块当前范围
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::GetRange(int & nMin, int & nMax) const
{
	nMin = m_nMin; 
	nMax = m_nMax;
}

//------------------------------------------------------------------
// @Function:	 SetRange()
// @Purpose: CSakuraSlider设置滑块当前范围
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASLIDER_CALLMETHOD CSakuraSlider::SetRange(int nMin, int nMax)
{
	m_nMin = nMin;
	m_nMax = nMax;

	SetValueInternal(m_nValue, false);
}
