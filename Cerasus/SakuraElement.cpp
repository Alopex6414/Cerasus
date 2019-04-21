/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraElement.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraElement.h"

// SakuraGUI �ؼ���ȾԪ��(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraElement()
// @Purpose: CSakuraElement���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement::CSakuraElement(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	m_FontBlend.OnCreate(m_pD3D9Device);
	m_TextureBlend.OnCreate(m_pD3D9Device);
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraElement()
// @Purpose: CSakuraElement��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement::~CSakuraElement()
{
}

//------------------------------------------------------------------
// @Function:	 CSakuraElement()
// @Purpose: CSakuraElement���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement::CSakuraElement(const CSakuraElement & Object)
{
	m_pD3D9Device = Object.m_pD3D9Device;
	m_FontBlend = Object.m_FontBlend;
	m_TextureBlend = Object.m_TextureBlend;
}

//------------------------------------------------------------------
// @Function:	 GetFontBlend()
// @Purpose: CSakuraElement��ȡ������Ⱦ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont& SAKURAELEMENT_CALLMETHOD CSakuraElement::GetFontBlend()
{
	return m_FontBlend;
}

//------------------------------------------------------------------
// @Function:	 GetTextureBlend()
// @Purpose: CSakuraElement��ȡ������Ⱦ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture& SAKURAELEMENT_CALLMETHOD CSakuraElement::GetTextureBlend()
{
	return m_TextureBlend;
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CSakuraElementˢ����Ⱦ��Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURAELEMENT_CALLMETHOD CSakuraElement::Refresh()
{
	m_FontBlend.m_Current = m_FontBlend.m_States[SAKURA_STATE_HIDDEN];
	m_TextureBlend.m_Current = m_TextureBlend.m_States[SAKURA_STATE_HIDDEN];
}
