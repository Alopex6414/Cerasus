/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSound.cpp
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
#include "DirectCommon.h"
#include "DirectSound.h"
#include "DirectThreadSafe.h"

//------------------------------------------------------------------
// @Function:	 DirectSound()
// @Purpose: DirectSound���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::DirectSound()
{
	m_bThreadSafe = true;//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);//��ʼ���ٽ���

	m_pDirectSound = NULL;//IDirectSound8�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectSoundBuffer = NULL;//IDirectSoundBuffer�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectSoundPrimary = NULL;//IDirectSoundBuffer�ӿڶ���ָ���ʼ��(NULL)(��������)
	m_pDirectSound3DBuffer = NULL;//IDirectSound3DBuffer�ӿڶ���ָ���ʼ��(NULL)
	m_pDirectSound3DListener = NULL;//IDirectSound3DListener�ӿڶ���ָ���ʼ��(NULL)
	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));//���m_DSBufferDesc�ڴ�
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));//���m_DSPrimaryDesc�ڴ�
}

//------------------------------------------------------------------
// @Function:	 ~DirectSound()
// @Purpose: DirectSound��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSound::~DirectSound()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	SAFE_RELEASE(m_pDirectSound3DListener);//IDirectSound3DListener�ͷ�
	SAFE_RELEASE(m_pDirectSound3DBuffer);//IDirectSound3DBuffer�ͷ�
	SAFE_RELEASE(m_pDirectSoundPrimary);//IDirectSoundBuffer�ͷ�(��������)
	SAFE_RELEASE(m_pDirectSoundBuffer);//IDirectSoundBuffer�ͷ�
	SAFE_RELEASE(m_pDirectSound);//IDirectSound�ͷ�
	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);//ɾ���ٽ���
}

//------------------------------------------------------------------------
// @Function:	DirectSoundGetSound()
// @Purpose: DirectSound ��ȡIDirectSound8�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND8
//------------------------------------------------------------------------
LPDIRECTSOUND8 DIRECTSOUND_CALLMODE DirectSound::DirectSoundGetSound(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound;
};

//------------------------------------------------------------------------
// @Function:	DirectSoundGetSoundBuffer()
// @Purpose: DirectSound ��ȡIDirectSoundBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMODE DirectSound::DirectSoundGetSoundBuffer(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSoundBuffer;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundGetSoundBuffer()
// @Purpose: DirectSound ��ȡIDirectSoundBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUNDBUFFER DIRECTSOUND_CALLMODE DirectSound::DirectSoundGetSoundPrimary(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSoundPrimary;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundGetSound3DBuffer()
// @Purpose: DirectSound ��ȡIDirectSound3DBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DBUFFER
//------------------------------------------------------------------------
LPDIRECTSOUND3DBUFFER DIRECTSOUND_CALLMODE DirectSound::DirectSoundGetSound3DBuffer(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound3DBuffer;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundGetSound3DListener()
// @Purpose: DirectSound ��ȡIDirectSound3DBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DLISTENER
//------------------------------------------------------------------------
LPDIRECTSOUND3DLISTENER DIRECTSOUND_CALLMODE DirectSound::DirectSoundGetSound3DListener(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectSound3DListener;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetSound()
// @Purpose: DirectSound ����IDirectSound3DBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND8
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetSound(LPDIRECTSOUND8 pDirectSound)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSound = pDirectSound;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetSoundBuffer()
// @Purpose: DirectSound ����IDirectSoundBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetSoundBuffer(LPDIRECTSOUNDBUFFER pDirectSoundBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer = pDirectSoundBuffer;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetSoundBuffer()
// @Purpose: DirectSound ����IDirectSoundBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUNDBUFFER
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetSoundPrimary(LPDIRECTSOUNDBUFFER pDirectSoundPrimary)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundPrimary = pDirectSoundPrimary;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetSound3DBuffer()
// @Purpose: DirectSound ����IDirectSound3DBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DBUFFER
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetSound3DBuffer(LPDIRECTSOUND3DBUFFER pDirectSound3DBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSound3DBuffer = pDirectSound3DBuffer;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetSound3DListener()
// @Purpose: DirectSound ����IDirectSound3DBuffer�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTSOUND3DLISTENER
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetSound3DListener(LPDIRECTSOUND3DLISTENER pDirectSound3DListener)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSound3DListener = pDirectSound3DListener;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundInit(HWND hWnd)
// @Purpose: DirectSound ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSoundInit(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//����IDirectSound8�ӿڶ���
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));//����IDirectSound8�ӿڶ���
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL));//����DirectSoundЭ������(Normalģʽ)

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	DirectSoundInit(HWND hWnd, DWORD dwSoundCoopFlags)
// @Purpose: DirectSound ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: DWORD dwSoundCoopFlags(����Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSoundInit(HWND hWnd, DWORD dwSoundCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//����IDirectSound8�ӿڶ���
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));//����IDirectSound8�ӿڶ���
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, dwSoundCoopFlags));//����DirectSoundЭ������

	return S_OK;//OK
}

