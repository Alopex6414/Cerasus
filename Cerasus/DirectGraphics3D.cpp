/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectGraphics3D.cpp
* @brief	This File is DirectGraphics3D DLL Project.
* @author	Alopex/Alice
* @version	v1.32a
* @date		2017-11-29	v1.00a	alopex	Create Project.
* @date		2017-12-03	v1.01a	alopex	Modify Bug.
* @date		2017-12-08	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.24a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-12	v1.25a	alopex	Add Get & Set & Reset Function.
* @date		2018-04-12	v1.26a	alopex	Add Macro Call Mode.
* @date		2018-06-21	v1.27a	alopex	Add Version Infomation.
* @date		2018-06-21	v1.28a	alopex	Add Transform Function.
* @date		2018-06-24	v1.29a	alopex	Repair Bugs.
* @date		2018-06-24	v1.30a	alopex	Repair Texture Alpha Channel.
* @date		2018-11-23	v1.31a	alopex	Alter Call Method.
* @date		2019-03-31	v1.32a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectGraphics3D.h"
#include "DirectThreadSafe.h"

// DirectX9 Graphics Class(DirectX9 3D绘制类)

//------------------------------------------------------------------
// @Function:	 DirectGraphics3D()
// @Purpose: DirectGraphics3D构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::DirectGraphics3D() :
	m_pD3D9Device(NULL),
	m_pD3D9VertexBuffer(NULL),
	m_pD3D9IndexBuffer(NULL),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics3D()
// @Purpose: DirectGraphics3D析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::~DirectGraphics3D()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);
	SAFE_RELEASE(m_pD3D9IndexBuffer);
	SAFE_RELEASE(m_pD3D9Texture);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics3D(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectGraphics3D构造函数
// @Since: v1.00a
// @Para: LPDIRECT3DDEVICE9 pD3D9Device		//IDirect3DDevice9接口指针
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::DirectGraphics3D(IDirect3DDevice9 * pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3D9VertexBuffer(NULL),
	m_pD3D9IndexBuffer(NULL),
	m_pD3D9Texture(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics3D()
// @Purpose: DirectGraphics3D拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D::DirectGraphics3D(const DirectGraphics3D & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;					// IDirect3DDevice9接口指针初始化
	m_pD3D9VertexBuffer = Object.m_pD3D9VertexBuffer;		// IDirect3DVertexBuffer9接口指针初始化(NULL)
	m_pD3D9IndexBuffer = Object.m_pD3D9IndexBuffer;			// IDirect3DIndexBuffer9接口指针初始化(NULL)
	m_pD3D9Texture = Object.m_pD3D9Texture;					// IDirect3DTexture9接口指针初始化(NULL)
}

//------------------------------------------------------------------
// @Function:	 operator=()
// @Purpose: DirectGraphics3D运算符重载
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectGraphics3D & DirectGraphics3D::operator=(const DirectGraphics3D & Object)
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

//-------------------------------------------------------------------------------
// @Function:	 IDirect3DDevice9* GetDevice() const
// @Purpose: DirectGraphics3D获取D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DDevice9*
//-------------------------------------------------------------------------------
IDirect3DDevice9 *DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//-------------------------------------------------------------------------------
// @Function:	 IDirect3DVertexBuffer9* GetVertexBuffer() const
// @Purpose: DirectGraphics3D获取D3D9顶点缓存
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DVertexBuffer9*
//-------------------------------------------------------------------------------
IDirect3DVertexBuffer9 *DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::GetVertexBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9VertexBuffer;
}

//-------------------------------------------------------------------------------
// @Function:	 IDirect3DIndexBuffer9* GetIndexBuffer() const
// @Purpose: DirectGraphics3D获取D3D9索引缓存
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DIndexBuffer9*
//-------------------------------------------------------------------------------
IDirect3DIndexBuffer9 *DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::GetIndexBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9IndexBuffer;
}

