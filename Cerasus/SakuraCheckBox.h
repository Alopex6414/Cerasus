/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraCheckBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-10	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURACHECKBOX_H_
#define __SAKURACHECKBOX_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraButton.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACHECKBOX_API	__declspec(dllexport)
#else
#define SAKURACHECKBOX_API	__declspec(dllimport)
#endif

#define	SAKURACHECKBOX_CALLMETHOD	__stdcall

//Class Definition
class SAKURACHECKBOX_API CSakuraCheckBox : public CSakuraButton
{
protected:
	bool	m_bChecked;
	RECT	m_rcButton;
	RECT	m_rcText;

protected:
	virtual	void	SAKURACHECKBOX_CALLMETHOD	SetCheckedInternal(bool bChecked, bool bFromInput);			// CSakuraCheckBox �����ڲ���ѡ

public:
	CSakuraCheckBox(CSakuraDialog* pDialog = NULL);			// CSakuraCheckBox ���캯��

	virtual void	SAKURACHECKBOX_CALLMETHOD	Render();					// CSakuraCheckBox ��Ⱦ�ؼ�

	virtual bool	SAKURACHECKBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraCheckBox ������Ϣ����
	virtual bool    SAKURACHECKBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraCheckBox �����Ϣ����

	virtual void    SAKURACHECKBOX_CALLMETHOD	OnHotkey();					// CSakuraCheckBox ����ȼ�
	virtual BOOL    SAKURACHECKBOX_CALLMETHOD	ContainsPoint(POINT pt);	// CSakuraCheckBox ����ڿؼ�����
	virtual void    SAKURACHECKBOX_CALLMETHOD	UpdateRects();				// CSakuraCheckBox ���¿ؼ�����

	bool			SAKURACHECKBOX_CALLMETHOD	GetChecked();				// CSakuraCheckBox ��ȡ�ؼ�ѡ��״̬
	void			SAKURACHECKBOX_CALLMETHOD	SetChecked(bool bChecked);	// CSakuraCheckBox ���ÿؼ�ѡ��״̬

};

#endif // !__SAKURACHECKBOX_H_
