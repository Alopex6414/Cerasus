/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusBlend.cpp
* @brief	This File is CerasusBlend DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#include "CerasusBlend.h"

// CreasusUI 渲染颜色(UI)

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CerasusBlendColor初始化颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CerasusBlendColor::Init(D3DCOLOR defaultColor, D3DCOLOR disabledColor, D3DCOLOR hiddenColor)
{
	for (int i = 0; i < MAX_CONTROL_STATES; i++)
	{
		States[i] = defaultColor;
	}

	States[CERASUS_STATE_DISABLED] = disabledColor;
	States[CERASUS_STATE_HIDDEN] = hiddenColor;
	Current = hiddenColor;
}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CerasusBlendColor渲染颜色
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CerasusBlendColor::Blend(UINT iState, float fElapsedTime, float fRate)
{
	D3DXCOLOR destColor = States[iState];
	D3DXColorLerp(&Current, &Current, &destColor, 1.0f - powf(fRate, 30 * fElapsedTime));
}
