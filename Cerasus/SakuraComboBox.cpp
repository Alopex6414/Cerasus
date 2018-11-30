/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraComboBox.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-14	v1.00a	alopex	Create Project.
*/
#include "SakuraDialog.h"
#include "SakuraComboBox.h"

// SakuraGUI ������������(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraComboBox()
// @Purpose: CSakuraComboBox���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraComboBox::CSakuraComboBox(CSakuraDialog* pDialog)
{
	m_eType = SAKURA_CONTROL_COMBOBOX;
	m_pDialog = pDialog;

	m_nDropHeight = 100;

	m_nSBWidth = 16;
	m_bOpened = false;
	m_iSelected = -1;
	m_iFocused = -1;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraComboBox()
// @Purpose: CSakuraComboBox��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraComboBox::~CSakuraComboBox()
{
	RemoveAllItems();
}

//------------------------------------------------------------------
// @Function:	 OnInit()
// @Purpose: CSakuraComboBox��ʼ���ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::OnInit()
{
	return m_pDialog->InitControl(&m_ScrollBar);
}

//------------------------------------------------------------------
// @Function:	 HandleKeyboard()
// @Purpose: CSakuraComboBox������Ϣ��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const DWORD REPEAT_MASK = (0x40000000);

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
		{
			switch (wParam)
			{
				case VK_RETURN:
					if (m_bOpened)
					{
						if (m_iSelected != m_iFocused)
						{
							m_iSelected = m_iFocused;
							m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						}
						m_bOpened = false;

						if (!m_pDialog->m_bKeyboardInput)
						{
							m_pDialog->ClearFocus();
						}
						return true;
					}
					break;

				case VK_F4:
					if (lParam & REPEAT_MASK)
					{
						return true;
					}

					m_bOpened = !m_bOpened;

					if (!m_bOpened)
					{
						m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);

						if (!m_pDialog->m_bKeyboardInput)
						{
							m_pDialog->ClearFocus();
						}
					}
					return true;

				case VK_LEFT:
				case VK_UP:
					if (m_iFocused > 0)
					{
						m_iFocused--;
						m_iSelected = m_iFocused;

						if (!m_bOpened)
						{
							m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						}
					}
					return true;

				case VK_RIGHT:
				case VK_DOWN:
					if (m_iFocused + 1 < (int)GetNumItems())
					{
						m_iFocused++;
						m_iSelected = m_iFocused;

						if (!m_bOpened)
						{
							m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						}
					}
					return true;
			}
			break;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 HandleMouse()
// @Purpose: CSakuraComboBox�����Ϣ��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam)
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
		case WM_MOUSEMOVE:
		{
			if (m_bOpened && PtInRect(&m_rcDropdown, pt))
			{
				for (auto iter = m_Items.begin(); iter != m_Items.end(); ++iter)
				{
					if((*iter)->bVisible && PtInRect(&(*iter)->rcActive, pt))
					{
						m_iFocused = iter - m_Items.begin();
					}
				}

				return true;
			}
			break;
		}

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

				if (m_bHasFocus)
				{
					m_bOpened = !m_bOpened;

					if (!m_bOpened)
					{
						if (!m_pDialog->m_bKeyboardInput)
						{
							m_pDialog->ClearFocus();
						}
					}
				}
				return true;
			}

			if (m_bOpened && PtInRect(&m_rcDropdown, pt))
			{
				for (int i = m_ScrollBar.GetTrackPos(); i < m_Items.size(); i++)
				{
					S_SakuraComboBoxItem* pItem = m_Items.at(i);
					if (pItem->bVisible && PtInRect(&pItem->rcActive, pt))
					{
						m_iFocused = m_iSelected = i;
						m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						m_bOpened = false;

						if (!m_pDialog->m_bKeyboardInput)
						{
							m_pDialog->ClearFocus();
						}
						break;
					}
				}
				return true;
			}

			if (m_bOpened)
			{
				m_iFocused = m_iSelected;

				m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
				m_bOpened = false;
			}

			m_bPressed = false;

			if (!m_pDialog->m_bKeyboardInput)
			{
				m_pDialog->ClearFocus();
			}
			break;
		}

		case WM_LBUTTONUP:
		{
			if (m_bPressed && ContainsPoint(pt))
			{
				m_bPressed = false;
				return true;
			}
			break;
		}

		case WM_MOUSEWHEEL:
		{
			int zDelta = (short)HIWORD(wParam) / WHEEL_DELTA;
			if (m_bOpened)
			{
				UINT uLines;
				SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &uLines, 0);
				m_ScrollBar.Scroll(-zDelta * uLines);
			}
			else
			{
				if (zDelta > 0)
				{
					if (m_iFocused > 0)
					{
						m_iFocused--;
						m_iSelected = m_iFocused;

						if (!m_bOpened)
						{
							m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						}
					}
				}
				else
				{
					if (m_iFocused + 1 < (int)GetNumItems())
					{
						m_iFocused++;
						m_iSelected = m_iFocused;

						if (!m_bOpened)
						{
							m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
						}
					}
				}
			}
			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 OnHotkey()
