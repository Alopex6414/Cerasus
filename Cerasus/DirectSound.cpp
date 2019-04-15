/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectSound.cpp
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
#include "DirectCommon.h"
#include "DirectSound.h"
#include "DirectThreadSafe.h"

// DirectX Sound Class(DirectX 音乐、音效输出)

//------------------------------------------------------------------
// @Function:	 DirectSound()
// @Purpose: DirectSound构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::DirectSound() :
	m_pDirectSound(NULL),
	m_pDirectSoundBuffer(NULL),
	m_pDirectSoundPrimary(NULL),
	m_pDirectSound3DBuffer(NULL),
	m_pDirectSound3DListener(NULL)
{
	m_bThreadSafe = true;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
}

//------------------------------------------------------------------
// @Function:	 ~DirectSound()
// @Purpose: DirectSound析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::~DirectSound()
{
	SAFE_RELEASE(m_pDirectSound3DListener);
	SAFE_RELEASE(m_pDirectSound3DBuffer);
	SAFE_RELEASE(m_pDirectSoundPrimary);
	SAFE_RELEASE(m_pDirectSoundBuffer);
	SAFE_RELEASE(m_pDirectSound);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);				// Delete Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectSound(bool bSafe)
// @Purpose: DirectSound构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::DirectSound(bool bSafe) :
	m_pDirectSound(NULL),
	m_pDirectSoundBuffer(NULL),
	m_pDirectSoundPrimary(NULL),
	m_pDirectSound3DBuffer(NULL),
	m_pDirectSound3DListener(NULL)
{
	m_bThreadSafe = bSafe;											// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
}

//------------------------------------------------------------------
// @Function:	 DirectSound(const DirectSound& Object)
// @Purpose: DirectSound拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::DirectSound(const DirectSound& Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

	m_pDirectSound = Object.m_pDirectSound;
	m_pDirectSoundBuffer = Object.m_pDirectSoundBuffer;
	m_pDirectSoundPrimary = Object.m_pDirectSoundPrimary;
	m_pDirectSound3DBuffer = Object.m_pDirectSound3DBuffer;
	m_pDirectSound3DListener = Object.m_pDirectSound3DListener;

	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
	memcpy_s(&m_DSBufferDesc, sizeof(m_DSBufferDesc), &(Object.m_DSBufferDesc), sizeof(Object.m_DSBufferDesc));
	memcpy_s(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc), &(Object.m_DSPrimaryDesc), sizeof(Object.m_DSPrimaryDesc));
}

//------------------------------------------------------------------
// @Function:	 operator=(const DirectSound& Object)
// @Purpose: DirectSound运算符重载
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectSound& DirectSound::operator=(const DirectSound& Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;							// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);			// Initialize Critical Section

		m_pDirectSound = Object.m_pDirectSound;
		m_pDirectSoundBuffer = Object.m_pDirectSoundBuffer;
		m_pDirectSoundPrimary = Object.m_pDirectSoundPrimary;
		m_pDirectSound3DBuffer = Object.m_pDirectSound3DBuffer;
		m_pDirectSound3DListener = Object.m_pDirectSound3DListener;

		ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
		ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
		memcpy_s(&m_DSBufferDesc, sizeof(m_DSBufferDesc), &(Object.m_DSBufferDesc), sizeof(Object.m_DSBufferDesc));
		memcpy_s(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc), &(Object.m_DSPrimaryDesc), sizeof(Object.m_DSPrimaryDesc));
	}

	return *this;
}

//------------------------------------------------------------------------
// @Function:	GetSound() const
// @Purpose: DirectSound 获取IDirectSound8接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND8
//------------------------------------------------------------------------
LPDIRECTSOUND8 DIRECTSOUND_CALLMETHOD DirectSound::GetSound() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound;
}

//------------------------------------------------------------------------
// @Function:	GetSoundBuffer() const
// @Purpose: DirectSound 获取IDirectSoundBuffer接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMETHOD DirectSound::GetSoundBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSoundBuffer;
}

//------------------------------------------------------------------------
// @Function:	GetSoundPrimary() const
// @Purpose: DirectSound 获取IDirectSoundBuffer接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMETHOD DirectSound::GetSoundPrimary() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSoundPrimary;
}

