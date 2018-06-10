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
	DirectShow();	//DirectShow Constructor Function(DirectShow构造函数)
	~DirectShow();	//DirectShow Destructor Function(DirectShow析构函数)

	//DirectShow访问
	long DIRECTSHOW_CALLMODE DirectShowGetVideoWidth(void) const;	//DirectShow Get Video Width(获取视频宽度)
	long DIRECTSHOW_CALLMODE DirectShowGetVideoHeight(void) const;	//DirectShow Get Video Height(获取视频高度)
	float DIRECTSHOW_CALLMODE DirectShowGetVideoFramePerSecond(void) const;	//DirectShow Get Video fps(获取视频场频)

	//DirectShow初始化
	HRESULT DIRECTSHOW_CALLMODE DirectShowInit(void);	//DirectShow Initialize(DirectShow初始化)

	//DirectShow加载文件(路径)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadFile(LPWSTR lpszFileName);	//DirectShow Load Audio/Video File(DirectShow加载文件)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadMP3(LPWSTR lpszFileName);	//DirectShow Load MP3 File(DirectShow加载MP3文件)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadAudio(LPWSTR lpszFileName);	//DirectShow Load Audio File(DirectShow加载音频文件)
	HRESULT DIRECTSHOW_CALLMODE DirectShowLoadVideo(LPWSTR lpszFileName);	//DirectShow Load Video File(DirectShow加载视频文件)

	//DirectShow播放MP3文件格式
	void DIRECTSHOW_CALLMODE DirectShowMP3Play(void);	//DirectShow MP3 Play(DirectShow播放)
	void DIRECTSHOW_CALLMODE DirectShowMP3Pause(void);	//DirectShow MP3 Pause(DirectShow暂停)
	void DIRECTSHOW_CALLMODE DirectShowMP3Stop(void);	//DirectShow MP3 Stop(DirectShow停止)
	void DIRECTSHOW_CALLMODE DirectShowMP3GetDuration(REFTIME* pRefDuration) const;	//DirectShow MP3 GetDuration(DirectShow获取时间总长度)
	void DIRECTSHOW_CALLMODE DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow MP3 GetCurrentPosition(DirectShow获取当前进度)
	void DIRECTSHOW_CALLMODE DirectShowMP3SetCurrentPosition(REFTIME RefPosition);	//DirectShow MP3 SetCurrentPosition(DirectShow设置当前进度)

	//DirectShow播放音频文件格式
	void DIRECTSHOW_CALLMODE DirectShowAudioPlay(void);	//DirectShow Audio Play(DirectShow播放)
	void DIRECTSHOW_CALLMODE DirectShowAudioPause(void);	//DirectShow Audio Pause(DirectShow暂停)
	void DIRECTSHOW_CALLMODE DirectShowAudioStop(void);	//DirectShow Audio Stop(DirectShow停止)
	void DIRECTSHOW_CALLMODE DirectShowAudioGetDuration(REFTIME* pRefDuration) const;//DirectShow Audio GetDuration(DirectShow获取时间总长度)
	void DIRECTSHOW_CALLMODE DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Audio GetCurrentPosition(DirectShow获取当前进度)
	void DIRECTSHOW_CALLMODE DirectShowAudioSetCurrentPosition(REFTIME RefPosition);	//DirectShow Audio SetCurrentPosition(DirectShow设置当前进度)

	//DirectShow播放视频文件格式
	HRESULT DIRECTSHOW_CALLMODE DirectShowGetVideoInfo(void);	//DirectShow Get Video Information(DirectShow获取视频格式)
	HRESULT DIRECTSHOW_CALLMODE DirectShowSetVideoPlayInWindow(HWND hWnd);	//DirectShow Set Video Play In Window(DirectShow设置视频在指定窗口内播放)(~窗口)
	HRESULT DIRECTSHOW_CALLMODE DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect);	//DirectShow Set Video Play In Window(DirectShow设置视频在指定窗口内播放)(~指定矩形区域)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPlayWait(void);	//DirectShow Video Play Wait(DirectShow播放)(等待)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPlay(void);	//DirectShow Video Play(DirectShow播放)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoPause(void);	//DirectShow Video Pause(DirectShow暂停)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoStop(void);	//DirectShow Video Stop(DirectShow停止)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoGetDuration(REFTIME* pRefDuration) const;	//DirectShow Video GetDuration(DirectShow获取时间总长度)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Video GetCurrentPosition(DirectShow获取当前进度)
	HRESULT DIRECTSHOW_CALLMODE DirectShowVideoSetCurrentPosition(REFTIME RefPosition);	//DirectShow Video SetCurrentPosition(DirectShow设置当前进度)
};

#endif