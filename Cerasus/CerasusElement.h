/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusElement.h
* @brief	This File is CerasusElement DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSELEMENT_H_
#define __CERASUSELEMENT_H_

//Include Direct Common Header File
#include "CerasusUICommon.h"
#include "CerasusBlend.h"

//Class Definition
class CCerasusElement
{
public:
	UINT m_nTexIndex;						// CCerasusElement 纹理序号
	UINT m_nFontIndex;						// CCerasusElement 字体序号

public:
	CCerasusBlendTex*	m_pTexElement;		// CCerasusElement 纹理图形(3D图元)
	CCerasusBlendFont*	m_pFontElement;		// CCerasusElement 字体绘制

public:
	CCerasusElement(IDirect3DDevice9* pD3D9Device);			// CCerasusElement 构造函数
	~CCerasusElement();										// CCerasusElement 析构函数

	// 访问
	CCerasusBlendTex*	CCerasusElementGetTexElement();		// CCerasusElement 获取纹理图形元素
	CCerasusBlendFont*	CCerasusElementGetFontElement();	// CCerasusElement 获取字体绘制元素

	// 控制
	void CCerasusElementSetTexElement(CCerasusBlendTex* pTexElement);			// CCerasusElement 设置纹理图形元素
	void CCerasusElementSetFontElement(CCerasusBlendFont* pFontElement);		// CCerasusElement 设置字体绘制元素

};

#endif // !__CERASUSELEMENT_H_

