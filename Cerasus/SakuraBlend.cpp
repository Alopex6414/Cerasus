/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraBlend.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraBlend.h"

// SakuraGUI �ؼ�����&������Ⱦ(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::CSakuraBlendFont()
{
	m_pD3D9Device = NULL;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraBlendFont()
// @Purpose: CSakuraBlendFont��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::~CSakuraBlendFont()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_States[i]);
	}

	SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont���캯��(����+1)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::CSakuraBlendFont(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraBlendFont��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURABLEND_CALLMETHOD CSakuraBlendFont::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetStates()
// @Purpose: CSakuraBlendFont��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont *SAKURABLEND_CALLMETHOD CSakuraBlendFont::GetCurrent() const
{
	return m_Current;
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraBlendFont��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::OnCreate(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 AddFont()
// @Purpose: CSakuraBlendFont�������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendFont::AddFont(SAKURA_CONTROL_STATE eType, LPWSTR strFontName, int nFontSize)
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

	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = pFontNode;
	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CSakuraBlendFont��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::Blend(SAKURA_CONTROL_STATE eType, LPCWSTR pString, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	if (m_States[eType] == NULL)
	{
		return;
	}

	m_States[eType]->DirectFontGetFont()->DrawTextW(NULL, pString, -1, pRect, Format, Color);
	m_Current = m_States[eType];
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::CSakuraBlendTexture()
{
	m_pD3D9Device = NULL;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::~CSakuraBlendTexture()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_States[i]);
	}

	SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture���캯��(����+1)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::CSakuraBlendTexture(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraBlendTexture��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURABLEND_CALLMETHOD CSakuraBlendTexture::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetCurrent()
// @Purpose: CSakuraBlendTexture��ȡ��ǰ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit *SAKURABLEND_CALLMETHOD CSakuraBlendTexture::GetCurrent() const
{
	return m_Current;
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraBlendTexture��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::OnCreate(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraBlendTexture�������(�ļ�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendTexture::AddTexture(SAKURA_CONTROL_STATE eType, CUUint sUnit)
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

	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = pTextureNode;
	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraBlendTexture�������(�ڴ浼��)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendTexture::AddTexture(SAKURA_CONTROL_STATE eType, CUUintEx sUnit)
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

	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = pTextureNode;
	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CSakuraBlendTexture��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::Blend(SAKURA_CONTROL_STATE eType)
{
	if (m_States[eType] == NULL)
	{
		return;
	}

	m_States[eType]->CCerasusUnitPaddingVertexAndIndex();
	m_States[eType]->CCerasusUnitMatrixTransform();
	m_States[eType]->CCerasusUnitSetAlphaBlendEnable();
	m_States[eType]->CCerasusUnitSetRenderState();
	m_States[eType]->CCerasusUnitRender();
	m_States[eType]->CCerasusUnitSetAlphaBlendDisable();
}
