/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectShow.h
* @brief	This Program is DirectShow DLL Project.
* @author	Alopex/Alice
* @version	v1.28a
* @date		2017-11-01	v1.00a	alopex	Create This Project.
* @date		2017-12-08	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-02	v1.11a	alopex	Make Demo And Add Video Play In Window Mode.
* @date		2018-01-02	v1.21a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-03	v1.22a	alopex	Add Thread Safe Variable Makesure Thread Safe(DirectSafe).
* @date		2018-01-04	v1.23a	alopex	Cancel Thread Safe Variable(DirectSafe).
* @date		2018-01-10	v1.24a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.25a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.26a	alopex	Add Version Infomation.
* @date		2018-11-23	v1.27a	alopex	Alter Call Method.
* @date		2019-04-10	v1.28a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTSHOW_H_
#define __DIRECTSHOW_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Include DirectShow Header File
#include <dshow.h>

// Include Static Library File
#pragma comment(lib,"Strmiids.lib") 

// Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTSHOW_API	__declspec(dllexport)
#else
#define DIRECTSHOW_API	__declspec(dllimport)
#endif

#define DIRECTSHOW_CALLMETHOD	__stdcall

// Class Definition
class DIRECTSHOW_API DirectShow
{
private:
	IGraphBuilder* m_pDirectShowGraphBuilder;				// DirectShow IGraphBuilder Interface Pointer(~DirectShow IGraphBuilder�ӿ�ָ��)
	IMediaControl* m_pDirectShowMediaControl;				// DirectShow IMediaControl Interface Pointer(~DirectShow IMediaControl�ӿ�ָ��)
	IMediaPosition* m_pDirectShowMediaPosition;				// DirectShow IMediaPosition Interface Pointer(~DirectShow IMediaPosition�ӿ�ָ��)
	IMediaEvent* m_pDirectShowMediaEvent;					// DirectShow IMediaEvent Interface Pointer(~DirectShow IMediaEvent�ӿ�ָ��)

	IBasicAudio* m_pDirectShowBasicAudio;					// DirectShow IBasicAudio Interface Pointer(~DirectShow IBasicAudio�ӿ�ָ��)
	IBasicVideo* m_pDirectShowBasicVideo;					// DirectShow IBasicVideo Interface Pointer(~DirectShow IBasicVideo�ӿ�ָ��)
	IVideoWindow* m_pDirectShowVideoWindow;					// DirectShow IVideoWindow Interface Pointer(~DirectShow IVideoWindow�ӿ�ָ��)

private:
	long m_lVideoWidth;										// DirectShow Video Origin Width(~DirectShow ��Ƶ���)
	long m_lVideoHeight;									// DirectShow Video Origin Height(~DirectShow ��Ƶ���)
	float m_fVideofps;										// DirectShow Video Origin Frame Per Second(fps)(~DirectShow ��Ƶfps)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectShow();											// DirectShow Construction Function(DirectShow���캯��)
	~DirectShow();											// DirectShow Destruction Function(DirectShow��������)

	DirectShow(bool bSafe);									// DirectShow Construction Function(DirectShow���캯��)(Overload + 1)
	DirectShow(const DirectShow&);							// DirectShow Construction Function(DirectShow�������캯��)

public:
	const DirectShow& operator=(const DirectShow&);			// DirectShow Overload= Function(DirectShow��������غ���)

public:
	IGraphBuilder*					DIRECTSHOW_CALLMETHOD		GetGraphBuilder() const;					// DirectShow Get Graph Builder(~DirectShow ��ȡͼ�ι�����)
	IMediaControl*					DIRECTSHOW_CALLMETHOD		GetMediaControl() const;					// DirectShow Get Media Control(~DirectShow ý�������)
	IMediaPosition*					DIRECTSHOW_CALLMETHOD		GetMediaPosition() const;					// DirectShow Get Media Position(~DirectShow ý��λ����)
	IMediaEvent*					DIRECTSHOW_CALLMETHOD		GetMediaEvent() const;						// DirectShow Get Media Event(~DirectShow ý���¼���)

	IBasicAudio*					DIRECTSHOW_CALLMETHOD		GetBasicAudio() const;						// DirectShow Get Basic Audio(~DirectShow ��ȡ������Ƶ)
	IBasicVideo*					DIRECTSHOW_CALLMETHOD		GetBasicVideo() const;						// DirectShow Get Basic Video(~DirectShow ��ȡ������Ƶ)
	IVideoWindow*					DIRECTSHOW_CALLMETHOD		GetVideoWindow() const;						// DirectShow Get Video Window(~DirectShow ��ȡ��Ƶ����)

