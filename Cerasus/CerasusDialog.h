/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusDialog.h
* @brief	This File is CerasusDialog DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-24	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSDIALOG_H_
#define __CERASUSDIALOG_H_

//Include Direct Common Header File
#include "CerasusUICommon.h"
#include "CerasusResourceManager.h"
#include "CerasusControl.h"
#include "CerasusStatic.h"
#include "CerasusButton.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSDIALOG_API	__declspec(dllexport)
#else
#define CERASUSDIALOG_API	__declspec(dllimport)
#endif

#define CERASUSDIALOG_CALLMETHOD	__stdcall

//Function Declaration
typedef VOID(CALLBACK*LPCALLBACKCERASUSGUIEVENT)(UINT nEvent, int nControlID, CCerasusControl* pControl, void* pUserContext);

//Class Definition
class CCerasusDialog
{
	friend class CCerasusResourceManager;

private:
	int	m_nX;					// CCerasusDialog ����X������
	int m_nY;					// CCerasusDialog ����Y������
	int m_nWidth;				// CCerasusDialog ���ڿ��
	int m_nHeight;				// CCerasusDialog ���ڸ߶�
	int m_nCaptionHeight;		// CCerasusDialog ���ڱ���߶�

	bool	m_bVisible;			// CCerasusDialog ���ڿɼ�
	bool	m_bCaption;			// CCerasusDialog ���ڱ������϶�
	bool	m_bMinimized;		// CCerasusDialog ������С��
	bool	m_bDrag;			// CCerasusDialog ������ק

	WCHAR	m_wszCaption[256];	// CCerasusDialog ���ڱ�������

	D3DCOLOR	m_colorTopLeft;			// CCerasusDialog �������ϽǶ�����ɫ
	D3DCOLOR	m_colorTopRight;		// CCerasusDialog �������ϽǶ�����ɫ
	D3DCOLOR	m_colorBottomLeft;		// CCerasusDialog �������½Ƕ�����ɫ
	D3DCOLOR	m_colorBottomRight;		// CCerasusDialog �������½Ƕ�����ɫ

	int m_nDefaultControlID;			// CCerasusDialog ����Ĭ�Ͽؼ�ID

	static double s_fTimeRefresh;		// CCerasusDialog ����ˢ��ʱ��
	double m_fTimeLastRefresh;			// CCerasusDialog �����ϴ�ˢ��ʱ��

	static CCerasusControl* s_pControlFocus;		// CCerasusDialog ��ý���ؼ�
	static CCerasusControl* s_pControlPressed;      // CCerasusDialog ��ǰ���¿ؼ�

	CCerasusControl* m_pControlMouseOver;           // CCerasusDialog ��ǰ��ͣ�ؼ�

private:
	CCerasusResourceManager* m_pManager;			// CCerasusDialog ������Դ������
	LPCALLBACKCERASUSGUIEVENT m_pCallbackEvent;		// CCerasusDialog �����¼��ص�����
	void* m_pCallbackEventUserContext;				// CCerasusDialog �����¼��ص��û�����

	vector<int> m_vecTextures;			// CCerasusDialog ��������
	vector<int> m_vecFonts;				// CCerasusDialog ��������

	vector<CCerasusControl*> m_vecControls;			// CCerasusDialog ���ڿؼ�����
	vector<CerasusElementHolder*> m_vecDefaultElements;	// CCerasusDialog ����Ĭ��Ԫ��

	CCerasusElement m_CapElement;		// CCerasusDialog ����Ԫ��

