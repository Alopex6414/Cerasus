/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraResourceManager.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraResourceManager.h"

// SakuraGUI 资源管理类(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraResourceManager()
// @Purpose: CSakuraResourceManager构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraResourceManager::CSakuraResourceManager()
{
	m_pD3D9Device = NULL;

	m_pFontCaches.clear();
	m_pTextureCaches.clear();
	m_pTextureExCaches.clear();
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraResourceManager()
// @Purpose: CSakuraResourceManager析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraResourceManager::~CSakuraResourceManager()
{
	for (auto iter = m_pFontCaches.begin(); iter != m_pFontCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pFontCaches.clear();

	for (auto iter = m_pTextureCaches.begin(); iter != m_pTextureCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pTextureCaches.clear();

	for (auto iter = m_pTextureExCaches.begin(); iter != m_pTextureExCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pTextureExCaches.clear();
}

//------------------------------------------------------------------
// @Function:	 CSakuraResourceManager()
// @Purpose: CSakuraResourceManager消息处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraResourceManager初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::OnCreate(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 OnDestroy()
// @Purpose: CSakuraResourceManager销毁
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::OnDestroy()
{
	m_pD3D9Device = NULL;

	for (auto iter = m_pFontCaches.begin(); iter != m_pFontCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pFontCaches.clear();

	for (auto iter = m_pTextureCaches.begin(); iter != m_pTextureCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pTextureCaches.clear();

	for (auto iter = m_pTextureExCaches.begin(); iter != m_pTextureExCaches.end(); ++iter)
	{
		SAFE_DELETE((*iter));
	}
	m_pTextureExCaches.clear();

}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraResourceManager获取设备接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetFontNode()
// @Purpose: CSakuraResourceManager获取字体节点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUFont *SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetFontNode(int nIndex)
{
	if (nIndex >= m_pFontCaches.size())
	{
		return NULL;
	}

	return m_pFontCaches.at(nIndex);
}

//------------------------------------------------------------------
// @Function:	 GetTextureNode()
// @Purpose: CSakuraResourceManager获取纹理节点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
S_CS_UNIT_PARA*SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetTextureNode(int nIndex)
{
	if (nIndex >= m_pTextureCaches.size())
	{
		return NULL;
	}

	return m_pTextureCaches.at(nIndex);
}

//------------------------------------------------------------------
// @Function:	 GetTextureNodeEx()
// @Purpose: CSakuraResourceManager获取纹理节点Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
S_CS_UNIT_EX_PARA*SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetTextureNodeEx(int nIndex)
{
	if (nIndex >= m_pTextureExCaches.size())
	{
		return NULL;
	}

	return m_pTextureExCaches.at(nIndex);
}

//------------------------------------------------------------------
// @Function:	 AddFont()
// @Purpose: CSakuraResourceManager添加字体资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::AddFont(CUFont * pFont)
{
	for (auto iter = m_pFontCaches.begin(); iter != m_pFontCaches.end(); ++iter)
	{
		size_t nLen = 0;
		nLen = wcslen(pFont->strFontName);
		
		if (0 == _wcsnicmp((*iter)->strFontName, pFont->strFontName, nLen) && (*iter)->nFontSize == pFont->nFontSize)
		{
			return (iter - m_pFontCaches.begin());
		}

	}

	CUFont* pNewFont = new CUFont();
	if (pNewFont == NULL)
	{
		return -1;
	}

	memset(pNewFont, 0, sizeof(pNewFont));
	wcscpy_s(pNewFont->strFontName, MAX_PATH, pFont->strFontName);
	pNewFont->nFontSize = pFont->nFontSize;
	m_pFontCaches.push_back(pNewFont);

	return (m_pFontCaches.size() - 1);
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraResourceManager添加纹理资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::AddTexture(S_CS_UNIT_PARA* pTexture)
{
	S_CS_UNIT_PARA* pNewTexture = new S_CS_UNIT_PARA();
	if (pNewTexture == NULL)
	{
		return -1;
	}

	memset(pNewTexture, 0, sizeof(pNewTexture));
	pNewTexture->nTextureWidth = pTexture->nTextureWidth;
	pNewTexture->nTextureHeight = pTexture->nTextureHeight;
	pNewTexture->nScreenWidth = pTexture->nScreenWidth;
	pNewTexture->nScreenHeight = pTexture->nScreenHeight;
	pNewTexture->fUnitAlpha = pTexture->fUnitAlpha;
	pNewTexture->pTextureStr = pTexture->pTextureStr;
	pNewTexture->rcUnit.left = pTexture->rcUnit.left;
	pNewTexture->rcUnit.right = pTexture->rcUnit.right;
	pNewTexture->rcUnit.top = pTexture->rcUnit.top;
	pNewTexture->rcUnit.bottom = pTexture->rcUnit.bottom;
	pNewTexture->rcUnitTex.left = pTexture->rcUnitTex.left;
	pNewTexture->rcUnitTex.right = pTexture->rcUnitTex.right;
	pNewTexture->rcUnitTex.top = pTexture->rcUnitTex.top;
	pNewTexture->rcUnitTex.bottom = pTexture->rcUnitTex.bottom;
	memcpy_s(&(pNewTexture->sCoordsTransformPara), sizeof(pNewTexture->sCoordsTransformPara), &(pTexture->sCoordsTransformPara), sizeof(pTexture->sCoordsTransformPara));
	m_pTextureCaches.push_back(pNewTexture);

	return (m_pTextureCaches.size() - 1);
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraResourceManager添加纹理资源Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::AddTexture(S_CS_UNIT_EX_PARA* pTexture)
{
	S_CS_UNIT_EX_PARA* pNewTexture = new S_CS_UNIT_EX_PARA();
	if (pNewTexture == NULL)
	{
		return -1;
	}

	memset(pNewTexture, 0, sizeof(pNewTexture));
	pNewTexture->nTextureWidth = pTexture->nTextureWidth;
	pNewTexture->nTextureHeight = pTexture->nTextureHeight;
	pNewTexture->nScreenWidth = pTexture->nScreenWidth;
	pNewTexture->nScreenHeight = pTexture->nScreenHeight;
	pNewTexture->fUnitAlpha = pTexture->fUnitAlpha;
	pNewTexture->pTextureArr = pTexture->pTextureArr;
	pNewTexture->nTextureArrSize = pTexture->nTextureArrSize;
	pNewTexture->rcUnit.left = pTexture->rcUnit.left;
	pNewTexture->rcUnit.right = pTexture->rcUnit.right;
	pNewTexture->rcUnit.top = pTexture->rcUnit.top;
	pNewTexture->rcUnit.bottom = pTexture->rcUnit.bottom;
	pNewTexture->rcUnitTex.left = pTexture->rcUnitTex.left;
	pNewTexture->rcUnitTex.right = pTexture->rcUnitTex.right;
	pNewTexture->rcUnitTex.top = pTexture->rcUnitTex.top;
	pNewTexture->rcUnitTex.bottom = pTexture->rcUnitTex.bottom;
	memcpy_s(&(pNewTexture->sCoordsTransformPara), sizeof(pNewTexture->sCoordsTransformPara), &(pTexture->sCoordsTransformPara), sizeof(pTexture->sCoordsTransformPara));
	m_pTextureExCaches.push_back(pNewTexture);

	return (m_pTextureExCaches.size() - 1);
}
