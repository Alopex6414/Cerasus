/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraUnit.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2019-01-06	v1.00a	alopex	Create Project.
*/
#include "SakuraUnit.h"

// SakuraGUI ͼ�οؼ�������(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraUnit()
// @Purpose: CSakuraUnit���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraUnit::CSakuraUnit(CSakuraDialog* pDialog)
{
	m_pDialog = pDialog;
	m_eType = SAKURA_CONTROL_UNIT;

	for (auto iter = m_vecElements.begin(); iter != m_vecElements.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecElements.clear();
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraUnit��Ⱦ�ؼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURAUNIT_CALLMETHOD CSakuraUnit::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	SAKURA_CONTROL_STATE iState = SAKURA_STATE_NORMAL;

	if (m_bEnabled == false)
	{
		iState = SAKURA_STATE_DISABLED;
	}

	m_vecElements.at(0)->GetTextureBlend().Blend(iState);
}
