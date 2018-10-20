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
	CCerasusUnit* m_pTexStates[MAX_CONTROL_STATES];			// CCerasusBlendTex �ؼ�����ȫ��״̬
	CCerasusUnit* m_pTexCurrent;							// CCerasusBlendTex	�ؼ�����ǰ״̬

protected:
	CUUint		m_sUnitArr[MAX_CONTROL_STATES];				// CCerasusBlendTex Ԫ������
	CUUintEx	m_sUnitExArr[MAX_CONTROL_STATES];			// CCerasusBlendTex Ԫ������(Ex)

public:
	CCerasusBlendTex(IDirect3DDevice9* pD3D9Device);		// CCerasusBlendTex ���캯��
	~CCerasusBlendTex();									// CCerasusBlendTex ��������

	void	SetUnit(UINT nState, CUUint sUnit);				// CCerasusBlendTex �����������
	void	SetUnitEx(UINT nState, CUUintEx sUnit);			// CCerasusBlendTex �����������(Ex)

	void	Init();											// CCerasusBlendTex ��ʼ���ؼ�����
	void	InitEx();										// CCerasusBlendTex ��ʼ���ؼ�����(����+1)
	void	Blend(UINT nState);								// CCerasusBlendTex ��Ⱦ�ؼ�����
	void	Refresh();										// CCerasusBlendTex ˢ�¿ؼ�����

};

class CCerasusBlendFont
{
public:
	DirectFont* m_pFontStates[MAX_CONTROL_STATES];			// CCerasusBlendFont �ؼ�����ȫ��״̬
	DirectFont* m_pFontCurrent;								// CCerasusBlendFont �ؼ����嵱ǰ״̬

protected:
	int		m_nFontSize;									// CCerasusBlendFont �����С
	LPWSTR	m_lpszFontType;									// CCerasusBlendFont �����ͺ�

	HWND	m_hWnd;											// CCerasusBlendFont ���ƴ��ھ��
	LPCWSTR m_lpcszStr;										// CCerasusBlendFont �����ַ���
	DWORD m_dwFormat;										// CCerasusBlendFont ���Ƹ�ʽ
	D3DCOLOR m_dwColor;										// CCerasusBlendFont ������ɫ

public:
	CCerasusBlendFont(IDirect3DDevice9* pD3D9Device);		// CCerasusBlendFont ���캯��
	~CCerasusBlendFont();									// CCerasusBlendFont ��������

	void	SetFontProperty(int nFontSize, LPWSTR lpszFontType);								// CCerasusBlendFont ������������
	void	SetFontText(HWND hWnd, LPCWSTR lpcszStr, DWORD dwFormat, D3DCOLOR dwColor);			// CCerasusBlendFont ������������

	void	Init();											// CCerasusBlendFont ��ʼ���ؼ�����
	void	Blend(UINT nState);								// CCerasusBlendFont ��Ⱦ�ؼ�����
	void	Refresh();										// CCerasusBlendFont ˢ�¿ؼ�����

};



#endif // !__CERASUSBLEND_H_
