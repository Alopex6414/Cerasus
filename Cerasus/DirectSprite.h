/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox 
*     All rights reserved.
*
* @file		DirectSprite.h
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Helium
* @version	v1.24a
* @date		2017-11-28	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Version Infomation.
* @date		2018-06-22	v1.24a	alopex	Add Struct Definition.
*/
#pragma once

#ifndef __DIRECTSPRITE_H_
#define __DIRECTSPRITE_H_

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTSPRITE_API __declspec(dllexport)
#else
#define DIRECTSPRITE_API __declspec(dllimport)
#endif

#define DIRECTSPRITE_CALLMODE	__stdcall

//Struct Definition
typedef struct
{
	float fScaleX;	//Scale变换X轴比例	//拉伸
	float fScaleY;	//Scale变换Y轴比例
} DirectSpriteScale, *LPDirectSpriteScale;

typedef struct
{
	float fRotateZ;	//Rotate变换Z轴比例	//旋转
} DirectSpriteRotate, *LPDirectSpriteRotate;

typedef struct
{
	float fTranslateX;	//Translate变换X轴比例	//平移
	float fTranslateY;	//Translate变换Y轴比例
} DirectSpriteTranslate, *LPDirectSpriteTranslate;

//变换参数
typedef struct
{
	DirectSpriteScale sScalePara;			//拉伸
	DirectSpriteRotate sRotatePara;			//旋转
	DirectSpriteTranslate sTranslatePara;	//平移
} DirectSpriteTransformPara, *LPDirectSpriteTransformPara;

//绘制参数
typedef struct
{
	RECT SpriteRect;						//Sprite矩形区域
	D3DXVECTOR3 SpriteCenter;				//Sprite中心向量
	D3DXVECTOR3 SpritePosition;				//Sprite位置向量
	D3DCOLOR SpriteColor;					//Sprite颜色
} DirectSpriteDrawPara, *LPDirectSpriteDrawPara;

//Class Definition
class DIRECTSPRITE_API DirectSprite
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;		//The Direct3D 9 Render Device
	LPDIRECT3DTEXTURE9 m_pSpriteTexture;	//The Direct3D 9 Sprite Texture
	LPD3DXSPRITE m_pSprite;					//The Direct3D 9 Sprite

private:
	CRITICAL_SECTION m_cs;					//Thread Safe(CriticalSection)
	bool m_bThreadSafe;						//Thread Safe Status

public:
	DirectSprite();				//DirectSprite Constructor Function(~DirectSprite构造函数)
	virtual ~DirectSprite();	//DirectSprite Destructor Function(~DirectSprite析构函数)

	DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device);					//DirectSprite Constructor Function(Use D3D Device)(~DirectSprite构造函数)(重载+1)

	//访问
	virtual LPDIRECT3DDEVICE9 DIRECTSPRITE_CALLMODE DirectSpriteGetDevice(void) const;				//DirectSprite Get Device
	virtual LPDIRECT3DTEXTURE9 DIRECTSPRITE_CALLMODE DirectSpriteGetTexture(void) const;			//DirectSprite Get Texture
	virtual LPD3DXSPRITE DIRECTSPRITE_CALLMODE DirectSpriteGetSprite(void) const;					//DirectSprite Get Sprite

	//控制
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteSetDevice(LPDIRECT3DDEVICE9 pD3D9Device);		//DirectSprite Set Device
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteSetTexture(LPDIRECT3DTEXTURE9 pSpriteTexture);	//DirectSprite Set Texture
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteSetSprite(LPD3DXSPRITE pSprite);					//DirectSprite Set Sprite

	virtual HRESULT DIRECTSPRITE_CALLMODE DirectSpriteInit(LPCWSTR lpszStr);		//DirectSprite Initialize
	virtual HRESULT DIRECTSPRITE_CALLMODE DirectSpriteReload(LPCWSTR lpszStr);		//DirectSprite Reload(Texture Changed)

	virtual void DIRECTSPRITE_CALLMODE DirectSpriteReset(void);						//DirectSprite Reset(D3D9丢失设备)(需要重新初始化)

	virtual HRESULT DIRECTSPRITE_CALLMODE DirectSpriteBegin(void);							//DirectSprite Begin Draw
	virtual HRESULT DIRECTSPRITE_CALLMODE DirectSpriteEnd(void);							//DirectSprite End Draw

	virtual void DIRECTSPRITE_CALLMODE DirectSpriteGetTransform(D3DXMATRIX* pMatrix);		//DirectSprite Get Transform
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteSetTransform(D3DXMATRIX* pMatrix);		//DirectSprite Set Transform

	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara);																//DirectSprite Draw
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor);	//DirectSprite Draw(重载+1)
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX = 1.0f, float fScaleY = 1.0f);				//DirectSprite Draw Scale
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara); 							//DirectSprite Draw Scale(重载+1)
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ = 0.0f);									//DirectSprite Draw Rotate
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara);							//DirectSprite Draw Rotate(重载+1)
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX = 0.0f, float fTranslateY = 0.0f);	//DirectSprite Draw Translate
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara);					//DirectSprite Draw Translate(重载+1)
	virtual void DIRECTSPRITE_CALLMODE DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara);				//DirectSprite Draw Transform
};

#endif