// @Purpose: CSakuraComboBox����ȼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::OnHotkey()
{
	if (m_bOpened)
	{
		return;
	}

	if (m_iSelected == -1)
	{
		return;
	}

	if (m_pDialog->IsKeyboardInputEnabled())
	{
		m_pDialog->RequestFocus(this);
	}

	m_iSelected++;

	if (m_iSelected >= (int)m_Items.size())
	{
		m_iSelected = 0;
	}

	m_iFocused = m_iSelected;
	m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, true, this);
}

//------------------------------------------------------------------
// @Function:	 CanHaveFocus()
// @Purpose: CSakuraComboBox���Ի�ȡ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::CanHaveFocus()
{
	return (m_bVisible && m_bEnabled);
}

//------------------------------------------------------------------
// @Function:	 OnFocusOut()
// @Purpose: CSakuraComboBox��ʧ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::OnFocusOut()
{
	CSakuraButton::OnFocusOut();

	m_bOpened = false;
}

//------------------------------------------------------------------
// @Function:	 OnFocusOut()
// @Purpose: CSakuraComboBox��ʧ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::Render()
{
	
}

//------------------------------------------------------------------
// @Function:	 UpdateRects()
// @Purpose: CSakuraComboBox���¿ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::UpdateRects()
{
	CSakuraButton::UpdateRects();

	m_rcButton = m_rcBoundingBox;
	m_rcButton.left = m_rcButton.right - (m_rcButton.bottom - m_rcButton.top);

	m_rcText = m_rcBoundingBox;
	m_rcText.right = m_rcButton.left;

	m_rcDropdown = m_rcText;
	OffsetRect(&m_rcDropdown, 0, (int)(0.90f * (m_rcText.bottom - m_rcText.top)));
	m_rcDropdown.bottom += m_nDropHeight;
	m_rcDropdown.right -= m_nSBWidth;

	m_rcDropdownText = m_rcDropdown;
	m_rcDropdownText.left += (int)(0.1f * (m_rcDropdown.right - m_rcDropdown.left));
	m_rcDropdownText.right -= (int)(0.1f * (m_rcDropdown.right - m_rcDropdown.left));
	m_rcDropdownText.top += (int)(0.1f * (m_rcDropdown.bottom - m_rcDropdown.top));
	m_rcDropdownText.bottom -= (int)(0.1f * (m_rcDropdown.bottom - m_rcDropdown.top));

	m_ScrollBar.SetLocation(m_rcDropdown.right, m_rcDropdown.top + 2);
	m_ScrollBar.SetSize(m_nSBWidth, (m_rcDropdown.bottom - m_rcDropdown.top) - 2);
	
}

//------------------------------------------------------------------
// @Function:	 AddItem()
// @Purpose: CSakuraComboBox�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::AddItem(const WCHAR * strText, void * pData)
{
	if (strText == NULL)
	{
		return E_INVALIDARG;
	}

	S_SakuraComboBoxItem* pItem = new S_SakuraComboBoxItem();
	if (pItem == NULL)
	{
		return DXTRACE_ERR_MSGBOX(L"new", E_OUTOFMEMORY);
	}

	ZeroMemory(pItem, sizeof(S_SakuraComboBoxItem));
	wcscpy_s(pItem->strText, 256, strText);
	pItem->pData = pData;

	m_Items.push_back(pItem);

	m_ScrollBar.SetTrackRange(0, m_Items.size());

	if (GetNumItems() == 1)
	{
		m_iSelected = 0;
		m_iFocused = 0;
		m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, false, this);
	}

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 RemoveAllItems()
// @Purpose: CSakuraComboBox�Ƴ�ȫ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::RemoveAllItems()
{
	for (auto iter = m_Items.begin(); iter != m_Items.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_Items.clear();
	m_ScrollBar.SetTrackRange(0, 1);
	m_iFocused = m_iSelected = -1;
}

//------------------------------------------------------------------
// @Function:	 RemoveItem()
// @Purpose: CSakuraComboBox�Ƴ���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::RemoveItem(UINT Index)
{
	m_Items.erase(m_Items.begin() + Index);

	m_ScrollBar.SetTrackRange(0, m_Items.size());
	if (m_iSelected >= m_Items.size())
	{
		m_iSelected = m_Items.size() - 1;
	}
}

//------------------------------------------------------------------
// @Function:	 ContainsItem()
// @Purpose: CSakuraComboBox������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::ContainsItem(const WCHAR * strText, UINT iStart)
{
	return (-1 != FindItem(strText, iStart));
}

//------------------------------------------------------------------
// @Function:	 FindItem()
// @Purpose: CSakuraComboBox������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::FindItem(const WCHAR * strText, UINT iStart)
{
	if (strText == NULL)
	{
		return -1;
	}

	for (int i = iStart; i < m_Items.size(); i++)
	{
		S_SakuraComboBoxItem* pItem = m_Items.at(i);

		if (0 == wcscmp(pItem->strText, strText))
		{
			return i;
		}
	}

	return -1;
}

//------------------------------------------------------------------
// @Function:	 GetItemData()
// @Purpose: CSakuraComboBox��ȡ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void *SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetItemData(const WCHAR * strText)
{
	int index = FindItem(strText);
	if (index == -1)
	{
		return NULL;
	}

	S_SakuraComboBoxItem* pItem = m_Items.at(index);
	if (pItem == NULL)
	{
		DXTRACE_ERR(L"S_SakuraComboBoxItem::At", E_FAIL);
		return NULL;
	}

	return pItem->pData;
}

//------------------------------------------------------------------
// @Function:	 GetItemData()
// @Purpose: CSakuraComboBox��ȡ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void *SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetItemData(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_Items.size())
	{
		return NULL;
	}

	return m_Items.at(nIndex)->pData;
}

