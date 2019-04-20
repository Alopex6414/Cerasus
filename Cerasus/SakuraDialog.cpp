/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraDialog.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
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

		S_CS_UNIT_EX_PARA sUnitNormalEx = { 0 };
		sUnitNormalEx.nScreenWidth = USER_SCREENWIDTH;
		sUnitNormalEx.nScreenHeight = USER_SCREENHEIGHT;
		sUnitNormalEx.nTextureWidth = 16;
		sUnitNormalEx.nTextureHeight = 16;
		sUnitNormalEx.fUnitAlpha = 1.0f;
		sUnitNormalEx.pTextureArr = CSakuraResource::m_ucCheckBox_UnChecked;
		sUnitNormalEx.nTextureArrSize = sizeof(CSakuraResource::m_ucCheckBox_UnChecked);
		sUnitNormalEx.rcUnit.left = 0;
		sUnitNormalEx.rcUnit.top = 0;
		sUnitNormalEx.rcUnit.right = 16;
		sUnitNormalEx.rcUnit.bottom = 16;
		sUnitNormalEx.rcUnitTex.left = 0;
		sUnitNormalEx.rcUnitTex.top = 0;
		sUnitNormalEx.rcUnitTex.right = 16;
		sUnitNormalEx.rcUnitTex.bottom = 16;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_SCREENHEIGHT * 0.5f));
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_SCREENHEIGHT * 0.5f);
		sUnitNormalEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
		sUnitNormalEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

		S_CS_UNIT_EX_PARA sUnitPressedEx = { 0 };
		sUnitPressedEx.nScreenWidth = USER_SCREENWIDTH;
		sUnitPressedEx.nScreenHeight = USER_SCREENHEIGHT;
		sUnitPressedEx.nTextureWidth = 16;
		sUnitPressedEx.nTextureHeight = 16;
		sUnitPressedEx.fUnitAlpha = 1.0f;
		sUnitPressedEx.pTextureArr = CSakuraResource::m_ucCheckBox_Checked;
		sUnitPressedEx.nTextureArrSize = sizeof(CSakuraResource::m_ucCheckBox_Checked);
		sUnitPressedEx.rcUnit.left = 0;
		sUnitPressedEx.rcUnit.top = 0;
		sUnitPressedEx.rcUnit.right = 16;
		sUnitPressedEx.rcUnit.bottom = 16;
		sUnitPressedEx.rcUnitTex.left = 0;
		sUnitPressedEx.rcUnitTex.top = 0;
		sUnitPressedEx.rcUnitTex.right = 16;
		sUnitPressedEx.rcUnitTex.bottom = 16;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_SCREENHEIGHT * 0.5f));
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_SCREENHEIGHT * 0.5f);
		sUnitPressedEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
		sUnitPressedEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

		pElement->GetTextureBlend().AddTexture(SAKURA_STATE_NORMAL, sUnitNormalEx);
		pElement->GetTextureBlend().AddTexture(SAKURA_STATE_PRESSED, sUnitPressedEx);

		SetDefaultElement(SAKURA_CONTROL_CHECKBOX, 0, &pElement);
	}

	// CSakuraRadioButton 单选框控件(默认)
	{
		CSakuraElement* pElement = new CSakuraElement(m_pManager->GetDevice());
		pElement->GetFontBlend().AddFont(SAKURA_STATE_NORMAL, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_DISABLED, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_FOCUS, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_MOUSEOVER, sFont.strFontName, sFont.nFontSize);
		pElement->GetFontBlend().AddFont(SAKURA_STATE_PRESSED, sFont.strFontName, sFont.nFontSize);

		S_CS_UNIT_EX_PARA sUnitNormalEx = { 0 };
		sUnitNormalEx.nScreenWidth = USER_SCREENWIDTH;
		sUnitNormalEx.nScreenHeight = USER_SCREENHEIGHT;
		sUnitNormalEx.nTextureWidth = 16;
		sUnitNormalEx.nTextureHeight = 16;
		sUnitNormalEx.fUnitAlpha = 1.0f;
		sUnitNormalEx.pTextureArr = CSakuraResource::m_ucRadioButton_UnChecked;
		sUnitNormalEx.nTextureArrSize = sizeof(CSakuraResource::m_ucRadioButton_UnChecked);
		sUnitNormalEx.rcUnit.left = 0;
		sUnitNormalEx.rcUnit.top = 0;
		sUnitNormalEx.rcUnit.right = 16;
		sUnitNormalEx.rcUnit.bottom = 16;
		sUnitNormalEx.rcUnitTex.left = 0;
		sUnitNormalEx.rcUnitTex.top = 0;
		sUnitNormalEx.rcUnitTex.right = 16;
		sUnitNormalEx.rcUnitTex.bottom = 16;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		sUnitNormalEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_SCREENHEIGHT * 0.5f));
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
		sUnitNormalEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_SCREENHEIGHT * 0.5f);
		sUnitNormalEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
		sUnitNormalEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

		S_CS_UNIT_EX_PARA sUnitPressedEx = { 0 };
		sUnitPressedEx.nScreenWidth = USER_SCREENWIDTH;
		sUnitPressedEx.nScreenHeight = USER_SCREENHEIGHT;
		sUnitPressedEx.nTextureWidth = 16;
		sUnitPressedEx.nTextureHeight = 16;
		sUnitPressedEx.fUnitAlpha = 1.0f;
		sUnitPressedEx.pTextureArr = CSakuraResource::m_ucRadioButton_Checked;
		sUnitPressedEx.nTextureArrSize = sizeof(CSakuraResource::m_ucRadioButton_Checked);
		sUnitPressedEx.rcUnit.left = 0;
		sUnitPressedEx.rcUnit.top = 0;
		sUnitPressedEx.rcUnit.right = 16;
		sUnitPressedEx.rcUnit.bottom = 16;
		sUnitPressedEx.rcUnitTex.left = 0;
		sUnitPressedEx.rcUnitTex.top = 0;
		sUnitPressedEx.rcUnitTex.right = 16;
		sUnitPressedEx.rcUnitTex.bottom = 16;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		sUnitPressedEx.sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(USER_SCREENHEIGHT * 0.5f));
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
		sUnitPressedEx.sCoordsTransformPara.sPrespectiveTransformPara.fZf = (USER_SCREENHEIGHT * 0.5f);
		sUnitPressedEx.sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
		sUnitPressedEx.sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

		pElement->GetTextureBlend().AddTexture(SAKURA_STATE_NORMAL, sUnitNormalEx);
		pElement->GetTextureBlend().AddTexture(SAKURA_STATE_PRESSED, sUnitPressedEx);

		SetDefaultElement(SAKURA_CONTROL_RADIOBUTTON, 0, &pElement);
	}


}

