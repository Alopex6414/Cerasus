/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraDialog.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraDialog.h"

// SakuraGUI ������(UI)
CSakuraControl*	CSakuraDialog::s_pControlFocus = NULL;			// CCerasusDialog ��ý���ؼ�
CSakuraControl*	CSakuraDialog::s_pControlPressed = NULL;		// CCerasusDialog ��ǰ���¿ؼ�

//------------------------------------------------------------------
// @Function:	 OnMouseMove()
// @Purpose: CSakuraDialog����ƶ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CSakuraDialog::OnMouseMove(POINT pt)
{
	CSakuraControl* pControl = GetControlAtPoint(pt);

	if (pControl == m_pControlMouseOver)
	{
		return;
	}

	if (m_pControlMouseOver)
	{
		m_pControlMouseOver->OnMouseLeave();
	}

	m_pControlMouseOver = pControl;
	if (pControl != NULL)
	{
		m_pControlMouseOver->OnMouseEnter();
	}

}

//------------------------------------------------------------------
// @Function:	 CSakuraDialog()
// @Purpose: CSakuraDialog���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraDialog::CSakuraDialog()
{
	m_nX = 0;
	m_nY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_bVisible = true;

	m_pControlMouseOver = NULL;

	m_pCallbackEvent = NULL;
	m_pCallbackEventUserContext = NULL;

	m_bNonUserEvents = false;
	m_bKeyboardInput = false;
	m_bMouseInput = true;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraDialog()
// @Purpose: CSakuraDialog��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraDialog::~CSakuraDialog()
{
	RemoveAllControls();
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraDialog������Ϣ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURADIALOG_CALLMETHOD CSakuraDialog::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool bHandled = false;

	if (!m_bVisible)
	{
		return false;
	}

	if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
	{
		if (s_pControlFocus->MsgProc(uMsg, wParam, lParam))
		{
			return true;
		}
	}

	switch (uMsg)
	{
		case WM_ACTIVATEAPP:
		{
			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (wParam)
				{
					s_pControlFocus->OnFocusIn();
				}
				else
				{
					s_pControlFocus->OnFocusOut();
				}
			}
			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (s_pControlFocus->HandleKeyboard(uMsg, wParam, lParam))
				{
					return true;
				}
			}

			if (uMsg == WM_KEYDOWN && (!s_pControlFocus || (s_pControlFocus->GetType() != SAKURA_CONTROL_EDITBOX && s_pControlFocus->GetType() != SAKURA_CONTROL_IMEEDITBOX)))
			{
				for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
				{
					if ((*iter)->GetHotkey() == wParam)
					{
						(*iter)->OnHotkey();
						return true;
					}
				}

			}

			if (uMsg == WM_KEYDOWN)
			{
				if (!m_bKeyboardInput)
				{
					return false;
				}

				switch (wParam)
				{
					case VK_RIGHT:
					case VK_DOWN:
					{
						if (s_pControlFocus != NULL)
						{
							return false;
						}
						break;
					}

					case VK_LEFT:
					case VK_UP:
					{
						if (s_pControlFocus != NULL)
						{
							return false;
						}
						break;
					}

					case VK_TAB:
					{
						return false;
					}
				}
			}

			break;
		}


		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_XBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
		{
			if (!m_bMouseInput)
			{
				return false;
			}

			POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };
			mousePoint.x -= m_nX;
			mousePoint.y -= m_nY;

			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (s_pControlFocus->HandleMouse(uMsg, mousePoint, wParam, lParam))
				{
					return true;
				}
			}

			CSakuraControl* pControl = GetControlAtPoint(mousePoint);
			if (pControl != NULL && pControl->GetEnabled())
			{
				bHandled = pControl->HandleMouse(uMsg, mousePoint, wParam, lParam);
				if (bHandled)
				{
					return true;
				}

			}
			else
			{
				if (uMsg == WM_LBUTTONDOWN && s_pControlFocus && s_pControlFocus->m_pDialog == this)
				{
					s_pControlFocus->OnFocusOut();
					s_pControlFocus = NULL;
				}
			}

			switch (uMsg)
			{
				case WM_MOUSEMOVE:
					OnMouseMove(mousePoint);
					return false;
			}

			break;
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 AddStatic()
// @Purpose: CSakuraDialog������Ӿ�̬�ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault, CSakuraStatic ** ppCreated)
{
	CSakuraStatic* pStatic = new CSakuraStatic(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pStatic;
	}

	if (pStatic == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pStatic));

	pStatic->SetID(ID);
	pStatic->SetText(strText);
	pStatic->SetLocation(x, y);
	pStatic->SetSize(width, height);
	pStatic->m_bIsDefault = bIsDefault;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddButton()
// @Purpose: CSakuraDialog������Ӱ�ť�ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, CSakuraButton ** ppCreated)
{
	CSakuraButton* pButton = new CSakuraButton(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pButton;
	}

	if (pButton == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pButton));

	pButton->SetID(ID);
	pButton->SetText(strText);
	pButton->SetLocation(x, y);
	pButton->SetSize(width, height);
	pButton->SetHotkey(nHotkey);
	pButton->m_bIsDefault = bIsDefault;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddControl()
