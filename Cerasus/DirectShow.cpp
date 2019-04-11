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

// DirectShow Class(DirectShow ��Ƶ����Ƶ��)

//------------------------------------------------------------------
// @Function:	 DirectShow()
// @Purpose: DirectShow���캯��
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
// @Purpose: DirectShow��������
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
// @Purpose: DirectShow���캯��
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
// @Purpose: DirectShow���캯��
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
// @Purpose: DirectShow���캯��
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
// @Purpose: DirectShow��ȡͼ�ι�����
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
// @Purpose: DirectShow��ȡý�������
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
// @Purpose: DirectShow��ȡý��λ��
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
// @Purpose: DirectShow��ȡý���¼�
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
// @Purpose: DirectShow��ȡ��Ƶ����
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
// @Purpose: DirectShow��ȡ��Ƶ����
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
// @Purpose: DirectShow��ȡ��Ƶ����
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
// @Purpose: DirectShow ��ȡ��Ƶ���
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
// @Purpose: DirectShow ��ȡ��Ƶ�߶�
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
// @Purpose: DirectShow ��ȡ��Ƶ��Ƶ
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
// @Purpose: DirectShow ��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::Create()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IGraphBuilder�ӿڶ���
	VERIFY(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pDirectShowGraphBuilder));

	// ����IMediaControl��IMediaPosition�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pDirectShowMediaControl));				// IMediaControl�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaPosition, (void**)&m_pDirectShowMediaPosition));				// IMediaPosition�ӿڶ���
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IMediaEvent, (void **)&m_pDirectShowMediaEvent));					// IMediaEvent�ӿڶ���

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadFile(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ��Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadFile(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ������Ƶ��Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow ����MP3��Դ�ļ�(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3��Դ�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadMP3(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����MP3��Դ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadAudio(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadAudio(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ������Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 LoadVideo(LPWSTR lpszFileName)
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::LoadVideo(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ������Ƶ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowLoadMP3(LPWSTR lpszFileName)
// @Purpose: DirectShow ����MP3��Դ�ļ�(.mp3)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(MP3��Դ�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowLoadMP3(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//����MP3��Դ�ļ�����
	VERIFY(m_pDirectShowGraphBuilder->RenderFile(lpszFileName, NULL));

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowAudioPlay(void)
// @Purpose: DirectShow ������Դ�ļ�
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
// @Purpose: DirectShow ��ͣ������Դ�ļ�
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
// @Purpose: DirectShow ֹͣ������Դ�ļ�
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
// @Purpose: DirectShow ��ȡ��Դ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioGetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡ��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioGetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ������Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowAudioSetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowMP3Play(void)
// @Purpose: DirectShow ����MP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ��ͣMP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ֹͣMP3��Դ�ļ�(.mp3)
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
// @Purpose: DirectShow ��ȡMP3��Դ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3GetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_Duration(pRefDuration);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡMP3��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3GetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition);
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ����MP3��Դ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: None
//---------------------------------------------------------------------------
void DIRECTSHOW_CALLMETHOD DirectShow::DirectShowMP3SetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition);
}

//------------------------------------------------------------------
// @Function:	 DirectShowGetVideoInfo(void)
// @Purpose: DirectShow ��ȡ��Ƶ��ʽ��Ϣ
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowGetVideoInfo(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd)
// @Purpose: DirectShow ������Ƶ��ָ�������ڲ���
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT WindowRect;
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	//��ƵAudio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//����IBasicAudio�ӿ�

	//����Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//����IVideoWindow�ӿ�
	GetClientRect(hWnd, &WindowRect);	//��ȡ��ǰ��������
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//������Ƶ���ھ��
	m_pDirectShowVideoWindow->put_Left(0);	//��Ƶԭ��X����
	m_pDirectShowVideoWindow->put_Top(0);	//��Ƶԭ��Y����
	m_pDirectShowVideoWindow->put_Width(WindowRect.right - WindowRect.left);	//��Ƶ���
	m_pDirectShowVideoWindow->put_Height(WindowRect.bottom - WindowRect.top);	//��Ƶ�߶�
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//����ģʽ
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//���ý��ܴ�����Ϣ���  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
// @Purpose: DirectShow ������Ƶ��ָ�������ڲ���
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: RECT sRect(��Ƶ��������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowSetVideoPlayInWindow(HWND hWnd, RECT sRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	long VideoWidth;
	long VideoHeight;
	REFTIME AvgTimePerFrame;
	float VideoFramePerSecond;

	//��ƵVideo
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicVideo, (void **)&m_pDirectShowBasicVideo));//����IBasicVideo�ӿ�
	VERIFY(m_pDirectShowBasicVideo->get_VideoWidth(&VideoWidth));	//��ȡ��Ƶ���
	VERIFY(m_pDirectShowBasicVideo->get_VideoHeight(&VideoHeight));	//��ȡ��Ƶ�߶�
	VERIFY(m_pDirectShowBasicVideo->get_AvgTimePerFrame(&AvgTimePerFrame));	//��ȡ��Ƶ֡��
	VideoFramePerSecond = (float)(1 / AvgTimePerFrame);	//������Ƶ��Ƶ
	m_lVideoWidth = VideoWidth;	//��Ƶ���
	m_lVideoHeight = VideoHeight;	//��Ƶ�߶�
	m_fVideofps = VideoFramePerSecond;	//��Ƶ��Ƶ

	//��ƵAudio
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pDirectShowBasicAudio));//����IBasicAudio�ӿ�

	//����Window
	VERIFY(m_pDirectShowGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&m_pDirectShowVideoWindow));//����IVideoWindow�ӿ�
	m_pDirectShowVideoWindow->put_Visible(OAFALSE);
	m_pDirectShowVideoWindow->put_Owner((OAHWND)hWnd);	//������Ƶ���ھ��
	m_pDirectShowVideoWindow->put_Left(sRect.left);	//��Ƶԭ��X����
	m_pDirectShowVideoWindow->put_Top(sRect.top);	//��Ƶԭ��Y����
	m_pDirectShowVideoWindow->put_Width(sRect.right - sRect.left);	//��Ƶ���
	m_pDirectShowVideoWindow->put_Height(sRect.bottom - sRect.top);	//��Ƶ�߶�
	m_pDirectShowVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);	//����ģʽ
	m_pDirectShowVideoWindow->put_MessageDrain((OAHWND)hWnd);//���ý��ܴ�����Ϣ���  
	m_pDirectShowVideoWindow->put_Visible(OATRUE);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPlayWait(void)
// @Purpose: DirectShow ������Ƶ�ļ�(�ȴ�)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
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
// @Purpose: DirectShow ������Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoPlay(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Run());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoPause(void)
// @Purpose: DirectShow ��ͣ��Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoPause(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Pause());

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectShowVideoStop(void)
// @Purpose: DirectShow ֹͣ��Ƶ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoStop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaControl->Stop());

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetDuration(REFTIME* pRefDuration) const
// @Purpose: DirectShow ��ȡ��Ƶ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefDuration(�ļ��ܳ���)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoGetDuration(REFTIME* pRefDuration) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->get_Duration(pRefDuration));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
// @Purpose: DirectShow ��ȡ��Ƶ�ļ��ܳ���
// @Since: v1.00a
// @Para: REFTIME* pRefPosition(��ǰ����λ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoGetCurrentPosition(REFTIME* pRefPosition) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->get_CurrentPosition(pRefPosition));

	return S_OK;//OK
}

//---------------------------------------------------------------------------
// @Function:	 DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
// @Purpose: DirectShow ������Ƶ�ļ���ǰ����λ��
// @Since: v1.00a
// @Para: REFTIME RefPosition(����λ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTSHOW_CALLMETHOD DirectShow::DirectShowVideoSetCurrentPosition(REFTIME RefPosition)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(m_pDirectShowMediaPosition->put_CurrentPosition(RefPosition));

	return S_OK;//OK
}