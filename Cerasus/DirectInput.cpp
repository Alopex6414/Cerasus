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
// @Purpose: DirectInput构造函数
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
// @Purpose: DirectInput析构函数
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
// @Purpose: DirectInput构造函数
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
// @Purpose: DirectInput构造函数
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
// @Purpose: DirectInput构造函数
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
// @Purpose: DirectInput获取DirectInput8接口指针
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUT8(DirectInput8接口指针)
//-------------------------------------------------------------------------------
LPDIRECTINPUT8 DIRECTINPUT_CALLMETHOD DirectInput::GetInput() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInput;
}

//-------------------------------------------------------------------------------
// @Function:	 GetKeyBorad()
// @Purpose: DirectInput获取DirectInput8接口设备键盘
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8接口设备指针)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetKeyBorad() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceKeyBoard;
}

//-------------------------------------------------------------------------------
// @Function:	 GetMouse()
// @Purpose: DirectInput获取DirectInput8接口设备鼠标
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8接口设备指针)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetMouse() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceMouse;
}

//-------------------------------------------------------------------------------
// @Function:	 GetJoyStick()
// @Purpose: DirectInput获取DirectInput8接口设备游戏杆
// @Since: v1.00a
// @Para: None
// @Return: LPDIRECTINPUTDEVICE8(DirectInput8接口设备指针)
//-------------------------------------------------------------------------------
LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInput::GetJoyStick() const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pDirectInputDeviceJoyStick;
}

//----------------------------------------------------------------------------------------------------
// @Function:	 DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
// @Purpose: DirectInput枚举游戏杆设备函数
// @Since: v1.00a
// @Para: LPCDIDEVICEINSTANCE pDirectDeviceInstance(DirectInput设备句柄指针)
// @Para: LPVOID pGUID_Ptr(DirectInput设备全局唯一标识符字符指针)
// @Return: DIENUM_STOP(停止枚举)
//----------------------------------------------------------------------------------------------------
BOOL DIRECTINPUT_CALLMETHOD DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
{
	*(GUID*)pGUID_Ptr = pDirectDeviceInstance->guidInstance;
	strcpy_s(g_cJoyStickName, (char*)pDirectDeviceInstance->tszProductName);
	return (DIENUM_STOP);
}

//------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));						// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));				// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));												// DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																	// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																		// DirectInputDevice轮询设备

	// 创建Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));								// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));				// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));														// DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																		// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());																			// DirectInputDevice轮询设备

	return S_OK;//OK
}

//-----------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 创建IDirectInputDevice8设备接口对象
	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
		break;
	case InputDevice_Mouse:
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
		break;
	case InputDevice_JoyStick:
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 填充DirectInput设备协作等级
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

	// 创建IDirectInputDevice8设备接口对象
	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
		break;
	case InputDevice_Mouse:
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
		break;
	case InputDevice_JoyStick:
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputMulDevice eDirectInputMulDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DWORD dwDeviceCoopFlags1(设备1协作级别)
// @Para: DWORD dwDeviceCoopFlags2(设备2协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 创建IDirectInputDevice8设备接口对象
	switch (eDirectInputMulDevice_X)
	{
	case InputDevice_KeyBoard_Mouse:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
													 
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
		break;
	case InputDevice_KeyBoard_JoyStick:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
													 
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	case InputDevice_Mouse_JoyStick:
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
												  
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1(枚举类型:设备协作级别)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags1;
	DWORD dwDeviceCoopFlags2;

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 填充DirectInput设备协作等级
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

	// 创建IDirectInputDevice8设备接口对象
	switch (eDirectInputMulDevice_X)
	{
	case InputDevice_KeyBoard_Mouse:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
		
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
		break;
	case InputDevice_KeyBoard_JoyStick:
		// KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));										// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																// DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																						// DirectInputDevice轮询设备
													 
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	case InputDevice_Mouse_JoyStick:
		// Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));												// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));													// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																		// DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());																						// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());																							// DirectInputDevice轮询设备
												  
		// JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));			// 枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));											// 创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));												// DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));																// DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());																					// DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());																						// DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE));									// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice轮询设备

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice轮询设备

	return S_OK;//OK
}

//------------------------------------------------------------------------------------------------------------------
// @Function:	CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 填充DirectInput设备协作等级
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

	// 创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));											// 创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));																	// DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());																						// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());																							// DirectInputDevice轮询设备

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));													// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));									// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																			// DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																							// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());																								// DirectInputDevice轮询设备

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));													// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));														// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																			// DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																							// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());																								// DirectInputDevice轮询设备

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------
// @Function:	CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMETHOD DirectInput::CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	// 创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	// 填充DirectInput设备协作等级
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

	// Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));														// 创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));															// DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));																				// DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());																								// DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());																									// DirectInputDevice轮询设备

	return S_OK;//OK
}