//-------------------------------------------------------------------------------
// @Function:	 IDirect3DTexture9* GetTexture() const
// @Purpose: DirectGraphics3D获取D3D9纹理
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DTexture9*
//-------------------------------------------------------------------------------
IDirect3DTexture9 *DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::GetTexture() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Texture;
}

//-------------------------------------------------------------------------------
// @Function:	 Create(int nPlane)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: int nPlane	//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Base)
// @Return: None
//-------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_BASE), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//------------------------------------------------------------------------------------------------
// @Function:	 Create(int nPlane, LPCSTR lpszStrTexture)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: int nPlane					//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Normal)
// @Para: LPCWSTR lpszStrTexture		//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_TEXTURE), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));

	return S_OK;
}

//------------------------------------------------------------------------------------------------
// @Function:	 Create(Vertex3DType eVertex3DType, int nPlane)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//顶点类型(枚举)
// @Para: int nPlane					//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Normal)
// @Return: None
//------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_BASE), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_TEXTURE), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL), 0, D3DFVF_VERTEX3D_NORMAL, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
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
// @Function:	 Create(Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//顶点类型(枚举)
// @Para: int nPlane					//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Normal)
// @Para: LPCWSTR lpszStrTexture		//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_BASE), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_TEXTURE), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL), 0, D3DFVF_VERTEX3D_NORMAL, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
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

//-------------------------------------------------------------------------------------------------------
// @Function:	 Create(D3DPOOL ePool, DWORD Usage, Vertex3DType eVertex3DType, int nPlane)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: D3DPOOL ePool					//D3D内存池类型
// @Para: DWORD Usage					//D3D附加属性
// @Para: Vertex3DType eVertex3DType	//顶点类型(枚举)
// @Para: int nPlane					//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Normal)
// @Return: None
//--------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(D3DPOOL ePool, DWORD Usage, E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_BASE), Usage, D3DFVF_VERTEX3D_BASE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_TEXTURE), Usage, D3DFVF_VERTEX3D_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL), Usage, D3DFVF_VERTEX3D_NORMAL, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), Usage, D3DFVF_VERTEX3D_NORMAL_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), Usage, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Create(D3DPOOL ePool, DWORD Usage, Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: D3DPOOL ePool					//D3D内存池类型
// @Para: DWORD Usage					//D3D附加属性
// @Para: Vertex3DType eVertex3DType	//顶点类型(枚举)
// @Para: int nPlane					//绘制平面数(立方体6个平面)(以此类推...)(Vertex类型:Normal)
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Create(D3DPOOL ePool, DWORD Usage, E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_BASE), Usage, D3DFVF_VERTEX3D_BASE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_TEXTURE), Usage, D3DFVF_VERTEX3D_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL), Usage, D3DFVF_VERTEX3D_NORMAL, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex3D_Type_Normal_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), Usage, D3DFVF_VERTEX3D_NORMAL_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面纹理
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		// VertexBuffer创建顶点缓存
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), Usage, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, ePool, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer创建索引缓存
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), Usage, D3DFMT_INDEX16, ePool, &m_pD3D9IndexBuffer, NULL));
		// Texture创建平面ee纹理
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
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateBase(UINT nCount)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_BASE), 0, D3DFVF_VERTEX3D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_TEXTURE), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileExW(m_pD3D9Device, pStr, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_TEXTURE), 0, D3DFVF_VERTEX3D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, pData, nSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateNormal(UINT nCount)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateNormal(UINT nCount)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_NORMAL), 0, D3DFVF_VERTEX3D_NORMAL, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateNormalTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateNormalTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileExW(m_pD3D9Device, pStr, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateNormalTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateNormalTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, pData, nSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateNormalSpecularTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateNormalSpecularTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileExW(m_pD3D9Device, pStr, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateNormalSpecularTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectGraphics3D初始化
// @Since: v1.00a
// @Para: UINT nCount					//绘制平面数(立方体6个平面)
// @Para: LPCWSTR pStr					//平面纹理路径(eg:L"Res\\title.png")
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::CreateNormalSpecularTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer创建顶点缓存
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer创建索引缓存
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture创建平面纹理
	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, pData, nSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pD3D9Texture));

	return S_OK;
}

