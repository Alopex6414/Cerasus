/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraListBox.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-12-04	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraDialog.h"
#include "SakuraListBox.h"

// SakuraGUI 列表框派生类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraListBox()
// @Purpose: CSakuraListBox构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraListBox::CSakuraListBox(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_LISTBOX;
	m_pDialog = pDialog;

	m_dwStyle = 0;
	m_nSBWidth = 16;
	m_nSelected = -1;
	m_nSelStart = 0;
	m_bDrag = false;
	m_nBorder = 6;
	m_nMargin = 5;
	m_nTextHeight = 0;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraListBox()
// @Purpose: CSakuraListBox析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraListBox::~CSakuraListBox()
{
	RemoveAllItems();
}

//------------------------------------------------------------------
// @Function:	 OnInit()
// @Purpose: CSakuraListBox控件初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURALISTBOX_CALLMETHOD CSakuraListBox::OnInit()
{
	return m_pDialog->InitControl(&m_ScrollBar);
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CSakuraListBox是否拥有焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURALISTBOX_CALLMETHOD CSakuraListBox::CanHaveFocus()
{
	return (m_bVisible && m_bEnabled);
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraListBox键盘消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURALISTBOX_CALLMETHOD CSakuraListBox::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!m_bEnabled || !m_bVisible)
	{
		return false;
	}

	if (m_ScrollBar.HandleKeyboard(uMsg, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_UP:
				case VK_DOWN:
				case VK_NEXT:
				case VK_PRIOR:
				case VK_HOME:
				case VK_END:
				{
					if (m_Items.size() == 0)
					{
						return true;
					}

					int nOldSelected = m_nSelected;

					switch (wParam)
					{
						case VK_UP:
						{
							--m_nSelected; 
							break;
						}
						case VK_DOWN:
						{
							++m_nSelected; 
							break;
						}
						case VK_NEXT:
						{
							m_nSelected += m_ScrollBar.GetPageSize() - 1;
							break;
						}
						case VK_PRIOR:
						{
							m_nSelected -= m_ScrollBar.GetPageSize() - 1;
							break;
						}
						case VK_HOME:
						{
							m_nSelected = 0; 
							break;
						}
						case VK_END:
						{
							m_nSelected = m_Items.size() - 1;
							break;
						}

					}

					if (m_nSelected < 0)
					{
						m_nSelected = 0;
					}
					if (m_nSelected >= (int)m_Items.size())
					{
						m_nSelected = m_Items.size() - 1;
					}

					if (nOldSelected != m_nSelected)
					{
						if (m_dwStyle & MULTISELECTION)
						{
							for (int i = 0; i < (int)m_Items.size(); ++i)
							{
								CSakuraListBoxItem* pItem = m_Items[i];
								pItem->bSelected = false;
							}

							if (GetKeyState(VK_SHIFT) < 0)
							{
								int nEnd = __max(m_nSelStart, m_nSelected);

								for (int n = __min(m_nSelStart, m_nSelected); n <= nEnd; ++n)
								{
									m_Items[n]->bSelected = true;
								}
							}
							else
							{
								m_Items[m_nSelected]->bSelected = true;

								m_nSelStart = m_nSelected;
							}
						}
						else
						{
							m_nSelStart = m_nSelected;
						}

						m_ScrollBar.ShowItem(m_nSelected);

						m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
					}
					return true;
				}

				case VK_SPACE:
					m_pDialog->SendEvent(EVENT_LISTBOX_ITEM_DBLCLK, true, this);
					return true;
			}
			break;
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraListBox鼠标消息响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURALISTBOX_CALLMETHOD CSakuraListBox::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
{
	if (!m_bEnabled || !m_bVisible)
	{
		return false;
	}

	if (WM_LBUTTONDOWN == uMsg)
	{
		if (!m_bHasFocus)
		{
			m_pDialog->RequestFocus(this);
		}
	}

	if (m_ScrollBar.HandleMouse(uMsg, pt, wParam, lParam))
	{
		return true;
	}

	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			if (m_Items.size() > 0 && PtInRect(&m_rcSelection, pt))
			{
				int nClicked;

				if (m_nTextHeight)
				{
					nClicked = m_ScrollBar.GetTrackPos() + (pt.y - m_rcText.top) / m_nTextHeight;
				}
				else
				{
					nClicked = -1;
				}

				if (nClicked >= m_ScrollBar.GetTrackPos() && nClicked < (int)m_Items.size() && nClicked < m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize())
				{
					m_bDrag = true;

					if (uMsg == WM_LBUTTONDBLCLK)
					{
						m_pDialog->SendEvent(EVENT_LISTBOX_ITEM_DBLCLK, true, this);
						return true;
					}

					m_nSelected = nClicked;
					if (!(wParam & MK_SHIFT))
					{
						m_nSelStart = m_nSelected;
					}

					if (m_dwStyle & MULTISELECTION)
					{
						CSakuraListBoxItem* pSelItem = m_Items.at(m_nSelected);
						if ((wParam & (MK_SHIFT | MK_CONTROL)) == MK_CONTROL)
						{
							pSelItem->bSelected = !pSelItem->bSelected;
						}
						else if ((wParam & (MK_SHIFT | MK_CONTROL)) == MK_SHIFT)
						{
							int nBegin = __min(m_nSelStart, m_nSelected);
							int nEnd = __max(m_nSelStart, m_nSelected);

							for (int i = 0; i < nBegin; ++i)
							{
								CSakuraListBoxItem* pItem = m_Items.at(i);
								pItem->bSelected = false;
							}

							for (int i = nEnd + 1; i < (int)m_Items.size(); ++i)
							{
								CSakuraListBoxItem* pItem = m_Items.at(i);
								pItem->bSelected = false;
							}

							for (int i = nBegin; i <= nEnd; ++i)
							{
								CSakuraListBoxItem* pItem = m_Items.at(i);
								pItem->bSelected = true;
							}
						}
						else if ((wParam & (MK_SHIFT | MK_CONTROL)) == (MK_SHIFT | MK_CONTROL))
						{
							int nBegin = __min(m_nSelStart, m_nSelected);
							int nEnd = __max(m_nSelStart, m_nSelected);

							bool bLastSelected = m_Items.at(m_nSelStart)->bSelected;
							for (int i = nBegin + 1; i < nEnd; ++i)
							{
								CSakuraListBoxItem* pItem = m_Items.at(i);
								pItem->bSelected = bLastSelected;
							}

							pSelItem->bSelected = true;

							m_nSelected = m_nSelStart;
						}
						else
						{
							for (int i = 0; i < (int)m_Items.size(); ++i)
							{
								CSakuraListBoxItem* pItem = m_Items.at(i);
								pItem->bSelected = false;
							}

							pSelItem->bSelected = true;
						}
					}

					m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
				}

				return true;
			}
			break;

		case WM_LBUTTONUP:
		{
			m_bDrag = false;

			if (m_nSelected != -1)
			{
				int nEnd = __max(m_nSelStart, m_nSelected);

				for (int n = __min(m_nSelStart, m_nSelected) + 1; n < nEnd; ++n)
				{
					m_Items[n]->bSelected = m_Items[m_nSelStart]->bSelected;
				}

				m_Items[m_nSelected]->bSelected = m_Items[m_nSelStart]->bSelected;

				if (m_nSelStart != m_nSelected)
				{
					m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
				}

				m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION_END, true, this);
			}
			return false;
		}

		case WM_MOUSEMOVE:
			if (m_bDrag)
			{
				int nItem;
				if (m_nTextHeight)
				{
					nItem = m_ScrollBar.GetTrackPos() + (pt.y - m_rcText.top) / m_nTextHeight;
				}
				else
				{
					nItem = -1;
				}

				if (nItem >= (int)m_ScrollBar.GetTrackPos() && nItem < (int)m_Items.size() && nItem < m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize())
				{
					m_nSelected = nItem;
					m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
				}
				else if (nItem < (int)m_ScrollBar.GetTrackPos())
				{
					m_ScrollBar.Scroll(-1);
					m_nSelected = m_ScrollBar.GetTrackPos();
					m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
				}
				else if (nItem >= m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize())
				{
					m_ScrollBar.Scroll(1);
					m_nSelected = __min((int)m_Items.size(), m_ScrollBar.GetTrackPos() + m_ScrollBar.GetPageSize()) - 1;
					m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
				}
			}
			break;

		case WM_MOUSEWHEEL:
		{
			UINT uLines;
			SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &uLines, 0);
			int nScrollAmount = int((short)HIWORD(wParam)) / WHEEL_DELTA * uLines;
			m_ScrollBar.Scroll(-nScrollAmount);
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraListBox消息处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURALISTBOX_CALLMETHOD CSakuraListBox::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraListBox渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	m_vecElements.at(0)->GetTextureBlend().Blend(SAKURA_STATE_NORMAL);
	m_vecElements.at(0)->GetFontBlend().Blend(SAKURA_STATE_NORMAL, _T(""), &m_rcBoundingBox);

	m_vecElements.at(1)->GetTextureBlend().Blend(SAKURA_STATE_NORMAL);
	m_vecElements.at(1)->GetFontBlend().Blend(SAKURA_STATE_NORMAL, _T(""), &m_rcBoundingBox);

	if (m_Items.size() > 0)
	{
		RECT rc = m_rcText;
		RECT rcSel = m_rcSelection;
		rc.bottom = rc.top + m_pDialog->GetManager()->GetFontNode(0)->nFontSize;

		m_nTextHeight = rc.bottom - rc.top;

		static bool bSBInit;
		if (!bSBInit)
		{
			if (m_nTextHeight)
			{
				m_ScrollBar.SetPageSize((m_rcText.bottom - m_rcText.top) / m_nTextHeight);
			}
			else
			{
				m_ScrollBar.SetPageSize((m_rcText.bottom - m_rcText.top));
			}
			bSBInit = true;
		}

		rc.right = m_rcText.right;
		for (int i = m_ScrollBar.GetTrackPos(); i < (int)m_Items.size(); ++i)
		{
			if (rc.bottom > m_rcText.bottom)
			{
				break;
			}

			CSakuraListBoxItem* pItem = m_Items.at(i);

			bool bSelectedStyle = false;

			if (!(m_dwStyle & MULTISELECTION) && i == m_nSelected)
			{
				bSelectedStyle = true;
			}
			else if (m_dwStyle & MULTISELECTION)
			{
				if (m_bDrag && ((i >= m_nSelected && i < m_nSelStart) || (i <= m_nSelected && i > m_nSelStart)))
				{
					bSelectedStyle = m_Items[m_nSelStart]->bSelected;
				}
				else if (pItem->bSelected)
				{
					bSelectedStyle = true;
				}
			}

			if (bSelectedStyle)
			{
				rcSel.top = rc.top; rcSel.bottom = rc.bottom;
				m_vecElements.at(1)->GetFontBlend().Blend(SAKURA_STATE_NORMAL, pItem->strText, &rcSel);
			}
			else
			{
				m_vecElements.at(0)->GetFontBlend().Blend(SAKURA_STATE_NORMAL, pItem->strText, &rc);
			}

			OffsetRect(&rc, 0, m_nTextHeight);
		}
	}

}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraListBox更新控件区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::UpdateRects()
{
	CSakuraControl::UpdateRects();

	m_rcSelection = m_rcBoundingBox;
	m_rcSelection.right -= m_nSBWidth;
	InflateRect(&m_rcSelection, -m_nBorder, -m_nBorder);
	m_rcText = m_rcSelection;
	InflateRect(&m_rcText, -m_nMargin, 0);

	m_ScrollBar.SetLocation(m_rcBoundingBox.right - m_nSBWidth, m_rcBoundingBox.top);
	m_ScrollBar.SetSize(m_nSBWidth, m_nHeight);
	CUFont* pFontNode = m_pDialog->GetManager()->GetFontNode(0);
	if (pFontNode && pFontNode->nFontSize)
	{
		m_ScrollBar.SetPageSize((m_rcText.bottom - m_rcText.top) / pFontNode->nFontSize);

		m_ScrollBar.ShowItem(m_nSelected);
	}
}

//------------------------------------------------------------------
// @Function:	 GetStyle()
// @Purpose: CSakuraListBox获取列表框样式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetStyle() const
{
	return m_dwStyle;
}

//------------------------------------------------------------------
// @Function:	 GetSize()
// @Purpose: CSakuraListBox获取长度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetSize() const
{
	return m_Items.size();
}

//------------------------------------------------------------------
// @Function:	 SetStyle()
// @Purpose: CSakuraListBox设置列表框样式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::SetStyle(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

//------------------------------------------------------------------
// @Function:	 GetScrollBarWidth()
// @Purpose: CSakuraListBox获取滚动条宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetScrollBarWidth() const
{
	return m_nSBWidth;
}

//------------------------------------------------------------------
// @Function:	 SetScrollBarWidth()
// @Purpose: CSakuraListBox设置滚动条宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::SetScrollBarWidth(int nWidth)
{
	m_nSBWidth = nWidth; 
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 SetBorder()
// @Purpose: CSakuraListBox设置边框宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::SetBorder(int nBorder, int nMargin)
{
	m_nBorder = nBorder; 
	m_nMargin = nMargin;
}

//------------------------------------------------------------------
// @Function:	 AddItem()
// @Purpose: CSakuraListBox添加项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURALISTBOX_CALLMETHOD CSakuraListBox::AddItem(const WCHAR * wszText, void * pData)
{
	CSakuraListBoxItem* pNewItem = new CSakuraListBoxItem();
	if (!pNewItem)
	{
		return E_OUTOFMEMORY;
	}

	wcscpy_s(pNewItem->strText, 256, wszText);
	pNewItem->pData = pData;
	SetRect(&pNewItem->rcActive, 0, 0, 0, 0);
	pNewItem->bSelected = false;

	m_Items.push_back(pNewItem);
	m_ScrollBar.SetTrackRange(0, m_Items.size());

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 InsertItem()
// @Purpose: CSakuraListBox插入项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURALISTBOX_CALLMETHOD CSakuraListBox::InsertItem(int nIndex, const WCHAR * wszText, void * pData)
{
	CSakuraListBoxItem* pNewItem = new CSakuraListBoxItem();
	if (!pNewItem)
	{
		return E_OUTOFMEMORY;
	}

	wcscpy_s(pNewItem->strText, 256, wszText);
	pNewItem->pData = pData;
	SetRect(&pNewItem->rcActive, 0, 0, 0, 0);
	pNewItem->bSelected = false;

	m_Items.insert(m_Items.begin() + nIndex, pNewItem);
	m_ScrollBar.SetTrackRange(0, m_Items.size());

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 RemoveItem()
// @Purpose: CSakuraListBox移除项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::RemoveItem(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_Items.size())
	{
		return;
	}

	CSakuraListBoxItem* pItem = m_Items.at(nIndex);
	SAFE_DELETE(pItem);

	m_Items.erase(m_Items.begin() + nIndex);
	m_ScrollBar.SetTrackRange(0, m_Items.size());
	if (m_nSelected >= (int)m_Items.size())
	{
		m_nSelected = m_Items.size() - 1;
	}

	m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
}

//------------------------------------------------------------------
// @Function:	 RemoveItemByData()
// @Purpose: CSakuraListBox移除项(值索引)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::RemoveItemByData(void * pData)
{
	
}

//------------------------------------------------------------------
// @Function:	 RemoveAllItems()
// @Purpose: CSakuraListBox移除所有项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::RemoveAllItems()
{
	for (int i = 0; i < m_Items.size(); ++i)
	{
		CSakuraListBoxItem* pItem = m_Items.at(i);
		SAFE_DELETE(pItem);
	}

	m_Items.clear();
	m_ScrollBar.SetTrackRange(0, 1);
}

//------------------------------------------------------------------
// @Function:	 GetItem()
// @Purpose: CSakuraListBox获取值
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraListBoxItem *SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetItem(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_Items.size())
	{
		return NULL;
	}

	return m_Items[nIndex];
}

//------------------------------------------------------------------
// @Function:	 GetSelectedIndex()
// @Purpose: CSakuraListBox获取值选中索引
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetSelectedIndex(int nPreviousSelected)
{
	if (nPreviousSelected < -1)
	{
		return -1;
	}

	if (m_dwStyle & MULTISELECTION)
	{
		for (int i = nPreviousSelected + 1; i < (int)m_Items.size(); ++i)
		{
			CSakuraListBoxItem* pItem = m_Items.at(i);

			if (pItem->bSelected)
			{
				return i;
			}
		}

		return -1;
	}
	else
	{
		return m_nSelected;
	}
}

//------------------------------------------------------------------
// @Function:	 GetSelectedItem()
// @Purpose: CSakuraListBox获取值选中项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraListBoxItem *SAKURALISTBOX_CALLMETHOD CSakuraListBox::GetSelectedItem(int nPreviousSelected)
{
	return GetItem(GetSelectedIndex(nPreviousSelected));
}

//------------------------------------------------------------------
// @Function:	 SelectItem()
// @Purpose: CSakuraListBox选中项
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURALISTBOX_CALLMETHOD CSakuraListBox::SelectItem(int nNewIndex)
{
	if (m_Items.size() == 0)
	{
		return;
	}

	int nOldSelected = m_nSelected;

	m_nSelected = nNewIndex;

	if (m_nSelected < 0)
	{
		m_nSelected = 0;
	}
	if (m_nSelected >= (int)m_Items.size())
	{
		m_nSelected = m_Items.size() - 1;
	}

	if (nOldSelected != m_nSelected)
	{
		if (m_dwStyle & MULTISELECTION)
		{
			m_Items[m_nSelected]->bSelected = true;
		}

		m_nSelStart = m_nSelected;

		m_ScrollBar.ShowItem(m_nSelected);
	}

	m_pDialog->SendEvent(EVENT_LISTBOX_SELECTION, true, this);
}
