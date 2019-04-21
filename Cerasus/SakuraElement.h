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
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraElement D3D9��Ⱦ�豸

public:
	CSakuraBlendFont	m_FontBlend;					// CSakuraElement ������Ⱦ��
	CSakuraBlendTexture	m_TextureBlend;					// CSakuraElement ������Ⱦ��

public:
	CSakuraElement(LPDIRECT3DDEVICE9 pD3D9Device);		// CSakuraElement ���캯��
	~CSakuraElement();									// CSakuraElement ��������

	CSakuraElement(const CSakuraElement& Object);		// CSakuraElement �������캯��

	CSakuraBlendFont&		SAKURAELEMENT_CALLMETHOD	GetFontBlend();			// CSakuraElement ��ȡ������Ⱦ��
	CSakuraBlendTexture&	SAKURAELEMENT_CALLMETHOD	GetTextureBlend();		// CSakuraElement ��ȡ������Ⱦ��

	void				SAKURAELEMENT_CALLMETHOD	Refresh();				// CSakuraElement ˢ����Ⱦ��Դ

};

// Struct Definition
typedef struct
{
	UINT nControlType;
	UINT iElement;
	CSakuraElement* pElement;
} CSakuraElementHolder, *LPCSakuraElementHolder;


#endif // !__SAKURAELEMENT_H_
