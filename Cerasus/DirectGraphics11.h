/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics11.h
* @brief	This Program is DirectGraphics11 DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2019-03-12	v1.00a	alopex	Create Project.
* @date		2019-03-13	v1.01a	alopex	Add Method.
*/
#pragma once

#ifndef __DIRECTGRAPHICS11_H_
#define __DIRECTGRAPHICS11_H_

// Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTGRAPHICS11_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS11_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS11_CALLMETHOD	__stdcall

// Class Definition
class DIRECTGRAPHICS11_API DirectGraphics11
{
private:
	ID3D11Device* m_pD3D11Device;						// Direct3D 11 Render Device(~D3D11设备对象)
	ID3D11DeviceContext* m_pD3D11Context;				// Direct3D 11 Render Context(~D3D11设备上下文)
	IDXGISwapChain* m_pD3D11SwapChain;					// Direct3D 11 Render Swap Chain(~D3D11渲染交换链)
	ID3D11RenderTargetView* m_pD3D11BackBufferTarget;	// Direct3D 11 Render Back Buffer Target(~D3D11后台缓冲)

	D3D_DRIVER_TYPE m_DriverType;						// Direct3D 11 Driver Type(~D3D11设备类型)
	D3D_FEATURE_LEVEL m_FeatureLevel;					// Direct3D 11 Feature Level(~D3D11特征等级)

	CRITICAL_SECTION m_cs;								// Direct3D 11 Thread Safe(CriticalSection)(~D3D11临界区变量)
	bool m_bThreadSafe;									// Direct3D 11 Thread Safe Status(~D3D11线程安全状态)

public:
	DirectGraphics11();									// DirectGraphics11 Constructor Function(~DirectGraphics11构造函数)
	~DirectGraphics11();								// DirectGraphics11 Destructor Function(~DirectGraphics11析构函数)

	virtual ID3D11Device*			DIRECTGRAPHICS11_CALLMETHOD	DirectGraphics11GetDevice() const;								// DirectGraphics11 Get Device(~DirectGraphics11获取设备对象)
	virtual ID3D11DeviceContext*	DIRECTGRAPHICS11_CALLMETHOD	DirectGraphics11GetContext() const;								// DirectGraphics11 Get Context(~DirectGraphics11获取设备上下文)
	virtual IDXGISwapChain*			DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11GetSwapChain() const;							// DirectGraphics11 Get Swap Chain(~DirectGraphics11获取交换链)
	virtual ID3D11RenderTargetView*	DIRECTGRAPHICS11_CALLMETHOD DirectGraphics11GetRenderTargetView() const;					// DirectGraphics11 Get Render Target View(~DirectGraphics11获取渲染视口目标)

	virtual bool	DIRECTGRAPHICS11_CALLMETHOD	DirectGraphics11Init(HWND hWnd);												// DirectGraphics11 Init(~DirectGraphics11初始化)
	virtual bool	DIRECTGRAPHICS11_CALLMETHOD	DirectGraphics11Init(HWND hWnd, UINT nScreenWidth, UINT nScreenHeight);			// DirectGraphics11 Init(~DirectGraphics11初始化)(重载+1)
	virtual bool	DIRECTGRAPHICS11_CALLMETHOD	DirectGraphics11Init(HWND hWnd, DXGI_SWAP_CHAIN_DESC swapChainDesc);			// DirectGraphics11 Init(~DirectGraphics11初始化)(重载+2)

};

#endif // !__DIRECTGRAPHICS11_H_

