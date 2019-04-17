/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectSprite.h
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
#pragma once

#ifndef __DIRECTSPRITE_H_
#define __DIRECTSPRITE_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTSPRITE_API __declspec(dllexport)
#else
#define DIRECTSPRITE_API __declspec(dllimport)
#endif

#define DIRECTSPRITE_CALLMETHOD	__stdcall

// Class Definition
class DIRECTSPRITE_API DirectSprite
{
private:
	LPDIRECT3DDEVICE9 m_pD3D9Device;						// Direct3D 9 Device Object(~D3D9设备对象)
	LPDIRECT3DTEXTURE9 m_pSpriteTexture;					// Direct3D 9 Sprite Texture(~D3D9精灵纹理)
	LPD3DXSPRITE m_pSprite;									// Direct3D 9 Sprite(~D3D9精灵)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	DirectSprite();																	// DirectSprite Construction Function(~DirectSprite构造函数)
	~DirectSprite();																// DirectSprite Destruction Function(~DirectSprite析构函数)

	DirectSprite(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// DirectSprite Construction Function(~DirectSprite构造函数)(Overload + 1)
	DirectSprite(const DirectSprite&);												// DirectSprite Construction Function(~DirectSprite拷贝构造函数)

public:
	const DirectSprite& operator=(const DirectSprite&);								// DirectSprite Operator= Function(~DirectSprite运算符函数)

public:
	LPDIRECT3DDEVICE9					DIRECTSPRITE_CALLMETHOD		GetDevice() const;					// DirectSprite Get Device(~DirectSprite获取D3D9设备指针)
	LPDIRECT3DTEXTURE9					DIRECTSPRITE_CALLMETHOD		GetTexture() const;					// DirectSprite Get Texture(~DirectSprite获取D3D9纹理指针)
	LPD3DXSPRITE						DIRECTSPRITE_CALLMETHOD		GetSprite() const;					// DirectSprite Get Sprite(~DirectSprite获取D3D9精灵指针)

public:
	HRESULT								DIRECTSPRITE_CALLMETHOD		Create(LPCWSTR lpszStr);														// DirectSprite Initialize Sprite(~DirectSprite初始化精灵)
	HRESULT								DIRECTSPRITE_CALLMETHOD		Create(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);					// DirectSprite Initialize Sprite(~DirectSprite初始化精灵)(Overload + 1)
	
	HRESULT								DIRECTSPRITE_CALLMETHOD		ReCreate(LPCWSTR lpszStr);														// DirectSprite Re-Create Sprite(~DirectSprite初始化精灵)
	HRESULT								DIRECTSPRITE_CALLMETHOD		ReCreate(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);					// DirectSprite Re-Create Sprite(~DirectSprite初始化精灵)(Overload + 1)

	void								DIRECTSPRITE_CALLMETHOD		Reset();																		// DirectSprite Reset(~DirectSprite丢失设备)(需要重新初始化)




	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteBegin(void);								//DirectSprite Begin Draw
	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteEnd(void);									//DirectSprite End Draw

	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteGetTransform(D3DXMATRIX* pMatrix);				//DirectSprite Get Transform
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteSetTransform(D3DXMATRIX* pMatrix);				//DirectSprite Set Transform

	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara);																//DirectSprite Draw
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor);	//DirectSprite Draw(重载+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX = 1.0f, float fScaleY = 1.0f);				//DirectSprite Draw Scale
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara); 							//DirectSprite Draw Scale(重载+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ = 0.0f);									//DirectSprite Draw Rotate
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara);							//DirectSprite Draw Rotate(重载+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX = 0.0f, float fTranslateY = 0.0f);	//DirectSprite Draw Translate
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara);				//DirectSprite Draw Translate(重载+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara);			//DirectSprite Draw Transform
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara, int nNowY, int nPosY);//DirectSprite Draw Transform
};

#endif