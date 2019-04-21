/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraUnit.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2019-01-06	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraUnit.h"

// SakuraGUI 图形控件派生类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraUnit()
// @Purpose: CSakuraUnit构造函数
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
// @Purpose: CSakuraUnit渲染控件
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
