/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CreasusUnit.h
* @brief	This File is CreasusUnit DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-07-04	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __CERASUSUNIT_H_
#define __CERASUSUNIT_H_

//Include Direct Common Header File
#include "DirectCommon.h"
#include "DirectGraphics3D.h"
#include "DirectThreadSafe.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSUNIT_API	__declspec(dllexport)
#else
#define CERASUSUNIT_API	__declspec(dllimport)
#endif

#define CERASUSUNIT_CALLMODE	__stdcall

//Struct Definition
typedef struct
{
	UINT nScreenWidth;			//窗口宽度
	UINT nScreenHeight;			//窗口高度
	LPWSTR pTextureStr;			//纹理路径
	UINT nTextureWidth;			//纹理宽度
	UINT nTextureHeight;		//纹理高度
	RECT rcUnit;				//图元矩形
	RECT rcUnitTex;				//纹理矩形
	float fUnitAlpha;			//Alpha值
	DG3D_CoordsTransformPara sCoordsTransformPara;	//坐标变换
} CUUint, *LPCUUint;

//Class Definition
class CERASUSUNIT_API CCerasusUnit
{
protected:
	DirectGraphics3D* m_pDirectGraphics3D;					//The DirectGraphics3D Class Interface(~CCerasusUnit 3D绘制单元)

private:
	CRITICAL_SECTION m_cs;									//Thread Safe(CriticalSection)
	bool m_bThreadSafe;										//Thread Safe Status

public:
	UINT m_nScreenWidth;									//CCerasusUnit Window Screen Width(~CCerasusUnit 窗口宽度)
	UINT m_nScreenHeight;									//CCerasusUnit Window Screen Height(~CCerasusUnit 窗口高度)
	LPWSTR m_pTextureStr;									//CCerasusUnit Texture String Path(~CCerasusUnit 纹理路径)
	UINT m_nTextureWidth;									//CCerasusUnit Texture Width(~CCerasusUnit 加载纹理宽度)
	UINT m_nTextureHeight;									//CCerasusUnit Texture Height(~CCerasusUnit 加载纹理高度)
	RECT m_rcUnit;											//CCerasusUnit Unit Rect(~CCerasusUnit 图元矩形位置)
	RECT m_rcUnitTex;										//CCerasusUnit Unit Texture Rect(~CCerasusUnit 纹理矩形位置)
	float m_fUnitAlpha;										//CCerasusUnit Unit Alpha(~CCerasusUnit 图元Alpha值)

	DG3D_CoordsTransformPara m_sCoordsTransformPara;		//CCerasusUnit Unit Coords Transform Para(~CCerasusUnit 图元坐标变换参数)

public:
	CCerasusUnit();											//CCerasusUnit Constructor Function(~CCerasusUnit 构造函数)
	~CCerasusUnit();										//CCerasusUnit Destructor Function(~CCerasusUnit 析构函数)

	//构造
	CCerasusUnit(IDirect3DDevice9* pD3D9Device);			//CCerasusUnit Constructor Function(~CCerasusUnit 构造函数)(重载+1)

	//访问
	virtual DirectGraphics3D* CERASUSUNIT_CALLMODE CCerasusUnitGetDirectGraphics3D() const;					//CCerasusUnit Get DirectGraphics3D(~CCerasusUnit 获取DirectGraphics3D接口指针)

	//控制
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetDirectGraphics3D(DirectGraphics3D* pDirectGraphics3D);	//CCerasusUnit Set DirectGraphics3D(~CCerasusUnit 设置DirectGraphics3D接口指针)

	//重置
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitReset();												//CCerasusUnit Reset(~CCerasusUnit 重置)

	//初始化
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitInit(CUUint sUnit);									//CCerasusUnit Init(~CCerasusUnit 初始化)

	//填充顶点索引
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitPaddingVertexAndIndex();									//CCerasusUnit PaddingVertexAndIndex(~CCerasusUnit 填充顶点索引)

	//矩阵变换
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitMatrixTransform();										//CCerasusUnit MatrixTransform(~CCerasusUnit 矩阵变换)

	//绘制
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitRender();													//CCerasusUnit Render(~CCerasusUnit 渲染)
};

#endif // !__CERASUSUNIT_H_

