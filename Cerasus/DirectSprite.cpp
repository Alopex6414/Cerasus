/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectSprite.cpp
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Alice
* @version	v1.28a
* @date		2017-11-28	v1.00a	alopex	Create This Project.
* @date		2017-12-08	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Version Infomation.
* @date		2018-06-22	v1.24a	alopex	Add Struct Definition.
* @date		2018-11-23	v1.25a	alopex	Alter Call Method.
* @date		2019-01-17	v1.26a	alopex	Add Init&ReInit Method.
* @date		2019-01-17	v1.27a	alopex	Add Draw Method.
* @date		2019-04-17	v1.28a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectSprite.h"
#include "DirectThreadSafe.h"

// DirectX精灵(一般用于2D场景渲染)

//------------------------------------------------------------------
// @Function:	 DirectSprite()
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite() :
	m_pD3D9Device(NULL),
	m_pSpriteTexture(NULL),
	m_pSprite(NULL)
{
	m_bThreadSafe = true;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section
}

//------------------------------------------------------------------
// @Function:	 ~DirectSprite()
// @Purpose: DirectSprite析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::~DirectSprite()
{
	SAFE_RELEASE(m_pSpriteTexture);
	SAFE_RELEASE(m_pSprite);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);				// Delete Critical Section
}

//----------------------------------------------------------------------
// @Function:	 DirectSprite(IDirect3DDevice9* pD3D9Device, bool bSafe)
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------------------------------
DirectSprite::DirectSprite(IDirect3DDevice9* pD3D9Device, bool bSafe) :
	m_pD3D9Device(pD3D9Device),
	m_pSpriteTexture(NULL),
	m_pSprite(NULL)
{
	m_bThreadSafe = bSafe;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section
}

//----------------------------------------------------------------------
// @Function:	 DirectSprite(const DirectSprite& Object)
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------------------------------
DirectSprite::DirectSprite(const DirectSprite& Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	m_pD3D9Device = Object.m_pD3D9Device;
	m_pSpriteTexture = Object.m_pSpriteTexture;
	m_pSprite = Object.m_pSprite;
}

//----------------------------------------------------------------------
// @Function:	 operator=(const DirectSprite& Object)
// @Purpose: DirectSprite构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//----------------------------------------------------------------------
const DirectSprite& DirectSprite::operator=(const DirectSprite& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

		m_pD3D9Device = Object.m_pD3D9Device;
		m_pSpriteTexture = Object.m_pSpriteTexture;
		m_pSprite = Object.m_pSprite;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice() const
// @Purpose: DirectSprite获取D3D9设备
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 DIRECTSPRITE_CALLMETHOD DirectSprite::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetTexture() const
// @Purpose: DirectSprite获取纹理
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DTEXTURE9 DIRECTSPRITE_CALLMETHOD DirectSprite::GetTexture() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pSpriteTexture;
}

//------------------------------------------------------------------
// @Function:	 GetSprite() const
// @Purpose: DirectSprite获取精灵
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPD3DXSPRITE DIRECTSPRITE_CALLMETHOD DirectSprite::GetSprite() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pSprite;
}

//------------------------------------------------------------------
// @Function:	 Create(LPCWSTR lpszStr)
// @Purpose: DirectSprite初始化函数
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//精灵纹理路径
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::Create(LPCWSTR lpszStr)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));			// D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));									// D3DXSprite精灵创建

	return S_OK;
}

//---------------------------------------------------------------------------
// @Function:	 Create(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectSprite初始化函数
// @Since: v1.00a
// @Para: LPCVOID pData			//精灵内存数组地址
// @Para: UINT nSize			//精灵内存数组长度
// @Return: None
//---------------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::Create(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, pData, nSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pSpriteTexture));			// D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));																																																// D3DXSprite精灵创建

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 ReCreate(LPCWSTR lpszStr)
// @Purpose: DirectSprite重新加载纹理
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//精灵纹理路径
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::ReCreate(LPCWSTR lpszStr)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	SAFE_RELEASE(m_pSpriteTexture);															// 释放m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);																// 释放m_pSprite
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));			// D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));									// D3DXSprite精灵创建

	return S_OK;
}

