/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraStatic.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURASTATIC_H_
#define __SAKURASTATIC_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"
#include "SakuraControl.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURASTATIC_API	__declspec(dllexport)
#else
#define SAKURASTATIC_API	__declspec(dllimport)
#endif

#define	SAKURASTATIC_CALLMETHOD	__stdcall

//Class Definition
class SAKURASTATIC_API CSakuraStatic : public CSakuraControl
{
protected:
	WCHAR		m_strText[MAX_PATH];			// CSakuraStatic ��̬�ؼ��ı�
	DWORD		m_dwFormat;						// CSakuraStatic ��̬�ؼ���ʽ
	D3DCOLOR	m_dwColor;						// CSakuraStatic ��̬�ؼ���ɫ

public:
	CSakuraStatic(CSakuraDialog* pDialog = NULL);							// CSakuraStatic ���캯��

	LPCWSTR			SAKURASTATIC_CALLMETHOD	GetText();						// CSakuraStatic ��ȡ�ı�
	HRESULT			SAKURASTATIC_CALLMETHOD SetText(LPCWSTR strText);		// CSakuraStatic �����ı�
	DWORD			SAKURASTATIC_CALLMETHOD	GetFormat();					// CSakuraStatic ��ȡ��ʽ
	HRESULT			SAKURASTATIC_CALLMETHOD SetFormat(DWORD dwFormat);		// CSakuraStatic ���ø�ʽ
	D3DCOLOR		SAKURASTATIC_CALLMETHOD	GetColor();						// CSakuraStatic ��ȡ��ɫ
	HRESULT			SAKURASTATIC_CALLMETHOD	SetColor(D3DCOLOR dwColor);		// CSakuraStatic ������ɫ

	virtual BOOL    SAKURASTATIC_CALLMETHOD	ContainsPoint(POINT pt);		// CSakuraStatic ������ڿؼ���
	virtual void	SAKURASTATIC_CALLMETHOD	Render();						// CSakuraStatic ��Ⱦ�ؼ�

};


#endif // !__SAKURASTATIC_H_

