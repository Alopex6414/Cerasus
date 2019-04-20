/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		CreasusUnit.cpp
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
#include "CerasusUnit.h"

// Cerasus Class(DirectX绘制3D图元)

//------------------------------------------------------------------
// @Function:	 CCerasusUnit()
// @Purpose: CCerasusUnit构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::CCerasusUnit() :
	m_pDirectGraphics3D(NULL),
	m_nScreenWidth(0),
	m_nScreenHeight(0),
	m_pTextureStr(NULL),
	m_pTextureArr(NULL),
	m_nTextureArrSize(0),
	m_nTextureWidth(0),
	m_nTextureHeight(0),
	m_fUnitAlpha(0.0)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	ZeroMemory(&m_rcUnit, sizeof(RECT));
	ZeroMemory(&m_rcUnitTex, sizeof(RECT));
	ZeroMemory(&m_sCoordsTransformPara, sizeof(S_DX_COORDS_TRANSFORM_PARA));
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusUnit()
// @Purpose: CCerasusUnit析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::~CCerasusUnit()
{
	SAFE_DELETE(m_pDirectGraphics3D);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//----------------------------------------------------------------------
// @Function:	 CCerasusUnit(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: CCerasusUnit构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------------------------------
CCerasusUnit::CCerasusUnit(IDirect3DDevice9* pD3D9Device, bool bSafe) :
	m_nScreenWidth(0),
	m_nScreenHeight(0),
	m_pTextureStr(NULL),
	m_pTextureArr(NULL),
	m_nTextureArrSize(0),
	m_nTextureWidth(0),
	m_nTextureHeight(0),
	m_fUnitAlpha(0.0)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pDirectGraphics3D = new DirectGraphics3D(pD3D9Device);

	ZeroMemory(&m_rcUnit, sizeof(RECT));
	ZeroMemory(&m_rcUnitTex, sizeof(RECT));
	ZeroMemory(&m_sCoordsTransformPara, sizeof(S_DX_COORDS_TRANSFORM_PARA));
}

//------------------------------------------------------------------
// @Function:	 CCerasusUnit(const CCerasusUnit & Object)
// @Purpose: CCerasusUnit拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit::CCerasusUnit(const CCerasusUnit & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

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

	memset(&m_sCoordsTransformPara, 0, sizeof(m_sCoordsTransformPara));
	memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &(Object.m_sCoordsTransformPara), sizeof(Object.m_sCoordsTransformPara));
}

//------------------------------------------------------------------
// @Function:	 operator=(const CCerasusUnit& Object)
// @Purpose: CCerasusUnit重载运算符
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const CCerasusUnit& CCerasusUnit::operator=(const CCerasusUnit& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

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

		memset(&m_sCoordsTransformPara, 0, sizeof(m_sCoordsTransformPara));
		memcpy_s(&m_sCoordsTransformPara, sizeof(m_sCoordsTransformPara), &(Object.m_sCoordsTransformPara), sizeof(Object.m_sCoordsTransformPara));
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetGraphics3D() const
// @Purpose: CCerasusUnit获取DirectGraphics3D接口指针
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics3D* CERASUSUNIT_CALLMETHOD CCerasusUnit::GetGraphics3D() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectGraphics3D;
}

//------------------------------------------------------------------
// @Function:	 GetScreenWidth() const
// @Purpose: CCerasusUnit获取屏幕宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetScreenWidth() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nScreenWidth;
}

//------------------------------------------------------------------
// @Function:	 GetScreenHeight() const
// @Purpose: CCerasusUnit获取屏幕高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetScreenHeight() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nScreenHeight;
}

//------------------------------------------------------------------
// @Function:	 GetTextureStr() const
// @Purpose: CCerasusUnit获取纹理路径
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPWSTR CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTextureStr() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pTextureStr;
}