//------------------------------------------------------------------
// @Function:	 SetDropHeight()
// @Purpose: CSakuraComboBox������߶�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::SetDropHeight(UINT nHeight)
{
	m_nDropHeight = nHeight; 
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 GetScrollBarWidth()
// @Purpose: CSakuraComboBox��ȡ���������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetScrollBarWidth() const
{
	return m_nSBWidth;
}

//------------------------------------------------------------------
// @Function:	 SetScrollBarWidth()
// @Purpose: CSakuraComboBox���ù��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::SetScrollBarWidth(int nWidth)
{
	m_nSBWidth = nWidth; 
	UpdateRects();
}

//------------------------------------------------------------------
// @Function:	 GetSelectedIndex()
// @Purpose: CSakuraComboBox��ȡѡ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetSelectedIndex() const
{
	return m_iSelected;
}

//------------------------------------------------------------------
// @Function:	 GetSelectedData()
// @Purpose: CSakuraComboBox��ȡѡ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void *SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetSelectedData()
{
	if (m_iSelected < 0)
	{
		return NULL;
	}

	S_SakuraComboBoxItem* pItem = m_Items.at(m_iSelected);
	return pItem->pData;
}

//------------------------------------------------------------------
// @Function:	 GetSelectedItem()
// @Purpose: CSakuraComboBox��ȡѡ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
S_SakuraComboBoxItem *SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetSelectedItem()
{
	if (m_iSelected < 0)
	{
		return NULL;
	}

	return m_Items.at(m_iSelected);
}

//------------------------------------------------------------------
// @Function:	 GetNumItems()
// @Purpose: CSakuraComboBox��ȡ��Ŀ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetNumItems()
{
	return m_Items.size();
}

//------------------------------------------------------------------
// @Function:	 GetItem()
// @Purpose: CSakuraComboBox��ȡ��Ŀ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
S_SakuraComboBoxItem *SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::GetItem(UINT Index)
{
	return m_Items.at(Index);
}

//------------------------------------------------------------------
// @Function:	 SetSelectedByIndex()
// @Purpose: CSakuraComboBox����ѡ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::SetSelectedByIndex(UINT Index)
{
	if (Index >= GetNumItems())
	{
		return E_INVALIDARG;
	}

	m_iFocused = m_iSelected = Index;
	m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, false, this);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 SetSelectedByIndex()
// @Purpose: CSakuraComboBox����ѡ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::SetSelectedByText(const WCHAR * strText)
{
	if (strText == NULL)
	{
		return E_INVALIDARG;
	}

	int index = FindItem(strText);
	if (index == -1)
	{
		return E_FAIL;
	}

	m_iFocused = m_iSelected = index;
	m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, false, this);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 SetSelectedByIndex()
// @Purpose: CSakuraComboBox����ѡ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURACOMBOBOX_CALLMETHOD CSakuraComboBox::SetSelectedByData(void * pData)
{
	for (int i = 0; i < m_Items.size(); i++)
	{
		S_SakuraComboBoxItem* pItem = m_Items.at(i);

		if (pItem->pData == pData)
		{
			m_iFocused = m_iSelected = i;
			m_pDialog->SendEvent(EVENT_COMBOBOX_SELECTION_CHANGED, false, this);
			return S_OK;
		}
	}

	return E_FAIL;
}
