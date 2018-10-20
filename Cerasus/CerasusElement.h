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
	UINT m_nTexIndex;						// CCerasusElement �������
	UINT m_nFontIndex;						// CCerasusElement �������

public:
	CCerasusBlendTex*	m_pTexElement;		// CCerasusElement ����ͼ��(3DͼԪ)
	CCerasusBlendFont*	m_pFontElement;		// CCerasusElement �������

public:
	CCerasusElement(IDirect3DDevice9* pD3D9Device);			// CCerasusElement ���캯��
	~CCerasusElement();										// CCerasusElement ��������

	// ����
	CCerasusBlendTex*	CCerasusElementGetTexElement();		// CCerasusElement ��ȡ����ͼ��Ԫ��
	CCerasusBlendFont*	CCerasusElementGetFontElement();	// CCerasusElement ��ȡ�������Ԫ��

	// ����
	void CCerasusElementSetTexElement(CCerasusBlendTex* pTexElement);			// CCerasusElement ��������ͼ��Ԫ��
	void CCerasusElementSetFontElement(CCerasusBlendFont* pFontElement);		// CCerasusElement �����������Ԫ��

};

#endif // !__CERASUSELEMENT_H_