//------------------------------------------------------------------------
// @Function:	GetSound3DBuffer() const
// @Purpose: DirectSound 获取IDirectSound3DBuffer接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUND3DBUFFER DIRECTSOUND_CALLMETHOD DirectSound::GetSound3DBuffer() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound3DBuffer;
}

//------------------------------------------------------------------------
// @Function:	GetSound3DListener() const
// @Purpose: DirectSound 获取IDirectSound3DBuffer接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DLISTENER
//------------------------------------------------------------------------
LPDIRECTSOUND3DLISTENER DIRECTSOUND_CALLMETHOD DirectSound::GetSound3DListener() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound3DListener;
}

//------------------------------------------------------------------------
// @Function:	Create(HWND hWnd)
// @Purpose: DirectSound 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::Create(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectSound8接口对象
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));					// 创建IDirectSound8接口对象
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL));			// 设置DirectSound协作级别(Normal模式)

	return S_OK;//OK 
}

//------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, DWORD dwSoundCoopFlags)
// @Purpose: DirectSound 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: DWORD dwSoundCoopFlags(声音协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::Create(HWND hWnd, DWORD dwSoundCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectSound8接口对象
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));					// 创建IDirectSound8接口对象
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, dwSoundCoopFlags));		// 设置DirectSound协作级别

	return S_OK;//OK
}