	long							DIRECTSHOW_CALLMETHOD		GetVideoWidth() const;						// DirectShow Get Video Width(~DirectShow ��ȡ������Ƶ)
	long							DIRECTSHOW_CALLMETHOD		GetVideoHeight() const;						// DirectShow Get Video Height(~DirectShow ��ȡ������Ƶ)
	float							DIRECTSHOW_CALLMETHOD		GetVideofps() const;						// DirectShow Get Video fps(~DirectShow ��ȡ������Ƶ)

public:
	HRESULT							DIRECTSHOW_CALLMETHOD		Create();									// DirectShow Initialize(~DirectShow ��ʼ��)

	HRESULT							DIRECTSHOW_CALLMETHOD		LoadFile(LPWSTR lpszFileName);				// DirectShow Load Audio/Video File(~DirectShow �����ļ�)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadMP3(LPWSTR lpszFileName);				// DirectShow Load MP3 File(~DirectShow ����MP3�ļ�)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadAudio(LPWSTR lpszFileName);				// DirectShow Load Audio File(~DirectShow ������Ƶ�ļ�)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadVideo(LPWSTR lpszFileName);				// DirectShow Load Audio File(~DirectShow ������Ƶ�ļ�)

	void							DIRECTSHOW_CALLMETHOD		MP3Play();																// DirectShow MP3 Play(~DirectShow ����)
	void							DIRECTSHOW_CALLMETHOD		MP3Pause();																// DirectShow MP3 Pause(~DirectShow ��ͣ)
	void							DIRECTSHOW_CALLMETHOD		MP3Stop();																// DirectShow MP3 Stop(~DirectShow ֹͣ)
	void							DIRECTSHOW_CALLMETHOD		MP3GetDuration(REFTIME* pRefDuration) const;							// DirectShow MP3 GetDuration(~DirectShow ��ȡʱ���ܳ���)
	void							DIRECTSHOW_CALLMETHOD		MP3GetCurrentPosition(REFTIME* pRefPosition) const;						// DirectShow MP3 GetCurrentPosition(~DirectShow ��ȡ��ǰ����)
	void							DIRECTSHOW_CALLMETHOD		MP3SetCurrentPosition(REFTIME RefPosition);								// DirectShow MP3 SetCurrentPosition(~DirectShow ���õ�ǰ����)

	void							DIRECTSHOW_CALLMETHOD		AudioPlay();															// DirectShow Audio Play(~DirectShow ����)
	void							DIRECTSHOW_CALLMETHOD		AudioPause();															// DirectShow Audio Pause(~DirectShow ��ͣ)
	void							DIRECTSHOW_CALLMETHOD		AudioStop();															// DirectShow Audio Stop(~DirectShow ֹͣ)
	void							DIRECTSHOW_CALLMETHOD		AudioGetDuration(REFTIME* pRefDuration) const;							// DirectShow Audio GetDuration(~DirectShow ��ȡʱ���ܳ���)
	void							DIRECTSHOW_CALLMETHOD		AudioGetCurrentPosition(REFTIME* pRefPosition) const;					// DirectShow Audio GetCurrentPosition(~DirectShow ��ȡ��ǰ����)
	void							DIRECTSHOW_CALLMETHOD		AudioSetCurrentPosition(REFTIME RefPosition);							// DirectShow Audio SetCurrentPosition(~DirectShow ���õ�ǰ����)

	HRESULT							DIRECTSHOW_CALLMETHOD		GetVideoInfo();															// DirectShow Get Video Information(~DirectShow ��ȡ��Ƶ��ʽ)
	HRESULT							DIRECTSHOW_CALLMETHOD		SetVideoPlayInWindow(HWND hWnd);										// DirectShow Set Video Play In Window(~DirectShow ������Ƶ��ָ�������ڲ���)
	HRESULT							DIRECTSHOW_CALLMETHOD		SetVideoPlayInWindow(HWND hWnd, RECT sRect);							// DirectShow Set Video Play In Window(~DirectShow ������Ƶ��ָ�������ڲ���)(~ָ����������)(Overload + 1)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPlayWait();														// DirectShow Video Play Wait(~DirectShow ����)(�ȴ�)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPlay();															// DirectShow Video Play(~DirectShow ����)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPause();															// DirectShow Video Pause(~DirectShow ��ͣ)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoStop();															// DirectShow Video Stop(~DirectShow ֹͣ)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoGetDuration(REFTIME* pRefDuration) const;							// DirectShow Video GetDuration(~DirectShow ��ȡʱ���ܳ���)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoGetCurrentPosition(REFTIME* pRefPosition) const;					// DirectShow Video GetCurrentPosition(~DirectShow ��ȡ��ǰ����)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoSetCurrentPosition(REFTIME RefPosition);							// DirectShow Video SetCurrentPosition(~DirectShow ���õ�ǰ����)

};

#endif