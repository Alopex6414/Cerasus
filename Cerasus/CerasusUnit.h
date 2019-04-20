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
	DirectGraphics3D* m_pDirectGraphics3D;					// DirectGraphics3D Class Interface(~CCerasusUnit DirectGraphics3D���Ƶ�Ԫ)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status

public:
	UINT m_nScreenWidth;									// CCerasusUnit Window Screen Width(~CCerasusUnit ���ڿ��)
	UINT m_nScreenHeight;									// CCerasusUnit Window Screen Height(~CCerasusUnit ���ڸ߶�)
	LPWSTR m_pTextureStr;									// CCerasusUnit Texture String Path(~CCerasusUnit ����·��)
	LPVOID m_pTextureArr;									// CCerasusUnit Texture In Memory Array(~CCerasusUnit ���������ַ)
	UINT m_nTextureArrSize;									// CCerasusUnit Texture In Memory Array Size(~CCerasusUnit �������鳤��)
	UINT m_nTextureWidth;									// CCerasusUnit Texture Width(~CCerasusUnit ����������)
	UINT m_nTextureHeight;									// CCerasusUnit Texture Height(~CCerasusUnit ��������߶�)
	RECT m_rcUnit;											// CCerasusUnit Unit Rect(~CCerasusUnit ͼԪ����λ��)
	RECT m_rcUnitTex;										// CCerasusUnit Unit Texture Rect(~CCerasusUnit �������λ��)
	float m_fUnitAlpha;										// CCerasusUnit Unit Alpha(~CCerasusUnit ͼԪAlphaֵ)
	S_DX_COORDS_TRANSFORM_PARA	m_sCoordsTransformPara;		// CCerasusUnit Unit Coords Transform Para(~CCerasusUnit ͼԪ����任����)

public:
	CCerasusUnit();																	// CCerasusUnit Construction Function(~CCerasusUnit ���캯��)
	~CCerasusUnit();																// CCerasusUnit Destruction Function(~CCerasusUnit ��������)

	CCerasusUnit(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// CCerasusUnit Construction Function(~CCerasusUnit ���캯��)(Overload + 1)
	CCerasusUnit(const CCerasusUnit&);												// CCerasusUnit Construction Function(~CCerasusUnit �������캯��)

public:
	const CCerasusUnit& operator=(const CCerasusUnit&);								// CCerasusUnit Operator= Function(~CCerasusUnit �������������)

public:
	DirectGraphics3D*					CERASUSUNIT_CALLMETHOD		GetGraphics3D()			const;					// CCerasusUnit Get DirectGraphics3D(~CCerasusUnit ��ȡDirectGraphics3D�ӿ�ָ��)

	UINT								CERASUSUNIT_CALLMETHOD		GetScreenWidth()		const;					// CCerasusUnit Get Screen Width(~CCerasusUnit ��ȡ��Ļ���)
	UINT								CERASUSUNIT_CALLMETHOD		GetScreenHeight()		const;					// CCerasusUnit Get Screen Height(~CCerasusUnit ��ȡ��Ļ�߶�)
	LPWSTR								CERASUSUNIT_CALLMETHOD		GetTextureStr()			const;					// CCerasusUnit Get Texture Path(~CCerasusUnit ��ȡ����·��)(�ļ�)
	LPVOID								CERASUSUNIT_CALLMETHOD		GetTextureArr()			const;					// CCerasusUnit Get Texture Path(~CCerasusUnit ��ȡ����·��)(�ڴ�)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureArrSize()		const;					// CCerasusUnit Get Texture Width(~CCerasusUnit ��ȡ����·������)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureWidth()		const;					// CCerasusUnit Get Texture Width(~CCerasusUnit ��ȡ������)
	UINT								CERASUSUNIT_CALLMETHOD		GetTextureHeight()		const;					// CCerasusUnit Get Texture Height(~CCerasusUnit ��ȡ����߶�)
	RECT								CERASUSUNIT_CALLMETHOD		GetUnitRect()			const;					// CCerasusUnit Get Unit Rect(~CCerasusUnit ͼԪ��״)
	RECT								CERASUSUNIT_CALLMETHOD		GetUnitTextureRect()	const;					// CCerasusUnit Get Unit Texture Rect(~CCerasusUnit ͼԪ������״)
	float								CERASUSUNIT_CALLMETHOD		GetUnitAlpha()			const;					// CCerasusUnit Get Unit Alpha(~CCerasusUnit ͼԪ͸����)
	S_DX_COORDS_TRANSFORM_PARA			CERASUSUNIT_CALLMETHOD		GetTransformPara()		const;					// CCerasusUnit Get Transform Parameters(~CCerasusUnit ����任�������)

	float&								CERASUSUNIT_CALLMETHOD		GetScaleX();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit �����任X)
	float&								CERASUSUNIT_CALLMETHOD		GetScaleY();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit �����任Y)
	float&								CERASUSUNIT_CALLMETHOD		GetScaleZ();									// CCerasusUnit Get WorldTransform Scale(~CCerasusUnit �����任Z)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateX();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit ��ת�任X)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateY();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit ��ת�任Y)
	float&								CERASUSUNIT_CALLMETHOD		GetRotateZ();									// CCerasusUnit Get WorldTransform Rotate(~CCerasusUnit ��ת�任Z)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateX();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit λ�Ʊ任X)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateY();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit λ�Ʊ任Y)
	float&								CERASUSUNIT_CALLMETHOD		GetTranslateZ();								// CCerasusUnit Get WorldTransform Translate(~CCerasusUnit λ�Ʊ任Z)
	float&								CERASUSUNIT_CALLMETHOD		GetAlpha();										// CCerasusUnit Get Unit Alpha(~CCerasusUnit ͸����Alpha)

public:
	HRESULT								CERASUSUNIT_CALLMETHOD		Create(S_CS_UNIT_PARA sUnit);					// CCerasusUnit Init(~CCerasusUnit ��ʼ��)
	HRESULT								CERASUSUNIT_CALLMETHOD		Create(S_CS_UNIT_EX_PARA sUnit);				// CCerasusUnit Init(~CCerasusUnit ��ʼ��)

	HRESULT								CERASUSUNIT_CALLMETHOD		Reset();										// CCerasusUnit Reset(~CCerasusUnit ����)
	HRESULT								CERASUSUNIT_CALLMETHOD		ReCreate();										// CCerasusUnit ReCreate(~CCerasusUnit ��ʧ�豸���³�ʼ��)

	void								CERASUSUNIT_CALLMETHOD		PaddingVertexAndIndex();						// CCerasusUnit PaddingVertexAndIndex(~CCerasusUnit ��䶥������)
	
	void								CERASUSUNIT_CALLMETHOD		MatrixTransform();								// CCerasusUnit MatrixTransform(~CCerasusUnit ����任)

	void								CERASUSUNIT_CALLMETHOD		SetAlphaEnable();								// CCerasusUnit Set Alpha Blend Enable(~CCerasusUnit ����Alpha��Ⱦ����)
	void								CERASUSUNIT_CALLMETHOD		SetAlphaDisable();								// CCerasusUnit Set Alpha Blend Disable(~CCerasusUnit ����Alpha��Ⱦ�ر�)
	void								CERASUSUNIT_CALLMETHOD		SetRenderState();								// CCerasusUnit Set Render States(~CCerasusUnit ������Ⱦ״̬)

	void								CERASUSUNIT_CALLMETHOD		Render();										// CCerasusUnit Render(~CCerasusUnit ��Ⱦ)

};

#endif // !__CERASUSUNIT_H_

