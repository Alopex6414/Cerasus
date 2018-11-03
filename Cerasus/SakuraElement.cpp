/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraElement.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraElement.h"

// SakuraGUI 控件渲染元素(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraElement()
// @Purpose: CSakuraElement构造函数
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
// @Purpose: CSakuraElement析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraElement::~CSakuraElement()
{
}

//------------------------------------------------------------------
// @Function:	 GetFontBlend()
// @Purpose: CSakuraElement获取字体渲染类
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
// @Purpose: CSakuraElement获取纹理渲染类
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
// @Purpose: CSakuraElement刷新渲染资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURAELEMENT_CALLMETHOD CSakuraElement::Refresh()
{
	m_FontBlend.m_Current = m_FontBlend.m_States[SAKURA_STATE_HIDDEN];
	m_TextureBlend.m_Current = m_TextureBlend.m_States[SAKURA_STATE_HIDDEN];
}
