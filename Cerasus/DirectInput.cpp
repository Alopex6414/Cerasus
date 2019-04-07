/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Sakura&Fantasy
*     All rights reserved.
*
* @file		DirectInput.cpp
* @brief	This Program is DirectInput DLL Project.
* @author	Alopex/Alice
* @version	v1.25a
* @date		2017-10-27	v1.00a	alopex	Create Project.
* @date		2017-12-03	v1.01a	alopex	Add Enum & Modify CallBack Function.
* @date		2017-12-08	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Get Members Function.
* @date		2018-11-23	v1.24a	alopex	Alter Call Method.
* @date		2019-04-04	v1.25a	alopex	Add Notes.
*/
#include "DirectCommon.h"
#include "DirectInput.h"
#include "DirectThreadSafe.h"

GUID g_JoyStickGUID;											// DirectInput JoyStick GUID
char g_cJoyStickName[DX9_INPUT_JOYSTICK_ARRAY_SIZE];			// DirectInput JoyStick Name Array

//------------------------------------------------------------------
// @Function:	 DirectInput()
// @Purpose: DirectInput���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectInput::DirectInput() :
	m_pDirectInput(NULL),
	m_pDirectInputDeviceKeyBoard(NULL),
	m_pDirectInputDeviceMouse(NULL),
	m_pDirectInputDeviceJoyStick(NULL)
{
	m_bThreadSafe = true;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	ZeroMemory(&m_DIMouseState, sizeof(m_DIMouseState));
	ZeroMemory(&m_DIJoyStickState, sizeof(m_DIJoyStickState));
	ZeroMemory(&m_cKeyBoradBuffer, sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE);
}

//------------------------------------------------------------------
// @Function:	 ~DirectInput()
// @Purpose: DirectInput��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectInput::~DirectInput()
{
	if (m_pDirectInputDeviceMouse != NULL)
	{
		m_pDirectInputDeviceMouse->Unacquire();
	}

	if (m_pDirectInputDeviceKeyBoard != NULL)
	{
		m_pDirectInputDeviceKeyBoard->Unacquire();
	}

	if (m_pDirectInputDeviceJoyStick != NULL)
	{
		m_pDirectInputDeviceJoyStick->Unacquire();
	}

	SAFE_RELEASE(m_pDirectInputDeviceMouse);
	SAFE_RELEASE(m_pDirectInputDeviceKeyBoard);
	SAFE_RELEASE(m_pDirectInputDeviceJoyStick);
	SAFE_RELEASE(m_pDirectInput);

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);		// Delete Critical Section
}

//------------------------------------------------------------------
// @Function:	 DirectInput(bool bSafe)
// @Purpose: DirectInput���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectInput::DirectInput(bool bSafe) :
	m_pDirectInput(NULL),
	m_pDirectInputDeviceKeyBoard(NULL),
	m_pDirectInputDeviceMouse(NULL),
	m_pDirectInputDeviceJoyStick(NULL)
{
	m_bThreadSafe = bSafe;									// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	ZeroMemory(&m_DIMouseState, sizeof(m_DIMouseState));
	ZeroMemory(&m_DIJoyStickState, sizeof(m_DIJoyStickState));
	ZeroMemory(&m_cKeyBoradBuffer, sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE);
}

//------------------------------------------------------------------
// @Function:	 DirectInput(const DirectInput &)
// @Purpose: DirectInput���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectInput::DirectInput(const DirectInput & Object)
{
	m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

	m_pDirectInput = Object.m_pDirectInput;
	m_pDirectInputDeviceKeyBoard = Object.m_pDirectInputDeviceKeyBoard;
	m_pDirectInputDeviceMouse = Object.m_pDirectInputDeviceMouse;
	m_pDirectInputDeviceJoyStick = Object.m_pDirectInputDeviceJoyStick;
	memcpy_s(&m_DIMouseState, sizeof(m_DIMouseState), &(Object.m_DIMouseState), sizeof(Object.m_DIMouseState));
	memcpy_s(&m_DIJoyStickState, sizeof(m_DIJoyStickState), &(Object.m_DIJoyStickState), sizeof(Object.m_DIJoyStickState));
	memcpy_s(&m_cKeyBoradBuffer, sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE, &(Object.m_cKeyBoradBuffer), sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE);
}

