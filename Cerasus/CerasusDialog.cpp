/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusDialog.cpp
* @brief	This File is CerasusDialog DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-24	v1.00a	alopex	Create Project.
*/
#include "CerasusDialog.h"

// CreasusUI 渲染对话框类(UI)

// Class Static Var
double				CCerasusDialog::s_fTimeRefresh = 0.0f;
CCerasusControl*	CCerasusDialog::s_pControlFocus = NULL;			// 当前有焦点的控件
CCerasusControl*	CCerasusDialog::s_pControlPressed = NULL;		// 当前被按压的控件

//extern HWND g_hWnd;

//------------------------------------------------------------------
// @Function:	 CCerasusDialog()
// @Purpose: CCerasusDialog构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusDialog::CCerasusDialog()
{
	m_nX = 0;
	m_nY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_pManager = NULL;
	m_bVisible = true;
	m_bCaption = false;
	m_bMinimized = false;
	m_bDrag = false;
	m_wszCaption[0] = L'\0';
	m_nCaptionHeight = 18;

	m_colorTopLeft = 0;
	m_colorTopRight = 0;
	m_colorBottomLeft = 0;
	m_colorBottomRight = 0;

	m_pCallbackEvent = NULL;
	m_pCallbackEventUserContext = NULL;

	m_fTimeLastRefresh = 0;

	m_pControlMouseOver = NULL;

	m_pNextDialog = this;
	m_pPrevDialog = this;

	m_nDefaultControlID = 0xffff;
	m_bNonUserEvents = false;
	m_bKeyboardInput = false;
	m_bMouseInput = true;

}

