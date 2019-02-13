/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUICommon.h
* @brief	This File is DXUI Project Common Header File.
* @author	alopex
* @version	v1.00a
* @date		2019-02-13	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __DXUICOMMON_H_
#define __DXUICOMMON_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectGraphics.h"
#include "DirectGraphics2D.h"
#include "DirectGraphics3D.h"
#include "DirectInput.h"
#include "DirectSound.h"
#include "DirectShow.h"
#include "DirectMesh.h"
#include "DirectSprite.h"
#include "DirectSurface.h"
#include "DirectTexture.h"
#include "DirectThreadSafe.h"

// Include Cerasus Common Header File
#include "CerasusAlgorithm.h"
#include "Cerasusfps.h"
#include "CerasusUnit.h"

// Include Windows Header File
#include <Windows.h>
#include <CommCtrl.h>

// Include C/C++ Standard Header File
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

// Include Windows Libraries
#pragma comment(lib,"WinMM.lib")
#pragma comment(lib,"Comctl32.lib")

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DXUI_API	__declspec(dllexport)
#else
#define DXUI_API	__declspec(dllimport)
#endif

#define DXUI_CALLMETHOD	__stdcall

#endif // !__DXUICOMMON_H_