	CCerasusDialog* m_pNextDialog;		// CCerasusDialog ��һ������ָ��
	CCerasusDialog* m_pPrevDialog;		// CCerasusDialog ��һ������ָ��

public:
	bool m_bNonUserEvents;				// CCerasusDialog �û��¼���־
	bool m_bKeyboardInput;				// CCerasusDialog ���������־
	bool m_bMouseInput;					// CCerasusDialog ��������־

public:
	CCerasusDialog();					// CCerasusDialog ���캯��
	~CCerasusDialog();					// CCerasusDialog ��������

	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog = true);							// CCerasusDialog ��ʼ������
	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog, CUUint sUnit);					// CCerasusDialog ��ʼ������(�ļ�����)
	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog, CUUintEx sUnit);					// CCerasusDialog ��ʼ������(�ڴ����)

	bool	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);									// CCerasusDialog ������Ϣ����

	HRESULT AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, CCerasusStatic** ppCreated = NULL);						// CCerasusDialog ������Ӿ�̬�ؼ�
	HRESULT AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CCerasusButton** ppCreated = NULL);		// CCerasusDialog ������Ӱ�ť�ؼ�

	HRESULT	AddControl(CCerasusControl* pControl);									// CCerasusDialog ������ӿؼ�
	HRESULT	InitControl(CCerasusControl* pControl);									// CCerasusDialog ���ڳ�ʼ���ؼ�

	CCerasusStatic*	GetStatic(int ID);												// CCerasusDialog ���ڻ�ȡ��̬�ؼ�
	CCerasusButton*	GetButton(int ID);												// CCerasusDialog ���ڻ�ȡ��ť�ؼ�

	CCerasusControl*GetControl(int ID);												// CCerasusDialog ��ȡ�ؼ�ָ��
	CCerasusControl*GetControl(int ID, UINT nControlType);							// CCerasusDialog ��ȡ�ؼ�ָ��
	CCerasusControl*GetControlAtPoint(POINT pt);									// CCerasusDialog ��ȡ������ڵĿؼ�ָ��

	bool	GetControlEnabled(int ID);												// CCerasusDialog ��ȡ�ؼ�ʹ��״̬
	void	SetControlEnabled(int ID, bool bEnabled);								// CCerasusDialog ���ÿؼ�ʹ��״̬
	
	void	ClearRadioButtonGroup(UINT nGroup);										// CCerasusDialog ���RadioButton��
	void	ClearComboBox(int ID);													// CCerasusDialog ���ComboBox

	HRESULT			SetDefaultElement(UINT nControlType, UINT iElement, CCerasusElement* pElement);			// CCerasusDialog ����Ĭ��Ԫ��
	CCerasusElement*GetDefaultElement(UINT nControlType, UINT iElement);									// CCerasusDialog ��ȡĬ��Ԫ��

	void			SendEvent(UINT nEvent, bool bTriggeredByUser, CCerasusControl* pControl);											// CCerasusDialog �����¼�
	void			RequestFocus(CCerasusControl* pControl);																			// CCerasusDialog ���󽹵�

	// Render ����
	HRESULT			DrawRect(RECT* pRect, D3DCOLOR color);																				// CCerasusDialog ���ƾ���
	HRESULT			DrawRect9(RECT* pRect, D3DCOLOR color);																				// CCerasusDialog ���ƾ���
	HRESULT			DrawText(LPCWSTR strText, CCerasusElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1);			// CCerasusDialog �����ı�
	HRESULT			DrawText9(LPCWSTR strText, CCerasusElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1);		// CCerasusDialog �����ı�

	// Attributes ����
	bool			GetVisible();													// CCerasusDialog ��ȡ�ɼ�����
	void			SetVisible(bool bVisible);										// CCerasusDialog ���ÿɼ�����
	bool			GetMinimized();													// CCerasusDialog ��ȡ��С������
	void			SetMinimized(bool bMinimized);									// CCerasusDialog ������С������
	void			SetBackgroundColors(D3DCOLOR colorAllCorners);					// CCerasusDialog ���ñ�����ɫ
	void			SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight);	// CCerasusDialog ���ñ�����ɫ
	void			EnableCaption(bool bEnable);									// CCerasusDialog ���ñ�����ʹ��
	int				GetCaptionHeight() const;										// CCerasusDialog ��ȡ�������߶�
	void            SetCaptionHeight(int nHeight);									// CCerasusDialog ���ñ������߶�
	void			SetCaptionText(const WCHAR* pwszText);							// CCerasusDialog ���ñ������ı�
	void			GetLocation(POINT& Pt) const;									// CCerasusDialog ��ȡ����λ��
	void			SetLocation(int x, int y);										// CCerasusDialog ���ô���λ��
	void			SetSize(int width, int height);									// CCerasusDialog ���ô��ڴ�С
	int				GetWidth();														// CCerasusDialog ��ȡ���ڿ��
	int				GetHeight();													// CCerasusDialog ��ȡ���ڸ߶�

	static void WINAPI  SetRefreshTime(float fTime);								// CCerasusDialog ����ˢ��ʱ��

	static CCerasusControl* WINAPI GetNextControl(CCerasusControl* pControl);		// CCerasusDialog ��ȡ������һ���ؼ�ָ��
	static CCerasusControl* WINAPI GetPrevControl(CCerasusControl* pControl);		// CCerasusDialog ��ȡ������һ���ؼ�ָ��

	void	RemoveControl(int ID);		// CCerasusDialog �Ƴ��ؼ�
	void	RemoveAllControls();		// CCerasusDialog �Ƴ����пؼ�

	void	SetCallback(LPCALLBACKCERASUSGUIEVENT pCallback, void* pUserContext = NULL);					// CCerasusDialog �����¼��ص�����
	void	EnableNonUserEvents(bool bEnable);																// CCerasusDialog ʹ�����û��¼�
	void    EnableKeyboardInput(bool bEnable);																// CCerasusDialog ʹ�ܼ�������
	void    EnableMouseInput(bool bEnable);																	// CCerasusDialog ʹ���������
	bool    IsKeyboardInputEnabled() const;																	// CCerasusDialog �жϼ����Ƿ�ʹ��

	void	Refresh();																// CCerasusDialog ����ˢ��

	static void WINAPI	ClearFocus();												// CCerasusDialog ����ؼ�����
	void                FocusDefaultControl();										// CCerasusDialog Ĭ�Ͽؼ�����

	HRESULT			SetFont(UINT Index, LPWSTR strFontName, int nFontSize);			// CCerasusDialog ��������Ԫ��
	DirectFont*		GetFont(UINT Index);											// CCerasusDialog ��ȡ����Ԫ��

	HRESULT			SetTexture(UINT Index, CUUint sUnit);							// CCerasusDialog ��������Ԫ��(�ļ�)
	HRESULT			SetTexture(UINT Index, CUUintEx sUnit);							// CCerasusDialog ��������Ԫ��(�ڴ�)
	CCerasusUnit*	GetTexture(UINT Index);											// CCerasusDialog ��ȡ����Ԫ��

private:
	void	InitDefaultElements();		// CCerasusDialog ��ʼ��Ĭ��Ԫ��

	void	OnMouseMove(POINT pt);		// CCerasusDialog ����ƶ�
	bool    OnCycleFocus(bool bForward);// CCerasusDialog ѭ������

};


#endif // !__CERASUSDIALOG_H_