//------------------------------------------------------------------
// @Function:	 ~CCerasusDialog()
// @Purpose: CCerasusDialog析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusDialog::~CCerasusDialog()
{
	RemoveAllControls();

	m_vecFonts.clear();
	m_vecTextures.clear();

	for (int i = 0; i < m_vecDefaultElements.size(); ++i)
	{
		SAFE_DELETE(m_vecDefaultElements[i]);
	}

	m_vecDefaultElements.clear();
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusDialog初始化窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::Init(CCerasusResourceManager * pManager, bool bRegisterDialog)
{
	m_pManager = pManager;

	if (bRegisterDialog)
	{
		m_pManager->RegisterDialog(this);
	}

	CUUintEx sUnit = { 0 };
	m_pManager->AddTexture(sUnit);
	InitDefaultElements();
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusDialog初始化窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::Init(CCerasusResourceManager * pManager, bool bRegisterDialog, CUUint sUnit)
{
	m_pManager = pManager;

	if (bRegisterDialog)
	{
		m_pManager->RegisterDialog(this);
	}

	m_pManager->AddTexture(sUnit);
	InitDefaultElements();
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusDialog初始化窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::Init(CCerasusResourceManager * pManager, bool bRegisterDialog, CUUintEx sUnit)
{
	m_pManager = pManager;

	if (bRegisterDialog)
	{
		m_pManager->RegisterDialog(this);
	}

	m_pManager->AddTexture(sUnit);
	InitDefaultElements();
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusDialog初始化窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool bHandled = false;

	// 窗口不可见，不需要处理任何消息
	if (!m_bVisible)
	{
		return false;
	}

	// 窗口标题使能，检测窗口标题栏单击状态
	if (m_bCaption)
	{
		if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONDBLCLK)
		{
			POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };

			if (mousePoint.x >= m_nX && mousePoint.x < m_nX + m_nWidth &&
				mousePoint.y >= m_nY && mousePoint.y < m_nY + m_nCaptionHeight)
			{
				m_bDrag = true;
				//SetCapture(g_hWnd);		// 需要窗口句柄
				return true;
			}
		}
		else if (uMsg == WM_LBUTTONUP && m_bDrag)
		{
			POINT mousePoint = { short(LOWORD(lParam)), short(HIWORD(lParam)) };

			if (mousePoint.x >= m_nX && mousePoint.x < m_nX + m_nWidth &&
				mousePoint.y >= m_nY && mousePoint.y < m_nY + m_nCaptionHeight)
			{
				ReleaseCapture();
				m_bDrag = false;
				m_bMinimized = !m_bMinimized;
				return true;
			}
		}
	}

	// 如果窗口处于最小化状态，不用发送消息给控件
	if (m_bMinimized)
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
		case WM_SIZE:
		case WM_MOVE:
		{
			POINT pt = { -1, -1 };
			OnMouseMove(pt);
			break;
		}

		case WM_ACTIVATEAPP:
			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (wParam)
					s_pControlFocus->OnFocusIn();
				else
					s_pControlFocus->OnFocusOut();
			}
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (s_pControlFocus->HandleKeyboard(uMsg, wParam, lParam))
					return true;
			}

			if (uMsg == WM_KEYDOWN && (!s_pControlFocus || (s_pControlFocus->GetType() != CERASUS_CONTROL_EDITBOX && s_pControlFocus->GetType() != CERASUS_CONTROL_IMEEDITBOX)))
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
					if (s_pControlFocus != NULL)
					{
						return OnCycleFocus(true);
					}
					break;

				case VK_LEFT:
				case VK_UP:
					if (s_pControlFocus != NULL)
					{
						return OnCycleFocus(false);
					}
					break;

				case VK_TAB:
				{
					bool bShiftDown = ((GetKeyState(VK_SHIFT) & 0x8000) != 0);
					return OnCycleFocus(!bShiftDown);
				}
				}
			}

			break;
		}


		// Mouse messages
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

			if (m_bCaption)
			{
				mousePoint.y -= m_nCaptionHeight;
			}

			if (s_pControlFocus && s_pControlFocus->m_pDialog == this && s_pControlFocus->GetEnabled())
			{
				if (s_pControlFocus->HandleMouse(uMsg, mousePoint, wParam, lParam))
				{
					return true;
				}
			}

			CCerasusControl* pControl = GetControlAtPoint(mousePoint);
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

		case WM_CAPTURECHANGED:
		{
			if ((HWND)lParam != hWnd)
			{
				m_bDrag = false;
			}
		}
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 AddStatic()
// @Purpose: CCerasusDialog窗口添加静态控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault, CCerasusStatic ** ppCreated)
{
	HRESULT hr = S_OK;

	CCerasusStatic* pStatic = new CCerasusStatic(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pStatic;
	}

	if (pStatic == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = AddControl(pStatic);
	if (FAILED(hr))
	{
		return hr;
	}

	pStatic->SetID(ID);
	pStatic->SetText(strText);
	pStatic->SetLocation(x, y);
	pStatic->SetSize(width, height);
	pStatic->m_bIsDefault = bIsDefault;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddButton()
// @Purpose: CCerasusDialog窗口添加按钮控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, CCerasusButton ** ppCreated)
{
	HRESULT hr = S_OK;

	CCerasusButton* pButton = new CCerasusButton(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pButton;
	}

	if (pButton == NULL)
	{
		return E_OUTOFMEMORY;
	}

	hr = AddControl(pButton);
	if (FAILED(hr))
	{
		return hr;
	}

	pButton->SetID(ID);
	pButton->SetText(strText);
	pButton->SetLocation(x, y);
	pButton->SetSize(width, height);
	pButton->SetHotkey(nHotkey);
	pButton->m_bIsDefault = bIsDefault;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddStatic()
// @Purpose: CCerasusDialog窗口添加控件基类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::AddControl(CCerasusControl * pControl)
{
	HRESULT hr = S_OK;

	// 初始化控件
	hr = InitControl(pControl);
	if (FAILED(hr))
	{
		return DXTRACE_ERR(L"CCerasusDialog::InitControl", hr);
	}

	// 添加控件向量
	m_vecControls.push_back(pControl);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 InitControl()
// @Purpose: CCerasusDialog窗口初始化控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::InitControl(CCerasusControl * pControl)
{
	// 检测控件基类的指针是否为空
	if (pControl == NULL)
	{
		return E_INVALIDARG;
	}

	// 在控件向量的最后一个添加控件
	pControl->m_nIndex = m_vecControls.size();

	// 从默认元素中挑选合适的控件资源
	for (int i = 0; i < m_vecDefaultElements.size(); ++i)
	{
		// 控件类型相同!!
		if (m_vecDefaultElements[i]->nControlType == pControl->GetType())
		{
			// 设置控件的元素
			pControl->SetElement(m_vecDefaultElements[i]->iElement, &m_vecDefaultElements[i]->Element);
		}
	}

	// 控件初始化函数响应
	VERIFY(pControl->OnInit());

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetStatic()
// @Purpose: CCerasusDialog窗口获取静态控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusStatic * CCerasusDialog::GetStatic(int ID)
{
	return (CCerasusStatic*)GetControl(ID, CERASUS_CONTROL_STATIC);
}

//------------------------------------------------------------------
// @Function:	 GetButton()
// @Purpose: CCerasusDialog窗口获取按钮控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusButton * CCerasusDialog::GetButton(int ID)
{
	return (CCerasusButton*)GetControl(ID, CERASUS_CONTROL_BUTTON);
}

//------------------------------------------------------------------
// @Function:	 GetControl()
// @Purpose: CCerasusDialog窗口获取控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl * CCerasusDialog::GetControl(int ID)
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
// @Purpose: CCerasusDialog窗口获取控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl * CCerasusDialog::GetControl(int ID, UINT nControlType)
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
// @Function:	 GetNextControl()
// @Purpose: CCerasusDialog获取窗口下一个控件指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl * __stdcall CCerasusDialog::GetNextControl(CCerasusControl * pControl)
{
	int Index = pControl->m_nIndex + 1;

	CCerasusDialog* pDialog = pControl->m_pDialog;

	while (Index >= (int)pDialog->m_vecControls.size())
	{
		pDialog = pDialog->m_pNextDialog;
		Index = 0;
	}

	return pDialog->m_vecControls[Index];
}

//------------------------------------------------------------------
// @Function:	 GetNextControl()
// @Purpose: CCerasusDialog获取窗口上一个控件指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl * __stdcall CCerasusDialog::GetPrevControl(CCerasusControl * pControl)
{
	int Index = pControl->m_nIndex - 1;

	CCerasusDialog* pDialog = pControl->m_pDialog;

	while (Index < 0)
	{
		pDialog = pDialog->m_pPrevDialog;
		if (pDialog == NULL)
		{
			pDialog = pControl->m_pDialog;
		}

		Index = pDialog->m_vecControls.size() - 1;
	}

	return pDialog->m_vecControls[Index];
}

//------------------------------------------------------------------
// @Function:	 RemoveControl()
// @Purpose: CCerasusDialog移除控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::RemoveControl(int ID)
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->GetID() == ID)
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
// @Purpose: CCerasusDialog移除所有控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::RemoveAllControls()
{
	if (s_pControlFocus && s_pControlFocus->m_pDialog == this)
		s_pControlFocus = NULL;
	if (s_pControlPressed && s_pControlPressed->m_pDialog == this)
		s_pControlPressed = NULL;

	m_pControlMouseOver = NULL;

	for (int i = 0; i < m_vecControls.size(); ++i)
	{
		SAFE_DELETE(m_vecControls[i]);
	}

	m_vecControls.clear();
}

//------------------------------------------------------------------
// @Function:	 SetCallback()
// @Purpose: CCerasusDialog设置回调函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetCallback(LPCALLBACKCERASUSGUIEVENT pCallback, void * pUserContext)
{
	m_pCallbackEvent = pCallback;
	m_pCallbackEventUserContext = pUserContext;
}

//------------------------------------------------------------------
// @Function:	 EnableNonUserEvents()
// @Purpose: CCerasusDialog使能无用户事件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::EnableNonUserEvents(bool bEnable)
{
	m_bNonUserEvents = bEnable;
}

//------------------------------------------------------------------
// @Function:	 EnableKeyboardInput()
// @Purpose: CCerasusDialog使能键盘输入
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::EnableKeyboardInput(bool bEnable)
{
	m_bKeyboardInput = bEnable;
}

//------------------------------------------------------------------
// @Function:	 EnableMouseInput()
// @Purpose: CCerasusDialog使能鼠标输入
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::EnableMouseInput(bool bEnable)
{
	m_bMouseInput = bEnable;
}

//------------------------------------------------------------------
// @Function:	 IsKeyboardInputEnabled()
// @Purpose: CCerasusDialog判断是否渐染输入使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::IsKeyboardInputEnabled() const
{
	return m_bKeyboardInput;
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CCerasusDialog刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::Refresh()
{
	if (s_pControlFocus)
	{
		s_pControlFocus->OnFocusOut();
	}

	if (m_pControlMouseOver)
	{
		m_pControlMouseOver->OnMouseLeave();
	}

	s_pControlFocus = NULL;
	s_pControlPressed = NULL;
	m_pControlMouseOver = NULL;

	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		(*iter)->Refresh();
	}

	if (m_bKeyboardInput)
		FocusDefaultControl();
}

//------------------------------------------------------------------
// @Function:	 GetControlAtPoint()
// @Purpose: CCerasusDialog获取鼠标所在的控件指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusControl * CCerasusDialog::GetControlAtPoint(POINT pt)
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
// @Function:	 GetControlEnabled()
// @Purpose: CCerasusDialog获取控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::GetControlEnabled(int ID)
{
	CCerasusControl* pControl = GetControl(ID);
	if (pControl == NULL)
	{
		return false;
	}

	return pControl->GetEnabled();
}

//------------------------------------------------------------------
// @Function:	 SetControlEnabled()
// @Purpose: CCerasusDialog设置控件使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetControlEnabled(int ID, bool bEnabled)
{
	CCerasusControl* pControl = GetControl(ID);
	if (pControl == NULL)
	{
		return;
	}

	pControl->SetEnabled(bEnabled);
}

//------------------------------------------------------------------
// @Function:	 ClearRadioButtonGroup()
// @Purpose: CCerasusDialog清除RadioButton组
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::ClearRadioButtonGroup(UINT nGroup)
{
}

//------------------------------------------------------------------
// @Function:	 ClearComboBox()
// @Purpose: CCerasusDialog清除ComboBox
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::ClearComboBox(int ID)
{
}

//------------------------------------------------------------------
// @Function:	 SetDefaultElement()
// @Purpose: CCerasusDialog设置默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::SetDefaultElement(UINT nControlType, UINT iElement, CCerasusElement * pElement)
{
	for (auto iter = m_vecDefaultElements.begin(); iter != m_vecDefaultElements.end(); ++iter)
	{
		if ((*iter)->nControlType == nControlType && (*iter)->iElement == iElement)
		{
			(*iter)->Element = *pElement;
			return S_OK;
		}
	}

	CerasusElementHolder* pNewHolder = new CerasusElementHolder();
	if (pNewHolder == NULL)
	{
		return E_OUTOFMEMORY;
	}

	pNewHolder->nControlType = nControlType;
	pNewHolder->iElement = iElement;
	pNewHolder->Element = *pElement;

	m_vecDefaultElements.push_back(pNewHolder);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetDefaultElement()
// @Purpose: CCerasusDialog获取默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusElement * CCerasusDialog::GetDefaultElement(UINT nControlType, UINT iElement)
{
	for (auto iter = m_vecDefaultElements.begin(); iter != m_vecDefaultElements.end(); ++iter)
	{
		if ((*iter)->nControlType == nControlType && (*iter)->iElement == iElement)
		{
			return &((*iter)->Element);
		}
	}

	return NULL;
}

//------------------------------------------------------------------
// @Function:	 SetFont()
// @Purpose: CCerasusDialog设置字体元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::SetFont(UINT Index, LPWSTR strFontName, int nFontSize)
{
	for (UINT i = m_vecFonts.size(); i <= Index; ++i)
	{
		m_vecFonts.push_back(-1);
	}

	int iFont = m_pManager->AddFont(strFontName, nFontSize);

	m_vecFonts[Index] = iFont;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetFont()
// @Purpose: CCerasusDialog获取字体元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont * CCerasusDialog::GetFont(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetFontNode(m_vecFonts[Index]);
}

//------------------------------------------------------------------
// @Function:	 SetTexture()
// @Purpose: CCerasusDialog设置纹理元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::SetTexture(UINT Index, CUUint sUnit)
{
	for (UINT i = m_vecTextures.size(); i <= Index; ++i)
	{
		m_vecTextures.push_back(-1);
	}

	int iTexture = m_pManager->AddTexture(sUnit);

	m_vecTextures[Index] = iTexture;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 SetTexture()
// @Purpose: CCerasusDialog设置纹理元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::SetTexture(UINT Index, CUUintEx sUnit)
{
	for (UINT i = m_vecTextures.size(); i <= Index; ++i)
	{
		m_vecTextures.push_back(-1);
	}

	int iTexture = m_pManager->AddTexture(sUnit);

	m_vecTextures[Index] = iTexture;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetTexture()
// @Purpose: CCerasusDialog获取纹理元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit * CCerasusDialog::GetTexture(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetTextureNode(m_vecTextures[Index]);
}

//------------------------------------------------------------------
// @Function:	 SendEvent()
// @Purpose: CCerasusDialog设置控件事件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SendEvent(UINT nEvent, bool bTriggeredByUser, CCerasusControl * pControl)
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
// @Purpose: CCerasusDialog请求获取焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::RequestFocus(CCerasusControl * pControl)
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
// @Function:	 DrawRect()
// @Purpose: CCerasusDialog绘制矩形
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::DrawRect(RECT * pRect, D3DCOLOR color)
{
	return DrawRect9(pRect, color);
}

//------------------------------------------------------------------
// @Function:	 DrawRect()
// @Purpose: CCerasusDialog绘制矩形
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::DrawRect9(RECT * pRect, D3DCOLOR color)
{

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DrawText()
// @Purpose: CCerasusDialog绘制文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::DrawText(LPCWSTR strText, CCerasusElement * pElement, RECT * prcDest, bool bShadow, int nCount)
{
	return DrawText9(strText, pElement, prcDest, bShadow, nCount);
}

//------------------------------------------------------------------
// @Function:	 DrawText9()
// @Purpose: CCerasusDialog绘制文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CCerasusDialog::DrawText9(LPCWSTR strText, CCerasusElement * pElement, RECT * prcDest, bool bShadow, int nCount)
{
	HRESULT hr = S_OK;

	if (pElement->m_FontColor.Current.a == 0)
	{
		return S_OK;
	}

	RECT rcScreen = *prcDest;
	OffsetRect(&rcScreen, m_nX, m_nY);

	if (m_bCaption)
	{
		OffsetRect(&rcScreen, 0, m_nCaptionHeight);
	}

	DirectFont* pFontNode = GetFont(pElement->m_iFont);

	if (bShadow)
	{
		RECT rcShadow = rcScreen;
		OffsetRect(&rcShadow, 1, 1);
		hr = pFontNode->DirectFontGetFont()->DrawText(NULL, strText, nCount, &rcShadow, pElement->m_dwTextureFormat, D3DCOLOR_ARGB(DWORD(pElement->m_FontColor.Current.a * 255), 0, 0, 0));
		if (FAILED(hr))
		{
			return hr;
		}

	}

	hr = pFontNode->DirectFontGetFont()->DrawText(NULL, strText, nCount, &rcScreen, pElement->m_dwTextureFormat, pElement->m_FontColor.Current);
	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetVisible()
// @Purpose: CCerasusDialog获取可见属性
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::GetVisible()
{
	return m_bVisible;
}

//------------------------------------------------------------------
// @Function:	 SetVisible()
// @Purpose: CCerasusDialog设置可见属性
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

//------------------------------------------------------------------
// @Function:	 GetMinimized()
// @Purpose: CCerasusDialog获取最小化属性
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::GetMinimized()
{
	return m_bMinimized;
}

//------------------------------------------------------------------
// @Function:	 SetMinimized()
// @Purpose: CCerasusDialog设置最小化属性
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetMinimized(bool bMinimized)
{
	m_bMinimized = bMinimized;
}

//------------------------------------------------------------------
// @Function:	 SetBackgroundColors()
// @Purpose: CCerasusDialog设置背景颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetBackgroundColors(D3DCOLOR colorAllCorners)
{
	SetBackgroundColors(colorAllCorners, colorAllCorners, colorAllCorners, colorAllCorners);
}

//------------------------------------------------------------------
// @Function:	 SetBackgroundColors()
// @Purpose: CCerasusDialog设置背景颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight)
{
	m_colorTopLeft = colorTopLeft;
	m_colorTopRight = colorTopRight;
	m_colorBottomLeft = colorBottomLeft;
	m_colorBottomRight = colorBottomRight;
}

//------------------------------------------------------------------
// @Function:	 EnableCaption()
// @Purpose: CCerasusDialog设置标题栏使能
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::EnableCaption(bool bEnable)
{
	m_bCaption = bEnable;
}

//------------------------------------------------------------------
// @Function:	 GetCaptionHeight()
// @Purpose: CCerasusDialog获取标题栏高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CCerasusDialog::GetCaptionHeight() const
{
	return m_nCaptionHeight;
}

//------------------------------------------------------------------
// @Function:	 GetCaptionHeight()
// @Purpose: CCerasusDialog设置标题栏高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetCaptionHeight(int nHeight)
{
	m_nCaptionHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 SetCaptionText()
// @Purpose: CCerasusDialog设置标题栏文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetCaptionText(const WCHAR * pwszText)
{
	wcscpy_s(m_wszCaption, sizeof(m_wszCaption) / sizeof(m_wszCaption[0]), pwszText);
}

//------------------------------------------------------------------
// @Function:	 GetLocation()
// @Purpose: CCerasusDialog获取窗口位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::GetLocation(POINT & Pt) const
{
	Pt.x = m_nX; 
	Pt.y = m_nY;
}

//------------------------------------------------------------------
// @Function:	 SetLocation()
// @Purpose: CCerasusDialog设置窗口位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetLocation(int x, int y)
{
	m_nX = x;
	m_nY = y;
}

//------------------------------------------------------------------
// @Function:	 SetSize()
// @Purpose: CCerasusDialog设置窗口大小
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::SetSize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

//------------------------------------------------------------------
// @Function:	 GetWidth()
// @Purpose: CCerasusDialog获取窗口宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CCerasusDialog::GetWidth()
{
	return m_nWidth;
}

//------------------------------------------------------------------
// @Function:	 GetHeight()
// @Purpose: CCerasusDialog获取窗口高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CCerasusDialog::GetHeight()
{
	return m_nHeight;
}

//------------------------------------------------------------------
// @Function:	 SetRefreshTime()
// @Purpose: CCerasusDialog设置刷新时间
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CCerasusDialog::SetRefreshTime(float fTime)
{
	s_fTimeRefresh = fTime;
}

//------------------------------------------------------------------
// @Function:	 ClearFocus()
// @Purpose: CCerasusDialog清除控件焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void __stdcall CCerasusDialog::ClearFocus()
{
	if (s_pControlFocus)
	{
		s_pControlFocus->OnFocusOut();
		s_pControlFocus = NULL;
	}

	ReleaseCapture();
}

//------------------------------------------------------------------
// @Function:	 ClearFocus()
// @Purpose: CCerasusDialog清除控件焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::FocusDefaultControl()
{
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		if ((*iter)->m_bIsDefault)
		{
			ClearFocus();

			s_pControlFocus = (*iter);
			s_pControlFocus->OnFocusIn();
			return;
		}

	}

}

//------------------------------------------------------------------
// @Function:	 InitDefaultElements()
// @Purpose: CCerasusDialog初始化默认元素
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::InitDefaultElements()
{
	SetFont(0, (LPWSTR)L"Arial", 14);

	CCerasusElement Element;
	RECT rcTexture;

	// Caption -- 标题栏
	m_CapElement.SetFont(0);
	SetRect(&rcTexture, 17, 269, 241, 287);
	m_CapElement.SetTexture(0, &rcTexture);
	m_CapElement.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_CapElement.m_FontColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_CapElement.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER);
	m_CapElement.m_TextureColor.Blend(CERASUS_STATE_NORMAL, 10.0f);
	m_CapElement.m_FontColor.Blend(CERASUS_STATE_NORMAL, 10.0f);

	// CCerasusStatic -- 静态控件
	Element.SetFont(0);
	Element.m_FontColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);

	SetDefaultElement(CERASUS_CONTROL_STATIC, 0, &Element);

	// CCerasusButton -- 按钮控件
	SetRect(&rcTexture, 0, 0, 136, 54);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.m_FontColor.States[CERASUS_STATE_MOUSEOVER] = D3DCOLOR_ARGB(255, 0, 0, 0);

	SetDefaultElement(CERASUS_CONTROL_BUTTON, 0, &Element);

	// CCerasusButton -- 填充布局
	SetRect(&rcTexture, 136, 0, 252, 54);
	Element.SetTexture(0, &rcTexture, D3DCOLOR_ARGB(0, 255, 255, 255));
	Element.m_TextureColor.States[CERASUS_STATE_MOUSEOVER] = D3DCOLOR_ARGB(160, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(60, 0, 0, 0);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(30, 255, 255, 255);

	SetDefaultElement(CERASUS_CONTROL_BUTTON, 1, &Element);

	// CCerasusCheckBox -- 复选框
	SetRect(&rcTexture, 0, 54, 27, 81);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER);
	Element.m_FontColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(255, 255, 255, 255);

	SetDefaultElement(CERASUS_CONTROL_CHECKBOX, 0, &Element);

	// CCerasusCheckBox -- 选中
	SetRect(&rcTexture, 27, 54, 54, 81);
	Element.SetTexture(0, &rcTexture);

	SetDefaultElement(CERASUS_CONTROL_CHECKBOX, 1, &Element);

	// CCerasusRadioButton -- 单选按钮
	SetRect(&rcTexture, 54, 54, 81, 81);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_VCENTER);
	Element.m_FontColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(255, 255, 255, 255);

	SetDefaultElement(CERASUS_CONTROL_RADIOBUTTON, 0, &Element);

	// CCerasusRadioButton -- 选中
	SetRect(&rcTexture, 81, 54, 108, 81);
	Element.SetTexture(0, &rcTexture);

	SetDefaultElement(CERASUS_CONTROL_RADIOBUTTON, 1, &Element);

	// CCerasusComboBox -- 主要
	SetRect(&rcTexture, 7, 81, 247, 123);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 200, 200, 200);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(170, 230, 230, 230);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(70, 200, 200, 200);
	Element.m_FontColor.States[CERASUS_STATE_MOUSEOVER] = D3DCOLOR_ARGB(255, 0, 0, 0);
	Element.m_FontColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(255, 0, 0, 0);
	Element.m_FontColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(200, 200, 200, 200);

	SetDefaultElement(CERASUS_CONTROL_COMBOBOX, 0, &Element);

	// CCerasusComboBox -- 下拉框
	SetRect(&rcTexture, 98, 189, 151, 238);
	Element.SetTexture(0, &rcTexture);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_PRESSED] = D3DCOLOR_ARGB(255, 150, 150, 150);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(70, 255, 255, 255);

	SetDefaultElement(CERASUS_CONTROL_COMBOBOX, 1, &Element);

	// CCerasusComboBox -- 下拉
	SetRect(&rcTexture, 13, 123, 241, 160);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 0, 0, 0), DT_LEFT | DT_TOP);

	SetDefaultElement(CERASUS_CONTROL_COMBOBOX, 2, &Element);

	// CCerasusComboBox -- 选中
	SetRect(&rcTexture, 12, 163, 239, 183);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_TOP);

	SetDefaultElement(CERASUS_CONTROL_COMBOBOX, 3, &Element);

	// CCerasusSlider -- Track
	SetRect(&rcTexture, 1, 187, 93, 228);
	Element.SetTexture(0, &rcTexture);
	Element.m_TextureColor.States[CERASUS_STATE_NORMAL] = D3DCOLOR_ARGB(150, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_FOCUS] = D3DCOLOR_ARGB(200, 255, 255, 255);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(70, 255, 255, 255);

	SetDefaultElement(CERASUS_CONTROL_SLIDER, 0, &Element);

	// CCerasusSlider -- Button
	SetRect(&rcTexture, 151, 193, 192, 234);
	Element.SetTexture(0, &rcTexture);

	SetDefaultElement(CERASUS_CONTROL_SLIDER, 1, &Element);

	// CCerasusScrollBar -- Track
	int nScrollBarStartX = 196;
	int nScrollBarStartY = 191;
	SetRect(&rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 21, nScrollBarStartX + 22, nScrollBarStartY + 32);
	Element.SetTexture(0, &rcTexture);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(255, 200, 200, 200);

	SetDefaultElement(CERASUS_CONTROL_SCROLLBAR, 0, &Element);

	// CCerasusScrollBar -- Up Arrow
	SetRect(&rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 1, nScrollBarStartX + 22, nScrollBarStartY + 21);
	Element.SetTexture(0, &rcTexture);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(255, 200, 200, 200);

	SetDefaultElement(CERASUS_CONTROL_SCROLLBAR, 1, &Element);

	// CCerasusScrollBar -- Down Arrow
	SetRect(&rcTexture, nScrollBarStartX + 0, nScrollBarStartY + 32, nScrollBarStartX + 22, nScrollBarStartY + 53);
	Element.SetTexture(0, &rcTexture);
	Element.m_TextureColor.States[CERASUS_STATE_DISABLED] = D3DCOLOR_ARGB(255, 200, 200, 200);

	SetDefaultElement(CERASUS_CONTROL_SCROLLBAR, 2, &Element);

	// CCerasusScrollBar - Button
	SetRect(&rcTexture, 220, 192, 238, 234);
	Element.SetTexture(0, &rcTexture);

	SetDefaultElement(CERASUS_CONTROL_SCROLLBAR, 3, &Element);

	//-------------------------------------
	// CCerasusEditBox
	//-------------------------------------
	// Element assignment:
	//   0 - text area
	//   1 - top left border
	//   2 - top border
	//   3 - top right border
	//   4 - left border
	//   5 - right border
	//   6 - lower left border
	//   7 - lower border
	//   8 - lower right border

	Element.SetFont(0, D3DCOLOR_ARGB(255, 0, 0, 0), DT_LEFT | DT_TOP);

	// Assign the style
	SetRect(&rcTexture, 14, 90, 241, 113);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 0, &Element);
	SetRect(&rcTexture, 8, 82, 14, 90);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 1, &Element);
	SetRect(&rcTexture, 14, 82, 241, 90);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 2, &Element);
	SetRect(&rcTexture, 241, 82, 246, 90);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 3, &Element);
	SetRect(&rcTexture, 8, 90, 14, 113);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 4, &Element);
	SetRect(&rcTexture, 241, 90, 246, 113);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 5, &Element);
	SetRect(&rcTexture, 8, 113, 14, 121);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 6, &Element);
	SetRect(&rcTexture, 14, 113, 241, 121);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 7, &Element);
	SetRect(&rcTexture, 241, 113, 246, 121);
	Element.SetTexture(0, &rcTexture);
	SetDefaultElement(CERASUS_CONTROL_EDITBOX, 8, &Element);

	// CCerasusListBox - Main
	SetRect(&rcTexture, 13, 123, 241, 160);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 0, 0, 0), DT_LEFT | DT_TOP);

	SetDefaultElement(CERASUS_CONTROL_LISTBOX, 0, &Element);

	// CCerasusListBox - Selection

	SetRect(&rcTexture, 16, 166, 240, 183);
	Element.SetTexture(0, &rcTexture);
	Element.SetFont(0, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT | DT_TOP);

	SetDefaultElement(CERASUS_CONTROL_LISTBOX, 1, &Element);

}

