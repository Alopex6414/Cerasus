/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraListBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-12-04	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURALISTBOX_H_
#define __SAKURALISTBOX_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"
#include "SakuraScrollBar.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURALISTBOX_API	__declspec(dllexport)
#else
#define SAKURALISTBOX_API	__declspec(dllimport)
#endif

#define	SAKURALISTBOX_CALLMETHOD	__stdcall

//Struct Definition
typedef struct
{
	WCHAR strText[256];
	void* pData;
	RECT rcActive;
	bool bSelected;
} CSakuraListBoxItem, *LPCSakuraListBoxItem;

//Class Definition
class SAKURALISTBOX_API CSakuraListBox : public CSakuraControl
{
protected:
	RECT m_rcText;							// CSakuraListBox �ı���
	RECT m_rcSelection;						// CSakuraListBox �ı�ѡ���
	CSakuraScrollBar m_ScrollBar;			// CSakuraListBox ������

	int m_nSBWidth;							// CSakuraListBox ���������
	int m_nBorder;							// CSakuraListBox �߿���
	int m_nMargin;
	int m_nTextHeight;						// CSakuraListBox �ı����
	DWORD m_dwStyle;						// CSakuraListBox �б����ʽ
	int m_nSelected;						// CSakuraListBox �б��ѡ����
	int m_nSelStart;						// CSakuraListBox �б��ʼ��
	bool m_bDrag;							// CSakuraListBox �б����ק

	vector<CSakuraListBoxItem*> m_Items;	// CSakuraListBox �б������

public:
	enum STYLE								// CSakuraListBox �б����ʽ
	{
		MULTISELECTION = 1
	};
	
public:
			CSakuraListBox(CSakuraDialog* pDialog = NULL);			// CSakuraListBox ���캯��
	virtual	~CSakuraListBox();										// CSakuraListBox ��������

	virtual	HRESULT	SAKURALISTBOX_CALLMETHOD	OnInit();			// CSakuraListBox ��ʼ���ؼ�
	virtual bool    SAKURALISTBOX_CALLMETHOD	CanHaveFocus();		// CSakuraListBox �Ƿ�ӵ�н���

	virtual bool    SAKURALISTBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraListBox ������Ϣ��Ӧ
	virtual bool    SAKURALISTBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraListBox �����Ϣ��Ӧ
	virtual bool    SAKURALISTBOX_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraListBox ��Ϣ������

	virtual void    SAKURALISTBOX_CALLMETHOD	Render();							// CSakuraListBox ��Ⱦ�ؼ�
	virtual void    SAKURALISTBOX_CALLMETHOD	UpdateRects();						// CSakuraListBox ���¿ؼ�����

	DWORD           SAKURALISTBOX_CALLMETHOD	GetStyle() const;					// CSakuraListBox ��ȡ��ʽ
	int             SAKURALISTBOX_CALLMETHOD	GetSize() const;					// CSakuraListBox ��ȡ����
	void            SAKURALISTBOX_CALLMETHOD	SetStyle(DWORD dwStyle);			// CSakuraListBox ������ʽ
	int             SAKURALISTBOX_CALLMETHOD	GetScrollBarWidth() const;			// CSakuraListBox ��ȡ���������
	void            SAKURALISTBOX_CALLMETHOD	SetScrollBarWidth(int nWidth);		// CSakuraListBox ���ù��������
	void            SAKURALISTBOX_CALLMETHOD	SetBorder(int nBorder, int nMargin);// CSakuraListBox ���ñ߿���

	HRESULT         SAKURALISTBOX_CALLMETHOD	AddItem(const WCHAR* wszText, void* pData);							// CSakuraListBox �����
	HRESULT         SAKURALISTBOX_CALLMETHOD	InsertItem(int nIndex, const WCHAR* wszText, void* pData);			// CSakuraListBox ������
	void            SAKURALISTBOX_CALLMETHOD	RemoveItem(int nIndex);												// CSakuraListBox �Ƴ���
	void            SAKURALISTBOX_CALLMETHOD	RemoveItemByData(void* pData);										// CSakuraListBox �Ƴ���(ֵ����)
	void            SAKURALISTBOX_CALLMETHOD	RemoveAllItems();													// CSakuraListBox �Ƴ�������

	CSakuraListBoxItem*	SAKURALISTBOX_CALLMETHOD	GetItem(int nIndex);											// CSakuraListBox ��ȡֵ
	int             SAKURALISTBOX_CALLMETHOD		GetSelectedIndex(int nPreviousSelected = -1);					// CSakuraListBox ��ȡѡ������
	CSakuraListBoxItem* SAKURALISTBOX_CALLMETHOD	GetSelectedItem(int nPreviousSelected = -1);					// CSakuraListBox ��ȡѡ����
	void            SAKURALISTBOX_CALLMETHOD		SelectItem(int nNewIndex);										// CSakuraListBox ѡ����

};

#endif // !__SAKURALISTBOX_H_
