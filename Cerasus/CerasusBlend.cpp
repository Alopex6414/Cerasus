/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		CerasusBlend.cpp
* @brief	This File is CerasusBlend DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-19	v1.00a	alopex	Create Project.
*/
#include "CerasusBlend.h"

// CreasusUI ��Ⱦ��Ԫ(UI)

//------------------------------------------------------------------
// @Function:	 CCerasusBlendTex()
// @Purpose: CCerasusBlendTex���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendTex::CCerasusBlendTex(IDirect3DDevice9* pD3D9Device)
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_pTexStates[i] = new CCerasusUnit(pD3D9Device);
		memset(&m_sUnitArr[i], 0, sizeof(CUUint));
		memset(&m_sUnitExArr[i], 0, sizeof(CUUintEx));
	}

	m_pTexCurrent = m_pTexStates[CERASUS_STATE_NORMAL];
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusBlendTex()
// @Purpose: CCerasusBlendTex��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendTex::~CCerasusBlendTex()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_pTexStates[i]);
	}

	m_pTexCurrent = NULL;
}

//------------------------------------------------------------------
// @Function:	 SetUnit()
// @Purpose: CCerasusBlendTex�����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::SetUnit(UINT nState, CUUint sUnit)
{
	memcpy_s(&m_sUnitArr[nState], sizeof(CUUint), &sUnit, sizeof(CUUint));
}

//------------------------------------------------------------------
// @Function:	 SetUnitEx()
// @Purpose: CCerasusBlendTex�����������(Ex)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::SetUnitEx(UINT nState, CUUintEx sUnit)
{
	memcpy_s(&m_sUnitExArr[nState], sizeof(CUUintEx), &sUnit, sizeof(CUUintEx));
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusBlendTex��ʼ���ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::Init()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_pTexStates[i]->CCerasusUnitInit(m_sUnitArr[i]);
	}

}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusBlendTex��ʼ���ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::InitEx()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_pTexStates[i]->CCerasusUnitInit(m_sUnitExArr[i]);
	}

}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CCerasusBlendTex��Ⱦ�ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::Blend(UINT nState)
{
	m_pTexCurrent = m_pTexStates[nState];

	m_pTexCurrent->CCerasusUnitPaddingVertexAndIndex();		// ��仺��
	m_pTexCurrent->CCerasusUnitMatrixTransform();			// ����任
	m_pTexCurrent->CCerasusUnitSetAlphaBlendEnable();		// ����Alpha����
	m_pTexCurrent->CCerasusUnitSetRenderState();			// ������Ⱦ״̬
	m_pTexCurrent->CCerasusUnitRender();					// ��Ⱦͼ��
	m_pTexCurrent->CCerasusUnitSetAlphaBlendDisable();		// �ر�Alpha����
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CCerasusBlendTexˢ�¿ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendTex::Refresh()
{
	m_pTexCurrent = m_pTexStates[CERASUS_STATE_HIDDEN];
}

//------------------------------------------------------------------
// @Function:	 CCerasusBlendFont()
// @Purpose: CCerasusBlendFont���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendFont::CCerasusBlendFont(IDirect3DDevice9* pD3D9Device)
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_pFontStates[i] = new DirectFont(pD3D9Device);
	}

	m_nFontSize = 12;
	m_lpszFontType = (LPWSTR)_T("Consolas");
	m_hWnd = NULL;
	m_lpcszStr = _T("");
	m_dwFormat = DT_CENTER | DT_VCENTER;
	m_dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_pFontCurrent = m_pFontStates[CERASUS_STATE_NORMAL];
}

//------------------------------------------------------------------
// @Function:	 ~CCerasusBlendFont()
// @Purpose: CCerasusBlendFont��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusBlendFont::~CCerasusBlendFont()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_pFontStates[i]);
	}

	m_pFontCurrent = NULL;
}

//------------------------------------------------------------------
// @Function:	 SetFontProperty()
// @Purpose: CCerasusBlendFont������������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendFont::SetFontProperty(int nFontSize, LPWSTR lpszFontType)
{
	m_nFontSize = nFontSize;
	m_lpszFontType = lpszFontType;
}

//------------------------------------------------------------------
// @Function:	 SetFontText()
// @Purpose: CCerasusBlendFont������������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendFont::SetFontText(HWND hWnd, LPCWSTR lpcszStr, DWORD dwFormat, D3DCOLOR dwColor)
{
	m_hWnd = hWnd;
	m_lpcszStr = lpcszStr;
	m_dwFormat = dwFormat;
	m_dwColor = dwColor;
}

//------------------------------------------------------------------
// @Function:	 Init()
// @Purpose: CCerasusBlendFont��ʼ���ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendFont::Init()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_pFontStates[i]->DirectFontInit(m_nFontSize, m_lpszFontType);
	}

}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CCerasusBlendFont��Ⱦ�ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendFont::Blend(UINT nState)
{
	m_pFontCurrent = m_pFontStates[nState];
	m_pFontCurrent->DirectFontDrawText(m_hWnd, m_lpcszStr, m_dwFormat, m_dwColor);
}

//------------------------------------------------------------------
// @Function:	 Refresh()
// @Purpose: CCerasusBlendFontˢ�¿ؼ�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCerasusBlendFont::Refresh()
{
	m_pFontCurrent = m_pFontStates[CERASUS_STATE_HIDDEN];
}