//------------------------------------------------------------------
// @Function:	 OnMouseMove()
// @Purpose: CCerasusDialog鼠标移动响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusDialog::OnMouseMove(POINT pt)
{
	CCerasusControl* pControl = GetControlAtPoint(pt);

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
// @Function:	 OnCycleFocus()
// @Purpose: CCerasusDialog循环焦点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CCerasusDialog::OnCycleFocus(bool bForward)
{
	CCerasusControl* pControl = NULL;
	CCerasusDialog* pDialog = NULL;
	CCerasusDialog* pLastDialog = NULL;

	if (s_pControlFocus == NULL)
	{
		if (bForward)
		{
			for (auto iter = m_pManager->m_pDialogs.begin(); iter != m_pManager->m_pDialogs.end(); ++iter)
			{
				pDialog = pLastDialog = *iter;
				if (pDialog && pDialog->m_vecControls.size() > 0)
				{
					pControl = pDialog->m_vecControls[0];
					break;
				}
			}

			if (!pDialog || !pControl)
			{
				return true;
			}
		}
		else
		{
			for (int i = m_pManager->m_pDialogs.size() - 1; i >= 0; --i)
			{
				pDialog = pLastDialog = m_pManager->m_pDialogs[i];
				if (pDialog && pDialog->m_vecControls.size() > 0)
				{
					pControl = pDialog->m_vecControls[pDialog->m_vecControls.size() - 1];
					break;
				}
			}

			if (!pDialog || !pControl)
			{
				return true;
			}
		}
	}
	else if (s_pControlFocus->m_pDialog != this)
	{
		return false;
	}
	else
	{
		pLastDialog = s_pControlFocus->m_pDialog;
		pControl = (bForward) ? GetNextControl(s_pControlFocus) : GetPrevControl(s_pControlFocus);
		pDialog = pControl->m_pDialog;
	}

	for (int i = 0; i < 0xffff; i++)
	{
		int nLastDialogIndex = -1;
		int nDialogIndex = -1;

		for (int i = 0; i < m_pManager->m_pDialogs.size(); ++i)
		{
			if (m_pManager->m_pDialogs[i] == pLastDialog)
			{
				nLastDialogIndex = i;
			}

			if (m_pManager->m_pDialogs[i] == pDialog)
			{
				nDialogIndex = i;
			}

		}

		if ((!bForward && nLastDialogIndex < nDialogIndex) || (bForward && nDialogIndex < nLastDialogIndex))
		{
			if (s_pControlFocus)
			{
				s_pControlFocus->OnFocusOut();
			}

			s_pControlFocus = NULL;
			return true;
		}

		if (pControl == s_pControlFocus)
		{
			return true;
		}

		if (pControl->m_pDialog->m_bKeyboardInput && pControl->CanHaveFocus())
		{
			if (s_pControlFocus)
			{
				s_pControlFocus->OnFocusOut();
			}
				
			s_pControlFocus = pControl;
			s_pControlFocus->OnFocusIn();
			return true;
		}

		pLastDialog = pDialog;
		pControl = (bForward) ? GetNextControl(pControl) : GetPrevControl(pControl);
		pDialog = pControl->m_pDialog;
	}

	DXTRACE_ERR(L"CCerasusDialog: Multiple dialogs are improperly chained together", E_FAIL);
	return false;
}
