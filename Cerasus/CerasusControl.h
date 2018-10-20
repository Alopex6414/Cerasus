/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusControl.h
* @brief	This File is CerasusControl DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSCONTROL_H_
#define __CERASUSCONTROL_H_

//Include CerasusUI Common Header File
#include "CerasusUICommon.h"
#include "CerasusElement.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSCONTROL_API	__declspec(dllexport)
#else
#define CERASUSCONTROL_API	__declspec(dllimport)
#endif

#define CERASUSCONTROL_CALLMODE	__stdcall

//Class Definition
class CERASUSCONTROL_API CCerasusControl
{
public:
	int m_nX;					// CCerasusControl �ؼ�X����
	int m_nY;					// CCerasusControl �ؼ�Y����
	int m_nWidth;				// CCerasusControl �ؼ����
	int m_nHeight;				// CCerasusControl �ؼ��߶�

	bool m_bVisible;			// CCerasusControl �ؼ��Ƿ�ɼ�(true:��ʾ/false:����)
	bool m_bMouseOver;			// CCerasusControl ���ָ���ڿؼ���(true:��/false:��)
	bool m_bHasFocus;			// CCerasusControl �ؼ��Ƿ�ӵ�����뽹��(true:��/false:��)
	bool m_bIsDefault;			// CCerasusControl �ؼ��Ƿ���Ĭ�Ͽؼ�(true:��/false:��)

	//CDXUTDialog* m_pDialog;    // CCerasusControl Parent container
	UINT m_nIndex;              // CCerasusControl �ؼ��б��пؼ�����

	CCerasusElement* m_Element;	// CCerasusControl �ؼ���ȾԪ��

protected:
	int m_nID;						// CCerasusControl �ؼ����
	CERASUS_CONTROL_TYPE m_eType;	// CCerasusControl �ؼ�����

	UINT m_nHotkey;					// CCerasusControl ���ⰴ������
	LPVOID m_pUserData;				// CCerasusControl �û����ݵ�ַ

	bool m_bEnabled;				// CCerasusControl �ؼ��Ƿ�ʹ��(true:��/false:��)
	RECT m_rcBoundingBox;			// CCerasusControl �ؼ�ʹ������

protected:
	virtual void	CERASUSCONTROL_CALLMODE UpdateRects();				// CCerasusControl ���¿ؼ�����

public:
	CCerasusControl();				// CCerasusControl ���캯��
	virtual ~CCerasusControl();		// CCerasusControl ��������

	virtual HRESULT CERASUSCONTROL_CALLMODE OnInit();					// CCerasusControl ��ʼ���ؼ�
	virtual void	CERASUSCONTROL_CALLMODE Refresh();					// CCerasusControl ˢ�¿ؼ�
	virtual void	CERASUSCONTROL_CALLMODE Render();					// CCerasusControl ��Ⱦ�ؼ�

	virtual bool	CERASUSCONTROL_CALLMODE MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CCerasusControl ��Ϣ����
	virtual bool	CERASUSCONTROL_CALLMODE HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);	// CCerasusControl ������Ϣ����
	virtual bool	CERASUSCONTROL_CALLMODE HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CCerasusControl �����Ϣ����

	virtual bool	CERASUSCONTROL_CALLMODE	CanHaveFocus();				// CCerasusControl �Ƿ�ӵ�н���
	virtual void	CERASUSCONTROL_CALLMODE	OnFocusIn();				// CCerasusControl ���ý���
	virtual void	CERASUSCONTROL_CALLMODE	OnFocusOut();				// CCerasusControl ��ʧ����
	virtual void	CERASUSCONTROL_CALLMODE	OnMouseEnter();				// CCerasusControl ������
	virtual void	CERASUSCONTROL_CALLMODE OnMouseLeave();				// CCerasusControl ����뿪
	virtual void	CERASUSCONTROL_CALLMODE OnHotkey();					// CCerasusControl ����ȼ�
	virtual BOOL	CERASUSCONTROL_CALLMODE ContainsPoint(POINT pt);	// CCerasusControl ������ڿؼ���
	virtual void	CERASUSCONTROL_CALLMODE SetEnabled(bool bEnabled);	// CCerasusControl ���ÿؼ�ʹ��
	virtual bool	CERASUSCONTROL_CALLMODE GetEnabled();				// CCerasusControl ��ȡ�ؼ�ʹ��
	virtual void	CERASUSCONTROL_CALLMODE SetVisible(bool bVisible);	// CCerasusControl ���ÿؼ��ɼ�
	virtual bool	CERASUSCONTROL_CALLMODE GetVisible();				// CCerasusControl ��ȡ�ؼ��ɼ�
	UINT			CERASUSCONTROL_CALLMODE GetType() const;			// CCerasusControl ��ȡ�ؼ�����
	int				CERASUSCONTROL_CALLMODE GetID() const;				// CCerasusControl ��ȡ�ؼ�ID
	void			CERASUSCONTROL_CALLMODE SetID(int nID);				// CCerasusControl ���ÿؼ�ID
	void			CERASUSCONTROL_CALLMODE SetLocation(int x, int y);	// CCerasusControl ���ÿؼ�����
	void			CERASUSCONTROL_CALLMODE SetSize(int width, int height);			// CCerasusControl ���ÿؼ���״
	void			CERASUSCONTROL_CALLMODE SetHotkey(UINT nHotkey);	// CCerasusControl ���������ֵ
	UINT			CERASUSCONTROL_CALLMODE GetHotkey();				// CCerasusControl ��ȡ�����ֵ
	void			CERASUSCONTROL_CALLMODE SetUserData(void* pUserData);			// CCerasusControl �����û�����
	void*			CERASUSCONTROL_CALLMODE GetUserData();				// CCerasusControl ��ȡ�û�����
	CCerasusElement*CERASUSCONTROL_CALLMODE GetElement();				// CCerasusControl ��ȡ��ȾԪ��
	HRESULT			CERASUSCONTROL_CALLMODE SetElement(CCerasusElement* pElement);	// CCerasusControl ������ȾԪ��

};


#endif // !__CERASUSCONTROL_H_

