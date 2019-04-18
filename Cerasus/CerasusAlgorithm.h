/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		CerasusAlgorithm.h
* @brief	This File is CerasusAlgorithm Dynamic Link Library Project.
* @author	alopex
* @version	v1.01a
* @date		2018-11-06	v1.00a	alopex	Create This File.
* @date		2019-04-18	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __CERASUSALGORITHM_H_
#define __CERASUSALGORITHM_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectThreadSafe.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSALGORITHM_API	__declspec(dllexport)
#else
#define CERASUSALGORITHM_API	__declspec(dllimport)
#endif

#define	CERASUSALGORITHM_CALLMETHOD	__stdcall

// Class Definition
class CERASUSALGORITHM_API CCerasusAlgorithm
{
public:
	CCerasusAlgorithm();			// CCerasusAlgorithm ���캯��
	~CCerasusAlgorithm();			// CCerasusAlgorithm ��������

	static void	CERASUSALGORITHM_CALLMETHOD	Increase(float& fVar, float fMax, float fStep);
	static void	CERASUSALGORITHM_CALLMETHOD	Decrease(float& fVar, float fMin, float fStep);
	static void	CERASUSALGORITHM_CALLMETHOD Circulation(float& fVar, float fMin, float fMax, float fStep);

	/*
	* ���Ժ���:Y=k*X
	*/
	static void	CERASUSALGORITHM_CALLMETHOD	Linear_Increase(float& fVar, float fMax, float fStep);							// CCerasusAlgorithm ���Ե���
	static void	CERASUSALGORITHM_CALLMETHOD	Linear_Decrease(float& fVar, float fMin, float fStep);							// CCerasusAlgorithm ���Եݼ�
	static void	CERASUSALGORITHM_CALLMETHOD Linear_Circulation(float& fVar, float fMin, float fMax, float fStep);			// CCerasusAlgorithm ����ѭ��

	/*
	* ���κ���:Y=k*X^2
	*/
	static void	CERASUSALGORITHM_CALLMETHOD	Quadratic_Increase(float& fVt, float fV0, float fVmax, float fAcc);				// CCerasusAlgorithm ���ε���
	static void	CERASUSALGORITHM_CALLMETHOD	Quadratic_Decrease(float& fVt, float fV0, float fVmin, float fAcc);				// CCerasusAlgorithm ���εݼ�

};

#endif // !__CERASUSALGORITHM_H_

