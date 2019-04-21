/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraScrollBar.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-28	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraScrollBar.h"

// SakuraGUI 滚动条控件派生类(UI)

//------------------------------------------------------------------
// @Function:	 UpdateThumbRect()
// @Purpose: CSakuraScrollBar滚动条位置更新
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::UpdateThumbRect()
{
	if (m_nEnd - m_nStart > m_nPageSize)
	{
		int nThumbHeight = __max((m_rcTrack.bottom - m_rcTrack.top) * m_nPageSize / (m_nEnd - m_nStart), SCROLLBAR_MINTHUMBSIZE);
		int nMaxPosition = m_nEnd - m_nStart - m_nPageSize;
		m_rcThumb.top = m_rcTrack.top + (m_nPosition - m_nStart) * ((m_rcTrack.bottom - m_rcTrack.top) - nThumbHeight) / nMaxPosition;
		m_rcThumb.bottom = m_rcThumb.top + nThumbHeight;
		m_bShowThumb = true;
	}
	else
	{
		m_rcThumb.bottom = m_rcThumb.top;
		m_bShowThumb = false;
	}

}

//------------------------------------------------------------------
// @Function:	 Cap()
// @Purpose: CSakuraScrollBar滚动条位置检测
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::Cap()
{
	if (m_nPosition < m_nStart || m_nEnd - m_nStart <= m_nPageSize)
	{
		m_nPosition = m_nStart;
	}
	else if (m_nPosition + m_nPageSize > m_nEnd)
	{
		m_nPosition = m_nEnd - m_nPageSize + 1;
	}

}

//------------------------------------------------------------------
// @Function:	 CSakuraScrollBar()
// @Purpose: CSakuraScrollBar构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraScrollBar::CSakuraScrollBar(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_SCROLLBAR;
	m_pDialog = pDialog;

	m_bShowThumb = true;
	m_bDrag = false;

	SetRect(&m_rcUpButton, 0, 0, 0, 0);
	SetRect(&m_rcDownButton, 0, 0, 0, 0);
	SetRect(&m_rcTrack, 0, 0, 0, 0);
	SetRect(&m_rcThumb, 0, 0, 0, 0);
	m_nPosition = 0;
	m_nPageSize = 1;
	m_nStart = 0;
	m_nEnd = 1;
	m_eArrow = SAKURA_SCROLLBAR_STATE_CLEAR;
	m_dArrowTS = 0.0;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraScrollBar()
