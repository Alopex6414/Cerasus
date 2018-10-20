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

// CreasusUI �ؼ�Ԫ��(UI)

//------------------------------------------------------------------
// @Function:	 CCerasusElement()
// @Purpose: CCerasusElement���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusElement::CCerasusElement(IDirect3DDevice9 * pD3D9Device)
{
	m_nTexIndex = 0;
	m_nFontIndex = 0;
	m_pTexElement = new CCerasusBlendTex(pD3D9Device);
	m_pFontElement = new CCerasusBlendFont(pD3D9Device);
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusElement()
// @Purpose: CCerasusElement��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusElement::~CCerasusElement()
{
	SAFE_DELETE(m_pFontElement);
	SAFE_DELETE(m_pTexElement);
}

//------------------------------------------------------------------
// @Function:	 CCerasusElementGetTexElement()
// @Purpose: CCerasusElement��ȡ����Ԫ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendTex * CCerasusElement::CCerasusElementGetTexElement()
{
	return m_pTexElement;
}

//------------------------------------------------------------------
// @Function:	 CCerasusElementGetFontElement()
// @Purpose: CCerasusElement��ȡ����Ԫ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendFont * CCerasusElement::CCerasusElementGetFontElement()
{
	return m_pFontElement;
}

//------------------------------------------------------------------
// @Function:	 CCerasusElementSetTexElement()
// @Purpose: CCerasusElement��������Ԫ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusElement::CCerasusElementSetTexElement(CCerasusBlendTex * pTexElement)
{
	m_pTexElement = pTexElement;
}

//------------------------------------------------------------------
// @Function:	 CCerasusElementSetFontElement()
// @Purpose: CCerasusElement��������Ԫ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusElement::CCerasusElementSetFontElement(CCerasusBlendFont * pFontElement)
{
	m_pFontElement = pFontElement;
}