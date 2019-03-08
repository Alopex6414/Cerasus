/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXUIBase.cpp
* @brief	This File is DXUI Project Source File.
* @author	alopex
* @version	v1.00a
* @date		2019-02-15	v1.00a	alopex	Create Project.
*/
#include "DXUIBase.h"
#include "DXUIManager.h"

// CDXUIWindow 窗口基类

//------------------------------------------------------------------
// @Function:	 CDXUIWindow()
// @Purpose: CDXUIWindow构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIWindow::CDXUIWindow() :
	m_hWnd(NULL),
	m_OldWndProc(::DefWindowProc),
	m_bSubclassed(false)
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
HWND CDXUIWindow::GetHWND() const
{
	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 operator HWND()
// @Purpose: CDXUIWindow获取窗口句柄
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIWindow::operator HWND() const
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
bool CDXUIWindow::RegisterWindowClass()
{
	WNDCLASS wc = { 0 };
	wc.style = GetClassStyle();
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.lpfnWndProc = CDXUIWindow::__WndProc;
	wc.hInstance = CDXUIPaintManagerUI::GetInstance();
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GetWindowClassName();
	ATOM ret = ::RegisterClass(&wc);
	ASSERT(ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

//------------------------------------------------------------------
// @Function:	 RegisterSuperclass()
// @Purpose: CDXUIWindow注册窗口类Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CDXUIWindow::RegisterSuperclass()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	if (!::GetClassInfoEx(NULL, GetSuperClassName(), &wc))
	{
		if (!::GetClassInfoEx(CDXUIPaintManagerUI::GetInstance(), GetSuperClassName(), &wc))
		{
			ASSERT(!"Unable to locate window class");
			return NULL;
		}
	}
	m_OldWndProc = wc.lpfnWndProc;
	wc.lpfnWndProc = CDXUIWindow::__ControlProc;
	wc.hInstance = CDXUIPaintManagerUI::GetInstance();
	wc.lpszClassName = GetWindowClassName();
	ATOM ret = ::RegisterClassEx(&wc);
	ASSERT(ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

//------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: CDXUIWindow创建窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND CDXUIWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu)
{
	return Create(hwndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu);
}

//------------------------------------------------------------------
// @Function:	 Create()
// @Purpose: CDXUIWindow创建窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND CDXUIWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu)
{
	if (GetSuperClassName() != NULL && !RegisterSuperclass())
	{
		return NULL;
	}

	if (GetSuperClassName() == NULL && !RegisterWindowClass())
	{
		return NULL;
	}

	m_hWnd = ::CreateWindowEx(dwExStyle, GetWindowClassName(), pstrName, dwStyle, x, y, cx, cy, hwndParent, hMenu, CDXUIPaintManagerUI::GetInstance(), this);
	ASSERT(m_hWnd != NULL);

	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 CreateDXUIWindow()
// @Purpose: CDXUIWindow创建窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND CDXUIWindow::CreateDXUIWindow(HWND hwndParent, LPCTSTR pstrWindowName, DWORD dwStyle, DWORD dwExStyle)
{
	return Create(hwndParent, pstrWindowName, dwStyle, dwExStyle, 0, 0, 0, 0, NULL);
}

//------------------------------------------------------------------
// @Function:	 Subclass()
// @Purpose: CDXUIWindow创建子窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HWND CDXUIWindow::Subclass(HWND hWnd)
{
	ASSERT(::IsWindow(hWnd));
	ASSERT(m_hWnd == NULL);

	m_OldWndProc = SubclassWindow(hWnd, __WndProc);

	if (m_OldWndProc == NULL)
	{
		return NULL;
	}

	m_bSubclassed = true;
	m_hWnd = hWnd;
	::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(this));

	return m_hWnd;
}

//------------------------------------------------------------------
// @Function:	 GetSuperClassName()
// @Purpose: CDXUIWindow获取窗口类名Ex
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPCTSTR CDXUIWindow::GetSuperClassName() const
{
	return NULL;
}

//------------------------------------------------------------------
// @Function:	 GetClassStyle()
// @Purpose: CDXUIWindow获取窗口类型
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
UINT CDXUIWindow::GetClassStyle() const
{
	return 0;
}

//------------------------------------------------------------------
// @Function:	 HandleMessage()
// @Purpose: CDXUIWindow消息处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProc(m_OldWndProc, m_hWnd, uMsg, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnFinalMessage()
// @Purpose: CDXUIWindow消息结束函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CDXUIWindow::OnFinalMessage(HWND hWnd)
{
}

//------------------------------------------------------------------
// @Function:	 __WndProc()
// @Purpose: CDXUIWindow窗口处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDXUIWindow* pThis = NULL;
	if (uMsg == WM_NCCREATE) 
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<CDXUIWindow*>(lpcs->lpCreateParams);
		pThis->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	}
	else 
	{
		pThis = reinterpret_cast<CDXUIWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (uMsg == WM_NCDESTROY && pThis != NULL) 
		{
			LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
			::SetWindowLongPtr(pThis->m_hWnd, GWLP_USERDATA, 0L);

			if (pThis->m_bSubclassed)
			{
				pThis->Unsubclass();
			}

			pThis->m_hWnd = NULL;
			pThis->OnFinalMessage(hWnd);
			return lRes;
		}
	}

	if (pThis != NULL) 
	{
		return pThis->HandleMessage(uMsg, wParam, lParam);
	}
	else 
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

//------------------------------------------------------------------
// @Function:	 __ControlProc()
// @Purpose: CDXUIWindow控件处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::__ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDXUIWindow* pThis = NULL;
	if (uMsg == WM_NCCREATE) 
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<CDXUIWindow*>(lpcs->lpCreateParams);
		::SetProp(hWnd, _T("WndX"), (HANDLE)pThis);
		pThis->m_hWnd = hWnd;
	}
	else 
	{
		pThis = reinterpret_cast<CDXUIWindow*>(::GetProp(hWnd, _T("WndX")));
		if (uMsg == WM_NCDESTROY && pThis != NULL) {
			LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
			
			if (pThis->m_bSubclassed)
			{
				pThis->Unsubclass();
			}

			::SetProp(hWnd, _T("WndX"), NULL);
			pThis->m_hWnd = NULL;
			pThis->OnFinalMessage(hWnd);
			return lRes;
		}
	}

	if (pThis != NULL) 
	{
		return pThis->HandleMessage(uMsg, wParam, lParam);
	}
	else 
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
