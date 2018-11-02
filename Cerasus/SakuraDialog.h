/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraDialog.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURADIALOG_H_
#define __SAKURADIALOG_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"
#include "SakuraStatic.h"
#include "SakuraButton.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURADIALOG_API	__declspec(dllexport)
#else
#define SAKURADIALOG_API	__declspec(dllimport)
#endif

#define	SAKURADIALOG_CALLMETHOD	__stdcall

//Class Definition
class SAKURADIALOG_API CSakuraDialog
{
private:
	int	m_nX;					// CSakuraDialog ����X������
	int m_nY;					// CSakuraDialog ����Y������
	int m_nWidth;				// CSakuraDialog ���ڿ��
	int m_nHeight;				// CSakuraDialog ���ڸ߶�

	bool	m_bVisible;			// CSakuraDialog ���ڿɼ�

	CSakuraControl*	m_pControlMouseOver;				// CSakuraDialog ����ڿؼ���

	static CSakuraControl*	s_pControlFocus;			// CSakuraDialog ��ý���ؼ�
	static CSakuraControl*	s_pControlPressed;			// CSakuraDialog ��ǰ���¿ؼ�

private:
	LPCALLBACKSAKURAGUIEVENT	m_pCallbackEvent;					// CSakuraDialog �����¼��ص�����
	void*						m_pCallbackEventUserContext;		// CSakuraDialog �����¼��ص��û�����

	vector<CSakuraControl*>		m_vecControls;						// CSakuraDialog ������ӵĿؼ�����

public:
	bool	m_bNonUserEvents;							// CSakuraDialog �û��¼���־
	bool	m_bKeyboardInput;							// CSakuraDialog ���������־
	bool	m_bMouseInput;								// CSakuraDialog ��������־

protected:
	void	OnMouseMove(POINT pt);						// CSakuraDialog ����ƶ�

public:
	CSakuraDialog();
	~CSakuraDialog();

	bool	SAKURADIALOG_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraDialog ������Ϣ����

	HRESULT SAKURADIALOG_CALLMETHOD	AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, CSakuraStatic** ppCreated = NULL);							// CSakuraDialog ������Ӿ�̬�ؼ�
	HRESULT SAKURADIALOG_CALLMETHOD	AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraButton** ppCreated = NULL);		// CSakuraDialog ������Ӱ�ť�ؼ�

	HRESULT	SAKURADIALOG_CALLMETHOD	AddControl(CSakuraControl* pControl);									// CSakuraDialog ������ӿؼ�
	HRESULT	SAKURADIALOG_CALLMETHOD	InitControl(CSakuraControl* pControl);									// CSakuraDialog ���ڳ�ʼ���ؼ�

	CSakuraStatic*	SAKURADIALOG_CALLMETHOD GetStatic(int ID);												// CSakuraDialog ���ڻ�ȡ��̬�ؼ�
	CSakuraButton*	SAKURADIALOG_CALLMETHOD GetButton(int ID);												// CSakuraDialog ���ڻ�ȡ��ť�ؼ�

	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID);												// CSakuraDialog ��ȡ�ؼ�ָ��
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID, UINT nControlType);							// CSakuraDialog ��ȡ�ؼ�ָ��
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControlAtPoint(POINT pt);									// CSakuraDialog ��ȡ������ڵĿؼ�ָ��

	void	SAKURADIALOG_CALLMETHOD	RemoveControl(int nID);													// CSakuraDialog �����Ƴ��ؼ�
	void	SAKURADIALOG_CALLMETHOD RemoveAllControls();													// CSakuraDialog �����Ƴ��ؼ�(ALL)

	void	SAKURADIALOG_CALLMETHOD	SetCallback(LPCALLBACKSAKURAGUIEVENT pCallback, void* pUserContext = NULL);						// CSakuraDialog �����¼��ص�����
	void	SAKURADIALOG_CALLMETHOD	EnableNonUserEvents(bool bEnable);																// CSakuraDialog ʹ�����û��¼�
	void    SAKURADIALOG_CALLMETHOD	EnableKeyboardInput(bool bEnable);																// CSakuraDialog ʹ�ܼ�������
	void    SAKURADIALOG_CALLMETHOD	EnableMouseInput(bool bEnable);																	// CSakuraDialog ʹ���������
	bool    SAKURADIALOG_CALLMETHOD	IsKeyboardInputEnabled() const;																	// CSakuraDialog �жϼ����Ƿ�ʹ��

	void	SAKURADIALOG_CALLMETHOD SendEvent(UINT nEvent, bool bTriggeredByUser, CSakuraControl* pControl);// CSakuraDialog �����¼�
	void	SAKURADIALOG_CALLMETHOD RequestFocus(CSakuraControl* pControl);									// CSakuraDialog ���󽹵�

	static void	SAKURADIALOG_CALLMETHOD	ClearFocus();														// CSakuraDialog ����ؼ�����

};


#endif // !__SAKURADIALOG_H_

