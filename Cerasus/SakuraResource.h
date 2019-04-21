/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraResource.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-12	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURARESOURCE_H_
#define __SAKURARESOURCE_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURARESOURCE_API	__declspec(dllexport)
#else
#define SAKURARESOURCE_API	__declspec(dllimport)
#endif

#define	SAKURARESOURCE_CALLMETHOD	__stdcall

// Class Definition
class SAKURARESOURCE_API CSakuraResource
{
public:
	// Button
	static unsigned char m_ucButton_Native[2935];

	// CheckBox
	static unsigned char m_ucCheckBox_UnChecked[720];
	static unsigned char m_ucCheckBox_Checked[822];
	static unsigned char m_ucCheckBox_Partical[780];

	// RadioButton
	static unsigned char m_ucRadioButton_UnChecked[851];
	static unsigned char m_ucRadioButton_Checked[900];

	// StarButton
	static unsigned char m_ucStarButton_Empty[900];
	static unsigned char m_ucStarButton_Full[862];
	static unsigned char m_ucStarButton_Half[889];

};

#endif // !__SAKURARESOURCE_H_
