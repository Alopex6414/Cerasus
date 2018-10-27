/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusResourceManager.cpp
* @brief	This File is CerasusResourceManager DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-24	v1.00a	alopex	Create Project.
*/
#include "CerasusResourceManager.h"

// CreasusUI 渲染资源管理类(UI)

//------------------------------------------------------------------
// @Function:	 CCerasusResourceManager()
// @Purpose: CCerasusResourceManager构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusResourceManager::CCerasusResourceManager(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
	m_pSprite = NULL;

	m_pFontCache.clear();
	m_pTextureCache.clear();
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusResourceManager()
// @Purpose: CCerasusResourceManager析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusResourceManager::~CCerasusResourceManager()
{
	// 内存垃圾回收...

	// 字体
	for (auto iter = m_pFontCache.begin(); iter != m_pFontCache.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_pFontCache.clear();

	// 纹理
	for (auto iter = m_pTextureCache.begin(); iter != m_pTextureCache.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_pTextureCache.clear();

	// 精灵
	SAFE_DELETE(m_pSprite);
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CCerasusResourceManager获取设备接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9 * CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetSprite()
// @Purpose: CCerasusResourceManager获取精灵接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite * CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetSprite() const
{
	return m_pSprite;
}

//------------------------------------------------------------------
// @Function:	 GetFontCache()
// @Purpose: CCerasusResourceManager获取渲染字体接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
vector<DirectFont*> CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetFontCache() const
{
	return m_pFontCache;
}

//------------------------------------------------------------------
// @Function:	 GetTextureCache()
// @Purpose: CCerasusResourceManager获取渲染纹理接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
vector<CCerasusUnit*> CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetTextureCache() const
{
	return m_pTextureCache;
}

//------------------------------------------------------------------
// @Function:	 MsgProc()
// @Purpose: CCerasusResourceManager消息响应处理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 OnD3D9ResetDevice()
// @Purpose: CCerasusResourceManager响应D3D9字体重置设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::OnD3D9ResetDevice()
{
	for (auto iter = m_pFontCache.begin(); iter != m_pFontCache.end(); ++iter)
	{
		VERIFY((*iter)->DirectFontGetFont()->OnResetDevice());
	}

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 OnD3D9ResetDevice()
// @Purpose: CCerasusResourceManager响应D3D9字体丢失设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::OnD3D9LostDevice()
{
	for (auto iter = m_pFontCache.begin(); iter != m_pFontCache.end(); ++iter)
	{
		VERIFY((*iter)->DirectFontReset());
	}

	for (auto iter = m_pTextureCache.begin(); iter != m_pTextureCache.end(); ++iter)
	{
		VERIFY((*iter)->CCerasusUnitReset());
	}

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 OnD3D9ResetDevice()
// @Purpose: CCerasusResourceManager响应D3D9字体删除设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::OnD3D9DestroyDevice()
{
	for (auto iter = m_pFontCache.begin(); iter != m_pFontCache.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_pFontCache.clear();

	for (auto iter = m_pTextureCache.begin(); iter != m_pTextureCache.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_pTextureCache.clear();

}

//------------------------------------------------------------------
// @Function:	 GetFontNode()
// @Purpose: CCerasusResourceManager获取字体节点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont * CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetFontNode(int nIndex)
{
	return m_pFontCache[nIndex];
}

//------------------------------------------------------------------
// @Function:	 GetTextureNode()
// @Purpose: CCerasusResourceManager获取纹理节点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit * CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::GetTextureNode(int nIndex)
{
	return m_pTextureCache[nIndex];
}

//------------------------------------------------------------------
// @Function:	 AddFont()
// @Purpose: CCerasusResourceManager添加字体
// @Since: v1.00a
// @Para: LPWSTR strFontName	// 字体名称
// @Para: int nFontSize			// 字体大小
// @Return: None
//------------------------------------------------------------------
int CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::AddFont(LPWSTR strFontName, int nFontSize)
{
	DirectFont* pFontNode = new DirectFont(m_pD3D9Device);

	if (pFontNode == NULL)
	{
		return -1;
	}

	HRESULT hr = pFontNode->DirectFontInit(nFontSize, strFontName);
	if (FAILED(hr))
	{
		return -2;
	}

	int nFont = 0;

	m_pFontCache.push_back(pFontNode);
	nFont = m_pFontCache.size() - 1;

	return nFont;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CCerasusResourceManager添加纹理
// @Since: v1.00a
// @Para: CUUint sUnit	// 添加纹理参数
// @Return: None
//------------------------------------------------------------------
int CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::AddTexture(CUUint sUnit)
{
	CCerasusUnit* pTextureNode = new CCerasusUnit(m_pD3D9Device);

	if (pTextureNode == NULL)
	{
		return -1;
	}

	HRESULT hr = pTextureNode->CCerasusUnitInit(sUnit);
	if (FAILED(hr))
	{
		return -2;
	}

	int nTexture = 0;

	m_pTextureCache.push_back(pTextureNode);
	nTexture = m_pTextureCache.size() - 1;

	return nTexture;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CCerasusResourceManager添加纹理
// @Since: v1.00a
// @Para: CUUintEx sUnit	// 添加纹理参数
// @Return: None
//------------------------------------------------------------------
int CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::AddTexture(CUUintEx sUnit)
{
	CCerasusUnit* pTextureNode = new CCerasusUnit(m_pD3D9Device);

	if (pTextureNode == NULL)
	{
		return -1;
	}

	HRESULT hr = pTextureNode->CCerasusUnitInit(sUnit);
	if (FAILED(hr))
	{
		return -2;
	}

	int nTexture = 0;

	m_pTextureCache.push_back(pTextureNode);
	nTexture = m_pTextureCache.size() - 1;

	return nTexture;
}

//------------------------------------------------------------------
// @Function:	 RegisterDialog()
// @Purpose: CCerasusResourceManager注册窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::RegisterDialog(CCerasusDialog * pDialog)
{
	for (auto iter = m_pDialogs.begin(); iter != m_pDialogs.end(); ++iter)
	{
		if (*iter == pDialog)
		{
			return true;
		}

	}

	m_pDialogs.push_back(pDialog);	// 添加

	return false;
}

//------------------------------------------------------------------
// @Function:	 RegisterDialog()
// @Purpose: CCerasusResourceManager注销窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSRESOURCEMANAGER_CALLMETHOD CCerasusResourceManager::UnRegisterDialog(CCerasusDialog * pDialog)
{
	

}
