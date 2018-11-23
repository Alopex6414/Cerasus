/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectInput.h
* @brief	This Program is DirectInput DLL Project.
* @author	Alopex/Helium
* @version	v1.24a
* @date		2017-10-27	v1.00a	alopex	Create Project.
* @date		2017-12-3	v1.01a	alopex	Add Enum & Modify CallBack Function.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-01-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.22a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.23a	alopex	Add Get Members Function.
* @date		2018-11-23	v1.24a	alopex	Alter Call Method.
*/
#pragma once

#ifndef __DIRECTINPUT_H_
#define __DIRECTINPUT_H_

//Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTINPUT_API	__declspec(dllexport)
#else
#define DIRECTINPUT_API	__declspec(dllimport)
#endif

#define DIRECTINPUT_CALLMETHOD	__stdcall

//Class Definition
#define KEYBOARD_ARRAYSIZE	256	//KeyBoard Array Size(��׼���������С256��)
#define JOYSTICK_ARRAYSIZE	80	//JoyStick Array Size(JoyStick��Ϸ�������С80��)

//DirectInput�����豸
enum DirectInputDevice
{
	DirectInputDevice_KeyBoard = 0,	//KeyBoard Device(����)
	DirectInputDevice_Mouse = 1,	//Mouse Device(���)
	DirectInputDevice_JoyStick = 2, //JoyStick Device(��Ϸ��)
};

//DirectInput�������豸
enum DirectInputMulDevice
{
	DirectInputDevice_KeyBoard_Mouse = 0,		//KeyBoard&Mouse(����&���)
	DirectInputDevice_KeyBoard_JoyStick = 1,	//KeyBoard&JoyStick(����&��Ϸ��)
	DirectInputDevice_Mouse_JoyStick = 2,		//Mouse&JoyStick(���&��Ϸ��)
};

//DirectInput�豸Э������
enum DirectInputDeviceCoopFlags
{
	DirectInputCoopFlags_ForeGround_Exclusive = 0,		//ForeGround_Exclusive(ǰ̨��ռģʽ)
	DirectInputCoopFlags_ForeGround_NoExclusive = 1,	//ForeGround_NoExclusive(ǰ̨�Ƕ�ռģʽ)
	DirectInputCoopFlags_BackGround_NoExclusive = 2,	//BackGround_NoExclusive(��̨�Ƕ�ռģʽ)
};

//DirectInput����ֵ״̬
enum DirectInputMouseState
{
	DIMouse_LeftButton = 0,		//MouseButton:Left(���)
	DIMouse_RightButton = 1,	//MouseButton:Right(�Ҽ�)
	DIMouse_MiddleButton = 2,	//MouseButton:Middle(�м�)
};

//CallBack Function
typedef	void	(CALLBACK*LPCALLBACKKEYDOWNPROCFUNC)(void);				//������Ӧ�ص�����
typedef void	(CALLBACK*LPCALLBACKMOUSEDOWNPROCFUNC)(void);			//�����Ӧ�ص�����

//Class
class DIRECTINPUT_API DirectInput
{
private:
	LPDIRECTINPUT8 m_pDirectInput;	//IDirectInput8 Interface Pointer(IDirectInput8�ӿ�ָ���Ա)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceKeyBoard;	//IDirectInputDevice8 Interface Pointer(KeyBoard Device)(IDirectInputDevice8�ӿ��豸ָ��:����)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceMouse;		//IDirectInputDevice8 Interface Pointer(Mouse Device)(IDirectInputDevice8�ӿ��豸ָ��:���)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceJoyStick;	//IDirectInputDevice8 Interface Pointer(JoyStick Device)(IDirectInputDevice8�ӿ��豸ָ��:��Ϸ��)

	DIMOUSESTATE m_DIMouseState;				//Mouse State Struct(���״̬)
	DIJOYSTATE m_DIJoyStickState;				//JoyStick State Struct(��Ϸ��״̬)
	char m_cKeyBoradBuffer[KEYBOARD_ARRAYSIZE]; //KeyBoard State Array(����״̬)

	CRITICAL_SECTION m_cs;			//Thread Safe(CriticalSection)
	bool m_bThreadSafe;				//Thread Safe Status

public:
	DirectInput();	//DirectInput Constructor Function(���캯��)
	~DirectInput();	//DirectInput Destructor Function(��������)

