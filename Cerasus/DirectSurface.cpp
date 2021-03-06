/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectSurface.cpp
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Alice
* @version	v1.16a
* @date		2017-12-09	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-06-23	v1.14a	alopex	Repair Bug.
* @date		2018-11-23	v1.15a	alopex	Alter Call Method.
* @date		2019-04-16	v1.16a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectSurface.h"
#include "DirectThreadSafe.h"

// DriectSurface Class (DirectX 绘制渲染表面)

//------------------------------------------------------------------
// @Function:	 DirectSurface()
// @Purpose: DirectSurface构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSurface::DirectSurface() :
	m_pD3D9Device(NULL),
	m_pD3D9Surface(NULL),
	m_pD3D9BackSurface(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectSurface()
// @Purpose: DirectSurface析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSurface::~DirectSurface()
{
	SAFE_RELEASE(m_pD3D9Surface);
	SAFE_RELEASE(m_pD3D9BackSurface);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurface(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: DirectSurface构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
DirectSurface::DirectSurface(IDirect3DDevice9* pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3D9Surface(NULL),
	m_pD3D9BackSurface(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectSurface(const DirectSurface& Object)
// @Purpose: DirectSurface构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSurface::DirectSurface(const DirectSurface& Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;
	m_pD3D9Surface = Object.m_pD3D9Surface;
	m_pD3D9BackSurface = Object.m_pD3D9BackSurface;
}

//------------------------------------------------------------------
// @Function:	 operator=(const DirectSurface& Object)
// @Purpose: DirectSurface构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectSurface& DirectSurface::operator=(const DirectSurface& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;
		m_pD3D9Surface = Object.m_pD3D9Surface;
		m_pD3D9BackSurface = Object.m_pD3D9BackSurface;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice() const
// @Purpose: DirectSurface获取D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9* DIRECTSURFACE_CALLMETHOD DirectSurface::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetSurface() const
// @Purpose: DirectSurface获取D3D9表面
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DSurface9* DIRECTSURFACE_CALLMETHOD DirectSurface::GetSurface() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Surface;
}

//-----------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: DirectSurface初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
HRESULT DIRECTSURFACE_CALLMETHOD DirectSurface::Create()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DSURFACE_DESC Desc;

	VERIFY(m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &m_pD3D9BackSurface));												// 获取后台缓冲表面
	VERIFY(m_pD3D9BackSurface->GetDesc(&Desc));																									// 获取Desc
	VERIFY(m_pD3D9Device->CreateOffscreenPlainSurface(Desc.Width, Desc.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pD3D9Surface, NULL));		// 创建离屏表面

	return S_OK;
}

//------------------------------------------------------------------------------------
// @Function:	 Load(LPWSTR lpszSurface, const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface导入纹理
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//------------------------------------------------------------------------------------
HRESULT DIRECTSURFACE_CALLMETHOD DirectSurface::Load(LPWSTR lpszSurface, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromFile(m_pD3D9Surface, NULL, pDestRect, lpszSurface, pSrcRect, D3DX_FILTER_NONE, NULL, NULL));

	return S_OK;
}

//---------------------------------------------------------------------------------------------
// @Function:	 Load(IDirect3DSurface9* pSurface, const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface导入纹理
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//---------------------------------------------------------------------------------------------
HRESULT DIRECTSURFACE_CALLMETHOD DirectSurface::Load(IDirect3DSurface9* pSurface, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromSurface(m_pD3D9Surface, NULL, pDestRect, pSurface, NULL, pSrcRect, D3DX_FILTER_NONE, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------------
// @Function:	 Load(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface导入纹理
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//-----------------------------------------------------------------------------------------------------
HRESULT DIRECTSURFACE_CALLMETHOD DirectSurface::Load(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromFileInMemory(m_pD3D9Surface, NULL, pDestRect, lpcszArray, nArraySize, pSrcRect, D3DX_FILTER_NONE, NULL, NULL));

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------------
// @Function:	 Load(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface导入纹理
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//-------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTSURFACE_CALLMETHOD DirectSurface::Load(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromMemory(m_pD3D9Surface, NULL, pDestRect, lpcszArray, Format, nPitch, NULL, pSrcRect, D3DX_FILTER_NONE, NULL));

	return S_OK;
}

//-------------------------------------------------------------------------------
// @Function:	 Render(const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface渲染
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTSURFACE_CALLMETHOD DirectSurface::Render(const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->StretchRect(m_pD3D9Surface, pDestRect, m_pD3D9BackSurface, pSrcRect, D3DTEXF_NONE);
}

//-----------------------------------------------------------------------
// @Function:	 Render(DWORD dwColor)
// @Purpose: DirectSurface渲染
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//纹理路径
// @Return: None
//-----------------------------------------------------------------------
void DIRECTSURFACE_CALLMETHOD DirectSurface::Render(DWORD dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DSURFACE_DESC Desc;
	D3DLOCKED_RECT Rect;

	m_pD3D9Surface->GetDesc(&Desc);
	m_pD3D9Surface->LockRect(&Rect, 0, 0);

	DWORD* Data = (DWORD*)Rect.pBits;

	for (UINT i = 0; i < Desc.Height; ++i)
	{
		for (UINT j = 0; j < Desc.Width; ++j)
		{
			int index = i * Rect.Pitch / 4 + j;
			Data[index] = dwColor;
		}
	}

	m_pD3D9Surface->UnlockRect();
	m_pD3D9Device->StretchRect(m_pD3D9Surface, NULL, m_pD3D9BackSurface, NULL, D3DTEXF_NONE);
}

//---------------------------------------------------------------------------------------------------
// @Function:	 RenderYUV(UCHAR* pArrayY, UCHAR* pArrayU, UCHAR* pArrayV, UINT nWidth, UINT nHeight)
// @Purpose: DirectSurface渲染
// @Since: v1.00a
// @Para: UCHAR* pArrayY		//Y数组地址
// @Para: UCHAR* pArrayU		//U数组地址
// @Para: UCHAR* pArrayV		//V数组地址
// @Para: UINT nWidth			//窗口宽度
// @Para: UINT nHeight			//窗口高度
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTSURFACE_CALLMETHOD DirectSurface::RenderYUV(UCHAR* pArrayY, UCHAR* pArrayU, UCHAR* pArrayV, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DSURFACE_DESC Desc;
	D3DLOCKED_RECT Rect;

	m_pD3D9Surface->GetDesc(&Desc);
	m_pD3D9Surface->LockRect(&Rect, 0, 0);

	for (UINT i = 0; i < nHeight; ++i)
	{
		memcpy((BYTE*)(Rect.pBits) + i * Rect.Pitch, (BYTE*)pArrayY + i * nWidth, nWidth);
	}
	for (UINT i = 0; i < nHeight / 2; ++i)
	{
		memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * nHeight + (Rect.Pitch / 2) * i, (BYTE*)pArrayV + i * nWidth / 2, nWidth / 2);
	}
	for (UINT i = 0; i < nHeight / 2; ++i)
	{
		memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * nHeight + Rect.Pitch * nHeight / 4 + (Rect.Pitch / 2) * i, (BYTE*)pArrayU + i * nWidth / 2, nWidth / 2);
	}

	m_pD3D9Surface->UnlockRect();
	m_pD3D9Device->StretchRect(m_pD3D9Surface, NULL, m_pD3D9BackSurface, NULL, D3DTEXF_NONE);
}
