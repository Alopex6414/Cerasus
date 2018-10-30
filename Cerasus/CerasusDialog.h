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
	int	m_nX;					// CCerasusDialog 窗口X轴坐标
	int m_nY;					// CCerasusDialog 窗口Y轴坐标
	int m_nWidth;				// CCerasusDialog 窗口宽度
	int m_nHeight;				// CCerasusDialog 窗口高度
	int m_nCaptionHeight;		// CCerasusDialog 窗口标题高度

	bool	m_bVisible;			// CCerasusDialog 窗口可见
	bool	m_bCaption;			// CCerasusDialog 窗口标题栏拖动
	bool	m_bMinimized;		// CCerasusDialog 窗口最小化
	bool	m_bDrag;			// CCerasusDialog 窗口拖拽

	WCHAR	m_wszCaption[256];	// CCerasusDialog 窗口标题名称

	D3DCOLOR	m_colorTopLeft;			// CCerasusDialog 窗口左上角顶点颜色
	D3DCOLOR	m_colorTopRight;		// CCerasusDialog 窗口右上角顶点颜色
	D3DCOLOR	m_colorBottomLeft;		// CCerasusDialog 窗口左下角顶点颜色
	D3DCOLOR	m_colorBottomRight;		// CCerasusDialog 窗口右下角顶点颜色

	int m_nDefaultControlID;			// CCerasusDialog 窗口默认控件ID

	static double s_fTimeRefresh;		// CCerasusDialog 窗口刷新时间
	double m_fTimeLastRefresh;			// CCerasusDialog 窗口上次刷新时间

	static CCerasusControl* s_pControlFocus;		// CCerasusDialog 获得焦点控件
	static CCerasusControl* s_pControlPressed;      // CCerasusDialog 当前按下控件

	CCerasusControl* m_pControlMouseOver;           // CCerasusDialog 当前悬停控件

private:
	CCerasusResourceManager* m_pManager;			// CCerasusDialog 窗口资源管理类
	LPCALLBACKCERASUSGUIEVENT m_pCallbackEvent;		// CCerasusDialog 窗口事件回调函数
	void* m_pCallbackEventUserContext;				// CCerasusDialog 窗口事件回调用户参数

	vector<int> m_vecTextures;			// CCerasusDialog 纹理数组
	vector<int> m_vecFonts;				// CCerasusDialog 字体数组

	vector<CCerasusControl*> m_vecControls;			// CCerasusDialog 窗口控件数组
	vector<CerasusElementHolder*> m_vecDefaultElements;	// CCerasusDialog 窗口默认元素

	CCerasusElement m_CapElement;		// CCerasusDialog 标题元素

	CCerasusDialog* m_pNextDialog;		// CCerasusDialog 下一个窗口指针
	CCerasusDialog* m_pPrevDialog;		// CCerasusDialog 上一个窗口指针

public:
	bool m_bNonUserEvents;				// CCerasusDialog 用户事件标志
	bool m_bKeyboardInput;				// CCerasusDialog 键盘输入标志
	bool m_bMouseInput;					// CCerasusDialog 鼠标输入标志

