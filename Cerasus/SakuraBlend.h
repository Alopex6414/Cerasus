/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraBlend.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURABLEND_H_
#define __SAKURABLEND_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURABLEND_API	__declspec(dllexport)
#else
#define SAKURABLEND_API	__declspec(dllimport)
#endif

#define	SAKURABLEND_CALLMETHOD	__stdcall

// Class Definition
class SAKURABLEND_API CSakuraBlendFont
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraBlendFont D3D9渲染设备

public:
	DirectFont* m_States[MAX_CONTROL_STATES];			// CSakuraBlendFont 各个控件状态字体
	DirectFont* m_Current;								// CSakuraBlendFont 当前控件状态字体

public:
	CSakuraBlendFont();													// CSakuraBlendFont 构造函数
	~CSakuraBlendFont();												// CSakuraBlendFont 析构函数

	CSakuraBlendFont(const CSakuraBlendFont& Object);					// CSakuraBlendFont 拷贝构造函数(重载+1)
	CSakuraBlendFont(LPDIRECT3DDEVICE9 pD3D9Device);					// CSakuraBlendFont 构造函数(重载+2)

	CSakuraBlendFont& operator=(const CSakuraBlendFont& Object);		// CSakuraBlendFont 赋值运算符重载

	LPDIRECT3DDEVICE9	SAKURABLEND_CALLMETHOD	GetDevice() const;													// CSakuraBlendFont 获取D3D9设备指针
	DirectFont*			SAKURABLEND_CALLMETHOD	GetCurrent() const;													// CSakuraBlendFont 获取控件状态字体

	void	SAKURABLEND_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);										// CSakuraBlendFont 初始化
	void	SAKURABLEND_CALLMETHOD	OnLostDevice();																	// CSakuraBlendFont 丢失设备
	void	SAKURABLEND_CALLMETHOD	OnResetDevice();																// CSakuraBlendFont	重置设备
	int		SAKURABLEND_CALLMETHOD	AddFont(SAKURA_CONTROL_STATE eType, LPWSTR strFontName, int nFontSize);			// CSakuraBlendFont 添加字体(字体名称、字体大小)
	void	SAKURABLEND_CALLMETHOD	Blend(SAKURA_CONTROL_STATE eType, LPCWSTR pString, LPRECT pRect, DWORD Format = DT_CENTER | DT_VCENTER, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));			// CSakuraBlendFont 渲染字体

};

class SAKURABLEND_API CSakuraBlendTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraBlendTexture D3D9渲染设备

public:
	CCerasusUnit* m_States[MAX_CONTROL_STATES];			// CSakuraBlendTexture 各个控件状态纹理
	CCerasusUnit* m_Current;							// CSakuraBlendTexture 当前控件状态纹理

public:
	CSakuraBlendTexture();													// CSakuraBlendTexture 构造函数
	~CSakuraBlendTexture();													// CSakuraBlendTexture 析构函数

	CSakuraBlendTexture(const CSakuraBlendTexture& Object);					// CSakuraBlendTexture 拷贝构造函数(重载+1)
	CSakuraBlendTexture(LPDIRECT3DDEVICE9 pD3D9Device);						// CSakuraBlendTexture 构造函数(重载+2)

	CSakuraBlendTexture& operator=(const CSakuraBlendTexture& Object);		// CSakuraBlendTexture 赋值运算符重载

	LPDIRECT3DDEVICE9	SAKURABLEND_CALLMETHOD	GetDevice() const;													// CSakuraBlendTexture 获取D3D9设备指针
	CCerasusUnit*		SAKURABLEND_CALLMETHOD	GetCurrent() const;													// CSakuraBlendTexture 获取控件状态字体

	void	SAKURABLEND_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);										// CSakuraBlendTexture 初始化
	void	SAKURABLEND_CALLMETHOD	OnLostDevice();																	// CSakuraBlendTexture 丢失设备
	void	SAKURABLEND_CALLMETHOD	OnResetDevice();																// CSakuraBlendTexture 重置设备
	int		SAKURABLEND_CALLMETHOD	AddTexture(SAKURA_CONTROL_STATE eType, S_CS_UNIT_PARA sUnit);					// CSakuraBlendTexture 添加纹理(文件导入)
	int		SAKURABLEND_CALLMETHOD	AddTexture(SAKURA_CONTROL_STATE eType, S_CS_UNIT_EX_PARA sUnit);				// CSakuraBlendTexture 添加纹理(内存导入)
	void	SAKURABLEND_CALLMETHOD	Blend(SAKURA_CONTROL_STATE eType);												// CSakuraBlendTexture 渲染纹理

};



#endif // !__SAKURABLEND_H_