//-----------------------------------------------------------------------------
// @Function:	 ReCreate(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
// @Purpose: DirectSprite重新加载纹理
// @Since: v1.00a
// @Para: LPCVOID pData			//精灵内存数组地址
// @Para: UINT nSize			//精灵内存数组长度
// @Return: None
//-----------------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::ReCreate(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	SAFE_RELEASE(m_pSpriteTexture);																																																						// 释放m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);																																																							// 释放m_pSprite
	VERIFY(D3DXCreateTextureFromFileInMemoryEx(m_pD3D9Device, pData, nSize, nWidth, nHeight, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), NULL, NULL, &m_pSpriteTexture));			// D3DXSprite精灵加载纹理
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));																																																// D3DXSprite精灵创建

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 Reset()
// @Purpose: DirectSprite重置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::Reset()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	SAFE_RELEASE(m_pSpriteTexture);
	m_pSprite->OnLostDevice();
}

//------------------------------------------------------------------
// @Function:	 Begin()
// @Purpose: DirectSprite开始渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::Begin()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pSprite->Begin(D3DXSPRITE_ALPHABLEND));
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 End()
// @Purpose: DirectSprite结束渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMETHOD DirectSprite::End()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pSprite->End());
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 GetMatrix(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite获取当前变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::GetMatrix(D3DXMATRIX* pMatrix)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->GetTransform(pMatrix);
}

//------------------------------------------------------------------
// @Function:	 SetMatrix(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite设置当前变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::SetMatrix(D3DXMATRIX* pMatrix)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->SetTransform(pMatrix);
}

//----------------------------------------------------------------------
// @Function:	 Draw(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara)
// @Purpose: DirectSprite设置当前变换矩阵
// @Since: v1.00a
// @Para: DirectSpriteDrawPara* sSpriteDrawPara
// @Return: None
//----------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::Draw(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
}

//----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 Draw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
// @Purpose: DirectSprite绘制精灵
// @Since: v1.00a
// @Para: RECT* pSpriteRect				//绘制矩形区域
// @Para: D3DXVECTOR3* pSpriteCenter	//绘制中心向量
// @Para: D3DXVECTOR3* pSpritePosition	//绘制位置向量
// @Para: D3DCOLOR SpriteColor			//绘制颜色
// @Return: None
//----------------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::Draw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->Draw(m_pSpriteTexture, pSpriteRect, pSpriteCenter, pSpritePosition, SpriteColor);
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 DrawScale(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara, float fScaleX, float fScaleY)
// @Purpose: DirectSprite绘制拉伸变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DrawScale(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara, float fScaleX, float fScaleY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, fScaleX, fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DrawScale(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara, S_DX_SPRITE_SCALE_PARA sScalePara)
// @Purpose: DirectSprite绘制拉伸变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DrawScale(S_DX_SPRITE_DRAW_PARA* sSpriteDrawPara, S_DX_SPRITE_SCALE_PARA sScalePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}








//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
// @Purpose: DirectSprite绘制旋转变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
// @Purpose: DirectSprite绘制旋转变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, sRotatePara.fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//---------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
// @Purpose: DirectSprite绘制平移变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, fTranslateX, fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite绘制平移变换
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite绘制变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;
	D3DXMATRIX MatrixRotate;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sTransformPara.sScalePara.fScaleX, sTransformPara.sScalePara.fScaleY, 1.0f);
	D3DXMatrixRotationZ(&MatrixRotate, sTransformPara.sRotatePara.fRotateZ);
	D3DXMatrixTranslation(&MatrixTranslate, sTransformPara.sTranslatePara.fTranslateX, sTransformPara.sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixScale * MatrixRotate * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite绘制变换矩阵
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMETHOD DirectSprite::DirectSpriteDrawTransform(DirectSpriteDrawPara * sSpriteDrawPara, DirectSpriteTransformPara sTransformPara, int nNowY, int nPosY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;
	D3DXMATRIX MatrixRotate;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sTransformPara.sScalePara.fScaleX, sTransformPara.sScalePara.fScaleY, 1.0f);
	D3DXMatrixRotationZ(&MatrixRotate, sTransformPara.sRotatePara.fRotateZ);
	D3DXMatrixTranslation(&MatrixTranslate, sTransformPara.sTranslatePara.fTranslateX, sTransformPara.sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixScale * MatrixRotate * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	if (nNowY >= nPosY)
	{
		m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	}
	m_pSprite->SetTransform(&MatrixNative);
}
