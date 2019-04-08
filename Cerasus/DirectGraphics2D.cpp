/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectGraphics2D.cpp
* @brief	This Program is DirectGraphics2D DLL Project.
* @author	Alopex/Alice
* @version	v1.26a
* @date		2017-11-02	v1.00a	alopex	Create Project.
* @date		2017-12-08	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-12	v1.22a	alopex	Add Reset Lost Device.
* @date		2018-04-12	v1.23a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.24a	alopex	Add Init Function.
* @date		2018-11-23	v1.25a	alopex	Alter Call Method.
* @date		2019-04-02	v1.26a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectGraphics2D.h"
#include "DirectThreadSafe.h"

// DirectX9 Graphics Class(DirectX9 2D绘制类)

//------------------------------------------------------------------
// @Function:	 DirectGraphics2D()
// @Purpose: DirectGraphics2D构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D() :
	m_pD3D9Device(NULL),
	m_pD3D9VertexBuffer(NULL),
	m_pD3D9IndexBuffer(NULL),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics2D()
// @Purpose: DirectGraphics2D析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics2D::~DirectGraphics2D()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);
	SAFE_RELEASE(m_pD3D9IndexBuffer);
	SAFE_RELEASE(m_pD3D9Texture);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//--------------------------------------------------------------------------
// @Function:	 DirectGraphics2D(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: DirectGraphics2D构造函数
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (绘制设备)
// @Return: None
//--------------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D(IDirect3DDevice9 * pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3D9VertexBuffer(NULL),
	m_pD3D9IndexBuffer(NULL),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//--------------------------------------------------------------------------
// @Function:	 DirectGraphics2D(const DirectGraphics2D & Object)
// @Purpose: DirectGraphics2D拷贝构造函数
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (绘制设备)
// @Return: None
//--------------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D(const DirectGraphics2D & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;					// IDirect3DDevice9接口指针初始化
	m_pD3D9VertexBuffer = Object.m_pD3D9VertexBuffer;		// IDirect3DVertexBuffer9接口指针初始化(NULL)
	m_pD3D9IndexBuffer = Object.m_pD3D9IndexBuffer;			// IDirect3DIndexBuffer9接口指针初始化(NULL)
	m_pD3D9Texture = Object.m_pD3D9Texture;					// IDirect3DTexture9接口指针初始化(NULL)
}

//--------------------------------------------------------------------------
// @Function:	 operator=(const DirectGraphics2D & Object)
// @Purpose: DirectGraphics2D拷贝构造函数
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (绘制设备)
// @Return: None
//--------------------------------------------------------------------------
const DirectGraphics2D & DirectGraphics2D::operator=(const DirectGraphics2D & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;					// IDirect3DDevice9接口指针初始化
		m_pD3D9VertexBuffer = Object.m_pD3D9VertexBuffer;		// IDirect3DVertexBuffer9接口指针初始化(NULL)
		m_pD3D9IndexBuffer = Object.m_pD3D9IndexBuffer;			// IDirect3DIndexBuffer9接口指针初始化(NULL)
		m_pD3D9Texture = Object.m_pD3D9Texture;					// IDirect3DTexture9接口指针初始化(NULL)
	}

	return *this;
}

//-----------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: DirectGraphics2D获取设备接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
IDirect3DDevice9 *DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//-----------------------------------------------------------------------
// @Function:	 GetVertexBuffer()
// @Purpose: DirectGraphics2D获取顶点缓冲接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
IDirect3DVertexBuffer9 *DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::GetVertexBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9VertexBuffer;
}

//-----------------------------------------------------------------------
// @Function:	 GetIndexBuffer()
// @Purpose: DirectGraphics2D获取索引缓冲接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
IDirect3DIndexBuffer9 *DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::GetIndexBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9IndexBuffer;
}

//-----------------------------------------------------------------------
// @Function:	 GetTexture()
// @Purpose: DirectGraphics2D获取纹理接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
IDirect3DTexture9 *DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::GetTexture() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Texture;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Create(int nPlane)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: int nPlane	//平面个数
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Create(int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: int nPlane				//平面个数
// @Para: LPCWSTR lpszStrTexture	//纹理路径
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//顶点类型
// @Para: int nPlane					//平面个数
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//顶点类型
// @Para: int nPlane					//平面个数
// @Para: LPCWSTR lpszStrTexture		//纹理路径
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex2D_Type_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateBase(UINT nCount)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: UINT nCount					//平面个数
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateBase(UINT nCount)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateTexture(UINT nCount, LPCWSTR pString)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: UINT nCount					//平面个数
// @Para: LPCWSTR pString				//纹理路径
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateTexture(UINT nCount, LPCWSTR pString)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, pString, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateSpecularTexture(UINT nCount, LPCWSTR pString)
// @Purpose: DirectGraphics2D初始化
// @Since: v1.00a
// @Para: UINT nCount					//平面个数
// @Para: LPCWSTR pString				//纹理路径
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateSpecularTexture(UINT nCount, LPCWSTR pString)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, pString, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: DirectGraphics2D重置(丢失设备)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(成功:S_OK, 失败:E_FAIL)
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Reset()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		//IDirect3DVertexBuffer9接口指针释放
	SAFE_RELEASE(m_pD3D9IndexBuffer);		//IDirect3DIndexBuffer9接口指针释放
	SAFE_RELEASE(m_pD3D9Texture);			//IDirect3DTexture9接口指针释放
	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX2D_BASE * VertexArray, int nSize)
