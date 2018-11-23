/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics3D.h
* @brief	This File is DirectGraphics3D DLL Project.
* @author	Alopex/Helium
* @version	v1.31a
* @date		2017-11-29	v1.00a	alopex	Create Project.
* @date		2017-12-3	v1.01a	alopex	Modify Bug.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.24a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-12	v1.25a	alopex	Add Get & Set & Reset Function.
* @date		2018-04-12	v1.26a	alopex	Add Macro Call Mode.
* @date		2018-06-21	v1.27a	alopex	Add Version Infomation.
* @date		2018-06-21	v1.28a	alopex	Add Transform Function.
* @date		2018-06-24	v1.29a	alopex	Repair Bugs.
* @date		2018-06-24	v1.30a	alopex	Repair Texture Alpha Channel.
* @date		2018-11-23	v1.31a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __DIRECTGRAPHICS3D_H_
#define __DIRECTGRAPHICS3D_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS3D_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS3D_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS3D_CALLMETHOD	__stdcall

//Struct Definition
//Vertex 3D Base(3D基本顶点格式)
struct Vertex3DBase
{
	float X, Y, Z;
	DWORD COLOR;
	Vertex3DBase(float x, float y, float z, DWORD Color) :X(x), Y(y), Z(z), COLOR(Color) {}
};

#define D3DFVF_VERTEX3D_BASE	(D3DFVF_XYZ | D3DFVF_DIFFUSE)				//基本顶点格式模式(3D坐标/漫反射光线)

//Vertex 3D Texture(3D纹理顶点格式)
struct Vertex3DTexture
{
	float X, Y, Z;
	DWORD COLOR;
	float U, V;
	Vertex3DTexture(float x, float y, float z, DWORD Color, float u, float v) :X(x), Y(y), Z(z), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_TEXTURE	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//纹理顶点格式模式(3D坐标/漫反射光线/纹理图样)

//Vertex 3D Normal(3D法线顶点格式)
struct Vertex3DNormal
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD COLOR;
	Vertex3DNormal(float x, float y, float z, float nx, float ny, float nz, DWORD Color) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), COLOR(Color) {}
};

#define D3DFVF_VERTEX3D_NORMAL	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)	//法线顶点格式模式(3D坐标/法线坐标/漫反射光线)

//Vertex 3D Normal Texture(3D法线纹理顶点格式)(光照栅格)
struct Vertex3DNormalTexture
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD COLOR;
	float U, V;
	Vertex3DNormalTexture(float x, float y, float z, float nx, float ny, float nz, DWORD Color, float u, float v) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_NORMAL_TEXTURE	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//法线纹理顶点格式模式(3D坐标/法线坐标/漫反射光线/纹理图样)

//Vertex 3D Normal Specular Texture(3D法线镜面反射纹理顶点格式)(镜面反射光、光照栅格)
struct Vertex3DNormalSpecularTexture
{
	float X, Y, Z;
	float nX, nY, nZ;
	DWORD DIFFUSE;
	DWORD SPECULAR;
	float U, V;
	Vertex3DNormalSpecularTexture(float x, float y, float z, float nx, float ny, float nz, DWORD Diffuse, DWORD Specular, float u, float v) :X(x), Y(y), Z(z), nX(nx), nY(ny), nZ(nz), DIFFUSE(Diffuse), SPECULAR(Specular), U(u), V(v) {}
};

#define D3DFVF_VERTEX3D_NORMAL_SPECULAR_TEXTURE	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)	//法线镜面反射纹理顶点格式模式(3D坐标/法线坐标/漫反射光线/纹理图样)

//World Space Scale Transform(~世界变换拉伸变换)
typedef struct
{
	float fScaleX;		//X轴比例
	float fScaleY;		//Y轴比例
	float fScaleZ;		//Z轴比例
} DG3D_ScalePara, *LPDG3D_ScalePara;

//World Space Rotate Transform(~世界变换旋转变换)
typedef struct
{
	float fRotateX;		//X轴旋转
	float fRotateY;		//Y轴旋转
	float fRotateZ;		//Z轴旋转
} DG3D_RotatePara, *LPDG3D_RotatePara;

//World Space Translate Transform(~世界变换位移变换)
typedef struct
{
	float fTranslateX;	//X轴平移
	float fTranslateY;	//Y轴平移
	float fTranslateZ;	//Z轴平移
} DG3D_TranslatePara, *LPDG3D_TranslatePara;

