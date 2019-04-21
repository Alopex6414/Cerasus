/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraUICommon.h
* @brief	This File is SakuraGUI Common Header File.
* @author	alopex
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURAUICOMMON_H_
#define __SAKURAUICOMMON_H_

// Include Direct Common Header File
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectInput.h"
#include "DirectSprite.h"
#include "DirectSurface.h"
#include "DirectTexture.h"
#include "DirectGraphics3D.h"
#include "DirectThreadSafe.h"

// Include Cerasus Common Header File
#include "CerasusUnit.h"

// Include C/C++ Standard Header File
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

// Using C/C++ Class Namespace
using namespace std;

// Macro Definition
#define MAX_CONTROL_STATES 6

#define EVENT_BUTTON_CLICKED                0x0101
#define EVENT_COMBOBOX_SELECTION_CHANGED    0x0201
#define EVENT_RADIOBUTTON_CHANGED           0x0301
#define EVENT_CHECKBOX_CHANGED              0x0401
#define EVENT_SLIDER_VALUE_CHANGED          0x0501
#define EVENT_EDITBOX_STRING                0x0601
#define EVENT_EDITBOX_CHANGE                0x0602
#define EVENT_LISTBOX_ITEM_DBLCLK           0x0701
#define EVENT_LISTBOX_SELECTION             0x0702
#define EVENT_LISTBOX_SELECTION_END         0x0703

// Enum Definition
enum SAKURA_CONTROL_TYPE
{
	SAKURA_CONTROL_BUTTON,
	SAKURA_CONTROL_STATIC,
	SAKURA_CONTROL_CHECKBOX,
	SAKURA_CONTROL_RADIOBUTTON,
	SAKURA_CONTROL_COMBOBOX,
	SAKURA_CONTROL_SLIDER,
	SAKURA_CONTROL_EDITBOX,
	SAKURA_CONTROL_IMEEDITBOX,
	SAKURA_CONTROL_LISTBOX,
	SAKURA_CONTROL_SCROLLBAR,
	SAKURA_CONTROL_UNIT,
};

enum SAKURA_CONTROL_STATE
{
	SAKURA_STATE_NORMAL,
	SAKURA_STATE_DISABLED,
	SAKURA_STATE_HIDDEN,
	SAKURA_STATE_FOCUS,
	SAKURA_STATE_MOUSEOVER,
	SAKURA_STATE_PRESSED,
};

enum SAKURA_SCROLLBAR_STATE
{
	SAKURA_SCROLLBAR_STATE_CLEAR,
	SAKURA_SCROLLBAR_STATE_CLICKED_UP,
	SAKURA_SCROLLBAR_STATE_CLICKED_DOWN,
	SAKURA_SCROLLBAR_STATE_HELD_UP,
	SAKURA_SCROLLBAR_STATE_HELD_DOWN,
};

// Struct Definition
typedef struct
{
	WCHAR strFontName[MAX_PATH];
	int nFontSize;
} CUFont, *LPCUFont;

// Class Definition
class CSakuraResourceManager;
class CSakuraDialog;
class CSakuraControl;
class CSakuraStatic;
class CSakuraButton;
class CSakuraCheckBox;
class CSakuraRadioButton;
class CSakuraComboBox;
class CSakuraScrollBar;
class CSakuraSlider;
class CSakuraUnit;

// Function Declaration
typedef VOID(CALLBACK*LPCALLBACKSAKURAGUIEVENT)(UINT nEvent, int nControlID, CSakuraControl* pControl, void* pUserContext);

#endif // !__SAKURAUICOMMON_H_