//------------------------------------------------------------------
// @Function:	 GetTextureArr() const
// @Purpose: CCerasusUnit获取纹理路径
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPVOID CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTextureArr() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pTextureArr;
}

//------------------------------------------------------------------
// @Function:	 GetTextureArrSize() const
// @Purpose: CCerasusUnit获取纹理路径数组长度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTextureArrSize() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nTextureArrSize;
}

//------------------------------------------------------------------
// @Function:	 GetTextureWidth() const
// @Purpose: CCerasusUnit获取纹理宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTextureWidth() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nTextureWidth;
}

//------------------------------------------------------------------
// @Function:	 GetTextureHeight() const
// @Purpose: CCerasusUnit获取纹理高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTextureHeight() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nTextureHeight;
}

//------------------------------------------------------------------
// @Function:	 GetUnitRect() const
// @Purpose: CCerasusUnit获取图元形状
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
RECT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetUnitRect() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_rcUnit;
}

//------------------------------------------------------------------
// @Function:	 GetUnitTextureRect() const
// @Purpose: CCerasusUnit获取纹理形状
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
RECT CERASUSUNIT_CALLMETHOD CCerasusUnit::GetUnitTextureRect() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_rcUnitTex;
}

//------------------------------------------------------------------
// @Function:	 GetUnitAlpha() const
// @Purpose: CCerasusUnit获取图元Alpha
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float CERASUSUNIT_CALLMETHOD CCerasusUnit::GetUnitAlpha() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_fUnitAlpha;
}

//------------------------------------------------------------------
// @Function:	 GetTransformPara() const
// @Purpose: CCerasusUnit坐标变换矩阵
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
S_DX_COORDS_TRANSFORM_PARA CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTransformPara() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara;
}

//------------------------------------------------------------------
// @Function:	 GetScaleX()
// @Purpose: CCerasusUnit比例变换X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetScaleX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX;
}

//------------------------------------------------------------------
// @Function:	 GetScaleY()
// @Purpose: CCerasusUnit比例变换Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetScaleY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY;
}

//------------------------------------------------------------------
// @Function:	 GetScaleZ()
// @Purpose: CCerasusUnit比例变换Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetScaleZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ;
}

//------------------------------------------------------------------
// @Function:	 GetRotateX()
// @Purpose: CCerasusUnit旋转变换X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetRotateX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX;
}

//------------------------------------------------------------------
// @Function:	 GetRotateY()
// @Purpose: CCerasusUnit旋转变换Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetRotateY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY;
}

//------------------------------------------------------------------
// @Function:	 GetRotateZ()
// @Purpose: CCerasusUnit旋转变换Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetRotateZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ;
}

//------------------------------------------------------------------
// @Function:	 GetTranslateX()
// @Purpose: CCerasusUnit位移变换X
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTranslateX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX;
}

//------------------------------------------------------------------
// @Function:	 GetTranslateY()
// @Purpose: CCerasusUnit位移变换Y
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTranslateY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY;
}

//------------------------------------------------------------------
// @Function:	 GetTranslateZ()
// @Purpose: CCerasusUnit位移变换Z
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetTranslateZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ;
}

//------------------------------------------------------------------
// @Function:	 GetAlpha()
// @Purpose: CCerasusUnit Alpha
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
float& CERASUSUNIT_CALLMETHOD CCerasusUnit::GetAlpha()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_fUnitAlpha;
}

//------------------------------------------------------------------
// @Function:	 Create(S_CS_UNIT_PARA sUnit)
// @Purpose: CCerasusUnit初始化图形单元(纹理)
// @Since: v1.00a
// @Para: LPCWSTR pStr		//纹理绝对路径
// @Para: UINT nWidth		//纹理宽度
// @Para: UINT nHeight		//纹理高度
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::Create(S_CS_UNIT_PARA sUnit)
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

	return m_pDirectGraphics3D->CreateTexture(1, m_pTextureStr, m_nTextureWidth, m_nTextureHeight);
}

