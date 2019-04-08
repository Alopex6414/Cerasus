/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectMesh.cpp
* @brief	This File is DirectX Library Common Header.
* @author	Alopex/Alice
* @version	v1.04a
* @date		2018-06-25	v1.00a	alopex	Create This File.
* @date		2018-06-26	v1.01a	alopex	Add Get&Set Function.
* @date		2018-06-26	v1.02a	alopex	Add Reset Function.
* @date		2018-11-23	v1.03a	alopex	Alter Call Method.
* @date		2019-04-08	v1.04a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectMesh.h"
#include "DirectThreadSafe.h"

// DirectX9 Mesh Class(DirectX 几何体绘制)

//------------------------------------------------------------------
// @Function:	 DirectMesh()
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectMesh::DirectMesh() :
	m_pD3D9Device(NULL),
	m_pD3DXMeshCube(NULL),
	m_pD3DXMeshSphere(NULL),
	m_pD3DXMeshCylinder(NULL),
	m_pD3DXMeshTorus(NULL),
	m_pD3DXMeshPolygon(NULL),
	m_pD3DXMeshTeapot(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectMesh()
// @Purpose: DirectMesh析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectMesh::~DirectMesh()
{
	SAFE_RELEASE(m_pD3DXMeshCube);
	SAFE_RELEASE(m_pD3DXMeshSphere);
	SAFE_RELEASE(m_pD3DXMeshCylinder);
	SAFE_RELEASE(m_pD3DXMeshTorus);
	SAFE_RELEASE(m_pD3DXMeshPolygon);
	SAFE_RELEASE(m_pD3DXMeshTeapot);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//---------------------------------------------------------------------
// @Function:	 DirectMesh(IDirect3DDevice9 * pD3D9Device, bool bSafe)
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
DirectMesh::DirectMesh(IDirect3DDevice9 * pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pD3DXMeshCube(NULL),
	m_pD3DXMeshSphere(NULL),
	m_pD3DXMeshCylinder(NULL),
	m_pD3DXMeshTorus(NULL),
	m_pD3DXMeshPolygon(NULL),
	m_pD3DXMeshTeapot(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section
}

//---------------------------------------------------------------------
// @Function:	 DirectMesh(const DirectMesh & Object)
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
DirectMesh::DirectMesh(const DirectMesh & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;
	m_pD3DXMeshCube = Object.m_pD3DXMeshCube;
	m_pD3DXMeshSphere = Object.m_pD3DXMeshSphere;
	m_pD3DXMeshCylinder = Object.m_pD3DXMeshCylinder;
	m_pD3DXMeshTorus = Object.m_pD3DXMeshTorus;
	m_pD3DXMeshPolygon = Object.m_pD3DXMeshPolygon;
	m_pD3DXMeshTeapot = Object.m_pD3DXMeshTeapot;
}

//---------------------------------------------------------------------
// @Function:	 operator=(const DirectMesh & Object)
// @Purpose: DirectMesh构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------
const DirectMesh & DirectMesh::operator=(const DirectMesh & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;
		m_pD3DXMeshCube = Object.m_pD3DXMeshCube;
		m_pD3DXMeshSphere = Object.m_pD3DXMeshSphere;
		m_pD3DXMeshCylinder = Object.m_pD3DXMeshCylinder;
		m_pD3DXMeshTorus = Object.m_pD3DXMeshTorus;
		m_pD3DXMeshPolygon = Object.m_pD3DXMeshPolygon;
		m_pD3DXMeshTeapot = Object.m_pD3DXMeshTeapot;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: DirectMesh获取D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9 *DIRECTMESH_CALLMETHOD DirectMesh::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetCube()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetCube() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCube;
}

//------------------------------------------------------------------
// @Function:	 GetSphere()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetSphere() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshSphere;
}

//------------------------------------------------------------------
// @Function:	 GetCylinder()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetCylinder() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCylinder;
}

//------------------------------------------------------------------
// @Function:	 GetTorus()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetTorus() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTorus;
}

//------------------------------------------------------------------
// @Function:	 GetPolygon()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetPolygon() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshPolygon;
}

//------------------------------------------------------------------
// @Function:	 DirectMeshGetTeapot()
// @Purpose: DirectMesh获取D3DXMesh
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXMesh *DIRECTMESH_CALLMETHOD DirectMesh::GetTeapot() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTeapot;
}

