/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectShow.cpp
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
#include "DirectCommon.h"
#include "DirectShow.h"
#include "DirectThreadSafe.h"

// DirectShow Class(DirectShow 视频、音频类)

//------------------------------------------------------------------
// @Function:	 DirectShow()
// @Purpose: DirectShow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::DirectShow() :
	m_pDirectShowGraphBuilder(NULL),
	m_pDirectShowMediaControl(NULL),
	m_pDirectShowMediaPosition(NULL),
	m_pDirectShowMediaEvent(NULL),
	m_pDirectShowBasicAudio(NULL),
	m_pDirectShowBasicVideo(NULL),
	m_pDirectShowVideoWindow(NULL),
	m_lVideoWidth(0),
	m_lVideoHeight(0),
	m_fVideofps(0.0f)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	CoInitialize(NULL);										// Initialize COM
}

//------------------------------------------------------------------
// @Function:	 ~DirectShow()
// @Purpose: DirectShow析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::~DirectShow()
{
	SAFE_RELEASE(m_pDirectShowVideoWindow);
	SAFE_RELEASE(m_pDirectShowBasicVideo);
	SAFE_RELEASE(m_pDirectShowBasicAudio);
	SAFE_RELEASE(m_pDirectShowMediaEvent);
	SAFE_RELEASE(m_pDirectShowMediaPosition);
	SAFE_RELEASE(m_pDirectShowMediaControl);
	SAFE_RELEASE(m_pDirectShowGraphBuilder);
	CoUninitialize();										// Release COM

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectShow(bool bSafe)
// @Purpose: DirectShow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::DirectShow(bool bSafe) :
	m_pDirectShowGraphBuilder(NULL),
	m_pDirectShowMediaControl(NULL),
	m_pDirectShowMediaPosition(NULL),
	m_pDirectShowMediaEvent(NULL),
	m_pDirectShowBasicAudio(NULL),
	m_pDirectShowBasicVideo(NULL),
	m_pDirectShowVideoWindow(NULL),
	m_lVideoWidth(0),
	m_lVideoHeight(0),
	m_fVideofps(0.0f)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	CoInitialize(NULL);										// Initialize COM
}

//------------------------------------------------------------------
// @Function:	 DirectShow(const DirectShow & Object)
// @Purpose: DirectShow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectShow::DirectShow(const DirectShow & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	CoInitialize(NULL);										// Initialize COM

	m_pDirectShowGraphBuilder = Object.m_pDirectShowGraphBuilder;
	m_pDirectShowMediaControl = Object.m_pDirectShowMediaControl;
	m_pDirectShowMediaPosition = Object.m_pDirectShowMediaPosition;
	m_pDirectShowMediaEvent = Object.m_pDirectShowMediaEvent;
	m_pDirectShowBasicAudio = Object.m_pDirectShowBasicAudio;
	m_pDirectShowBasicVideo = Object.m_pDirectShowBasicVideo;
	m_pDirectShowVideoWindow = Object.m_pDirectShowVideoWindow;
	m_lVideoWidth = Object.m_lVideoWidth;
	m_lVideoHeight = Object.m_lVideoHeight;
	m_fVideofps = Object.m_fVideofps;
}

//------------------------------------------------------------------
// @Function:	 operator=(const DirectShow & Object)
// @Purpose: DirectShow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectShow & DirectShow::operator=(const DirectShow & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		CoInitialize(NULL);										// Initialize COM

		m_pDirectShowGraphBuilder = Object.m_pDirectShowGraphBuilder;
		m_pDirectShowMediaControl = Object.m_pDirectShowMediaControl;
		m_pDirectShowMediaPosition = Object.m_pDirectShowMediaPosition;
		m_pDirectShowMediaEvent = Object.m_pDirectShowMediaEvent;
		m_pDirectShowBasicAudio = Object.m_pDirectShowBasicAudio;
		m_pDirectShowBasicVideo = Object.m_pDirectShowBasicVideo;
		m_pDirectShowVideoWindow = Object.m_pDirectShowVideoWindow;
		m_lVideoWidth = Object.m_lVideoWidth;
		m_lVideoHeight = Object.m_lVideoHeight;
		m_fVideofps = Object.m_fVideofps;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetGraphBuilder()
// @Purpose: DirectShow获取图形构造器
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IGraphBuilder *DIRECTSHOW_CALLMETHOD DirectShow::GetGraphBuilder() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowGraphBuilder;
}

//------------------------------------------------------------------
// @Function:	 GetMediaControl()
// @Purpose: DirectShow获取媒体控制器
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IMediaControl *DIRECTSHOW_CALLMETHOD DirectShow::GetMediaControl() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowMediaControl;
}

//------------------------------------------------------------------
// @Function:	 GetMediaPosition()
// @Purpose: DirectShow获取媒体位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IMediaPosition *DIRECTSHOW_CALLMETHOD DirectShow::GetMediaPosition() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowMediaPosition;
}

//------------------------------------------------------------------
// @Function:	 GetMediaEvent()
// @Purpose: DirectShow获取媒体事件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IMediaEvent *DIRECTSHOW_CALLMETHOD DirectShow::GetMediaEvent() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowMediaEvent;
}

//------------------------------------------------------------------
// @Function:	 GetBasicAudio()
// @Purpose: DirectShow获取音频基础
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IBasicAudio *DIRECTSHOW_CALLMETHOD DirectShow::GetBasicAudio() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowBasicAudio;
}