//------------------------------------------------------------------------------------
// @Function:	DirectSoundInit(HWND hWnd, DirectSoundCoopFlags eDirectSoundCoopFlags)
// @Purpose: DirectSound ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: DirectSoundCoopFlags eDirectSoundCoopFlags(ö������:����Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSoundInit(HWND hWnd, DirectSoundCoopFlags eDirectSoundCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwSoundCoopFlags;

	//����IDirectSound8�ӿڶ���
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));//����IDirectSound8�ӿڶ���

	//����豸Э������
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

	//����DirectSoundЭ������
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, dwSoundCoopFlags));//����DirectSoundЭ������

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	DirectSound3DInit(HWND hWnd)
// @Purpose: DirectSound3D ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSound3DInit(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//����IDirectSound8�ӿڶ���
	VERIFY(DirectSoundCreate8(NULL, &m_pDirectSound, NULL));//����IDirectSound8�ӿڶ���
	VERIFY(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY));//����DirectSoundЭ������(Priorityģʽ)

	//����IDirectSoundBuffer�ӿڶ���(��������)
	ZeroMemory(&m_DSPrimaryDesc, sizeof(m_DSPrimaryDesc));
	m_DSPrimaryDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSPrimaryDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	VERIFY(m_pDirectSound->CreateSoundBuffer(&m_DSPrimaryDesc, &m_pDirectSoundPrimary, NULL));//����������������
	VERIFY(m_pDirectSoundPrimary->QueryInterface(IID_IDirectSound3DListener, (void**)&m_pDirectSound3DListener));//����3D Listener

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	DirectSoundLoadWave(LPWSTR lpszFileName)
// @Purpose: DirectSound ����Wave��Դ�ļ�(.wav)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(Wave��Դ�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSoundLoadWave(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HMMIO hWave;
	MMCKINFO Parent;
	MMCKINFO Child;
	MMRESULT result;
	WAVEFORMATEX *pWaveFormatEx;
	WAVEFORMATEX *pWaveFormatExDevice;
	UCHAR *pSoundBuffer = NULL;
	UCHAR *pAudioPtr1 = NULL;
	UCHAR *pAudioPtr2 = NULL;
	DWORD dwAudioLen1 = 0;
	DWORD dwAudioLen2 = 0;

	pWaveFormatEx = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatEx, sizeof(WAVEFORMATEX));
	ZeroMemory(&Parent, sizeof(Parent));
	ZeroMemory(&Child, sizeof(Child));

	//����Wave��Դ�ļ�
	hWave = mmioOpen(lpszFileName, NULL, MMIO_READ | MMIO_ALLOCBUF);//����Դ�ļ�(.wav)
	if (hWave == NULL)//�ļ���ʧ��
	{
		return E_FAIL;//FAIL
	}

	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');//��֤�ļ�����(.wav)
	result = mmioDescend(hWave, &Parent, NULL, MMIO_FINDRIFF);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('f', 'm', 't', ' ');//��֤�ļ�����(wavefmt)
	result = mmioDescend(hWave, &Child, &Parent, NULL);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	if (mmioRead(hWave, (char*)pWaveFormatEx, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))//��ȡ�ļ���ʽ��Ϣ
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	if (pWaveFormatEx->wFormatTag != WAVE_FORMAT_PCM)//ȷ���ļ����ݸ�ʽ��PCM��ʽ
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	result = mmioAscend(hWave, &Child, NULL);//Now ascend up one level, So we can access data chunk
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('d', 'a', 't', 'a');//��֤���ݶ���Ϣ
	result = mmioDescend(hWave, &Child, &Parent, MMIO_FINDCHUNK);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	pSoundBuffer = (UCHAR*)malloc(Child.cksize);//������Դ�ڴ�ռ�
	mmioRead(hWave, (char*)pSoundBuffer, Child.cksize);//��ȡ��Դ���ݵ��ڴ�
	mmioClose(hWave, NULL);//�ر��ļ�

	//������Դ���ݽṹ��
	pWaveFormatExDevice = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatExDevice, sizeof(WAVEFORMATEX));
	pWaveFormatExDevice->wFormatTag = pWaveFormatEx->wFormatTag;
	pWaveFormatExDevice->nChannels = pWaveFormatEx->nChannels;
	pWaveFormatExDevice->nSamplesPerSec = pWaveFormatEx->nSamplesPerSec;
	pWaveFormatExDevice->nBlockAlign = pWaveFormatEx->nBlockAlign;
	pWaveFormatExDevice->nAvgBytesPerSec = pWaveFormatEx->nAvgBytesPerSec;
	pWaveFormatExDevice->wBitsPerSample = pWaveFormatEx->wBitsPerSample;
	pWaveFormatExDevice->cbSize = pWaveFormatEx->cbSize;

	//׼����������������
	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	m_DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCDEFER;
	m_DSBufferDesc.dwBufferBytes = Child.cksize;
	m_DSBufferDesc.lpwfxFormat = pWaveFormatExDevice;

	//��������������
	if (m_pDirectSound->CreateSoundBuffer(&m_DSBufferDesc, &m_pDirectSoundBuffer, NULL) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	//д������������
	m_pDirectSoundBuffer->Lock(0, Child.cksize, (void**)&pAudioPtr1, &dwAudioLen1, (void**)&pAudioPtr2, &dwAudioLen2, DSBLOCK_FROMWRITECURSOR);
	memcpy(pAudioPtr1, pSoundBuffer, dwAudioLen1);
	memcpy(pAudioPtr2, (pSoundBuffer + dwAudioLen1), dwAudioLen2);
	m_pDirectSoundBuffer->Unlock(pAudioPtr1, dwAudioLen1, pAudioPtr2, dwAudioLen2);

	SAFE_DELETE(pSoundBuffer);
	SAFE_DELETE(pWaveFormatEx);
	SAFE_DELETE(pWaveFormatExDevice);

	return S_OK;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundLoad3DWave(LPWSTR lpszFileName)
// @Purpose: DirectSound ����Wave��Դ�ļ�(.wav)(3D)
// @Since: v1.00a
// @Para: LPWSTR lpszFileName(Wave��Դ�ļ���Ե�ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTSOUND_CALLMODE DirectSound::DirectSoundLoad3DWave(LPWSTR lpszFileName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HMMIO hWave;
	MMCKINFO Parent;
	MMCKINFO Child;
	MMRESULT result;
	WAVEFORMATEX *pWaveFormatEx;
	WAVEFORMATEX *pWaveFormatExDevice;
	UCHAR *pSoundBuffer = NULL;
	UCHAR *pAudioPtr1 = NULL;
	UCHAR *pAudioPtr2 = NULL;
	DWORD dwAudioLen1 = 0;
	DWORD dwAudioLen2 = 0;

	pWaveFormatEx = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatEx, sizeof(WAVEFORMATEX));
	ZeroMemory(&Parent, sizeof(Parent));
	ZeroMemory(&Child, sizeof(Child));

	//����Wave��Դ�ļ�
	hWave = mmioOpen(lpszFileName, NULL, MMIO_READ | MMIO_ALLOCBUF);//����Դ�ļ�(.wav)
	if (hWave == NULL)//�ļ���ʧ��
	{
		return E_FAIL;//FAIL
	}

	Parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');//��֤�ļ�����(.wav)
	result = mmioDescend(hWave, &Parent, NULL, MMIO_FINDRIFF);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('f', 'm', 't', ' ');//��֤�ļ�����(wavefmt)
	result = mmioDescend(hWave, &Child, &Parent, NULL);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	if (mmioRead(hWave, (char*)pWaveFormatEx, sizeof(WAVEFORMATEX)) != sizeof(WAVEFORMATEX))//��ȡ�ļ���ʽ��Ϣ
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	if (pWaveFormatEx->wFormatTag != WAVE_FORMAT_PCM)//ȷ���ļ����ݸ�ʽ��PCM��ʽ
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	result = mmioAscend(hWave, &Child, NULL);//Now ascend up one level, So we can access data chunk
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	Child.ckid = mmioFOURCC('d', 'a', 't', 'a');//��֤���ݶ���Ϣ
	result = mmioDescend(hWave, &Child, &Parent, MMIO_FINDCHUNK);
	if (result)
	{
		mmioClose(hWave, NULL);//�ر��ļ�
		return E_FAIL;//FAIL
	}

	pSoundBuffer = (UCHAR*)malloc(Child.cksize);//������Դ�ڴ�ռ�
	mmioRead(hWave, (char*)pSoundBuffer, Child.cksize);//��ȡ��Դ���ݵ��ڴ�
	mmioClose(hWave, NULL);//�ر��ļ�

	//������Դ���ݽṹ��
	pWaveFormatExDevice = new WAVEFORMATEX;
	ZeroMemory(pWaveFormatExDevice, sizeof(WAVEFORMATEX));
	pWaveFormatExDevice->wFormatTag = pWaveFormatEx->wFormatTag;
	pWaveFormatExDevice->nChannels = pWaveFormatEx->nChannels;
	pWaveFormatExDevice->nSamplesPerSec = pWaveFormatEx->nSamplesPerSec;
	pWaveFormatExDevice->nBlockAlign = pWaveFormatEx->nBlockAlign;
	pWaveFormatExDevice->nAvgBytesPerSec = pWaveFormatEx->nAvgBytesPerSec;
	pWaveFormatExDevice->wBitsPerSample = pWaveFormatEx->wBitsPerSample;
	pWaveFormatExDevice->cbSize = pWaveFormatEx->cbSize;

	//׼����������������
	ZeroMemory(&m_DSBufferDesc, sizeof(m_DSBufferDesc));
	m_DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	m_DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2;
	m_DSBufferDesc.dwBufferBytes = Child.cksize;
	m_DSBufferDesc.lpwfxFormat = pWaveFormatExDevice;

	//��������������
	if (m_pDirectSound->CreateSoundBuffer(&m_DSBufferDesc, &m_pDirectSoundBuffer, NULL) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	if (m_pDirectSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, (void**)&m_pDirectSound3DBuffer) != DS_OK)
	{
		SAFE_DELETE(pSoundBuffer);
		return E_FAIL;//FAIL
	}

	//����3D��Դλ��
	m_pDirectSound3DListener->SetPosition(0, 0, 0, 1);//Listenerλ��
	m_pDirectSound3DBuffer->SetPosition(-10, 0, 0, 1);//3D��Դλ��
	m_pDirectSound3DBuffer->SetConeOrientation(0, 0, -1, 1);//�泯��
	m_pDirectSound3DListener->SetOrientation(1, 0, 0, 0, 1, 0, 1);//������

	//д������������
	m_pDirectSoundBuffer->Lock(0, Child.cksize, (void**)&pAudioPtr1, &dwAudioLen1, (void**)&pAudioPtr2, &dwAudioLen2, DSBLOCK_FROMWRITECURSOR);
	memcpy(pAudioPtr1, pSoundBuffer, dwAudioLen1);
	memcpy(pAudioPtr2, (pSoundBuffer + dwAudioLen1), dwAudioLen2);
	m_pDirectSoundBuffer->Unlock(pAudioPtr1, dwAudioLen1, pAudioPtr2, dwAudioLen2);

	SAFE_DELETE(pSoundBuffer);
	SAFE_DELETE(pWaveFormatEx);
	SAFE_DELETE(pWaveFormatExDevice);

	return S_OK;
}

