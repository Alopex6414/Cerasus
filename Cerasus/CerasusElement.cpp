/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusElement.cpp
* @brief	This File is CerasusElement DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "CerasusElement.h"

// CreasusUI 渲染元素(UI)

//------------------------------------------------------------------
// @Function:	 SetFont()
// @Purpose: CCerasusElement设置字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusElement::SetFont(UINT iFont, D3DCOLOR defaultFontColor, DWORD dwTextFormat)
{
	this->m_iFont = iFont;
	this->m_dwTextureFormat = dwTextFormat;

	m_FontColor.Init(defaultFontColor);
}

//------------------------------------------------------------------
// @Function:	 SetTexture()
// @Purpose: CCerasusElement设置纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusElement::SetTexture(UINT iTexture, RECT * prcTexture, D3DCOLOR defaultTextureColor)
{
	this->m_iTexture = iTexture;

	if (prcTexture)
	{
		m_rcTexture = *prcTexture;
	}
	else
	{
		SetRectEmpty(&m_rcTexture);
	}

	m_TextureColor.Init(defaultTextureColor);
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CCerasusElement刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusElement::Refresh()
{
	m_FontColor.Current = m_FontColor.States[CERASUS_STATE_HIDDEN];
	m_TextureColor.Current = m_TextureColor.States[CERASUS_STATE_HIDDEN];
}
