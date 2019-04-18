/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectGraphics11.h
* @brief	This Program is DirectGraphics11 DLL Project.
* @author	Alopex/Alice
* @version	v1.02a
* @date		2019-03-12	v1.00a	alopex	Create Project.
* @date		2019-03-13	v1.01a	alopex	Add Method.
* @date		2019-04-03	v1.02a	alopex	Add Notes.
*/
#pragma once

#ifndef __DIRECTGRAPHICS11_H_
#define __DIRECTGRAPHICS11_H_

// Include DirectX Common Header File
#include "DirectCommon.h"

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

protected:
	CRITICAL_SECTION m_cs;								// Direct3D 11 Thread Safe(CriticalSection)(~D3D11临界区变量)
	bool m_bThreadSafe;									// Direct3D 11 Thread Safe Status(~D3D11线程安全状态)

public:
	DirectGraphics11();									// DirectGraphics11 Construction Function(~DirectGraphics11构造函数)
	~DirectGraphics11();								// DirectGraphics11 Destruction Function(~DirectGraphics11析构函数)

	DirectGraphics11(bool bSafe);						// DirectGraphics11 Construction Function(~DirectGraphics11构造函数)(线程安全)(Overload + 1)
	DirectGraphics11(const DirectGraphics11&);			// DirectGraphics11 Construction Function(~DirectGraphics11拷贝构造函数)

public:
	const DirectGraphics11& operator=(const DirectGraphics11&);																			// DirectGraphics11 Overload(~DirectGraphics11重载运算符'=')

public:
	ID3D11Device*					DIRECTGRAPHICS11_CALLMETHOD		GetDevice() const;													// DirectGraphics11 Get Device(~DirectGraphics11获取设备对象)
	ID3D11DeviceContext*			DIRECTGRAPHICS11_CALLMETHOD		GetContext() const;													// DirectGraphics11 Get Context(~DirectGraphics11获取设备上下文)
	IDXGISwapChain*					DIRECTGRAPHICS11_CALLMETHOD		GetSwapChain() const;												// DirectGraphics11 Get Swap Chain(~DirectGraphics11获取交换链)
	ID3D11RenderTargetView*			DIRECTGRAPHICS11_CALLMETHOD		GetRenderTargetView() const;										// DirectGraphics11 Get Render Target View(~DirectGraphics11获取渲染视口目标)

public:
	bool							DIRECTGRAPHICS11_CALLMETHOD		Create(HWND hWnd);													// DirectGraphics11 Init(~DirectGraphics11初始化)
	bool							DIRECTGRAPHICS11_CALLMETHOD		Create(HWND hWnd, UINT nScreenWidth, UINT nScreenHeight);			// DirectGraphics11 Init(~DirectGraphics11初始化)(Overload + 1)
	bool							DIRECTGRAPHICS11_CALLMETHOD		Create(HWND hWnd, DXGI_SWAP_CHAIN_DESC swapChainDesc);				// DirectGraphics11 Init(~DirectGraphics11初始化)(Overload + 2)

	bool							DIRECTGRAPHICS11_CALLMETHOD		Render();															// DirectGraphics11 Render(~DirectGraphics11开始渲染)(黑色)
	bool							DIRECTGRAPHICS11_CALLMETHOD		Render(const float ClearColor[4]);									// DirectGraphics11 Render(~DirectGraphics11开始渲染)(Overload + 1)

};

#endif // !__DIRECTGRAPHICS11_H_

