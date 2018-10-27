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
double				CCerasusDialog::s_fTimeRefresh;
CCerasusControl*	CCerasusDialog::s_pControlFocus;
CCerasusControl*	CCerasusDialog::s_pControlPressed;

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
