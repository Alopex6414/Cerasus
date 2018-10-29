/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusButton.h
* @brief	This File is CerasusButton DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-22	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSBUTTON_H_
#define __CERASUSBUTTON_H_

//Include CerasusUI Common Header File
#include "CerasusUICommon.h"
#include "CerasusStatic.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSBUTTON_API	__declspec(dllexport)
#else
#define CERASUSBUTTON_API	__declspec(dllimport)
#endif

#define CERASUSBUTTON_CALLMODE	__stdcall

//Class Definition
class CCerasusButton : public CCerasusStatic
{
protected:
	bool m_bPressed;

public:
	CCerasusButton(CCerasusDialog* pDialog = NULL);						// CCerasusButton ���캯��

	virtual void	CERASUSBUTTON_CALLMODE Render(float fElapsedTime);	// CCerasusButton ��Ⱦ�ؼ�

	virtual bool	CERASUSBUTTON_CALLMODE HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);				// CCerasusButton ������Ϣ����
	virtual bool	CERASUSBUTTON_CALLMODE HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CCerasusButton �����Ϣ����

	virtual void	CERASUSBUTTON_CALLMODE OnHotkey();					// CCerasusButton ����ȼ�
	virtual BOOL	CERASUSBUTTON_CALLMODE ContainsPoint(POINT pt);		// CCerasusButton ������ڿؼ���
	virtual bool	CERASUSBUTTON_CALLMODE CanHaveFocus();				// CCerasusButton �Ƿ�ӵ�н���

};



#endif // !__CERASUSBUTTON_H_

