/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraResourceManager.h
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#pragma once

#ifndef __SAKURARESOURCEMANAGER_H_
#define __SAKURARESOURCEMANAGER_H_

// Include SakuraGUI Common Header File
#include "SakuraUICommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define SAKURARESOURCEMANAGER_API	__declspec(dllexport)
#else
#define SAKURARESOURCEMANAGER_API	__declspec(dllimport)
#endif

#define	SAKURARESOURCEMANAGER_CALLMETHOD	__stdcall

// Class Definition
class SAKURARESOURCEMANAGER_API CSakuraResourceManager
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;					// CSakuraResourceManager D3D9渲染设备接口指针

	vector<CUFont*>		m_pFontCaches;					// CSakuraResourceManager 字体渲染资源
	vector<S_CS_UNIT_PARA*>		m_pTextureCaches;		// CSakuraResourceManager 纹理渲染资源
	vector<S_CS_UNIT_EX_PARA*>	m_pTextureExCaches;		// CSakuraResourceManager 纹理渲染资源(Ex)

public:
	CSakuraResourceManager();
	~CSakuraResourceManager();
	
	bool	SAKURARESOURCEMANAGER_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);			// CSakuraResourceManager 消息处理函数

	HRESULT	SAKURARESOURCEMANAGER_CALLMETHOD	OnCreate(LPDIRECT3DDEVICE9 pD3D9Device);			// CSakuraResourceManager 初始化设备
	void	SAKURARESOURCEMANAGER_CALLMETHOD	OnDestroy();										// CSakuraResourceManager 销毁设备

	LPDIRECT3DDEVICE9	SAKURARESOURCEMANAGER_CALLMETHOD	GetDevice() const;						// CSakuraResourceManager 获取D3D9渲染设备接口指针

	CUFont*				SAKURARESOURCEMANAGER_CALLMETHOD	GetFontNode(int nIndex);				// CSakuraResourceManager 获取字体节点
	S_CS_UNIT_PARA*		SAKURARESOURCEMANAGER_CALLMETHOD	GetTextureNode(int nIndex);				// CSakuraResourceManager 获取纹理节点
	S_CS_UNIT_EX_PARA*	SAKURARESOURCEMANAGER_CALLMETHOD	GetTextureNodeEx(int nIndex);			// CSakuraResourceManager 获取纹理节点(Ex)

	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddFont(CUFont* pFont);								// CSakuraResourceManager 添加字体资源
	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddTexture(S_CS_UNIT_PARA* pTexture);				// CSakuraResourceManager 添加纹理资源
	int		SAKURARESOURCEMANAGER_CALLMETHOD	AddTexture(S_CS_UNIT_EX_PARA* pTexture);			// CSakuraResourceManager 添加纹理资源

};


#endif // !__SAKURARESOURCEMANAGER_H_