//------------------------------------------------------------------
// @Function:	 CreateCube()
// @Purpose: DirectMesh初始化立方体
// @Since: v1.00a
// @Para: FLOAT fWidth(Cube立方体X轴向宽度)
// @Para: FLOAT fHeight(Cube立方体Y轴向高度)
// @Para: FLOAT fDepth(Cube立方体Z轴向深度)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateCube(FLOAT fWidth, FLOAT fHeight, FLOAT fDepth)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateBox(m_pD3D9Device, fWidth, fHeight, fDepth, &m_pD3DXMeshCube, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateCylinder()
// @Purpose: DirectMesh初始化柱体
// @Since: v1.00a
// @Para: FLOAT fRadius1(Cylinder柱体沿Z轴负方向的半径大小)
// @Para: FLOAT fRadius2(Cylinder柱体沿Z正方向的半径大小)
// @Para: FLOAT fLength(Cylinder柱体沿Z轴的长度)
// @Para: UINT nSlices(Cylinder柱体的外围有几个面)
// @Para: UINT nStacks(Cylinder柱体的两端间共有几段)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateCylinder(FLOAT fRadius1, FLOAT fRadius2, FLOAT fLength, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateCylinder(m_pD3D9Device, fRadius1, fRadius2, fLength, nSlices, nStacks, &m_pD3DXMeshCylinder, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateSphere()
// @Purpose: DirectMesh初始化球面体
// @Since: v1.00a
// @Para: FLOAT fRadius(Sphere球面体沿Z轴直径大小)
// @Para: UINT nSlices(Sphere球面体绕主轴线切片数)
// @Para: UINT nStacks(Sphere球面体绕主轴线的纬线数)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateSphere(FLOAT fRadius, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateSphere(m_pD3D9Device, fRadius, nSlices, nStacks, &m_pD3DXMeshSphere, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateTorus()
// @Purpose: DirectMesh初始化圆环体
// @Since: v1.00a
// @Para: FLOAT fInnerRadius(Torus圆环体内直径)
// @Para: FLOAT fOuterRadius(Torus圆环体外直径)
// @Para: UINT nSides(Torus圆环的外圈有几个面)
// @Para: UINT nRings(Torus圆环的内圈有几个面)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateTorus(FLOAT fInnerRadius, FLOAT fOuterRadius, UINT nSides, UINT nRings)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateTorus(m_pD3D9Device, fInnerRadius, fOuterRadius, nSides, nRings, &m_pD3DXMeshTorus, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreatePolygon()
// @Purpose: DirectMesh初始化多面体
// @Since: v1.00a
// @Para: FLOAT fLength(多面体边长)
// @Para: UINT nSides(多面体边数)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreatePolygon(FLOAT fLength, UINT nSides)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreatePolygon(m_pD3D9Device, fLength, nSides, &m_pD3DXMeshPolygon, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateTeapot()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateTeapot()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateTeapot(m_pD3D9Device, &m_pD3DXMeshTeapot, NULL);
}

//------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: DirectMesh重置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTMESH_CALLMETHOD DirectMesh::Reset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	SAFE_RELEASE(m_pD3DXMeshCube);
	SAFE_RELEASE(m_pD3DXMeshSphere);
	SAFE_RELEASE(m_pD3DXMeshCylinder);
	SAFE_RELEASE(m_pD3DXMeshTorus);
	SAFE_RELEASE(m_pD3DXMeshPolygon);
	SAFE_RELEASE(m_pD3DXMeshTeapot);
}










//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetCube()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetCube()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCube->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetCylinder()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetCylinder()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshCylinder->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetSphere()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetSphere()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshSphere->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetTorus()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetTorus()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTorus->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetPolygon()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetPolygon()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshPolygon->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubsetTeaport()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubsetTeapot()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXMeshTeapot->DrawSubset(0);
}

//------------------------------------------------------------------
// @Function:	 DirectMeshDrawSubset()
// @Purpose: DirectMesh绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::DirectMeshDrawSubset(DM_GEOMETRY eGeometry)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	switch (eGeometry)
	{
	case DM_CUBE:
		hr = m_pD3DXMeshCube->DrawSubset(0);
		break;
	case DM_SPHERE:
		hr = m_pD3DXMeshSphere->DrawSubset(0);
		break;
	case DM_CYLINDER:
		hr = m_pD3DXMeshCylinder->DrawSubset(0);
		break;
	case DM_TORUS:
		hr = m_pD3DXMeshTorus->DrawSubset(0);
		break;
	case DM_POLYGON:
		hr = m_pD3DXMeshPolygon->DrawSubset(0);
		break;
	case DM_TEAPOT:
		hr = m_pD3DXMeshTeapot->DrawSubset(0);
		break;
	default:
		break;
	}

	return hr;
}