/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraComboBox.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-14	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURACOMBOBOX_H_
#define __SAKURACOMBOBOX_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraButton.h"
#include "SakuraScrollBar.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURACOMBOBOX_API	__declspec(dllexport)
#else
#define SAKURACOMBOBOX_API	__declspec(dllimport)
#endif

#define	SAKURACOMBOBOX_CALLMETHOD	__stdcall

// Struct Definition
struct S_SakuraComboBoxItem
{
	WCHAR strText[256];
	void* pData;

	RECT rcActive;
	bool bVisible;
};

// Class Definition
class SAKURACOMBOBOX_API CSakuraComboBox : public CSakuraButton
{
protected:
	int m_iSelected;			// CSakuraComboBox Combo选中项序号
	int m_iFocused;				// CSakuraComboBox Combo焦点项序号
	int m_nDropHeight;			// CSakuraComboBox 每项高度
	int m_nSBWidth;				// CSakuraComboBox ScrollBar宽度

	bool m_bOpened;				// CSakuraComboBox 是否点击下拉框

	RECT m_rcText;				// CSakuraComboBox 文本区域
	RECT m_rcButton;			// CSakuraComboBox 按钮区域
	RECT m_rcDropdown;			// CSakuraComboBox 下拉框区域
	RECT m_rcDropdownText;		// CSakuraComboBox 下拉框文字区域

	CSakuraScrollBar m_ScrollBar;					// CSakuraComboBox 滚动条
	vector<S_SakuraComboBoxItem*>	m_Items;		// CSakuraComboBox 列表数据

public:
			CSakuraComboBox(CSakuraDialog* pDialog = NULL);			// CSakuraComboBox 构造函数
	virtual	~CSakuraComboBox();										// CSakuraComboBox 析构函数

	virtual	HRESULT	SAKURACOMBOBOX_CALLMETHOD	OnInit();			// CSakuraComboBox 初始化控件

	virtual bool	SAKURACOMBOBOX_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraComboBox 键盘消息响应
	virtual bool    SAKURACOMBOBOX_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraComboBox 鼠标消息响应
	virtual void    SAKURACOMBOBOX_CALLMETHOD	OnHotkey();			// CSakuraComboBox 鼠标热键响应

	virtual bool    SAKURACOMBOBOX_CALLMETHOD	CanHaveFocus();		// CSakuraComboBox 是否获取焦点
	virtual void    SAKURACOMBOBOX_CALLMETHOD	OnFocusOut();		// CSakuraComboBox 焦点丢失
	virtual void    SAKURACOMBOBOX_CALLMETHOD	Render();			// CSakuraComboBox 渲染控件

	virtual void    SAKURACOMBOBOX_CALLMETHOD	UpdateRects();		// CSakuraComboBox 更新控件区域

	HRESULT         SAKURACOMBOBOX_CALLMETHOD	AddItem(const WCHAR* strText, void* pData);			// CSakuraComboBox 添加项
	void            SAKURACOMBOBOX_CALLMETHOD	RemoveAllItems();									// CSakuraComboBox 移除全部项
	void            SAKURACOMBOBOX_CALLMETHOD	RemoveItem(UINT Index);								// CSakuraComboBox 移除项
	bool            SAKURACOMBOBOX_CALLMETHOD	ContainsItem(const WCHAR* strText, UINT iStart = 0);// CSakuraComboBox 包含项
	int             SAKURACOMBOBOX_CALLMETHOD	FindItem(const WCHAR* strText, UINT iStart = 0);	// CSakuraComboBox 查找项
	void*			SAKURACOMBOBOX_CALLMETHOD	GetItemData(const WCHAR* strText);					// CSakuraComboBox 获取项数据
	void*			SAKURACOMBOBOX_CALLMETHOD	GetItemData(int nIndex);							// CSakuraComboBox 获取项数据(重载+1)
	void            SAKURACOMBOBOX_CALLMETHOD	SetDropHeight(UINT nHeight);						// CSakuraComboBox 设置项高度
	int             SAKURACOMBOBOX_CALLMETHOD	GetScrollBarWidth() const;							// CSakuraComboBox 获取滚动条宽度
	void            SAKURACOMBOBOX_CALLMETHOD	SetScrollBarWidth(int nWidth);						// CSakuraComboBox 设置滚动条宽度
	int             SAKURACOMBOBOX_CALLMETHOD	GetSelectedIndex() const;							// CSakuraComboBox 获取选中序号
	void*			SAKURACOMBOBOX_CALLMETHOD	GetSelectedData();									// CSakuraComboBox 获取选中数据
	S_SakuraComboBoxItem*	SAKURACOMBOBOX_CALLMETHOD	GetSelectedItem();							// CSakuraComboBox 获取选中项

	UINT            SAKURACOMBOBOX_CALLMETHOD	GetNumItems();										// CSakuraComboBox 获取项目数量
	S_SakuraComboBoxItem*	SAKURACOMBOBOX_CALLMETHOD	GetItem(UINT Index);						// CSakuraComboBox 获取项目

	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByIndex(UINT Index);						// CSakuraComboBox 设置选中项(索引)
	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByText(const WCHAR* strText);			// CSakuraComboBox 设置选中项(文本)
	HRESULT         SAKURACOMBOBOX_CALLMETHOD	SetSelectedByData(void* pData);						// CSakuraComboBox 设置选中项(数据)

};

#endif // !__SAKURACOMBOBOX_H_

