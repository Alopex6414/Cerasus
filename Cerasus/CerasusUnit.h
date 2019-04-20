/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		CreasusUnit.h
* @brief	This File is CreasusUnit DLL Project.
* @author	Alopex/Helium
* @version	v1.08a
* @date		2018-07-04	v1.00a	alopex	Create Project.
* @date		2018-07-05	v1.01a	alopex	Add Get&Set Function.
* @date		2018-07-05	v1.02a	alopex	Add Translate Function.
* @date		2018-07-06	v1.03a	alopex	Modify Para.
* @date		2018-07-14	v1.04a	alopex	Modify Function.
* @date		2018-07-14	v1.05a	alopex	Add Texture Create In Memory Function.
* @date		2018-11-04	v1.06a	alopex	Add LostDevice ReCreate Method.
* @date		2018-11-23	v1.07a	alopex	Alter Call Method.
* @date		2019-04-19	v1.08a	alopex	Add Notes.
*/
#pragma once

#ifndef __CERASUSUNIT_H_
#define __CERASUSUNIT_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"
#include "DirectGraphics3D.h"
#include "DirectThreadSafe.h"

#include "CerasusTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define CERASUSUNIT_API	__declspec(dllexport)
#else
#define CERASUSUNIT_API	__declspec(dllimport)
#endif

#define CERASUSUNIT_CALLMETHOD	__stdcall

// Class Definition
class CERASUSUNIT_API CCerasusUnit
{
private:
	DirectGraphics3D* m_pDirectGraphics3D;					// DirectGraphics3D Class Interface(~CCerasusUnit DirectGraphics3D绘制单元)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status

public:
	UINT m_nScreenWidth;									// CCerasusUnit Window Screen Width(~CCerasusUnit 窗口宽度)
	UINT m_nScreenHeight;									// CCerasusUnit Window Screen Height(~CCerasusUnit 窗口高度)
	LPWSTR m_pTextureStr;									// CCerasusUnit Texture String Path(~CCerasusUnit 纹理路径)
	LPVOID m_pTextureArr;									// CCerasusUnit Texture In Memory Array(~CCerasusUnit 纹理数组地址)
	UINT m_nTextureArrSize;									// CCerasusUnit Texture In Memory Array Size(~CCerasusUnit 纹理数组长度)
	UINT m_nTextureWidth;									// CCerasusUnit Texture Width(~CCerasusUnit 加载纹理宽度)
	UINT m_nTextureHeight;									// CCerasusUnit Texture Height(~CCerasusUnit 加载纹理高度)
	RECT m_rcUnit;											// CCerasusUnit Unit Rect(~CCerasusUnit 图元矩形位置)
	RECT m_rcUnitTex;										// CCerasusUnit Unit Texture Rect(~CCerasusUnit 纹理矩形位置)
	float m_fUnitAlpha;										// CCerasusUnit Unit Alpha(~CCerasusUnit 图元Alpha值)
	S_DX_COORDS_TRANSFORM_PARA	m_sCoordsTransformPara;		// CCerasusUnit Unit Coords Transform Para(~CCerasusUnit 图元坐标变换参数)

public:
	CCerasusUnit();																	// CCerasusUnit Construction Function(~CCerasusUnit 构造函数)
	~CCerasusUnit();																// CCerasusUnit Destruction Function(~CCerasusUnit 析构函数)