//------------------------------------------------------------------
// @Function:	 operator=(const DirectInput &)
// @Purpose: DirectInput���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
const DirectInput & DirectInput::operator=(const DirectInput & Object)
{
	if (&Object != this)
	{
		m_bThreadSafe = Object.m_bThreadSafe;					// Thread Safety flag. When m_bThreadSafe = true, Start Thread Safe Mechanism.
		if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	// Initialize Critical Section

		m_pDirectInput = Object.m_pDirectInput;
		m_pDirectInputDeviceKeyBoard = Object.m_pDirectInputDeviceKeyBoard;
		m_pDirectInputDeviceMouse = Object.m_pDirectInputDeviceMouse;
		m_pDirectInputDeviceJoyStick = Object.m_pDirectInputDeviceJoyStick;
		memcpy_s(&m_DIMouseState, sizeof(m_DIMouseState), &(Object.m_DIMouseState), sizeof(Object.m_DIMouseState));
		memcpy_s(&m_DIJoyStickState, sizeof(m_DIJoyStickState), &(Object.m_DIJoyStickState), sizeof(Object.m_DIJoyStickState));
		memcpy_s(&m_cKeyBoradBuffer, sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE, &(Object.m_cKeyBoradBuffer), sizeof(char) * DX9_INPUT_KEYBOARD_ARRAY_SIZE);
	}

	return *this;
}

//-------------------------------------------------------------------------------
// @Function:	 GetInput()
// @Purpose: DirectInput��ȡDirectInput8�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUT8(DirectInput8�ӿ�ָ��)
//-------------------------------------------------------------------------------
LPDIRECTINPUT8 DIRECTINPUT_CALLMETHOD DirectInput::GetInput() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInput;
}

//-------------------------------------------------------------------------------
// @Function:	 GetKeyBorad()
// @Purpose: DirectInput��ȡDirectInput8�ӿ��豸����
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8�ӿ��豸ָ��)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetKeyBorad() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceKeyBoard;
}

//-------------------------------------------------------------------------------
// @Function:	 GetMouse()
// @Purpose: DirectInput��ȡDirectInput8�ӿ��豸���
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8�ӿ��豸ָ��)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetMouse() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceMouse;
}

//-------------------------------------------------------------------------------
// @Function:	 GetJoyStick()
// @Purpose: DirectInput��ȡDirectInput8�ӿ��豸��Ϸ��
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8�ӿ��豸ָ��)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetJoyStick() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceJoyStick;
}

//----------------------------------------------------------------------------------------------------
// @Function:	 DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
// @Purpose: DirectInputö����Ϸ���豸����
// @Since: v1.00a
// @Para: LPCDIDEVICEINSTANCE pDirectDeviceInstance(DirectInput�豸���ָ��)
// @Para: LPVOID pGUID_Ptr(DirectInput�豸ȫ��Ψһ��ʶ���ַ�ָ��)
// @Return: DIENUM_STOP(ֹͣö��)
//----------------------------------------------------------------------------------------------------
BOOL DIRECTINPUT_CALLMETHOD DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
{
	*(GUID*)pGUID_Ptr = pDirectDeviceInstance->guidInstance;
	strcpy_s(g_cJoyStickName, (char*)pDirectDeviceInstance->tszProductName);
	return (DIENUM_STOP);
}

//------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput ��ʼ�������豸(����/���)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ����KeyBoard�����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));						// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));				// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));												// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																	// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																		// DirectInputDevice��ѯ�豸

	// ����Mouse����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));								// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));				// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));														// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																		// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceMouse->Poll());																			// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//-----------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(����/���/��Ϸ��)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputDevice eDirectInputDevice_X(ö������:����/���/��Ϸ��)
