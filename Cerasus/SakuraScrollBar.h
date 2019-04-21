/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraScrollBar.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-11-28	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURASCROLLBAR_H_
#define __SAKURASCROLLBAR_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASCROLLBAR_API	__declspec(dllexport)
#else
#define SAKURASCROLLBAR_API	__declspec(dllimport)
#endif

#define	SAKURASCROLLBAR_CALLMETHOD	__stdcall

#define SCROLLBAR_MINTHUMBSIZE	8

// Class Definition
class SAKURASCROLLBAR_API CSakuraScrollBar : public CSakuraControl
{
protected:
	bool m_bShowThumb;			// CSakuraScrollBar 是否显示滚动条滑块
	bool m_bDrag;				// CSakuraScrollBar 是否被拖拽

	RECT m_rcUpButton;			// CSakuraScrollBar 滚动条上滑按钮区域
	RECT m_rcDownButton;		// CSakuraScrollBar 滚动条下滑按钮区域
	RECT m_rcTrack;				// CSakuraScrollBar 滚动条轨迹区域
	RECT m_rcThumb;				// CSakuraScrollBar 滚动条滑块区域

	int m_nPosition;			// CSakuraScrollBar 第一条显示位置
	int m_nPageSize;			// CSakuraScrollBar 每页显示多少条
	int m_nStart;				// CSakuraScrollBar 第一个项位置
	int m_nEnd;					// CSakuraScrollBar 最后一项位置

	POINT m_LastMouse;			// CSakuraScrollBar 上次鼠标位置
	SAKURA_SCROLLBAR_STATE m_eArrow;	// CSakuraScrollBar 滚动条状态
	double m_dArrowTS;

protected:
	void	SAKURASCROLLBAR_CALLMETHOD	UpdateThumbRect();	// CSakuraScrollBar 滚动条位置更新
	void	SAKURASCROLLBAR_CALLMETHOD	Cap();				// CSakuraScrollBar 滚动条位置检测

public:
	CSakuraScrollBar(CSakuraDialog* pDialog = NULL);		// CSakuraScrollBar 构造函数
	virtual	~CSakuraScrollBar();							// CSakuraScrollBar 析构函数

	virtual bool	SAKURASCROLLBAR_CALLMETHOD	HandleKeyboard(UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraScrollBar 键盘消息响应
	virtual bool    SAKURASCROLLBAR_CALLMETHOD	HandleMouse(UINT uMsg, POINT pt, WPARAM wParam, LPARAM lParam);		// CSakuraScrollBar 鼠标消息响应
	virtual bool    SAKURASCROLLBAR_CALLMETHOD	MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);					// CSakuraScrollBar 消息处理

	virtual void    SAKURASCROLLBAR_CALLMETHOD	Render();															// CSakuraScrollBar 渲染控件
	virtual void    SAKURASCROLLBAR_CALLMETHOD	UpdateRects();														// CSakuraScrollBar 更新控件区域

	void            SAKURASCROLLBAR_CALLMETHOD	SetTrackRange(int nStart, int nEnd);								// CSakuraScrollBar 设置轨迹范围
	int             SAKURASCROLLBAR_CALLMETHOD	GetTrackPos();														// CSakuraScrollBar 获取轨迹位置
	void			SAKURASCROLLBAR_CALLMETHOD  SetTrackPos(int nPosition);											// CSakuraScrollBar 设置轨迹位置
	int             SAKURASCROLLBAR_CALLMETHOD	GetPageSize();														// CSakuraScrollBar 获取每页数量
	void            SAKURASCROLLBAR_CALLMETHOD	SetPageSize(int nPageSize);											// CSakuraScrollBar 设置每页数量

	void            SAKURASCROLLBAR_CALLMETHOD	Scroll(int nDelta);													// CSakuraScrollBar 滚动条滚动
	void            SAKURASCROLLBAR_CALLMETHOD	ShowItem(int nIndex);												// CSakuraScrollBar 显示条数
};


#endif // !__SAKURASCROLLBAR_H_

