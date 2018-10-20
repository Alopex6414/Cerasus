/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusStatic.h
* @brief	This File is CerasusStatic DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSSTATIC_H_
#define __CERASUSSTATIC_H_

//Include CerasusUI Common Header File
#include "CerasusUICommon.h"
#include "CerasusControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSSTATIC_API	__declspec(dllexport)
#else
#define CERASUSSTATIC_API	__declspec(dllimport)
#endif

#define CERASUSSTATIC_CALLMODE	__stdcall

//Class Definition
class CERASUSSTATIC_API CCerasusStatic : public CCerasusControl
{
protected:
	WCHAR m_strText[MAX_PATH];			// CCerasusStatic ��̬�ؼ��ı�

public:
	CCerasusStatic();					// CCerasusStatic ���캯��

	virtual void	CERASUSSTATIC_CALLMODE Render();						// CCerasusStatic ��Ⱦ�ؼ�
	virtual BOOL	CERASUSSTATIC_CALLMODE ContainsPoint(POINT pt);			// CCerasusStatic ������ڿؼ���

	LPCWSTR			CERASUSSTATIC_CALLMODE GetText();						// CCerasusStatic ��ȡ��ǰ�ı�
	HRESULT			CERASUSSTATIC_CALLMODE SetText(LPCWSTR strText);		// CCerasusStatic ���õ�ǰ�ı�

};



#endif // !__CERASUSSTATIC_H_
