/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraDialog.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURADIALOG_H_
#define __SAKURADIALOG_H_

// Include SakuraGUI Common Header File
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

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURADIALOG_API	__declspec(dllexport)
#else
#define SAKURADIALOG_API	__declspec(dllimport)
#endif

#define	SAKURADIALOG_CALLMETHOD	__stdcall

// Class Definition
class SAKURADIALOG_API CSakuraDialog
{
	friend class CSakuraDialog;

private:
	int	m_nX;					// CSakuraDialog 窗口X轴坐标
	int m_nY;					// CSakuraDialog 窗口Y轴坐标
	int m_nWidth;				// CSakuraDialog 窗口宽度
	int m_nHeight;				// CSakuraDialog 窗口高度

	bool	m_bVisible;			// CSakuraDialog 窗口可见

	D3DCOLOR	m_colorTopLeft;							// CSakuraDialog 窗口左上角顶点颜色
	D3DCOLOR	m_colorTopRight;						// CSakuraDialog 窗口右上角顶点颜色
	D3DCOLOR	m_colorBottomLeft;						// CSakuraDialog 窗口左下角顶点颜色
	D3DCOLOR	m_colorBottomRight;						// CSakuraDialog 窗口右下角顶点颜色

	CSakuraControl*	m_pControlMouseOver;				// CSakuraDialog 鼠标在控件上

	static CSakuraControl*	s_pControlFocus;			// CSakuraDialog 获得焦点控件
	static CSakuraControl*	s_pControlPressed;			// CSakuraDialog 当前按下控件

private:
	CSakuraResourceManager*		m_pManager;							// CSakuraDialog 窗口资源类
	LPCALLBACKSAKURAGUIEVENT	m_pCallbackEvent;					// CSakuraDialog 窗口事件回调函数
	void*						m_pCallbackEventUserContext;		// CSakuraDialog 窗口事件回调用户参数

