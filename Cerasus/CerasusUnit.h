/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CreasusUnit.h
* @brief	This File is CreasusUnit DLL Project.
* @author	Alopex/Helium
* @version	v1.04a
* @date		2018-07-04	v1.00a	alopex	Create Project.
* @date		2018-07-05	v1.01a	alopex	Add Get&Set Function.
* @date		2018-07-05	v1.02a	alopex	Add Translate Function.
* @date		2018-07-06	v1.03a	alopex	Modify Para.
* @date		2018-07-14	v1.04a	alopex	Modify Function.
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

	virtual UINT CERASUSUNIT_CALLMODE CCerasusUnitGetScreenWidth() const;									//CCerasusUnit Get Screen Width(~CCerasusUnit 获取屏幕宽度)
	virtual UINT CERASUSUNIT_CALLMODE CCerasusUnitGetScreenHeight() const;									//CCerasusUnit Get Screen Height(~CCerasusUnit 获取屏幕高度)
	virtual LPWSTR CERASUSUNIT_CALLMODE CCerasusUnitGetTextureStr() const;									//CCerasusUnit Get Texture Path(~CCerasusUnit 获取纹理路径)
	virtual UINT CERASUSUNIT_CALLMODE CCerasusUnitGetTextureWidth() const;									//CCerasusUnit Get Texture Width(~CCerasusUnit 获取纹理宽度)
	virtual UINT CERASUSUNIT_CALLMODE CCerasusUnitGetTextureHeight() const;									//CCerasusUnit Get Texture Height(~CCerasusUnit 获取纹理高度)
	virtual RECT CERASUSUNIT_CALLMODE CCerasusUnitGetUnitRect() const;										//CCerasusUnit Get Unit Rect(~CCerasusUnit 图元形状)
	virtual RECT CERASUSUNIT_CALLMODE CCerasusUnitGetUnitTextureRect() const;								//CCerasusUnit Get Unit Texture Rect(~CCerasusUnit 图元纹理形状)
	virtual float CERASUSUNIT_CALLMODE CCerasusUnitGetUnitAlpha() const;									//CCerasusUnit Get Unit Alpha(~CCerasusUnit 图元Alpha)
	virtual DG3D_CoordsTransformPara CERASUSUNIT_CALLMODE CCerasusUnitGetTransform() const;					//CCerasusUnit Get Transform(~CCerasusUnit 坐标变换矩阵)

	//控制
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetDirectGraphics3D(DirectGraphics3D* pDirectGraphics3D);	//CCerasusUnit Set DirectGraphics3D(~CCerasusUnit 设置DirectGraphics3D接口指针)

	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetScreenWidth(UINT);										//CCerasusUnit Set Screen Width(~CCerasusUnit 获取屏幕宽度)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetScreenHeight(UINT);									//CCerasusUnit Set Screen Height(~CCerasusUnit 获取屏幕高度)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetTextureStr(LPWSTR);									//CCerasusUnit Set Texture Path(~CCerasusUnit 获取纹理路径)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetTextureWidth(UINT);									//CCerasusUnit Set Texture Width(~CCerasusUnit 获取纹理宽度)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetTextureHeight(UINT);									//CCerasusUnit Set Texture Height(~CCerasusUnit 获取纹理高度)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetUnitRect(RECT);										//CCerasusUnit Set Unit Rect(~CCerasusUnit 图元形状)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetUnitTextureRect(RECT);									//CCerasusUnit Set Unit Texture Rect(~CCerasusUnit 图元纹理形状)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetUnitAlpha(float);										//CCerasusUnit Set Unit Alpha(~CCerasusUnit 图元Alpha)
	virtual VOID CERASUSUNIT_CALLMODE CCerasusUnitSetTransform(DG3D_CoordsTransformPara);					//CCerasusUnit Set Transform(~CCerasusUnit 坐标变换矩阵)

	//变换
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetScaleX();											//CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换X)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetScaleY();											//CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换Y)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetScaleZ();											//CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换Z)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetRotateX();											//CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换X)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetRotateY();											//CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换Y)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetRotateZ();											//CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换Z)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetTranslateX();										//CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换X)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetTranslateY();										//CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换Y)
	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetTranslateZ();										//CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换Z)

	virtual float& CERASUSUNIT_CALLMODE CCerasusUnitGetAlpha();												//CCerasusUnit Get Unit Alpha(~CCerasusUnit Alpha)

	//重置
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitReset();												//CCerasusUnit Reset(~CCerasusUnit 重置)

	//初始化
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitInit(CUUint sUnit);									//CCerasusUnit Init(~CCerasusUnit 初始化)

	//填充顶点索引
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitPaddingVertexAndIndex();									//CCerasusUnit PaddingVertexAndIndex(~CCerasusUnit 填充顶点索引)

	//矩阵变换
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitMatrixTransform();										//CCerasusUnit MatrixTransform(~CCerasusUnit 矩阵变换)

	//设置渲染状态
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetAlphaBlendEnable();									//CCerasusUnit Set Alpha Blend Enable(~CCerasusUnit 设置Alpha渲染开启)
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetAlphaBlendDisable();									//CCerasusUnit Set Alpha Blend Disable(~CCerasusUnit 设置Alpha渲染关闭)
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetRenderState();											//CCerasusUnit Set Render States(~CCerasusUnit 设置渲染状态)

	//绘制
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitRender();													//CCerasusUnit Render(~CCerasusUnit 渲染)
};

#endif // !__CERASUSUNIT_H_