//------------------------------------------------------------------------
// @Function:	DirectSoundPlay(void)
// @Purpose: DirectSound ����Wave��Դ�ļ�(ѭ������)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundPlay(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, NULL);//���β��� Once
}

//------------------------------------------------------------------------
// @Function:	DirectSoundPlay(DirectSoundPlayState eDSPlayState_X)
// @Purpose: DirectSound ����Wave��Դ�ļ�
// @Since: v1.00a
// @Para: DirectSoundPlayState eDSPlayState_X(����״̬)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundPlay(DirectSoundPlayState eDSPlayState_X)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eDSPlayState_X)
	{
	case DSPlayState_Loop://Loop
		m_pDirectSoundBuffer->Play(NULL, NULL, DSBPLAY_LOOPING);
		break;
	case DSPlayState_Once://Once
		m_pDirectSoundBuffer->Play(NULL, NULL, NULL);
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------
// @Function:	DirectSoundPlayOnce(void)
// @Purpose: DirectSound ����Wave��Դ�ļ�(���β���)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundPlayOnce(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, NULL);//���β��� Once
}

//------------------------------------------------------------------------
// @Function:	DirectSoundPlayLoop(void)
// @Purpose: DirectSound ����Wave��Դ�ļ�(ѭ������)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundPlayLoop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Play(NULL, NULL, DSBPLAY_LOOPING);//ѭ������ Loop
}