	vector<CSakuraControl*>		m_vecControls;						// CSakuraDialog 窗口添加的控件数组
	vector<CSakuraElementHolder*>	m_vecDefaultControls;			// CSakuraDialog 窗口默认控件元素数组

protected:
	CCerasusUnit*	m_pDialogGraphics;					// CSakuraDialog 窗口绘制背景

public:
	bool	m_bNonUserEvents;							// CSakuraDialog 用户事件标志
	bool	m_bKeyboardInput;							// CSakuraDialog 键盘输入标志
	bool	m_bMouseInput;								// CSakuraDialog 鼠标输入标志

protected:
	void	SAKURADIALOG_CALLMETHOD	OnMouseMove(POINT pt);													// CSakuraDialog 鼠标移动
	void	SAKURADIALOG_CALLMETHOD	InitDefaultElement();													// CSakuraDialog 窗口控件默认资源初始化
	void	SAKURADIALOG_CALLMETHOD AlterDefaultElement(CSakuraControl* pControl);							// CSakuraDialog 窗口控件默认资源修改

public:
	CSakuraDialog();
	~CSakuraDialog();

	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager);								// CSakuraDialog 窗口初始化响应
	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager, S_CS_UNIT_PARA sUnit);		// CSakuraDialog 窗口初始化响应
	void	SAKURADIALOG_CALLMETHOD	OnCreate(CSakuraResourceManager* pManager, S_CS_UNIT_EX_PARA sUnit);	// CSakuraDialog 窗口初始化响应

	void	SAKURADIALOG_CALLMETHOD	OnLost();																// CSakuraDialog 窗口丢失设备
	void	SAKURADIALOG_CALLMETHOD	OnReset();																// CSakuraDialog 窗口重置设备
	
	bool	SAKURADIALOG_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraDialog 窗口消息处理

	HRESULT SAKURADIALOG_CALLMETHOD	AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, CSakuraStatic** ppCreated = NULL);																				// CSakuraDialog 窗口添加静态控件
	HRESULT SAKURADIALOG_CALLMETHOD	AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraButton** ppCreated = NULL);															// CSakuraDialog 窗口添加按钮控件
	HRESULT SAKURADIALOG_CALLMETHOD AddCheckBox(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, CSakuraCheckBox** ppCreated = NULL);								// CSakuraDialog 窗口添加复选框控件
	HRESULT	SAKURADIALOG_CALLMETHOD AddRadioButton(int ID, UINT nButtonGroup, LPCWSTR strText, int x, int y, int width, int height, bool bChecked = false, UINT nHotkey = 0, bool bIsDefault = false, CSakuraRadioButton** ppCreated = NULL);		// CSakuraDialog 窗口添加单选框控件
	HRESULT	SAKURADIALOG_CALLMETHOD	AddComboBox(int ID, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraComboBox** ppCreated = NULL);																		// CSakuraDialog 窗口添加下拉选择框控件
	HRESULT	SAKURADIALOG_CALLMETHOD	AddSlider(int ID, int x, int y, int width, int height, int min = 0, int max = 100, int value = 50, bool bIsDefault = false, CSakuraSlider** ppCreated = NULL);													// CSakuraDialog 窗口添加滑块控件
	HRESULT SAKURADIALOG_CALLMETHOD AddUnit(int ID, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CSakuraUnit** ppCreated = NULL);

	HRESULT	SAKURADIALOG_CALLMETHOD	AddControl(CSakuraControl* pControl);									// CSakuraDialog 窗口添加控件
	HRESULT	SAKURADIALOG_CALLMETHOD	InitControl(CSakuraControl* pControl);									// CSakuraDialog 窗口初始化控件

	HRESULT	SAKURADIALOG_CALLMETHOD	AddFont(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);			// CSakuraDialog 窗口添加控件字体
	HRESULT	SAKURADIALOG_CALLMETHOD AddTexture(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);		// CSakuraDialog 窗口添加控件纹理
	HRESULT	SAKURADIALOG_CALLMETHOD AddTextureEx(int ID, UINT nControlType, UINT iElement, SAKURA_CONTROL_STATE eType, UINT Index);		// CSakuraDialog 窗口添加控件纹理Ex

	CCerasusUnit*		SAKURADIALOG_CALLMETHOD GetDialogGraphics();										// CSakuraDialog 窗口获取背景图形
	vector<CSakuraControl*>&	SAKURADIALOG_CALLMETHOD GetControls();										// CSakuraDialog 窗口获取控件向量

	CSakuraStatic*		SAKURADIALOG_CALLMETHOD GetStatic(int ID);											// CSakuraDialog 窗口获取静态控件
	CSakuraButton*		SAKURADIALOG_CALLMETHOD GetButton(int ID);											// CSakuraDialog 窗口获取按钮控件
	CSakuraCheckBox*	SAKURADIALOG_CALLMETHOD	GetCheckBox(int ID);										// CSakuraDialog 窗口获取复选框控件
	CSakuraRadioButton*	SAKURADIALOG_CALLMETHOD	GetRadioButton(int ID);										// CSakuraDialog 窗口获取单选框控件
	CSakuraComboBox*	SAKURADIALOG_CALLMETHOD	GetComboBox(int ID);										// CSakuraDialog 窗口获取下拉框控件
	CSakuraSlider*		SAKURADIALOG_CALLMETHOD GetSlider(int ID);											// CSakuraDialog 窗口获取滑块控件
	CSakuraUnit*		SAKURADIALOG_CALLMETHOD GetUnit(int ID);											// CSakuraDialog 窗口获取图形控件

	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID);												// CSakuraDialog 获取控件指针
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControl(int ID, UINT nControlType);							// CSakuraDialog 获取控件指针
	CSakuraControl*	SAKURADIALOG_CALLMETHOD	GetControlAtPoint(POINT pt);									// CSakuraDialog 获取鼠标所在的控件指针

	bool	SAKURADIALOG_CALLMETHOD GetControlEnabled(int ID);												// CSakuraDialog 获取控件使能
	void	SAKURADIALOG_CALLMETHOD	SetControlEnabled(int ID, bool bEnabled);								// CSakuraDialog 设置控件使能

	void	SAKURADIALOG_CALLMETHOD	ClearRadioButtonGroup(UINT nGroup);										// CSakuraDialog 清除单选按钮的组别
	void	SAKURADIALOG_CALLMETHOD	ClearComboBox(int nID);													// CSakuraDialog 清除下拉列表

	HRESULT	SAKURADIALOG_CALLMETHOD SetDefaultElement(UINT nControlType, UINT iElement, CSakuraElement** ppElement);				// CSakuraDialog 设置默认控件元素
	CSakuraElement*	SAKURADIALOG_CALLMETHOD	GetDefaultElement(UINT nControlType, UINT iElement);									// CSakuraDialog 获取默认控件元素
	void	SAKURADIALOG_CALLMETHOD RemoveAllDefaultElements();												// CSakuraDialog 窗口移除所有默认元素

	void	SAKURADIALOG_CALLMETHOD	RemoveControl(int nID);													// CSakuraDialog 窗口移除控件
	void	SAKURADIALOG_CALLMETHOD RemoveAllControls();													// CSakuraDialog 窗口移除控件(ALL)

	void	SAKURADIALOG_CALLMETHOD	SetCallback(LPCALLBACKSAKURAGUIEVENT pCallback, void* pUserContext = NULL);						// CSakuraDialog 设置事件回调函数
	void	SAKURADIALOG_CALLMETHOD	EnableNonUserEvents(bool bEnable);																// CSakuraDialog 使能无用户事件
	void    SAKURADIALOG_CALLMETHOD	EnableKeyboardInput(bool bEnable);																// CSakuraDialog 使能键盘输入
	void    SAKURADIALOG_CALLMETHOD	EnableMouseInput(bool bEnable);																	// CSakuraDialog 使能鼠标输入
	bool    SAKURADIALOG_CALLMETHOD	IsKeyboardInputEnabled() const;																	// CSakuraDialog 判断键盘是否使能

	void	SAKURADIALOG_CALLMETHOD SendEvent(UINT nEvent, bool bTriggeredByUser, CSakuraControl* pControl);// CSakuraDialog 发送事件
	void	SAKURADIALOG_CALLMETHOD RequestFocus(CSakuraControl* pControl);									// CSakuraDialog 请求焦点

	bool	SAKURADIALOG_CALLMETHOD	GetVisible();															// CSakuraDialog 获取可见属性
	void	SAKURADIALOG_CALLMETHOD	SetVisible(bool bVisible);												// CSakuraDialog 设置可见属性
	void	SAKURADIALOG_CALLMETHOD SetBackgroundColors(D3DCOLOR colorAllCorners);							// CCerasusDialog 设置背景颜色
	void	SAKURADIALOG_CALLMETHOD SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight);	// CCerasusDialog 设置背景颜色
	void	SAKURADIALOG_CALLMETHOD	GetLocation(POINT& Pt) const;											// CSakuraDialog 获取窗口位置
	void	SAKURADIALOG_CALLMETHOD	SetLocation(int x, int y);												// CSakuraDialog 设置窗口位置
	void	SAKURADIALOG_CALLMETHOD	SetSize(int width, int height);											// CSakuraDialog 设置窗口大小
	int		SAKURADIALOG_CALLMETHOD	GetWidth();																// CSakuraDialog 获取窗口宽度
	int		SAKURADIALOG_CALLMETHOD	GetHeight();															// CSakuraDialog 获取窗口高度

	int		SAKURADIALOG_CALLMETHOD	SetFontRes(CUFont* pFont);												// CSakuraDialog 窗口添加字体资源
	int		SAKURADIALOG_CALLMETHOD	SetTextrueRes(S_CS_UNIT_PARA* pTexture);								// CSakuraDialog 窗口添加纹理资源
	int		SAKURADIALOG_CALLMETHOD	SetTextrueExRes(S_CS_UNIT_EX_PARA* pTexture);							// CSakuraDialog 窗口添加纹理资源(Ex)

	CUFont*	SAKURADIALOG_CALLMETHOD	GetFontRes(UINT Index);													// CSakuraDialog 窗口获取字体资源
	S_CS_UNIT_PARA*	SAKURADIALOG_CALLMETHOD	GetTextureRes(UINT Index);										// CSakuraDialog 窗口获取纹理资源
	S_CS_UNIT_EX_PARA*	SAKURADIALOG_CALLMETHOD	GetTextureExRes(UINT Index);								// CSakuraDialog 窗口获取纹理资源(Ex)

	CSakuraResourceManager* SAKURADIALOG_CALLMETHOD	GetManager();											// CSakuraDialog 窗口获取资源管理类

	static void	SAKURADIALOG_CALLMETHOD	ClearFocus();														// CSakuraDialog 清除控件焦点

	HRESULT	SAKURADIALOG_CALLMETHOD	OnRender();																// CSakuraDialog 窗口渲染

};


#endif // !__SAKURADIALOG_H_

