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

#define DX9_INPUT_KEYBOARD_ARRAY_SIZE	256			// KeyBoard Array Size(��׼���������С256��)
#define DX9_INPUT_JOYSTICK_ARRAY_SIZE	80			// JoyStick Array Size(JoyStick��Ϸ�������С80��)

// Class Definition
class DIRECTINPUT_API DirectInput
{
private:
	LPDIRECTINPUT8			m_pDirectInput;							// IDirectInput8 Interface Pointer(IDirectInput8�ӿ�ָ���Ա)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceKeyBoard;			// IDirectInputDevice8 Interface Pointer(KeyBoard Device)(IDirectInputDevice8�ӿ��豸ָ��:����)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceMouse;				// IDirectInputDevice8 Interface Pointer(Mouse Device)(IDirectInputDevice8�ӿ��豸ָ��:���)
	LPDIRECTINPUTDEVICE8	m_pDirectInputDeviceJoyStick;			// IDirectInputDevice8 Interface Pointer(JoyStick Device)(IDirectInputDevice8�ӿ��豸ָ��:��Ϸ��)

private:
	DIMOUSESTATE m_DIMouseState;									// DirectInput Mouse State Struct(~DirectInput���״̬)
	DIJOYSTATE m_DIJoyStickState;									// DirectInput JoyStick State Struct(~DirectInput��Ϸ��״̬)
	char m_cKeyBoradBuffer[DX9_INPUT_KEYBOARD_ARRAY_SIZE];			// DirectInput KeyBoard State Array(~DirectInput����״̬)

protected:
	CRITICAL_SECTION m_cs;											// Direct3D 9 Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;												// Direct3D 9 Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectInput();													// DirectInput Construction Function(~DirectInput���캯��)
	~DirectInput();													// DirectInput Destruction Function(~DirectInput��������)

	DirectInput(bool bSafe);										// DirectInput Construction Function(~DirectInput���캯��)(Overload + 1)
	DirectInput(const DirectInput&);								// DirectInput Construction Function(~DirectInput�������캯��)

public:
	const DirectInput& operator=(const DirectInput&);				// DirectInput Operater= Function(~DirectInput���������'=')

public:
	LPDIRECTINPUT8					DIRECTINPUT_CALLMETHOD		GetInput() const;				// DirectInput Get DirectInput8(~DirectInput��ȡDirectInput8�ӿ�ָ��)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetKeyBorad() const;			// DirectInput Get DirectInput Device Keyboard(~DirectInput��ȡ�豸ָ��:����)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetMouse() const;				// DirectInput Get DirectInput Device Mouse(~DirectInput��ȡ�豸ָ��:���)
	LPDIRECTINPUTDEVICE8			DIRECTINPUT_CALLMETHOD		GetJoyStick() const;			// DirectInput Get DirectInput Device JoyStick(~DirectInput��ȡ�豸ָ��:��Ϸ��)

public:
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance);																																																// DirectInput Initialize(KeyBoard&Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(��̨/�Ƕ�ռ)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, DWORD dwDeviceCoopFlags);																														// DirectInput Single Device Initialize(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags);																					// DirectInput Single Device Initialize(Overload + 2)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2);																						// DirectInput Multiple Device Initialize(Overload + 3)
	HRESULT							DIRECTINPUT_CALLMETHOD		Create(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_MUL_TYPE eDirectInputMulDevice_X, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags1, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDirectInputDeviceCoopFlags2);			// DirectInput Multiple Device Initialize(Overload + 4)

	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance);																																														// DirectInput Initialize(KeyBoard)(dwDeviceCoopFlags:DISCL_FOREGROUND | DISCL_EXCLUSIVE)(ǰ̨/��ռ)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);																																							// DirectInput Initialize(KeyBoard)(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateKeyBoard(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags);																																	// DirectInput Initialize(KeyBoard)(Overload + 2)

	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance);																																														// DirectInput Initialize(Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(��̨/�Ƕ�ռ)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);																																								// DirectInput Initialize(Mouse)(Overload + 1)
	HRESULT							DIRECTINPUT_CALLMETHOD		CreateMouse(HWND hWnd, HINSTANCE hInstance, E_DX_INPUT_DEVICE_COOPFLAGS_TYPE eDeviceCoopFlags);																																		// DirectInput Initialize(Mouse)(Overload + 2)
	
	void							DIRECTINPUT_CALLMETHOD		GetDeviceState();														// DirectInput Get Device State(KeyBoard&Mouse)
	void							DIRECTINPUT_CALLMETHOD		GetDeviceState(E_DX_INPUT_DEVICE_TYPE eDirectInputDevice_X);			// DirectInput Get Device State
	
	bool							DIRECTINPUT_CALLMETHOD		KeyBoardIsDown(int nKeyValue);											// DirectInput KeyBoard Is KeyDown(���̰�������)
	bool							DIRECTINPUT_CALLMETHOD		KeyBoardIsUp(int nKeyValue);											// DirectInput KeyBoard Is KeyUp(���̰����ͷ�)

	bool							DIRECTINPUT_CALLMETHOD		MouseIsDown(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton);				// DirectInput Mouse Is KeyDown(��갴������)
	bool							DIRECTINPUT_CALLMETHOD		MouseIsUp(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton);				// DirectInput Mouse Is KeyUp(��갴���ͷ�)
	
	float							DIRECTINPUT_CALLMETHOD		MouseGetX();															// DirectInput Mouse Get X Axis Value(��ȡ���X������)
	float							DIRECTINPUT_CALLMETHOD		MouseGetY();															// DirectInput Mouse Get Y Axis Value(��ȡ���Y������)
	float							DIRECTINPUT_CALLMETHOD		MouseGetZ();															// DirectInput Mouse Get Z Axis Value(Mouse Wheel)(��ȡ���Z��/��������)

	void							DIRECTINPUT_CALLMETHOD		KeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc);													// DirectInput KeyDown Proc(���̻ص�����)
	void							DIRECTINPUT_CALLMETHOD		MouseDownProc(E_DX_INPUT_MOUSE_STATE_TYPE eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc);			// DirectInput MouseDown Proc(���ص�����)
	
};

#endif