//------------------------------------------------------------------
// @Function:	 GetBasicVideo()
// @Purpose: DirectShow获取视频基础
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IBasicVideo *DIRECTSHOW_CALLMETHOD DirectShow::GetBasicVideo() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowBasicVideo;
}

//------------------------------------------------------------------
// @Function:	 GetVideoWindow()
// @Purpose: DirectShow获取视频窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IVideoWindow *DIRECTSHOW_CALLMETHOD DirectShow::GetVideoWindow() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectShowVideoWindow;
}

//------------------------------------------------------------------
// @Function:	 GetVideoWidth() const
// @Purpose: DirectShow 获取视频宽度
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
long DIRECTSHOW_CALLMETHOD DirectShow::GetVideoWidth() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_lVideoWidth;
}

//------------------------------------------------------------------
// @Function:	 GetVideoHeight() const
// @Purpose: DirectShow 获取视频高度
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
long DIRECTSHOW_CALLMETHOD DirectShow::GetVideoHeight() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_lVideoHeight;
}

//------------------------------------------------------------------
// @Function:	 GetVideofps() const
// @Purpose: DirectShow 获取视频场频
// @Since: v1.00a
// @Para: None
// @Return: long
//------------------------------------------------------------------
float DIRECTSHOW_CALLMETHOD DirectShow::GetVideofps() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_fVideofps;
}

//------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: DirectShow 初始化
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::Create()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IGraphBuilder接口对象
	VERIFY(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pDirectShowGraphBuilder));

	// 创建IMediaControl和IMediaPosition接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pDirectShowMediaControl));				// IMediaControl接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pDirectShowMediaPosition));				// IMediaPosition接口对象
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&m_pDirectShowMediaEvent));					// IMediaEvent接口对象

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadFile(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载音频视频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadFile(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 加载音频视频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3音源文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadMP3(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 加载MP3音源文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadAudio(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载音频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadAudio(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 加载音频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadVideo(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载视频文件
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadVideo(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 加载视频文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow 加载MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3音源文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowLoadMP3(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//加载MP3音源文件数据
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPlay(void)
// @Purpose: DirectShow 播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioPlay(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Run();
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPause(void)
// @Purpose: DirectShow 暂停播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioPause(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Pause();
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioStop(void)
// @Purpose: DirectShow 停止播放音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioStop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Stop();
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取音源文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioGetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Play(void)
// @Purpose: DirectShow 播放MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3Play(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Run();
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Pause(void)
// @Purpose: DirectShow 暂停MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3Pause(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Pause();
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Stop(void)
// @Purpose: DirectShow 停止MP3音源文件(.mp3)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3Stop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaControl->Stop();
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取MP3音源文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3GetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取MP3音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置MP3音源文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoInfo(void)
// @Purpose: DirectShow 获取视频格式信息
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowGetVideoInfo(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd)
// @Purpose: DirectShow 设置视频在指定窗口内播放
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT WindowRect;
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	//音频Audio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//创建IBasicAudio接口

	//窗口Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//创建IVideoWindow接口
	GetClientRect(hWnd, &WindowRect);	//读取当前窗口区域
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//设置视频窗口句柄
	m_pDirectShowVideoWindow->put_Left(0);	//视频原点X坐标
	m_pDirectShowVideoWindow->put_Top(0);	//视频原点Y坐标
	m_pDirectShowVideoWindow->put_Width(WindowRect.right - WindowRect.left);	//视频宽度
	m_pDirectShowVideoWindow->put_Height(WindowRect.bottom - WindowRect.top);	//视频高度
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//窗口模式
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//设置接受窗口信息句柄  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
// @Purpose: DirectShow 设置视频在指定窗口内播放
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: RECT sRect(视频播放区域)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//视频Video
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//创建IBasicVideo接口
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//读取视频宽度
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//读取视频高度
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//读取视频帧率
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//计算视频场频
	m_lVideoWidth = VideoWidth;	//视频宽度
	m_lVideoHeight = VideoHeight;	//视频高度
	m_fVideofps = VideoFramePerSecond;	//视频场频

	//音频Audio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//创建IBasicAudio接口

	//窗口Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//创建IVideoWindow接口
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//设置视频窗口句柄
	m_pDirectShowVideoWindow->put_Left(sRect.left);	//视频原点X坐标
	m_pDirectShowVideoWindow->put_Top(sRect.top);	//视频原点Y坐标
	m_pDirectShowVideoWindow->put_Width(sRect.right - sRect.left);	//视频宽度
	m_pDirectShowVideoWindow->put_Height(sRect.bottom - sRect.top);	//视频高度
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//窗口模式
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//设置接受窗口信息句柄  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlayWait(void)
// @Purpose: DirectShow 播放视频文件(等待)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoPlayWait(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	long evCode = 0;

	VERIFY(m_pDirectShowMediaControl->Run());
	while (evCode != EC_COMPLETE)
	{
		m_pDirectShowMediaEvent->WaitForCompletion(1000, &evCode);
	}

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlay(void)
// @Purpose: DirectShow 播放视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoPlay(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Run());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPause(void)
// @Purpose: DirectShow 暂停视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoPause(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Pause());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoStop(void)
// @Purpose: DirectShow 停止视频文件
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoStop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Stop());

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow 读取视频文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(文件总长度)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoGetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->get_Duration(pRefDuration));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow 读取视频文件总长度
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(当前播放位置)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow 设置视频文件当前播放位置
// @Since: v1.00a
// @Para: REFTIME RefPosition(播放位置)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition));

	return S_OK;//OK
}