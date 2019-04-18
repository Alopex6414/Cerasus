/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectSurface.h
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Alice
* @version	v1.16a
* @date		2017-12-09	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-06-23	v1.14a	alopex	Repair Bug.
* @date		2018-11-23	v1.15a	alopex	Alter Call Method.
* @date		2019-04-16	v1.16a	alopex	Add Notes.
*/
#ifndef __DIRECTSURFACE_H_
#define __DIRECTSURFACE_H_

// Include DirectX Common Header File
#include "DirectCommon.h"

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTSURFACE_API	__declspec(dllexport)
#else
#define DIRECTSURFACE_API	__declspec(dllimport)
#endif

#define DIRECTSURFACE_CALLMETHOD	__stdcall

// Class Definition
class DIRECTSURFACE_API DirectSurface
{
private:
	IDirect3DDevice9*	m_pD3D9Device;						// Direct3D 9 Device Object(~D3D9�豸����)
	IDirect3DSurface9*	m_pD3D9Surface;						// Direct3D 9 Surface Object(~D3D9���Ʊ���)
	IDirect3DSurface9*	m_pD3D9BackSurface;					// Direct3D 9 Back Surface Object(~D3D9��̨����)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectSurface();																	// DirectSurface Construction Function(~DirectSurface���캯��)
	~DirectSurface();																	// DirectSurface Destruction  Function(~DirectSurface��������)

	DirectSurface(IDirect3DDevice9* pD3D9Device, bool bSafe = true);					// DirectSurface Construction Function(~DirectSurface���캯��)(Overload + 1)
	DirectSurface(const DirectSurface&);												// DirectSurface Construction Function(~DirectSurface�������캯��)

public:
	const DirectSurface& operator=(const DirectSurface&);								// DirectSurface Operator= Function(~DirectSurface�������������)

public:
	IDirect3DDevice9*					DIRECTSURFACE_CALLMETHOD		GetDevice() const;					// DirectSurface Get D3D9Device(~DirectSurface��ȡD3D9�豸)
	IDirect3DSurface9*					DIRECTSURFACE_CALLMETHOD		GetSurface() const;					// DirectSurface Get D3D9Surface(~DirectSurface��ȡD3D9����)

public:
	HRESULT								DIRECTSURFACE_CALLMETHOD		Create();																													// DirectSurface Initialize(~DirectSurface��ʼ��)

	HRESULT								DIRECTSURFACE_CALLMETHOD		Load(LPWSTR lpszSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);										// DirectSurface Load Surface From File(~DirectSurface��������)(�ļ�����)
	HRESULT								DIRECTSURFACE_CALLMETHOD		Load(IDirect3DSurface9* pSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);								// DirectSurface Load Surface From File(~DirectSurface��������)(�������)
	HRESULT								DIRECTSURFACE_CALLMETHOD		Load(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);						// DirectSurface Load Surface From File(~DirectSurface��������)(�ڴ��ļ�����)
	HRESULT								DIRECTSURFACE_CALLMETHOD		Load(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);			// DirectSurface Load Surface From File(~DirectSurface��������)(�ļ�����)

	void								DIRECTSURFACE_CALLMETHOD		Render(const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);															// DirectSurface Render Surface(~DirectSurface��Ⱦ:����)
	void								DIRECTSURFACE_CALLMETHOD		Render(DWORD dwColor);																										// DirectSurface Render Surface(~DirectSurface��Ⱦ:��ɫ)

	void								DIRECTSURFACE_CALLMETHOD		RenderYUV(UCHAR* pArrayY, UCHAR* pArrayU, UCHAR* pArrayV, UINT nWidth, UINT nHeight);										// DirectSurface Render Surface YUV(~DirectSurface��Ⱦ:YUVͼ��)

};


#endif