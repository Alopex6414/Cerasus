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

// Cerasus Unit Type(CerasusͼԪ����)
typedef struct
{
	UINT nScreenWidth;											// Cerasus Unit ���ڿ��
	UINT nScreenHeight;											// Cerasus Unit ���ڸ߶�
	LPWSTR pTextureStr;											// Cerasus Unit ����·��
	UINT nTextureWidth;											// Cerasus Unit ������
	UINT nTextureHeight;										// Cerasus Unit ����߶�
	RECT rcUnit;												// Cerasus Unit ͼԪ����
	RECT rcUnitTex;												// Cerasus Unit �������
	float fUnitAlpha;											// Cerasus Unit Alphaֵ
	S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara;			// Cerasus Unit ����任
} S_CS_UNIT_PARA, *LPS_CS_UNIT_PARA;

// Cerasus UnitEx Type(CerasusͼԪ����EX)
typedef struct
{
	UINT nScreenWidth;											// Cerasus Unit Ex ���ڿ��
	UINT nScreenHeight;											// Cerasus Unit Ex ���ڸ߶�
	LPVOID pTextureArr;											// Cerasus Unit Ex ����·��
	UINT nTextureArrSize;										// Cerasus Unit Ex ����·��
	UINT nTextureWidth;											// Cerasus Unit Ex ������
	UINT nTextureHeight;										// Cerasus Unit Ex ����߶�
	RECT rcUnit;												// Cerasus Unit Ex ͼԪ����
	RECT rcUnitTex;												// Cerasus Unit Ex �������
	float fUnitAlpha;											// Cerasus Unit Ex Alphaֵ
	S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara;			// Cerasus Unit Ex ����任
} S_CS_UNIT_EX_PARA, *LPS_CS_UNIT_EX_PARA;

#endif // !__CERASUSTYPES_H_