//------------------------------------------------------------------------
// @Function:	DirectSoundStop(void)
// @Purpose: DirectSound ֹͣ����Wave��Դ�ļ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundStop(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->Stop();//ֹͣ����
}

//------------------------------------------------------------------------
// @Function:	DirectSoundSetVolume(LONG dwVolume)
// @Purpose: DirectSound ����Wave��Դ����
// @Since: v1.00a
// @Para: LONG lVolume(-10000~0)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetVolume(LONG lVolume)
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
// @Purpose: DirectSound ����Wave��ԴƵ��
// @Since: v1.00a
// @Para: DWORD dwFrequency(100Hz~200,000Hz)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetFrequency(DWORD dwFrequency)
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
// @Purpose: DirectSound ����Wave��Դ����ƽ��
// @Since: v1.00a
// @Para: LONG lPan
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetPan(LONG lPan)
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
// @Purpose: DirectSound ����Wave��Դ����λ��
// @Since: v1.00a
// @Para: DWORD dwNewPositon(����λ��)
// @Return: None
//------------------------------------------------------------------------
void DIRECTSOUND_CALLMODE DirectSound::DirectSoundSetCurrentPosition(DWORD dwNewPositon)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pDirectSoundBuffer->SetCurrentPosition(dwNewPositon);
}