// @Para: DWORD dwDeviceCoopFlags(�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ����IDirectInputDevice8�豸�ӿڶ���
	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_Mouse:
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_JoyStick:
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(����/���/��Ϸ��)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputDevice eDirectInputDevice_X(ö������:����/���/��Ϸ��)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags(ö������:�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ���DirectInput�豸Э���ȼ�
	switch (eDirectInputDeviceCoopFlags)
	{
	case InputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case InputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case InputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	// ����IDirectInputDevice8�豸�ӿڶ���
	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_Mouse:
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_JoyStick:
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
// @Purpose: DirectInput ��ʼ�������豸(����/���/��Ϸ��)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputMulDevice eDirectInputMulDevice_X(ö������:����/���/��Ϸ��)
// @Para: DWORD dwDeviceCoopFlags1(�豸1Э������)
// @Para: DWORD dwDeviceCoopFlags2(�豸2Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ����IDirectInputDevice8�豸�ӿڶ���
	switch (eDirectInputMulDevice_X)
	{
	case InputDevice_KeyBoard_Mouse:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
													 
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_KeyBoard_JoyStick:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
													 
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_Mouse_JoyStick:
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
												  
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2)
// @Purpose: DirectInput ��ʼ�������豸(����/���/��Ϸ��)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputDevice eDirectInputDevice_X(ö������:����/���/��Ϸ��)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1(ö������:�豸Э������)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2(ö������:�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags1;
	DWORD dwDeviceCoopFlags2;

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ���DirectInput�豸Э���ȼ�
	switch (eDirectInputDeviceCoopFlags1)
	{
	case InputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags1 = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case InputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags1 = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case InputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags1 = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	switch (eDirectInputDeviceCoopFlags2)
	{
	case InputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags2 = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case InputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags2 = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case InputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags2 = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	// ����IDirectInputDevice8�豸�ӿڶ���
	switch (eDirectInputMulDevice_X)
	{
	case InputDevice_KeyBoard_Mouse:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
		
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_KeyBoard_JoyStick:
		// KeyBoard�����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice��ѯ�豸
													 
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	case InputDevice_Mouse_JoyStick:
		// Mouse����豸
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));													// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice��ѯ�豸
												  
		// JoyStick��Ϸ���豸
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// ö��JoyStick��Ϸ���豸GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// ����IDirectInputDevice8�ӿڶ���(JoyStick��Ϸ���豸����)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice����Э������
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice�������ݸ�ʽ(��׼��Ϸ�˽ṹ)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice��ȡ�豸����Ȩ
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice��ѯ�豸
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput ��ʼ�������豸(����)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ����KeyBoard�����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE));									// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(����)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DWORD dwDeviceCoopFlags(�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ����KeyBoard�����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//------------------------------------------------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(����)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(ö������:�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ���DirectInput�豸Э���ȼ�
	switch (eDeviceCoopFlags)
	{
	case InputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case InputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case InputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	// ����KeyBoard�����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// ����IDirectInputDevice8�ӿڶ���(KeyBoard�豸����)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice�������ݸ�ʽ(��׼���̽ṹ)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput ��ʼ�������豸(���)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// Mouse����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));													// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));									// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																			// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																							// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceMouse->Poll());																								// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(���)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DWORD dwDeviceCoopFlags(�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// Mouse����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));													// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																			// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																							// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceMouse->Poll());																								// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
// @Purpose: DirectInput ��ʼ�������豸(���)
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: HINSTANCE hInstance(����ʵ�����)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(ö������:�豸Э������)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// ����IDirectInput8�ӿڶ���
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// ���DirectInput�豸Э���ȼ�
	switch (eDeviceCoopFlags)
	{
	case InputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case InputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case InputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	// Mouse����豸
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));														// ����IDirectInputDevice8�ӿڶ���(Mouse����豸����)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));															// DirectInputDevice����Э������
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																				// DirectInputDevice�������ݸ�ʽ(��׼���ṹ)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																								// DirectInputDevice��ȡ�豸����Ȩ
	VERIFY(m_pDirectInputDeviceMouse->Poll());																									// DirectInputDevice��ѯ�豸

	return S_OK;//OK
}

//-------------------------------------------------------------------------------
// @Function:	GetDeviceState()
// @Purpose: DirectInput ��ȡ�豸״̬(����&���)
// @Since: v1.00a
// @Para: None
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::GetDeviceState()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	// ��ȡKeyBoard�����豸״̬
	hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);									// ��ȡKeyBoard�����豸״̬
	if (hr)
	{
		m_pDirectInputDeviceKeyBoard->Poll();																									// ��ѯ�豸
		m_pDirectInputDeviceKeyBoard->Acquire();																								// ��ȡ����Ȩ
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);								// ��ȡKeyBoard�����豸״̬
	}

	// ��ȡMouse����豸״̬
	hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);											// ��ȡMouse����豸״̬
	if (hr)
	{
		m_pDirectInputDeviceMouse->Poll();																										// ��ѯ�豸
		m_pDirectInputDeviceMouse->Acquire();																									// ��ȡ����Ȩ
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);										// ��ȡMouse����豸״̬
	}

}

