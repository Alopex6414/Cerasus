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
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnMouseMove(POINT pt)
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
// @Function:	 InitDefaultElement()
// @Purpose: CSakuraDialog初始化默认控件资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::InitDefaultElement()
{
	CUFont sFont = { 0 };

	wcscpy_s(sFont.strFontName, MAX_PATH, _T("Consolas"));
	sFont.nFontSize = 16;
	SetFontRes(&sFont);

	// CSakuraStatic 静态控件(默认)
	{
		CSakuraElement* pElement = new CSakuraElement(m_pManager->GetDevice());
		pElement->GetFontBlend().AddFont(SAKURA_STATE_NORMAL, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_DISABLED, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_FOCUS, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_MOUSEOVER, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_PRESSED, sFont.strFontName, sFont.nFontSize);
		SetDefaultElement(SAKURA_CONTROL_STATIC, 0, &pElement);
	}

	// CSakuraButton 按钮控件(默认)
	{
		CSakuraElement* pElement = new CSakuraElement(m_pManager->GetDevice());
		pElement->GetFontBlend().AddFont(SAKURA_STATE_NORMAL, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_DISABLED, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_FOCUS, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_MOUSEOVER, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_PRESSED, sFont.strFontName, sFont.nFontSize);
		SetDefaultElement(SAKURA_CONTROL_BUTTON, 0, &pElement);
	}

	// CSakuraCheckBox 复选框控件(默认)
	{
		CSakuraElement* pElement = new CSakuraElement(m_pManager->GetDevice());
		pElement->GetFontBlend().AddFont(SAKURA_STATE_NORMAL, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_DISABLED, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_FOCUS, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_MOUSEOVER, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_PRESSED, sFont.strFontName, sFont.nFontSize);
		SetDefaultElement(SAKURA_CONTROL_CHECKBOX, 0, &pElement);
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

	srand((unsigned int)time(NULL));

	m_colorTopLeft = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	m_colorTopRight = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	m_colorBottomLeft = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	m_colorBottomRight = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);

	m_pDialogGraphics = NULL;
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
	RemoveAllDefaultElements();
	SAFE_DELETE(m_pDialogGraphics);
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
	InitDefaultElement();
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraDialog窗口初始化处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnCreate(CSakuraResourceManager * pManager, CUUint sUnit)
{
	m_pManager = pManager;
	m_pDialogGraphics = new CCerasusUnit(m_pManager->GetDevice());
	m_pDialogGraphics->CCerasusUnitInit(sUnit);
	InitDefaultElement();
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraDialog窗口初始化处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnCreate(CSakuraResourceManager * pManager, CUUintEx sUnit)
{
	m_pManager = pManager;
	m_pDialogGraphics = new CCerasusUnit(m_pManager->GetDevice());
	m_pDialogGraphics->CCerasusUnitInit(sUnit);
	InitDefaultElement();
}

//------------------------------------------------------------------
// @Function:	 OnLost()
// @Purpose: CSakuraDialog窗口丢失设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnLost()
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		for (auto iter2 = (*iter)->GetElements().begin(); iter2 != (*iter)->GetElements().end(); ++iter2)
		{
			(*iter2)->GetFontBlend().OnLostDevice();
			(*iter2)->GetTextureBlend().OnLostDevice();
		}
	}

	if (m_pDialogGraphics)
	{
		m_pDialogGraphics->CCerasusUnitReset();
	}
	
}

//------------------------------------------------------------------
// @Function:	 OnReset()
// @Purpose: CSakuraDialog窗口重置设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnReset()
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		for (auto iter2 = (*iter)->GetElements().begin(); iter2 != (*iter)->GetElements().end(); ++iter2)
		{
			(*iter2)->GetFontBlend().OnResetDevice();
			(*iter2)->GetTextureBlend().OnResetDevice();
		}
	}

	if (m_pDialogGraphics)
	{
		m_pDialogGraphics->CCerasusUnitReCreate();
	}

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
// @Function:	 AddCheckBox()
// @Purpose: CSakuraDialog窗口添加复选框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddCheckBox(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bChecked, UINT nHotkey, bool bIsDefault, CSakuraCheckBox ** ppCreated)
{
	CSakuraCheckBox* pCheckBox = new CSakuraCheckBox(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pCheckBox;
	}

	if (pCheckBox == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pCheckBox));
	
	pCheckBox->SetID(ID);
	pCheckBox->SetText(strText);
	pCheckBox->SetLocation(x, y);
	pCheckBox->SetSize(width, height);
	pCheckBox->SetHotkey(nHotkey);
	pCheckBox->m_bIsDefault = bIsDefault;
	pCheckBox->SetChecked(bChecked);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddRadioButton()
