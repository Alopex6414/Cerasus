/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraUnit.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2019-01-06	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURAUNIT_H_
#define __SAKURAUNIT_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURAUNIT_API	__declspec(dllexport)
#else
#define SAKURAUNIT_API	__declspec(dllimport)
#endif

#define	SAKURAUNIT_CALLMETHOD	__stdcall

//Class Definition
class SAKURAUNIT_API CSakuraUnit : public CSakuraControl
{
public:
	CSakuraUnit(CSakuraDialog* pDialog = NULL);		// CSakuraUnit 构造函数

	virtual void	SAKURAUNIT_CALLMETHOD	Render();			// CSakuraUnit 渲染控件

};

#endif // !__SAKURAUNIT_H_

