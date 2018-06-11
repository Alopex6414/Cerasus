/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSafe.cpp
* @brief	This Program is DirectSafe DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2018-1-3	v1.00a	alopex	Create Project.
* @date		2018-1-4	v1.01a	alopex	Modify inline Key Words.
* @date		2018-4-12	v1.02a	alopex	Add Macro Call Mode.
*/
#include "DirectCommon.h"
#include "DirectSafe.h"

//DirectSafe主要用于DirectX类库线程安全(~临界区)
CRITICAL_SECTION g_csDirect;
bool g_bDirectSafe = true;

//------------------------------------------------------------------
// @Function:	 DirectSafe()
// @Purpose: DirectSafe构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSafe::DirectSafe()
{
	if (g_bDirectSafe) EnterCriticalSection(&g_csDirect);
}

//------------------------------------------------------------------
// @Function:	 ~DirectSafe()
// @Purpose: DirectSafe析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSafe::~DirectSafe()
{
	if (g_bDirectSafe) LeaveCriticalSection(&g_csDirect);
}

//------------------------------------------------------------------
// @Function:	 DirectSafeInit()
// @Purpose: DirectSafe初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSAFE_CALLMODE DirectSafeInit()
{
	if (g_bDirectSafe) InitializeCriticalSection(&g_csDirect);
}

//------------------------------------------------------------------
// @Function:	 DirectSafeDelete()
// @Purpose: DirectSafe释放
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSAFE_CALLMODE DirectSafeDelete()
{
	if (g_bDirectSafe) DeleteCriticalSection(&g_csDirect);
}