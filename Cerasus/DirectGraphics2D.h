/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectGraphics2D.h
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
#pragma once

#ifndef __DIRECTGRAPHICS2D_H_
#define __DIRECTGRAPHICS2D_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS2D_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS2D_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS2D_CALLMETHOD	__stdcall

// Class Definition
class DIRECTGRAPHICS2D_API DirectGraphics2D
{
private:
	IDirect3DDevice9*		m_pD3D9Device;					// Direct3D 9 Device Object(~D3D9�豸����)
	IDirect3DVertexBuffer9* m_pD3D9VertexBuffer;			// Direct3D 9 Vertex Buffer(~D3D9���㻺��)
	IDirect3DIndexBuffer9*	m_pD3D9IndexBuffer;				// Direct3D 9 Index  Buffer(~D3D9��������)
	IDirect3DTexture9*		m_pD3D9Texture;					// Direct3D 9 Texture(~D3D9����)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status

public:
	DirectGraphics2D();										// DirectGraphics2D Construction Function(~DirectGraphics2D���캯��)
	~DirectGraphics2D();									// DirectGraphics2D Destruction  Function(~DirectGraphics2D��������)

	DirectGraphics2D(IDirect3DDevice9* pD3D9Device, bool bSafe = true);			// DirectGraphics2D Construction Function(~DirectGraphics2D���캯��)(Overload + 1)
	DirectGraphics2D(const DirectGraphics2D&);									// DirectGraphics2D Construction Function(~DirectGraphics2D�������캯��)

public:
	const DirectGraphics2D & operator=(const DirectGraphics2D&);				// DirectGraphics2D Operator Overload(~DirectGraphics2D����=)

public:
	IDirect3DDevice9*			DIRECTGRAPHICS2D_CALLMETHOD		GetDevice() const;					// DirectGraphics2D Get Device Object(~DirectGraphics��ȡD3D9�豸����)
	IDirect3DVertexBuffer9*		DIRECTGRAPHICS2D_CALLMETHOD		GetVertexBuffer() const;			// DirectGraphics2D Get D3D9 Vertex Buffer(~DirectGraphics3D��ȡD3D9���㻺��)
	IDirect3DIndexBuffer9*		DIRECTGRAPHICS2D_CALLMETHOD		GetIndexBuffer() const;				// DirectGraphics2D Get D3D9 Index Buffer(~DirectGraphics3D��ȡD3D9��������)
	IDirect3DTexture9*			DIRECTGRAPHICS2D_CALLMETHOD		GetTexture() const;					// DirectGraphics2D Get D3D9 Texture(~DirectGraphics3D��ȡD3D9����)

public:
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		Create(int nPlane);																		// DirectGraphics2D Initialization(��ʼ��)(ƽ����)
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		Create(int nPlane, LPCWSTR lpszStrTexture);												// DirectGraphics2D Initialization(��ʼ��)(ƽ����/����)(Overload + 1)
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane);									// DirectGraphics2D Initialization(��ʼ��)(��������/ƽ����)(Overload + 2)
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		Create(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, LPCWSTR lpszStrTexture);			// DirectGraphics2D Initialization(��ʼ��)(��������/ƽ����/����)(Overload + 3)

	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		CreateBase(UINT nCount);																// DirectGraphics2D Initialization(��ʼ��)(2D���������ʽ)
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		CreateTexture(UINT nCount, LPCWSTR pString);											// DirectGraphics2D Initialization(��ʼ��)(2D�������ʽ)
	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		CreateSpecularTexture(UINT nCount, LPCWSTR pString);									// DirectGraphics2D Initialization(��ʼ��)(2D�����������ʽģʽ)

	HRESULT						DIRECTGRAPHICS2D_CALLMETHOD		Reset();																				// DirectGraphics2D D3D9 Reset(����)(Reset����Ҫ����Init�������³�ʼ��)

	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertex(S_DX_VERTEX2D_BASE* VertexArray, int nSize);								// DirectGraphics2D Padding Vertex(��䶥������)(2D���������ʽ)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertex(S_DX_VERTEX2D_TEXTURE* VertexArray, int nSize);							// DirectGraphics2D Padding Vertex(��䶥������)(2D���������ʽ)(Overload + 1)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertex(S_DX_VERTEX2D_SPECULAR_TEXTURE* VertexArray, int nSize);					// DirectGraphics2D Padding Vertex(��䶥������)(2D���㾵�������ʽ)(Overload + 2)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane);		// DirectGraphics2D Padding Vertex(��䶥������)(2D�����ʽö��)(Overload + 3)

	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingIndex(int nPlane);																// DirectGraphics2D Padding Index(�����������)

	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX2D_BASE* VertexArray, int nPlane);						// DirectGraphics2D Padding Vertex and Index(��䶥�����������)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX2D_TEXTURE* VertexArray, int nPlane);					// DirectGraphics2D Padding Vertex and Index(��䶥�����������)(Overload + 1)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX2D_SPECULAR_TEXTURE* VertexArray, int nPlane);			// DirectGraphics2D Padding Vertex and Index(��䶥�����������)(Overload + 2)
	void						DIRECTGRAPHICS2D_CALLMETHOD		PaddingVertexAndIndex(E_DX_VERTEX2D_TYPE eVertex2DType, LPVOID VertexArray, int nPlane);// DirectGraphics2D Padding Vertex and Index(��䶥�����������)(Overload + 3)

	void						DIRECTGRAPHICS2D_CALLMETHOD		AlphaEnable();																			// DirectGraphics2D Render State Setting(����Alpha���)//��Ⱦ��Ϲر�Alpha���
	void						DIRECTGRAPHICS2D_CALLMETHOD		AlphaDisable();																			// DirectGraphics2D Render State Setting(�ر�Alpha���)

	void						DIRECTGRAPHICS2D_CALLMETHOD		AlphaMix();																				// DirectGraphics2D Render State Setting(Alpha�ں�����)
	void						DIRECTGRAPHICS2D_CALLMETHOD		ColorMix();																				// DirectGraphics2D Render State Setting(Color�ں�����)(ѡ��)
	void						DIRECTGRAPHICS2D_CALLMETHOD		ColorMix(D3DXCOLOR MixColor);															// DirectGraphics2D Render State Setting(Color�ں�����)(���)

	void						DIRECTGRAPHICS2D_CALLMETHOD		Setting();																				// DirectGraphics2D Render State Setting

	void						DIRECTGRAPHICS2D_CALLMETHOD		Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nPlane, bool bIsTexture = false);										// DirectGraphics2D Render(��Ⱦ)
	void						DIRECTGRAPHICS2D_CALLMETHOD		Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture = false);						// DirectGraphics2D Render(��Ⱦ)(Overload + 1)
	void						DIRECTGRAPHICS2D_CALLMETHOD		Render(E_DX_VERTEX2D_TYPE eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);			// DirectGraphics2D Render(��Ⱦ)(Overload + 2)

};

#endif