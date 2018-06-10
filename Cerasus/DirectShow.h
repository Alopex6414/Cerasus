/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectShow.h
* @brief	This Program is DirectShow DLL Project.
* @author	Alopex/Helium
* @version	v1.25a
* @date		2017-11-1	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-2	v1.11a	alopex	Make Demo And Add Video Play In Window Mode.
* @date		2018-1-2	v1.21a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-3	v1.22a	alopex	Add Thread Safe Variable Makesure Thread Safe(DirectSafe).
* @date		2018-1-4	v1.23a	alopex	Cancel Thread Safe Variable(DirectSafe).
* @date		2018-1-10	v1.24a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.25a	alopex	Add Macro Call Mode.
*/
#pragma once

#ifndef __DIRECTSHOW_H_
#define __DIRECTSHOW_H_

//Include DirectShow Header File
#include <dshow.h>

//Include Static Library File
#pragma comment(lib,"Strmiids.lib") 

//Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTSHOW_API	__declspec(dllexport)
#else
#define DIRECTSHOW_API	__declspec(dllimport)
#endif

#define DIRECTSHOW_CALLMODE	__stdcall

//Class Definition

//Class
class DIRECTSHOW_API DirectShow
{
private:
	IGraphBuilder* m_pDirectShowGraphBuilder;	//IGraphBuilder Interface Pointer
	IMediaControl* m_pDirectShowMediaControl;	//IMediaControl Interface Pointer
	IMediaPosition* m_pDirectShowMediaPosition;	//IMediaPosition Interface Pointer
	IMediaEvent* m_pDirectShowMediaEvent;		//IMediaEvent Interface Pointer

	IBasicAudio* m_pDirectShowBasicAudio;		//IBasicAudio Interface Pointer
	IBasicVideo* m_pDirectShowBasicVideo;		//IBasicVideo Interface Pointer
	IVideoWindow* m_pDirectShowVideoWindow;		//IVideoWindow Interface Pointer

	long m_lVideoWidth;							//Video Origin Width
	long m_lVideoHeight;						//Video Origin Height
	float m_fVideofps;							//Video Origin Frame Per Second(fps)

	CRITICAL_SECTION m_cs;						//Thread Safe(CriticalSection)
	bool m_bThreadSafe;							//Thread Safe Status

public:
	DirectShow();	//DirectShow Constructor Function(DirectShow���캯��)
	~DirectShow();	//DirectShow Destructor Function(DirectShow��������)

	//DirectShow����
	long DIRECTSHOW_CALLMODE DirectShowGetVideoWidth(void) const;	//DirectShow Get Video Width(��ȡ��Ƶ���)
	long DIRECTSHOW_CALLMODE DirectShowGetVideoHeight(void) const;	//DirectShow Get Video Height(��ȡ��Ƶ�߶�)
	float DIRECTSHOW_CALLMODE DirectShowGetVideoFramePerSecond(void) const;	//DirectShow Get Video fps(��ȡ��Ƶ��Ƶ)

	//DirectShow��ʼ��
	HRESULT DIRECTSHOW_CALLMODE DirectShowInit(void);	//DirectShow Initialize(DirectShow��ʼ��)

	//DirectShow�����ļ�(·��)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadFile(LPWSTR lpszFileName);	//DirectShow Load Audio/Video File(DirectShow�����ļ�)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadMP3(LPWSTR lpszFileName);	//DirectShow Load MP3 File(DirectShow����MP3�ļ�)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadAudio(LPWSTR lpszFileName);	//DirectShow Load Audio File(DirectShow������Ƶ�ļ�)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadVideo(LPWSTR lpszFileName);	//DirectShow Load Video File(DirectShow������Ƶ�ļ�)

	//DirectShow����MP3�ļ���ʽ
	void DIRECTSHOW_CALLMODE DirectShowMP3Play(void);	//DirectShow MP3 Play(DirectShow����)
	void DIRECTSHOW_CALLMODE DirectShowMP3Pause(void);	//DirectShow MP3 Pause(DirectShow��ͣ)
	void DIRECTSHOW_CALLMODE DirectShowMP3Stop(void);	//DirectShow MP3 Stop(DirectShowֹͣ)
	void DIRECTSHOW_CALLMODE DirectShowMP3GetDuration(REFTIME* pRefDuration) const;	//DirectShow MP3 GetDuration(DirectShow��ȡʱ���ܳ���)
	void DIRECTSHOW_CALLMODE DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow MP3 GetCurrentPosition(DirectShow��ȡ��ǰ����)
	void DIRECTSHOW_CALLMODE DirectShowMP3SetCurrentPosition(REFTIME RefPosition);	//DirectShow MP3 SetCurrentPosition(DirectShow���õ�ǰ����)

	//DirectShow������Ƶ�ļ���ʽ
	void DIRECTSHOW_CALLMODE DirectShowAudioPlay(void);	//DirectShow Audio Play(DirectShow����)
	void DIRECTSHOW_CALLMODE DirectShowAudioPause(void);	//DirectShow Audio Pause(DirectShow��ͣ)
	void DIRECTSHOW_CALLMODE DirectShowAudioStop(void);	//DirectShow Audio Stop(DirectShowֹͣ)
	void DIRECTSHOW_CALLMODE DirectShowAudioGetDuration(REFTIME* pRefDuration) const;//DirectShow Audio GetDuration(DirectShow��ȡʱ���ܳ���)
	void DIRECTSHOW_CALLMODE DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Audio GetCurrentPosition(DirectShow��ȡ��ǰ����)
	void DIRECTSHOW_CALLMODE DirectShowAudioSetCurrentPosition(REFTIME RefPosition);	//DirectShow Audio SetCurrentPosition(DirectShow���õ�ǰ����)

	//DirectShow������Ƶ�ļ���ʽ
	HRESULT DIRECTSHOW_CALLMODE DirectShowGetVideoInfo(void);	//DirectShow Get Video Information(DirectShow��ȡ��Ƶ��ʽ)
	HRESULT DIRECTSHOW_CALLMODE DirectShowSetVideoPlayInWindow(HWND hWnd);	//DirectShow Set Video Play In Window(DirectShow������Ƶ��ָ�������ڲ���)(~����)
	HRESULT DIRECTSHOW_CALLMODE DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect);	//DirectShow Set Video Play In Window(DirectShow������Ƶ��ָ�������ڲ���)(~ָ����������)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPlayWait(void);	//DirectShow Video Play Wait(DirectShow����)(�ȴ�)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPlay(void);	//DirectShow Video Play(DirectShow����)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPause(void);	//DirectShow Video Pause(DirectShow��ͣ)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoStop(void);	//DirectShow Video Stop(DirectShowֹͣ)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoGetDuration(REFTIME* pRefDuration) const;	//DirectShow Video GetDuration(DirectShow��ȡʱ���ܳ���)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Video GetCurrentPosition(DirectShow��ȡ��ǰ����)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoSetCurrentPosition(REFTIME RefPosition);	//DirectShow Video SetCurrentPosition(DirectShow���õ�ǰ����)
};

#endif