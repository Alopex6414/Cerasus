/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraListBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-12-04	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURALISTBOX_H_
#define __SAKURALISTBOX_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"
#include "SakuraScrollBar.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURALISTBOX_API	__declspec(dllexport)
#else
#define SAKURALISTBOX_API	__declspec(dllimport)
#endif

#define	SAKURALISTBOX_CALLMETHOD	__stdcall

// Struct Definition
typedef struct
{
	WCHAR strText[256];
	void* pData;
	RECT rcActive;
	bool bSelected;
} CSakuraListBoxItem, *LPCSakuraListBoxItem;

// Class Definition
class SAKURALISTBOX_API CSakuraListBox : public CSakuraControl
{
protected:
	RECT m_rcText;							// CSakuraListBox 文本框
	RECT m_rcSelection;						// CSakuraListBox 文本选择框
	CSakuraScrollBar m_ScrollBar;			// CSakuraListBox 滚动条

	int m_nSBWidth;							// CSakuraListBox 滚动条宽度
	int m_nBorder;							// CSakuraListBox 边框宽度
	int m_nMargin;
	int m_nTextHeight;						// CSakuraListBox 文本宽度
	DWORD m_dwStyle;						// CSakuraListBox 列表框样式
	int m_nSelected;						// CSakuraListBox 列表框选中项
	int m_nSelStart;						// CSakuraListBox 列表框开始项
	bool m_bDrag;							// CSakuraListBox 列表框拖拽

	vector<CSakuraListBoxItem*> m_Items;	// CSakuraListBox 列表框内容

public:
	enum STYLE								// CSakuraListBox 列表框样式
	{
		MULTISELECTION = 1
	};
	
public:
			CSakuraListBox(CSakuraDialog* pDialog = NULL);			// CSakuraListBox 构造函数
	virtual	~CSakuraListBox();										// CSakuraListBox 析构函数

	virtual	HRESULT	SAKURALISTBOX_CALLMETHOD	OnInit();			// CSakuraListBox 初始化控件
	virtual bool    SAKURALISTBOX_CALLMETHOD	CanHaveFocus();		// CSakuraListBox 是否拥有焦点

	virtual bool    SAKURALISTBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraListBox 键盘消息响应
	virtual bool    SAKURALISTBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraListBox 鼠标消息响应
	virtual bool    SAKURALISTBOX_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraListBox 消息处理函数

	virtual void    SAKURALISTBOX_CALLMETHOD	Render();							// CSakuraListBox 渲染控件
	virtual void    SAKURALISTBOX_CALLMETHOD	UpdateRects();						// CSakuraListBox 更新控件区域

	DWORD           SAKURALISTBOX_CALLMETHOD	GetStyle() const;					// CSakuraListBox 获取样式
	int             SAKURALISTBOX_CALLMETHOD	GetSize() const;					// CSakuraListBox 获取长度
	void            SAKURALISTBOX_CALLMETHOD	SetStyle(DWORD dwStyle);			// CSakuraListBox 设置样式
	int             SAKURALISTBOX_CALLMETHOD	GetScrollBarWidth() const;			// CSakuraListBox 获取滚动条宽度
	void            SAKURALISTBOX_CALLMETHOD	SetScrollBarWidth(int nWidth);		// CSakuraListBox 设置滚动条宽度
	void            SAKURALISTBOX_CALLMETHOD	SetBorder(int nBorder, int nMargin);// CSakuraListBox 设置边框宽度

	HRESULT         SAKURALISTBOX_CALLMETHOD	AddItem(const WCHAR* wszText, void* pData);							// CSakuraListBox 添加项
	HRESULT         SAKURALISTBOX_CALLMETHOD	InsertItem(int nIndex, const WCHAR* wszText, void* pData);			// CSakuraListBox 插入项
	void            SAKURALISTBOX_CALLMETHOD	RemoveItem(int nIndex);												// CSakuraListBox 移除项
	void            SAKURALISTBOX_CALLMETHOD	RemoveItemByData(void* pData);										// CSakuraListBox 移除项(值索引)
	void            SAKURALISTBOX_CALLMETHOD	RemoveAllItems();													// CSakuraListBox 移除所有项

	CSakuraListBoxItem*	SAKURALISTBOX_CALLMETHOD	GetItem(int nIndex);											// CSakuraListBox 获取值
	int             SAKURALISTBOX_CALLMETHOD		GetSelectedIndex(int nPreviousSelected = -1);					// CSakuraListBox 获取选中索引
	CSakuraListBoxItem* SAKURALISTBOX_CALLMETHOD	GetSelectedItem(int nPreviousSelected = -1);					// CSakuraListBox 获取选中项
	void            SAKURALISTBOX_CALLMETHOD		SelectItem(int nNewIndex);										// CSakuraListBox 选中项

};

#endif // !__SAKURALISTBOX_H_
