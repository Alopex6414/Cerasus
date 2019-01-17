/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox 
*     All rights reserved.
*
* @file		DirectSprite.h
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Helium
* @version	v1.26a
* @date		2017-11-28	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Version Infomation.
* @date		2018-06-22	v1.24a	alopex	Add Struct Definition.
* @date		2018-11-23	v1.25a	alopex	Alter Call Method.
* @date		2019-01-17	v1.26a	alopex	Add Init&ReInit Method.
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

#define DIRECTSPRITE_CALLMETHOD	__stdcall

//Struct Definition
typedef struct
{
	float fScaleX;	//Scale�任X�����	//����
	float fScaleY;	//Scale�任Y�����
} DirectSpriteScale, *LPDirectSpriteScale;

typedef struct
{
	float fRotateZ;	//Rotate�任Z�����	//��ת
} DirectSpriteRotate, *LPDirectSpriteRotate;

typedef struct
{
	float fTranslateX;	//Translate�任X�����	//ƽ��
	float fTranslateY;	//Translate�任Y�����
} DirectSpriteTranslate, *LPDirectSpriteTranslate;

//�任����
typedef struct
{
	DirectSpriteScale sScalePara;			//����
	DirectSpriteRotate sRotatePara;			//��ת
	DirectSpriteTranslate sTranslatePara;	//ƽ��
} DirectSpriteTransformPara, *LPDirectSpriteTransformPara;

//���Ʋ���
typedef struct
{
	RECT SpriteRect;						//Sprite��������
	D3DXVECTOR3 SpriteCenter;				//Sprite��������
	D3DXVECTOR3 SpritePosition;				//Spriteλ������
	D3DCOLOR SpriteColor;					//Sprite��ɫ
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
	DirectSprite();				//DirectSprite Constructor Function(~DirectSprite���캯��)
	virtual ~DirectSprite();	//DirectSprite Destructor Function(~DirectSprite��������)

	DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device);													//DirectSprite Constructor Function(Use D3D Device)(~DirectSprite���캯��)(����+1)

	//����
	virtual LPDIRECT3DDEVICE9 DIRECTSPRITE_CALLMETHOD DirectSpriteGetDevice(void) const;			//DirectSprite Get Device
	virtual LPDIRECT3DTEXTURE9 DIRECTSPRITE_CALLMETHOD DirectSpriteGetTexture(void) const;			//DirectSprite Get Texture
	virtual LPD3DXSPRITE DIRECTSPRITE_CALLMETHOD DirectSpriteGetSprite(void) const;					//DirectSprite Get Sprite

	//����
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteSetDevice(LPDIRECT3DDEVICE9 pD3D9Device);		//DirectSprite Set Device
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteSetTexture(LPDIRECT3DTEXTURE9 pSpriteTexture);	//DirectSprite Set Texture
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteSetSprite(LPD3DXSPRITE pSprite);				//DirectSprite Set Sprite

	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteInit(LPCWSTR lpszStr);						//DirectSprite Initialize
	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteReload(LPCWSTR lpszStr);					//DirectSprite Reload(Texture Changed)

	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteInit(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);		//DirectSprite Initialize
	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteReload(LPCVOID pData, UINT nSize, UINT nWidth, UINT nHeight);	//DirectSprite Reload(Texture Changed)

	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteReset(void);									//DirectSprite Reset(D3D9��ʧ�豸)(��Ҫ���³�ʼ��)

	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteBegin(void);								//DirectSprite Begin Draw
	virtual HRESULT DIRECTSPRITE_CALLMETHOD DirectSpriteEnd(void);									//DirectSprite End Draw

	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteGetTransform(D3DXMATRIX* pMatrix);				//DirectSprite Get Transform
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteSetTransform(D3DXMATRIX* pMatrix);				//DirectSprite Set Transform

	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara);																//DirectSprite Draw
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor);	//DirectSprite Draw(����+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX = 1.0f, float fScaleY = 1.0f);				//DirectSprite Draw Scale
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara); 							//DirectSprite Draw Scale(����+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ = 0.0f);									//DirectSprite Draw Rotate
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara);							//DirectSprite Draw Rotate(����+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX = 0.0f, float fTranslateY = 0.0f);	//DirectSprite Draw Translate
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara);				//DirectSprite Draw Translate(����+1)
	virtual void DIRECTSPRITE_CALLMETHOD DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara);			//DirectSprite Draw Transform
};

#endif