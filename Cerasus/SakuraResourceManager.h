/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraResourceManager.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __SAKURARESOURCEMANAGER_H_
#define __SAKURARESOURCEMANAGER_H_

//Include SakuraGUI Common Header File
#include "SakuraUICommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURARESOURCEMANAGER_API	__declspec(dllexport)
#else
#define SAKURARESOURCEMANAGER_API	__declspec(dllimport)
#endif

#define	SAKURARESOURCEMANAGER_CALLMETHOD	__stdcall

//Class Definition
class SAKURARESOURCEMANAGER_API CSakuraResourceManager
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;					// CSakuraResourceManager D3D9��Ⱦ�豸�ӿ�ָ��

	vector<CUFont*>		m_pFontCaches;					// CSakuraResourceManager ������Ⱦ��Դ
	vector<CUUint*>		m_pTextureCaches;				// CSakuraResourceManager ������Ⱦ��Դ
	vector<CUUintEx*>	m_pTextureExCaches;				// CSakuraResourceManager ������Ⱦ��Դ(Ex)

public:
	CSakuraResourceManager();
	~CSakuraResourceManager();
	
	bool	SAKURARESOURCEMANAGER_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraResourceManager ��Ϣ������

	HRESULT	SAKURARESOURCEMANAGER_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);			// CSakuraResourceManager ��ʼ���豸
	void	SAKURARESOURCEMANAGER_CALLMETHOD	OnDestroy();										// CSakuraResourceManager �����豸

	LPDIRECT3DDEVICE9	SAKURARESOURCEMANAGER_CALLMETHOD	GetDevice() const;						// CSakuraResourceManager ��ȡD3D9��Ⱦ�豸�ӿ�ָ��

	CUFont*				SAKURARESOURCEMANAGER_CALLMETHOD	GetFontNode(int nIndex);				// CSakuraResourceManager ��ȡ����ڵ�
	CUUint*				SAKURARESOURCEMANAGER_CALLMETHOD	GetTextureNode(int nIndex);				// CSakuraResourceManager ��ȡ����ڵ�
	CUUintEx*			SAKURARESOURCEMANAGER_CALLMETHOD	GetTextureNodeEx(int nIndex);			// CSakuraResourceManager ��ȡ����ڵ�(Ex)

	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddFont(CUFont* pFont);								// CSakuraResourceManager ���������Դ
	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddTexture(CUUint* pTexture);						// CSakuraResourceManager ���������Դ
	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddTexture(CUUintEx* pTexture);						// CSakuraResourceManager ���������Դ

};


#endif // !__SAKURARESOURCEMANAGER_H_

