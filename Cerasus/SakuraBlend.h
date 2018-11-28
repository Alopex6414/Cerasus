/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraBlend.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURABLEND_H_
#define __SAKURABLEND_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURABLEND_API	__declspec(dllexport)
#else
#define SAKURABLEND_API	__declspec(dllimport)
#endif

#define	SAKURABLEND_CALLMETHOD	__stdcall

//Class Definition
class SAKURABLEND_API CSakuraBlendFont
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraBlendFont D3D9��Ⱦ�豸

public:
	DirectFont* m_States[MAX_CONTROL_STATES];			// CSakuraBlendFont �����ؼ�״̬����
	DirectFont* m_Current;								// CSakuraBlendFont ��ǰ�ؼ�״̬����

public:
	CSakuraBlendFont();									// CSakuraBlendFont ���캯��
	~CSakuraBlendFont();								// CSakuraBlendFont ��������

	CSakuraBlendFont(const CSakuraBlendFont& Object);	// CSakuraBlendFont �������캯��(����+1)
	CSakuraBlendFont(LPDIRECT3DDEVICE9 pD3D9Device);	// CSakuraBlendFont ���캯��(����+2)

	CSakuraBlendFont& operator=(const CSakuraBlendFont& Object);		// CSakuraBlendFont ��ֵ���������

	LPDIRECT3DDEVICE9	SAKURABLEND_CALLMETHOD	GetDevice() const;													// CSakuraBlendFont ��ȡD3D9�豸ָ��
	DirectFont*			SAKURABLEND_CALLMETHOD	GetCurrent() const;													// CSakuraBlendFont ��ȡ�ؼ�״̬����

	void	SAKURABLEND_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);										// CSakuraBlendFont ��ʼ��
	void	SAKURABLEND_CALLMETHOD	OnLostDevice();																	// CSakuraBlendFont ��ʧ�豸
	void	SAKURABLEND_CALLMETHOD	OnResetDevice();																// CSakuraBlendFont	�����豸
	int		SAKURABLEND_CALLMETHOD	AddFont(SAKURA_CONTROL_STATE eType, LPWSTR strFontName, int nFontSize);			// CSakuraBlendFont �������(�������ơ������С)
	void	SAKURABLEND_CALLMETHOD	Blend(SAKURA_CONTROL_STATE eType, LPCWSTR pString, LPRECT pRect, DWORD Format = DT_CENTER | DT_VCENTER, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 255, 255));			// CSakuraBlendFont ��Ⱦ����

};

class SAKURABLEND_API CSakuraBlendTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;					// CSakuraBlendTexture D3D9��Ⱦ�豸

public:
	CCerasusUnit* m_States[MAX_CONTROL_STATES];			// CSakuraBlendTexture �����ؼ�״̬����
	CCerasusUnit* m_Current;							// CSakuraBlendTexture ��ǰ�ؼ�״̬����

public:
	CSakuraBlendTexture();								// CSakuraBlendTexture ���캯��
	~CSakuraBlendTexture();								// CSakuraBlendTexture ��������

	CSakuraBlendTexture(const CSakuraBlendTexture& Object);	// CSakuraBlendTexture �������캯��(����+1)
	CSakuraBlendTexture(LPDIRECT3DDEVICE9 pD3D9Device);		// CSakuraBlendTexture ���캯��(����+2)

	CSakuraBlendTexture& operator=(const CSakuraBlendTexture& Object);		// CSakuraBlendTexture ��ֵ���������

	LPDIRECT3DDEVICE9	SAKURABLEND_CALLMETHOD	GetDevice() const;													// CSakuraBlendTexture ��ȡD3D9�豸ָ��
	CCerasusUnit*		SAKURABLEND_CALLMETHOD	GetCurrent() const;													// CSakuraBlendTexture ��ȡ�ؼ�״̬����

	void	SAKURABLEND_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);										// CSakuraBlendTexture ��ʼ��
	void	SAKURABLEND_CALLMETHOD	OnLostDevice();																	// CSakuraBlendTexture ��ʧ�豸
	void	SAKURABLEND_CALLMETHOD	OnResetDevice();																// CSakuraBlendTexture	�����豸
	int		SAKURABLEND_CALLMETHOD	AddTexture(SAKURA_CONTROL_STATE eType, CUUint sUnit);							// CSakuraBlendTexture �������(�ļ�����)
	int		SAKURABLEND_CALLMETHOD	AddTexture(SAKURA_CONTROL_STATE eType, CUUintEx sUnit);							// CSakuraBlendTexture �������(�ڴ浼��)
	void	SAKURABLEND_CALLMETHOD	Blend(SAKURA_CONTROL_STATE eType);												// CSakuraBlendTexture ��Ⱦ����

};



#endif // !__SAKURABLEND_H_