// @Purpose: CSakuraScrollBar析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraScrollBar::~CSakuraScrollBar()
{
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraScrollBar键盘消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraScrollBar鼠标消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	static int ThumbOffsetY;

	m_LastMouse = pt;
	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		{
			if (PtInRect(&m_rcUpButton, pt))
			{
				if (m_nPosition > m_nStart)
				{
					--m_nPosition;
				}
				
				UpdateThumbRect();
				m_eArrow = SAKURA_SCROLLBAR_STATE_CLICKED_UP;
				//m_dArrowTS = DXUTGetTime();
				return true;
			}

			if (PtInRect(&m_rcDownButton, pt))
			{
				if (m_nPosition + m_nPageSize <= m_nEnd)
				{
					++m_nPosition;
				}

				UpdateThumbRect();
				m_eArrow = SAKURA_SCROLLBAR_STATE_CLICKED_DOWN;
				//m_dArrowTS = DXUTGetTime();
				return true;
			}

			if (PtInRect(&m_rcThumb, pt))
			{
				m_bDrag = true;
				ThumbOffsetY = pt.y - m_rcThumb.top;
				return true;
			}

			if (m_rcThumb.left <= pt.x &&
				m_rcThumb.right > pt.x)
			{
				if (m_rcThumb.top > pt.y && m_rcTrack.top <= pt.y)
				{
					Scroll(-(m_nPageSize - 1));
					return true;
				}
				else if (m_rcThumb.bottom <= pt.y && m_rcTrack.bottom > pt.y)
				{
					Scroll(m_nPageSize - 1);
					return true;
				}
			}

			break;
		}

		case WM_LBUTTONUP:
		{
			m_bDrag = false;
			UpdateThumbRect();
			m_eArrow = SAKURA_SCROLLBAR_STATE_CLEAR;
			break;
		}

		case WM_MOUSEMOVE:
		{
			if (m_bDrag)
			{
				m_rcThumb.bottom += pt.y - ThumbOffsetY - m_rcThumb.top;
				m_rcThumb.top = pt.y - ThumbOffsetY;
				if (m_rcThumb.top < m_rcTrack.top)
				{
					OffsetRect(&m_rcThumb, 0, m_rcTrack.top - m_rcThumb.top);
				}
				else if (m_rcThumb.bottom > m_rcTrack.bottom)
				{
					OffsetRect(&m_rcThumb, 0, m_rcTrack.bottom - m_rcThumb.bottom);
				}

				int nMaxFirstItem = m_nEnd - m_nStart - m_nPageSize + 1;
				int nMaxThumb = (m_rcTrack.bottom - m_rcTrack.top) - (m_rcThumb.bottom - m_rcThumb.top);

				m_nPosition = m_nStart + (m_rcThumb.top - m_rcTrack.top + nMaxThumb / (nMaxFirstItem * 2)) *  nMaxFirstItem / nMaxThumb;

				return true;
			}

			break;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraScrollBar消息处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraScrollBar渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::Render()
{
	if (m_eArrow != SAKURA_SCROLLBAR_STATE_CLEAR)
	{
		if (PtInRect(&m_rcUpButton, m_LastMouse))
		{
			switch (m_eArrow)
			{
			case SAKURA_SCROLLBAR_STATE_CLICKED_UP:
				{
					Scroll(-1);
					m_eArrow = SAKURA_SCROLLBAR_STATE_HELD_UP;
				}
				break;
			case SAKURA_SCROLLBAR_STATE_HELD_UP:
				{
					Scroll(-1);
				}
				break;
			}
		}
		else if (PtInRect(&m_rcDownButton, m_LastMouse))
		{
			switch (m_eArrow)
			{
			case SAKURA_SCROLLBAR_STATE_CLICKED_DOWN:
				{
					Scroll(1);
					m_eArrow = SAKURA_SCROLLBAR_STATE_HELD_DOWN;
				}
				break;
			case SAKURA_SCROLLBAR_STATE_HELD_DOWN:
				{
					Scroll(1);
				}
				break;
			}
		}

	}

	if (m_bVisible == false)
	{
		return;
	}

	SAKURA_CONTROL_STATE iState = SAKURA_STATE_NORMAL;

	if (m_bEnabled == false || m_bShowThumb == false)
	{
		iState = SAKURA_STATE_DISABLED;
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
	m_vecElements.at(2)->GetTextureBlend().Blend(iState);
	m_vecElements.at(3)->GetTextureBlend().Blend(iState);
}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraScrollBar更新控件区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::UpdateRects()
{
	CSakuraControl::UpdateRects();

	SetRect(&m_rcUpButton, m_rcBoundingBox.left, m_rcBoundingBox.top, m_rcBoundingBox.right, m_rcBoundingBox.top + (m_rcBoundingBox.bottom - m_rcBoundingBox.top));
	SetRect(&m_rcDownButton, m_rcBoundingBox.left, m_rcBoundingBox.bottom - (m_rcBoundingBox.bottom - m_rcBoundingBox.top), m_rcBoundingBox.right, m_rcBoundingBox.bottom);
	SetRect(&m_rcTrack, m_rcUpButton.left, m_rcUpButton.bottom, m_rcDownButton.right, m_rcDownButton.top);
	m_rcThumb.left = m_rcUpButton.left;
	m_rcThumb.right = m_rcUpButton.right;

	UpdateThumbRect();
}

//------------------------------------------------------------------
// @Function:	 SetTrackRange()
// @Purpose: CSakuraScrollBar设置轨迹范围
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::SetTrackRange(int nStart, int nEnd)
{
	m_nStart = nStart; 
	m_nEnd = nEnd;
	Cap();
	UpdateThumbRect();
}

//------------------------------------------------------------------
// @Function:	 GetTrackPos()
// @Purpose: CSakuraScrollBar获取轨迹位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::GetTrackPos()
{
	return m_nPosition;
}

//------------------------------------------------------------------
// @Function:	 SetTrackPos()
// @Purpose: CSakuraScrollBar设置轨迹位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::SetTrackPos(int nPosition)
{
	m_nPosition = nPosition;
	Cap();
	UpdateThumbRect();
}

//------------------------------------------------------------------
// @Function:	 GetPageSize()
// @Purpose: CSakuraScrollBar获取每页数量
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::GetPageSize()
{
	return m_nPageSize;
}

//------------------------------------------------------------------
// @Function:	 SetPageSize()
// @Purpose: CSakuraScrollBar设置每页数量
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::SetPageSize(int nPageSize)
{
	m_nPageSize = nPageSize;
	Cap();
	UpdateThumbRect();
}

//------------------------------------------------------------------
// @Function:	 Scroll()
// @Purpose: CSakuraScrollBar滚动
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::Scroll(int nDelta)
{
	m_nPosition += nDelta;
	Cap();
	UpdateThumbRect();
}

//------------------------------------------------------------------
// @Function:	 ShowItem()
// @Purpose: CSakuraScrollBar显示条数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASCROLLBAR_CALLMETHOD CSakuraScrollBar::ShowItem(int nIndex)
{
	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (nIndex >= m_nEnd)
	{
		nIndex = m_nEnd - 1;
	}

	if (m_nPosition > nIndex)
	{
		m_nPosition = nIndex;
	}
	else if (m_nPosition + m_nPageSize <= nIndex)
	{
		m_nPosition = nIndex - m_nPageSize + 1;
	}

	UpdateThumbRect();
}
