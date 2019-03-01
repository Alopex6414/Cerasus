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

// CDXUIWindow ���ڻ���

//------------------------------------------------------------------
// @Function:	 CDXUIWindow()
// @Purpose: CDXUIWindow���캯��
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
// @Purpose: CDXUIWindow��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CDXUIWindow::~CDXUIWindow()
{
}

//------------------------------------------------------------------
// @Function:	 GetHWND()
// @Purpose: CDXUIWindow��ȡ���ھ��
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
// @Purpose: CDXUIWindow��ȡ���ھ��
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
// @Purpose: CDXUIWindowע�ᴰ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CDXUIWindow::RegisterWindowClass()
{
	return false;
}

//------------------------------------------------------------------
// @Function:	 GetSuperClassName()
// @Purpose: CDXUIWindow��ȡ��������Ex
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
// @Purpose: CDXUIWindow��ȡ��������
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
// @Purpose: CDXUIWindow��Ϣ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

//------------------------------------------------------------------
// @Function:	 OnFinalMessage()
// @Purpose: CDXUIWindow��Ϣ��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CDXUIWindow::OnFinalMessage(HWND hWnd)
{
}

//------------------------------------------------------------------
// @Function:	 __WndProc()
// @Purpose: CDXUIWindow���ڴ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

//------------------------------------------------------------------
// @Function:	 __ControlProc()
// @Purpose: CDXUIWindow�ؼ�������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CDXUIWindow::__ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}
