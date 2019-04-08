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

// DirectX9 Graphics Class(DirectX9 2D������)

//------------------------------------------------------------------
// @Function:	 DirectGraphics2D()
// @Purpose: DirectGraphics2D���캯��
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
// @Purpose: DirectGraphics2D��������
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
// @Purpose: DirectGraphics2D���캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (�����豸)
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
// @Purpose: DirectGraphics2D�������캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (�����豸)
// @Return: None
//--------------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D(const DirectGraphics2D & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;					// IDirect3DDevice9�ӿ�ָ���ʼ��
	m_pD3D9VertexBuffer = Object.m_pD3D9VertexBuffer;		// IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9IndexBuffer = Object.m_pD3D9IndexBuffer;			// IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Texture = Object.m_pD3D9Texture;					// IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
}

//--------------------------------------------------------------------------
// @Function:	 operator=(const DirectGraphics2D & Object)
// @Purpose: DirectGraphics2D�������캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (�����豸)
// @Return: None
//--------------------------------------------------------------------------
const DirectGraphics2D & DirectGraphics2D::operator=(const DirectGraphics2D & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;					// IDirect3DDevice9�ӿ�ָ���ʼ��
		m_pD3D9VertexBuffer = Object.m_pD3D9VertexBuffer;		// IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
		m_pD3D9IndexBuffer = Object.m_pD3D9IndexBuffer;			// IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
		m_pD3D9Texture = Object.m_pD3D9Texture;					// IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
	}

	return *this;
}

//-----------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: DirectGraphics2D��ȡ�豸�ӿ�ָ��
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
// @Purpose: DirectGraphics2D��ȡ���㻺��ӿ�ָ��
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
// @Purpose: DirectGraphics2D��ȡ��������ӿ�ָ��
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
// @Purpose: DirectGraphics2D��ȡ����ӿ�ָ��
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
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: int nPlane	//ƽ�����
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Create(int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: int nPlane				//ƽ�����
// @Para: LPCWSTR lpszStrTexture	//����·��
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture����ƽ������
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//��������
// @Para: int nPlane					//ƽ�����
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Specular_Texture:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
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
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//��������
// @Para: int nPlane					//ƽ�����
// @Para: LPCWSTR lpszStrTexture		//����·��
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture����ƽ������
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex2D_Type_Specular_Texture:
		// VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		// IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		// Texture����ƽ������
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
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: UINT nCount					//ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateBase(UINT nCount)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_BASE), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateTexture(UINT nCount, LPCWSTR pString)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: UINT nCount					//ƽ�����
// @Para: LPCWSTR pString				//����·��
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateTexture(UINT nCount, LPCWSTR pString)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_TEXTURE), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture����ƽ������
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, pString, &m_pD3D9Texture));

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 CreateSpecularTexture(UINT nCount, LPCWSTR pString)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: UINT nCount					//ƽ�����
// @Para: LPCWSTR pString				//����·��
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::CreateSpecularTexture(UINT nCount, LPCWSTR pString)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nCount * sizeof(S_DX_VERTEX2D_SPECULAR_TEXTURE), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	// IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nCount * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	// Texture����ƽ������
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, pString, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: DirectGraphics2D����(��ʧ�豸)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(�ɹ�:S_OK, ʧ��:E_FAIL)
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Reset()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		//IDirect3DVertexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9IndexBuffer);		//IDirect3DIndexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9Texture);			//IDirect3DTexture9�ӿ�ָ���ͷ�
	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 PaddingVertex(S_DX_VERTEX2D_BASE * VertexArray, int nSize)
// @Purpose: DirectGraphics2D��䶥��(Base����)
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray		//��䶥�������ַ
// @Para: int nSize						//��䶥�����鳤��
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
// @Purpose: DirectGraphics2D��䶥��(Texture����)
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray	//��䶥�������ַ
// @Para: int nSize						//��䶥�����鳤��
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
// @Purpose: DirectGraphics2D��䶥��(Specular����)
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray		//��䶥�������ַ
// @Para: int nSize									//��䶥�����鳤��
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
// @Purpose: DirectGraphics2D��䶥��(ö������)
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType						//��������
// @Para: LPVOID VertexArray								//��䶥�������ַ
// @Para: int nPlane										//���ƽ�����
// @Return: None
//--------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_BASE* pVertices2DBase = NULL;
	S_DX_VERTEX2D_TEXTURE* pVertices2DTexture = NULL;
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices2DSpecularTexture = NULL;

	//��䶥�㻺��
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
// @Purpose: DirectGraphics2D�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//--------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingIndex(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// �����������
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
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray					//��䶥�������ַ
// @Para: int nPlane								//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_BASE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��䶥�㻺��
	S_DX_VERTEX2D_BASE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// �����������
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
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray				//��䶥�������ַ
// @Para: int nPlane								//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��䶥�㻺��
	S_DX_VERTEX2D_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// �����������
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
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray				//��䶥�������ַ
// @Para: int nPlane										//���ƽ�����
// @Return: None
//------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(S_DX_VERTEX2D_SPECULAR_TEXTURE * VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��䶥�㻺��
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	// �����������
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
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType						//��������
// @Para: LPVOID VertexArray								//��䶥�������ַ
// @Para: int nPlane										//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::PaddingVertexAndIndex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_VERTEX2D_BASE* pVertices2DBase = NULL;
	S_DX_VERTEX2D_TEXTURE* pVertices2DTexture = NULL;
	S_DX_VERTEX2D_SPECULAR_TEXTURE* pVertices2DSpecularTexture = NULL;

	// ��䶥�㻺��
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

	// �����������
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
// @Purpose: DirectGraphics2D����Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha��Ͽ���
}

//---------------------------------------------------------------
// @Function:	 AlphaDisable()
// @Purpose: DirectGraphics2D�ر�Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					// Alpha��Ϲر�
}

//---------------------------------------------------------------
// @Function:	 AlphaMix()
// @Purpose: DirectGraphics2D������Ⱦ״̬(Alpha�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::AlphaMix()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��Ⱦģʽ:Alpha�������
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha��Ͽ���
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					// Alpha���ģʽ:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);		// D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
}

//---------------------------------------------------------------
// @Function:	 ColorMix()
// @Purpose: DirectGraphics2D������Ⱦ״̬(Color�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::ColorMix()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------
// @Function:	 ColorMix(D3DXCOLOR MixColor)
// @Purpose: DirectGraphics2D������Ⱦ״̬(Color�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::ColorMix(D3DXCOLOR MixColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��Ⱦģʽ:����������
	m_pD3D9Device->SetRenderState(D3DRS_TEXTUREFACTOR, MixColor);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
}

//-----------------------------------------------------------
// @Function:	 Setting()
// @Purpose: DirectGraphics2D������Ⱦ״̬
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMETHOD DirectGraphics2D::Setting()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ��Ⱦģʽ:Alpha�������
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					// Alpha��Ͽ���
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					// Alpha���ģʽ:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);		// D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, bool bIsTexture)
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
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
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nStartIndex				//��ʼ����
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
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
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nStartIndex				//��ʼ����
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
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
