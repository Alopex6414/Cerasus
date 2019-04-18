/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectSound.h
* @brief	This Program is DirectSound DLL Project.
* @author	Alopex/Alice
* @version	v1.25a
* @date		2017-10-31	v1.00a	alopex	Create Project
* @date		2017-12-03	v1.01a	alopex	Add Enum
* @date		2017-12-08	v1.11a	alopex	Code Do Not Rely On MSVCR Library
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Get Members Function.
* @date		2018-11-23	v1.24a	alopex	Alter Call Method.
* @date		2019-04-15	v1.24a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTSOUND_H_
#define __DIRECTSOUND_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTSOUND_API	__declspec(dllexport)
#else
#define DIRECTSOUND_API	__declspec(dllimport)
#endif

#define DIRECTSOUND_CALLMETHOD	__stdcall

#define DSVOLUME_DB(V)			((LONG)(-30 * (100 - V)))

// Class Definition
class DIRECTSOUND_API DirectSound
{
private:
	LPDIRECTSOUND8 m_pDirectSound;								// IDirectSound8 Interface Pointer(IDirectSound8�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER m_pDirectSoundBuffer;					// IDirectSoundBuffer Interface Pointer(IDirectSoundBuffer�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER m_pDirectSoundPrimary;					// IDirectSoundBuffer Interface Pointer(IDirectSoundBuffer�ӿ�ָ��:������)
	LPDIRECTSOUND3DBUFFER m_pDirectSound3DBuffer;				// IDirectSound3DBuffer Interface Pointer(IDirectSound3DBuffer�ӿ�ָ��)
	LPDIRECTSOUND3DLISTENER m_pDirectSound3DListener;			// IDirectSound3DListener Interface Pointer(IDirectSound3DBuffer�ӿ�ָ��:��������)

private:
	DSBUFFERDESC m_DSPrimaryDesc;								// DirectSount Wave Buffer(Main)(~DirectSound������)
	DSBUFFERDESC m_DSBufferDesc;								// DirectSount Wave Buffer(~DirectSound������)

protected:
	CRITICAL_SECTION m_cs;										// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;											// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectSound();												// DirectSound Construction Function(~DirectSound���캯��)
	~DirectSound();												// DirectSound Destruction Function(~DirectSound��������)

	DirectSound(bool bSafe);									// DirectSound Construction Function(~DirectSound���캯��)(Overload + 1)
	DirectSound(const DirectSound&);							// DirectSound Construction Function(~DirectSound�������캯��)

public:
	const DirectSound& operator=(const DirectSound&);			// DirectSound Operater= Function(~DirectSound���������'=')

public:
	LPDIRECTSOUND8					DIRECTSOUND_CALLMETHOD		GetSound() const;							// DirectSound Get Sound(DirectSound��ȡIDirectSound8�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER				DIRECTSOUND_CALLMETHOD		GetSoundBuffer() const;						// DirectSound Get SoundBuffer(DirectSound��ȡIDirectSoundBuffer�ӿ�ָ��)
	LPDIRECTSOUNDBUFFER				DIRECTSOUND_CALLMETHOD		GetSoundPrimary() const;					// DirectSound Get SoundBuffer(DirectSound��ȡIDirectSoundBuffer�ӿ�ָ��:������)
	LPDIRECTSOUND3DBUFFER			DIRECTSOUND_CALLMETHOD		GetSound3DBuffer() const;					// DirectSound Get Sound3DBuffer(DirectSound��ȡIDirectSound3DBuffer�ӿ�ָ��)
	LPDIRECTSOUND3DLISTENER			DIRECTSOUND_CALLMETHOD		GetSound3DListener() const;					// DirectSound Get Sound3DListener(DirectSound��ȡIDirectSound3DBuffer�ӿ�ָ��:��������)

public:
	HRESULT							DIRECTSOUND_CALLMETHOD		Create(HWND hWnd);																// DirectSound Initialize(SoundCoopFlags:Normal)
	HRESULT							DIRECTSOUND_CALLMETHOD		Create(HWND hWnd, DWORD dwSoundCoopFlags);										// DirectSound Initialize(Overload + 1)
	HRESULT							DIRECTSOUND_CALLMETHOD		Create(HWND hWnd, E_DX_SOUND_COOPFLAGS_TYPE eDirectSoundCoopFlags);				// DirectSound Initialize(Overload + 2)
	HRESULT							DIRECTSOUND_CALLMETHOD		Create3D(HWND hWnd);															// DirectSound3D Initialize(SoundCoopFlags:Priority)

	HRESULT							DIRECTSOUND_CALLMETHOD		LoadWave(LPWSTR lpszFileName);													// DirectSound Load Wave(����Wav)
	HRESULT							DIRECTSOUND_CALLMETHOD		LoadWave3D(LPWSTR lpszFileName);												// DirectSound Load 3D Wave(����Wav:3D)

	void							DIRECTSOUND_CALLMETHOD		Play();																			// DirectSound Play Wave(Once)(���β���)
	void							DIRECTSOUND_CALLMETHOD		Play(E_DX_SOUND_PLAYSTATE_TYPE eDSPlayState_X);									// DirectSound Play Wave(���β���/ѭ������)(Overload + 1)
	void							DIRECTSOUND_CALLMETHOD		PlayOnce();																		// DirectSound Play Wave(Once)(���β���)
	void							DIRECTSOUND_CALLMETHOD		PlayLoop();																		// DirectSound Play Wave(Loop)(ѭ������)

	void							DIRECTSOUND_CALLMETHOD		Stop();																			// DirectSound Stop Play(ֹͣ����)

	void							DIRECTSOUND_CALLMETHOD		SetVolume(LONG lVolume);														// DirectSound SetVolume(��������)
	void							DIRECTSOUND_CALLMETHOD		SetFrequency(DWORD dwFrequency);												// DirectSound SetFrequency(����Ƶ��)
	void							DIRECTSOUND_CALLMETHOD		SoundSetPan(LONG lPan);															// DirectSound SetPan(No 3D Voice)(��������ƽ��:��֧��3D)
	void							DIRECTSOUND_CALLMETHOD		SetCurrentPosition(DWORD dwNewPositon);											// DirectSound SetCurrentPosition(���ò��Ž���)

};

#endif