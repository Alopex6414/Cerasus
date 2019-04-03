/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectGraphics11.cpp
* @brief	This Program is DirectGraphics11 DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2019-03-12	v1.00a	alopex	Create Project.
* @date		2019-03-13	v1.01a	alopex	Add Method.
* @date		2019-04-03	v1.02a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectGraphics11.h"
#include "DirectThreadSafe.h"

// DirectX11 Graphics Class(DirectX11 ������)

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 ���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics11::DirectGraphics11() :
	m_pD3D11Device(NULL),
	m_pD3D11Context(NULL),
	m_pD3D11SwapChain(NULL),
	m_pD3D11BackBufferTarget(NULL),
	m_DriverType(D3D_DRIVER_TYPE_NULL),
	m_FeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
	m_bThreadSafe = true;									// DirectGraphics11 �̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 ��ʼ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics11()
// @Purpose: DirectGraphics11 ��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics11::~DirectGraphics11()
{
	SAFE_RELEASE(m_pD3D11BackBufferTarget);
	SAFE_RELEASE(m_pD3D11SwapChain);
	SAFE_RELEASE(m_pD3D11Context);
	SAFE_RELEASE(m_pD3D11Device);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// DirectGraphics11 ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 ���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics11::DirectGraphics11(bool bSafe) :
	m_pD3D11Device(NULL),
	m_pD3D11Context(NULL),
	m_pD3D11SwapChain(NULL),
	m_pD3D11BackBufferTarget(NULL),
	m_DriverType(D3D_DRIVER_TYPE_NULL),
	m_FeatureLevel(D3D_FEATURE_LEVEL_11_0)
{
	m_bThreadSafe = bSafe;									// DirectGraphics11 �̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 ��ʼ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 �������캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics11::DirectGraphics11(const DirectGraphics11 & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// DirectGraphics11 �̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 ��ʼ���ٽ���

	m_pD3D11Device = Object.m_pD3D11Device;
	m_pD3D11Context = Object.m_pD3D11Context;
	m_pD3D11SwapChain = Object.m_pD3D11SwapChain;
	m_pD3D11BackBufferTarget = Object.m_pD3D11BackBufferTarget;
	m_DriverType = Object.m_DriverType;
	m_FeatureLevel = Object.m_FeatureLevel;
}

//------------------------------------------------------------------
// @Function:	 operator=()
// @Purpose: DirectGraphics11 ���������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectGraphics11 & DirectGraphics11::operator=(const DirectGraphics11 & Object)
{
	if (&Object == this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// DirectGraphics11 �̰߳�ȫ
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 ��ʼ���ٽ���

		m_pD3D11Device = Object.m_pD3D11Device;
		m_pD3D11Context = Object.m_pD3D11Context;
		m_pD3D11SwapChain = Object.m_pD3D11SwapChain;
		m_pD3D11BackBufferTarget = Object.m_pD3D11BackBufferTarget;
		m_DriverType = Object.m_DriverType;
		m_FeatureLevel = Object.m_FeatureLevel;
	}

	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: DirectGraphics11 ��ȡD3D11�豸����
// @Since: v1.00a
// @Para: None
// @Return: ID3D11Device*(D3D11�豸����ָ��)
//------------------------------------------------------------------
ID3D11Device *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11Device;
}

//------------------------------------------------------------------
// @Function:	 GetContext()
// @Purpose: DirectGraphics11 ��ȡD3D11�豸������
// @Since: v1.00a
// @Para: None
// @Return: ID3D11DeviceContext*(D3D11�豸������ָ��)
//------------------------------------------------------------------
ID3D11DeviceContext *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetContext() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11Context;
}

//------------------------------------------------------------------
// @Function:	 GetSwapChain()
// @Purpose: DirectGraphics11 ��ȡD3D11������
// @Since: v1.00a
// @Para: None
// @Return: IDXGISwapChain*(D3D11������ָ��)
//------------------------------------------------------------------
IDXGISwapChain *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetSwapChain() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11SwapChain;
}

//------------------------------------------------------------------
// @Function:	 GetRenderTargetView()
// @Purpose: DirectGraphics11 ��ȡD3D11��Ⱦ�ӿ�Ŀ��
// @Since: v1.00a
// @Para: None
// @Return: ID3D11RenderTargetView*(D3D11��Ⱦ�ӿ�Ŀ��)
//------------------------------------------------------------------
ID3D11RenderTargetView *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetRenderTargetView() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11BackBufferTarget;
}