	CCerasusUnit(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// CCerasusUnit Construction Function(~CCerasusUnit 构造函数)(Overload + 1)
	CCerasusUnit(const CCerasusUnit&);												// CCerasusUnit Construction Function(~CCerasusUnit 拷贝构造函数)

public:
	const CCerasusUnit& operator=(const CCerasusUnit&);								// CCerasusUnit Operator= Function(~CCerasusUnit 重载运算符函数)

public:
	DirectGraphics3D*					CERASUSUNIT_CALLMETHOD		GetGraphics3D()			const;					// CCerasusUnit Get DirectGraphics3D(~CCerasusUnit 获取DirectGraphics3D接口指针)

	UINT								CERASUSUNIT_CALLMETHOD		GetScreenWidth()		const;					// CCerasusUnit Get Screen Width(~CCerasusUnit 获取屏幕宽度)
	UINT								CERASUSUNIT_CALLMETHOD		GetScreenHeight()		const;					// CCerasusUnit Get Screen Height(~CCerasusUnit 获取屏幕高度)
	LPWSTR								CERASUSUNIT_CALLMETHOD		GetTextureStr()			const;					// CCerasusUnit Get Texture Path(~CCerasusUnit 获取纹理路径)(文件)
	LPVOID								CERASUSUNIT_CALLMETHOD		GetTextureArr()			const;					// CCerasusUnit Get Texture Path(~CCerasusUnit 获取纹理路径)(内存)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureArrSize()		const;					// CCerasusUnit Get Texture Width(~CCerasusUnit 获取纹理路径长度)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureWidth()		const;					// CCerasusUnit Get Texture Width(~CCerasusUnit 获取纹理宽度)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureHeight()		const;					// CCerasusUnit Get Texture Height(~CCerasusUnit 获取纹理高度)
	RECT								CERASUSUNIT_CALLMETHOD		GetUnitRect()			const;					// CCerasusUnit Get Unit Rect(~CCerasusUnit 图元形状)
	RECT								CERASUSUNIT_CALLMETHOD		GetUnitTextureRect()	const;					// CCerasusUnit Get Unit Texture Rect(~CCerasusUnit 图元纹理形状)
	float								CERASUSUNIT_CALLMETHOD		GetUnitAlpha()			const;					// CCerasusUnit Get Unit Alpha(~CCerasusUnit 图元透明度)
	S_DX_COORDS_TRANSFORM_PARA			CERASUSUNIT_CALLMETHOD		GetTransformPara()		const;					// CCerasusUnit Get Transform Parameters(~CCerasusUnit 坐标变换矩阵参数)

	float&								CERASUSUNIT_CALLMETHOD		GetScaleX();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换X)
	float&								CERASUSUNIT_CALLMETHOD		GetScaleY();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换Y)
	float&								CERASUSUNIT_CALLMETHOD		GetScaleZ();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit 比例变换Z)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateX();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换X)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateY();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换Y)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateZ();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit 旋转变换Z)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateX();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换X)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateY();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换Y)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateZ();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit 位移变换Z)
	float&								CERASUSUNIT_CALLMETHOD		GetAlpha();										// CCerasusUnit Get Unit Alpha(~CCerasusUnit 透明的Alpha)

public:
	HRESULT								CERASUSUNIT_CALLMETHOD		Create(S_CS_UNIT_PARA sUnit);					// CCerasusUnit Init(~CCerasusUnit 初始化)
	HRESULT								CERASUSUNIT_CALLMETHOD		Create(S_CS_UNIT_EX_PARA sUnit);				// CCerasusUnit Init(~CCerasusUnit 初始化)

	HRESULT								CERASUSUNIT_CALLMETHOD		Reset();										// CCerasusUnit Reset(~CCerasusUnit 重置)
	HRESULT								CERASUSUNIT_CALLMETHOD		ReCreate();										// CCerasusUnit ReCreate(~CCerasusUnit 丢失设备重新初始化)

	void								CERASUSUNIT_CALLMETHOD		PaddingVertexAndIndex();						// CCerasusUnit PaddingVertexAndIndex(~CCerasusUnit 填充顶点索引)
	
	void								CERASUSUNIT_CALLMETHOD		MatrixTransform();								// CCerasusUnit MatrixTransform(~CCerasusUnit 矩阵变换)

	void								CERASUSUNIT_CALLMETHOD		SetAlphaEnable();								// CCerasusUnit Set Alpha Blend Enable(~CCerasusUnit 设置Alpha渲染开启)
	void								CERASUSUNIT_CALLMETHOD		SetAlphaDisable();								// CCerasusUnit Set Alpha Blend Disable(~CCerasusUnit 设置Alpha渲染关闭)
	void								CERASUSUNIT_CALLMETHOD		SetRenderState();								// CCerasusUnit Set Render States(~CCerasusUnit 设置渲染状态)

	void								CERASUSUNIT_CALLMETHOD		Render();										// CCerasusUnit Render(~CCerasusUnit 渲染)

};

#endif // !__CERASUSUNIT_H_