// @Purpose: CSakuraDialog������ӿؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddControl(CSakuraControl * pControl)
{
	VERIFY(InitControl(pControl));
	
	m_vecControls.push_back(pControl);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 InitControl()
// @Purpose: CSakuraDialog���ڳ�ʼ���ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::InitControl(CSakuraControl * pControl)
{
	if (pControl == NULL)
	{
		return E_INVALIDARG;
	}

	pControl->m_nIndex = m_vecControls.size();

	//...

	VERIFY(pControl->OnInit());

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetStatic()
// @Purpose: CSakuraDialog���ڻ�ȡ��̬�ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraStatic *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetStatic(int ID)
{
	return (CSakuraStatic*)GetControl(ID, SAKURA_CONTROL_STATIC);
}

//------------------------------------------------------------------
// @Function:	 GetButton()
// @Purpose: CSakuraDialog���ڻ�ȡ��ť�ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraButton *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetButton(int ID)
{
	return (CSakuraButton*)GetControl(ID, SAKURA_CONTROL_BUTTON);
}

//------------------------------------------------------------------
// @Function:	 GetControl()
// @Purpose: CSakuraDialog��ȡ�ؼ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraControl *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetControl(int ID)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->GetID() == ID)
		{
			return (*iter);
		}

	}

	return NULL;
}

//------------------------------------------------------------------
// @Function:	 GetControl()
// @Purpose: CSakuraDialog��ȡ�ؼ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraControl *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetControl(int ID, UINT nControlType)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->GetID() == ID && (*iter)->GetType() == nControlType)
		{
			return (*iter);
		}

	}

	return NULL;
}

//------------------------------------------------------------------
// @Function:	 GetControlAtPoint()
// @Purpose: CSakuraDialog��ȡ���ؼ����ڿؼ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraControl *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetControlAtPoint(POINT pt)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter) == NULL)
		{
			continue;
		}

		if ((*iter)->ContainsPoint(pt) && (*iter)->GetEnabled() && (*iter)->GetVisible())
		{
			return (*iter);
		}
	}

	return NULL;
}

//------------------------------------------------------------------
// @Function:	 RemoveControl()
// @Purpose: CSakuraDialogɾ���ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::RemoveControl(int nID)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->GetID() == nID)
		{
			ClearFocus();

			if (s_pControlFocus == (*iter))
			{
				s_pControlFocus = NULL;
			}
			if (s_pControlPressed == (*iter))
			{
				s_pControlPressed = NULL;
			}
			if (m_pControlMouseOver == (*iter))
			{
				m_pControlMouseOver = NULL;
			}

			SAFE_DELETE((*iter));
			m_vecControls.erase(iter);
		}

	}

}

//------------------------------------------------------------------
// @Function:	 RemoveAllControls()
// @Purpose: CSakuraDialogɾ��ȫ���ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::RemoveAllControls()
{
	if (s_pControlFocus != NULL && s_pControlFocus->m_pDialog == this)
	{
		s_pControlFocus = NULL;
	}
	if (s_pControlPressed != NULL && s_pControlPressed->m_pDialog == this)
	{
		s_pControlPressed = NULL;
	}
	m_pControlMouseOver = NULL;

	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecControls.clear();
}

//------------------------------------------------------------------
// @Function:	 SetCallback()
// @Purpose: CSakuraDialog���ûص�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetCallback(LPCALLBACKSAKURAGUIEVENT pCallback, void * pUserContext)
{
	m_pCallbackEvent = pCallback;
	m_pCallbackEventUserContext = pUserContext;
}

//------------------------------------------------------------------
// @Function:	 EnableNonUserEvents()
// @Purpose: CSakuraDialogʹ�����û��¼�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::EnableNonUserEvents(bool bEnable)
{
	m_bNonUserEvents = bEnable;
}

//------------------------------------------------------------------
// @Function:	 EnableKeyboardInput()
// @Purpose: CSakuraDialogʹ�ܼ��������¼�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::EnableKeyboardInput(bool bEnable)
{
	m_bKeyboardInput = bEnable;
}

//------------------------------------------------------------------
// @Function:	 EnableMouseInput()
// @Purpose: CSakuraDialogʹ����������¼�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::EnableMouseInput(bool bEnable)
{
	m_bMouseInput = bEnable;
}

//------------------------------------------------------------------
// @Function:	 IsKeyboardInputEnabled()
// @Purpose: CSakuraDialog�жϼ�������ʹ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURADIALOG_CALLMETHOD CSakuraDialog::IsKeyboardInputEnabled() const
{
	return m_bKeyboardInput;
}

//------------------------------------------------------------------
// @Function:	 SendEvent()
// @Purpose: CSakuraDialog���ͻص��¼�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SendEvent(UINT nEvent, bool bTriggeredByUser, CSakuraControl * pControl)
{
	if (m_pCallbackEvent == NULL)
	{
		return;
	}

	if (!bTriggeredByUser && !m_bNonUserEvents)
	{
		return;
	}

	m_pCallbackEvent(nEvent, pControl->GetID(), pControl, m_pCallbackEventUserContext);
}

//------------------------------------------------------------------
// @Function:	 RequestFocus()
// @Purpose: CSakuraDialog���󽹵�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::RequestFocus(CSakuraControl * pControl)
{
	if (s_pControlFocus == pControl)
	{
		return;
	}

	if (!pControl->CanHaveFocus())
	{
		return;
	}

	if (s_pControlFocus)
	{
		s_pControlFocus->OnFocusOut();
	}

	pControl->OnFocusIn();
	s_pControlFocus = pControl;
}

//------------------------------------------------------------------
// @Function:	 ClearFocus()
// @Purpose: CSakuraDialog����ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::ClearFocus()
{
	if (s_pControlFocus)
	{
		s_pControlFocus->OnFocusOut();
		s_pControlFocus = NULL;
	}

	ReleaseCapture();
}
