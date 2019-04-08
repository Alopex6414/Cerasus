/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectMesh.h
* @brief	This File is DirectX Library Common Header.
* @author	Alopex/Alice
* @version	v1.04a
* @date		2018-06-25	v1.00a	alopex	Create This File.
* @date		2018-06-26	v1.01a	alopex	Add Get&Set Function.
* @date		2018-06-26	v1.02a	alopex	Add Reset Function.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
* @date		2019-04-08	v1.04a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTMESH_H_
#define __DIRECTMESH_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTMESH_API	__declspec(dllexport)
#else
#define DIRECTMESH_API	__declspec(dllimport)
#endif

#define DIRECTMESH_CALLMETHOD	__stdcall

// Class Definition
class DIRECTMESH_API DirectMesh
{
private:
	IDirect3DDevice9*	m_pD3D9Device;					// Direct3D 9 Device Object(~D3D9设备对象)
	ID3DXMesh*			m_pD3DXMeshCube;				// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(立方体)
	ID3DXMesh*			m_pD3DXMeshSphere;				// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(球面体)
	ID3DXMesh*			m_pD3DXMeshCylinder;			// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(柱体)
	ID3DXMesh*			m_pD3DXMeshTorus;				// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(圆环体)
	ID3DXMesh*			m_pD3DXMeshPolygon;				// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(多边形)
	ID3DXMesh*			m_pD3DXMeshTeapot;				// Direct3D 9 Device Mesh(~D3DX几何体绘制网格)(茶壶)

protected:
	CRITICAL_SECTION m_cs;								// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;									// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	DirectMesh();															// DirectMesh Construction Function(~DirectMesh构造函数)
	~DirectMesh();															// DirectMesh Destruction Function(~DirectMesh析构函数)

	DirectMesh(IDirect3DDevice9* pD3D9Device, bool bSafe = true);			// DirectMesh Construction Function(~DirectMesh构造函数)(Overload + 1)
	DirectMesh(const DirectMesh&);											// DirectMesh Construction Function(~DirectMesh拷贝构造函数)

public:
	const DirectMesh & operator=(const DirectMesh&);						// DirectMesh Operator Overload(~DirectMesh重载=)

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