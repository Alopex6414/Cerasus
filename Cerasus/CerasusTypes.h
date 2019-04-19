/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		CerasusTypes.h
* @brief	This File is DirectX Library Template Header.
* @author	Alopex/Alice
* @version	v1.00a
* @date		2019-04-18	v1.00a	alopex	Create File.
*/
#pragma once

#ifndef __CERASUSTYPES_H_
#define __CERASUSTYPES_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

/// Struct Definition

// Cerasus Unit Type(Cerasus图元类型)
typedef struct
{
	UINT nScreenWidth;											// Cerasus Unit 窗口宽度
	UINT nScreenHeight;											// Cerasus Unit 窗口高度
	LPWSTR pTextureStr;											// Cerasus Unit 纹理路径
	UINT nTextureWidth;											// Cerasus Unit 纹理宽度
	UINT nTextureHeight;										// Cerasus Unit 纹理高度
	RECT rcUnit;												// Cerasus Unit 图元矩形
	RECT rcUnitTex;												// Cerasus Unit 纹理矩形
	float fUnitAlpha;											// Cerasus Unit Alpha值
	S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara;			// Cerasus Unit 坐标变换
} S_CS_UNIT_PARA, *LPS_CS_UNIT_PARA;

// Cerasus UnitEx Type(Cerasus图元类型EX)
typedef struct
{
	UINT nScreenWidth;											// Cerasus Unit Ex 窗口宽度
	UINT nScreenHeight;											// Cerasus Unit Ex 窗口高度
	LPVOID pTextureArr;											// Cerasus Unit Ex 纹理路径
	UINT nTextureArrSize;										// Cerasus Unit Ex 纹理路径
	UINT nTextureWidth;											// Cerasus Unit Ex 纹理宽度
	UINT nTextureHeight;										// Cerasus Unit Ex 纹理高度
	RECT rcUnit;												// Cerasus Unit Ex 图元矩形
	RECT rcUnitTex;												// Cerasus Unit Ex 纹理矩形
	float fUnitAlpha;											// Cerasus Unit Ex Alpha值
	S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara;			// Cerasus Unit Ex 坐标变换
} S_CS_UNIT_EX_PARA, *LPS_CS_UNIT_EX_PARA;

#endif // !__CERASUSTYPES_H_
