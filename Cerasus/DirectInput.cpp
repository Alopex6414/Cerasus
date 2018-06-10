/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectInput.cpp
* @brief	This Program is DirectInput DLL Project.
* @author	Alopex/Helium
* @version	v1.22a
* @date		2017-10-27	v1.00a	alopex	Create Project.
* @date		2017-12-3	v1.01a	alopex	Add Enum & Modify CallBack Function.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.22a	alopex	Add Macro Call Mode.
*/
#include "DirectCommon.h"
#include "DirectInput.h"
#include "DirectThreadSafe.h"

GUID g_JoyStickGUID;	//JoyStick GUID
char g_cJoyStickName[JOYSTICK_ARRAYSIZE]; //JoyStick Name Array

//------------------------------------------------------------------
// @Function:	 DirectInput()
// @Purpose: DirectInput构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectInput::DirectInput()
{
	m_bThreadSafe = true;									//线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//初始化临界区

	m_pDirectInput = NULL;					//IDirectInput8接口对象指针初始化(NULL)
	m_pDirectInputDeviceKeyBoard = NULL;	//IDirectInputDevice8 KeyBoard键盘设备指针初始化(NULL)
	m_pDirectInputDeviceMouse = NULL;		//IDirectInputDevice8 Mouse鼠标设备指针初始化(NULL)
	m_pDirectInputDeviceJoyStick = NULL;	//IDirectInputDevice8 JoyStick游戏杆设备指针初始化(NULL)
	ZeroMemory(&m_DIMouseState, sizeof(m_DIMouseState));//清除MouseState内存
	ZeroMemory(&m_DIJoyStickState, sizeof(m_DIJoyStickState));//清除JoyStick内存
	ZeroMemory(&m_cKeyBoradBuffer, sizeof(char) * KEYBOARD_ARRAYSIZE);//清除KeyBoradBuffer内存
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
	if (m_pDirectInputDeviceMouse != NULL)//Mouse鼠标设备指针不为NULL
	{
		m_pDirectInputDeviceMouse->Unacquire();//Mouse鼠标设备释放控制权
	}
	if (m_pDirectInputDeviceKeyBoard != NULL)//KeyBoard键盘设备指针不为NULL
	{
		m_pDirectInputDeviceKeyBoard->Unacquire();//KeyBoard键盘设备释放控制权
	}
	if (m_pDirectInputDeviceJoyStick != NULL)//JoyStick游戏杆设备指针不为NULL
	{
		m_pDirectInputDeviceJoyStick->Unacquire();//JoyStick游戏杆设备释放控制权
	}

	SAFE_RELEASE(m_pDirectInputDeviceMouse);//Mouse鼠标设备释放
	SAFE_RELEASE(m_pDirectInputDeviceKeyBoard);//KeyBoard键盘设备释放
	SAFE_RELEASE(m_pDirectInputDeviceJoyStick);//JoyStick游戏杆设备释放
	SAFE_RELEASE(m_pDirectInput);//DirectInput释放

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//删除临界区
}

//----------------------------------------------------------------------------------------------------
// @Function:	 DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
// @Purpose: DirectInput枚举游戏杆设备函数
// @Since: v1.00a
// @Para: LPCDIDEVICEINSTANCE pDirectDeviceInstance(DirectInput设备句柄指针)
// @Para: LPVOID pGUID_Ptr(DirectInput设备全局唯一标识符字符指针)
// @Return: DIENUM_STOP(停止枚举)
//----------------------------------------------------------------------------------------------------
BOOL DIRECTINPUT_CALLMODE DirectInputEnumJoySticks(LPCDIDEVICEINSTANCE pDirectDeviceInstance, LPVOID pGUID_Ptr)
{
	*(GUID*)pGUID_Ptr = pDirectDeviceInstance->guidInstance;
	strcpy_s(g_cJoyStickName, (char*)pDirectDeviceInstance->tszProductName);
	return (DIENUM_STOP);
}