//-------------------------------------------------------------------------------
// @Function:	GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X)
// @Purpose: DirectInput ��ȡ�豸״̬(����/���)
// @Since: v1.00a
// @Para: DirectInputDevice eDirectInputDevice_X(ö������:����/���/��Ϸ��)
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// ��ȡKeyBoard�����豸״̬
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);								// ��ȡKeyBoard�����豸״̬
		if (hr)
		{
			m_pDirectInputDeviceKeyBoard->Poll();																								// ��ѯ�豸
			m_pDirectInputDeviceKeyBoard->Acquire();																							// ��ȡ����Ȩ
			hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);							// ��ȡKeyBoard�����豸״̬
		}
		break;
	case InputDevice_Mouse:
		// ��ȡMouse����豸״̬
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);										// ��ȡMouse����豸״̬
		if (hr)
		{
			m_pDirectInputDeviceMouse->Poll();																									// ��ѯ�豸
			m_pDirectInputDeviceMouse->Acquire();																								// ��ȡ����Ȩ
			hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);									// ��ȡMouse����豸״̬
		}
		break;
	case InputDevice_JoyStick:
		// ��ȡJoyStick��Ϸ���豸״̬
		hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);								// ��ȡJoyStick��Ϸ���豸״̬
		if (hr)
		{
			m_pDirectInputDeviceJoyStick->Poll();																								// ��ѯ�豸
			m_pDirectInputDeviceJoyStick->Acquire();																							// ��ȡ����Ȩ
			hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);							// ��ȡJoyStick��Ϸ���豸״̬
		}
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
// @Function:	KeyBoardIsDown(int nKeyValue)
// @Purpose: DirectInput ��ȡKeyBoard�����豸����״̬
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard��ֵ)(eg:DIK_A)
// @Return: bool(true:KeyDown,false:KeyUp)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::KeyBoardIsDown(int nKeyValue)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? true : false;
}

//--------------------------------------------------------------
// @Function:	KeyBoardIsUp(int nKeyValue)
// @Purpose: DirectInput ��ȡKeyBoard�����豸����״̬
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard��ֵ)(eg:DIK_A)
// @Return: bool(true:KeyUp,false:KeyDown)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::KeyBoardIsUp(int nKeyValue)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
// @Purpose: DirectInput ��ȡMouse����豸����״̬
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(����ֵ)
// @Return: bool(true:MouseDown,false:MouseUp)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? true : false;
}

//-------------------------------------------------------------------------
// @Function:	MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
// @Purpose: DirectInput ��ȡMouse����豸����״̬
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(����ֵ)
// @Return: bool(true:MouseUp,false:MouseDown)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetX()
// @Purpose: DirectInput ��ȡMouse���X������
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse���X������)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lX;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetY()
// @Purpose: DirectInput ��ȡMouse���Y������
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse���Y������)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lY;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetZ()
// @Purpose: DirectInput ��ȡMouse���Z������
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse���Z������)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lZ;
}

//----------------------------------------------------------------------------------------
// @Function:	KeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc)
// @Purpose: DirectInput ��ȡKeyBoard�����豸����״̬(��������Ӧ)
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard��ֵ)(eg:DIK_A)
// @Para: LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc(KeyBoard�����ص�����)
// @Return: None
//----------------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::KeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_cKeyBoradBuffer[nKeyValue] & 0x80)
	{
		(*pCallBackKeyDownProc)();//KeyProc
	}
}

//------------------------------------------------------------------------------------------------------------------------------
// @Function:	MouseDownProc(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc)
// @Purpose: DirectInput ��ȡMouse����豸����״̬(��������Ӧ)
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(����ֵ)
// @Para: LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc(Mouse�����ص�����)
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::MouseDownProc(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80)
	{
		(*pCallBackMouseDownProc)();//MouseProc
	}
}