//----------------------------------------------------------------------------------------------
// @Function:	 HRESULT Reset()
// @Purpose: DirectGraphics3D重置(丢失设备)
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Reset()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		// IDirect3DVertexBuffer9接口指针释放
	SAFE_RELEASE(m_pD3D9IndexBuffer);		// IDirect3DIndexBuffer9接口指针释放
	SAFE_RELEASE(m_pD3D9Texture);			// IDirect3DTexture9接口指针释放
	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_SCALE_PARA sScalePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_RotatePara sRotatePara			//伸缩变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_SCALE_PARA sScalePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;									// 世界变换矩阵
	D3DXMATRIX MatrixScale;									// 缩放变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);						// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	// 设置缩放矩阵
	MatrixWorld = MatrixWorld * MatrixScale;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);	// 设置世界变换
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_RotatePara sRotatePara			//旋转变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;						// 旋转变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);					// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);					// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);					// 设置旋转矩阵Z
	MatrixWorld = MatrixWorld * MatrixRotateX * MatrixRotateY * MatrixRotateZ;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_TRANSLATE_PARA sTranslatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//平移变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_TRANSLATE_PARA sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixTranslate;													// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//平移变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixScale;														// 缩放变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;						// 旋转变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	//设置缩放矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);					// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);					// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);					// 设置旋转矩阵Z
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_TRANSLATE_PARA sTranslatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//平移变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_TRANSLATE_PARA sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixScale;														// 缩放变换矩阵
	D3DXMATRIX MatrixTranslate;													// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	// 设置缩放矩阵
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixScale * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_TranslatePara sTranslatePara			//平移变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;						// 旋转变换矩阵
	D3DXMATRIX MatrixTranslate;													// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);					// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);					// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);					// 设置旋转矩阵Z
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_ScalePara sScalePara			//伸缩变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;														// 世界变换矩阵
	D3DXMATRIX MatrixScale;														// 缩放变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;						// 旋转变换矩阵
	D3DXMATRIX MatrixTranslate;													// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);											// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, sScalePara.fScaleZ);	// 设置缩放矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sRotatePara.fRotateX);					// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sRotatePara.fRotateY);					// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sRotatePara.fRotateZ);					// 设置旋转矩阵Z
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);						// 设置世界变换
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 WorldSpaceTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara)
// @Purpose: DirectGraphics3D世界坐标变换
// @Since: v1.00a
// @Para: DG3D_ScalePara sScalePara			//伸缩变换参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::WorldSpaceTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;															// 世界变换矩阵
	D3DXMATRIX MatrixScale;															// 缩放变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;							// 旋转变换矩阵
	D3DXMATRIX MatrixTranslate;														// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);												// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sWorldTransformPara.sScalePara.fScaleX, sWorldTransformPara.sScalePara.fScaleY, sWorldTransformPara.sScalePara.fScaleZ);	// 设置缩放矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sWorldTransformPara.sRotatePara.fRotateX);	// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sWorldTransformPara.sRotatePara.fRotateY);	// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sWorldTransformPara.sRotatePara.fRotateZ);	// 设置旋转矩阵Z
	D3DXMatrixTranslation(&MatrixTranslate, sWorldTransformPara.sTranslatePara.fTranslateX, sWorldTransformPara.sTranslatePara.fTranslateY, sWorldTransformPara.sTranslatePara.fTranslateZ);	//设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);							// 设置世界变换
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewSpaceTransform(D3DXVECTOR3* pvEye)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//摄像机位置(观察者位置)
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewSpaceTransform(D3DXVECTOR3 * pvEye)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixView;
	D3DXVECTOR3 Vector_At(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vector_Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&MatrixView, pvEye, &Vector_At, &Vector_Up);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewSpaceTransform(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvAt)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//摄像机位置(观察者位置)