//------------------------------------------------------------------------
// @Function:	DirectInputInit(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputInit(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备

	//Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//-----------------------------------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//创建IDirectInputDevice8设备接口对象
	switch (eDirectInputDevice_X)
	{
	case DirectInputDevice_KeyBoard:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_Mouse:
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_JoyStick:
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputMulDevice eDirectInputMulDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DWORD dwDeviceCoopFlags1(设备1协作级别)
// @Para: DWORD dwDeviceCoopFlags2(设备2协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//创建IDirectInputDevice8设备接口对象
	switch (eDirectInputMulDevice_X)
	{
	case DirectInputDevice_KeyBoard_Mouse:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_KeyBoard_JoyStick:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_Mouse_JoyStick:
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//填充DirectInput设备协作等级
	switch (eDirectInputDeviceCoopFlags)
	{
	case DirectInputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case DirectInputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case DirectInputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	//创建IDirectInputDevice8设备接口对象
	switch (eDirectInputDevice_X)
	{
	case DirectInputDevice_KeyBoard:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_Mouse:
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_JoyStick:
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2)
// @Purpose: DirectInput 初始化输入设备(键盘/鼠标/游戏杆)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1(枚举类型:设备协作级别)
// @Para: DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags1;
	DWORD dwDeviceCoopFlags2;

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//填充DirectInput设备协作等级
	switch (eDirectInputDeviceCoopFlags1)
	{
	case DirectInputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags1 = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case DirectInputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags1 = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case DirectInputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags1 = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	switch (eDirectInputDeviceCoopFlags2)
	{
	case DirectInputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags2 = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case DirectInputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags2 = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case DirectInputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags2 = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	//创建IDirectInputDevice8设备接口对象
	switch (eDirectInputMulDevice_X)
	{
	case DirectInputDevice_KeyBoard_Mouse:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_KeyBoard_JoyStick:
		//KeyBoard键盘设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
		VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
		VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	case DirectInputDevice_Mouse_JoyStick:
		//Mouse鼠标设备
		VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
		VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags1));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
		VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备
		//JoyStick游戏杆设备
		VERIFY(m_pDirectInput->EnumDevices(DI8DEVTYPE_JOYSTICK, DirectInputEnumJoySticks, &g_JoyStickGUID, DIEDFL_ATTACHEDONLY));//枚举JoyStick游戏杆设备GUID
		VERIFY(m_pDirectInput->CreateDevice(g_JoyStickGUID, &m_pDirectInputDeviceJoyStick, NULL));//创建IDirectInputDevice8接口对象(JoyStick游戏杆设备对象)
		VERIFY(m_pDirectInputDeviceJoyStick->SetCooperativeLevel(hWnd, dwDeviceCoopFlags2));//DirectInputDevice设置协作级别
		VERIFY(m_pDirectInputDeviceJoyStick->SetDataFormat(&c_dfDIJoystick));//DirectInputDevice设置数据格式(标准游戏杆结构)
		VERIFY(m_pDirectInputDeviceJoyStick->Acquire());//DirectInputDevice获取设备控制权
		VERIFY(m_pDirectInputDeviceJoyStick->Poll());//DirectInputDevice轮询设备
		break;
	default:
		break;
	}

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//------------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(键盘)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//填充DirectInput设备协作等级
	switch (eDeviceCoopFlags)
	{
	case DirectInputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case DirectInputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case DirectInputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	//创建KeyBoard键盘设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDirectInputDeviceKeyBoard, NULL));//创建IDirectInputDevice8接口对象(KeyBoard设备对象)
	VERIFY(m_pDirectInputDeviceKeyBoard->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceKeyBoard->SetDataFormat(&c_dfDIKeyboard));//DirectInputDevice设置数据格式(标准键盘结构)
	VERIFY(m_pDirectInputDeviceKeyBoard->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceKeyBoard->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//------------------------------------------------------------------------
// @Function:	DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//----------------------------------------------------------------------------------------------
// @Function:	DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DWORD dwDeviceCoopFlags(设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//----------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------------------
// @Function:	DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags)
// @Purpose: DirectInput 初始化输入设备(鼠标)
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: HINSTANCE hInstance(窗口实例句柄)
// @Para: DirectInputDeviceCoopFlags eDeviceCoopFlags(枚举类型:设备协作级别)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------------------
HRESULT DIRECTINPUT_CALLMODE DirectInput::DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	DWORD dwDeviceCoopFlags;

	//创建IDirectInput8接口对象
	VERIFY(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL));

	//填充DirectInput设备协作等级
	switch (eDeviceCoopFlags)
	{
	case DirectInputCoopFlags_ForeGround_Exclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
		break;
	case DirectInputCoopFlags_ForeGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		break;
	case DirectInputCoopFlags_BackGround_NoExclusive:
		dwDeviceCoopFlags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
		break;
	default:
		break;
	}

	//Mouse鼠标设备
	VERIFY(m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pDirectInputDeviceMouse, NULL));//创建IDirectInputDevice8接口对象(Mouse鼠标设备对象)
	VERIFY(m_pDirectInputDeviceMouse->SetCooperativeLevel(hWnd, dwDeviceCoopFlags));//DirectInputDevice设置协作级别
	VERIFY(m_pDirectInputDeviceMouse->SetDataFormat(&c_dfDIMouse));//DirectInputDevice设置数据格式(标准鼠标结构)
	VERIFY(m_pDirectInputDeviceMouse->Acquire());//DirectInputDevice获取设备控制权
	VERIFY(m_pDirectInputDeviceMouse->Poll());//DirectInputDevice轮询设备

	return S_OK;//OK
}

//-------------------------------------------------------------------------------
// @Function:	DirectInputGetDeviceState(void) const
// @Purpose: DirectInput 读取设备状态(键盘&鼠标)
// @Since: v1.00a
// @Para: None
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMODE DirectInput::DirectInputGetDeviceState(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	//获取KeyBoard键盘设备状态
	hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);//获取KeyBoard键盘设备状态
	if (hr)
	{
		m_pDirectInputDeviceKeyBoard->Poll();//轮询设备
		m_pDirectInputDeviceKeyBoard->Acquire();//获取控制权
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);//获取KeyBoard键盘设备状态
	}

	//获取Mouse鼠标设备状态
	hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);//获取Mouse鼠标设备状态
	if (hr)
	{
		m_pDirectInputDeviceMouse->Poll();//轮询设备
		m_pDirectInputDeviceMouse->Acquire();//获取控制权
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);//获取Mouse鼠标设备状态
	}
}

