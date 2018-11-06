/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusAlgorithm.cpp
* @brief	This File is CerasusAlgorithm Dynamic Link Library Project.
* @author	alopex
* @version	v1.00a
* @date		2018-11-06	v1.00a	alopex	Create This File.
*/
#include "CerasusAlgorithm.h"

// CerasusAlgorithm类 算法(Algorithm)

//------------------------------------------------------------------
// @Function:	 CerasusAlgorithm()
// @Purpose: CerasusAlgorithm构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusAlgorithm::CCerasusAlgorithm()
{
}

//------------------------------------------------------------------
// @Function:	 ~CerasusAlgorithm()
// @Purpose: CerasusAlgorithm析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusAlgorithm::~CCerasusAlgorithm()
{
}

//------------------------------------------------------------------
// @Function:	 Increase()
// @Purpose: CerasusAlgorithm变量递增
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Increase(float & fVar, float fMax, float fStep)
{
	fVar += fStep;
	if (fVar >= fMax)
	{
		fVar = fMax;
	}

}

//------------------------------------------------------------------
// @Function:	 Decrease()
// @Purpose: CerasusAlgorithm变量递减
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Decrease(float & fVar, float fMin, float fStep)
{
	fVar -= fStep;
	if (fVar <= fMin)
	{
		fVar = fMin;
	}

}

//------------------------------------------------------------------
// @Function:	 Circulation()
// @Purpose: CerasusAlgorithm变量循环
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Circulation(float & fVar, float fMin, float fMax, float fStep)
{
	static bool bflag = true;

	if (bflag == true)
	{
		fVar += fStep;
		if (fVar >= fMax)
		{
			fVar = fMax;
			bflag = false;
		}

	}
	else
	{
		fVar -= fStep;
		if (fVar <= fMin)
		{
			fVar = fMin;
			bflag = true;
		}

	}

}