// @Purpose: DirectGraphics2D填充顶点(Base类型)
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray		//填充顶点数组地址
// @Para: int nSize						//填充顶点数组长度
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertex(S_DX_VERTEX2D_BASE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_BASE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX2D_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics2D填充顶点(Texture类型)
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray	//填充顶点数组地址
// @Para: int nSize						//填充顶点数组长度
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertex(S_DX_VERTEX2D_TEXTURE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX2D_SPECULAR_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics2D填充顶点(Specular类型)
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray		//填充顶点数组地址
// @Para: int nSize									//填充顶点数组长度
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertex(S_DX_VERTEX2D_SPECULAR_TEXTURE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//--------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
// @Purpose: DirectGraphics2D填充顶点(枚举类型)
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType						//顶点类型
// @Para: LPVOID VertexArray								//填充顶点数组地址
// @Para: int nPlane										//填充平面个数
// @Return: None
//--------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_BASE* pVertices2DBase = NULL;
	S_DX_VERTEX2D_TEXTURE* pVertices2DTexture = NULL;
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices2DSpecularTexture = NULL;

	//填充顶点缓存
	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DBase, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DBase + i) = *((S_DX_VERTEX2D_BASE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DTexture + i) = *((S_DX_VERTEX2D_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DSpecularTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DSpecularTexture + i) = *((S_DX_VERTEX2D_SPECULAR_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}

}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingIndex(int nPlane)
// @Purpose: DirectGraphics2D填充索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//--------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingIndex(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充索引缓存
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX2D_BASE * VertexArray, int nSize)
// @Purpose: DirectGraphics2D填充顶点索引
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray					//填充顶点数组地址
// @Para: int nPlane								//填充平面个数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_BASE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX2D_BASE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// 填充索引缓存
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX2D_TEXTURE * VertexArray, int nPlane)
// @Purpose: DirectGraphics2D填充顶点索引
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray				//填充顶点数组地址
// @Para: int nPlane								//填充平面个数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX2D_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// 填充索引缓存
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX2D_SPECULAR_TEXTURE * VertexArray, int nPlane)
// @Purpose: DirectGraphics2D填充顶点索引
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray				//填充顶点数组地址
// @Para: int nPlane										//填充平面个数
// @Return: None
//------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_SPECULAR_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// 填充索引缓存
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
// @Purpose: DirectGraphics2D填充顶点索引
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType						//顶点类型
// @Para: LPVOID VertexArray								//填充顶点数组地址
// @Para: int nPlane										//填充平面个数
// @Return: None
//---------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_BASE* pVertices2DBase = NULL;
	S_DX_VERTEX2D_TEXTURE* pVertices2DTexture = NULL;
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices2DSpecularTexture = NULL;

	// 填充顶点缓存
	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DBase, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DBase + i) = *((S_DX_VERTEX2D_BASE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DTexture + i) = *((S_DX_VERTEX2D_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DSpecularTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DSpecularTexture + i) = *((S_DX_VERTEX2D_SPECULAR_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}

	// 填充索引缓存
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------
// @Function:	 AlphaEnable()
// @Purpose: DirectGraphics2D开启Alpha混合
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha混合开启
}

//---------------------------------------------------------------
// @Function:	 AlphaDisable()
// @Purpose: DirectGraphics2D关闭Alpha混合
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha混合关闭
}

//---------------------------------------------------------------
// @Function:	 AlphaMix()
// @Purpose: DirectGraphics2D设置渲染状态(Alpha融合)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaMix()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 渲染模式:Alpha混合设置
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha混合开启
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					// Alpha混合模式:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 渲染模式:纹理混合设置
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);		// D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
}

//---------------------------------------------------------------
// @Function:	 ColorMix()
// @Purpose: DirectGraphics2D设置渲染状态(Color融合)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::ColorMix()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 渲染模式:纹理混合设置
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------
// @Function:	 ColorMix(D3DXCOLOR MixColor)
// @Purpose: DirectGraphics2D设置渲染状态(Color融合)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::ColorMix(D3DXCOLOR MixColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 渲染模式:纹理混合设置
	m_pD3D9Device->SetRenderState(D3DRS_TEXTUREFACTOR, MixColor);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
}

//-----------------------------------------------------------
// @Function:	 Setting()
// @Purpose: DirectGraphics2D设置渲染状态
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Setting()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 渲染模式:Alpha混合设置
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha混合开启
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					// Alpha混合模式:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 渲染模式:纹理混合设置
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);		// D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics2D渲染绘制
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//顶点枚举类型
// @Para: int nPlane					//平面数量
// @Para: bool bIsTexture				//是否渲染纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics2D渲染绘制
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//顶点枚举类型
// @Para: int nStartIndex				//开始索引
// @Para: int nPlane					//平面数量
// @Para: bool bIsTexture				//是否渲染纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
// @Purpose: DirectGraphics2D渲染绘制
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//顶点枚举类型
// @Para: int nStartIndex				//开始索引
// @Para: int nPlane					//平面数量
// @Para: bool bIsTexture				//是否渲染纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}

}
