/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusResourceManager.h
* @brief	This File is CerasusResourceManager DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-24	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSRESOURCEMANAGER_H_
#define __CERASUSRESOURCEMANAGER_H_

//Include Direct Common Header File
#include "CerasusUICommon.h"
#include "CerasusDialog.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSRESOURCEMANAGER_API	__declspec(dllexport)
#else
#define CERASUSRESOURCEMANAGER_API	__declspec(dllimport)
#endif

#define CERASUSRESOURCEMANAGER_CALLMETHOD	__stdcall

//Class Definition
class CCerasusResourceManager
{
protected:
	LPDIRECT3DDEVICE9	m_pD3D9Device;				// D3D9��Ⱦ�豸

protected:
	DirectSprite*		m_pSprite;					// D3DX�㾫��

protected:
	vector<DirectFont*>		m_pFontCache;			// ��Ⱦ����
	vector<CCerasusUnit*>	m_pTextureCache;		// ��Ⱦ����

public:
	vector<CCerasusDialog*>	m_pDialogs;				// ��Ⱦ����

public:
	CCerasusResourceManager(LPDIRECT3DDEVICE9 pD3D9Device);
	~CCerasusResourceManager();

	IDirect3DDevice9*		CERASUSRESOURCEMANAGER_CALLMETHOD	GetDevice()			const;			// ��ȡ�豸�ӿ�ָ��
	DirectSprite*			CERASUSRESOURCEMANAGER_CALLMETHOD	GetSprite()			const;			// ��ȡ����ӿ�ָ��
	vector<DirectFont*>		CERASUSRESOURCEMANAGER_CALLMETHOD	GetFontCache()		const;			// ��ȡ��Ⱦ��������
	vector<CCerasusUnit*>	CERASUSRESOURCEMANAGER_CALLMETHOD	GetTextureCache()	const;			// ��ȡ��Ⱦ��������

public:
	bool	CERASUSRESOURCEMANAGER_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9ResetDevice();					// �����豸
	HRESULT	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9LostDevice();						// ��ʧ�豸
	void	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9DestroyDevice();					// ɾ���豸

public:
	DirectFont*		CERASUSRESOURCEMANAGER_CALLMETHOD	GetFontNode(int nIndex);		// ��ȡ����ڵ�
	CCerasusUnit*	CERASUSRESOURCEMANAGER_CALLMETHOD	GetTextureNode(int nIndex);		// ��ȡ����ڵ�

	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddFont(LPWSTR strFontName, int nFontSize);			// �������(�������ơ������С)
	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddTexture(CUUint sUnit);							// �������(�ļ�����)
	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddTexture(CUUintEx sUnit);							// �������(�ڴ浼��)

public:
	bool	CERASUSRESOURCEMANAGER_CALLMETHOD	RegisterDialog(CCerasusDialog* pDialog);			// ע�ᴰ��
	void	CERASUSRESOURCEMANAGER_CALLMETHOD	UnRegisterDialog(CCerasusDialog* pDialog);			// ע������


};

#endif // !__CERASUSRESOURCEMANAGER_H_