// @Purpose: CSakuraDialog窗口添加单选框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddRadioButton(int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height, bool bChecked, UINT nHotkey, bool bIsDefault, CSakuraRadioButton ** ppCreated)
{
	CSakuraRadioButton* pRadioButton = new CSakuraRadioButton();

	if (ppCreated != NULL)
	{
		*ppCreated = pRadioButton;
	}

	if (pRadioButton == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pRadioButton));

	pRadioButton->SetID(ID);
	pRadioButton->SetText(strText);
	pRadioButton->SetButtonGroup(nButtonGroup);
	pRadioButton->SetLocation(x, y);
	pRadioButton->SetSize(width, height);
	pRadioButton->SetHotkey(nHotkey);
	pRadioButton->SetChecked(bChecked);
	pRadioButton->m_bIsDefault = bIsDefault;
	pRadioButton->SetChecked(bChecked);

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

	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		if ((*iter)->nControlType == pControl->GetType())
		{
			CSakuraElement** ppElement = &(pControl->GetElement((*iter)->iElement));
			
			SAFE_DELETE(*ppElement);
			*ppElement = (*iter)->pElement;
		}

	}

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

	if ((*ppElement) == NULL)
	{
		(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	}
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
	CSakuraElement** ppElement = &(pControl->GetElement(iElement));
	CUUint* pTexture = GetTextureRes(Index);

	if ((*ppElement) == NULL)
	{
		(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	}
	(*ppElement)->GetTextureBlend().AddTexture(eType, *pTexture);

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
	CSakuraElement** ppElement = &(pControl->GetElement(iElement));
	CUUintEx* pTexture = GetTextureExRes(Index);

	if ((*ppElement) == NULL)
	{
		(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	}
	(*ppElement)->GetTextureBlend().AddTexture(eType, *pTexture);

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
// @Function:	 GetCheckBox()
// @Purpose: CSakuraDialog窗口获取复选框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraCheckBox *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetCheckBox(int ID)
{
	return (CSakuraCheckBox*)GetControl(ID, SAKURA_CONTROL_CHECKBOX);
}

//------------------------------------------------------------------
// @Function:	 GetRadioButton()
// @Purpose: CSakuraDialog窗口获取单选框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraRadioButton *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetRadioButton(int ID)
{
	return (CSakuraRadioButton*)GetControl(ID, SAKURA_CONTROL_RADIOBUTTON);
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
// @Function:	 ClearRadioButtonGroup()
// @Purpose: CSakuraDialog清除单选按钮组别
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::ClearRadioButtonGroup(UINT nGroup)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->GetType() == SAKURA_CONTROL_RADIOBUTTON)
		{
			CSakuraRadioButton* pRadioButton = dynamic_cast<CSakuraRadioButton*>(*iter);
			if (pRadioButton->GetButtonGroup() == nGroup)
			{
				pRadioButton->SetChecked(false, false);
			}

		}

	}

}

//------------------------------------------------------------------
// @Function:	 ClearComboBox()
// @Purpose: CSakuraDialog清除下拉列表框
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::ClearComboBox(int nID)
{
	
}

//------------------------------------------------------------------
// @Function:	 SetDefaultElement()
// @Purpose: CSakuraDialog设置默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::SetDefaultElement(UINT nControlType, UINT iElement, CSakuraElement ** ppElement)
{
	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		if ((*iter)->nControlType == nControlType && (*iter)->iElement == iElement)
		{
			SAFE_DELETE((*iter)->pElement);
			(*iter)->pElement = *ppElement;
			return S_OK;
		}

	}

	m_vecDefaultControls.push_back(NULL);
	CSakuraElementHolder** ppNewElementHolder = &(*(m_vecDefaultControls.end() - 1));
	(*ppNewElementHolder) = new CSakuraElementHolder();
	(*ppNewElementHolder)->nControlType = nControlType;
	(*ppNewElementHolder)->iElement = iElement;
	(*ppNewElementHolder)->pElement = *ppElement;

	return S_OK;
}


//------------------------------------------------------------------
// @Function:	 GetDefaultElement()
// @Purpose: CSakuraDialog获取默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetDefaultElement(UINT nControlType, UINT iElement)
{
	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		if ((*iter)->nControlType == nControlType && (*iter)->iElement == iElement)
		{
			return (*iter)->pElement;
		}
	}

	return NULL;
}

//------------------------------------------------------------------
// @Function:	 RemoveAllDefaultElements()
// @Purpose: CSakuraDialog移除全部默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::RemoveAllDefaultElements()
{
	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		SAFE_DELETE((*iter)->pElement);
		SAFE_DELETE((*iter));
	}
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

//------------------------------------------------------------------
// @Function:	 OnRender()
// @Purpose: CSakuraDialog窗口渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::OnRender()
{
	if (m_pManager == NULL)
	{
		return E_FAIL;
	}

	if (!m_bVisible)
	{
		return S_OK;
	}

	// 渲染窗口
	if (m_pDialogGraphics)
	{
		m_pDialogGraphics->CCerasusUnitMatrixTransform();
		m_pDialogGraphics->CCerasusUnitPaddingVertexAndIndex();
		m_pDialogGraphics->CCerasusUnitSetAlphaBlendEnable();
		m_pDialogGraphics->CCerasusUnitSetRenderState();
		m_pDialogGraphics->CCerasusUnitRender();
		m_pDialogGraphics->CCerasusUnitSetAlphaBlendDisable();
	}

	// 渲染控件
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		(*iter)->Render();
	}

	return S_OK;
}
