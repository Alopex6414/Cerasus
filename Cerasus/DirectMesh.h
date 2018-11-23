/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectMesh.h
* @brief	This File is DirectX Library Common Header.
* @author	Alopex/Helium
* @version	v1.03a
* @date		2018-06-25	v1.00a	alopex	Create This File.
* @date		2018-06-26	v1.01a	alopex	Add Get&Set Function.
* @date		2018-06-26	v1.02a	alopex	Add Reset Function.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __DIRECTMESH_H_
#define __DIRECTMESH_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTMESH_API	__declspec(dllexport)
#else
#define DIRECTMESH_API	__declspec(dllimport)
#endif

#define DIRECTMESH_CALLMETHOD	__stdcall

//Enum Definition
enum DM_GEOMETRY
{
	DM_CUBE = 0,			//立方体
	DM_SPHERE = 1,			//球体
	DM_CYLINDER = 2,		//柱体
	DM_TORUS = 3,			//圆环
	DM_POLYGON = 4,			//多边形
	DM_TEAPOT = 5,			//茶壶
};

//Class Definition
class DIRECTMESH_API DirectMesh
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;		//The Direct3D 9 Render Device(D3D9绘制设备)
	LPD3DXMESH m_pD3DXMeshCube;				//The Direct3D 9 Mesh(D3DX几何体绘制网格)(立方体)
	LPD3DXMESH m_pD3DXMeshSphere;			//The Direct3D 9 Mesh(D3DX几何体绘制网格)(球面体)
	LPD3DXMESH m_pD3DXMeshCylinder;			//The Direct3D 9 Mesh(D3DX几何体绘制网格)(柱体)
	LPD3DXMESH m_pD3DXMeshTorus;			//The Direct3D 9 Mesh(D3DX几何体绘制网格)(圆环体)
	LPD3DXMESH m_pD3DXMeshPolygon;			//The Direct3D 9 Mesh(D3DX几何体绘制网格)(多边形)
	LPD3DXMESH m_pD3DXMeshTeapot;			//The Direct3D 9 Mesh(D3DX几何体绘制网格)(茶壶)

private:
	CRITICAL_SECTION m_cs;					//Thread Safe(CriticalSection)
	bool m_bThreadSafe;						//Thread Safe Status

public:
	DirectMesh();	//DirectMesh Constructor Function(~构造函数)
	~DirectMesh();	//DirectMesh Destructor Function(~析构函数)

	DirectMesh(LPDIRECT3DDEVICE9 pD3D9Device);	//DirectMesh Constructor Function(~构造函数)(重载+1)

	//访问
	virtual LPDIRECT3DDEVICE9 DIRECTMESH_CALLMETHOD DirectMeshGetDevice() const;			//DirectMesh Get D3D9 Device(D3DXMesh获取D3D9设备)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetCube() const;						//DirectMesh Get D3D9 Cube(D3DXMesh获取立方体)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetSphere() const;					//DirectMesh Get D3D9 Sphere(D3DXMesh获取球体)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetCylinder() const;					//DirectMesh Get D3D9 Cylinder(D3DXMesh获取柱体)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetTorus() const;					//DirectMesh Get D3D9 Torus(D3DXMesh获取圆环)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetPolygon() const;					//DirectMesh Get D3D9 Polygon(D3DXMesh获取多边形)
	virtual LPD3DXMESH DIRECTMESH_CALLMETHOD DirectMeshGetTeapot() const;					//DirectMesh Get D3D9 Teapot(D3DXMesh获取茶壶)

	//控制
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetDevice(LPDIRECT3DDEVICE9 pD3D9Device);	//DirectMesh Set D3D9 Device(D3DXMesh设置D3D9设备)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetCube(LPD3DXMESH pD3DXMeshCube);			//DirectMesh Set D3D9 Cube(D3DXMesh设置D3D9立方体)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetSphere(LPD3DXMESH pD3DXMeshSphere);		//DirectMesh Set D3D9 Sphere(D3DXMesh设置D3D9球体)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetCylinder(LPD3DXMESH pD3DXMeshCylinder);	//DirectMesh Set D3D9 Cylinder(D3DXMesh设置D3D9柱体)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetTorus(LPD3DXMESH pD3DXMeshTorus);		//DirectMesh Set D3D9 Torus(D3DXMesh设置D3D9圆环)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetPolygon(LPD3DXMESH pD3DXMeshPolygon);	//DirectMesh Set D3D9 Polygon(D3DXMesh设置D3D9多边形)
	virtual void DIRECTMESH_CALLMETHOD DirectMeshSetTeapot(LPD3DXMESH pD3DXMeshTeapot);		//DirectMesh Set D3D9 Teapot(D3DXMesh设置D3D9茶壶)

	//重置
	virtual void DIRECTMESH_CALLMETHOD DirectMeshReset();									//DirectMesh Reset(D3DXMesh重置设备) 

	//初始化
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitCube(FLOAT fWidth, FLOAT fHeight, FLOAT fDepth);												//DirectMesh Initialization Cube(D3DXMesh初始化立方体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitCylinder(FLOAT fRadius1, FLOAT fRadius2, FLOAT fLength, UINT nSlices, UINT nStacks);			//DirectMesh Initialization Cylinder(D3DXMesh初始化柱体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitSphere(FLOAT fRadius, UINT nSlices, UINT nStacks);												//DirectMesh Initialization Cylinder(D3DXMesh初始化球面体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitTorus(FLOAT fInnerRadius, FLOAT fOuterRadius, UINT nSides, UINT nRings);						//DirectMesh Initialization Cylinder(D3DXMesh初始化圆环体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitPolygon(FLOAT fLength, UINT nSides);															//DirectMesh Initialization Cylinder(D3DXMesh初始化多面体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshInitTeapot();																						//DirectMesh Initialization Cylinder(D3DXMesh初始化茶壶)

	//绘制
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetCube();					//DirectMesh Draw Subset(D3DXMesh绘制立方体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetCylinder();				//DirectMesh Draw Subset(D3DXMesh绘制柱体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetSphere();					//DirectMesh Draw Subset(D3DXMesh绘制球体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetTorus();					//DirectMesh Draw Subset(D3DXMesh绘制圆环体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetPolygon();				//DirectMesh Draw Subset(D3DXMesh绘制多面体)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubsetTeapot();					//DirectMesh Draw Subset(D3DXMesh绘制茶壶)
	virtual HRESULT DIRECTMESH_CALLMETHOD DirectMeshDrawSubset(DM_GEOMETRY eGeometry);	//DirectMesh Draw Subset(D3DXMesh绘制)
};

#endif