/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectTexture.h
* @brief	This File is DirectTexture DLL Project.
* @author	Alopex/Alice
* @version	v1.17a
* @date		2017-12-10	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-07-01	v1.14a	alopex	Modify Thread Safe Class.
* @date		2018-07-09	v1.15a	alopex	Add 32 Channel Texture.
* @date		2018-11-23	v1.16a	alopex	Alter Call Method.
* @date		2019-04-18	v1.17a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTTEXTURE_H_
#define __DIRECTTEXTURE_H_

// Include DirectX Common Header File
#include "DirectCommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTTEXTURE_API	__declspec(dllexport)
#else
#define DIRECTTEXTURE_API	__declspec(dllimport)
#endif

#define DIRECTTEXTURE_CALLMETHOD	__stdcall

// Class Definition
class DIRECTTEXTURE_API DirectTexture
{
private:
	IDirect3DDevice9* m_pD3D9Device;						// Direct3D 9 Device Object(~D3D9�豸����)
	IDirect3DTexture9* m_pD3D9Texture;						// Direct3D 9 Texture Object(~D3D9�������)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectTexture();																	// DirectTexture Construction Function(~DirectTexture���캯��)
	~DirectTexture();																	// DirectTexture Destructoion Function(~DirectTexture��������)

	DirectTexture(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// DirectTexture Construction Function(~DirectTexture���캯��)(Overload + 1)
	DirectTexture(const DirectTexture&);												// DirectTexture Construction Function(~DirectTexture�������캯��)

public:
	const DirectTexture& operator=(const DirectTexture&);								// DirectTexture Operator= Function(~DirectTexture���������)

public:
	IDirect3DDevice9*					DIRECTTEXTURE_CALLMETHOD		GetDevice() const;					// DirectTexture Get D3D9 Device(~DirectTexture��ȡD3D9�豸)
	IDirect3DTexture9*					DIRECTTEXTURE_CALLMETHOD		GetTexture() const;					// DirectTexture Get D3D9 Texture(~DirectTexture��ȡD3D9����)

public:
	HRESULT								DIRECTTEXTURE_CALLMETHOD		Create(LPWSTR lpszTexture);																	// DirectTexture Create and Load D3D9 Texture(~DirectTexture��������)(�ļ�)
	HRESULT								DIRECTTEXTURE_CALLMETHOD		Create(LPCVOID lpSrcData, UINT nSrcDataSize);												// DirectTexture Create and Load D3D9 Texture(~DirectTexture��������)(�ڴ�)

	HRESULT								DIRECTTEXTURE_CALLMETHOD		CreateEx(LPWSTR lpszTexture, UINT nWidth, UINT nHeight);									// DirectTexture Create and Load D3D9 Texture Ex(~DirectTexture��������)(�ļ�)
	HRESULT								DIRECTTEXTURE_CALLMETHOD		CreateEx(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight);					// DirectTexture Create and Load D3D9 Texture Ex(~DirectTexture��������)(�ڴ�)

	HRESULT								DIRECTTEXTURE_CALLMETHOD		CreateEx32(LPWSTR lpszTexture, UINT nWidth, UINT nHeight);									// DirectTexture Create and Load D3D9 Texture Ex(~DirectTexture��������)(�ļ�)(Alpha)
	HRESULT								DIRECTTEXTURE_CALLMETHOD		CreateEx32(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight);				// DirectTexture Create and Load D3D9 Texture Ex(~DirectTexture��������)(�ڴ�)(Alpha)

	void								DIRECTTEXTURE_CALLMETHOD		Reset();																					// DirectTexture Reset(~DirectTexture����D3D9����)

	void								DIRECTTEXTURE_CALLMETHOD		Select();																					// DirectTexture Select(~DirectTextureѡ��D3D9����)

};


#endif