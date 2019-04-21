/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		SakuraBlend.cpp
* @brief	This File is SakuraGUI DLL Project.
* @author	Alopex/Alice
* @version	v1.01a
* @date		2018-10-16	v1.00a	alopex	Create Project.
* @date		2019-04-20	v1.01a	alopex	Add Notes.
*/
#include "SakuraBlend.h"

// SakuraGUI 控件字体&纹理渲染(UI)

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont构造函数
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
// @Purpose: CSakuraBlendFont析构函数
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

	//SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendFont()
// @Purpose: CSakuraBlendFont拷贝构造函数(重载+1)
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
// @Purpose: CSakuraBlendFont构造函数(重载+2)
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
// @Purpose: CSakuraBlendFont赋值运算符重载
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
// @Purpose: CSakuraBlendFont获取设备指针
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
// @Purpose: CSakuraBlendFont获取设备指针
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
// @Purpose: CSakuraBlendFont初始化
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
// @Purpose: CSakuraBlendFont丢失设备
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
// @Purpose: CSakuraBlendFont重置设备
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
// @Purpose: CSakuraBlendFont添加字体
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
// @Purpose: CSakuraBlendFont渲染字体
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
// @Purpose: CSakuraBlendTexture构造函数
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
// @Purpose: CSakuraBlendTexture析构函数
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

	//SAFE_DELETE(m_Current);
}

//------------------------------------------------------------------
// @Function:	 CSakuraBlendTexture()
// @Purpose: CSakuraBlendTexture拷贝构造函数(重载+1)
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
// @Purpose: CSakuraBlendTexture构造函数(重载+2)
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
// @Purpose: CSakuraBlendTexture赋值运算符重载
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
// @Purpose: CSakuraBlendTexture获取设备指针
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
// @Purpose: CSakuraBlendTexture获取当前纹理
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
// @Purpose: CSakuraBlendTexture初始化
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
// @Purpose: CSakuraBlendTexture丢失设备
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
// @Purpose: CSakuraBlendTexture重置设备
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
// @Purpose: CSakuraBlendTexture添加纹理(文件导入)
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
// @Purpose: CSakuraBlendTexture添加纹理(内存导入)
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
// @Purpose: CSakuraBlendTexture渲染纹理
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
