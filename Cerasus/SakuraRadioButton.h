/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraRadioButton.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-13	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURARADIOBUTTON_H_
#define __SAKURARADIOBUTTON_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraCheckBox.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURARADIOBUTTON_API	__declspec(dllexport)
#else
#define SAKURARADIOBUTTON_API	__declspec(dllimport)
#endif

#define	SAKURARADIOBUTTON_CALLMETHOD	__stdcall

//Class Definition
class SAKURARADIOBUTTON_API CSakuraRadioButton : public CSakuraCheckBox
{
protected:
	UINT m_nButtonGroup;

protected:
	virtual void	SAKURARADIOBUTTON_CALLMETHOD	SetCheckedInternal(bool bChecked, bool bClearGroup, bool bFromInput);			// CSakuraRadioButton �ڲ�ѡ�пؼ�

public:
	CSakuraRadioButton(CSakuraDialog* pDialog = NULL);			// CSakuraRadioButton ���캯��

	virtual bool	SAKURARADIOBUTTON_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraRadioButton ������Ϣ����
	virtual bool    SAKURARADIOBUTTON_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraRadioButton �����Ϣ����

	virtual void    SAKURARADIOBUTTON_CALLMETHOD	OnHotkey();															// CSakuraRadioButton ����ȼ�
	void			SAKURARADIOBUTTON_CALLMETHOD	SetChecked(bool bChecked, bool bClearGroup = true);					// CSakuraRadioButton ���ÿؼ�ѡ��
	void			SAKURARADIOBUTTON_CALLMETHOD	SetButtonGroup(UINT nButtonGroup);									// CSakuraRadioButton ���ÿؼ����
	UINT			SAKURARADIOBUTTON_CALLMETHOD	GetButtonGroup();													// CSakuraRadioButton ��ȡ�ؼ����

};



#endif // !__SAKURARADIOBUTTON_H_
