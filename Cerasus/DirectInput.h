/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Team Gorgeous Bubble
*     All rights reserved.
*
* @file		DirectInput.h
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
#pragma once

#ifndef __DIRECTINPUT_H_
#define __DIRECTINPUT_H_

// Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectTypes.h"

// Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTINPUT_API	__declspec(dllexport)
#else
#define DIRECTINPUT_API	__declspec(dllimport)
#endif

#define DIRECTINPUT_CALLMETHOD	__stdcall

#define DX9_INPUT_KEYBOARD_ARRAY_SIZE	256			// KeyBoard Array Size(标准键盘数组大小256键)
#define DX9_INPUT_JOYSTICK_ARRAY_SIZE	80			// JoyStick Array Size(JoyStick游戏杆数组大小80键)

// Class Definition
class DIRECTINPUT_API DirectInput
{
private:
	LPDIRECTINPUT8			m_pDirectInput;							// IDirectInput8 Interface Pointer(IDirectInput8接口指针成员)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceKeyBoard;			// IDirectInputDevice8 Interface Pointer(KeyBoard Device)(IDirectInputDevice8接口设备指针:键盘)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceMouse;				// IDirectInputDevice8 Interface Pointer(Mouse Device)(IDirectInputDevice8接口设备指针:鼠标)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceJoyStick;			// IDirectInputDevice8 Interface Pointer(JoyStick Device)(IDirectInputDevice8接口设备指针:游戏杆)

private:
	DIMOUSESTATE m_DIMouseState;									// DirectInput Mouse State Struct(~DirectInput鼠标状态)
	DIJOYSTATE m_DIJoyStickState;									// DirectInput JoyStick State Struct(~DirectInput游戏杆状态)
	char m_cKeyBoradBuffer[DX9_INPUT_KEYBOARD_ARRAY_SIZE];			// DirectInput KeyBoard State Array(~DirectInput键盘状态)

protected:
	CRITICAL_SECTION m_cs;											// Direct3D 9 Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;												// Direct3D 9 Thread Safe Status(~D3D9线程安全状态)

public:
	DirectInput();													// DirectInput Construction Function(~DirectInput构造函数)
	~DirectInput();													// DirectInput Destruction Function(~DirectInput析构函数)

	DirectInput(bool bSafe);										// DirectInput Construction Function(~DirectInput构造函数)(Overload + 1)
	DirectInput(const DirectInput&);								// DirectInput Construction Function(~DirectInput拷贝构造函数)

public:
	const DirectInput& operator=(const DirectInput&);				// DirectInput Operater= Function(~DirectInput重载运算符'=')

public:
	LPDIRECTINPUT8					DIRECTINPUT_CALLMETHOD		GetInput() const;				// DirectInput Get DirectInput8(~DirectInput获取DirectInput8接口指针)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetKeyBorad() const;			// DirectInput Get DirectInput Device Keyboard(~DirectInput获取设备指针:键盘)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetMouse() const;				// DirectInput Get DirectInput Device Mouse(~DirectInput获取设备指针:鼠标)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetJoyStick() const;			// DirectInput Get DirectInput Device JoyStick(~DirectInput获取设备指针:游戏杆)

public:
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance);																																																// DirectInput Initialize(KeyBoard&Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(后台/非独占)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags);																														// DirectInput Single Device Initialize(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags);																					// DirectInput Single Device Initialize(Overload + 2)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2);																						// DirectInput Multiple Device Initialize(Overload + 3)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2);			// DirectInput Multiple Device Initialize(Overload + 4)

	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance);																																														// DirectInput Initialize(KeyBoard)(dwDeviceCoopFlags:DISCL_FOREGROUND | DISCL_EXCLUSIVE)(前台/独占)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);																																							// DirectInput Initialize(KeyBoard)(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags);																																	// DirectInput Initialize(KeyBoard)(Overload + 2)

	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance);																																														// DirectInput Initialize(Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(后台/非独占)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);																																								// DirectInput Initialize(Mouse)(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags);																																		// DirectInput Initialize(Mouse)(Overload + 2)
	
	void							DIRECTINPUT_CALLMETHOD		GetDeviceState();														// DirectInput Get Device State(KeyBoard&Mouse)
	void							DIRECTINPUT_CALLMETHOD		GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X);			// DirectInput Get Device State
	
	bool							DIRECTINPUT_CALLMETHOD		KeyBoardIsDown(int nKeyValue);											// DirectInput KeyBoard Is KeyDown(键盘按键按下)
	bool							DIRECTINPUT_CALLMETHOD		KeyBoardIsUp(int nKeyValue);											// DirectInput KeyBoard Is KeyUp(键盘按键释放)

	bool							DIRECTINPUT_CALLMETHOD		MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton);				// DirectInput Mouse Is KeyDown(鼠标按键按下)
	bool							DIRECTINPUT_CALLMETHOD		MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton);				// DirectInput Mouse Is KeyUp(鼠标按键释放)
	
	float							DIRECTINPUT_CALLMETHOD		MouseGetX();															// DirectInput Mouse Get X Axis Value(获取鼠标X轴坐标)
	float							DIRECTINPUT_CALLMETHOD		MouseGetY();															// DirectInput Mouse Get Y Axis Value(获取鼠标Y轴坐标)
	float							DIRECTINPUT_CALLMETHOD		MouseGetZ();															// DirectInput Mouse Get Z Axis Value(Mouse Wheel)(获取鼠标Z轴/滚轮坐标)

	void							DIRECTINPUT_CALLMETHOD		KeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc);													// DirectInput KeyDown Proc(键盘回调函数)
	void							DIRECTINPUT_CALLMETHOD		MouseDownProc(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc);			// DirectInput MouseDown Proc(鼠标回调函数)
	
};

#endif