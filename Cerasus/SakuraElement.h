/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraElement.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURAELEMENT_H_
#define __SAKURAELEMENT_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraBlend.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURAELEMENT_API	__declspec(dllexport)
#else
#define SAKURAELEMENT_API	__declspec(dllimport)
#endif

#define	SAKURAELEMENT_CALLMETHOD	__stdcall

// Class Definition
class SAKURAELEMENT_API CSakuraElement
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraElement D3D9渲染设备

public:
	CSakuraBlendFont	m_FontBlend;					// CSakuraElement 字体渲染类
	CSakuraBlendTexture	m_TextureBlend;					// CSakuraElement 纹理渲染类

public:
	CSakuraElement(LPDIRECT3DDEVICE9 pD3D9Device);		// CSakuraElement 构造函数
	~CSakuraElement();									// CSakuraElement 析构函数

	CSakuraElement(const CSakuraElement& Object);		// CSakuraElement 拷贝构造函数

	CSakuraBlendFont&		SAKURAELEMENT_CALLMETHOD	GetFontBlend();			// CSakuraElement 获取字体渲染类
	CSakuraBlendTexture&	SAKURAELEMENT_CALLMETHOD	GetTextureBlend();		// CSakuraElement 获取纹理渲染类

	void				SAKURAELEMENT_CALLMETHOD	Refresh();				// CSakuraElement 刷新渲染资源

};

// Struct Definition
typedef struct
{
	UINT nControlType;
	UINT iElement;
	CSakuraElement* pElement;
} CSakuraElementHolder, *LPCSakuraElementHolder;


#endif // !__SAKURAELEMENT_H_