//------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, E_DX_SOUND_COOPFLAGS_TYPE eDirectSoundCoopFlags)
// @Purpose: DirectSound 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: DirectSoundCoopFlags eDirectSoundCoopFlags(枚举类型:声音协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::Create(HWND hWnd, E_DX_SOUND_COOPFLAGS_TYPE eDirectSoundCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwSoundCoopFlags;

	// 创建IDirectSound8接口对象
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));					// 创建IDirectSound8接口对象

	// 填充设备协作级别
	switch (eDirectSoundCoopFlags)
	{
	case DSCoopFlags_Normal:
		dwSoundCoopFlags = DSSCL_NORMAL;
		break;
	case DSCoopFlags_Priority:
		dwSoundCoopFlags = DSSCL_PRIORITY;
		break;
	case DSCoopFlags_Exclusive:
		dwSoundCoopFlags = DSSCL_EXCLUSIVE;
		break;
	case DSCoopFlags_WritePrimary:
		dwSoundCoopFlags = DSSCL_WRITEPRIMARY;
		break;
	default:
		break;
	}

	// 设置DirectSound协作级别
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, dwSoundCoopFlags));		// 设置DirectSound协作级别

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	Create3D(HWND hWnd)
// @Purpose: DirectSound3D 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::Create3D(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectSound8接口对象
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));					// 创建IDirectSound8接口对象
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY));			// 设置DirectSound协作级别(Priority模式)

	// 创建IDirectSoundBuffer接口对象(主缓冲区)
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
	m_DSPrimaryDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSPrimaryDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	VERIFY(m_pDirectSound->CreateSoundBuffer(&m_DSPrimaryDesc, &m_pDirectSoundPrimary, NULL));								// 创建声音主缓冲区
	VERIFY(m_pDirectSoundPrimary->QueryInterface(IID_IDirectSound3DListener, (void**)& m_pDirectSound3DListener));			// 创建3D Listener

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	LoadWave(LPWSTR lpszFileName)
// @Purpose: DirectSound 加载Wave音源文件(.wav)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(Wave音源文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::LoadWave(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HMMIO hWave;
	MMCKINFO Parent;
	MMCKINFO Child;
	MMRESULT result;
	WAVEFORMATEX* pWaveFormatEx;
	WAVEFORMATEX* pWaveFormatExDevice;
	UCHAR* pSoundBuffer = NULL;
	UCHAR* pAudioPtr1 = NULL;
	UCHAR* pAudioPtr2 = NULL;
	DWORD dwAudioLen1 = 0;
	DWORD dwAudioLen2 = 0;

	pWaveFormatEx = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatEx, sizeof(WAVEFORMATEX));
	ZeroMemory(&Parent, sizeof(Parent));
	ZeroMemory(&Child, sizeof(Child));

	//加载Wave音源文件
	hWave = mmioOpen(lpszFileName, NULL, MMIO_READ | MMIO_ALLOCBUF);//打开音源文件(.wav)
	if (hWave == NULL)//文件打开失败
	{
		return E_FAIL;//FAIL
	}

	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');//验证文件类型(.wav)
	result = mmioDescend(hWave, &Parent, NULL, MMIO_FINDRIFF);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('f', 'm', 't', ' ');//验证文件类型(wavefmt)
	result = mmioDescend(hWave, &Child, &Parent, NULL);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	if (mmioRead(hWave, (char*)pWaveFormatEx, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))//读取文件格式信息
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	if (pWaveFormatEx->wFormatTag != WAVE_FORMAT_PCM)//确认文件数据格式是PCM格式
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	result = mmioAscend(hWave, &Child, NULL);//Now ascend up one level, So we can access data chunk
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('d', 'a', 't', 'a');//验证数据段信息
	result = mmioDescend(hWave, &Child, &Parent, MMIO_FINDCHUNK);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	pSoundBuffer = (UCHAR*)malloc(Child.cksize);//申请音源内存空间
	mmioRead(hWave, (char*)pSoundBuffer, Child.cksize);//读取音源数据到内存
	mmioClose(hWave, NULL);//关闭文件

	//设置音源数据结构体
	pWaveFormatExDevice = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatExDevice, sizeof(WAVEFORMATEX));
	pWaveFormatExDevice->wFormatTag = pWaveFormatEx->wFormatTag;
	pWaveFormatExDevice->nChannels = pWaveFormatEx->nChannels;
	pWaveFormatExDevice->nSamplesPerSec = pWaveFormatEx->nSamplesPerSec;
	pWaveFormatExDevice->nBlockAlign = pWaveFormatEx->nBlockAlign;
	pWaveFormatExDevice->nAvgBytesPerSec = pWaveFormatEx->nAvgBytesPerSec;
	pWaveFormatExDevice->wBitsPerSample = pWaveFormatEx->wBitsPerSample;
	pWaveFormatExDevice->cbSize = pWaveFormatEx->cbSize;

	//准备创建声音缓冲区
	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	m_DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	m_DSBufferDesc.dwBufferBytes = Child.cksize;
	m_DSBufferDesc.lpwfxFormat = pWaveFormatExDevice;

	//创建声音缓冲区
	if (m_pDirectSound->CreateSoundBuffer(&m_DSBufferDesc, &m_pDirectSoundBuffer, NULL) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	//写入声音缓冲区
	m_pDirectSoundBuffer->Lock(0, Child.cksize, (void**)& pAudioPtr1, &dwAudioLen1, (void**)& pAudioPtr2, &dwAudioLen2, DSBLOCK_FROMWRITECURSOR);
	memcpy(pAudioPtr1, pSoundBuffer, dwAudioLen1);
	memcpy(pAudioPtr2, (pSoundBuffer + dwAudioLen1), dwAudioLen2);
	m_pDirectSoundBuffer->Unlock(pAudioPtr1, dwAudioLen1, pAudioPtr2, dwAudioLen2);

	SAFE_DELETE(pSoundBuffer);
	SAFE_DELETE(pWaveFormatEx);
	SAFE_DELETE(pWaveFormatExDevice);

	return S_OK;
}

