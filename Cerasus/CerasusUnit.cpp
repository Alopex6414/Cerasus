/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CreasusUnit.cpp
* @brief	This File is CreasusUnit DLL Project.
* @author	Alopex/Helium
* @version	v1.07a
* @date		2018-07-04	v1.00a	alopex	Create Project.
* @date		2018-07-05	v1.01a	alopex	Add Get&Set Function.
* @date		2018-07-05	v1.02a	alopex	Add Translate Function.
* @date		2018-07-06	v1.03a	alopex	Modify Para.
* @date		2018-07-14	v1.04a	alopex	Modify Function.
* @date		2018-07-14	v1.05a	alopex	Add Texture Create In Memory Function.
* @date		2018-11-04	v1.06a	alopex	Add LostDevice ReCreate Method.
* @date		2018-11-23	v1.07a	alopex	Alter Call Method.
*/
#include "CerasusUnit.h"

//------------------------------------------------------------------
// @Function:	 CCerasusUnit()
// @Purpose: CCerasusUnit���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::CCerasusUnit()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pDirectGraphics3D = NULL;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_pTextureStr = NULL;
	m_pTextureArr = NULL;
	m_nTextureArrSize = 0;
	m_nTextureWidth = 0;
	m_nTextureHeight = 0;
	m_fUnitAlpha = 0.0f;
	ZeroMemory(&m_rcUnit, sizeof(RECT));
	ZeroMemory(&m_rcUnitTex, sizeof(RECT));
	ZeroMemory(&m_sCoordsTransformPara, sizeof(DG3D_CoordsTransformPara));
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusUnit()
// @Purpose: CCerasusUnit��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::~CCerasusUnit()
{
	SAFE_DELETE(m_pDirectGraphics3D);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnit()
// @Purpose: CCerasusUnit�������캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::CCerasusUnit(const CCerasusUnit & Object)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pDirectGraphics3D = Object.m_pDirectGraphics3D;
	m_nScreenWidth = Object.m_nScreenWidth;
	m_nScreenHeight = Object.m_nScreenHeight;
	m_pTextureStr = Object.m_pTextureStr;
	m_pTextureArr = Object.m_pTextureArr;
	m_nTextureArrSize = Object.m_nTextureArrSize;
	m_nTextureWidth = Object.m_nTextureWidth;
	m_nTextureHeight = Object.m_nTextureHeight;
	m_rcUnit = Object.m_rcUnit;
	m_rcUnitTex = Object.m_rcUnitTex;
	m_fUnitAlpha = Object.m_fUnitAlpha;

	memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &(Object.m_sCoordsTransformPara), sizeof(Object.m_sCoordsTransformPara));
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnit()
// @Purpose: CCerasusUnit���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::CCerasusUnit(IDirect3DDevice9 * pD3D9Device)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pDirectGraphics3D = new DirectGraphics3D(pD3D9Device);
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_pTextureStr = NULL;
	m_pTextureArr = NULL;
	m_nTextureArrSize = 0;
	m_nTextureWidth = 0;
	m_nTextureHeight = 0;
	m_fUnitAlpha = 0.0f;
	ZeroMemory(&m_rcUnit, sizeof(RECT));
	ZeroMemory(&m_rcUnitTex, sizeof(RECT));
	ZeroMemory(&m_sCoordsTransformPara, sizeof(DG3D_CoordsTransformPara));
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetDirectGraphics3D()
// @Purpose: CCerasusUnit��ȡDirectGraphics3D�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D *CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetDirectGraphics3D() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectGraphics3D;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetScreenWidth()
// @Purpose: CCerasusUnit��ȡ��Ļ���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetScreenWidth() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nScreenWidth;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetScreenHeight()
// @Purpose: CCerasusUnit��ȡ��Ļ�߶�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetScreenHeight() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nScreenHeight;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTextureStr()
// @Purpose: CCerasusUnit��ȡ����·��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPWSTR CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTextureStr() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pTextureStr;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTextureWidth()
// @Purpose: CCerasusUnit��ȡ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTextureWidth() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nTextureWidth;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTextureHeight()
// @Purpose: CCerasusUnit��ȡ����߶�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTextureHeight() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nTextureHeight;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetUnitRect()
// @Purpose: CCerasusUnit��ȡͼԪ��״
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
RECT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetUnitRect() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_rcUnit;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetUnitTextureRect()
// @Purpose: CCerasusUnit��ȡ������״
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
RECT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetUnitTextureRect() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_rcUnitTex;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetUnitAlpha()
// @Purpose: CCerasusUnit��ȡͼԪAlpha
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetUnitAlpha() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_fUnitAlpha;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTransform()
// @Purpose: CCerasusUnit����任����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DG3D_CoordsTransformPara CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTransform() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetDirectGraphics3D()
// @Purpose: CCerasusUnit����DirectGraphics3D�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetDirectGraphics3D(DirectGraphics3D * pDirectGraphics3D)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D = pDirectGraphics3D;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetScreenWidth()
// @Purpose: CCerasusUnit������Ļ���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetScreenWidth(UINT nScreenWidth)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_nScreenWidth = nScreenWidth;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetScreenHeight()
// @Purpose: CCerasusUnit������Ļ�߶�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetScreenHeight(UINT nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_nScreenHeight = nScreenHeight;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetTextureStr()
// @Purpose: CCerasusUnit��������·��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetTextureStr(LPWSTR pTextureStr)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pTextureStr = pTextureStr;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetTextureWidth()
// @Purpose: CCerasusUnit����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetTextureWidth(UINT nTextureWidth)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_nTextureWidth = nTextureWidth;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetTextureHeight()
// @Purpose: CCerasusUnit����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetTextureHeight(UINT nTextureHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_nTextureHeight = nTextureHeight;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetUnitRect()
// @Purpose: CCerasusUnit����ͼԪ��״
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetUnitRect(RECT rcUnit)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_rcUnit = rcUnit;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetUnitTextureRect()
// @Purpose: CCerasusUnit����������״
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetUnitTextureRect(RECT rcUnitTex)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_rcUnitTex = rcUnitTex;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetUnitAlpha()
// @Purpose: CCerasusUnit����ͼԪAlpha
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetUnitAlpha(float fUnitAlpha)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_fUnitAlpha = fUnitAlpha;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetTransform()
// @Purpose: CCerasusUnit����任����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetTransform(DG3D_CoordsTransformPara sCoordsTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &sCoordsTransformPara, sizeof(sCoordsTransformPara));
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetScaleX()
// @Purpose: CCerasusUnit�����任X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetScaleX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetScaleY()
// @Purpose: CCerasusUnit�����任Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetScaleY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetScaleZ()
// @Purpose: CCerasusUnit�����任Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetScaleZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetRotateX()
// @Purpose: CCerasusUnit��ת�任X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetRotateX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetRotateY()
// @Purpose: CCerasusUnit��ת�任Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetRotateY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetRotateZ()
// @Purpose: CCerasusUnit��ת�任Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetRotateZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTranslateX()
// @Purpose: CCerasusUnitλ�Ʊ任X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTranslateX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTranslateY()
// @Purpose: CCerasusUnitλ�Ʊ任Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTranslateY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetTranslateZ()
// @Purpose: CCerasusUnitλ�Ʊ任Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetTranslateZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitGetAlpha()
// @Purpose: CCerasusUnit Alpha
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float &CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitGetAlpha()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_fUnitAlpha;
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitReset()
// @Purpose: CCerasusUnit����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitReset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectGraphics3D->DirectGraphics3DReset();
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitReCreate()
// @Purpose: CCerasusUnit���³�ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitReCreate()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_pTextureStr)
	{
		return m_pDirectGraphics3D->DirectGraphics3DInitVertex3DTexture(1, m_pTextureStr, m_nTextureWidth, m_nTextureHeight);
	}
	else
	{
		return m_pDirectGraphics3D->DirectGraphics3DInitVertex3DTexture(1, m_pTextureArr, m_nTextureArrSize, m_nTextureWidth, m_nTextureHeight);
	}

}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitInit()
// @Purpose: CCerasusUnit��ʼ��ͼ�ε�Ԫ(����)
// @Since: v1.00a
// @Para: LPCWSTR pStr		//�������·��
// @Para: UINT nWidth		//������
// @Para: UINT nHeight		//����߶�
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitInit(CUUint sUnit)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	m_nScreenWidth = sUnit.nScreenWidth;
	m_nScreenHeight = sUnit.nScreenHeight;
	m_pTextureStr = sUnit.pTextureStr;
	m_nTextureWidth = sUnit.nTextureWidth;
	m_nTextureHeight = sUnit.nTextureHeight;
	m_fUnitAlpha = sUnit.fUnitAlpha;
	memcpy_s(&m_rcUnit, sizeof(m_rcUnit), &(sUnit.rcUnit), sizeof(sUnit.rcUnit));
	memcpy_s(&m_rcUnitTex, sizeof(m_rcUnitTex), &(sUnit.rcUnitTex), sizeof(sUnit.rcUnitTex));
	memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &(sUnit.sCoordsTransformPara), sizeof(sUnit.sCoordsTransformPara));

	return m_pDirectGraphics3D->DirectGraphics3DInitVertex3DTexture(1, m_pTextureStr, m_nTextureWidth, m_nTextureHeight);
}

HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitInit(CUUintEx sUnit)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	m_nScreenWidth = sUnit.nScreenWidth;
	m_nScreenHeight = sUnit.nScreenHeight;
	m_pTextureArr = sUnit.pTextureArr;
	m_nTextureArrSize = sUnit.nTextureArrSize;
	m_nTextureWidth = sUnit.nTextureWidth;
	m_nTextureHeight = sUnit.nTextureHeight;
	m_fUnitAlpha = sUnit.fUnitAlpha;
	memcpy_s(&m_rcUnit, sizeof(m_rcUnit), &(sUnit.rcUnit), sizeof(sUnit.rcUnit));
	memcpy_s(&m_rcUnitTex, sizeof(m_rcUnitTex), &(sUnit.rcUnitTex), sizeof(sUnit.rcUnitTex));
	memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &(sUnit.sCoordsTransformPara), sizeof(sUnit.sCoordsTransformPara));

	return m_pDirectGraphics3D->DirectGraphics3DInitVertex3DTexture(1, m_pTextureArr, m_nTextureArrSize, m_nTextureWidth, m_nTextureHeight);
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitPaddingVertexAndIndex()
// @Purpose: CCerasusUnit��䶥������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitPaddingVertexAndIndex()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	float fVertex1X = 0.0f;
	float fVertex2X = 0.0f;
	float fVertex3X = 0.0f;
	float fVertex4X = 0.0f;
	float fVertex1Y = 0.0f;
	float fVertex2Y = 0.0f;
	float fVertex3Y = 0.0f;
	float fVertex4Y = 0.0f;

	float fVertex1U = 0.0f;
	float fVertex2U = 0.0f;
	float fVertex3U = 0.0f;
	float fVertex4U = 0.0f;
	float fVertex1V = 0.0f;
	float fVertex2V = 0.0f;
	float fVertex3V = 0.0f;
	float fVertex4V = 0.0f;

	fVertex1X = -(m_nScreenWidth * 0.5f) + m_rcUnit.left * 1.0f;
	fVertex1Y = (m_nScreenHeight * 0.5f) - m_rcUnit.top * 1.0f;
	fVertex2X = -(m_nScreenWidth * 0.5f) + m_rcUnit.right * 1.0f;
	fVertex2Y = (m_nScreenHeight * 0.5f) - m_rcUnit.top * 1.0f;
	fVertex3X = -(m_nScreenWidth * 0.5f) + m_rcUnit.right * 1.0f;
	fVertex3Y = (m_nScreenHeight * 0.5f) - m_rcUnit.bottom * 1.0f;
	fVertex4X = -(m_nScreenWidth * 0.5f) + m_rcUnit.left * 1.0f;
	fVertex4Y = (m_nScreenHeight * 0.5f) - m_rcUnit.bottom * 1.0f;

	fVertex1U = (float)(m_rcUnitTex.left * 1.0f / m_nTextureWidth);
	fVertex1V = (float)(m_rcUnitTex.top * 1.0f / m_nTextureHeight);
	fVertex2U = (float)(m_rcUnitTex.right * 1.0f / m_nTextureWidth);
	fVertex2V = (float)(m_rcUnitTex.top * 1.0f / m_nTextureHeight);
	fVertex3U = (float)(m_rcUnitTex.right * 1.0f / m_nTextureWidth);
	fVertex3V = (float)(m_rcUnitTex.bottom * 1.0f / m_nTextureHeight);
	fVertex4U = (float)(m_rcUnitTex.left * 1.0f / m_nTextureWidth);
	fVertex4V = (float)(m_rcUnitTex.bottom * 1.0f / m_nTextureHeight);

	Vertex3DTexture pVertices[] = 
	{
		{ fVertex1X, fVertex1Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex1U, fVertex1V },
		{ fVertex2X, fVertex2Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex2U, fVertex2V },
		{ fVertex3X, fVertex3Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex3U, fVertex3V },
		{ fVertex4X, fVertex4Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex4U, fVertex4V },
	};

	m_pDirectGraphics3D->DirectGraphics3DPaddingVertexAndIndex(pVertices, 1);
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitMatrixTransform()
// @Purpose: CCerasusUnit����任
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitMatrixTransform()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DG3D_CoordsTransformPara sCoordsTransformPara = { 0 };

	//����任
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ;

	//ȡ���任
	sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(m_nScreenHeight * 0.5f));

	//ͶӰ�任
	sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
	sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(m_nScreenWidth * 1.0f / m_nScreenHeight);
	sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fZf = (m_nScreenHeight * 0.5f);

	//�ӿڱ任
	sCoordsTransformPara.sViewPortTransformPara.nUserWidth = m_nScreenWidth;
	sCoordsTransformPara.sViewPortTransformPara.nUserHeight = m_nScreenHeight;

	m_pDirectGraphics3D->DirectGraphics3DMatrixTransform(sCoordsTransformPara);
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetAlphaBlendEnable()
// @Purpose: CCerasusUnit����Alpha��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetAlphaBlendEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->DirectGraphics3DRenderStateAlphaEnable();
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetAlphaBlendDisable()
// @Purpose: CCerasusUnit����Alpha��Ⱦ�ر�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetAlphaBlendDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->DirectGraphics3DRenderStateAlphaDisable();
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitSetRenderState()
// @Purpose: CCerasusUnit������Ⱦ״̬
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitSetRenderState()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					//Alpha���ģʽ:ADD
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//��Ⱦģʽ:����������
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDirectGraphics3D->DirectGraphics3DGetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnitRender()
// @Purpose: CCerasusUnit��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::CCerasusUnitRender()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->DirectGraphics3DRender(Vertex3D_Type_Texture, 1, true);
}
