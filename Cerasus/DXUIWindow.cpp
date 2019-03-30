/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIWindow.cpp
* @brief	This File is DXUI Project File.
* @author	alopex
* @version	v1.00a
* @date		2019-03-13	v1.00a	alopex	Create Project.
*/
#include "DXUIWindow.h"
#include "DXUIManager.h"

// CDXUIWindow 窗口类(UI)

//------------------------------------------------------------------
// @Function:	 CDXUIWindow()
// @Purpose: CDXUIWindow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIWindow::CDXUIWindow() :
	m_hWnd(NULL),
	m_WndProc(::DefWindowProc),
	m_bSubClassed(false)
{
}

//------------------------------------------------------------------
// @Function:	 ~CDXUIWindow()
// @Purpose: CDXUIWindow析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIWindow::~CDXUIWindow()
{
}

//------------------------------------------------------------------
// @Function:	 GetHWND()
// @Purpose: CDXUIWindow获取窗口句柄
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::GetHWND() const
{
	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 RegisterWindowClass()
// @Purpose: CDXUIWindow注册窗口类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool DXUIWINDOW_CALLMETHOD CDXUIWindow::RegisterWindowClass(WORD wIcon)
{
	WNDCLASS wc = { 0 };

	wc.style = GetClassStyle();
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = CDXUIWindow::WndProc;
	wc.hInstance = CDXUIManager::GetInstance();
	wc.hIcon = LoadIcon(CDXUIManager::GetInstance(), MAKEINTRESOURCE(wIcon));
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(wIcon);
	wc.lpszClassName = GetWindowClassName();

	ATOM atom = ::RegisterClass(&wc);
	assert(atom != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);

	return atom != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

//------------------------------------------------------------------
// @Function:	 RegisterWindowClassEx()
// @Purpose: CDXUIWindow注册窗口类(Ex)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool DXUIWINDOW_CALLMETHOD CDXUIWindow::RegisterWindowClassEx(WORD wIcon)
{
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = GetClassStyle();
	wcex.lpfnWndProc = CDXUIWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = CDXUIManager::GetInstance();
	wcex.hIcon = LoadIcon(CDXUIManager::GetInstance(), MAKEINTRESOURCE(wIcon));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCE(wIcon);
	wcex.lpszClassName = GetWindowClassName();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(wIcon));

	ATOM atom = ::RegisterClassEx(&wcex);
	assert(atom != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);

	return (atom != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
}

//------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: CDXUIWindow创建窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, const RECT rc, HMENU hMenu, WORD wIcon)
{
	return Create(hWndParent, pstrName, dwStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu, wIcon);
}

//------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: CDXUIWindow创建窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::Create(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, int x, int y, int cx, int cy, HMENU hMenu, WORD wIcon)
{
	// Register Window Class
	if (GetWindowClassName() == NULL || !RegisterWindowClass(wIcon))
	{
		return NULL;
	}

	// Create Window...
	m_hWnd = CreateWindow(GetWindowClassName(), pstrName, dwStyle, x, y, cx, cy, hWndParent, hMenu, CDXUIManager::GetInstance(), this);
	assert(m_hWnd != NULL);

	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 CreateEx()
// @Purpose: CDXUIWindow创建窗口(Ex)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu, WORD wIcon)
{
	return CreateEx(hWndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu, wIcon);
}

//------------------------------------------------------------------
// @Function:	 CreateEx()
// @Purpose: CDXUIWindow创建窗口(Ex)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::CreateEx(HWND hWndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu, WORD wIcon)
{
	// Register Window Class Extra
	if (GetWindowClassNameEx() == NULL || !RegisterWindowClassEx(wIcon))
	{
		return NULL;
	}

	// Create Window Extra...
	m_hWnd = CreateWindowEx(dwExStyle, GetWindowClassNameEx(), pstrName, dwStyle, x, y, cx, cy, hWndParent, hMenu, CDXUIManager::GetInstance(), this);
	assert(m_hWnd != NULL);

	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 SubClass()
// @Purpose: CDXUIWindow注册子类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND DXUIWINDOW_CALLMETHOD CDXUIWindow::SubClass(HWND hWnd)
{
	assert(::IsWindow(hWnd));
	assert(m_hWnd == NULL);

	m_WndProc = SubclassWindow(hWnd, WndProc);
	if (m_WndProc == NULL)
	{
		return NULL;
	}

	m_bSubClassed = true;
	m_hWnd = hWnd;
	::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(this));

	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 UnSubClass()
// @Purpose: CDXUIWindow注销子类
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DXUIWINDOW_CALLMETHOD CDXUIWindow::UnSubClass()
{
	assert(::IsWindow(m_hWnd));

	if (!::IsWindow(m_hWnd))
	{
		return;
	}

	if (!m_bSubClassed)
	{
		return;
	}

	SubclassWindow(m_hWnd, m_WndProc);
	m_WndProc = ::DefWindowProc;
	m_bSubClassed = false;
}

//------------------------------------------------------------------
// @Function:	 ShowWindow()
// @Purpose: CDXUIWindow显示窗口(非模态)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DXUIWINDOW_CALLMETHOD CDXUIWindow::ShowWindow(bool bShow, bool bTakeFocus)
{
	assert(::IsWindow(m_hWnd));

	if (!::IsWindow(m_hWnd))
	{
		return;
	}

	::ShowWindow(m_hWnd, bShow ? (bTakeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

//------------------------------------------------------------------
// @Function:	 ShowModal()
// @Purpose: CDXUIWindow显示窗口(模态)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT DXUIWINDOW_CALLMETHOD CDXUIWindow::ShowModal()
{
	return 0;
}

//------------------------------------------------------------------
// @Function:	 GetWindowClassName()
// @Purpose: CDXUIWindow获取窗口类名
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPCTSTR DXUIWINDOW_CALLMETHOD CDXUIWindow::GetWindowClassName() const
{
	return NULL;
}

//------------------------------------------------------------------
// @Function:	 GetWindowClassNameEx()
// @Purpose: CDXUIWindow获取窗口类名(Ex)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPCTSTR DXUIWINDOW_CALLMETHOD CDXUIWindow::GetWindowClassNameEx() const
{
	return NULL;
}

//------------------------------------------------------------------
// @Function:	 GetClassStyle()
// @Purpose: CDXUIWindow获取窗口样式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT DXUIWINDOW_CALLMETHOD CDXUIWindow::GetClassStyle() const
{
	return 0;
}

//------------------------------------------------------------------
// @Function:	 HandleMessage()
// @Purpose: CDXUIWindow窗口消息处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT DXUIWINDOW_CALLMETHOD CDXUIWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProc(m_WndProc, m_hWnd, uMsg, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnFinalMessage()
// @Purpose: CDXUIWindow窗口销毁处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DXUIWINDOW_CALLMETHOD CDXUIWindow::OnFinalMessage(HWND hWnd)
{
	
}

//------------------------------------------------------------------
// @Function:	 WndProc()
// @Purpose: CDXUIWindow窗口类消息回调函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT DXUIWINDOW_CALLMETHOD CDXUIWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDXUIWindow* pWindow = NULL;

	if (uMsg == WM_NCCREATE)
	{
		// Create Window Message...
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pWindow = static_cast<CDXUIWindow*>(lpcs->lpCreateParams);
		pWindow->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pWindow));
	}
	else
	{
		pWindow = reinterpret_cast<CDXUIWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (uMsg == WM_NCDESTROY && pWindow != NULL)
		{
			// Destroy Window Message...
			LRESULT lRes = ::CallWindowProc(pWindow->m_WndProc, hWnd, uMsg, wParam, lParam);
			::SetWindowLongPtr(pWindow->m_hWnd, GWLP_USERDATA, 0L);
			if (pWindow->m_bSubClassed)
			{
				pWindow->UnSubClass();
			}
			pWindow->m_hWnd = NULL;
			pWindow->OnFinalMessage(hWnd);
			return lRes;
		}
	}

	if (pWindow != NULL)
	{
		return pWindow->HandleMessage(uMsg, wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

}
