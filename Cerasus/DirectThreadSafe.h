/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectThreadSafe.h
* @brief	This Program is DirectThreadSafe Header File.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-01-10	v1.00a	alopex	Create This File.
* @date		2019-04-18	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTTHREADSAFE_H_
#define __DIRECTTHREADSAFE_H_

// Include DirectX Common Header File
#include "DirectCommon.h"

// Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTTHREADSAFE_API	__declspec(dllexport)
#else
#define DIRECTTHREADSAFE_API	__declspec(dllimport)
#endif

// Class Definition
class DIRECTTHREADSAFE_API DirectThreadSafe
{
private:
	CRITICAL_SECTION* m_pCriticalSection;					// CriticalSection Variable
	bool m_bThreadSafe;										// CriticalSection ThreadSafe Use Variable

public:
	DirectThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe);
	~DirectThreadSafe();
};

#endif