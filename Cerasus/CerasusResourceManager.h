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
	LPDIRECT3DDEVICE9	m_pD3D9Device;				// D3D9渲染设备

protected:
	DirectSprite*		m_pSprite;					// D3DX点精灵

protected:
	vector<DirectFont*>		m_pFontCache;			// 渲染字体
	vector<CCerasusUnit*>	m_pTextureCache;		// 渲染纹理

public:
	vector<CCerasusDialog*>	m_pDialogs;				// 渲染窗口

public:
	CCerasusResourceManager(LPDIRECT3DDEVICE9 pD3D9Device);
	~CCerasusResourceManager();

	IDirect3DDevice9*		CERASUSRESOURCEMANAGER_CALLMETHOD	GetDevice()			const;			// 获取设备接口指针
	DirectSprite*			CERASUSRESOURCEMANAGER_CALLMETHOD	GetSprite()			const;			// 获取精灵接口指针
	vector<DirectFont*>		CERASUSRESOURCEMANAGER_CALLMETHOD	GetFontCache()		const;			// 获取渲染字体数组
	vector<CCerasusUnit*>	CERASUSRESOURCEMANAGER_CALLMETHOD	GetTextureCache()	const;			// 获取渲染纹理数组

public:
	bool	CERASUSRESOURCEMANAGER_CALLMETHOD	MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9ResetDevice();					// 重置设备
	HRESULT	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9LostDevice();						// 丢失设备
	void	CERASUSRESOURCEMANAGER_CALLMETHOD	OnD3D9DestroyDevice();					// 删除设备

public:
	DirectFont*		CERASUSRESOURCEMANAGER_CALLMETHOD	GetFontNode(int nIndex);		// 获取字体节点
	CCerasusUnit*	CERASUSRESOURCEMANAGER_CALLMETHOD	GetTextureNode(int nIndex);		// 获取纹理节点

	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddFont(LPWSTR strFontName, int nFontSize);			// 添加字体(字体名称、字体大小)
	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddTexture(CUUint sUnit);							// 添加纹理(文件导入)
	int		CERASUSRESOURCEMANAGER_CALLMETHOD	AddTexture(CUUintEx sUnit);							// 添加纹理(内存导入)

public:
	bool	CERASUSRESOURCEMANAGER_CALLMETHOD	RegisterDialog(CCerasusDialog* pDialog);			// 注册窗口
	void	CERASUSRESOURCEMANAGER_CALLMETHOD	UnRegisterDialog(CCerasusDialog* pDialog);			// 注销窗口


};

#endif // !__CERASUSRESOURCEMANAGER_H_
