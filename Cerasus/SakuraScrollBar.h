/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraScrollBar.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-28	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURASCROLLBAR_H_
#define __SAKURASCROLLBAR_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASCROLLBAR_API	__declspec(dllexport)
#else
#define SAKURASCROLLBAR_API	__declspec(dllimport)
#endif

#define	SAKURASCROLLBAR_CALLMETHOD	__stdcall

#define SCROLLBAR_MINTHUMBSIZE	8

//Class Definition
class SAKURASCROLLBAR_API CSakuraScrollBar : public CSakuraControl
{
protected:
	bool m_bShowThumb;			// CSakuraScrollBar �Ƿ���ʾ����������
	bool m_bDrag;				// CSakuraScrollBar �Ƿ���ק

	RECT m_rcUpButton;			// CSakuraScrollBar �������ϻ���ť����
	RECT m_rcDownButton;		// CSakuraScrollBar �������»���ť����
	RECT m_rcTrack;				// CSakuraScrollBar �������켣����
	RECT m_rcThumb;				// CSakuraScrollBar ��������������

	int m_nPosition;			// CSakuraScrollBar ��һ����ʾλ��
	int m_nPageSize;			// CSakuraScrollBar ÿҳ��ʾ������
	int m_nStart;				// CSakuraScrollBar ��һ����λ��
	int m_nEnd;					// CSakuraScrollBar ���һ��λ��

	POINT m_LastMouse;			// CSakuraScrollBar �ϴ����λ��
	SAKURA_SCROLLBAR_STATE m_eArrow;	// CSakuraScrollBar ������״̬
	double m_dArrowTS;

protected:
	void	SAKURASCROLLBAR_CALLMETHOD	UpdateThumbRect();	// CSakuraScrollBar ������λ�ø���
	void	SAKURASCROLLBAR_CALLMETHOD	Cap();				// CSakuraScrollBar ������λ�ü��

public:
	CSakuraScrollBar(CSakuraDialog* pDialog = NULL);		// CSakuraScrollBar ���캯��
	virtual	~CSakuraScrollBar();							// CSakuraScrollBar ��������

	virtual bool	SAKURASCROLLBAR_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraScrollBar ������Ϣ��Ӧ
	virtual bool    SAKURASCROLLBAR_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraScrollBar �����Ϣ��Ӧ
	virtual bool    SAKURASCROLLBAR_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraScrollBar ��Ϣ����

	virtual void    SAKURASCROLLBAR_CALLMETHOD	Render();															// CSakuraScrollBar ��Ⱦ�ؼ�
	virtual void    SAKURASCROLLBAR_CALLMETHOD	UpdateRects();														// CSakuraScrollBar ���¿ؼ�����

	void            SAKURASCROLLBAR_CALLMETHOD	SetTrackRange(int nStart, int nEnd);								// CSakuraScrollBar ���ù켣��Χ
	int             SAKURASCROLLBAR_CALLMETHOD	GetTrackPos();														// CSakuraScrollBar ��ȡ�켣λ��
	void			SAKURASCROLLBAR_CALLMETHOD  SetTrackPos(int nPosition);											// CSakuraScrollBar ���ù켣λ��
	int             SAKURASCROLLBAR_CALLMETHOD	GetPageSize();														// CSakuraScrollBar ��ȡÿҳ����
	void            SAKURASCROLLBAR_CALLMETHOD	SetPageSize(int nPageSize);											// CSakuraScrollBar ����ÿҳ����

	void            SAKURASCROLLBAR_CALLMETHOD	Scroll(int nDelta);													// CSakuraScrollBar ����������
	void            SAKURASCROLLBAR_CALLMETHOD	ShowItem(int nIndex);												// CSakuraScrollBar ��ʾ����
};


#endif // !__SAKURASCROLLBAR_H_

