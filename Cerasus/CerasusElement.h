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
	UINT	m_iFont;			// CCerasusElement 字体元素序号
	UINT	m_iTexture;			// CCerasusElement 纹理元素序号
	DWORD	m_dwTextureFormat;	// CCerasusElement 纹理绘制格式
	RECT	m_rcTexture;		// CCerasusElement 纹理区域大小

	CerasusBlendColor	m_FontColor;		// CCerasusElement 字体渲染颜色
	CerasusBlendColor	m_TextureColor;		// CCerasusElement 纹理渲染颜色

public:
	void SetFont(UINT iFont, D3DCOLOR defaultFontColor = D3DCOLOR_ARGB(255, 255, 255, 255), DWORD dwTextFormat = DT_CENTER | DT_VCENTER);
	void SetTexture(UINT iTexture, RECT* prcTexture, D3DCOLOR defaultTextureColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Refresh();

};

//Struct Definition
struct CerasusElementHolder
{
	UINT nControlType;
	UINT iElement;
	CCerasusElement Element;
};


#endif // !__CERASUSELEMENT_H_