//World Space Transform(~世界变换)
typedef struct
{
	DG3D_ScalePara sScalePara;			//比例系数
	DG3D_RotatePara sRotatePara;		//旋转系数
	DG3D_TranslatePara sTranslatePara;	//平移系数
} DG3D_WorldTransformPara, *LPDG3D_WorldTransformPara;

//View Space Transform(~取景变换)
typedef struct
{
	D3DXVECTOR3 vEye;	//摄像机位置
	D3DXVECTOR3 vAt;	//物体位置
	D3DXVECTOR3 vUp;	//向上向量
} DG3D_ViewTransformPara, *LPDG3D_ViewTransformPara;

//Perspective Transform(~投影变换)
typedef struct
{
	float fovy;			//Y轴视域角度(弧度) eg:D3DX_PI * 0.5f
	float fAspect;		//视口屏幕比例(宽度/高度)
	float fZn;			//视截体近裁剪面距离
	float fZf;			//视截体远裁剪面距离
} DG3D_PrespectiveTransformPara, *LPDG3D_PrespectiveTransformPara;

//ViewPort Transform(~视口变换)
typedef struct
{
	int nUserWidth;		//窗口视口宽度
	int nUserHeight;	//窗口视口高度
} DG3D_ViewPortTransformPara, *LPDG3D_ViewPortTransformPara;

//Coords Transform(~坐标变换)
typedef struct
{
	DG3D_WorldTransformPara sWorldTransformPara;				//世界变换系数
	DG3D_ViewTransformPara sViewTransformPara;					//取景变换系数
	DG3D_PrespectiveTransformPara sPrespectiveTransformPara;	//投影变换系数
	DG3D_ViewPortTransformPara sViewPortTransformPara;			//视口变换系数
} DG3D_CoordsTransformPara, *LPDG3D_CoordsTransformPara;

//Enum Definition(Vertex顶点类型)
enum Vertex3DType
{
	Vertex3D_Type_Base = 0,							//Base类型
	Vertex3D_Type_Texture = 1,						//Texture类型
	Vertex3D_Type_Normal = 2,						//Normal类型
	Vertex3D_Type_Normal_Texture = 3,				//NormalTexture类型
	Vertex3D_Type_Normal_Specular_Texture = 4,		//NormalSpecularTexture类型
};

//Enum Definition(Light光源类型)
enum LightType
{
	LightType_Point = 0,							//Point点光源
	LightType_Direction = 1,						//Direction平行光源
	LightType_Spot = 2,								//Spot聚光灯光源
};

//Class Definition
class DIRECTGRAPHICS3D_API DirectGraphics3D
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;						//The Direct3D 9 Render Device(~DirectGraphics3D d3d9设备)
	LPDIRECT3DVERTEXBUFFER9 m_pD3D9VertexBuffer;			//The Direct3D 9 Vertex Buffer(~DirectGraphics3D d3d9顶点缓存)
	LPDIRECT3DINDEXBUFFER9 m_pD3D9IndexBuffer;				//The Direct3D 9 Index  Buffer(~DirectGraphics3D d3d9索引缓存)

private:
	LPDIRECT3DTEXTURE9 m_pD3D9Texture;						//The Direct3D 9 Texture(~DirectGraphics3D d3d9纹理)

	CRITICAL_SECTION m_cs;									//Thread Safe(CriticalSection)
	bool m_bThreadSafe;										//Thread Safe Status