//------------------------------------------------------------------
// @Function:	 Create(S_CS_UNIT_EX_PARA sUnit)
// @Purpose: CCerasusUnit初始化图形单元(纹理)
// @Since: v1.00a
// @Para: LPCWSTR pStr		//纹理绝对路径
// @Para: UINT nWidth		//纹理宽度
// @Para: UINT nHeight		//纹理高度
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::Create(S_CS_UNIT_EX_PARA sUnit)
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

	return m_pDirectGraphics3D->CreateTexture(1, m_pTextureArr, m_nTextureArrSize, m_nTextureWidth, m_nTextureHeight);
}

//------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: CCerasusUnit重置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::Reset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectGraphics3D->Reset();
}

//------------------------------------------------------------------
// @Function:	 ReCreate()
// @Purpose: CCerasusUnit重新初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT CERASUSUNIT_CALLMETHOD CCerasusUnit::ReCreate()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_pTextureStr)
	{
		return m_pDirectGraphics3D->CreateTexture(1, m_pTextureStr, m_nTextureWidth, m_nTextureHeight);
	}
	else
	{
		return m_pDirectGraphics3D->CreateTexture(1, m_pTextureArr, m_nTextureArrSize, m_nTextureWidth, m_nTextureHeight);
	}

}

//------------------------------------------------------------------
// @Function:	 PaddingVertexAndIndex()
// @Purpose: CCerasusUnit填充顶点索引
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::PaddingVertexAndIndex()
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

	S_DX_VERTEX3D_TEXTURE pVertices[] =
	{
		{ fVertex1X, fVertex1Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex1U, fVertex1V },
		{ fVertex2X, fVertex2Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex2U, fVertex2V },
		{ fVertex3X, fVertex3Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex3U, fVertex3V },
		{ fVertex4X, fVertex4Y, -1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fUnitAlpha), fVertex4U, fVertex4V },
	};

	m_pDirectGraphics3D->PaddingVertexAndIndex(pVertices, 1);
}

//------------------------------------------------------------------
// @Function:	 MatrixTransform()
// @Purpose: CCerasusUnit矩阵变换
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::MatrixTransform()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	S_DX_COORDS_TRANSFORM_PARA sCoordsTransformPara = { 0 };

	//世界变换
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = m_sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = m_sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = m_sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ;

	//取景变换
	sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, -(m_nScreenHeight * 0.5f));

	//投影变换
	sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;;
	sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(m_nScreenWidth * 1.0f / m_nScreenHeight);
	sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fZf = (m_nScreenHeight * 0.5f);

	//视口变换
	sCoordsTransformPara.sViewPortTransformPara.nUserWidth = m_nScreenWidth;
	sCoordsTransformPara.sViewPortTransformPara.nUserHeight = m_nScreenHeight;

	m_pDirectGraphics3D->MatrixTransform(sCoordsTransformPara);
}

//------------------------------------------------------------------
// @Function:	 SetAlphaEnable()
// @Purpose: CCerasusUnit设置Alpha渲染开启
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::SetAlphaEnable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->AlphaEnable();
}

//------------------------------------------------------------------
// @Function:	 SetAlphaDisable()
// @Purpose: CCerasusUnit设置Alpha渲染关闭
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::SetAlphaDisable()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->AlphaDisable();
}

//------------------------------------------------------------------
// @Function:	 SetRenderState()
// @Purpose: CCerasusUnit设置渲染状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::SetRenderState()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					// Alpha混合模式:ADD
	m_pDirectGraphics3D->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirectGraphics3D->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 渲染模式:纹理混合设置
	m_pDirectGraphics3D->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDirectGraphics3D->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);			// D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pDirectGraphics3D->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pDirectGraphics3D->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pDirectGraphics3D->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: CCerasusUnit渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CERASUSUNIT_CALLMETHOD CCerasusUnit::Render()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectGraphics3D->Render(Vertex3D_Type_Texture, 1, true);
}
