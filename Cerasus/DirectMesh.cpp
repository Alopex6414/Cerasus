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

// DirectX9 Mesh Class(DirectX ���������)

//------------------------------------------------------------------
// @Function:	 DirectMesh()
// @Purpose: DirectMesh���캯��
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
// @Purpose: DirectMesh��������
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
// @Purpose: DirectMesh���캯��
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
// @Purpose: DirectMesh���캯��
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
// @Purpose: DirectMesh���캯��
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
// @Purpose: DirectMesh��ȡD3D9�豸
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ȡD3DXMesh
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
// @Purpose: DirectMesh��ʼ��������
// @Since: v1.00a
// @Para: FLOAT fWidth(Cube������X������)
// @Para: FLOAT fHeight(Cube������Y����߶�)
// @Para: FLOAT fDepth(Cube������Z�������)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateCube(FLOAT fWidth, FLOAT fHeight, FLOAT fDepth)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateBox(m_pD3D9Device, fWidth, fHeight, fDepth, &m_pD3DXMeshCube, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateCylinder()
// @Purpose: DirectMesh��ʼ������
// @Since: v1.00a
// @Para: FLOAT fRadius1(Cylinder������Z�Ḻ����İ뾶��С)
// @Para: FLOAT fRadius2(Cylinder������Z������İ뾶��С)
// @Para: FLOAT fLength(Cylinder������Z��ĳ���)
// @Para: UINT nSlices(Cylinder�������Χ�м�����)
// @Para: UINT nStacks(Cylinder��������˼乲�м���)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateCylinder(FLOAT fRadius1, FLOAT fRadius2, FLOAT fLength, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateCylinder(m_pD3D9Device, fRadius1, fRadius2, fLength, nSlices, nStacks, &m_pD3DXMeshCylinder, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateSphere()
// @Purpose: DirectMesh��ʼ��������
// @Since: v1.00a
// @Para: FLOAT fRadius(Sphere��������Z��ֱ����С)
// @Para: UINT nSlices(Sphere����������������Ƭ��)
// @Para: UINT nStacks(Sphere�������������ߵ�γ����)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateSphere(FLOAT fRadius, UINT nSlices, UINT nStacks)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateSphere(m_pD3D9Device, fRadius, nSlices, nStacks, &m_pD3DXMeshSphere, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateTorus()
// @Purpose: DirectMesh��ʼ��Բ����
// @Since: v1.00a
// @Para: FLOAT fInnerRadius(TorusԲ������ֱ��)
// @Para: FLOAT fOuterRadius(TorusԲ������ֱ��)
// @Para: UINT nSides(TorusԲ������Ȧ�м�����)
// @Para: UINT nRings(TorusԲ������Ȧ�м�����)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreateTorus(FLOAT fInnerRadius, FLOAT fOuterRadius, UINT nSides, UINT nRings)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreateTorus(m_pD3D9Device, fInnerRadius, fOuterRadius, nSides, nRings, &m_pD3DXMeshTorus, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreatePolygon()
// @Purpose: DirectMesh��ʼ��������
// @Since: v1.00a
// @Para: FLOAT fLength(������߳�)
// @Para: UINT nSides(���������)
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTMESH_CALLMETHOD DirectMesh::CreatePolygon(FLOAT fLength, UINT nSides)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return D3DXCreatePolygon(m_pD3D9Device, fLength, nSides, &m_pD3DXMeshPolygon, NULL);
}

//------------------------------------------------------------------
// @Function:	 CreateTeapot()
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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
// @Purpose: DirectMesh����
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