//------------------------------------------------------------------
// @Function:	 AlterDefaultElement()
// @Purpose: CSakuraDialog修改默认控件资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::AlterDefaultElement(CSakuraControl * pControl)
{
	if (pControl == NULL || pControl->m_bIsDefault == false)
	{
		return;
	}

	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		if ((*iter)->nControlType == pControl->GetType())
		{
			CSakuraElement** ppElement = &(pControl->GetElement((*iter)->iElement));

			if (pControl->GetType() == SAKURA_CONTROL_CHECKBOX || pControl->GetType() == SAKURA_CONTROL_RADIOBUTTON)
			{
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_nScreenWidth = pControl->m_pDialog->GetWidth();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_nScreenHeight = pControl->m_pDialog->GetHeight();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_rcUnit.left = pControl->m_nX;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_rcUnit.top = pControl->m_nY;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_rcUnit.right = pControl->m_nX + pControl->m_nHeight;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_rcUnit.bottom = pControl->m_nY + pControl->m_nHeight;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(pControl->m_pDialog->GetHeight() * 0.5f));
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(pControl->m_pDialog->GetWidth() * 1.0f / pControl->m_pDialog->GetHeight());
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_sCoordsTransformPara.sPrespectiveTransformPara.fZf = (pControl->m_pDialog->GetHeight() * 0.5f);
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_sCoordsTransformPara.sViewPortTransformPara.nUserWidth = pControl->m_pDialog->GetWidth();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_NORMAL]->m_sCoordsTransformPara.sViewPortTransformPara.nUserHeight = pControl->m_pDialog->GetHeight();
			
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_nScreenWidth = pControl->m_pDialog->GetWidth();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_nScreenHeight = pControl->m_pDialog->GetHeight();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_rcUnit.left = pControl->m_nX;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_rcUnit.top = pControl->m_nY;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_rcUnit.right = pControl->m_nX + pControl->m_nHeight;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_rcUnit.bottom = pControl->m_nY + pControl->m_nHeight;
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(pControl->m_pDialog->GetHeight() * 0.5f));
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(pControl->m_pDialog->GetWidth() * 1.0f / pControl->m_pDialog->GetHeight());
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_sCoordsTransformPara.sPrespectiveTransformPara.fZf = (pControl->m_pDialog->GetHeight() * 0.5f);
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_sCoordsTransformPara.sViewPortTransformPara.nUserWidth = pControl->m_pDialog->GetWidth();
				(*ppElement)->GetTextureBlend().m_States[SAKURA_STATE_PRESSED]->m_sCoordsTransformPara.sViewPortTransformPara.nUserHeight = pControl->m_pDialog->GetHeight();
			}

		}

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
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnCreate(CSakuraResourceManager * pManager, S_CS_UNIT_PARA sUnit)
{
	m_pManager = pManager;
	m_pDialogGraphics = new CCerasusUnit(m_pManager->GetDevice());
	m_pDialogGraphics->Create(sUnit);
	InitDefaultElement();
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraDialog窗口初始化处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::OnCreate(CSakuraResourceManager * pManager, S_CS_UNIT_EX_PARA sUnit)
{
	m_pManager = pManager;
	m_pDialogGraphics = new CCerasusUnit(m_pManager->GetDevice());
	m_pDialogGraphics->Create(sUnit);
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

	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		(*iter)->pElement->GetFontBlend().OnLostDevice();
		(*iter)->pElement->GetTextureBlend().OnLostDevice();
	}

	if (m_pDialogGraphics)
	{
		m_pDialogGraphics->Reset();
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

	for (auto iter = m_vecDefaultControls.begin(); iter != m_vecDefaultControls.end(); ++iter)
	{
		(*iter)->pElement->GetFontBlend().OnResetDevice();
		(*iter)->pElement->GetTextureBlend().OnResetDevice();
	}

	if (m_pDialogGraphics)
	{
		m_pDialogGraphics->ReCreate();
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

	AlterDefaultElement(pStatic);

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

	AlterDefaultElement(pButton);

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

	AlterDefaultElement(pCheckBox);

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
	CSakuraRadioButton* pRadioButton = new CSakuraRadioButton(this);

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

	AlterDefaultElement(pRadioButton);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddComboBox()
// @Purpose: CSakuraDialog窗口添加下拉选择框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddComboBox(int ID, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, CSakuraComboBox ** ppCreated)
{
	CSakuraComboBox* pComboBox = new CSakuraComboBox(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pComboBox;
	}

	if (pComboBox == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pComboBox));

	pComboBox->SetID(ID);
	pComboBox->SetLocation(x, y);
	pComboBox->SetSize(width, height);
	pComboBox->SetHotkey(nHotkey);
	pComboBox->m_bIsDefault = bIsDefault;

	AlterDefaultElement(pComboBox);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddSlider()
// @Purpose: CSakuraDialog窗口添加滑块控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddSlider(int ID, int x, int y, int width, int height, int min, int max, int value, bool bIsDefault, CSakuraSlider ** ppCreated)
{
	CSakuraSlider* pSlider = new CSakuraSlider(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pSlider;
	}

	if (pSlider == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pSlider));

	pSlider->SetID(ID);
	pSlider->SetLocation(x, y);
	pSlider->SetSize(width, height);
	pSlider->m_bIsDefault = bIsDefault;
	pSlider->SetRange(min, max);
	pSlider->SetValue(value);
	pSlider->UpdateRects();

	AlterDefaultElement(pSlider);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 AddUnit()
// @Purpose: CSakuraDialog窗口添加图形控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURADIALOG_CALLMETHOD CSakuraDialog::AddUnit(int ID, int x, int y, int width, int height, UINT nHotkey, bool bIsDefault, CSakuraUnit ** ppCreated)
{
	CSakuraUnit* pUnit = new CSakuraUnit(this);

	if (ppCreated != NULL)
	{
		*ppCreated = pUnit;
	}

	if (pUnit == NULL)
	{
		return E_OUTOFMEMORY;
	}

	VERIFY(AddControl(pUnit));

	pUnit->SetID(ID);
	pUnit->SetLocation(x, y);
	pUnit->SetSize(width, height);
	pUnit->SetHotkey(nHotkey);
	pUnit->m_bIsDefault = bIsDefault;

	AlterDefaultElement(pUnit);

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
			(*ppElement) = new CSakuraElement(*((*iter)->pElement));
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
	S_CS_UNIT_PARA* pTexture = GetTextureRes(Index);

	if ((*ppElement) == NULL)
	{
		(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	}
	(*ppElement)->GetTextureBlend().AddTexture(eType, *pTexture);

	//pControl->SetLocation(pTexture->rcUnit.left, pTexture->rcUnit.top);
	//pControl->SetSize(pTexture->rcUnit.right - pTexture->rcUnit.left, pTexture->rcUnit.bottom - pTexture->rcUnit.top);

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
	S_CS_UNIT_EX_PARA* pTexture = GetTextureExRes(Index);

	if ((*ppElement) == NULL)
	{
		(*ppElement) = new CSakuraElement(m_pManager->GetDevice());
	}
	(*ppElement)->GetTextureBlend().AddTexture(eType, *pTexture);

	//pControl->SetLocation(pTexture->rcUnit.left, pTexture->rcUnit.top);
	//pControl->SetSize(pTexture->rcUnit.right - pTexture->rcUnit.left, pTexture->rcUnit.bottom - pTexture->rcUnit.top);

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetDialogGraphics()
// @Purpose: CSakuraDialog窗口获取背景图形
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetDialogGraphics()
{
	return m_pDialogGraphics;
}

//------------------------------------------------------------------
// @Function:	 GetControls()
// @Purpose: CSakuraDialog窗口获取控件向量
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
vector<CSakuraControl*>&SAKURADIALOG_CALLMETHOD CSakuraDialog::GetControls()
{
	return m_vecControls;
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
	return dynamic_cast<CSakuraStatic*>(GetControl(ID, SAKURA_CONTROL_STATIC));
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
	return dynamic_cast<CSakuraButton*>(GetControl(ID, SAKURA_CONTROL_BUTTON));
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
	return dynamic_cast<CSakuraCheckBox*>(GetControl(ID, SAKURA_CONTROL_CHECKBOX));
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
	return dynamic_cast<CSakuraRadioButton*>(GetControl(ID, SAKURA_CONTROL_RADIOBUTTON));
}

//------------------------------------------------------------------
// @Function:	 GetComboBox()
// @Purpose: CSakuraDialog窗口获取下拉框控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraComboBox *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetComboBox(int ID)
{
	return dynamic_cast<CSakuraComboBox*>(GetControl(ID, SAKURA_CONTROL_COMBOBOX));
}

//------------------------------------------------------------------
// @Function:	 GetSlider()
// @Purpose: CSakuraDialog窗口获取滑块控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraSlider *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetSlider(int ID)
{
	return dynamic_cast<CSakuraSlider*>(GetControl(ID, SAKURA_CONTROL_SLIDER));
}

//------------------------------------------------------------------
// @Function:	 GetUnit()
// @Purpose: CSakuraDialog窗口获取图形控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraUnit *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetUnit(int ID)
{
	return dynamic_cast<CSakuraUnit*>(GetControl(ID, SAKURA_CONTROL_UNIT));
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
// @Function:	 GetControlEnabled()
// @Purpose: CSakuraDialog获取控件使能状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURADIALOG_CALLMETHOD CSakuraDialog::GetControlEnabled(int ID)
{
	CSakuraControl* pControl = GetControl(ID);

	if (pControl == NULL)
	{
		return false;
	}

	return (pControl->GetEnabled());
}

//------------------------------------------------------------------
// @Function:	 SetControlEnabled()
// @Purpose: CSakuraDialog设置控件使能状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURADIALOG_CALLMETHOD CSakuraDialog::SetControlEnabled(int ID, bool bEnabled)
{
	CSakuraControl* pControl = GetControl(ID);

	if (pControl == NULL)
	{
		return;
	}

	pControl->SetEnabled(bEnabled);
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
	CSakuraComboBox* pComboBox = GetComboBox(nID);

	if (pComboBox == NULL)
	{
		return;
	}
	
	pComboBox->RemoveAllItems();
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
int SAKURADIALOG_CALLMETHOD CSakuraDialog::SetTextrueRes(S_CS_UNIT_PARA* pTexture)
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
int SAKURADIALOG_CALLMETHOD CSakuraDialog::SetTextrueExRes(S_CS_UNIT_EX_PARA* pTexture)
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
S_CS_UNIT_PARA*SAKURADIALOG_CALLMETHOD CSakuraDialog::GetTextureRes(UINT Index)
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
S_CS_UNIT_EX_PARA*SAKURADIALOG_CALLMETHOD CSakuraDialog::GetTextureExRes(UINT Index)
{
	if (m_pManager == NULL)
	{
		return NULL;
	}

	return m_pManager->GetTextureNodeEx(Index);
}

//------------------------------------------------------------------
// @Function:	 GetManager()
// @Purpose: CSakuraDialog获取资源管理类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraResourceManager *SAKURADIALOG_CALLMETHOD CSakuraDialog::GetManager()
{
	return m_pManager;
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
		m_pDialogGraphics->MatrixTransform();
		m_pDialogGraphics->PaddingVertexAndIndex();
		m_pDialogGraphics->SetAlphaEnable();
		m_pDialogGraphics->SetRenderState();
		m_pDialogGraphics->Render();
		m_pDialogGraphics->SetAlphaDisable();
	}

	// 渲染控件
	for (auto iter = m_vecControls.begin(); iter != m_vecControls.end(); ++iter)
	{
		(*iter)->Render();
	}

	return S_OK;
}
