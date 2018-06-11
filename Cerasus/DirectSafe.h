/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSafe.h
* @brief	This Program is DirectSafe DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-1-3	v1.00a	alopex	Create Project.
* @date		2018-1-4	v1.01a	alopex	Modify inline Key Words.
* @date		2018-4-12	v1.02a	alopex	Add Macro Call Mode.
*/
#pragma once

#ifndef __DIRECTSAFE_H_
#define __DIRECTSAFE_H_

//Include DirectX Common Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTSAFE_API	__declspec(dllexport)
#else
#define DIRECTSAFE_API	__declspec(dllimport)
#endif

#define DIRECTSAFE_CALLMODE	__stdcall

//Class Definition
class DIRECTSAFE_API DirectSafe
{
public:
	DirectSafe();
	~DirectSafe();
};

//Variable Definition
extern "C" DIRECTSAFE_API CRITICAL_SECTION g_csDirect;
extern "C" DIRECTSAFE_API bool g_bDirectSafe;

//Function Definition
extern "C" DIRECTSAFE_API void DIRECTSAFE_CALLMODE DirectSafeInit();
extern "C" DIRECTSAFE_API void DIRECTSAFE_CALLMODE DirectSafeDelete();

#endif