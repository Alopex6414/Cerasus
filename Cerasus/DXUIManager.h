/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIManager.h
* @brief	This File is DXUI Project File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-13	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __DXUIMANAGER_H_
#define __DXUIMANAGER_H_

// Include DXUI Common Header File
#include "DXUICommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DXUIMANAGER_API	__declspec(dllexport)
#else
#define DXUIMANAGER_API	__declspec(dllimport)
#endif

#define DXUIMANAGER_CALLMETHOD	__stdcall

// Class Definition
class DXUIMANAGER_API CDXUIManager
{
private:
	static HINSTANCE m_hInstance;

public:
	CDXUIManager();
	~CDXUIManager();

	static HINSTANCE	DXUIMANAGER_CALLMETHOD	GetInstance();
	static void			DXUIMANAGER_CALLMETHOD	SetInstance(HINSTANCE hInstance);

};

#endif // !__DXUIMANAGER_H_
