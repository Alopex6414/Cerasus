/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
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
	IDirect3DDevice9*	m_pD3D9Device;					// Direct3D 9 Device Object(~D3D9�豸����)
	ID3DXMesh*			m_pD3DXMeshCube;				// Direct3D 9 Device Mesh(~D3DX�������������)(������)
	ID3DXMesh*			m_pD3DXMeshSphere;				// Direct3D 9 Device Mesh(~D3DX�������������)(������)
	ID3DXMesh*			m_pD3DXMeshCylinder;			// Direct3D 9 Device Mesh(~D3DX�������������)(����)
	ID3DXMesh*			m_pD3DXMeshTorus;				// Direct3D 9 Device Mesh(~D3DX�������������)(Բ����)
	ID3DXMesh*			m_pD3DXMeshPolygon;				// Direct3D 9 Device Mesh(~D3DX�������������)(�����)
	ID3DXMesh*			m_pD3DXMeshTeapot;				// Direct3D 9 Device Mesh(~D3DX�������������)(���)

protected:
	CRITICAL_SECTION m_cs;								// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;									// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectMesh();															// DirectMesh Construction Function(~DirectMesh���캯��)
	~DirectMesh();															// DirectMesh Destruction Function(~DirectMesh��������)

	DirectMesh(IDirect3DDevice9* pD3D9Device, bool bSafe = true);			// DirectMesh Construction Function(~DirectMesh���캯��)(Overload + 1)
	DirectMesh(const DirectMesh&);											// DirectMesh Construction Function(~DirectMesh�������캯��)

public:
	const DirectMesh & operator=(const DirectMesh&);						// DirectMesh Operator Overload(~DirectMesh����=)

public:
	IDirect3DDevice9*					DIRECTMESH_CALLMETHOD		GetDevice() const;					// DirectMesh Get D3D9 Device(~D3DXMesh��ȡD3D9�豸)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetCube() const;					// DirectMesh Get D3D9 Cube(D3DXMesh��ȡ������)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetSphere() const;					// DirectMesh Get D3D9 Sphere(D3DXMesh��ȡ����)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetCylinder() const;				// DirectMesh Get D3D9 Cylinder(D3DXMesh��ȡ����)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetTorus() const;					// DirectMesh Get D3D9 Torus(D3DXMesh��ȡԲ��)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetPolygon() const;					// DirectMesh Get D3D9 Polygon(D3DXMesh��ȡ�����)
	ID3DXMesh*							DIRECTMESH_CALLMETHOD		GetTeapot() const;					// DirectMesh Get D3D9 Teapot(D3DXMesh��ȡ���)

public:
	HRESULT								DIRECTMESH_CALLMETHOD		CreateCube(FLOAT fWidth, FLOAT fHeight, FLOAT fDepth);														// DirectMesh Initialization Cube(~D3DXMesh��ʼ��������)
	HRESULT								DIRECTMESH_CALLMETHOD		CreateCylinder(FLOAT fRadius1, FLOAT fRadius2, FLOAT fLength, UINT nSlices, UINT nStacks);					// DirectMesh Initialization Cylinder(~D3DXMesh��ʼ������)
	HRESULT								DIRECTMESH_CALLMETHOD		CreateSphere(FLOAT fRadius, UINT nSlices, UINT nStacks);													// DirectMesh Initialization Sphere(~D3DXMesh��ʼ��������)
	HRESULT								DIRECTMESH_CALLMETHOD		CreateTorus(FLOAT fInnerRadius, FLOAT fOuterRadius, UINT nSides, UINT nRings);								// DirectMesh Initialization Torus(~D3DXMesh��ʼ��Բ����)
	HRESULT								DIRECTMESH_CALLMETHOD		CreatePolygon(FLOAT fLength, UINT nSides);																	// DirectMesh Initialization Polygon(~D3DXMesh��ʼ��������)
	HRESULT								DIRECTMESH_CALLMETHOD		CreateTeapot();																								// DirectMesh Initialization Teapot(~D3DXMesh��ʼ�����)

	void								DIRECTMESH_CALLMETHOD		Reset();																									// DirectMesh Reset(~D3DXMesh�����豸)

	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetCube();																							// DirectMesh Draw Subset(~D3DXMesh����������)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetCylinder();																						// DirectMesh Draw Subset(~D3DXMesh��������)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetSphere();																							// DirectMesh Draw Subset(~D3DXMesh��������)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetTorus();																							// DirectMesh Draw Subset(~D3DXMesh����Բ����)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetPolygon();																						// DirectMesh Draw Subset(~D3DXMesh���ƶ�����)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubsetTeapot();																							// DirectMesh Draw Subset(~D3DXMesh���Ʋ��)
	HRESULT								DIRECTMESH_CALLMETHOD		DrawSubset(E_DX_MESH_GEOMETRY_TYPE eGeometry);																// DirectMesh Draw Subset(~D3DXMesh����)

};

#endif