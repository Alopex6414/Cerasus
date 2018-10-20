/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusBlend.h
* @brief	This File is CerasusBlend DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSBLEND_H_
#define __CERASUSBLEND_H_

//Include Direct Common Header File
#include "CerasusUICommon.h"

//Class Definition
class CCerasusBlendTex
{
public:
	CCerasusUnit* m_pTexStates[MAX_CONTROL_STATES];			// CCerasusBlendTex 控件纹理全部状态
	CCerasusUnit* m_pTexCurrent;							// CCerasusBlendTex	控件纹理当前状态

protected:
	CUUint		m_sUnitArr[MAX_CONTROL_STATES];				// CCerasusBlendTex 元素数组
	CUUintEx	m_sUnitExArr[MAX_CONTROL_STATES];			// CCerasusBlendTex 元素数组(Ex)

public:
	CCerasusBlendTex(IDirect3DDevice9* pD3D9Device);		// CCerasusBlendTex 构造函数
	~CCerasusBlendTex();									// CCerasusBlendTex 析构函数

	void	SetUnit(UINT nState, CUUint sUnit);				// CCerasusBlendTex 设置纹理参数
	void	SetUnitEx(UINT nState, CUUintEx sUnit);			// CCerasusBlendTex 设置纹理参数(Ex)

	void	Init();											// CCerasusBlendTex 初始化控件纹理
	void	InitEx();										// CCerasusBlendTex 初始化控件纹理(重载+1)
	void	Blend(UINT nState);								// CCerasusBlendTex 渲染控件纹理
	void	Refresh();										// CCerasusBlendTex 刷新控件纹理

};

class CCerasusBlendFont
{
public:
	DirectFont* m_pFontStates[MAX_CONTROL_STATES];			// CCerasusBlendFont 控件字体全部状态
	DirectFont* m_pFontCurrent;								// CCerasusBlendFont 控件字体当前状态

protected:
	int		m_nFontSize;									// CCerasusBlendFont 字体大小
	LPWSTR	m_lpszFontType;									// CCerasusBlendFont 字体型号

	HWND	m_hWnd;											// CCerasusBlendFont 绘制窗口句柄
	LPCWSTR m_lpcszStr;										// CCerasusBlendFont 绘制字符串
	DWORD m_dwFormat;										// CCerasusBlendFont 绘制格式
	D3DCOLOR m_dwColor;										// CCerasusBlendFont 绘制颜色

public:
	CCerasusBlendFont(IDirect3DDevice9* pD3D9Device);		// CCerasusBlendFont 构造函数
	~CCerasusBlendFont();									// CCerasusBlendFont 析构函数

	void	SetFontProperty(int nFontSize, LPWSTR lpszFontType);								// CCerasusBlendFont 设置字体属性
	void	SetFontText(HWND hWnd, LPCWSTR lpcszStr, DWORD dwFormat, D3DCOLOR dwColor);			// CCerasusBlendFont 设置字体内容

	void	Init();											// CCerasusBlendFont 初始化控件字体
	void	Blend(UINT nState);								// CCerasusBlendFont 渲染控件字体
	void	Refresh();										// CCerasusBlendFont 刷新控件字体

};



#endif // !__CERASUSBLEND_H_
