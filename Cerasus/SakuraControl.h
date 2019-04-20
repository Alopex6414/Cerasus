/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraControl.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURACONTROL_H_
#define __SAKURACONTROL_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraElement.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACONTROL_API	__declspec(dllexport)
#else
#define SAKURACONTROL_API	__declspec(dllimport)
#endif

#define	SAKURACONTROL_CALLMETHOD	__stdcall

// Class Definition
class SAKURACONTROL_API CSakuraControl
{
public:
	int m_nX;					// CSakuraControl �ؼ�X����
	int m_nY;					// CSakuraControl �ؼ�Y����
	int m_nWidth;				// CSakuraControl �ؼ����
	int m_nHeight;				// CSakuraControl �ؼ��߶�

	bool m_bVisible;			// CSakuraControl �ؼ��Ƿ�ɼ�(true:��ʾ/false:����)
	bool m_bMouseOver;			// CSakuraControl ���ָ���ڿؼ���(true:��/false:��)
	bool m_bHasFocus;			// CSakuraControl �ؼ��Ƿ�ӵ�����뽹��(true:��/false:��)
	bool m_bIsDefault;			// CSakuraControl �ؼ��Ƿ���Ĭ�Ͽؼ�(true:��/false:��)

	CSakuraDialog* m_pDialog;	// CSakuraControl ���ڿؼ�����
	UINT m_nIndex;              // CSakuraControl �ؼ��б��пؼ�����

	vector<CSakuraElement*> m_vecElements;								// CSakuraControl �ؼ���ȾԪ��

protected:
	int m_nID;						// CSakuraControl �ؼ����
	SAKURA_CONTROL_TYPE m_eType;	// CSakuraControl �ؼ�����

	UINT m_nHotkey;					// CSakuraControl ���ⰴ������
	LPVOID m_pUserData;				// CSakuraControl �û����ݵ�ַ

	bool m_bEnabled;				// CSakuraControl �ؼ��Ƿ�ʹ��(true:��/false:��)
	RECT m_rcBoundingBox;			// CSakuraControl �ؼ�ʹ������

protected:
	virtual void	SAKURACONTROL_CALLMETHOD UpdateRects();				// CSakuraControl ���¿ؼ�����

public:
	CSakuraControl(CSakuraDialog* pDialog = NULL);						// CSakuraControl ���캯��
	virtual ~CSakuraControl();											// CSakuraControl ��������

	virtual HRESULT SAKURACONTROL_CALLMETHOD	OnInit();					// CSakuraControl ��ʼ���ؼ�
	virtual void	SAKURACONTROL_CALLMETHOD	Refresh();					// CSakuraControl ˢ�¿ؼ�
	virtual void	SAKURACONTROL_CALLMETHOD	Render();					// CSakuraControl ��Ⱦ�ؼ�

	virtual bool	SAKURACONTROL_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraControl ��Ϣ����
	virtual bool	SAKURACONTROL_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraControl ������Ϣ����
	virtual bool	SAKURACONTROL_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraControl �����Ϣ����

	vector<CSakuraElement*>&	SAKURACONTROL_CALLMETHOD	GetElements();	// CSakuraControl ��ȡ�ؼ���ȾԪ��

	virtual bool	SAKURACONTROL_CALLMETHOD	CanHaveFocus();				// CSakuraControl �Ƿ�ӵ�н���
	virtual void	SAKURACONTROL_CALLMETHOD	OnFocusIn();				// CSakuraControl ���ý���
	virtual void	SAKURACONTROL_CALLMETHOD	OnFocusOut();				// CSakuraControl ��ʧ����
	virtual void	SAKURACONTROL_CALLMETHOD	OnMouseEnter();				// CSakuraControl ������
	virtual void	SAKURACONTROL_CALLMETHOD	OnMouseLeave();				// CSakuraControl ����뿪
	virtual void	SAKURACONTROL_CALLMETHOD	OnHotkey();					// CSakuraControl ����ȼ�
	virtual BOOL	SAKURACONTROL_CALLMETHOD	ContainsPoint(POINT pt);	// CSakuraControl ������ڿؼ���
	virtual void	SAKURACONTROL_CALLMETHOD	SetEnabled(bool bEnabled);	// CSakuraControl ���ÿؼ�ʹ��
	virtual bool	SAKURACONTROL_CALLMETHOD	GetEnabled();				// CSakuraControl ��ȡ�ؼ�ʹ��
	virtual void	SAKURACONTROL_CALLMETHOD	SetVisible(bool bVisible);	// CSakuraControl ���ÿؼ��ɼ�
	virtual bool	SAKURACONTROL_CALLMETHOD	GetVisible();				// CSakuraControl ��ȡ�ؼ��ɼ�
	UINT			SAKURACONTROL_CALLMETHOD	GetType() const;			// CSakuraControl ��ȡ�ؼ�����
	int				SAKURACONTROL_CALLMETHOD	GetID() const;				// CSakuraControl ��ȡ�ؼ�ID
	void			SAKURACONTROL_CALLMETHOD	SetID(int nID);				// CSakuraControl ���ÿؼ�ID
	void			SAKURACONTROL_CALLMETHOD	SetLocation(int x, int y);	// CSakuraControl ���ÿؼ�����
	void			SAKURACONTROL_CALLMETHOD	SetSize(int width, int height);			// CSakuraControl ���ÿؼ���״
	void			SAKURACONTROL_CALLMETHOD	SetHotkey(UINT nHotkey);	// CSakuraControl ���������ֵ
	UINT			SAKURACONTROL_CALLMETHOD	GetHotkey();				// CSakuraControl ��ȡ�����ֵ
	void			SAKURACONTROL_CALLMETHOD	SetUserData(void* pUserData);			// CSakuraControl �����û�����
	void*			SAKURACONTROL_CALLMETHOD	GetUserData();				// CSakuraControl ��ȡ�û�����
	CSakuraElement*&SAKURACONTROL_CALLMETHOD	GetElement(UINT iElement);	// CSakuraControl ��ȡ��ȾԪ��

};


#endif // !__SAKURACONTROL_H_

