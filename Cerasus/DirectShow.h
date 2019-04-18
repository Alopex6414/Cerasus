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
	IGraphBuilder*					DIRECTSHOW_CALLMETHOD		GetGraphBuilder() const;					// DirectShow Get Graph Builder(~DirectShow 获取图形构造器)
	IMediaControl*					DIRECTSHOW_CALLMETHOD		GetMediaControl() const;					// DirectShow Get Media Control(~DirectShow 媒体控制器)
	IMediaPosition*					DIRECTSHOW_CALLMETHOD		GetMediaPosition() const;					// DirectShow Get Media Position(~DirectShow 媒体位置器)
	IMediaEvent*					DIRECTSHOW_CALLMETHOD		GetMediaEvent() const;						// DirectShow Get Media Event(~DirectShow 媒体事件器)

	IBasicAudio*					DIRECTSHOW_CALLMETHOD		GetBasicAudio() const;						// DirectShow Get Basic Audio(~DirectShow 获取基础音频)
	IBasicVideo*					DIRECTSHOW_CALLMETHOD		GetBasicVideo() const;						// DirectShow Get Basic Video(~DirectShow 获取基础视频)
	IVideoWindow*					DIRECTSHOW_CALLMETHOD		GetVideoWindow() const;						// DirectShow Get Video Window(~DirectShow 获取视频窗口)

	long							DIRECTSHOW_CALLMETHOD		GetVideoWidth() const;						// DirectShow Get Video Width(~DirectShow 获取基础音频)
	long							DIRECTSHOW_CALLMETHOD		GetVideoHeight() const;						// DirectShow Get Video Height(~DirectShow 获取基础音频)
	float							DIRECTSHOW_CALLMETHOD		GetVideofps() const;						// DirectShow Get Video fps(~DirectShow 获取基础音频)

public:
	HRESULT							DIRECTSHOW_CALLMETHOD		Create();									// DirectShow Initialize(~DirectShow 初始化)

	HRESULT							DIRECTSHOW_CALLMETHOD		LoadFile(LPWSTR lpszFileName);				// DirectShow Load Audio/Video File(~DirectShow 加载文件)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadMP3(LPWSTR lpszFileName);				// DirectShow Load MP3 File(~DirectShow 加载MP3文件)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadAudio(LPWSTR lpszFileName);				// DirectShow Load Audio File(~DirectShow 加载音频文件)
	HRESULT							DIRECTSHOW_CALLMETHOD		LoadVideo(LPWSTR lpszFileName);				// DirectShow Load Audio File(~DirectShow 加载视频文件)

	void							DIRECTSHOW_CALLMETHOD		MP3Play();																// DirectShow MP3 Play(~DirectShow 播放)
	void							DIRECTSHOW_CALLMETHOD		MP3Pause();																// DirectShow MP3 Pause(~DirectShow 暂停)
	void							DIRECTSHOW_CALLMETHOD		MP3Stop();																// DirectShow MP3 Stop(~DirectShow 停止)
	void							DIRECTSHOW_CALLMETHOD		MP3GetDuration(REFTIME* pRefDuration) const;							// DirectShow MP3 GetDuration(~DirectShow 获取时间总长度)
	void							DIRECTSHOW_CALLMETHOD		MP3GetCurrentPosition(REFTIME* pRefPosition) const;						// DirectShow MP3 GetCurrentPosition(~DirectShow 获取当前进度)
	void							DIRECTSHOW_CALLMETHOD		MP3SetCurrentPosition(REFTIME RefPosition);								// DirectShow MP3 SetCurrentPosition(~DirectShow 设置当前进度)

	void							DIRECTSHOW_CALLMETHOD		AudioPlay();															// DirectShow Audio Play(~DirectShow 播放)
	void							DIRECTSHOW_CALLMETHOD		AudioPause();															// DirectShow Audio Pause(~DirectShow 暂停)
	void							DIRECTSHOW_CALLMETHOD		AudioStop();															// DirectShow Audio Stop(~DirectShow 停止)
	void							DIRECTSHOW_CALLMETHOD		AudioGetDuration(REFTIME* pRefDuration) const;							// DirectShow Audio GetDuration(~DirectShow 获取时间总长度)
	void							DIRECTSHOW_CALLMETHOD		AudioGetCurrentPosition(REFTIME* pRefPosition) const;					// DirectShow Audio GetCurrentPosition(~DirectShow 获取当前进度)
	void							DIRECTSHOW_CALLMETHOD		AudioSetCurrentPosition(REFTIME RefPosition);							// DirectShow Audio SetCurrentPosition(~DirectShow 设置当前进度)

	HRESULT							DIRECTSHOW_CALLMETHOD		GetVideoInfo();															// DirectShow Get Video Information(~DirectShow 获取视频格式)
	HRESULT							DIRECTSHOW_CALLMETHOD		SetVideoPlayInWindow(HWND hWnd);										// DirectShow Set Video Play In Window(~DirectShow 设置视频在指定窗口内播放)
	HRESULT							DIRECTSHOW_CALLMETHOD		SetVideoPlayInWindow(HWND hWnd, RECT sRect);							// DirectShow Set Video Play In Window(~DirectShow 设置视频在指定窗口内播放)(~指定矩形区域)(Overload + 1)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPlayWait();														// DirectShow Video Play Wait(~DirectShow 播放)(等待)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPlay();															// DirectShow Video Play(~DirectShow 播放)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoPause();															// DirectShow Video Pause(~DirectShow 暂停)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoStop();															// DirectShow Video Stop(~DirectShow 停止)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoGetDuration(REFTIME* pRefDuration) const;							// DirectShow Video GetDuration(~DirectShow 获取时间总长度)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoGetCurrentPosition(REFTIME* pRefPosition) const;					// DirectShow Video GetCurrentPosition(~DirectShow 获取当前进度)
	HRESULT							DIRECTSHOW_CALLMETHOD		VideoSetCurrentPosition(REFTIME RefPosition);							// DirectShow Video SetCurrentPosition(~DirectShow 设置当前进度)

};

#endif