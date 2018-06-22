/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSound.h
* @brief	This Program is DirectSound DLL Project.
* @author	Alopex/Helium
* @version	v1.23a
* @date		2017-10-31	v1.00a	alopex	Create Project
* @date		2017-12-03	v1.01a	alopex	Add Enum
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Get Members Function.
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

	//DirectSound����
	LPDIRECTSOUND8 DIRECTSOUND_CALLMODE DirectSoundGetSound(void) const;					//DirectSound Get Sound(DirectSound��ȡIDirectSound8�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMODE DirectSoundGetSoundBuffer(void) const;			//DirectSound Get SoundBuffer(DirectSound��ȡIDirectSoundBuffer�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMODE DirectSoundGetSoundPrimary(void) const;		//DirectSound Get SoundBuffer(DirectSound��ȡIDirectSoundBuffer�ӿ�ָ��:������)
	LPDIRECTSOUND3DBUFFER DIRECTSOUND_CALLMODE DirectSoundGetSound3DBuffer(void) const;		//DirectSound Get Sound3DBuffer(DirectSound��ȡIDirectSound3DBuffer�ӿ�ָ��)
	LPDIRECTSOUND3DLISTENER DIRECTSOUND_CALLMODE DirectSoundGetSound3DListener(void) const;	//DirectSound Get Sound3DListener(DirectSound��ȡIDirectSound3DBuffer�ӿ�ָ��:��������)
	
	//DirectSound����
	void DIRECTSOUND_CALLMODE DirectSoundSetSound(LPDIRECTSOUND8 pDirectSound);									//DirectSound Set Sound(DirectSound����IDirectSound8�ӿ�ָ��)
	void DIRECTSOUND_CALLMODE DirectSoundSetSoundBuffer(LPDIRECTSOUNDBUFFER pDirectSoundBuffer);				//DirectSound Set SoundBuffer(DirectSound����IDirectSoundBuffer�ӿ�ָ��)
	void DIRECTSOUND_CALLMODE DirectSoundSetSoundPrimary(LPDIRECTSOUNDBUFFER pDirectSoundPrimary);				//DirectSound Set SoundBuffer(DirectSound����IDirectSoundBuffer�ӿ�ָ��:������)
	void DIRECTSOUND_CALLMODE DirectSoundSetSound3DBuffer(LPDIRECTSOUND3DBUFFER pDirectSound3DBuffer);			//DirectSound Set Sound3DBuffer(DirectSound����IDirectSound3DBuffer�ӿ�ָ��)
	void DIRECTSOUND_CALLMODE DirectSoundSetSound3DListener(LPDIRECTSOUND3DLISTENER pDirectSound3DListener);	//DirectSound Set Sound3DListener(DirectSound����IDirectSound3DBuffer�ӿ�ָ��:��������)

	//DirectSound��ʼ��
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd);												//DirectSound Initialize(SoundCoopFlags:Normal)
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd, DWORD dwSoundCoopFlags);						//DirectSound Initialize(����+1)
	HRESULT DIRECTSOUND_CALLMODE DirectSoundInit(HWND hWnd, DirectSoundCoopFlags eDirectSoundCoopFlags);	//DirectSound Initialize(����+2)
	HRESULT DIRECTSOUND_CALLMODE DirectSound3DInit(HWND hWnd);												//DirectSound3D Initialize(SoundCoopFlags:Priority)

	//DirectSound����
	HRESULT DIRECTSOUND_CALLMODE DirectSoundLoadWave(LPWSTR lpszFileName);			//DirectSound Load Wave(����Wav)
	HRESULT DIRECTSOUND_CALLMODE DirectSoundLoad3DWave(LPWSTR lpszFileName);		//DirectSound Load 3D Wave(����Wav:3D)

	//DirectSound����
	void DIRECTSOUND_CALLMODE DirectSoundPlay(void);	//DirectSound Play Wave(Once)(���β���)
	void DIRECTSOUND_CALLMODE DirectSoundPlay(DirectSoundPlayState eDSPlayState_X);	//DirectSound Play Wave(���β���/ѭ������)(����+1)
	void DIRECTSOUND_CALLMODE DirectSoundPlayOnce(void);//DirectSound Play Wave(Once)(���β���)
	void DIRECTSOUND_CALLMODE DirectSoundPlayLoop(void);//DirectSound Play Wave(Loop)(ѭ������)
	void DIRECTSOUND_CALLMODE DirectSoundStop(void);//DirectSound Stop Play(ֹͣ����)
	void DIRECTSOUND_CALLMODE DirectSoundSetVolume(LONG lVolume);//DirectSound SetVolume(��������)
	void DIRECTSOUND_CALLMODE DirectSoundSetFrequency(DWORD dwFrequency);//DirectSound SetFrequency(����Ƶ��)
	void DIRECTSOUND_CALLMODE DirectSoundSetPan(LONG lPan);//DirectSound SetPan(No 3D Voice)(��������ƽ��:��֧��3D)
	void DIRECTSOUND_CALLMODE DirectSoundSetCurrentPosition(DWORD dwNewPositon);//DirectSound SetCurrentPosition(���ò��Ž���)
};

#endif