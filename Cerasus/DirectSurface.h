/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSurface.h
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Helium
* @version	v1.12a
* @date		2017-12-9	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.12a	alopex	Add Macro Call Mode.
*/
#ifndef __DIRECTSURFACE_H_
#define __DIRECTSURFACE_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTSURFACE_API	__declspec(dllexport)
#else
#define DIRECTSURFACE_API	__declspec(dllimport)
#endif

#define DIRECTSURFACE_CALLMODE	__stdcall

//Class Definition
class DIRECTSURFACE_API DirectSurface
{
private:
	IDirect3DDevice9*	m_pD3D9Device;										//The Direct3D 9 Device(D3D9�����豸)
	IDirect3DSurface9*	m_pD3D9Surface;										//The Direct3D 9 Surface(D3D9���Ʊ���)
	IDirect3DSurface9*	m_pD3D9BackSurface;									//The Direct3D 9 Surface(D3D9��̨����)

	CRITICAL_SECTION m_cs;													//Thread Safe(CriticalSection)
	bool m_bThreadSafe;														//Thread Safe Status

public:
	DirectSurface();														//DirectSurface Constructor Function(���캯��)
	~DirectSurface();														//DirectSurface Destructor  Function(��������)

	//����
	DirectSurface(IDirect3DDevice9* pD3D9Device);							//DirectSurface Constructor Function(���캯��)

	//����
	IDirect3DDevice9* DIRECTSURFACE_CALLMODE DirectSurfaceGetDevice(void) const;			//DirectSurface Get D3D9Device(��ȡD3D9�豸)
	IDirect3DSurface9* DIRECTSURFACE_CALLMODE DirectSurfaceGetSurface(void) const;			//DirectSurface Get D3D9Surface(��ȡD3D9����)

	//����
	void DIRECTSURFACE_CALLMODE DirectSurfaceSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectSurface Set D3D9Device(����D3D9�豸)
	void DIRECTSURFACE_CALLMODE DirectSurfaceSetSurface(IDirect3DSurface9* pD3D9Surface);	//DirectSurface Set D3D9Surface(��ȡD3D9����)

	//��ʼ��
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceInit(void);							//DirectSurface Initialize(DirectSurface��ʼ��)

	//���ر���
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPWSTR lpszSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);										//DirectSurface Load Surface From File(DirectSurface��������)(�ļ�����)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(IDirect3DSurface9* pSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);							//DirectSurface Load Surface From File(DirectSurface��������)(�������)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);					//DirectSurface Load Surface From File(DirectSurface��������)(�ڴ��ļ�����)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);		//DirectSurface Load Surface From File(DirectSurface��������)(�ڴ����)

	//��Ⱦ����
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceRender(const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);																	//DirectSurface Render Surface(����)
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceRender(DWORD dwColor);																												//DirectSurface Render Surface(��ɫ)				

};


#endif