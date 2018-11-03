/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraResourceManager.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraResourceManager.h"

// SakuraGUI ��Դ������(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraResourceManager()
// @Purpose: CSakuraResourceManager���캯��
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
// @Purpose: CSakuraResourceManager��������
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
// @Purpose: CSakuraResourceManager��Ϣ������
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
// @Purpose: CSakuraResourceManager��ʼ��
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
// @Purpose: CSakuraResourceManager����
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
// @Purpose: CSakuraResourceManager��ȡ�豸�ӿ�ָ��
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
// @Purpose: CSakuraResourceManager��ȡ����ڵ�
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
// @Purpose: CSakuraResourceManager��ȡ����ڵ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUUint *SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetTextureNode(int nIndex)
{
	if (nIndex >= m_pTextureCaches.size())
	{
		return NULL;
	}

	return m_pTextureCaches.at(nIndex);
}

//------------------------------------------------------------------
// @Function:	 GetTextureNodeEx()
// @Purpose: CSakuraResourceManager��ȡ����ڵ�Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CUUintEx *SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::GetTextureNodeEx(int nIndex)
{
	if (nIndex >= m_pTextureExCaches.size())
	{
		return NULL;
	}

	return m_pTextureExCaches.at(nIndex);
}

//------------------------------------------------------------------
// @Function:	 AddFont()
// @Purpose: CSakuraResourceManager���������Դ
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
// @Purpose: CSakuraResourceManager���������Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::AddTexture(CUUint * pTexture)
{
	CUUint* pNewTexture = new CUUint();
	if (pNewTexture == NULL)
	{
		return -1;
	}

	memset(pNewTexture, 0, sizeof(pNewTexture));
	memcpy_s(pNewTexture, sizeof(pNewTexture), pTexture, sizeof(CUUint));
	m_pTextureCaches.push_back(pNewTexture);

	return (m_pTextureCaches.size() - 1);
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraResourceManager���������ԴEx
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURARESOURCEMANAGER_CALLMETHOD CSakuraResourceManager::AddTexture(CUUintEx * pTexture)
{
	CUUintEx* pNewTexture = new CUUintEx();
	if (pNewTexture == NULL)
	{
		return -1;
	}

	memset(pNewTexture, 0, sizeof(pNewTexture));
	memcpy_s(pNewTexture, sizeof(pNewTexture), pTexture, sizeof(CUUintEx));
	m_pTextureExCaches.push_back(pNewTexture);

	return (m_pTextureExCaches.size() - 1);
}
