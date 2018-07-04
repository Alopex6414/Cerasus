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
	UINT nScreenWidth;			//���ڿ��
	UINT nScreenHeight;			//���ڸ߶�
	LPWSTR pTextureStr;			//����·��
	UINT nTextureWidth;			//������
	UINT nTextureHeight;		//����߶�
	RECT rcUnit;				//ͼԪ����
	RECT rcUnitTex;				//�������
	float fUnitAlpha;			//Alphaֵ
	DG3D_CoordsTransformPara sCoordsTransformPara;	//����任
} CUUint, *LPCUUint;

//Class Definition
class CERASUSUNIT_API CCerasusUnit
{
protected:
	DirectGraphics3D* m_pDirectGraphics3D;					//The DirectGraphics3D Class Interface(~CCerasusUnit 3D���Ƶ�Ԫ)

private:
	CRITICAL_SECTION m_cs;									//Thread Safe(CriticalSection)
	bool m_bThreadSafe;										//Thread Safe Status

public:
	UINT m_nScreenWidth;									//CCerasusUnit Window Screen Width(~CCerasusUnit ���ڿ��)
	UINT m_nScreenHeight;									//CCerasusUnit Window Screen Height(~CCerasusUnit ���ڸ߶�)
	LPWSTR m_pTextureStr;									//CCerasusUnit Texture String Path(~CCerasusUnit ����·��)
	UINT m_nTextureWidth;									//CCerasusUnit Texture Width(~CCerasusUnit ����������)
	UINT m_nTextureHeight;									//CCerasusUnit Texture Height(~CCerasusUnit ��������߶�)
	RECT m_rcUnit;											//CCerasusUnit Unit Rect(~CCerasusUnit ͼԪ����λ��)
	RECT m_rcUnitTex;										//CCerasusUnit Unit Texture Rect(~CCerasusUnit �������λ��)
	float m_fUnitAlpha;										//CCerasusUnit Unit Alpha(~CCerasusUnit ͼԪAlphaֵ)

	DG3D_CoordsTransformPara m_sCoordsTransformPara;		//CCerasusUnit Unit Coords Transform Para(~CCerasusUnit ͼԪ����任����)

public:
	CCerasusUnit();											//CCerasusUnit Constructor Function(~CCerasusUnit ���캯��)
	~CCerasusUnit();										//CCerasusUnit Destructor Function(~CCerasusUnit ��������)

	//����
	CCerasusUnit(IDirect3DDevice9* pD3D9Device);			//CCerasusUnit Constructor Function(~CCerasusUnit ���캯��)(����+1)

	//����
	virtual DirectGraphics3D* CERASUSUNIT_CALLMODE CCerasusUnitGetDirectGraphics3D() const;					//CCerasusUnit Get DirectGraphics3D(~CCerasusUnit ��ȡDirectGraphics3D�ӿ�ָ��)

	//����
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitSetDirectGraphics3D(DirectGraphics3D* pDirectGraphics3D);	//CCerasusUnit Set DirectGraphics3D(~CCerasusUnit ����DirectGraphics3D�ӿ�ָ��)

	//����
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitReset();												//CCerasusUnit Reset(~CCerasusUnit ����)

	//��ʼ��
	virtual HRESULT CERASUSUNIT_CALLMODE CCerasusUnitInit(CUUint sUnit);									//CCerasusUnit Init(~CCerasusUnit ��ʼ��)

	//��䶥������
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitPaddingVertexAndIndex();									//CCerasusUnit PaddingVertexAndIndex(~CCerasusUnit ��䶥������)

	//����任
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitMatrixTransform();										//CCerasusUnit MatrixTransform(~CCerasusUnit ����任)

	//����
	virtual void CERASUSUNIT_CALLMODE CCerasusUnitRender();													//CCerasusUnit Render(~CCerasusUnit ��Ⱦ)
};

#endif // !__CERASUSUNIT_H_