//-------------------------------------------------------------------------------
// @Function:	GetDeviceState()
// @Purpose: DirectInput 读取设备状态(键盘&鼠标)
// @Since: v1.00a
// @Para: None
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::GetDeviceState()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	// 获取KeyBoard键盘设备状态
	hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);									// 获取KeyBoard键盘设备状态
	if (hr)
	{
		m_pDirectInputDeviceKeyBoard->Poll();																									// 轮询设备
		m_pDirectInputDeviceKeyBoard->Acquire();																								// 获取控制权
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);								// 获取KeyBoard键盘设备状态
	}

	// 获取Mouse鼠标设备状态
	hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);											// 获取Mouse鼠标设备状态
	if (hr)
	{
		m_pDirectInputDeviceMouse->Poll();																										// 轮询设备
		m_pDirectInputDeviceMouse->Acquire();																									// 获取控制权
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);										// 获取Mouse鼠标设备状态
	}

}

//-------------------------------------------------------------------------------
// @Function:	GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X)
// @Purpose: DirectInput 读取设备状态(键盘/鼠标)
// @Since: v1.00a
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMETHOD DirectInput::GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	switch (eDirectInputDevice_X)
	{
	case InputDevice_KeyBoard:
		// 读取KeyBoard键盘设备状态
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);								// 获取KeyBoard键盘设备状态
		if (hr)
		{
			m_pDirectInputDeviceKeyBoard->Poll();																								// 轮询设备
			m_pDirectInputDeviceKeyBoard->Acquire();																							// 获取控制权
			hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);							// 获取KeyBoard键盘设备状态
		}
		break;
	case InputDevice_Mouse:
		// 读取Mouse鼠标设备状态
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);										// 获取Mouse鼠标设备状态
		if (hr)
		{
			m_pDirectInputDeviceMouse->Poll();																									// 轮询设备
			m_pDirectInputDeviceMouse->Acquire();																								// 获取控制权
			hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);									// 获取Mouse鼠标设备状态
		}
		break;
	case InputDevice_JoyStick:
		// 读取JoyStick游戏杆设备状态
		hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);								// 获取JoyStick游戏杆设备状态
		if (hr)
		{
			m_pDirectInputDeviceJoyStick->Poll();																								// 轮询设备
			m_pDirectInputDeviceJoyStick->Acquire();																							// 获取控制权
			hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);							// 获取JoyStick游戏杆设备状态
		}
		break;
	default:
		break;
	}

}

//--------------------------------------------------------------
// @Function:	KeyBoardIsDown(int nKeyValue)
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Return: bool(true:KeyDown,false:KeyUp)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::KeyBoardIsDown(int nKeyValue)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? true : false;
}

//--------------------------------------------------------------
// @Function:	KeyBoardIsUp(int nKeyValue)
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Return: bool(true:KeyUp,false:KeyDown)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::KeyBoardIsUp(int nKeyValue)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Return: bool(true:MouseDown,false:MouseUp)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? true : false;
}

//-------------------------------------------------------------------------
// @Function:	MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Return: bool(true:MouseUp,false:MouseDown)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMETHOD DirectInput::MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetX()
// @Purpose: DirectInput 读取Mouse鼠标X轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标X轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetX()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lX;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetY()
// @Purpose: DirectInput 读取Mouse鼠标Y轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标Y轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetY()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lY;
}

//-------------------------------------------------------------------------
// @Function:	MouseGetZ()
// @Purpose: DirectInput 读取Mouse鼠标Z轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标Z轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMETHOD DirectInput::MouseGetZ()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lZ;
}

//----------------------------------------------------------------------------------------
// @Function:	KeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc)
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态(处理按键响应)
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Para: LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc(KeyBoard按键回调函数)
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
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态(处理按键响应)
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Para: LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc(Mouse按键回调函数)
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