public:
	DirectGraphics3D();				//DirectGraphics3D Constructor Function
	virtual ~DirectGraphics3D();	//DirectGraphics3D Destructor  Function

	//构造
	DirectGraphics3D(IDirect3DDevice9* pD3D9Device);	//DirectGraphics3D Constructor Function(D3D9设备传入)(重载+1)

	//访问
	virtual IDirect3DDevice9* DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DGetDevice(void) const;					//DirectGraphics3D Get D3D9 Device 获取D3D9设备
	virtual IDirect3DVertexBuffer9* DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DGetVertexBuffer(void) const;		//DirectGraphics3D Get D3D9 Vertex Buffer 获取D3D9顶点缓存
	virtual IDirect3DIndexBuffer9* DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DGetIndexBuffer(void) const;			//DirectGraphics3D Get D3D9 Index Buffer 获取D3D9索引缓存
	virtual IDirect3DTexture9* DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DGetTexture(void) const;					//DirectGraphics3D Get D3D9 Texture 获取D3D9纹理

	//控制
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DSetDevice(IDirect3DDevice9* pD3D9Device);							//DirectGraphics3D Set D3D9 Device 设置D3D9设备
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DSetVertexBuffer(IDirect3DVertexBuffer9* pD3D9VertexBuffer);		//DirectGraphics3D Set D3D9 Vertex Buffer 设置D3D9顶点缓存
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DSetIndexBuffer(IDirect3DIndexBuffer9* pD3D9IndexBuffer);			//DirectGraphics3D Set D3D9 Index Buffer 设置D3D9索引缓存
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DSetTexture(IDirect3DTexture9* pD3D9Texture);						//DirectGraphics3D Set D3D9 Texture 设置D3D9纹理

	//重置(丢失设备)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DReset(void);										//DirectGraphics3D Reset D3D9重置(Reset之后需要调用Init函数重新初始化)

	//初始化
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(int nPlane);									//DirectGraphics3D Initialization(初始化)(3D基本顶点格式)(平面数)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(int nPlane, LPCWSTR lpszStrTexture);			//DirectGraphics3D Initialization(初始化)(3D纹理顶点格式)(平面数)(纹理路径)(重载+1)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane);		//DirectGraphics3D Initialization(初始化)(重载+2)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture);								//DirectGraphics3D Initialization(初始化)(重载+3)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(D3DPOOL ePool, DWORD Usage, Vertex3DType eVertex3DType, int nPlane);							//DirectGraphics3D Initialization(初始化)(重载+4)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInit(D3DPOOL ePool, DWORD Usage, Vertex3DType eVertex3DType, int nPlane, LPCWSTR lpszStrTexture);	//DirectGraphics3D Initialization(初始化)(重载+5)
	
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DBase(UINT nCount);																//DirectGraphics3D Initialization(初始化)(3D基本顶点格式)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);					//DirectGraphics3D Initialization(初始化)(3D纹理顶点格式)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DNormal(UINT nCount);															//DirectGraphics3D Initialization(初始化)(3D法线顶点格式)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DNormalTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);			//DirectGraphics3D Initialization(初始化)(3D法线纹理顶点格式)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DNormalSpecularTexture(UINT nCount, LPCWSTR pStr, UINT nWidth, UINT nHeight);	//DirectGraphics3D Initialization(初始化)(3D法线镜面反射纹理顶点格式)

	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);					//DirectGraphics3D Initialization(初始化)(3D纹理顶点格式)(从内存读取纹理)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DNormalTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);			//DirectGraphics3D Initialization(初始化)(3D法线纹理顶点格式)(从内存读取纹理)
	virtual HRESULT DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DInitVertex3DNormalSpecularTexture(UINT nCount, LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);	//DirectGraphics3D Initialization(初始化)(3D法线镜面反射纹理顶点格式)(从内存读取纹理)

	//坐标(T)(矩阵变换)
	//世界变换
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara);																//DirectGraphics3D WorldSpaceTransform(Scale)(世界变换)(拉伸变换)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara);																//DirectGraphics3D WorldSpaceTransform(Rotate)(世界变换)(旋转变换)(重载+1)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_TranslatePara sTranslatePara);														//DirectGraphics3D WorldSpaceTransform(Translate)(世界变换)(位移变换)(重载+2)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara);									//DirectGraphics3D WorldSpaceTransform(世界变换)(拉伸、旋转变换)(重载+3)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_TranslatePara sTranslatePara);								//DirectGraphics3D WorldSpaceTransform(世界变换)(拉伸、位移变换)(重载+4)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara);							//DirectGraphics3D WorldSpaceTransform(世界变换)(重载+5)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_ScalePara sScalePara, DG3D_RotatePara sRotatePara, DG3D_TranslatePara sTranslatePara);//DirectGraphics3D WorldSpaceTransform(世界变换)(重载+6)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DWorldSpaceTransform(DG3D_WorldTransformPara sWorldTransformPara);												//DirectGraphics3D WorldSpaceTransform(世界变换)(重载+7)
	
	//取景变换
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye);																		//DirectGraphics3D ViewSpaceTransform(取景变换)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt);														//DirectGraphics3D ViewSpaceTransform(取景变换)(重载+1)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewSpaceTransform(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvAt, D3DXVECTOR3* pvUp);									//DirectGraphics3D ViewSpaceTransform(取景变换)(重载+2)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewSpaceTransform(DG3D_ViewTransformPara sViewTransformPara);													//DirectGraphics3D ViewSpaceTransform(取景变换)(重载+3)
	
	//投影变换
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPerspectiveTransform(DG3D_PrespectiveTransformPara sPrespectiveTransformPara);									//DirectGraphics3D PerspectiveTransform(透视/投影变换)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPerspectiveTransform(float fovy, float fAspect, float fZn, float fZf);											//DirectGraphics3D PerspectiveTransform(透视/投影变换)(重载+1)
	
	//视口变换
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewPortTransform(DG3D_ViewPortTransformPara sViewPortTransformPara);											//DirectGraphics3D ViewPortTransform(视口变换)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DViewPortTransform(int nUserWidth, int nUserHeight);															//DirectGraphics3D ViewPortTransform(视口变换)(重载+1)
	
	//坐标变换
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DMatrixTransform(DG3D_WorldTransformPara sWorldTransformPara, DG3D_ViewTransformPara sViewTransformPara, DG3D_PrespectiveTransformPara sPrespectiveTransformPara, DG3D_ViewPortTransformPara sViewPortTransformPara);					//DirectGraphics3D MatrixTransform(坐标变换)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DMatrixTransform(DG3D_CoordsTransformPara sCoordsTransformPara);																																										//DirectGraphics3D MatrixTransform(坐标变换)(重载+1)

	//光照(L)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DLightSettingPoint(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, float fRange, D3DCOLOR dwAmbientLight);																							//DirectGraphics3D Light Setting(光源设置)(点光源)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DLightSettingDirectional(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vDirectional, D3DCOLOR dwAmbientLight);																								//DirectGraphics3D Light Setting(光源设置)(平行光源)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DLightSettingSpot(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);						//DirectGraphics3D Light Setting(光源设置)(聚光灯光源)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DLightSetting(D3DLIGHT9* pD3D9Light, D3DCOLOR dwAmbientLight);																																											//DirectGraphics3D Light Setting(光源设置)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DLightSetting(LightType eLightType, D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXVECTOR3 vPosition, D3DXVECTOR3 vDirectional, float fRange, float fFallOff, float fPhi, float fTheta, D3DCOLOR dwAmbientLight);		//DirectGraphics3D Light Setting(光源设置)

	//材质(M)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DMaterialSetting(D3DMATERIAL9* pD3D9Material);																					//DirectGraphics3D Material Setting(材质设置)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive);								//DirectGraphics3D Material Setting(材质设置)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DMaterialSetting(D3DXCOLOR cAmbient, D3DXCOLOR cDiffuse, D3DXCOLOR cSpecular, D3DXCOLOR cEmissive, float fPower);				//DirectGraphics3D Material Setting(材质设置)

	//填充
	//顶点
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DBase* VertexArray, int nSize);						//DirectGraphics3D Padding Vertex(填充顶点数据)(3D基本顶点格式)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DTexture* VertexArray, int nSize);					//DirectGraphics3D Padding Vertex(填充顶点数据)(3D纹理顶点格式)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DNormal* VertexArray, int nSize);						//DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线顶点格式)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DNormalTexture* VertexArray, int nSize);				//DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线纹理顶点格式)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DNormalSpecularTexture* VertexArray, int nSize);		//DirectGraphics3D Padding Vertex(填充顶点数据)(3D法线镜面反射纹理顶点格式)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nSize);	//DirectGraphics3D Padding Vertex(填充顶点数据)

	//索引
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingIndex(int nPlane);													//DirectGraphics3D Padding Index(填充索引数据)

	//All
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DBase* VertexArray, int nPlane);							//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DTexture* VertexArray, int nPlane);						//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormal* VertexArray, int nPlane);						//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalTexture* VertexArray, int nPlane);					//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DNormalSpecularTexture* VertexArray, int nPlane);			//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DPaddingVertexAndIndex(Vertex3DType eVertex3DType, LPVOID VertexArray, int nPlane);		//DirectGraphics3D Padding Vertex and Index(填充顶点和索引数据)

	//渲染
	//渲染模式
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRenderStateAlphaEnable();																//DirectGraphics3D Render State Setting(开启Alpha混合)//渲染完毕关闭Alpha混合
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRenderStateAlphaDisable();																//DirectGraphics3D Render State Setting(关闭Alpha混合)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRenderStateLightEnable();																//DirectGraphics3D Render State Setting(开启Light光照)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRenderStateLightDisable();																//DirectGraphics3D Render State Setting(关闭Light光照)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRenderStateSetting();																	//DirectGraphics3D Render State Setting(设置渲染模式)

	//渲染
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRender(Vertex3DType eVertex3DType, int nPlane, bool bIsTexture = false);											//DirectGraphics3D Render(渲染)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture = false);							//DirectGraphics3D Render(渲染)
	virtual void DIRECTGRAPHICS3D_CALLMETHOD DirectGraphics3DRender(Vertex3DType eVertex3DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);				//DirectGraphics3D Render(渲染)
};


#endif