//-------------------------------------------------------------------------------
// @Function:	DirectInputGetDeviceState(DirectInputDevice eDirectInputDevice_X) const
// @Purpose: DirectInput 读取设备状态(键盘/鼠标)
// @Since: v1.00a
// @Para: DirectInputDevice eDirectInputDevice_X(枚举类型:键盘/鼠标/游戏杆)
// @Return: None
//-------------------------------------------------------------------------------
void DIRECTINPUT_CALLMODE DirectInput::DirectInputGetDeviceState(DirectInputDevice eDirectInputDevice_X) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	HRESULT hr;

	switch (eDirectInputDevice_X)
	{
	case DirectInputDevice_KeyBoard:
		//读取KeyBoard键盘设备状态
		hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);//获取KeyBoard键盘设备状态
		if (hr)
		{
			m_pDirectInputDeviceKeyBoard->Poll();//轮询设备
			m_pDirectInputDeviceKeyBoard->Acquire();//获取控制权
			hr = m_pDirectInputDeviceKeyBoard->GetDeviceState(sizeof(m_cKeyBoradBuffer), (LPVOID)m_cKeyBoradBuffer);//获取KeyBoard键盘设备状态
		}
		break;
	case DirectInputDevice_Mouse:
		//读取Mouse鼠标设备状态
		hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);//获取Mouse鼠标设备状态
		if (hr)
		{
			m_pDirectInputDeviceMouse->Poll();//轮询设备
			m_pDirectInputDeviceMouse->Acquire();//获取控制权
			hr = m_pDirectInputDeviceMouse->GetDeviceState(sizeof(m_DIMouseState), (LPVOID)&m_DIMouseState);//获取Mouse鼠标设备状态
		}
		break;
	case DirectInputDevice_JoyStick:
		//读取JoyStick游戏杆设备状态
		hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);//获取JoyStick游戏杆设备状态
		if (hr)
		{
			m_pDirectInputDeviceJoyStick->Poll();//轮询设备
			m_pDirectInputDeviceJoyStick->Acquire();//获取控制权
			hr = m_pDirectInputDeviceJoyStick->GetDeviceState(sizeof(m_DIJoyStickState), (LPVOID)&m_DIJoyStickState);//获取JoyStick游戏杆设备状态
		}
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
// @Function:	DIKeyBoardIsDown(int nKeyValue) const
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Return: bool(true:KeyDown,false:KeyUp)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMODE DirectInput::DIKeyBoardIsDown(int nKeyValue) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? true : false;
}

