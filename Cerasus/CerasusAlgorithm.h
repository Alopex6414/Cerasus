/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusAlgorithm.h
* @brief	This File is CerasusAlgorithm Dynamic Link Library Project.
* @author	alopex
* @version	v1.00a
* @date		2018-11-06	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __CERASUSALGORITHM_H_
#define __CERASUSALGORITHM_H_

//Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectThreadSafe.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSALGORITHM_API	__declspec(dllexport)
#else
#define CERASUSALGORITHM_API	__declspec(dllimport)
#endif

#define	CERASUSALGORITHM_CALLMETHOD	__stdcall

//Class Definition
class CERASUSALGORITHM_API CCerasusAlgorithm
{
public:
	CCerasusAlgorithm();			// CCerasusAlgorithm 构造函数
	~CCerasusAlgorithm();			// CCerasusAlgorithm 析构函数

	static void	CERASUSALGORITHM_CALLMETHOD	Increase(float& fVar, float fMax, float fStep);
	static void	CERASUSALGORITHM_CALLMETHOD	Decrease(float& fVar, float fMin, float fStep);
	static void	CERASUSALGORITHM_CALLMETHOD Circulation(float& fVar, float fMin, float fMax, float fStep);

};

#endif // !__CERASUSALGORITHM_H_

