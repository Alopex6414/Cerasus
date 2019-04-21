/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraStatic.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraStatic.h"

// SakuraGUI 静态控件派生类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraStatic()
// @Purpose: CSakuraStatic构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraStatic::CSakuraStatic(CSakuraDialog* pDialog)
{
	m_pDialog = pDialog;
	m_eType = SAKURA_CONTROL_STATIC;

	ZeroMemory(m_strText, sizeof(m_strText));
	m_dwFormat = DT_CENTER | DT_VCENTER;
	m_dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	for (auto iter = m_vecElements.begin(); iter != m_vecElements.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}

	m_vecElements.clear();
}

//------------------------------------------------------------------
// @Function:	 GetText()
// @Purpose: CSakuraStatic获取文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPCWSTR SAKURASTATIC_CALLMETHOD CSakuraStatic::GetText()
{
	return m_strText;
}

//------------------------------------------------------------------
// @Function:	 SetText()
// @Purpose: CSakuraStatic设置文本
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURASTATIC_CALLMETHOD CSakuraStatic::SetText(LPCWSTR strText)
{
	if (strText == NULL)
	{
		m_strText[0] = 0;
		return S_OK;
	}

	wcscpy_s(m_strText, MAX_PATH, strText);
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetFormat()
// @Purpose: CSakuraStatic获取格式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD SAKURASTATIC_CALLMETHOD CSakuraStatic::GetFormat()
{
	return m_dwFormat;
}

//------------------------------------------------------------------
// @Function:	 SetFormat()
// @Purpose: CSakuraStatic设置格式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURASTATIC_CALLMETHOD CSakuraStatic::SetFormat(DWORD dwFormat)
{
	m_dwFormat = dwFormat;
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetColor()
// @Purpose: CSakuraStatic获取颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
D3DCOLOR SAKURASTATIC_CALLMETHOD CSakuraStatic::GetColor()
{
	return m_dwColor;
}

//------------------------------------------------------------------
// @Function:	 SetColor()
// @Purpose: CSakuraStatic设置颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURASTATIC_CALLMETHOD CSakuraStatic::SetColor(D3DCOLOR dwColor)
{
	m_dwColor = dwColor;
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 ContainsPoint()
// @Purpose: CSakuraStatic鼠标落在控件内
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL SAKURASTATIC_CALLMETHOD CSakuraStatic::ContainsPoint(POINT pt)
{
	return FALSE;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CSakuraStatic渲染静态控件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURASTATIC_CALLMETHOD CSakuraStatic::Render()
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

	m_vecElements.at(0)->GetFontBlend().Blend(iState, m_strText, &m_rcBoundingBox, m_dwFormat, m_dwColor);
}
