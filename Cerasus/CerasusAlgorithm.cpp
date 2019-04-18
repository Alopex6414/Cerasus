/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		CerasusAlgorithm.cpp
* @brief	This File is CerasusAlgorithm Dynamic Link Library Project.
* @author	alopex
* @version	v1.01a
* @date		2018-11-06	v1.00a	alopex	Create This File.
* @date		2019-04-18	v1.01a	alopex	Add Notes.
*/
#include "CerasusAlgorithm.h"

// CerasusAlgorithm�� �㷨(Algorithm)

//------------------------------------------------------------------
// @Function:	 CerasusAlgorithm()
// @Purpose: CerasusAlgorithm���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusAlgorithm::CCerasusAlgorithm()
{
}

//------------------------------------------------------------------
// @Function:	 ~CerasusAlgorithm()
// @Purpose: CerasusAlgorithm��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusAlgorithm::~CCerasusAlgorithm()
{
}

//------------------------------------------------------------------
// @Function:	 Increase()
// @Purpose: CerasusAlgorithm��������
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
// @Purpose: CerasusAlgorithm�����ݼ�
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
// @Purpose: CerasusAlgorithm����ѭ��
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

//------------------------------------------------------------------
// @Function:	 Linear_Increase()
// @Purpose: CerasusAlgorithm���Ե���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Linear_Increase(float & fVar, float fMax, float fStep)
{
	Increase(fVar, fMax, fStep);
}

//------------------------------------------------------------------
// @Function:	 Linear_Decrease()
// @Purpose: CerasusAlgorithm���Եݼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Linear_Decrease(float & fVar, float fMin, float fStep)
{
	Decrease(fVar, fMin, fStep);
}

//------------------------------------------------------------------
// @Function:	 Linear_Circulation()
// @Purpose: CerasusAlgorithm����ѭ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Linear_Circulation(float & fVar, float fMin, float fMax, float fStep)
{
	Circulation(fVar, fMin, fMax, fStep);
}

//------------------------------------------------------------------
// @Function:	 Quadratic_Increase()
// @Purpose: CerasusAlgorithm���ε���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Quadratic_Increase(float& fVt, float fV0, float fVmax, float fAcc)
{
	if (fAcc >= 0)
	{
		float fX0 = fV0;
		float fXt = sqrtf(2.0f * fAcc * (fVt - fV0));

		fXt += fAcc;
		fVt = fX0 + powf(fXt, 2.0f) / (2.0f * fAcc);
		if (fVt >= fVmax)
		{
			fVt = fVmax;
		}
	}
	else
	{
		float fX0 = fV0;
		float fXl = sqrtf(2.0f * (-fAcc) * (fVmax - fV0));
		float fXt = sqrtf(powf(fXl, 2.0f) + 2.0f * fAcc * (fVt - fV0));

		fXt += fAcc;
		if (fXt <= 0)
		{
			fVt = fVmax;
		}
		else
		{
			fVt = fX0 + (powf(fXt, 2.0f) - powf(fXl, 2.0f)) / (2.0f * fAcc);
			if (fVt >= fVmax)
			{
				fVt = fVmax;
			}
		}		
	}

}

//------------------------------------------------------------------
// @Function:	 Quadratic_Decrease()
// @Purpose: CerasusAlgorithm���εݼ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSALGORITHM_CALLMETHOD CCerasusAlgorithm::Quadratic_Decrease(float& fVt, float fV0, float fVmin, float fAcc)
{
	if (fAcc >= 0)
	{
		float fX0 = fV0;
		float fXt = sqrtf(2.0f * fAcc * (fV0 - fVt));

		fXt += fAcc;
		fVt = fX0 - powf(fXt, 2.0f) / (2.0f * fAcc);
		if (fVt <= fVmin)
		{
			fVt = fVmin;
		}
	}
	else
	{
		float fX0 = fV0;
		float fXl = sqrtf(2.0f * (-fAcc) * (fV0 - fVmin));
		float fXt = sqrtf(powf(fXl, 2.0f) + 2.0f * fAcc * (fVt - fV0));

		fXt += fAcc;
		if (fXt <= 0)
		{
			fVt = fVmin;
		}
		else
		{
			fVt = fX0 - (powf(fXt, 2.0f) - powf(fXl, 2.0f)) / (2.0f * fAcc);
			if (fVt <= fVmin)
			{
				fVt = fVmin;
			}
		}
	}

}
