/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraEditBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-12-04	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURAEDITBOX_H_
#define __SAKURAEDITBOX_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURAEDITBOX_API	__declspec(dllexport)
#else
#define SAKURAEDITBOX_API	__declspec(dllimport)
#endif

#define	SAKURAEDITBOX_CALLMETHOD	__stdcall

//Class Definition
class SAKURAEDITBOX_API CSakuraEditBox : public CSakuraControl
{
public:
			CSakuraEditBox(CSakuraDialog* pDialog = NULL);
	virtual ~CSakuraEditBox();

};



#endif // !__SAKURAEDITBOX_H_

