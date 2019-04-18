/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectGraphics3D.h
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
#pragma once

#ifndef __DIRECTGRAPHICS3D_H_
#define __DIRECTGRAPHICS3D_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS3D_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS3D_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS3D_CALLMETHOD	__stdcall

// Class Definition
class DIRECTGRAPHICS3D_API DirectGraphics3D
{
private:
	IDirect3DDevice9*		m_pD3D9Device;					// Direct3D 9 Device Object(~D3D9设备对象)
	IDirect3DVertexBuffer9* m_pD3D9VertexBuffer;			// Direct3D 9 Vertex Buffer(~D3D9顶点缓存)
	IDirect3DIndexBuffer9*	m_pD3D9IndexBuffer;				// Direct3D 9 Index  Buffer(~D3D9索引缓存)
	IDirect3DTexture9*		m_pD3D9Texture;					// Direct3D 9 Texture(~D3D9纹理)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status

public:
	DirectGraphics3D();										// DirectGraphics3D Construction Function(~DirectGraphics3D构造函数)
	~DirectGraphics3D();									// DirectGraphics3D Destruction Function(~DirectGraphics3D析构函数)

	DirectGraphics3D(IDirect3DDevice9* pD3D9Device, bool bSafe = true);			// DirectGraphics3D Construction Function(~DirectGraphics3D构造函数)(Overload + 1)
	DirectGraphics3D(const DirectGraphics3D&);									// DirectGraphics3D Construction Function(~DirectGraphics3D拷贝构造函数)

public:
	const DirectGraphics3D & operator=(const DirectGraphics3D&);				// DirectGraphics3D Operator Overload(~DirectGraphics3D重载=)

public:
	IDirect3DDevice9*			DIRECTGRAPHICS3D_CALLMETHOD		GetDevice() const;					// DirectGraphics3D Get Device Object(~DirectGraphics获取D3D9设备对象)
	IDirect3DVertexBuffer9*		DIRECTGRAPHICS3D_CALLMETHOD		GetVertexBuffer() const;			// DirectGraphics3D Get D3D9 Vertex Buffer(~DirectGraphics3D获取D3D9顶点缓存)
	IDirect3DIndexBuffer9*		DIRECTGRAPHICS3D_CALLMETHOD		GetIndexBuffer() const;				// DirectGraphics3D Get D3D9 Index Buffer(~DirectGraphics3D获取D3D9索引缓存)
	IDirect3DTexture9*			DIRECTGRAPHICS3D_CALLMETHOD		GetTexture() const;					// DirectGraphics3D Get D3D9 Texture(~DirectGraphics3D获取D3D9纹理)

public:
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(int nPlane);																									// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D基本顶点格式)(平面数)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(int nPlane, LPCWSTR lpszStrTexture);																			// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D纹理顶点格式)(平面数)(纹理路径)(Overload + 1)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane);																// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(Overload + 2)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, LPCWSTR lpszStrTexture);										// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(Overload + 3)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(D3DPOOL ePool, DWORD Usage, E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane);									// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(Overload + 4)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Create(D3DPOOL ePool, DWORD Usage, E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, LPCWSTR lpszStrTexture);			// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(Overload + 5)

	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateBase(UINT nCount);																							// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D基本顶点格式)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);												// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D纹理顶点格式)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);									// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D纹理顶点格式)(从内存读取纹理)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateNormal(UINT nCount);																							// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D法线顶点格式)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateNormalTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);											// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D法线纹理顶点格式)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateNormalTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);								// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D法线纹理顶点格式)(从内存读取纹理)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateNormalSpecularTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);									// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D法线镜面反射纹理顶点格式)
	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		CreateNormalSpecularTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);						// DirectGraphics3D Initialization(~DirectGraphics3D初始化)(3D法线镜面反射纹理顶点格式)(从内存读取纹理)

	HRESULT						DIRECTGRAPHICS3D_CALLMETHOD		Reset();																											// DirectGraphics3D Reset(Reset之后需要调用Create函数重新初始化)

	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_SCALE_PARA sScalePara);																	// DirectGraphics3D WorldSpaceTransform(Scale)(世界变换)(拉伸变换)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara);																	// DirectGraphics3D WorldSpaceTransform(Rotate)(世界变换)(旋转变换)(Overload + 1)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_TRANSLATE_PARA sTranslatePara);															// DirectGraphics3D WorldSpaceTransform(Translate)(世界变换)(位移变换)(Overload + 2)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara);										// DirectGraphics3D WorldSpaceTransform(世界变换)(拉伸、旋转变换)(Overload + 3)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_TRANSLATE_PARA sTranslatePara);								// DirectGraphics3D WorldSpaceTransform(世界变换)(拉伸、位移变换)(Overload + 4)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara);								// DirectGraphics3D WorldSpaceTransform(世界变换)(Overload + 5)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_SCALE_PARA sScalePara, S_DX_ROTATE_PARA sRotatePara, S_DX_TRANSLATE_PARA sTranslatePara);	// DirectGraphics3D WorldSpaceTransform(世界变换)(Overload + 6)
	void						DIRECTGRAPHICS3D_CALLMETHOD		WorldSpaceTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara);													// DirectGraphics3D WorldSpaceTransform(世界变换)(Overload + 7)

	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewSpaceTransform(D3DXVECTOR3* pvEye);																				// DirectGraphics3D ViewSpaceTransform(取景变换)
	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt);															// DirectGraphics3D ViewSpaceTransform(取景变换)(Overload + 1)
	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt, D3DXVECTOR3* pvUp);										// DirectGraphics3D ViewSpaceTransform(取景变换)(Overload + 2)
	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewSpaceTransform(S_DX_VIEW_TRANSFORM_PARA sViewTransformPara);													// DirectGraphics3D ViewSpaceTransform(取景变换)(Overload + 3)

	void						DIRECTGRAPHICS3D_CALLMETHOD		PerspectiveTransform(float fovy, float fAspect, float fZn, float fZf);												// DirectGraphics3D PerspectiveTransform(透视/投影变换)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PerspectiveTransform(S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara);									// DirectGraphics3D PerspectiveTransform(透视/投影变换)(Overload + 1)

	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewPortTransform(int nUserWidth, int nUserHeight);																	// DirectGraphics3D ViewPortTransform(视口变换)
	void						DIRECTGRAPHICS3D_CALLMETHOD		ViewPortTransform(S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara);												// DirectGraphics3D ViewPortTransform(视口变换)(Overload + 1)

	void						DIRECTGRAPHICS3D_CALLMETHOD		MatrixTransform(S_DX_WORLD_TRANSFORM_PARA sWorldTransformPara, S_DX_VIEW_TRANSFORM_PARA sViewTransformPara, S_DX_PRESPECTIVE_TRANSFORM_PARA sPrespectiveTransformPara, S_DX_VIEWPORT_TRANSFORM_PARA sViewPortTransformPara);			// DirectGraphics3D MatrixTransform(坐标变换)
	void						DIRECTGRAPHICS3D_CALLMETHOD		MatrixTransform(S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara);																																										// DirectGraphics3D MatrixTransform(坐标变换)(Overload + 1)

	void						DIRECTGRAPHICS3D_CALLMETHOD		SetLightPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight);																								// DirectGraphics3D Light Setting(光源设置)(点光源)
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetLightDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight);																									// DirectGraphics3D Light Setting(光源设置)(平行光源)
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetLightSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);							// DirectGraphics3D Light Setting(光源设置)(聚光灯光源)
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetLight(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight);																																												// DirectGraphics3D Light Setting(光源设置)
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetLight(E_DX_LIGHT_TYPE eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);	// DirectGraphics3D Light Setting(光源设置)

	void						DIRECTGRAPHICS3D_CALLMETHOD		SetMaterial(D3DMATERIAL9* pD3D9Material);
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive);
	void						DIRECTGRAPHICS3D_CALLMETHOD		SetMaterial(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower);

	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(S_DX_VERTEX3D_BASE* VertexArray, int nSize);															// DirectGraphics3D Padding Vertex(填充顶点数据)(3D基本顶点格式)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(S_DX_VERTEX3D_TEXTURE* VertexArray, int nSize);														// DirectGraphics3D Padding Vertex(填充顶点数据)(3D纹理顶点格式)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(S_DX_VERTEX3D_NORMAL* VertexArray, int nSize);														// DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线顶点格式)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(S_DX_VERTEX3D_NORMAL_TEXTURE* VertexArray, int nSize);												// DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线纹理顶点格式)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* VertexArray, int nSize);										// DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线镜面反射纹理顶点格式)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nSize);										// DirectGraphics3D Padding Vertex(填充顶点数据)

	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingIndex(int nPlane);																							// DirectGraphics3D Padding Index(填充索引数据)

	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX3D_BASE* VertexArray, int nPlane);													// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX3D_TEXTURE* VertexArray, int nPlane);												// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL* VertexArray, int nPlane);												// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_TEXTURE* VertexArray, int nPlane);										// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(S_DX_VERTEX3D_NORMAL_SPECULAR_TEXTURE* VertexArray, int nPlane);								// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	void						DIRECTGRAPHICS3D_CALLMETHOD		PaddingVertexAndIndex(E_DX_VERTEX3D_TYPE eVertex3DType, LPVOID VertexArray, int nPlane);							// DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)

	void						DIRECTGRAPHICS3D_CALLMETHOD		AlphaEnable();																									// DirectGraphics3D Render State Setting(开启Alpha混合)//渲染完毕关闭Alpha混合
	void						DIRECTGRAPHICS3D_CALLMETHOD		AlphaDisable();																								// DirectGraphics3D Render State Setting(关闭Alpha混合)

	void						DIRECTGRAPHICS3D_CALLMETHOD		LightEnable();																									// DirectGraphics3D Render State Setting(开启Light光照)
	void						DIRECTGRAPHICS3D_CALLMETHOD		LightDisable();																								// DirectGraphics3D Render State Setting(关闭Light光照)

	void						DIRECTGRAPHICS3D_CALLMETHOD		Setting();																										// DirectGraphics3D Render State Setting(设置渲染模式)

	void						DIRECTGRAPHICS3D_CALLMETHOD		Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nPlane, bool bIsTexture = false);										// DirectGraphics3D Render(渲染)
	void						DIRECTGRAPHICS3D_CALLMETHOD		Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture = false);						// DirectGraphics3D Render(渲染)
	void						DIRECTGRAPHICS3D_CALLMETHOD		Render(E_DX_VERTEX3D_TYPE eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);			// DirectGraphics3D Render(渲染)

};


#endif