//--------------------------------------------------------------
// @Function:	DIKeyBoardIsUp(int nKeyValue) const
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Return: bool(true:KeyUp,false:KeyDown)
//--------------------------------------------------------------
bool DIRECTINPUT_CALLMODE DirectInput::DIKeyBoardIsUp(int nKeyValue) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_cKeyBoradBuffer[nKeyValue] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	DIMouseIsDown(DirectInputMouseState eDIMouse_XButton) const
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Return: bool(true:MouseDown,false:MouseUp)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMODE DirectInput::DIMouseIsDown(DirectInputMouseState eDIMouse_XButton) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? true : false;
}

//-------------------------------------------------------------------------
// @Function:	DIMouseIsUp(DirectInputMouseState eDIMouse_XButton) const
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Return: bool(true:MouseUp,false:MouseDown)
//-------------------------------------------------------------------------
bool DIRECTINPUT_CALLMODE DirectInput::DIMouseIsUp(DirectInputMouseState eDIMouse_XButton) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80) ? false : true;
}

//-------------------------------------------------------------------------
// @Function:	DIMouseGetX(void) const
// @Purpose: DirectInput 读取Mouse鼠标X轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标X轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMODE DirectInput::DIMouseGetX(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lX;
}

//-------------------------------------------------------------------------
// @Function:	DIMouseGetY(void) const
// @Purpose: DirectInput 读取Mouse鼠标Y轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标Y轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMODE DirectInput::DIMouseGetY(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lY;
}

//-------------------------------------------------------------------------
// @Function:	DIMouseGetZ(void) const
// @Purpose: DirectInput 读取Mouse鼠标Z轴坐标
// @Since: v1.00a
// @Para: None
// @Return: float(Mouse鼠标Z轴坐标)
//-------------------------------------------------------------------------
float DIRECTINPUT_CALLMODE DirectInput::DIMouseGetZ(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (float)m_DIMouseState.lZ;
}

//---------------------------------------------------------------------------
// @Function:	DIKeyDownProc(int nKeyValue, KeyDownProc)
// @Purpose: DirectInput 读取KeyBoard键盘设备按键状态(处理按键响应)
// @Since: v1.00a
// @Para: int nKeyValue(KeyBoard键值)(eg:DIK_A)
// @Para: LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc(KeyBoard按键回调函数)
// @Return: None
//---------------------------------------------------------------------------
void CALLBACK DirectInput::DIKeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_cKeyBoradBuffer[nKeyValue] & 0x80)
	{
		(*pCallBackKeyDownProc)();//KeyProc
	}
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	DIMouseDownProc(DirectInputMouseState eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc)
// @Purpose: DirectInput 读取Mouse鼠标设备按键状态(处理按键响应)
// @Since: v1.00a
// @Para: DirectInputMouseState eDIMouse_XButton(鼠标键值)
// @Para: LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc(Mouse按键回调函数)
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void CALLBACK DirectInput::DIMouseDownProc(DirectInputMouseState eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (m_DIMouseState.rgbButtons[eDIMouse_XButton] & 0x80)
	{
		(*pCallBackMouseDownProc)();//MouseProc
	}
}