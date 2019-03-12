/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics11.cpp
* @brief	This Program is DirectGraphics11 DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2019-03-12	v1.00a	alopex	Create Project.
*/
#include "DirectCommon.h"
#include "DirectGraphics11.h"
#include "DirectThreadSafe.h"

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
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit()
// @Purpose: DirectGraphics11 初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11::DirectGraphicsInit(HWND hWnd)
{
	RECT Rect = { 0 };
	UINT nWidth = 0;
	UINT nHeight = 0;

	GetClientRect(hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	return false;
}
