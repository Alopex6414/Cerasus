/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSound.h
* @brief	This Program is DirectSound DLL Project.
* @author	Alopex/Helium
* @version	v1.22a
* @date		2017-10-31	v1.00a	alopex	Create Project
* @date		2017-12-03	v1.01a	alopex	Add Enum
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library
* @date		2018-1-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.22a	alopex	Add Macro Call Mode.
*/
#pragma once

#ifndef __DIRECTSOUND_H_
#define __DIRECTSOUND_H_

//Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTSOUND_API	__declspec(dllexport)
#else
#define DIRECTSOUND_API	__declspec(dllimport)
#endif

#define DIRECTSOUND_CALLMODE	__stdcall

//Class Definetion
#define DSVOLUME_DB(Volume)	((LONG)(-30*(100 - Volume)))	//����(�ֱ�)

//Enum Definetion
//DirectSound�豸Э������
enum DirectSoundCoopFlags
{
	DSCoopFlags_Normal = 0,			//DSSCL_NORMAL(����)
	DSCoopFlags_Priority = 1,		//DSSCL_PRIORITY(����)
	DSCoopFlags_Exclusive = 2,		//DSSCL_EXCLUSIVE(��ռ)
	DSCoopFlags_WritePrimary = 3,	//DSSCL_WRITEPRIMARY(��ȫ����)
};

//DirectSound����״̬
enum DirectSoundPlayState
{
	DSPlayState_Loop = 0,	//PlayState:Loop(ѭ������)
	DSPlayState_Once = 1,	//PlayState:Once(���β���)
};

//Class
class DIRECTSOUND_API DirectSound
{
private:
	LPDIRECTSOUND8 m_pDirectSound;	//IDirectSound8 Interface Pointer(IDirectSound8�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER m_pDirectSoundBuffer;	//IDirectSoundBuffer Interface Pointer(IDirectSoundBuffer�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER m_pDirectSoundPrimary;	//IDirectSoundBuffer Interface Pointer(IDirectSoundBuffer�ӿ�ָ��:������)
	LPDIRECTSOUND3DBUFFER m_pDirectSound3DBuffer;	//IDirectSound3DBuffer Interface Pointer(IDirectSound3DBuffer�ӿ�ָ��)
	LPDIRECTSOUND3DLISTENER m_pDirectSound3DListener;	//IDirectSound3DListener Interface Pointer(IDirectSound3DBuffer�ӿ�ָ��:��������)

	DSBUFFERDESC m_DSPrimaryDesc;	//DirectSount Wave Buffer(Main)(������)
	DSBUFFERDESC m_DSBufferDesc;	//DirectSount Wave Buffer(������)

	CRITICAL_SECTION m_cs;			//Thread Safe(CriticalSection)
	bool m_bThreadSafe;				//Thread Safe Status

public:
	DirectSound();	//DirectSound Constructor Function(���캯��)
	~DirectSound();	//DirectSound Destructor Function(��������)

	//DirectSound��ʼ��
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd);	//DirectSound Initialize(SoundCoopFlags:Normal)
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd, DWORD dwSoundCoopFlags);	//DirectSound Initialize
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd, DirectSoundCoopFlags eDirectSoundCoopFlags);	//DirectSound Initialize
	HRESULT DIRECTSOUND_CALLMODE DirectSound3DInit(HWND hWnd);	//DirectSound3D Initialize(SoundCoopFlags:Priority)

	//DirectSound����
	HRESULT DIRECTSOUND_CALLMODE DirectSoundLoadWave(LPWSTR lpszFileName);		//DirectSound Load Wave(����Wav)
	HRESULT DIRECTSOUND_CALLMODE DirectSoundLoad3DWave(LPWSTR lpszFileName);		//DirectSound Load 3D Wave(����Wav:3D)

	//DirectSound����
	void DIRECTSOUND_CALLMODE DirectSoundPlay(void);	//DirectSound Play Wave(Once)(���β���)
	void DIRECTSOUND_CALLMODE DirectSoundPlay(DirectSoundPlayState eDSPlayState_X);	//DirectSound Play Wave(���β���/ѭ������)
	void DIRECTSOUND_CALLMODE DirectSoundPlayOnce(void);//DirectSound Play Wave(Once)(���β���)
	void DIRECTSOUND_CALLMODE DirectSoundPlayLoop(void);//DirectSound Play Wave(Loop)(ѭ������)
	void DIRECTSOUND_CALLMODE DirectSoundStop(void);//DirectSound Stop Play(ֹͣ����)
	void DIRECTSOUND_CALLMODE DirectSoundSetVolume(LONG lVolume);//DirectSound SetVolume(��������)
	void DIRECTSOUND_CALLMODE DirectSoundSetFrequency(DWORD dwFrequency);//DirectSound SetFrequency(����Ƶ��)
	void DIRECTSOUND_CALLMODE DirectSoundSetPan(LONG lPan);//DirectSound SetPan(No 3D Voice)(��������ƽ��:��֧��3D)
	void DIRECTSOUND_CALLMODE DirectSoundSetCurrentPosition(DWORD dwNewPositon);//DirectSound SetCurrentPosition(���ò��Ž���)
};

#endif