//------------------------------------------------------------------------
// @Function:	LoadWave3D(LPWSTR lpszFileName)
// @Purpose: DirectSound 加载Wave音源文件(.wav)(3D)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(Wave音源文件相对地址)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMETHOD DirectSound::LoadWave3D(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HMMIO hWave;
	MMCKINFO Parent;
	MMCKINFO Child;
	MMRESULT result;
	WAVEFORMATEX* pWaveFormatEx;
	WAVEFORMATEX* pWaveFormatExDevice;
	UCHAR* pSoundBuffer = NULL;
	UCHAR* pAudioPtr1 = NULL;
	UCHAR* pAudioPtr2 = NULL;
	DWORD dwAudioLen1 = 0;
	DWORD dwAudioLen2 = 0;

	pWaveFormatEx = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatEx, sizeof(WAVEFORMATEX));
	ZeroMemory(&Parent, sizeof(Parent));
	ZeroMemory(&Child, sizeof(Child));

	//加载Wave音源文件
	hWave = mmioOpen(lpszFileName, NULL, MMIO_READ | MMIO_ALLOCBUF);//打开音源文件(.wav)
	if (hWave == NULL)//文件打开失败
	{
		return E_FAIL;//FAIL
	}

	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');//验证文件类型(.wav)
	result = mmioDescend(hWave, &Parent, NULL, MMIO_FINDRIFF);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('f', 'm', 't', ' ');//验证文件类型(wavefmt)
	result = mmioDescend(hWave, &Child, &Parent, NULL);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	if (mmioRead(hWave, (char*)pWaveFormatEx, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))//读取文件格式信息
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	if (pWaveFormatEx->wFormatTag != WAVE_FORMAT_PCM)//确认文件数据格式是PCM格式
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	result = mmioAscend(hWave, &Child, NULL);//Now ascend up one level, So we can access data chunk
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('d', 'a', 't', 'a');//验证数据段信息
	result = mmioDescend(hWave, &Child, &Parent, MMIO_FINDCHUNK);
	if (result)
	{
		mmioClose(hWave, NULL);//关闭文件
		return E_FAIL;//FAIL
	}

	pSoundBuffer = (UCHAR*)malloc(Child.cksize);//申请音源内存空间
	mmioRead(hWave, (char*)pSoundBuffer, Child.cksize);//读取音源数据到内存
	mmioClose(hWave, NULL);//关闭文件

	//设置音源数据结构体
	pWaveFormatExDevice = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatExDevice, sizeof(WAVEFORMATEX));
	pWaveFormatExDevice->wFormatTag = pWaveFormatEx->wFormatTag;
	pWaveFormatExDevice->nChannels = pWaveFormatEx->nChannels;
	pWaveFormatExDevice->nSamplesPerSec = pWaveFormatEx->nSamplesPerSec;
	pWaveFormatExDevice->nBlockAlign = pWaveFormatEx->nBlockAlign;
	pWaveFormatExDevice->nAvgBytesPerSec = pWaveFormatEx->nAvgBytesPerSec;
	pWaveFormatExDevice->wBitsPerSample = pWaveFormatEx->wBitsPerSample;
	pWaveFormatExDevice->cbSize = pWaveFormatEx->cbSize;

	//准备创建声音缓冲区
	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	m_DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
	m_DSBufferDesc.dwBufferBytes = Child.cksize;
	m_DSBufferDesc.lpwfxFormat = pWaveFormatExDevice;

	//创建声音缓冲区
	if (m_pDirectSound->CreateSoundBuffer(&m_DSBufferDesc, &m_pDirectSoundBuffer, NULL) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	if (m_pDirectSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, (void**)& m_pDirectSound3DBuffer) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	//设置3D音源位置
	m_pDirectSound3DListener->SetPosition(0, 0, 0, 1);//Listener位置
	m_pDirectSound3DBuffer->SetPosition(-10, 0, 0, 1);//3D音源位置
	m_pDirectSound3DBuffer->SetConeOrientation(0, 0, -1, 1);//面朝向
	m_pDirectSound3DListener->SetOrientation(1, 0, 0, 0, 1, 0, 1);//脸朝向

	//写入声音缓冲区
	m_pDirectSoundBuffer->Lock(0, Child.cksize, (void**)& pAudioPtr1, &dwAudioLen1, (void**)& pAudioPtr2, &dwAudioLen2, DSBLOCK_FROMWRITECURSOR);
	memcpy(pAudioPtr1, pSoundBuffer, dwAudioLen1);
	memcpy(pAudioPtr2, (pSoundBuffer + dwAudioLen1), dwAudioLen2);
	m_pDirectSoundBuffer->Unlock(pAudioPtr1, dwAudioLen1, pAudioPtr2, dwAudioLen2);

	SAFE_DELETE(pSoundBuffer);
	SAFE_DELETE(pWaveFormatEx);
	SAFE_DELETE(pWaveFormatExDevice);

	return S_OK;
}

//------------------------------------------------------------------------
// @Function:	Play()
// @Purpose: DirectSound 播放Wave音源文件(循环播放)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::Play()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, NULL);
}

