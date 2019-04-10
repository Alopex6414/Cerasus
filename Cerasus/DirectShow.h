/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
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
	IGraphBuilder* m_pDirectShowGraphBuilder;				// DirectShow IGraphBuilder Interface Pointer(~DirectShow IGraphBuilder接口指针)
	IMediaControl* m_pDirectShowMediaControl;				// DirectShow IMediaControl Interface Pointer(~DirectShow IMediaControl接口指针)
	IMediaPosition* m_pDirectShowMediaPosition;				// DirectShow IMediaPosition Interface Pointer(~DirectShow IMediaPosition接口指针)
	IMediaEvent* m_pDirectShowMediaEvent;					// DirectShow IMediaEvent Interface Pointer(~DirectShow IMediaEvent接口指针)

	IBasicAudio* m_pDirectShowBasicAudio;					// DirectShow IBasicAudio Interface Pointer(~DirectShow IBasicAudio接口指针)
	IBasicVideo* m_pDirectShowBasicVideo;					// DirectShow IBasicVideo Interface Pointer(~DirectShow IBasicVideo接口指针)
	IVideoWindow* m_pDirectShowVideoWindow;					// DirectShow IVideoWindow Interface Pointer(~DirectShow IVideoWindow接口指针)

private:
	long m_lVideoWidth;										// DirectShow Video Origin Width(~DirectShow 视频宽度)
	long m_lVideoHeight;									// DirectShow Video Origin Height(~DirectShow 视频宽度)
	float m_fVideofps;										// DirectShow Video Origin Frame Per Second(fps)(~DirectShow 视频fps)

protected:
	CRITICAL_SECTION m_cs;									// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;										// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	DirectShow();											// DirectShow Construction Function(DirectShow构造函数)
	~DirectShow();											// DirectShow Destruction Function(DirectShow析构函数)

	DirectShow(bool bSafe);									// DirectShow Construction Function(DirectShow构造函数)(Overload + 1)
	DirectShow(const DirectShow&);							// DirectShow Construction Function(DirectShow拷贝构造函数)

public:
	const DirectShow& operator=(const DirectShow&);			// DirectShow Overload= Function(DirectShow运算符重载函数)

public:
	IGraphBuilder*					DIRECTSHOW_CALLMETHOD		GetGraphBuilder() const;
	IMediaControl*					DIRECTSHOW_CALLMETHOD		GetMediaControl() const;
	IMediaPosition*					DIRECTSHOW_CALLMETHOD		GetMediaPosition() const;
	IMediaEvent*					DIRECTSHOW_CALLMETHOD		GetMediaEvent() const;

	IBasicAudio*					DIRECTSHOW_CALLMETHOD		GetBasicAudio() const;
	IBasicVideo*					DIRECTSHOW_CALLMETHOD		GetBasicVideo() const;
	IVideoWindow*					DIRECTSHOW_CALLMETHOD		GetVideoWindow() const;

	long							DIRECTSHOW_CALLMETHOD		GetVideoWidth() const;
	long							DIRECTSHOW_CALLMETHOD		GetVideoHeight() const;
	float							DIRECTSHOW_CALLMETHOD		GetVideofps() const;

	//DirectShow访问
	long DIRECTSHOW_CALLMETHOD DirectShowGetVideoWidth(void) const;				//DirectShow Get Video Width(获取视频宽度)
	long DIRECTSHOW_CALLMETHOD DirectShowGetVideoHeight(void) const;			//DirectShow Get Video Height(获取视频高度)
	float DIRECTSHOW_CALLMETHOD DirectShowGetVideoFramePerSecond(void) const;	//DirectShow Get Video fps(获取视频场频)

	//DirectShow初始化
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowInit(void);							//DirectShow Initialize(DirectShow初始化)

	//DirectShow加载文件(路径)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowLoadFile(LPWSTR lpszFileName);		//DirectShow Load Audio/Video File(DirectShow加载文件)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowLoadMP3(LPWSTR lpszFileName);		//DirectShow Load MP3 File(DirectShow加载MP3文件)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowLoadAudio(LPWSTR lpszFileName);		//DirectShow Load Audio File(DirectShow加载音频文件)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowLoadVideo(LPWSTR lpszFileName);		//DirectShow Load Video File(DirectShow加载视频文件)

	//DirectShow播放MP3文件格式
	void DIRECTSHOW_CALLMETHOD DirectShowMP3Play(void);							//DirectShow MP3 Play(DirectShow播放)
	void DIRECTSHOW_CALLMETHOD DirectShowMP3Pause(void);						//DirectShow MP3 Pause(DirectShow暂停)
	void DIRECTSHOW_CALLMETHOD DirectShowMP3Stop(void);							//DirectShow MP3 Stop(DirectShow停止)
	void DIRECTSHOW_CALLMETHOD DirectShowMP3GetDuration(REFTIME* pRefDuration) const;			//DirectShow MP3 GetDuration(DirectShow获取时间总长度)
	void DIRECTSHOW_CALLMETHOD DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow MP3 GetCurrentPosition(DirectShow获取当前进度)
	void DIRECTSHOW_CALLMETHOD DirectShowMP3SetCurrentPosition(REFTIME RefPosition);			//DirectShow MP3 SetCurrentPosition(DirectShow设置当前进度)

	//DirectShow播放音频文件格式
	void DIRECTSHOW_CALLMETHOD DirectShowAudioPlay(void);						//DirectShow Audio Play(DirectShow播放)
	void DIRECTSHOW_CALLMETHOD DirectShowAudioPause(void);						//DirectShow Audio Pause(DirectShow暂停)
	void DIRECTSHOW_CALLMETHOD DirectShowAudioStop(void);						//DirectShow Audio Stop(DirectShow停止)
	void DIRECTSHOW_CALLMETHOD DirectShowAudioGetDuration(REFTIME* pRefDuration) const;			//DirectShow Audio GetDuration(DirectShow获取时间总长度)
	void DIRECTSHOW_CALLMETHOD DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Audio GetCurrentPosition(DirectShow获取当前进度)
	void DIRECTSHOW_CALLMETHOD DirectShowAudioSetCurrentPosition(REFTIME RefPosition);			//DirectShow Audio SetCurrentPosition(DirectShow设置当前进度)

	//DirectShow播放视频文件格式
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowGetVideoInfo(void);									//DirectShow Get Video Information(DirectShow获取视频格式)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowSetVideoPlayInWindow(HWND hWnd);					//DirectShow Set Video Play In Window(DirectShow设置视频在指定窗口内播放)(~窗口)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect);		//DirectShow Set Video Play In Window(DirectShow设置视频在指定窗口内播放)(~指定矩形区域)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoPlayWait(void);								//DirectShow Video Play Wait(DirectShow播放)(等待)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoPlay(void);									//DirectShow Video Play(DirectShow播放)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoPause(void);									//DirectShow Video Pause(DirectShow暂停)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoStop(void);									//DirectShow Video Stop(DirectShow停止)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoGetDuration(REFTIME* pRefDuration) const;		//DirectShow Video GetDuration(DirectShow获取时间总长度)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const;	//DirectShow Video GetCurrentPosition(DirectShow获取当前进度)
	HRESULT DIRECTSHOW_CALLMETHOD DirectShowVideoSetCurrentPosition(REFTIME RefPosition);		//DirectShow Video SetCurrentPosition(DirectShow设置当前进度)
};

#endif