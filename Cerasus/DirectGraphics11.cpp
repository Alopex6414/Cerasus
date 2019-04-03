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

// DirectX11 Graphics Class(DirectX11 绘制类)

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 构造函数
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
	m_bThreadSafe = true;									// DirectGraphics11 线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 初始化临界区
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics11()
// @Purpose: DirectGraphics11 析构函数
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

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// DirectGraphics11 删除临界区
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 构造函数
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
	m_bThreadSafe = bSafe;									// DirectGraphics11 线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 初始化临界区
}

//------------------------------------------------------------------
// @Function:	 DirectGraphics11()
// @Purpose: DirectGraphics11 拷贝构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics11::DirectGraphics11(const DirectGraphics11 & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// DirectGraphics11 线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 初始化临界区

	m_pD3D11Device = Object.m_pD3D11Device;
	m_pD3D11Context = Object.m_pD3D11Context;
	m_pD3D11SwapChain = Object.m_pD3D11SwapChain;
	m_pD3D11BackBufferTarget = Object.m_pD3D11BackBufferTarget;
	m_DriverType = Object.m_DriverType;
	m_FeatureLevel = Object.m_FeatureLevel;
}

//------------------------------------------------------------------
// @Function:	 operator=()
// @Purpose: DirectGraphics11 重载运算符
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectGraphics11 & DirectGraphics11::operator=(const DirectGraphics11 & Object)
{
	if (&Object == this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// DirectGraphics11 线程安全
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// DirectGraphics11 初始化临界区

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
// @Purpose: DirectGraphics11 获取D3D11设备对象
// @Since: v1.00a
// @Para: None
// @Return: ID3D11Device*(D3D11设备对象指针)
//------------------------------------------------------------------
ID3D11Device *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetDevice() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11Device;
}

//------------------------------------------------------------------
// @Function:	 GetContext()
// @Purpose: DirectGraphics11 获取D3D11设备上下文
// @Since: v1.00a
// @Para: None
// @Return: ID3D11DeviceContext*(D3D11设备上下文指针)
//------------------------------------------------------------------
ID3D11DeviceContext *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetContext() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11Context;
}

//------------------------------------------------------------------
// @Function:	 GetSwapChain()
// @Purpose: DirectGraphics11 获取D3D11交换链
// @Since: v1.00a
// @Para: None
// @Return: IDXGISwapChain*(D3D11交换链指针)
//------------------------------------------------------------------
IDXGISwapChain *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetSwapChain() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11SwapChain;
}

//------------------------------------------------------------------
// @Function:	 GetRenderTargetView()
// @Purpose: DirectGraphics11 获取D3D11渲染视口目标
// @Since: v1.00a
// @Para: None
// @Return: ID3D11RenderTargetView*(D3D11渲染视口目标)
//------------------------------------------------------------------
ID3D11RenderTargetView *DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::GetRenderTargetView() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D11BackBufferTarget;
}

//------------------------------------------------------------------
// @Function:	 Create(HWND hWnd)
// @Purpose: DirectGraphics11 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: bool(false:失败/true:成功)
//------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect = { 0 };
	UINT nWidth = 0;
	UINT nHeight = 0;

	// D3D11 获取渲染窗口大小
	GetClientRect(hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	// D3D11 设备类型枚举
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// 硬件设备(0)
		D3D_DRIVER_TYPE_WARP,		// WARP设备(1)
		D3D_DRIVER_TYPE_REFERENCE,	// 参考设备(2)
		D3D_DRIVER_TYPE_SOFTWARE	// 软件设备(3)
	};

	// D3D11 特征等级枚举
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 交换链结构体填充
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11后台缓冲数量(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11后台缓冲表面宽度(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11后台缓冲表面高度(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11后台缓冲像素格式
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11刷新频率分母(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11刷新频率分子
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11渲染输出目标
	swapChainDesc.OutputWindow = hWnd;								// D3D11渲染窗口句柄
	swapChainDesc.Windowed = true;									// D3D11窗口模式:true/全屏模式:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11采样区域数量
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11采样区域质量

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 创建设备和交换链
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

	// D3D11 创建目标渲染视图
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
// @Purpose: DirectGraphics11 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: UINT nScreenWidth(窗口宽度)
// @Para: UINT nScreenHeight(窗口高度)
// @Return: bool(false:失败/true:成功)
//------------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd, UINT nScreenWidth, UINT nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	UINT nWidth = nScreenWidth;
	UINT nHeight = nScreenHeight;

	// D3D11 设备类型枚举
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// 硬件设备(0)
		D3D_DRIVER_TYPE_WARP,		// WARP设备(1)
		D3D_DRIVER_TYPE_REFERENCE,	// 参考设备(2)
		D3D_DRIVER_TYPE_SOFTWARE	// 软件设备(3)
	};

	// D3D11 特征等级枚举
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 交换链结构体填充
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11后台缓冲数量(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11后台缓冲表面宽度(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11后台缓冲表面高度(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11后台缓冲像素格式
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11刷新频率分母(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11刷新频率分子
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11渲染输出目标
	swapChainDesc.OutputWindow = hWnd;								// D3D11渲染窗口句柄
	swapChainDesc.Windowed = true;									// D3D11窗口模式:true/全屏模式:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11采样区域数量
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11采样区域质量

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 创建设备和交换链
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

	// D3D11 创建目标渲染视图
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
// @Purpose: DirectGraphics11 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: DXGI_SWAP_CHAIN_DESC swapChainDesc(交换链结构)
// @Return: bool(false:失败/true:成功)
//---------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::Create(HWND hWnd, DXGI_SWAP_CHAIN_DESC swapChainDesc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect = { 0 };
	UINT nWidth = 0;
	UINT nHeight = 0;

	// D3D11 获取渲染窗口大小
	GetClientRect(hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	// D3D11 设备类型枚举
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// 硬件设备(0)
		D3D_DRIVER_TYPE_WARP,		// WARP设备(1)
		D3D_DRIVER_TYPE_REFERENCE,	// 参考设备(2)
		D3D_DRIVER_TYPE_SOFTWARE	// 软件设备(3)
	};

	// D3D11 特征等级枚举
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT totalDriverTypes = ARRAYSIZE(driverTypes);
	UINT totalFeatureLevels = ARRAYSIZE(featureLevels);

	// D3D11 交换链结构体填充
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;									// D3D11后台缓冲数量(1)
	swapChainDesc.BufferDesc.Width = nWidth;						// D3D11后台缓冲表面宽度(Pixel)
	swapChainDesc.BufferDesc.Height = nHeight;						// D3D11后台缓冲表面高度(Pixel)
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// D3D11后台缓冲像素格式
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;			// D3D11刷新频率分母(60fps)
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;			// D3D11刷新频率分子
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// D3D11渲染输出目标
	swapChainDesc.OutputWindow = hWnd;								// D3D11渲染窗口句柄
	swapChainDesc.Windowed = true;									// D3D11窗口模式:true/全屏模式:false
	swapChainDesc.SampleDesc.Count = 1;								// D3D11采样区域数量
	swapChainDesc.SampleDesc.Quality = 0;							// D3D11采样区域质量

	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr;
	UINT driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		// D3D11 创建设备和交换链
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

	// D3D11 创建目标渲染视图
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
// @Purpose: DirectGraphics11 渲染
// @Since: v1.00a
// @Para: None
// @Return: bool(false:失败/true:成功)
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
// @Purpose: DirectGraphics11 渲染
// @Since: v1.00a
// @Para: const float ClearColor[4](清屏背景色RGBA)
// @Return: bool(false:失败/true:成功)
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
