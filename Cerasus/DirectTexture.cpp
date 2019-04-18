/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectTexture.cpp
* @brief	This File is DirectTexture DLL Project.
* @author	Alopex/Alice
* @version	v1.17a
* @date		2017-12-10	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-07-01	v1.14a	alopex	Modify Thread Safe Class.
* @date		2018-07-09	v1.15a	alopex	Add 32 Channel Texture.
* @date		2018-11-23	v1.16a	alopex	Alter Call Method.
* @date		2019-04-18	v1.17a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectTexture.h"
#include "DirectThreadSafe.h"

// DirectTexture Class (DirectX 绘制渲染纹理)

//------------------------------------------------------------------
// @Function:	 DirectTexture()
// @Purpose: DirectTexture构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectTexture::DirectTexture() :
	m_pD3D9Device(NULL),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectTexture()
// @Purpose: DirectTexture析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectTexture::~DirectTexture()
{
	SAFE_RELEASE(m_pD3D9Texture);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//-----------------------------------------------------------------------
// @Function:	 DirectTexture(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: DirectTexture构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
DirectTexture::DirectTexture(IDirect3DDevice9* pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//-----------------------------------------------------------------------
// @Function:	 DirectTexture(const DirectTexture& Object)
// @Purpose: DirectTexture拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
DirectTexture::DirectTexture(const DirectTexture& Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;
	m_pD3D9Texture = Object.m_pD3D9Texture;
}

//-----------------------------------------------------------------------
// @Function:	 operator=(const DirectTexture& Object)
// @Purpose: DirectTexture拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
const DirectTexture& DirectTexture::operator=(const DirectTexture& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;
		m_pD3D9Texture = Object.m_pD3D9Texture;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice() const
// @Purpose: DirectTexture获取D3D9绘制设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9* DIRECTTEXTURE_CALLMETHOD DirectTexture::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetTexture() const
// @Purpose: DirectTexture获取D3D9绘制纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DTexture9* DIRECTTEXTURE_CALLMETHOD DirectTexture::GetTexture() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Texture;
}

//------------------------------------------------------------------
// @Function:	 Create(LPWSTR lpszTexture)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPWSTR lpszTexture	//D3D9纹理路径
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::Create(LPWSTR lpszTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszTexture, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------
// @Function:	 Create(LPCVOID lpSrcData, UINT nSrcDataSize)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPCVOID lpSrcData			//纹理内存数组地址
// @Para: UINT nSrcDataSize			//纹理内存数组大小
// @Return: None
//-----------------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::Create(LPCVOID lpSrcData, UINT nSrcDataSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileInMemory(m_pD3D9Device, lpSrcData, nSrcDataSize, &m_pD3D9Texture));

	return S_OK;
}

//----------------------------------------------------------------------------------------
// @Function:	 CreateEx(LPWSTR lpszTexture, UINT nWidth, UINT nHeight)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPWSTR lpszTexture	//D3D9纹理路径
// @Para: UINT nWidth			//纹理宽度(2^n)
// @Para: UINT nHeight			//纹理高度(2^n)
// @Return: None
//----------------------------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::CreateEx(LPWSTR lpszTexture, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileEx(m_pD3D9Device, lpszTexture, nWidth, nHeight, 0, 0, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_XRGB(0, 0, 0), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//----------------------------------------------------------------------------------------------------------
// @Function:	 CreateEx(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPWSTR lpszTexture	//D3D9纹理路径
// @Para: UINT nWidth			//纹理宽度(2^n)
// @Para: UINT nHeight			//纹理高度(2^n)
// @Return: None
//----------------------------------------------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::CreateEx(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, lpSrcData, nSrcDataSize, nWidth, nHeight, 0, 0, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_XRGB(0, 0, 0), NULL, NULL, &m_pD3D9Texture));

	return	S_OK;
}

//----------------------------------------------------------------------------------------
// @Function:	 CreateEx32(LPWSTR lpszTexture, UINT nWidth, UINT nHeight)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPWSTR lpszTexture	//D3D9纹理路径
// @Para: UINT nWidth			//纹理宽度(2^n)
// @Para: UINT nHeight			//纹理高度(2^n)
// @Return: None
//----------------------------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::CreateEx32(LPWSTR lpszTexture, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileEx(m_pD3D9Device, lpszTexture, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//----------------------------------------------------------------------------------------------------------
// @Function:	 CreateEx32(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectTexture加载纹理
// @Since: v1.00a
// @Para: LPWSTR lpszTexture	//D3D9纹理路径
// @Para: UINT nWidth			//纹理宽度(2^n)
// @Para: UINT nHeight			//纹理高度(2^n)
// @Return: None
//----------------------------------------------------------------------------------------------------------
HRESULT DIRECTTEXTURE_CALLMETHOD DirectTexture::CreateEx32(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, lpSrcData, nSrcDataSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return	S_OK;
}

//------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: DirectTexture重置D3D9绘制纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTTEXTURE_CALLMETHOD DirectTexture::Reset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	SAFE_RELEASE(m_pD3D9Texture);
}

//------------------------------------------------------------------
// @Function:	 Select()
// @Purpose: DirectTexture重置D3D9绘制纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTTEXTURE_CALLMETHOD DirectTexture::Select()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
}