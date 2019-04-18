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
	IDirect3DDevice9* m_pD3D9Device;						// Direct3D 9 Device Object(~D3D9设备对象)
	IDirect3DTexture9* m_pD3D9Texture;						// Direct3D 9 Texture Object(~D3D9纹理对象)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	DirectTexture();																	// DirectTexture Construction Function(~DirectTexture构造函数)
	~DirectTexture();																	// DirectTexture Destructoion Function(~DirectTexture析构函数)

	DirectTexture(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// DirectTexture Construction Function(~DirectTexture构造函数)(Overload + 1)
	DirectTexture(const DirectTexture&);												// DirectTexture Construction Function(~DirectTexture拷贝构造函数)

public:
	const DirectTexture& operator=(const DirectTexture&);								// DirectTexture Operator= Function(~DirectTexture运算符重载)

	//访问
	virtual IDirect3DDevice9* DIRECTTEXTURE_CALLMETHOD DirectTextureGetDevice(void) const;				//DirectTexture Get D3D9 Device(获取D3D9设备)
	virtual IDirect3DTexture9* DIRECTTEXTURE_CALLMETHOD DirectTextureGetTexture(void) const;			//DirectTexture Get D3D9 Texture(获取D3D9纹理)

	//控制
	virtual void DIRECTTEXTURE_CALLMETHOD DirectTextureSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectTexture Set D3D9 Device(设置D3D9设备)
	virtual void DIRECTTEXTURE_CALLMETHOD DirectTextureSetTexture(IDirect3DTexture9* pD3D9Texture);		//DirectTexture Set D3D9 Device(设置D3D9纹理)

	//重置
	virtual void DIRECTTEXTURE_CALLMETHOD DirectTextureReset(void);										//DirectTexture Reset(重置D3D9纹理)

	//加载纹理
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTexture(LPWSTR lpszTexture);														//DirectTexture Load Texture(加载纹理)(文件)
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTexture(LPCVOID lpSrcData, UINT nSrcDataSize);									//DirectTexture Load Texture(加载纹理)(内存)
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTextureEx(LPWSTR lpszTexture, UINT nWidth, UINT nHeight);							//DirectTexture Load Texture Ex(加载纹理)(文件)
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTextureEx(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight);		//DirectTexture Load Texture Ex(加载纹理)(内存)
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTextureEx32(LPWSTR lpszTexture, UINT nWidth, UINT nHeight);						//DirectTexture Load Texture Ex(加载纹理)(文件)(Alpha通道)
	virtual HRESULT DIRECTTEXTURE_CALLMETHOD DirectTextureLoadTextureEx32(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight);		//DirectTexture Load Texture Ex(加载纹理)(内存)(Alpha通道)

	//渲染纹理
	virtual void DIRECTTEXTURE_CALLMETHOD DirectTextureSelectTexture(void);								//DirectTexture Select Texture(D3D9设备选中纹理)
};


#endif