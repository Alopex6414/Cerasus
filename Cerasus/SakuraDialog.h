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
#include "SakuraResourceManager.h"
#include "SakuraResource.h"
#include "SakuraControl.h"
#include "SakuraStatic.h"
#include "SakuraButton.h"
#include "SakuraCheckBox.h"
#include "SakuraRadioButton.h"
#include "SakuraComboBox.h"
#include "SakuraSlider.h"
#include "SakuraScrollBar.h"
#include "SakuraUnit.h"

#include "DirectGraphics.h"

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
	friend class CSakuraDialog;

private:
	int	m_nX;					// CSakuraDialog ����X������
	int m_nY;					// CSakuraDialog ����Y������
	int m_nWidth;				// CSakuraDialog ���ڿ��
	int m_nHeight;				// CSakuraDialog ���ڸ߶�

	bool	m_bVisible;			// CSakuraDialog ���ڿɼ�

	D3DCOLOR	m_colorTopLeft;							// CSakuraDialog �������ϽǶ�����ɫ
	D3DCOLOR	m_colorTopRight;						// CSakuraDialog �������ϽǶ�����ɫ
	D3DCOLOR	m_colorBottomLeft;						// CSakuraDialog �������½Ƕ�����ɫ
	D3DCOLOR	m_colorBottomRight;						// CSakuraDialog �������½Ƕ�����ɫ

	CSakuraControl*	m_pControlMouseOver;				// CSakuraDialog ����ڿؼ���

	static CSakuraControl*	s_pControlFocus;			// CSakuraDialog ��ý���ؼ�
	static CSakuraControl*	s_pControlPressed;			// CSakuraDialog ��ǰ���¿ؼ�

private:
	CSakuraResourceManager*		m_pManager;							// CSakuraDialog ������Դ��
	LPCALLBACKSAKURAGUIEVENT	m_pCallbackEvent;					// CSakuraDialog �����¼��ص�����
	void*						m_pCallbackEventUserContext;		// CSakuraDialog �����¼��ص��û�����

	vector<CSakuraControl*>		m_vecControls;						// CSakuraDialog ������ӵĿؼ�����
	vector<CSakuraElementHolder*>	m_vecDefaultControls;			// CSakuraDialog ����Ĭ�Ͽؼ�Ԫ������

protected:
	CCerasusUnit*	m_pDialogGraphics;					// CSakuraDialog ���ڻ��Ʊ���

public:
	bool	m_bNonUserEvents;							// CSakuraDialog �û��¼���־
	bool	m_bKeyboardInput;							// CSakuraDialog ���������־
	bool	m_bMouseInput;								// CSakuraDialog ��������־

protected:
	void	SAKURADIALOG_CALLMETHOD	OnMouseMove(POINT pt);													// CSakuraDialog ����ƶ�
	void	SAKURADIALOG_CALLMETHOD	InitDefaultElement();													// CSakuraDialog ���ڿؼ�Ĭ����Դ��ʼ��
	void	SAKURADIALOG_CALLMETHOD AlterDefaultElement(CSakuraControl* pControl);							// CSakuraDialog ���ڿؼ�Ĭ����Դ�޸�

