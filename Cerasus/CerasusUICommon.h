/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusUICommon.h
* @brief	This File is CreasusUI Common Header File.
* @author	alopex
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSUICOMMON_H_
#define __CERASUSUICOMMON_H_

//Include Direct Common Header File
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectSprite.h"
#include "DirectGraphics3D.h"
#include "DirectThreadSafe.h"

#include "CerasusUnit.h"

//Include C/C++ Standard Header File
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

//Using C/C++ Class Namespace
using namespace std;

//Macro Definition
#define MAX_CONTROL_STATES 6

//Enum Definition
enum CERASUS_CONTROL_TYPE
{
	CERASUS_CONTROL_BUTTON,
	CERASUS_CONTROL_STATIC,
	CERASUS_CONTROL_CHECKBOX,
	CERASUS_CONTROL_RADIOBUTTON,
	CERASUS_CONTROL_COMBOBOX,
	CERASUS_CONTROL_SLIDER,
	CERASUS_CONTROL_EDITBOX,
	CERASUS_CONTROL_IMEEDITBOX,
	CERASUS_CONTROL_LISTBOX,
	CERASUS_CONTROL_SCROLLBAR,
};

enum CERASUS_CONTROL_STATE
{
	CERASUS_STATE_NORMAL,
	CERASUS_STATE_DISABLED,
	CERASUS_STATE_HIDDEN,
	CERASUS_STATE_FOCUS,
	CERASUS_STATE_MOUSEOVER,
	CERASUS_STATE_PRESSED,
};

//Struct Definition

//Class Definition
class CCerasusDialog;
class CCerasusControl;
class CCerasusStatic;
class CCerasusButton;
class CCerasusResourceManager;

#endif // !__CERASUSUICOMMON_H_