//------------------------------------------------------------------------
// @Function:	Play(E_DX_SOUND_PLAYSTATE_TYPE eDSPlayState_X)
// @Purpose: DirectSound 播放Wave音源文件
// @Since: v1.00a
// @Para: DirectSoundPlayState eDSPlayState_X(播放状态)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::Play(E_DX_SOUND_PLAYSTATE_TYPE eDSPlayState_X)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eDSPlayState_X)
	{
	case DSPlayState_Loop:
		m_pDirectSoundBuffer->Play(NULL, NULL, DSBPLAY_LOOPING);
		break;
	case DSPlayState_Once:
		m_pDirectSoundBuffer->Play(NULL, NULL, NULL);
		break;
	default:
		break;
	}

}

//------------------------------------------------------------------------
// @Function:	PlayOnce()
// @Purpose: DirectSound 播放Wave音源文件(单次播放)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::PlayOnce()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, NULL);
}

//------------------------------------------------------------------------
// @Function:	PlayLoop()
// @Purpose: DirectSound 播放Wave音源文件(循环播放)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::PlayLoop()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, DSBPLAY_LOOPING);
}

void DIRECTSOUND_CALLMETHOD DirectSound::Stop()
{
	return void DIRECTSOUND_CALLMETHOD();
}

void DIRECTSOUND_CALLMETHOD DirectSound::SetVolume(LONG lVolume)
{
	return void DIRECTSOUND_CALLMETHOD();
}

void DIRECTSOUND_CALLMETHOD DirectSound::SetFrequency(DWORD dwFrequency)
{
	return void DIRECTSOUND_CALLMETHOD();
}

void DIRECTSOUND_CALLMETHOD DirectSound::SoundSetPan(LONG lPan)
{
	return void DIRECTSOUND_CALLMETHOD();
}

void DIRECTSOUND_CALLMETHOD DirectSound::SetCurrentPosition(DWORD dwNewPositon)
{
	return void DIRECTSOUND_CALLMETHOD();
}


//------------------------------------------------------------------------
// @Function:	DirectSoundStop(void)
// @Purpose: DirectSound 停止播放Wave音源文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::DirectSoundStop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Stop();//停止播放
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetVolume(LONG dwVolume)
// @Purpose: DirectSound 设置Wave音源音量
// @Since: v1.00a
// @Para: LONG lVolume(-10000~0)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::DirectSoundSetVolume(LONG lVolume)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (lVolume < DSBVOLUME_MIN)
	{
		lVolume = DSBVOLUME_MIN;
	}
	if (lVolume > DSBVOLUME_MAX)
	{
		lVolume = DSBVOLUME_MAX;
	}

	m_pDirectSoundBuffer->SetVolume(lVolume);
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetFrequency(DWORD dwFrequency)
// @Purpose: DirectSound 设置Wave音源频率
// @Since: v1.00a
// @Para: DWORD dwFrequency(100Hz~200,000Hz)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::DirectSoundSetFrequency(DWORD dwFrequency)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (dwFrequency < DSBFREQUENCY_MIN)
	{
		dwFrequency = DSBFREQUENCY_MIN;
	}
	if (dwFrequency > DSBFREQUENCY_MAX)
	{
		dwFrequency = DSBFREQUENCY_MAX;
	}

	m_pDirectSoundBuffer->SetFrequency(dwFrequency);
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetPan(LONG lPan)
// @Purpose: DirectSound 设置Wave音源声道平衡
// @Since: v1.00a
// @Para: LONG lPan
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::DirectSoundSetPan(LONG lPan)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (lPan < DSBPAN_LEFT)
	{
		lPan = DSBPAN_LEFT;
	}
	if (lPan > DSBPAN_RIGHT)
	{
		lPan = DSBPAN_RIGHT;
	}
	
	m_pDirectSoundBuffer->SetPan(lPan);
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetCurrentPosition(DWORD dwNewPositon)
// @Purpose: DirectSound 设置Wave音源播放位置
// @Since: v1.00a
// @Para: DWORD dwNewPositon(播放位置)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMETHOD DirectSound::DirectSoundSetCurrentPosition(DWORD dwNewPositon)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->SetCurrentPosition(dwNewPositon);
}