	//DirectInput����
	LPDIRECTINPUT8 DIRECTINPUT_CALLMETHOD DirectInputGetInput(void) const;								//DirectInput Get DirectInput8(~DirectInput��ȡDirectInput8�ӿ�ָ��)
	LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInputGetInputDeviceKeyBoard(void) const;			//DirectInput Get DirectInput Device Keyboard(~DirectInput��ȡ�豸ָ��:����)
	LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInputGetInputDeviceMouse(void) const;				//DirectInput Get DirectInput Device Mouse(~DirectInput��ȡ�豸ָ��:���)
	LPDIRECTINPUTDEVICE8 DIRECTINPUT_CALLMETHOD DirectInputGetInputDeviceJoyStick(void) const;			//DirectInput Get DirectInput Device JoyStick(~DirectInput��ȡ�豸ָ��:��Ϸ��)

	//DirectInput����
	void DIRECTINPUT_CALLMETHOD DirectInputSetInput(LPDIRECTINPUT8 pDirectInput);											//DirectInput Set DirectInput8(~DirectInput����DirectInput8�ӿ�ָ��)
	void DIRECTINPUT_CALLMETHOD DirectInputSetInputDeviceKeyBoard(LPDIRECTINPUTDEVICE8 pDirectInputDeviceKeyBoard);			//DirectInput Set DirectInput Device Keyboard(~DirectInput�����豸ָ��:����)
	void DIRECTINPUT_CALLMETHOD DirectInputSetInputDeviceMouse(LPDIRECTINPUTDEVICE8 pDirectInputDeviceMouse);				//DirectInput Set DirectInput Device Mouse(~DirectInput�����豸ָ��:���)
	void DIRECTINPUT_CALLMETHOD DirectInputSetInputDeviceJoyStick(LPDIRECTINPUTDEVICE8 pDirectInputDeviceJoyStick);			//DirectInput Set DirectInput Device JoyStick(~DirectInput�����豸ָ��:��Ϸ��)

	//DirectInput��ʼ��
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputInit(HWND hWnd, HINSTANCE hInstance);																										//DirectInput Initialize(KeyBoard&Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(��̨/�Ƕ�ռ)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DWORD dwDeviceCoopFlags);									//DirectInput Single Device Initialize(����+1)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2);	//DirectInput Multiple Device Initialize(����+2)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags);		//DirectInput Single Device Initialize(����+3)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2);	//DirectInput Multiple Device Initialize(����+4)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance);													//DirectInput Initialize(KeyBoard)(dwDeviceCoopFlags:DISCL_FOREGROUND | DISCL_EXCLUSIVE)(ǰ̨/��ռ)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);						//DirectInput Initialize(KeyBoard)(����+1)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags);	//DirectInput Initialize(KeyBoard)(����+2)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance);													//DirectInput Initialize(Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)(��̨/�Ƕ�ռ)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);							//DirectInput Initialize(Mouse)(����+1)
	HRESULT DIRECTINPUT_CALLMETHOD DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags);		//DirectInput Initialize(Mouse)(����+2)
	
	//DirectInput��ȡ�豸״̬
	void DIRECTINPUT_CALLMETHOD DirectInputGetDeviceState(void) const;										//DirectInput Get Device State(KeyBoard&Mouse)
	void DIRECTINPUT_CALLMETHOD DirectInputGetDeviceState(DirectInputDevice eDirectInputDevice_X) const;	//DirectInput Get Device State
	
	//DirectInput���(����/���)����״̬
	bool DIRECTINPUT_CALLMETHOD DIKeyBoardIsDown(int nKeyValue) const;								//DirectInput KeyBoard Is KeyDown(���̰�������)
	bool DIRECTINPUT_CALLMETHOD DIKeyBoardIsUp(int nKeyValue) const;								//DirectInput KeyBoard Is KeyUp(���̰����ͷ�)
	bool DIRECTINPUT_CALLMETHOD DIMouseIsDown(DirectInputMouseState eDIMouse_XButton) const;		//DirectInput Mouse Is KeyDown(��갴������)
	bool DIRECTINPUT_CALLMETHOD DIMouseIsUp(DirectInputMouseState eDIMouse_XButton) const;			//DirectInput Mouse Is KeyUp(��갴���ͷ�)
	
	//DirectInput��ȡ�������
	float DIRECTINPUT_CALLMETHOD DIMouseGetX(void) const;											//DirectInput Mouse Get X Axis Value(��ȡ���X������)
	float DIRECTINPUT_CALLMETHOD DIMouseGetY(void) const;											//DirectInput Mouse Get Y Axis Value(��ȡ���Y������)
	float DIRECTINPUT_CALLMETHOD DIMouseGetZ(void) const;											//DirectInput Mouse Get Z Axis Value(Mouse Wheel)(��ȡ���Z��/��������)
	
	//DirectInput(����/���)�ص�����
	void CALLBACK DIKeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc);									//DirectInput KeyDown Proc(���̻ص�����)
	void CALLBACK DIMouseDownProc(DirectInputMouseState eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc);	//DirectInput MouseDown Proc(���ص�����)
};

#endif