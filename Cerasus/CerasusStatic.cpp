/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusStatic.cpp
* @brief	This File is CerasusStatic DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#include "CerasusStatic.h"

// CreasusUI 静态控件(CCerasusStatic)

//------------------------------------------------------------------
// @Function:	 CCerasusStatic()
// @Purpose: CCerasusStatic构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusStatic::CCerasusStatic()
{
	m_eType = CERASUS_CONTROL_STATIC;

	ZeroMemory(m_strText, sizeof(m_strText));

}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CCerasusStatic渲染控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSSTATIC_CALLMODE CCerasusStatic::Render()
{
	if (m_bVisible == false)
	{
		return;
	}

	CERASUS_CONTROL_STATE nState = CERASUS_STATE_NORMAL;

	if (m_bEnabled == false)
	{
		nState = CERASUS_STATE_DISABLED;
	}

	m_Element->CCerasusElementGetFontElement()->Blend(nState);
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CCerasusStatic鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CERASUSSTATIC_CALLMODE CCerasusStatic::ContainsPoint(POINT pt)
{
	return FALSE;
}

//------------------------------------------------------------------
// @Function:	 GetText()
// @Purpose: CCerasusStatic获取文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPCWSTR CERASUSSTATIC_CALLMODE CCerasusStatic::GetText()
{
	return m_strText;
}

//------------------------------------------------------------------
// @Function:	 SetText()
// @Purpose: CCerasusStatic设置文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSSTATIC_CALLMODE CCerasusStatic::SetText(LPCWSTR strText)
{
	if (strText == NULL)
	{
		m_strText[0] = 0;
		return S_OK;
	}

	wcscpy_s(m_strText, MAX_PATH, strText);
	return S_OK;
}