// @Para: D3DXVECTOR3* pvAt			//物体位置
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewSpaceTransform(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvAt)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixView;
	D3DXVECTOR3 Vector_Up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&MatrixView, pvEye, pvEye, &Vector_Up);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewSpaceTransform(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvAt, D3DXVECTOR3 * pvUp)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//摄像机位置(观察者位置)
// @Para: D3DXVECTOR3* pvAt			//物体位置
// @Para: D3DXVECTOR3* pvUp			//向上向量
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewSpaceTransform(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvAt, D3DXVECTOR3 * pvUp)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, pvEye, pvAt, pvUp);
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewSpaceTransform(S_DX_VIEW_TRANSFORM_PARA sViewTransformPara)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: D3DXVECTOR3* pvEye		//摄像机位置(观察者位置)
// @Para: D3DXVECTOR3* pvAt			//物体位置
// @Para: D3DXVECTOR3* pvUp			//向上向量
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewSpaceTransform(S_DX_VIEW_TRANSFORM_PARA sViewTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, &(sViewTransformPara.vEye), &(sViewTransformPara.vAt), &(sViewTransformPara.vUp));
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PerspectiveTransform(float fovy, float fAspect, float fZn, float fZf)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: DG3D_PrespectiveTransformPara sPrespectiveTransformPara		//投影变换结构体参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PerspectiveTransform(float fovy, float fAspect, float fZn, float fZf)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, fovy, fAspect, fZn, fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PerspectiveTransform(S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: DG3D_PrespectiveTransformPara sPrespectiveTransformPara		//投影变换结构体参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PerspectiveTransform(S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, sPrespectiveTransformPara.fovy, sPrespectiveTransformPara.fAspect, sPrespectiveTransformPara.fZn, sPrespectiveTransformPara.fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewPortTransform(int nUserWidth, int nUserHeight)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				//视口变换结构体参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewPortTransform(int nUserWidth, int nUserHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = nUserWidth;
	ViewPort.Height = nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 ViewPortTransform(S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara)
// @Purpose: DirectGraphics3D视口变换
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				//视口变换结构体参数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::ViewPortTransform(S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = sViewPortTransformPara.nUserWidth;
	ViewPort.Height = sViewPortTransformPara.nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 MatrixTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara, S_DX_VIEW_TRANSFORM_PARA sViewTransformPara, S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara, S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara)
// @Purpose: DirectGraphics3D矩阵变换
// @Since: v1.00a
// @Para: DG3D_ViewPortTransformPara sViewPortTransformPara				
// @Return: None
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::MatrixTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara, S_DX_VIEW_TRANSFORM_PARA sViewTransformPara, S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara, S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;															// 世界变换矩阵
	D3DXMATRIX MatrixScale;															// 缩放变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;							// 旋转变换矩阵
	D3DXMATRIX MatrixTranslate;														// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);												// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sWorldTransformPara.sScalePara.fScaleX, sWorldTransformPara.sScalePara.fScaleY, sWorldTransformPara.sScalePara.fScaleZ);	// 设置缩放矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sWorldTransformPara.sRotatePara.fRotateX);	// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sWorldTransformPara.sRotatePara.fRotateY);	// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sWorldTransformPara.sRotatePara.fRotateZ);	// 设置旋转矩阵Z
	D3DXMatrixTranslation(&MatrixTranslate, sWorldTransformPara.sTranslatePara.fTranslateX, sWorldTransformPara.sTranslatePara.fTranslateY, sWorldTransformPara.sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);							// 设置世界变换

	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, &(sViewTransformPara.vEye), &(sViewTransformPara.vAt), &(sViewTransformPara.vUp));
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);

	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, sPrespectiveTransformPara.fovy, sPrespectiveTransformPara.fAspect, sPrespectiveTransformPara.fZn, sPrespectiveTransformPara.fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);

	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = sViewPortTransformPara.nUserWidth;
	ViewPort.Height = sViewPortTransformPara.nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 MatrixTransform(S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara)
