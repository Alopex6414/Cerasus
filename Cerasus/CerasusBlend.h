/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusBlend.h
* @brief	This File is CerasusBlend DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSBLEND_H_
#define __CERASUSBLEND_H_

//Include Direct Common Header File
#include "CerasusUICommon.h"

//Struct Definition
struct CerasusBlendColor
{
	void	Init(D3DCOLOR defaultColor, D3DCOLOR disabledColor = D3DCOLOR_ARGB(200, 128, 128, 128), D3DCOLOR hiddenColor = 0);
	void	Blend(UINT iState, float fElapsedTime, float fRate = 0.7f);

	D3DCOLOR	States[MAX_CONTROL_STATES];
	D3DXCOLOR	Current;
};



#endif // !__CERASUSBLEND_H_
