/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		SakuraBlend.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-10-16	v1.00a	alopex	Create Project.
*/
#include "SakuraBlend.h"

// SakuraGUI �ؼ�����&������Ⱦ(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::CSakuraBlendFont()
{
	m_pD3D9Device = NULL;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraBlendFont()
// @Purpose: CSakuraBlendFont��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::~CSakuraBlendFont()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_States[i]);
	}

	SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont�������캯��(����+1)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::CSakuraBlendFont(const CSakuraBlendFont & Object)
{
	m_pD3D9Device = Object.m_pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (Object.m_States[i] == NULL)
		{
			m_States[i] = NULL;
		}
		else
		{
			m_States[i] = new DirectFont(*(Object.m_States[i]));
		}
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont���캯��(����+2)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont::CSakuraBlendFont(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont��ֵ���������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendFont & CSakuraBlendFont::operator=(const CSakuraBlendFont & Object)
{
	m_pD3D9Device = Object.m_pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (Object.m_States[i] == NULL)
		{
			m_States[i] = NULL;
		}
		else
		{
			m_States[i] = new DirectFont(*(Object.m_States[i]));
		}
	}

	m_Current = NULL;
	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraBlendFont��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURABLEND_CALLMETHOD CSakuraBlendFont::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetStates()
// @Purpose: CSakuraBlendFont��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont *SAKURABLEND_CALLMETHOD CSakuraBlendFont::GetCurrent() const
{
	return m_Current;
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraBlendFont��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::OnCreate(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 OnLostDevice()
// @Purpose: CSakuraBlendFont��ʧ�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::OnLostDevice()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (m_States[i] != NULL)
		{
			m_States[i]->GetFont()->OnLostDevice();
		}
	}

}

//------------------------------------------------------------------
// @Function:	 OnResetDevice()
// @Purpose: CSakuraBlendFont�����豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::OnResetDevice()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (m_States[i] != NULL)
		{
			m_States[i]->GetFont()->OnResetDevice();
		}
	}

}

//------------------------------------------------------------------
// @Function:	 AddFont()
// @Purpose: CSakuraBlendFont�������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendFont::AddFont(SAKURA_CONTROL_STATE eType, LPWSTR strFontName, int nFontSize)
{
	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = new DirectFont(m_pD3D9Device);

	if (m_States[eType] == NULL)
	{
		return -1;
	}

	HRESULT hr = m_States[eType]->Create(nFontSize, strFontName);
	if (FAILED(hr))
	{
		return -2;
	}

	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CSakuraBlendFont��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendFont::Blend(SAKURA_CONTROL_STATE eType, LPCWSTR pString, LPRECT pRect, DWORD Format, D3DCOLOR Color)
{
	if (m_States[eType] == NULL)
	{
		return;
	}

	m_States[eType]->GetFont()->DrawTextW(NULL, pString, -1, pRect, Format, Color);
	m_Current = m_States[eType];
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::CSakuraBlendTexture()
{
	m_pD3D9Device = NULL;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::~CSakuraBlendTexture()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		SAFE_DELETE(m_States[i]);
	}

	SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture�������캯��(����+1)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::CSakuraBlendTexture(const CSakuraBlendTexture & Object)
{
	m_pD3D9Device = Object.m_pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (Object.m_States[i] == NULL)
		{
			m_States[i] = NULL;
		}
		else
		{
			m_States[i] = new CCerasusUnit(*(Object.m_States[i]));
		}
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture���캯��(����+2)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture::CSakuraBlendTexture(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		m_States[i] = NULL;
	}

	m_Current = NULL;
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture��ֵ���������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CSakuraBlendTexture & CSakuraBlendTexture::operator=(const CSakuraBlendTexture & Object)
{
	m_pD3D9Device = Object.m_pD3D9Device;

	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (Object.m_States[i] == NULL)
		{
			m_States[i] = NULL;
		}
		else
		{
			m_States[i] = new CCerasusUnit(*(Object.m_States[i]));
		}
	}

	m_Current = NULL;
	return *this;
}

//------------------------------------------------------------------
// @Function:	 GetDevice()
// @Purpose: CSakuraBlendTexture��ȡ�豸ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LPDIRECT3DDEVICE9 SAKURABLEND_CALLMETHOD CSakuraBlendTexture::GetDevice() const
{
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 GetCurrent()
// @Purpose: CSakuraBlendTexture��ȡ��ǰ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCerasusUnit *SAKURABLEND_CALLMETHOD CSakuraBlendTexture::GetCurrent() const
{
	return m_Current;
}

//------------------------------------------------------------------
// @Function:	 OnCreate()
// @Purpose: CSakuraBlendTexture��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::OnCreate(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 OnLostDevice()
// @Purpose: CSakuraBlendTexture��ʧ�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::OnLostDevice()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (m_States[i] != NULL)
		{
			m_States[i]->Reset();
		}
	}
}

//------------------------------------------------------------------
// @Function:	 OnResetDevice()
// @Purpose: CSakuraBlendTexture�����豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::OnResetDevice()
{
	for (int i = 0; i < MAX_CONTROL_STATES; ++i)
	{
		if (m_States[i] != NULL)
		{
			m_States[i]->ReCreate();
		}
	}
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraBlendTexture�������(�ļ�����)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendTexture::AddTexture(SAKURA_CONTROL_STATE eType, S_CS_UNIT_PARA sUnit)
{
	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = new CCerasusUnit(m_pD3D9Device);

	if (m_States[eType] == NULL)
	{
		return -1;
	}

	HRESULT hr = m_States[eType]->Create(sUnit);
	if (FAILED(hr))
	{
		return -2;
	}

	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 AddTexture()
// @Purpose: CSakuraBlendTexture�������(�ڴ浼��)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int SAKURABLEND_CALLMETHOD CSakuraBlendTexture::AddTexture(SAKURA_CONTROL_STATE eType, S_CS_UNIT_EX_PARA sUnit)
{
	if (m_States[eType] != NULL)
	{
		SAFE_DELETE(m_States[eType]);
	}

	m_States[eType] = new CCerasusUnit(m_pD3D9Device);

	if (m_States[eType] == NULL)
	{
		return -1;
	}

	HRESULT hr = m_States[eType]->Create(sUnit);
	if (FAILED(hr))
	{
		return -2;
	}

	m_Current = m_States[eType];

	return 0;
}

//------------------------------------------------------------------
// @Function:	 Blend()
// @Purpose: CSakuraBlendTexture��Ⱦ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void SAKURABLEND_CALLMETHOD CSakuraBlendTexture::Blend(SAKURA_CONTROL_STATE eType)
{
	if (m_States[eType] == NULL)
	{
		return;
	}

	m_States[eType]->MatrixTransform();
	m_States[eType]->PaddingVertexAndIndex();
	m_States[eType]->SetAlphaEnable();
	m_States[eType]->SetRenderState();
	m_States[eType]->Render();
	m_States[eType]->SetAlphaDisable();
}