// @Purpose: DirectGraphics3D矩阵变换
// @Since: v1.00a
// @Para: DG3D_CoordsTransformPara sCoordsTransformPara		//矩阵变换系数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::MatrixTransform(S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX MatrixWorld;																				// 世界变换矩阵
	D3DXMATRIX MatrixScale;																				// 缩放变换矩阵
	D3DXMATRIX MatrixRotateX, MatrixRotateY, MatrixRotateZ;												// 旋转变换矩阵
	D3DXMATRIX MatrixTranslate;																			// 平移变换矩阵

	D3DXMatrixIdentity(&MatrixWorld);																	// 单位化矩阵
	D3DXMatrixScaling(&MatrixScale, sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX, sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY, sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ);	// 设置缩放矩阵
	D3DXMatrixRotationX(&MatrixRotateX, sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX);	// 设置旋转矩阵X
	D3DXMatrixRotationY(&MatrixRotateY, sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY);	// 设置旋转矩阵Y
	D3DXMatrixRotationZ(&MatrixRotateZ, sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ);	// 设置旋转矩阵Z
	D3DXMatrixTranslation(&MatrixTranslate, sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX, sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY, sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ);	// 设置平移矩阵
	MatrixWorld = MatrixWorld * MatrixScale * MatrixRotateX * MatrixRotateY * MatrixRotateZ * MatrixTranslate;
	m_pD3D9Device->SetTransform(D3DTS_WORLD, &MatrixWorld);												// 设置世界变换

	D3DXMATRIX MatrixView;
	D3DXMatrixLookAtLH(&MatrixView, &(sCoordsTransformPara.sViewTransformPara.vEye), &(sCoordsTransformPara.sViewTransformPara.vAt), &(sCoordsTransformPara.sViewTransformPara.vUp));
	m_pD3D9Device->SetTransform(D3DTS_VIEW, &MatrixView);

	D3DXMATRIX MatrixProject;
	D3DXMatrixPerspectiveFovLH(&MatrixProject, sCoordsTransformPara.sPrespectiveTransformPara.fovy, sCoordsTransformPara.sPrespectiveTransformPara.fAspect, sCoordsTransformPara.sPrespectiveTransformPara.fZn, sCoordsTransformPara.sPrespectiveTransformPara.fZf);
	m_pD3D9Device->SetTransform(D3DTS_PROJECTION, &MatrixProject);

	D3DVIEWPORT9 ViewPort;
	ViewPort.X = 0;
	ViewPort.Y = 0;
	ViewPort.Width = sCoordsTransformPara.sViewPortTransformPara.nUserWidth;
	ViewPort.Height = sCoordsTransformPara.sViewPortTransformPara.nUserHeight;
	ViewPort.MinZ = 0.0f;
	ViewPort.MaxZ = 1.0f;
	m_pD3D9Device->SetViewport(&ViewPort);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetLightPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D光照设置
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9光照
// @Para: D3DCOLOR dwAmbientLight					//环境光
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetLightPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DLIGHT9 D3D9Light;
	
	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		// 清除内存

	D3D9Light.Type = D3DLIGHT_POINT;				// 光源类型(点光源)
	D3D9Light.Ambient = cAmbient;					// 环境光
	D3D9Light.Diffuse = cDiffuse;					// 漫反射光
	D3D9Light.Specular = cSpecular;					// 镜面反射光
	D3D9Light.Position = vPosition;					// 点光源位置
	D3D9Light.Attenuation0 = 1.0f;					// 光源衰减系数0
	D3D9Light.Attenuation1 = 0.0f;					// 光源衰减系数1
	D3D9Light.Attenuation2 = 0.0f;					// 光源衰减系数2
	D3D9Light.Range = fRange;						// 光源范围

	m_pD3D9Device->SetLight(0, &D3D9Light);										// 设置光源  
	m_pD3D9Device->LightEnable(0, true);										// 启用光照  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				// 设置一下环境光
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetLightDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D光照设置
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9光照
// @Para: D3DCOLOR dwAmbientLight					//环境光
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetLightDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		// 清除内存

	D3D9Light.Type = D3DLIGHT_DIRECTIONAL;			// 光源类型(平行光源)
	D3D9Light.Ambient = cAmbient;					// 环境光
	D3D9Light.Diffuse = cDiffuse;					// 漫反射光
	D3D9Light.Specular = cSpecular;					// 镜面反射光
	D3D9Light.Direction = vDirectional;				// 平行光方向

	m_pD3D9Device->SetLight(0, &D3D9Light);										// 设置光源  
	m_pD3D9Device->LightEnable(0, true);										// 启用光照  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				// 设置一下环境光
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetLightSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D光照设置
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9光照
// @Para: D3DCOLOR dwAmbientLight					//环境光
// @Return: None
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetLightSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));		// 清除内存

	D3D9Light.Type = D3DLIGHT_SPOT;					// 光源类型(聚光灯光源)
	D3D9Light.Ambient = cAmbient;					// 环境光
	D3D9Light.Diffuse = cDiffuse;					// 漫反射光
	D3D9Light.Specular = cSpecular;					// 镜面反射光
	D3D9Light.Position = vPosition;					// 聚光灯光源位置
	D3D9Light.Direction = vDirectional;				// 平行光方向
	D3D9Light.Attenuation0 = 1.0f;					// 光源衰减系数0
	D3D9Light.Attenuation1 = 0.0f;					// 光源衰减系数1
	D3D9Light.Attenuation2 = 0.0f;					// 光源衰减系数2
	D3D9Light.Range = fRange;						// 光源范围
	D3D9Light.Falloff = fFallOff;					// 聚光灯衰减
	D3D9Light.Phi = fPhi;
	D3D9Light.Theta = fTheta;

	m_pD3D9Device->SetLight(0, &D3D9Light);										// 设置光源  
	m_pD3D9Device->LightEnable(0, true);										// 启用光照  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				// 设置一下环境光
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetLight(D3DLIGHT9 * pD3D9Light, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D光照设置
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9光照
// @Para: D3DCOLOR dwAmbientLight					//环境光
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetLight(D3DLIGHT9 * pD3D9Light, D3DCOLOR dwAmbientLight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetLight(0, pD3D9Light);										// 设置光源  
	m_pD3D9Device->LightEnable(0, true);										// 启用光照  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				// 设置一下环境光
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetLight(E_DX_LIGHT_TYPE eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
// @Purpose: DirectGraphics3D光照设置
// @Since: v1.00a
// @Para: D3DLIGHT9* pD3D9Light						//D3D9光照
// @Para: D3DCOLOR dwAmbientLight					//环境光
// @Return: None
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetLight(E_DX_LIGHT_TYPE eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DLIGHT9 D3D9Light;

	ZeroMemory(&D3D9Light, sizeof(D3DLIGHT9));			// 清除内存

	switch (eLightType)
	{
	case Light_Type_Point:								// (点光源)
		D3D9Light.Type = D3DLIGHT_POINT;				// 光源类型(点光源)
		D3D9Light.Ambient = cAmbient;					// 环境光
		D3D9Light.Diffuse = cDiffuse;					// 漫反射光
		D3D9Light.Specular = cSpecular;					// 镜面反射光
		D3D9Light.Position = vPosition;					// 点光源位置
		D3D9Light.Attenuation0 = 1.0f;					// 光源衰减系数0
		D3D9Light.Attenuation1 = 0.0f;					// 光源衰减系数1
		D3D9Light.Attenuation2 = 0.0f;					// 光源衰减系数2
		D3D9Light.Range = fRange;						// 光源范围
		break;
	case Light_Type_Direction:							// (平行光源)
		D3D9Light.Type = D3DLIGHT_DIRECTIONAL;			// 光源类型(平行光源)
		D3D9Light.Ambient = cAmbient;					// 环境光
		D3D9Light.Diffuse = cDiffuse;					// 漫反射光
		D3D9Light.Specular = cSpecular;					// 镜面反射光
		D3D9Light.Direction = vDirectional;				// 平行光方向
		break;
	case Light_Type_Spot:								// (聚光灯光源)
		D3D9Light.Type = D3DLIGHT_SPOT;					// 光源类型(聚光灯光源)
		D3D9Light.Ambient = cAmbient;					// 环境光
		D3D9Light.Diffuse = cDiffuse;					// 漫反射光
		D3D9Light.Specular = cSpecular;					// 镜面反射光
		D3D9Light.Position = vPosition;					// 聚光灯光源位置
		D3D9Light.Direction = vDirectional;				// 平行光方向
		D3D9Light.Attenuation0 = 1.0f;					// 光源衰减系数0
		D3D9Light.Attenuation1 = 0.0f;					// 光源衰减系数1
		D3D9Light.Attenuation2 = 0.0f;					// 光源衰减系数2
		D3D9Light.Range = fRange;						// 光源范围
		D3D9Light.Falloff = fFallOff;					// 聚光灯衰减
		D3D9Light.Phi = fPhi;
		D3D9Light.Theta = fTheta;
		break;
	default:
		return;
		break;
	}

	m_pD3D9Device->SetLight(0, &D3D9Light);										// 设置光源  
	m_pD3D9Device->LightEnable(0, true);										// 启用光照  
	m_pD3D9Device->SetRenderState(D3DRS_AMBIENT, dwAmbientLight);				// 设置一下环境光
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetMaterial(D3DMATERIAL9 * pD3D9Material)
// @Purpose: DirectGraphics3D材质设置
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9材质
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetMaterial(D3DMATERIAL9 * pD3D9Material)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetMaterial(pD3D9Material);				// 设置一下材质
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive)
// @Purpose: DirectGraphics3D材质设置
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9材质
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DMATERIAL9 D3D9Material;

	ZeroMemory(&D3D9Material, sizeof(D3DMATERIAL9));		// 清除内存

	D3D9Material.Ambient = cAmbient;						// 环境光
	D3D9Material.Diffuse = cDiffuse;						// 漫反射光
	D3D9Material.Specular = cSpecular;						// 镜面反射光
	D3D9Material.Emissive = cEmissive;						// 物体自发光

	m_pD3D9Device->SetMaterial(&D3D9Material);				// 设置一下材质
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower)
// @Purpose: DirectGraphics3D材质设置
// @Since: v1.00a
// @Para: D3DMATERIAL9* pD3D9Material				//D3D9材质
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DMATERIAL9 D3D9Material;

	ZeroMemory(&D3D9Material, sizeof(D3DMATERIAL9));		// 清除内存

	D3D9Material.Ambient = cAmbient;						// 环境光
	D3D9Material.Diffuse = cDiffuse;						// 漫反射光
	D3D9Material.Specular = cSpecular;						// 镜面反射光
	D3D9Material.Emissive = cEmissive;						// 物体自发光
	D3D9Material.Power = fPower;							// 镜面反射强度

	m_pD3D9Device->SetMaterial(&D3D9Material);				// 设置一下材质
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX3D_BASE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DBase* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(S_DX_VERTEX3D_BASE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_BASE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX3D_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(S_DX_VERTEX3D_TEXTURE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX3D_NORMAL * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DNormal* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(S_DX_VERTEX3D_NORMAL * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_NORMAL* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX3D_NORMAL_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DNormalTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(S_DX_VERTEX3D_NORMAL_TEXTURE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_NORMAL_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DNormalSpecularTexture* VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE * VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType
// @Para: LPVOID VertexArray
// @Para: int nSize
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX3D_BASE* pVertices3DBase = NULL;
	S_DX_VERTEX3D_TEXTURE* pVertices3DTexture = NULL;
	S_DX_VERTEX3D_NORMAL* pVertices3DNormal = NULL;
	S_DX_VERTEX3D_NORMAL_TEXTURE* pVertices3DNormalTexture = NULL;
	S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* pVertices3DNormalSpecularTexture = NULL;

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DBase, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DBase + i) = *((S_DX_VERTEX3D_BASE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DTexture + i) = *((S_DX_VERTEX3D_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormal, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormal + i) = *((S_DX_VERTEX3D_NORMAL*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormalTexture + i) = *((S_DX_VERTEX3D_NORMAL_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalSpecularTexture, 0);

		for (int i = 0; i < nSize; ++i)
		{
			*(pVertices3DNormalSpecularTexture + i) = *((S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}

}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingIndex(int nPlane)
// @Purpose: DirectGraphics3D填充索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingIndex(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX3D_BASE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(S_DX_VERTEX3D_BASE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_BASE* pVertices = NULL;

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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX3D_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(S_DX_VERTEX3D_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_TEXTURE* pVertices = NULL;

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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_NORMAL* pVertices = NULL;

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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_NORMAL_TEXTURE* pVertices = NULL;

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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE * VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* pVertices = NULL;

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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nSize)
// @Purpose: DirectGraphics3D填充顶点和索引
// @Since: v1.00a
// @Para: int nPlane	//平面数
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::PaddingVertexAndIndex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 填充顶点缓存
	S_DX_VERTEX3D_BASE* pVertices3DBase = NULL;
	S_DX_VERTEX3D_TEXTURE* pVertices3DTexture = NULL;
	S_DX_VERTEX3D_NORMAL* pVertices3DNormal = NULL;
	S_DX_VERTEX3D_NORMAL_TEXTURE* pVertices3DNormalTexture = NULL;
	S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* pVertices3DNormalSpecularTexture = NULL;

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DBase, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DBase + i) = *((S_DX_VERTEX3D_BASE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DTexture + i) = *((S_DX_VERTEX3D_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormal, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormal + i) = *((S_DX_VERTEX3D_NORMAL*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormalTexture + i) = *((S_DX_VERTEX3D_NORMAL_TEXTURE*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices3DNormalSpecularTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices3DNormalSpecularTexture + i) = *((S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE*)VertexArray + i);
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

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 AlphaEnable()
// @Purpose: DirectGraphics3D开启Alpha混合
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::AlphaEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha混合开启
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 AlphaDisable()
// @Purpose: DirectGraphics3D关闭Alpha混合
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::AlphaDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha混合关闭
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 LightEnable()
// @Purpose: DirectGraphics3D开启Light光照
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::LightEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_LIGHTING, TRUE);							// Light开启光照
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 LightDisable()
// @Purpose: DirectGraphics3D关闭Light光照
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::LightDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_LIGHTING, FALSE);							// Light关闭光照
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Setting()
// @Purpose: DirectGraphics3D设置渲染模式
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Setting()
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
// @Function:	 Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics3D渲染
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//顶点类型
// @Para: int nPlane					//绘制平面数量
// @Para: bool bIsTexture				//是否启用纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
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
// @Function:	 Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics3D渲染
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType	//顶点类型
// @Para: int nStartIndex				//开始绘制索引序号
// @Para: int nPlane					//绘制平面数量
// @Para: bool bIsTexture				//是否启用纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
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
// @Function:	 Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
// @Purpose: DirectGraphics3D渲染
// @Since: v1.00a
// @Para: Vertex3DType eVertex3DType			//顶点类型
// @Para: int nStartIndex						//开始绘制索引序号
// @Para: int nPlane							//绘制平面数量
// @Para: LPDIRECT3DTEXTURE9 pRenderTexture		//导入渲染纹理
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3D::Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex3DType)
	{
	case Vertex3D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_BASE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex3D_Type_Normal_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}

}
