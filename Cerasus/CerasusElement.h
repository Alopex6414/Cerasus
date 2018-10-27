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
	UINT	m_iFont;			// CCerasusElement ����Ԫ�����
	UINT	m_iTexture;			// CCerasusElement ����Ԫ�����
	DWORD	m_dwTextureFormat;	// CCerasusElement ������Ƹ�ʽ
	RECT	m_rcTexture;		// CCerasusElement ���������С

	CerasusBlendColor	m_FontColor;		// CCerasusElement ������Ⱦ��ɫ
	CerasusBlendColor	m_TextureColor;		// CCerasusElement ������Ⱦ��ɫ

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

