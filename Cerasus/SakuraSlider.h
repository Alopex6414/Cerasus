/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraSlider.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-30	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURASLIDER_H_
#define __SAKURASLIDER_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASLIDER_API	__declspec(dllexport)
#else
#define SAKURASLIDER_API	__declspec(dllimport)
#endif

#define	SAKURASLIDER_CALLMETHOD	__stdcall

//Class Definition
class SAKURASLIDER_API CSakuraSlider : public CSakuraControl
{
protected:
	int	m_nValue;			// CSakuraSlider ��ǰֵ

	int m_nMin;				// CSakuraSlider ��Сֵ
	int m_nMax;				// CSakuraSlider ���ֵ

	int m_nDragX;			// CSakuraSlider ��קX����
	int m_nDragOffset;		// CSakuraSlider ��קλ��ƫ��
	int m_nButtonX;			// CSakuraSlider ��ťX����

	bool m_bPressed;		// CSakuraSlider �����Ƿ񱻰�ѹ
	RECT m_rcButton;		// CSakuraSlider ���鰴ť����

protected:
	void	SAKURASLIDER_CALLMETHOD	SetValueInternal(int nValue, bool bFromInput);			// CSakuraSlider ����ֵ
	int		SAKURASLIDER_CALLMETHOD	ValueFromPos(int x);									// CSakuraSlider ����ֵ

public:
	CSakuraSlider(CSakuraDialog* pDialog = NULL);																// CSakuraSlider ���캯��

	virtual BOOL	SAKURASLIDER_CALLMETHOD	ContainsPoint(POINT pt);											// CSakuraSlider ����Ƿ����ڿؼ��ڲ�
	virtual bool    SAKURASLIDER_CALLMETHOD	CanHaveFocus();														// CSakuraSlider �Ƿ�ӵ�н���

	virtual bool    SAKURASLIDER_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraSlider ������Ϣ��Ӧ
	virtual bool    SAKURASLIDER_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraSlider �����Ϣ��Ӧ

	virtual void    SAKURASLIDER_CALLMETHOD	UpdateRects();														// CSakuraSlider ���¿ؼ�����
	virtual void    SAKURASLIDER_CALLMETHOD	Render();															// CSakuraSlider ��Ⱦ�ؼ�

	void            SAKURASLIDER_CALLMETHOD	SetValue(int nValue);												// CSakuraSlider ���û��鵱ǰֵ
	int             SAKURASLIDER_CALLMETHOD	GetValue() const;													// CSakuraSlider ��ȡ���鵱ǰֵ
	void            SAKURASLIDER_CALLMETHOD	GetRange(int& nMin, int& nMax) const;								// CSakuraSlider ��ȡ���鷶Χ
	void            SAKURASLIDER_CALLMETHOD	SetRange(int nMin, int nMax);										// CSakuraSlider ���û��鷶Χ

};


#endif // !__SAKURASLIDER_H_
