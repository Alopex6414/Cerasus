/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraComboBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-11-14	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURACOMBOBOX_H_
#define __SAKURACOMBOBOX_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraButton.h"
#include "SakuraScrollBar.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACOMBOBOX_API	__declspec(dllexport)
#else
#define SAKURACOMBOBOX_API	__declspec(dllimport)
#endif

#define	SAKURACOMBOBOX_CALLMETHOD	__stdcall

//Struct Definition
struct S_SakuraComboBoxItem
{
	WCHAR strText[256];
	void* pData;

	RECT rcActive;
	bool bVisible;
};

//Class Definition
class SAKURACOMBOBOX_API CSakuraComboBox : public CSakuraButton
{
protected:
	int m_iSelected;			// CSakuraComboBox Comboѡ�������
	int m_iFocused;				// CSakuraComboBox Combo���������
	int m_nDropHeight;			// CSakuraComboBox ÿ��߶�
	int m_nSBWidth;				// CSakuraComboBox ScrollBar���

	bool m_bOpened;				// CSakuraComboBox �Ƿ���������

	RECT m_rcText;				// CSakuraComboBox �ı�����
	RECT m_rcButton;			// CSakuraComboBox ��ť����
	RECT m_rcDropdown;			// CSakuraComboBox ����������
	RECT m_rcDropdownText;		// CSakuraComboBox ��������������

	CSakuraScrollBar m_ScrollBar;					// CSakuraComboBox ������
	vector<S_SakuraComboBoxItem*>	m_Items;		// CSakuraComboBox �б�����

public:
			CSakuraComboBox(CSakuraDialog* pDialog = NULL);			// CSakuraComboBox ���캯��
	virtual	~CSakuraComboBox();										// CSakuraComboBox ��������

	virtual	HRESULT	SAKURACOMBOBOX_CALLMETHOD	OnInit();			// CSakuraComboBox ��ʼ���ؼ�

	virtual bool	SAKURACOMBOBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraComboBox ������Ϣ��Ӧ
	virtual bool    SAKURACOMBOBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraComboBox �����Ϣ��Ӧ
	virtual void    SAKURACOMBOBOX_CALLMETHOD	OnHotkey();			// CSakuraComboBox ����ȼ���Ӧ

	virtual bool    SAKURACOMBOBOX_CALLMETHOD	CanHaveFocus();		// CSakuraComboBox �Ƿ��ȡ����
	virtual void    SAKURACOMBOBOX_CALLMETHOD	OnFocusOut();		// CSakuraComboBox ���㶪ʧ
	virtual void    SAKURACOMBOBOX_CALLMETHOD	Render();			// CSakuraComboBox ��Ⱦ�ؼ�

	virtual void    SAKURACOMBOBOX_CALLMETHOD	UpdateRects();		// CSakuraComboBox ���¿ؼ�����

	HRESULT         SAKURACOMBOBOX_CALLMETHOD	AddItem(const WCHAR* strText, void* pData);			// CSakuraComboBox �����
	void            SAKURACOMBOBOX_CALLMETHOD	RemoveAllItems();									// CSakuraComboBox �Ƴ�ȫ����
	void            SAKURACOMBOBOX_CALLMETHOD	RemoveItem(UINT Index);								// CSakuraComboBox �Ƴ���
	bool            SAKURACOMBOBOX_CALLMETHOD	ContainsItem(const WCHAR* strText, UINT iStart = 0);// CSakuraComboBox ������
	int             SAKURACOMBOBOX_CALLMETHOD	FindItem(const WCHAR* strText, UINT iStart = 0);	// CSakuraComboBox ������
	void*			SAKURACOMBOBOX_CALLMETHOD	GetItemData(const WCHAR* strText);					// CSakuraComboBox ��ȡ������
	void*			SAKURACOMBOBOX_CALLMETHOD	GetItemData(int nIndex);							// CSakuraComboBox ��ȡ������(����+1)
	void            SAKURACOMBOBOX_CALLMETHOD	SetDropHeight(UINT nHeight);						// CSakuraComboBox ������߶�
	int             SAKURACOMBOBOX_CALLMETHOD	GetScrollBarWidth() const;							// CSakuraComboBox ��ȡ���������
	void            SAKURACOMBOBOX_CALLMETHOD	SetScrollBarWidth(int nWidth);						// CSakuraComboBox ���ù��������
	int             SAKURACOMBOBOX_CALLMETHOD	GetSelectedIndex() const;							// CSakuraComboBox ��ȡѡ�����
	void*			SAKURACOMBOBOX_CALLMETHOD	GetSelectedData();									// CSakuraComboBox ��ȡѡ������
	S_SakuraComboBoxItem*	SAKURACOMBOBOX_CALLMETHOD	GetSelectedItem();							// CSakuraComboBox ��ȡѡ����

	UINT            SAKURACOMBOBOX_CALLMETHOD	GetNumItems();										// CSakuraComboBox ��ȡ��Ŀ����
	S_SakuraComboBoxItem*	SAKURACOMBOBOX_CALLMETHOD	GetItem(UINT Index);						// CSakuraComboBox ��ȡ��Ŀ

	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByIndex(UINT Index);						// CSakuraComboBox ����ѡ����(����)
	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByText(const WCHAR* strText);			// CSakuraComboBox ����ѡ����(�ı�)
	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByData(void* pData);						// CSakuraComboBox ����ѡ����(����)

};

#endif // !__SAKURACOMBOBOX_H_

