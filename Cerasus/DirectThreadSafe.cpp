/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectThreadSafe.cpp
* @brief	This Program is DirectThreadSafe Header File.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-01-10	v1.00a	alopex	Create This File.
* @date		2019-04-18	v1.01a	alopex	Add Notes.
*/
#include "DirectThreadSafe.h"

// DirectThreadSafe构造函数
DirectThreadSafe::DirectThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe)
{
	m_pCriticalSection = (CRITICAL_SECTION*)pCriticalSection;
	m_bThreadSafe = bThreadSafe;

	if (m_bThreadSafe) EnterCriticalSection(m_pCriticalSection);
}

// DirectThreadSafe析构函数
DirectThreadSafe::~DirectThreadSafe()
{
	if (m_bThreadSafe) LeaveCriticalSection(m_pCriticalSection);
}