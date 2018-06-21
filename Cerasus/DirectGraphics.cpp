/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics.cpp
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.27a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-2	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-02-11	v1.22a	alopex	Add D3D9 Lost Device Function.
* @date		2018-04-12	v1.23a	alopex	Add Macro Call Mode.
* @date		2018-06-16	v1.24a	alopex	Add StretchRect Function.
* @date		2018-06-17	v1.25a	alopex	Modify Reset Function.
* @date		2018-06-18	v1.26a	alopex	Modify D3D9 Clear Function(Background Color).
* @date		2018-06-21	v1.27a	alopex	Update Function D3DXFont Abort.
*/
#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectThreadSafe.h"

//------------------------------------------------------------------
// @Function:	 DirectGraphics()
// @Purpose: DirectGraphics���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::DirectGraphics()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_nWidth = 0;			//IDirect3D9���ڿ��
	m_nHeight = 0;			//IDirect3D9���ڸ߶�

	m_pD3D9 = NULL;			//IDirect3D9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Device = NULL;	//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3DXFont = NULL;		//ID3DXFont�ӿ�ָ���ʼ��(NULL)
	ZeroMemory(&m_D3D9Caps, sizeof(m_D3D9Caps));	//���m_D3D9Caps�ڴ�����
	ZeroMemory(&m_D3D9pp, sizeof(m_D3D9pp));		//���m_D3D9pp�ڴ�����
	ZeroMemory(m_wcD3D9AdapterType, sizeof(wchar_t)*ADAPTERTYPESIZE);	//���m_wcD3D9AdapterType�ڴ�����
	ZeroMemory(m_wcD3D9BackFormat, sizeof(wchar_t)*D3D9FORMATSIZE);		//���m_wcD3D9BackFormat�ڴ�����
	ZeroMemory(m_wcD3D9AutoDepthStencilFormat, sizeof(wchar_t)*D3D9FORMATSIZE);	//���m_wcD3D9AutoDepthStencilFormat�ڴ�����
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics()
// @Purpose: DirectGraphics��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::~DirectGraphics()
{
	SAFE_RELEASE(m_pD3DXFont);		//ID3DXFont�ӿ��ͷ�
	SAFE_RELEASE(m_pD3D9Device);	//IDirect3D9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9);			//IDirect3DDevice9�ӿ�ָ���ͷ�

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetObject(void) const
// @Purpose: DirectGraphics��ȡD3D9����
// @Since: v1.00a
// @Para: None
// @Return: IDirect3D9*(D3D9����ָ��)
//------------------------------------------------------------------
IDirect3D9* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetObject(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetDevice(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸����
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DDevice9*(D3D9�豸����ָ��)
//------------------------------------------------------------------
IDirect3DDevice9* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetCaps(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸�ͺ�
// @Since: v1.00a
// @Para: None
// @Return: D3DCAPS9*(D3D9�豸�ͺ�ָ��)
//------------------------------------------------------------------
const D3DCAPS9* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetCaps(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9Caps);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetPresentParameters(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸����
// @Since: v1.00a
// @Para: None
// @Return: D3DPRESENT_PARAMETERS*(D3D9�豸����ָ��)
//------------------------------------------------------------------
const D3DPRESENT_PARAMETERS* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetPresentParameters(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9pp);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetAdapterType(void) const
// @Purpose: DirectGraphics��ȡD3D9 GPU�ͺ�
// @Since: v1.00a
// @Para: None
// @Return: wchar_t*(���ַ������ַ)
//------------------------------------------------------------------
const wchar_t* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetAdapterType(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_wcD3D9AdapterType;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetBackBufferFormat(void) const
// @Purpose: DirectGraphics��ȡD3D9 ��̨�����ʽ
// @Since: v1.00a
// @Para: None
// @Return: wchar_t*(���ַ������ַ)
//------------------------------------------------------------------
const wchar_t* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetBackBufferFormat(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_wcD3D9BackFormat;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetAutoDepthStencilFormat(void) const
// @Purpose: DirectGraphics��ȡD3D9 ���ģ�建���ʽ
// @Since: v1.00a
// @Para: None
// @Return: wchar_t*(���ַ������ַ)
//------------------------------------------------------------------
const wchar_t* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetAutoDepthStencilFormat(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_wcD3D9AutoDepthStencilFormat;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetFont(void) const
// @Purpose: DirectGraphics��ȡD3D9 GPU����
// @Since: v1.00a
// @Para: None
// @Return: ID3DXFont*(ID3DXFont����ָ��)
//------------------------------------------------------------------
const ID3DXFont* DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetFont(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXFont;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetSufaceWidth(void) const
// @Purpose: DirectGraphics��ȡD3D9 �豸������
// @Since: v1.00a
// @Para: None
// @Return: UINT
//------------------------------------------------------------------
const UINT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetSufaceWidth(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nWidth;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetSufaceHeight(void) const
// @Purpose: DirectGraphics��ȡD3D9 �豸����߶�
// @Since: v1.00a
// @Para: None
// @Return: UINT
//------------------------------------------------------------------
const UINT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetSufaceHeight(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_nHeight;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsTestCooperativeLevel(void) const
// @Purpose: DirectGraphics��ȡD3D9 ��ǰ״̬
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//			D3DERR_DEVICELOST:�豸��ʧ(�޷�Reset)
//			D3DERR_DEVICENOTRESET:�豸δReset(����Reset)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsTestCooperativeLevel(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->TestCooperativeLevel());
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsResetDevice(void) const
// @Purpose: DirectGraphics����D3D9 ��ʼ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsResetDevice(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->Reset(&m_D3D9pp));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetBackBuffer(IDirect3DSurface9* pD3D9BackBuffer)
// @Purpose: DirectGraphics��ȡD3D9 ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetBackBuffer(IDirect3DSurface9** ppD3D9BackBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, ppD3D9BackBuffer));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsResetFont(void)
// @Purpose: DirectGraphics ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(����״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsResetFont(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3DXFont ? m_pD3DXFont->OnLostDevice() : S_OK);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsReset(void)
// @Purpose: DirectGraphics ����D3D9 DirectGraphics��
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(����״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	IDirect3DSurface9* pD3D9BackBuffer = NULL;
	if (m_pD3DXFont) VERIFY(m_pD3DXFont->OnLostDevice());
	VERIFY(m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer));
	SAFE_RELEASE(pD3D9BackBuffer);
	VERIFY(m_pD3D9Device->Reset(&m_D3D9pp));
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface)
// @Purpose: DirectGraphics ������������
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9** ppD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->CreateOffscreenPlainSurface(nWidth, nHeight, D3DFormat, D3DPool, ppD3D9Surface, NULL);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, IDirect3DSurface9**& ppD3D9Surface)
// @Purpose: DirectGraphics ������������
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, IDirect3DSurface9 ** ppD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->CreateOffscreenPlainSurface(nWidth, nHeight, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, ppD3D9Surface, NULL);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, IDirect3DSurface9**& ppD3D9Surface)
// @Purpose: DirectGraphics ������������
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsCreateOffscreenPlainSurface(IDirect3DSurface9 ** ppD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->CreateOffscreenPlainSurface(USER_SCREENWIDTH, USER_SCREENHEIGHT, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, ppD3D9Surface, NULL);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
// @Purpose: DirectGraphics ���Ʊ���
// @Since: v1.00a
// @Para: IDirect3DSurface9* pSourceSurface(Դ�����ַ)
// @Para: const RECT* pSourceRect(Դ��������)
// @Para: IDirect3DSurface9* pDestSurface(Ŀ������ַ)
// @Para: const RECT* pDestRect(Ŀ���������)
// @Para: D3DTEXTUREFILTERTYPE Filter(D3D�����˲�����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect)
// @Purpose: DirectGraphics ���Ʊ���
// @Since: v1.00a
// @Para: IDirect3DSurface9* pSourceSurface(Դ�����ַ)
// @Para: const RECT* pSourceRect(Դ��������)
// @Para: IDirect3DSurface9* pDestSurface(Ŀ������ַ)
// @Para: const RECT* pDestRect(Ŀ���������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsStretchRect(IDirect3DSurface9 * pSourceSurface, const RECT * pSourceRect, IDirect3DSurface9 * pDestSurface, const RECT * pDestRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, D3DTEXF_NONE);
}

//------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, IDirect3DSurface9* pDestSurface)
// @Purpose: DirectGraphics ���Ʊ���
// @Since: v1.00a
// @Para: IDirect3DSurface9* pSourceSurface(Դ�����ַ)
// @Para: IDirect3DSurface9* pDestSurface(Ŀ������ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsStretchRect(IDirect3DSurface9 * pSourceSurface, IDirect3DSurface9 * pDestSurface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->StretchRect(pSourceSurface, NULL, pDestSurface, NULL, D3DTEXF_NONE);
}

//----------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect)
// @Purpose: DirectGraphics ���Ʊ���
// @Since: v1.00a
// @Para: IDirect3DSurface9* pSourceSurface(Դ�����ַ)
// @Para: const RECT* pSourceRect(Դ��������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsStretchRect(IDirect3DSurface9 * pSourceSurface, const RECT * pSourceRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	IDirect3DSurface9* pD3D9BackBuffer = NULL;
	HRESULT hr;

	m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
	hr = m_pD3D9Device->StretchRect(pSourceSurface, pSourceRect, pD3D9BackBuffer, NULL, D3DTEXF_NONE);
	SAFE_RELEASE(pD3D9BackBuffer);

	return hr;
}

//---------------------------------------------------------------------------
// @Function:	 DirectGraphicsStretchRect(IDirect3DSurface9* pSourceSurface)
// @Purpose: DirectGraphics ���Ʊ���
// @Since: v1.00a
// @Para: IDirect3DSurface9* pSourceSurface(Դ�����ַ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsStretchRect(IDirect3DSurface9 * pSourceSurface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	IDirect3DSurface9* pD3D9BackBuffer = NULL;
	HRESULT hr;

	m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
	hr = m_pD3D9Device->StretchRect(pSourceSurface, NULL, pD3D9BackBuffer, NULL, D3DTEXF_NONE);
	SAFE_RELEASE(pD3D9BackBuffer);

	return hr;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsInit(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = true;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡ���ڳߴ�
	m_nWidth = m_D3D9pp.BackBufferWidth;
	m_nHeight = m_D3D9pp.BackBufferHeight;

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	//��ȡ��̨�������ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9BackFormat);

	//��ȡ��Ȼ����ģ�建�����ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9AutoDepthStencilFormat);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: bool bIsWindowed(�Ƿ��Դ���ģʽ����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = bIsWindowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡ���ڳߴ�
	m_nWidth = m_D3D9pp.BackBufferWidth;
	m_nHeight = m_D3D9pp.BackBufferHeight;

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	//��ȡ��̨�������ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9BackFormat);

	//��ȡ��Ȼ����ģ�建�����ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9AutoDepthStencilFormat);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: bool bIsWindowed(�Ƿ��Դ���ģʽ����)
// @Para: int nScreenWidth(��Ļ���)
// @Para: int nScreenHeight(��Ļ�߶�)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = nScreenWidth;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = nScreenHeight;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = bIsWindowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡ���ڳߴ�
	m_nWidth = m_D3D9pp.BackBufferWidth;
	m_nHeight = m_D3D9pp.BackBufferHeight;

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	//��ȡ��̨�������ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9BackFormat);

	//��ȡ��Ȼ����ģ�建�����ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9AutoDepthStencilFormat);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: D3DPRESENT_PARAMETERS D3D9pp(D3D9����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = D3D9pp.BackBufferWidth;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = D3D9pp.BackBufferHeight;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3D9pp.BackBufferFormat;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = D3D9pp.BackBufferCount;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3D9pp.MultiSampleType;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = D3D9pp.MultiSampleQuality;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3D9pp.SwapEffect;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = D3D9pp.hDeviceWindow;//�豸��ش��ھ��
	m_D3D9pp.Windowed = D3D9pp.Windowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = D3D9pp.EnableAutoDepthStencil;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3D9pp.AutoDepthStencilFormat;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = D3D9pp.Flags;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3D9pp.FullScreen_RefreshRateInHz;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3D9pp.PresentationInterval;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3D9pp.hDeviceWindow, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡ���ڳߴ�
	m_nWidth = m_D3D9pp.BackBufferWidth;
	m_nHeight = m_D3D9pp.BackBufferHeight;

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	//��ȡ��̨�������ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9BackFormat);

	//��ȡ��Ȼ����ģ�建�����ظ�ʽ
	DirectGraphicsGetD3D9Format(m_wcD3D9AutoDepthStencilFormat);

	return S_OK;//OK
}
//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBeginScene(void)
// @Purpose: DirectGraphics ��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsBeginScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->BeginScene());	//��ʼ��Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEndScene(void)
// @Purpose: DirectGraphics ������Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsEndScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//������Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBegin(void)
// @Purpose: DirectGraphics ��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsBegin(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//���ͼ��
	VERIFY(m_pD3D9Device->BeginScene());	//��ʼ��Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBegin(void)
// @Purpose: DirectGraphics ��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsBegin(D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color, 1.0f, 0));		//���ͼ��
	VERIFY(m_pD3D9Device->BeginScene());	//��ʼ��Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEnd(void)
// @Purpose: DirectGraphics ������Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsEnd(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//������Ⱦ
	VERIFY(m_pD3D9Device->Present(NULL, NULL, NULL, NULL));		//�ύ��Ⱦ(��ʾ)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsPresent(void)
// @Purpose: DirectGraphics �ύ��Ⱦ(��ʾ)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsPresent(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Present(NULL,NULL,NULL,NULL));		//�ύ��Ⱦ(��ʾ)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(void)
// @Purpose: DirectGraphics ���ͼ��
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsClear(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//���ͼ��
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(DWORD dwColor)
// @Purpose: DirectGraphics ���ͼ��
// @Since: v1.00a
// @Para: D3DCOLOR Color(������ɫ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsClear(D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, Color, 1.0f, 0));		//���ͼ��
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(void)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontInit(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, 20, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: int nFontSize		//�����С
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontInit(int Height)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, Height, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: int nFontSize			//�����С
// @Para: LPWSTR lpszFontType	//��������
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontInit(int Height, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, Height, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, lpszFontType, &m_pD3DXFont));
	return S_OK;//OK
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCWSTR pFaceName)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: INT Height
// @Para: UINT Width
// @Para: UINT Weight
// @Para: UINT MipLevels
// @Para: BOOL Italic
// @Para: DWORD CharSet
// @Para: DWORD OutputPrecision
// @Para: DWORD Quality
// @Para: DWORD PitchAndFamily
// @Para: LPCWSTR pFaceName
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontInit(INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCWSTR pFaceName)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, Height, Width, Weight, MipLevels, Italic, CharSet, OutputPrecision, Quality, PitchAndFamily, pFaceName, &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawText(HWND hWnd)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: HWND hWnd		//���ھ��
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontDrawText(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3DXFont->DrawText(NULL, m_wcD3D9AdapterType, -1, &Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawText(D3DXCOLOR dwColor)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: HWND hWnd				//���ھ��
// @Para: D3DXCOLOR dwColor		//������ɫ
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3DXFont->DrawText(NULL, m_wcD3D9AdapterType, -1, &Rect, DT_TOP | DT_LEFT, dwColor);
}

//-----------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawTextW(LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: LPCWSTR pString		//�ַ�����(Unicode)
// @Para: INT Count				//���鳤��(-1)
// @Para: LPRECT pRect			//��������
// @Para: DWORD Format			//���Ƹ�ʽ
// @Para: D3DCOLOR Color		//������ɫ
// @Return: None
//-----------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontDrawTextW(LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3DXFont->DrawTextW(NULL, pString, Count, pRect, Format, Color);
}

//-----------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawTextA(LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: LPCSTR pString		//�ַ�����(ASCII)
// @Para: INT Count				//���鳤��(-1)
// @Para: LPRECT pRect			//��������
// @Para: DWORD Format			//���Ƹ�ʽ
// @Para: D3DCOLOR Color		//������ɫ
// @Return: None
//-----------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsFontDrawTextA(LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3DXFont->DrawTextA(NULL, pString, Count, pRect, Format, Color);
}

//-----------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsGetD3D9Format(LPCWSTR pString, UINT nSize)
// @Purpose: DirectGraphics ��ȡ��̨�����ͺ�
// @Since: v1.01a
// @Para: LPCWSTR pString		//�����ַ
// @Para: UINT nSize			//���鳤��
// @Return: None
//-----------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS_CALLMODE DirectGraphics::DirectGraphicsGetD3D9Format(LPWSTR pString)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	CHAR chString[MAX_PATH] = { 0 };
	INT nSize = 0;

	switch (m_D3D9pp.BackBufferFormat)
	{
	case D3DFMT_UNKNOWN:
		strcpy_s(chString, "D3DFMT_UNKNOWN");
		break;
	case D3DFMT_R8G8B8:
		strcpy_s(chString, "D3DFMT_R8G8B8");
		break;
	case D3DFMT_A8R8G8B8:
		strcpy_s(chString, "D3DFMT_A8R8G8B8");
		break;
	case D3DFMT_X8R8G8B8:
		strcpy_s(chString, "D3DFMT_A8R8G8B8");
		break;
	case D3DFMT_R5G6B5:
		strcpy_s(chString, "D3DFMT_R5G6B5");
		break;
	case D3DFMT_X1R5G5B5:
		strcpy_s(chString, "D3DFMT_X1R5G5B5");
		break;
	case D3DFMT_A1R5G5B5:
		strcpy_s(chString, "D3DFMT_A1R5G5B5");
		break;
	case D3DFMT_A4R4G4B4:
		strcpy_s(chString, "D3DFMT_A4R4G4B4");
		break;
	case D3DFMT_R3G3B2:
		strcpy_s(chString, "D3DFMT_R3G3B2");
		break;
	case D3DFMT_A8:
		strcpy_s(chString, "D3DFMT_A8");
		break;
	case D3DFMT_A8R3G3B2:
		strcpy_s(chString, "D3DFMT_A8R3G3B2");
		break;
	case D3DFMT_X4R4G4B4:
		strcpy_s(chString, "D3DFMT_X4R4G4B4");
		break;
	case D3DFMT_A2B10G10R10:
		strcpy_s(chString, "D3DFMT_A2B10G10R10");
		break;
	case D3DFMT_A8B8G8R8:
		strcpy_s(chString, "D3DFMT_A8B8G8R8");
		break;
	case D3DFMT_X8B8G8R8:
		strcpy_s(chString, "D3DFMT_X8B8G8R8");
		break;
	case D3DFMT_G16R16:
		strcpy_s(chString, "D3DFMT_G16R16");
		break;
	case D3DFMT_A2R10G10B10:
		strcpy_s(chString, "D3DFMT_A2R10G10B10");
		break;
	case D3DFMT_A16B16G16R16:
		strcpy_s(chString, "D3DFMT_A16B16G16R16");
		break;
	case D3DFMT_A8P8:
		strcpy_s(chString, "D3DFMT_A8P8");
		break;
	case D3DFMT_P8:
		strcpy_s(chString, "D3DFMT_P8");
		break;
	case D3DFMT_L8:
		strcpy_s(chString, "D3DFMT_L8");
		break;
	case D3DFMT_A8L8:
		strcpy_s(chString, "D3DFMT_A8L8");
		break;
	case D3DFMT_A4L4:
		strcpy_s(chString, "D3DFMT_A4L4");
		break;
	case D3DFMT_V8U8:
		strcpy_s(chString, "D3DFMT_V8U8");
		break;
	case D3DFMT_L6V5U5:
		strcpy_s(chString, "D3DFMT_L6V5U5");
		break;
	case D3DFMT_X8L8V8U8:
		strcpy_s(chString, "D3DFMT_X8L8V8U8");
		break;
	case D3DFMT_Q8W8V8U8:
		strcpy_s(chString, "D3DFMT_Q8W8V8U8");
		break;
	case D3DFMT_V16U16:
		strcpy_s(chString, "D3DFMT_V16U16");
		break;
	case D3DFMT_A2W10V10U10:
		strcpy_s(chString, "D3DFMT_A2W10V10U10");
		break;
	case D3DFMT_UYVY:
		strcpy_s(chString, "D3DFMT_UYVY");
		break;
	case D3DFMT_R8G8_B8G8:
		strcpy_s(chString, "D3DFMT_R8G8_B8G8");
		break;
	case D3DFMT_YUY2:
		strcpy_s(chString, "D3DFMT_YUY2");
		break;
	case D3DFMT_G8R8_G8B8:
		strcpy_s(chString, "D3DFMT_G8R8_G8B8");
		break;
	case D3DFMT_DXT1:
		strcpy_s(chString, "D3DFMT_DXT1");
		break;
	case D3DFMT_DXT2:
		strcpy_s(chString, "D3DFMT_DXT2");
		break;
	case D3DFMT_DXT3:
		strcpy_s(chString, "D3DFMT_DXT3");
		break;
	case D3DFMT_DXT4:
		strcpy_s(chString, "D3DFMT_DXT4");
		break;
	case D3DFMT_DXT5:
		strcpy_s(chString, "D3DFMT_DXT5");
		break;
	case D3DFMT_D16_LOCKABLE:
		strcpy_s(chString, "D3DFMT_D16_LOCKABLE");
		break;
	case D3DFMT_D32:
		strcpy_s(chString, "D3DFMT_D32");
		break;
	case D3DFMT_D15S1:
		strcpy_s(chString, "D3DFMT_D15S1");
		break;
	case D3DFMT_D24S8:
		strcpy_s(chString, "D3DFMT_D24S8");
		break;
	case D3DFMT_D24X8:
		strcpy_s(chString, "D3DFMT_D24X8");
		break;
	case D3DFMT_D24X4S4:
		strcpy_s(chString, "D3DFMT_D24X4S4");
		break;
	case D3DFMT_D16:
		strcpy_s(chString, "D3DFMT_D16");
		break;
	case D3DFMT_D32F_LOCKABLE:
		strcpy_s(chString, "D3DFMT_D32F_LOCKABLE");
		break;
	case D3DFMT_D24FS8:
		strcpy_s(chString, "D3DFMT_D24FS8");
		break;
/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)
	case D3DFMT_D32_LOCKABLE:
		strcpy_s(chString, "D3DFMT_D32_LOCKABLE");
		break;
	case D3DFMT_S8_LOCKABLE:
		strcpy_s(chString, "D3DFMT_S8_LOCKABLE");
		break;
#endif // !D3D_DISABLE_9EX
	case D3DFMT_L16:
		strcpy_s(chString, "D3DFMT_L16");
		break;
	case D3DFMT_VERTEXDATA:
		strcpy_s(chString, "D3DFMT_VERTEXDATA");
		break;
	case D3DFMT_INDEX16:
		strcpy_s(chString, "D3DFMT_INDEX16");
		break;
	case D3DFMT_INDEX32:
		strcpy_s(chString, "D3DFMT_INDEX32");
		break;
	case D3DFMT_Q16W16V16U16:
		strcpy_s(chString, "D3DFMT_Q16W16V16U16");
		break;
	case D3DFMT_MULTI2_ARGB8:
		strcpy_s(chString, "D3DFMT_MULTI2_ARGB8");
		break;
	case D3DFMT_R16F:
		strcpy_s(chString, "D3DFMT_R16F");
		break;
	case D3DFMT_G16R16F:
		strcpy_s(chString, "D3DFMT_G16R16F");
		break;
	case D3DFMT_A16B16G16R16F:
		strcpy_s(chString, "D3DFMT_A16B16G16R16F");
		break;
	case D3DFMT_R32F:
		strcpy_s(chString, "D3DFMT_R32F");
		break;
	case D3DFMT_G32R32F:
		strcpy_s(chString, "D3DFMT_G32R32F");
		break;
	case D3DFMT_A32B32G32R32F:
		strcpy_s(chString, "D3DFMT_A32B32G32R32F");
		break;
	case D3DFMT_CxV8U8:
		strcpy_s(chString, "D3DFMT_CxV8U8");
		break;
		/* D3D9Ex only -- */
#if !defined(D3D_DISABLE_9EX)
	case D3DFMT_A1:
		strcpy_s(chString, "D3DFMT_A1");
		break;
	case D3DFMT_A2B10G10R10_XR_BIAS:
		strcpy_s(chString, "D3DFMT_A2B10G10R10_XR_BIAS");
		break;
	case D3DFMT_BINARYBUFFER:
		strcpy_s(chString, "D3DFMT_BINARYBUFFER");
		break;
#endif // !D3D_DISABLE_9EX

	case D3DFMT_FORCE_DWORD:
		strcpy_s(chString, "D3DFMT_FORCE_DWORD");
		break;
	default:
		strcpy_s(chString, "D3DFMT_UNKNOWN");
		break;
	}

	nSize = MultiByteToWideChar(CP_ACP, 0, chString, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, chString, -1, pString, nSize);
}