//------------------------------------------------------------------
// @Function:	 Create(HWND hWnd)
// @Purpose: DirectGraphics11 ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: bool(false:ʧ��/true:�ɹ�)
//------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect = { 0 };
	UINT nWidth = 0;
	UINT nHeight = 0;

	// D3D11 ��ȡ��Ⱦ���ڴ�С
	GetClientRect(hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	// D3D11 �豸����ö��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// Ӳ���豸(0)
		D3D_DRIVER_TYPE_WARP,		// WARP�豸(1)
		D3D_DRIVER_TYPE_REFERENCE,	// �ο��豸(2)
		D3D_DRIVER_TYPE_SOFTWARE	// ����豸(3)
	};

	// D3D11 �����ȼ�ö��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 �������ṹ�����
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11��̨��������(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11��̨���������(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11��̨�������߶�(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11��̨�������ظ�ʽ
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11ˢ��Ƶ�ʷ�ĸ(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11ˢ��Ƶ�ʷ���
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11��Ⱦ���Ŀ��
	swapChainDesc.OutputWindow = hWnd;								// D3D11��Ⱦ���ھ��
	swapChainDesc.Windowed = true;									// D3D11����ģʽ:true/ȫ��ģʽ:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11������������
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11������������

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 �����豸�ͽ�����
		hr = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_pD3D11SwapChain, &m_pD3D11Device, &m_FeatureLevel, &m_pD3D11Context);
		if (SUCCEEDED(hr))
		{
			m_DriverType = driverTypes[driver];
			break;
		}
	}

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Device And SwapChain Failed!");
		return false;
	}

	// D3D11 ����Ŀ����Ⱦ��ͼ
	ID3D11Texture2D* backBufferTexture = NULL;

	hr = m_pD3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 SwapChain Get Buffer Failed!");
		return false;
	}

	hr = m_pD3D11Device->CreateRenderTargetView(backBufferTexture, 0, &m_pD3D11BackBufferTarget);

	SAFE_RELEASE(backBufferTexture);

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Target View Failed!");
		return false;
	}

	m_pD3D11Context->OMSetRenderTargets(1, &m_pD3D11BackBufferTarget, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(nWidth);
	viewport.Height = static_cast<float>(nHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pD3D11Context->RSSetViewports(1, &viewport);

	return true;
}

//-----------------------------------------------------------------------
// @Function:	 Create(HWND hWnd, UINT nScreenWidth, UINT nScreenHeight)
// @Purpose: DirectGraphics11 ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: UINT nScreenWidth(���ڿ��)
// @Para: UINT nScreenHeight(���ڸ߶�)
// @Return: bool(false:ʧ��/true:�ɹ�)
//------------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd, UINT nScreenWidth, UINT nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	UINT nWidth = nScreenWidth;
	UINT nHeight = nScreenHeight;

	// D3D11 �豸����ö��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// Ӳ���豸(0)
		D3D_DRIVER_TYPE_WARP,		// WARP�豸(1)
		D3D_DRIVER_TYPE_REFERENCE,	// �ο��豸(2)
		D3D_DRIVER_TYPE_SOFTWARE	// ����豸(3)
	};

	// D3D11 �����ȼ�ö��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 �������ṹ�����
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11��̨��������(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11��̨���������(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11��̨�������߶�(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11��̨�������ظ�ʽ
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11ˢ��Ƶ�ʷ�ĸ(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11ˢ��Ƶ�ʷ���
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11��Ⱦ���Ŀ��
	swapChainDesc.OutputWindow = hWnd;								// D3D11��Ⱦ���ھ��
	swapChainDesc.Windowed = true;									// D3D11����ģʽ:true/ȫ��ģʽ:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11������������
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11������������

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 �����豸�ͽ�����
		hr = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_pD3D11SwapChain, &m_pD3D11Device, &m_FeatureLevel, &m_pD3D11Context);
		if (SUCCEEDED(hr))
		{
			m_DriverType = driverTypes[driver];
			break;
		}
	}

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Device And SwapChain Failed!");
		return false;
	}

	// D3D11 ����Ŀ����Ⱦ��ͼ
	ID3D11Texture2D* backBufferTexture = NULL;

	hr = m_pD3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 SwapChain Get Buffer Failed!");
		return false;
	}

	hr = m_pD3D11Device->CreateRenderTargetView(backBufferTexture, 0, &m_pD3D11BackBufferTarget);

	SAFE_RELEASE(backBufferTexture);

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Target View Failed!");
		return false;
	}

	m_pD3D11Context->OMSetRenderTargets(1, &m_pD3D11BackBufferTarget, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(nWidth);
	viewport.Height = static_cast<float>(nHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pD3D11Context->RSSetViewports(1, &viewport);

	return true;
}

//---------------------------------------------------------------------
// @Function:	 Create(HWND hWnd, DXGI_SWAP_CHAIN_DESC swapChainDesc)
// @Purpose: DirectGraphics11 ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: DXGI_SWAP_CHAIN_DESC swapChainDesc(�������ṹ)
// @Return: bool(false:ʧ��/true:�ɹ�)
//---------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd, DXGI_SWAP_CHAIN_DESC swapChainDesc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect = { 0 };
	UINT nWidth = 0;
	UINT nHeight = 0;

	// D3D11 ��ȡ��Ⱦ���ڴ�С
	GetClientRect(hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	// D3D11 �豸����ö��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// Ӳ���豸(0)
		D3D_DRIVER_TYPE_WARP,		// WARP�豸(1)
		D3D_DRIVER_TYPE_REFERENCE,	// �ο��豸(2)
		D3D_DRIVER_TYPE_SOFTWARE	// ����豸(3)
	};

	// D3D11 �����ȼ�ö��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 �������ṹ�����
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11��̨��������(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11��̨���������(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11��̨�������߶�(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11��̨�������ظ�ʽ
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11ˢ��Ƶ�ʷ�ĸ(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11ˢ��Ƶ�ʷ���
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11��Ⱦ���Ŀ��
	swapChainDesc.OutputWindow = hWnd;								// D3D11��Ⱦ���ھ��
	swapChainDesc.Windowed = true;									// D3D11����ģʽ:true/ȫ��ģʽ:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11������������
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11������������

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 �����豸�ͽ�����
		hr = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_pD3D11SwapChain, &m_pD3D11Device, &m_FeatureLevel, &m_pD3D11Context);
		if (SUCCEEDED(hr))
		{
			m_DriverType = driverTypes[driver];
			break;
		}
	}

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Device And SwapChain Failed!");
		return false;
	}

	// D3D11 ����Ŀ����Ⱦ��ͼ
	ID3D11Texture2D* backBufferTexture = NULL;

	hr = m_pD3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 SwapChain Get Buffer Failed!");
		return false;
	}

	hr = m_pD3D11Device->CreateRenderTargetView(backBufferTexture, 0, &m_pD3D11BackBufferTarget);

	SAFE_RELEASE(backBufferTexture);

	if (FAILED(hr))
	{
		DXTRACE_MSG("D3D11 Create Target View Failed!");
		return false;
	}

	m_pD3D11Context->OMSetRenderTargets(1, &m_pD3D11BackBufferTarget, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(nWidth);
	viewport.Height = static_cast<float>(nHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_pD3D11Context->RSSetViewports(1, &viewport);

	return true;
}

//------------------------------------------------------------------
// @Function:	 Render()
// @Purpose: DirectGraphics11 ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: bool(false:ʧ��/true:�ɹ�)
//------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Render()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	if (m_pD3D11Context == NULL)
	{
		return false;
	}

	m_pD3D11Context->ClearRenderTargetView(m_pD3D11BackBufferTarget, ClearColor);
	m_pD3D11SwapChain->Present(0, 0);

	return true;
}

//------------------------------------------------------------------
// @Function:	 Render(const float ClearColor[4])
// @Purpose: DirectGraphics11 ��Ⱦ
// @Since: v1.00a
// @Para: const float ClearColor[4](��������ɫRGBA)
// @Return: bool(false:ʧ��/true:�ɹ�)
//------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Render(const float ClearColor[4])
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_pD3D11Context == NULL)
	{
		return false;
	}

	m_pD3D11Context->ClearRenderTargetView(m_pD3D11BackBufferTarget, ClearColor);
	m_pD3D11SwapChain->Present(0, 0);

	return true;
}
