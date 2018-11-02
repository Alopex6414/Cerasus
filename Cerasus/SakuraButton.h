/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraButton.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURABUTTON_H_
#define __SAKURABUTTON_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraStatic.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURABUTTON_API	__declspec(dllexport)
#else
#define SAKURABUTTON_API	__declspec(dllimport)
#endif

#define	SAKURABUTTON_CALLMETHOD	__stdcall

//Class Definition
class SAKURABUTTON_API CSakuraButton : public CSakuraStatic
{
protected:
	bool m_bPressed;			// CSakuraButton ����״̬

public:
	CSakuraButton(CSakuraDialog* pDialog = NULL);							// CSakuraButton ���캯��

	virtual void	SAKURABUTTON_CALLMETHOD	Render();						// CSakuraButton ��Ⱦ�ؼ�

	virtual bool	SAKURABUTTON_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraButton ������Ϣ����
	virtual bool	SAKURABUTTON_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraButton �����Ϣ����

	virtual void	SAKURABUTTON_CALLMETHOD OnHotkey();						// CSakuraButton ����ȼ�
	virtual BOOL	SAKURABUTTON_CALLMETHOD ContainsPoint(POINT pt);		// CSakuraButton ������ڿؼ���
	virtual bool	SAKURABUTTON_CALLMETHOD CanHaveFocus();					// CSakuraButton �Ƿ�ӵ�н���

};



#endif // !__SAKURABUTTON_H_

