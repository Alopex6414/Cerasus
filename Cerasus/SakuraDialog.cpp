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

// SakuraGUI 窗口类(UI)
CSakuraControl*	CSakuraDialog::s_pControlFocus = NULL;			// CCerasusDialog 获得焦点控件
CSakuraControl*	CSakuraDialog::s_pControlPressed = NULL;		// CCerasusDialog 当前按下控件

//------------------------------------------------------------------
// @Function:	 OnMouseMove()
// @Purpose: CSakuraDialog鼠标移动
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
// @Purpose: CSakuraDialog构造函数
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

	m_pManager = NULL;
	m_pCallbackEvent = NULL;
	m_pCallbackEventUserContext = NULL;

	m_bNonUserEvents = false;
	m_bKeyboardInput = false;
	m_bMouseInput = true;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraDialog()
// @Purpose: CSakuraDialog析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraDialog::~CSakuraDialog()
{
	RemoveAllControls();
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraDialog窗口初始化处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnCreate(CSakuraResourceManager * pManager)
{
	m_pManager = pManager;
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CSakuraDialog窗口消息处理
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
// @Purpose: CSakuraDialog窗口添加静态控件
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
// @Purpose: CSakuraDialog窗口添加按钮控件
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
// @Purpose: CSakuraDialog窗口添加控件
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
// @Purpose: CSakuraDialog窗口初始化控件
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
// @Function:	 AddFont()
// @Purpose: CSakuraDialog窗口控件添加字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddFont(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index)
{
	CSakuraControl* pControl = GetControl(ID, nControlType);
	CSakuraElement** ppElement = &(pControl->GetElement(iElement));
	CUFont* pFont = GetFontRes(Index);

	if (*ppElement)
	{
		SAFE_DELETE(*ppElement);
	}

	(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	(*ppElement)->GetFontBlend().AddFont(eType, pFont->strFontName, pFont->nFontSize);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraDialog窗口控件添加纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddTexture(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index)
{
	CSakuraControl* pControl = GetControl(ID, nControlType);
	CSakuraElement* pElement = pControl->GetElement(iElement);
	CUUint* pTexture = GetTextureRes(Index);

	if (pElement)
	{
		SAFE_DELETE(pElement);
	}

	pElement = new CSakuraElement(m_pManager->GetDevice());
	pElement->GetTextureBlend().AddTexture(eType, *pTexture);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddTextureEx()
// @Purpose: CSakuraDialog窗口控件添加纹理Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddTextureEx(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index)
{
	CSakuraControl* pControl = GetControl(ID, nControlType);
	CSakuraElement* pElement = pControl->GetElement(iElement);
	CUUint* pTexture = GetTextureRes(Index);

	if (pElement)
	{
		SAFE_DELETE(pElement);
	}

	pElement = new CSakuraElement(m_pManager->GetDevice());
	pElement->GetTextureBlend().AddTexture(eType, *pTexture);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetStatic()
// @Purpose: CSakuraDialog窗口获取静态控件
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
// @Purpose: CSakuraDialog窗口获取按钮控件
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
// @Purpose: CSakuraDialog获取控件指针
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
// @Purpose: CSakuraDialog获取控件指针
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
// @Purpose: CSakuraDialog获取鼠标控件所在控件指针
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
// @Purpose: CSakuraDialog删除控件
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
// @Purpose: CSakuraDialog删除全部控件
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
// @Purpose: CSakuraDialog设置回调函数
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
// @Purpose: CSakuraDialog使能无用户事件
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
// @Purpose: CSakuraDialog使能键盘输入事件
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
// @Purpose: CSakuraDialog使能鼠标输入事件
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
// @Purpose: CSakuraDialog判断键盘输入使能
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
// @Purpose: CSakuraDialog发送回调事件
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
// @Purpose: CSakuraDialog请求焦点
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
// @Function:	 GetVisible()
// @Purpose: CSakuraDialog获取窗口是否可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURADIALOG_CALLMETHOD CSakuraDialog::GetVisible()
{
	return m_bVisible;
}

//------------------------------------------------------------------
// @Function:	 SetVisible()
// @Purpose: CSakuraDialog设置窗口是否可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

//------------------------------------------------------------------
// @Function:	 SetBackgroundColors()
// @Purpose: CSakuraDialog设置窗口背景颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetBackgroundColors(D3DCOLOR colorAllCorners)
{
	SetBackgroundColors(colorAllCorners, colorAllCorners, colorAllCorners, colorAllCorners);
}

//------------------------------------------------------------------
// @Function:	 SetBackgroundColors()
// @Purpose: CSakuraDialog设置窗口背景颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight)
{
	m_colorTopLeft = colorTopLeft;
	m_colorTopRight = colorTopRight;
	m_colorBottomLeft = colorBottomLeft;
	m_colorBottomRight = colorBottomRight;
}

//------------------------------------------------------------------
// @Function:	 GetLocation()
// @Purpose: CSakuraDialog获取窗口坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::GetLocation(POINT & Pt) const
{
	Pt.x = m_nX;
	Pt.y = m_nY;
}

//------------------------------------------------------------------
// @Function:	 SetLocation()
// @Purpose: CSakuraDialog设置窗口坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetLocation(int x, int y)
{
	m_nX = x;
	m_nY = y;
}

//------------------------------------------------------------------
// @Function:	 SetSize()
// @Purpose: CSakuraDialog设置窗口大小
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

//------------------------------------------------------------------
// @Function:	 GetWidth()
// @Purpose: CSakuraDialog获取窗口宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURADIALOG_CALLMETHOD CSakuraDialog::GetWidth()
{
	return m_nWidth;
}

//------------------------------------------------------------------
// @Function:	 GetHeight()
// @Purpose: CSakuraDialog获取窗口高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURADIALOG_CALLMETHOD CSakuraDialog::GetHeight()
{
	return m_nHeight;
}

//------------------------------------------------------------------
// @Function:	 AddFontRes()
// @Purpose: CSakuraDialog添加字体资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURADIALOG_CALLMETHOD CSakuraDialog::SetFontRes(CUFont * pFont)
{
	if (m_pManager == NULL)
	{
		return -1;
	}

	return m_pManager->AddFont(pFont);
}

//------------------------------------------------------------------
// @Function:	 AddTextrueRes()
// @Purpose: CSakuraDialog添加纹理资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURADIALOG_CALLMETHOD CSakuraDialog::SetTextrueRes(CUUint * pTexture)
{
	if (m_pManager == NULL)
	{
		return -1;
	}

	return m_pManager->AddTexture(pTexture);
}

//------------------------------------------------------------------
// @Function:	 AddTextrueExRes()
// @Purpose: CSakuraDialog添加纹理资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURADIALOG_CALLMETHOD CSakuraDialog::SetTextrueExRes(CUUintEx * pTexture)
{
	if (m_pManager == NULL)
	{
		return -1;
	}

	return m_pManager->AddTexture(pTexture);
}

//------------------------------------------------------------------
// @Function:	 GetFontRes()
// @Purpose: CSakuraDialog获取字体资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUFont *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetFontRes(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetFontNode(Index);
}

//------------------------------------------------------------------
// @Function:	 GetTextureRes()
// @Purpose: CSakuraDialog获取纹理资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUUint *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetTextureRes(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetTextureNode(Index);
}

//------------------------------------------------------------------
// @Function:	 GetTextureExRes()
// @Purpose: CSakuraDialog获取纹理资源Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUUintEx *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetTextureExRes(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetTextureNodeEx(Index);
}

//------------------------------------------------------------------
// @Function:	 ClearFocus()
// @Purpose: CSakuraDialog清除控件焦点
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