public:
	CSakuraDialog();
	~CSakuraDialog();

	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager);								// CSakuraDialog ���ڳ�ʼ����Ӧ
	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager, CUUint sUnit);				// CSakuraDialog ���ڳ�ʼ����Ӧ
	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager, CUUintEx sUnit);				// CSakuraDialog ���ڳ�ʼ����Ӧ

	void	SAKURADIALOG_CALLMETHOD	OnLost();																// CSakuraDialog ���ڶ�ʧ�豸
	void	SAKURADIALOG_CALLMETHOD	OnReset();																// CSakuraDialog ���������豸
	
	bool	SAKURADIALOG_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraDialog ������Ϣ����

	HRESULT SAKURADIALOG_CALLMETHOD	AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, CSakuraStatic** ppCreated = NULL);																				// CSakuraDialog ������Ӿ�̬�ؼ�
	HRESULT SAKURADIALOG_CALLMETHOD	AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraButton** ppCreated = NULL);															// CSakuraDialog ������Ӱ�ť�ؼ�
	HRESULT SAKURADIALOG_CALLMETHOD AddCheckBox(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, CSakuraCheckBox** ppCreated = NULL);								// CSakuraDialog ������Ӹ�ѡ��ؼ�
	HRESULT	SAKURADIALOG_CALLMETHOD AddRadioButton(int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, CSakuraRadioButton** ppCreated = NULL);		// CSakuraDialog ������ӵ�ѡ��ؼ�
	HRESULT	SAKURADIALOG_CALLMETHOD	AddComboBox(int ID, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraComboBox** ppCreated = NULL);																		// CSakuraDialog �����������ѡ���ؼ�
	HRESULT	SAKURADIALOG_CALLMETHOD	AddSlider(int ID, int x, int y, int width, int height, int min = 0, int max = 100, int value = 50, bool bIsDefault = false, CSakuraSlider** ppCreated = NULL);													// CSakuraDialog ������ӻ���ؼ�
	HRESULT SAKURADIALOG_CALLMETHOD AddUnit(int ID, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraUnit** ppCreated = NULL);

	HRESULT	SAKURADIALOG_CALLMETHOD	AddControl(CSakuraControl* pControl);									// CSakuraDialog ������ӿؼ�
	HRESULT	SAKURADIALOG_CALLMETHOD	InitControl(CSakuraControl* pControl);									// CSakuraDialog ���ڳ�ʼ���ؼ�

	HRESULT	SAKURADIALOG_CALLMETHOD	AddFont(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);			// CSakuraDialog ������ӿؼ�����
	HRESULT	SAKURADIALOG_CALLMETHOD AddTexture(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);		// CSakuraDialog ������ӿؼ�����
	HRESULT	SAKURADIALOG_CALLMETHOD AddTextureEx(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);		// CSakuraDialog ������ӿؼ�����Ex

	CCerasusUnit*		SAKURADIALOG_CALLMETHOD GetDialogGraphics();										// CSakuraDialog ���ڻ�ȡ����ͼ��

	CSakuraStatic*		SAKURADIALOG_CALLMETHOD GetStatic(int ID);											// CSakuraDialog ���ڻ�ȡ��̬�ؼ�
	CSakuraButton*		SAKURADIALOG_CALLMETHOD GetButton(int ID);											// CSakuraDialog ���ڻ�ȡ��ť�ؼ�
	CSakuraCheckBox*	SAKURADIALOG_CALLMETHOD	GetCheckBox(int ID);										// CSakuraDialog ���ڻ�ȡ��ѡ��ؼ�
	CSakuraRadioButton*	SAKURADIALOG_CALLMETHOD	GetRadioButton(int ID);										// CSakuraDialog ���ڻ�ȡ��ѡ��ؼ�
	CSakuraComboBox*	SAKURADIALOG_CALLMETHOD	GetComboBox(int ID);										// CSakuraDialog ���ڻ�ȡ������ؼ�
	CSakuraSlider*		SAKURADIALOG_CALLMETHOD GetSlider(int ID);											// CSakuraDialog ���ڻ�ȡ����ؼ�
	CSakuraUnit*		SAKURADIALOG_CALLMETHOD GetUnit(int ID);											// CSakuraDialog ���ڻ�ȡͼ�οؼ�

	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID);												// CSakuraDialog ��ȡ�ؼ�ָ��
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID, UINT nControlType);							// CSakuraDialog ��ȡ�ؼ�ָ��
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControlAtPoint(POINT pt);									// CSakuraDialog ��ȡ������ڵĿؼ�ָ��

	bool	SAKURADIALOG_CALLMETHOD GetControlEnabled(int ID);												// CSakuraDialog ��ȡ�ؼ�ʹ��
	void	SAKURADIALOG_CALLMETHOD	SetControlEnabled(int ID, bool bEnabled);								// CSakuraDialog ���ÿؼ�ʹ��

	void	SAKURADIALOG_CALLMETHOD	ClearRadioButtonGroup(UINT nGroup);										// CSakuraDialog �����ѡ��ť�����
	void	SAKURADIALOG_CALLMETHOD	ClearComboBox(int nID);													// CSakuraDialog ��������б�

	HRESULT	SAKURADIALOG_CALLMETHOD SetDefaultElement(UINT nControlType, UINT iElement, CSakuraElement** ppElement);				// CSakuraDialog ����Ĭ�Ͽؼ�Ԫ��
	CSakuraElement*	SAKURADIALOG_CALLMETHOD	GetDefaultElement(UINT nControlType, UINT iElement);									// CSakuraDialog ��ȡĬ�Ͽؼ�Ԫ��
	void	SAKURADIALOG_CALLMETHOD RemoveAllDefaultElements();												// CSakuraDialog �����Ƴ�����Ĭ��Ԫ��

	void	SAKURADIALOG_CALLMETHOD	RemoveControl(int nID);													// CSakuraDialog �����Ƴ��ؼ�
	void	SAKURADIALOG_CALLMETHOD RemoveAllControls();													// CSakuraDialog �����Ƴ��ؼ�(ALL)

	void	SAKURADIALOG_CALLMETHOD	SetCallback(LPCALLBACKSAKURAGUIEVENT pCallback, void* pUserContext = NULL);						// CSakuraDialog �����¼��ص�����
	void	SAKURADIALOG_CALLMETHOD	EnableNonUserEvents(bool bEnable);																// CSakuraDialog ʹ�����û��¼�
	void    SAKURADIALOG_CALLMETHOD	EnableKeyboardInput(bool bEnable);																// CSakuraDialog ʹ�ܼ�������
	void    SAKURADIALOG_CALLMETHOD	EnableMouseInput(bool bEnable);																	// CSakuraDialog ʹ���������
	bool    SAKURADIALOG_CALLMETHOD	IsKeyboardInputEnabled() const;																	// CSakuraDialog �жϼ����Ƿ�ʹ��

	void	SAKURADIALOG_CALLMETHOD SendEvent(UINT nEvent, bool bTriggeredByUser, CSakuraControl* pControl);// CSakuraDialog �����¼�
	void	SAKURADIALOG_CALLMETHOD RequestFocus(CSakuraControl* pControl);									// CSakuraDialog ���󽹵�

	bool	SAKURADIALOG_CALLMETHOD	GetVisible();															// CSakuraDialog ��ȡ�ɼ�����
	void	SAKURADIALOG_CALLMETHOD	SetVisible(bool bVisible);												// CSakuraDialog ���ÿɼ�����
	void	SAKURADIALOG_CALLMETHOD SetBackgroundColors(D3DCOLOR colorAllCorners);							// CCerasusDialog ���ñ�����ɫ
	void	SAKURADIALOG_CALLMETHOD SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight);	// CCerasusDialog ���ñ�����ɫ
	void	SAKURADIALOG_CALLMETHOD	GetLocation(POINT& Pt) const;											// CSakuraDialog ��ȡ����λ��
	void	SAKURADIALOG_CALLMETHOD	SetLocation(int x, int y);												// CSakuraDialog ���ô���λ��
	void	SAKURADIALOG_CALLMETHOD	SetSize(int width, int height);											// CSakuraDialog ���ô��ڴ�С
	int		SAKURADIALOG_CALLMETHOD	GetWidth();																// CSakuraDialog ��ȡ���ڿ��
	int		SAKURADIALOG_CALLMETHOD	GetHeight();															// CSakuraDialog ��ȡ���ڸ߶�

	int		SAKURADIALOG_CALLMETHOD	SetFontRes(CUFont* pFont);												// CSakuraDialog �������������Դ
	int		SAKURADIALOG_CALLMETHOD	SetTextrueRes(CUUint* pTexture);										// CSakuraDialog �������������Դ
	int		SAKURADIALOG_CALLMETHOD	SetTextrueExRes(CUUintEx* pTexture);									// CSakuraDialog �������������Դ(Ex)

	CUFont*	SAKURADIALOG_CALLMETHOD	GetFontRes(UINT Index);													// CSakuraDialog ���ڻ�ȡ������Դ
	CUUint*	SAKURADIALOG_CALLMETHOD	GetTextureRes(UINT Index);												// CSakuraDialog ���ڻ�ȡ������Դ
	CUUintEx*	SAKURADIALOG_CALLMETHOD	GetTextureExRes(UINT Index);										// CSakuraDialog ���ڻ�ȡ������Դ(Ex)

	CSakuraResourceManager* SAKURADIALOG_CALLMETHOD	GetManager();											// CSakuraDialog ���ڻ�ȡ��Դ������

	static void	SAKURADIALOG_CALLMETHOD	ClearFocus();														// CSakuraDialog ����ؼ�����

	HRESULT	SAKURADIALOG_CALLMETHOD	OnRender();																// CSakuraDialog ������Ⱦ

};


#endif // !__SAKURADIALOG_H_