public:
	CCerasusDialog();					// CCerasusDialog 构造函数
	~CCerasusDialog();					// CCerasusDialog 析构函数

	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog = true);							// CCerasusDialog 初始化窗口
	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog, CUUint sUnit);					// CCerasusDialog 初始化窗口(文件加载)
	void	Init(CCerasusResourceManager* pManager, bool bRegisterDialog, CUUintEx sUnit);					// CCerasusDialog 初始化窗口(内存加载)

	bool	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);									// CCerasusDialog 窗口消息处理

	HRESULT AddStatic(int ID, LPCWSTR strText, int x, int y, int width, int height, bool bIsDefault = false, CCerasusStatic** ppCreated = NULL);						// CCerasusDialog 窗口添加静态控件
	HRESULT AddButton(int ID, LPCWSTR strText, int x, int y, int width, int height, UINT nHotkey = 0, bool bIsDefault = false, CCerasusButton** ppCreated = NULL);		// CCerasusDialog 窗口添加按钮控件

	HRESULT	AddControl(CCerasusControl* pControl);									// CCerasusDialog 窗口添加控件
	HRESULT	InitControl(CCerasusControl* pControl);									// CCerasusDialog 窗口初始化控件

	CCerasusStatic*	GetStatic(int ID);												// CCerasusDialog 窗口获取静态控件
	CCerasusButton*	GetButton(int ID);												// CCerasusDialog 窗口获取按钮控件

	CCerasusControl*GetControl(int ID);												// CCerasusDialog 获取控件指针
	CCerasusControl*GetControl(int ID, UINT nControlType);							// CCerasusDialog 获取控件指针
	CCerasusControl*GetControlAtPoint(POINT pt);									// CCerasusDialog 获取鼠标所在的控件指针

	bool	GetControlEnabled(int ID);												// CCerasusDialog 获取控件使能状态
	void	SetControlEnabled(int ID, bool bEnabled);								// CCerasusDialog 设置控件使能状态
	
	void	ClearRadioButtonGroup(UINT nGroup);										// CCerasusDialog 清除RadioButton组
	void	ClearComboBox(int ID);													// CCerasusDialog 清除ComboBox

	HRESULT			SetDefaultElement(UINT nControlType, UINT iElement, CCerasusElement* pElement);			// CCerasusDialog 设置默认元素
	CCerasusElement*GetDefaultElement(UINT nControlType, UINT iElement);									// CCerasusDialog 获取默认元素

	void			SendEvent(UINT nEvent, bool bTriggeredByUser, CCerasusControl* pControl);											// CCerasusDialog 发送事件
	void			RequestFocus(CCerasusControl* pControl);																			// CCerasusDialog 请求焦点

	// Render 属性
	HRESULT			DrawRect(RECT* pRect, D3DCOLOR color);																				// CCerasusDialog 绘制矩形
	HRESULT			DrawRect9(RECT* pRect, D3DCOLOR color);																				// CCerasusDialog 绘制矩形
	HRESULT			DrawText(LPCWSTR strText, CCerasusElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1);			// CCerasusDialog 绘制文本
	HRESULT			DrawText9(LPCWSTR strText, CCerasusElement* pElement, RECT* prcDest, bool bShadow = false, int nCount = -1);		// CCerasusDialog 绘制文本

	// Attributes 属性
	bool			GetVisible();													// CCerasusDialog 获取可见属性
	void			SetVisible(bool bVisible);										// CCerasusDialog 设置可见属性
	bool			GetMinimized();													// CCerasusDialog 获取最小化属性
	void			SetMinimized(bool bMinimized);									// CCerasusDialog 设置最小化属性
	void			SetBackgroundColors(D3DCOLOR colorAllCorners);					// CCerasusDialog 设置背景颜色
	void			SetBackgroundColors(D3DCOLOR colorTopLeft, D3DCOLOR colorTopRight, D3DCOLOR colorBottomLeft, D3DCOLOR colorBottomRight);	// CCerasusDialog 设置背景颜色
	void			EnableCaption(bool bEnable);									// CCerasusDialog 设置标题栏使能
	int				GetCaptionHeight() const;										// CCerasusDialog 获取标题栏高度
	void            SetCaptionHeight(int nHeight);									// CCerasusDialog 设置标题栏高度
	void			SetCaptionText(const WCHAR* pwszText);							// CCerasusDialog 设置标题栏文本
	void			GetLocation(POINT& Pt) const;									// CCerasusDialog 获取窗口位置
	void			SetLocation(int x, int y);										// CCerasusDialog 设置窗口位置
	void			SetSize(int width, int height);									// CCerasusDialog 设置窗口大小
	int				GetWidth();														// CCerasusDialog 获取窗口宽度
	int				GetHeight();													// CCerasusDialog 获取窗口高度

	static void WINAPI  SetRefreshTime(float fTime);								// CCerasusDialog 设置刷新时间

	static CCerasusControl* WINAPI GetNextControl(CCerasusControl* pControl);		// CCerasusDialog 获取窗口下一个控件指针
	static CCerasusControl* WINAPI GetPrevControl(CCerasusControl* pControl);		// CCerasusDialog 获取窗口上一个控件指针

	void	RemoveControl(int ID);		// CCerasusDialog 移除控件
	void	RemoveAllControls();		// CCerasusDialog 移除所有控件

	void	SetCallback(LPCALLBACKCERASUSGUIEVENT pCallback, void* pUserContext = NULL);					// CCerasusDialog 设置事件回调函数
	void	EnableNonUserEvents(bool bEnable);																// CCerasusDialog 使能无用户事件
	void    EnableKeyboardInput(bool bEnable);																// CCerasusDialog 使能键盘输入
	void    EnableMouseInput(bool bEnable);																	// CCerasusDialog 使能鼠标输入
	bool    IsKeyboardInputEnabled() const;																	// CCerasusDialog 判断键盘是否使能

	void	Refresh();																// CCerasusDialog 窗口刷新

	static void WINAPI	ClearFocus();												// CCerasusDialog 清除控件焦点
	void                FocusDefaultControl();										// CCerasusDialog 默认控件焦点

	HRESULT			SetFont(UINT Index, LPWSTR strFontName, int nFontSize);			// CCerasusDialog 设置字体元素
	DirectFont*		GetFont(UINT Index);											// CCerasusDialog 获取字体元素

	HRESULT			SetTexture(UINT Index, CUUint sUnit);							// CCerasusDialog 设置纹理元素(文件)
	HRESULT			SetTexture(UINT Index, CUUintEx sUnit);							// CCerasusDialog 设置纹理元素(内存)
	CCerasusUnit*	GetTexture(UINT Index);											// CCerasusDialog 获取纹理元素

private:
	void	InitDefaultElements();		// CCerasusDialog 初始化默认元素

	void	OnMouseMove(POINT pt);		// CCerasusDialog 鼠标移动
	bool    OnCycleFocus(bool bForward);// CCerasusDialog 循环焦点

};


#endif // !__CERASUSDIALOG_H_

