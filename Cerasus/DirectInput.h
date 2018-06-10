/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectInput.h
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
#pragma once

#ifndef __DIRECTINPUT_H_
#define __DIRECTINPUT_H_

//Macro Definition
#ifdef  CERASUS_EXPORTS
#define DIRECTINPUT_API	__declspec(dllexport)
#else
#define DIRECTINPUT_API	__declspec(dllimport)
#endif

#define DIRECTINPUT_CALLMODE	__stdcall

//Class Definition
#define KEYBOARD_ARRAYSIZE	256	//KeyBoard Array Size(标准键盘数组大小256键)
#define JOYSTICK_ARRAYSIZE	80	//JoyStick Array Size(JoyStick游戏杆数组大小80键)

//DirectInput输入设备
enum DirectInputDevice
{
	DirectInputDevice_KeyBoard = 0,	//KeyBoard Device(键盘)
	DirectInputDevice_Mouse = 1,	//Mouse Device(鼠标)
	DirectInputDevice_JoyStick = 2, //JoyStick Device(游戏杆)
};

//DirectInput多输入设备
enum DirectInputMulDevice
{
	DirectInputDevice_KeyBoard_Mouse = 0,		//KeyBoard&Mouse(键盘&鼠标)
	DirectInputDevice_KeyBoard_JoyStick = 1,	//KeyBoard&JoyStick(键盘&游戏杆)
	DirectInputDevice_Mouse_JoyStick = 2,		//Mouse&JoyStick(鼠标&游戏杆)
};

//DirectInput设备协作级别
enum DirectInputDeviceCoopFlags
{
	DirectInputCoopFlags_ForeGround_Exclusive = 0,		//ForeGround_Exclusive(前台独占模式)
	DirectInputCoopFlags_ForeGround_NoExclusive = 1,	//ForeGround_NoExclusive(前台非独占模式)
	DirectInputCoopFlags_BackGround_NoExclusive = 2,	//BackGround_NoExclusive(后台非独占模式)
};

//DirectInput鼠标键值状态
enum DirectInputMouseState
{
	DIMouse_LeftButton = 0,		//MouseButton:Left(左键)
	DIMouse_RightButton = 1,	//MouseButton:Right(右键)
	DIMouse_MiddleButton = 2,	//MouseButton:Middle(中键)
};

//CallBack Function
typedef	void	(CALLBACK*LPCALLBACKKEYDOWNPROCFUNC)(void);				//键盘响应回调函数
typedef void	(CALLBACK*LPCALLBACKMOUSEDOWNPROCFUNC)(void);			//鼠标响应回调函数

//Class
class DIRECTINPUT_API DirectInput
{
private:
	LPDIRECTINPUT8 m_pDirectInput;	//IDirectInput8 Interface Pointer(IDirectInput8接口指针成员)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceKeyBoard;	//IDirectInputDevice8 Interface Pointer(KeyBoard Device)(IDirectInputDevice8接口设备指针:键盘)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceMouse;		//IDirectInputDevice8 Interface Pointer(Mouse Device)(IDirectInputDevice8接口设备指针:鼠标)
	LPDIRECTINPUTDEVICE8 m_pDirectInputDeviceJoyStick;	//IDirectInputDevice8 Interface Pointer(JoyStick Device)(IDirectInputDevice8接口设备指针:游戏杆)

	DIMOUSESTATE m_DIMouseState;	//Mouse State Struct(鼠标状态)
	DIJOYSTATE m_DIJoyStickState;	//JoyStick State Struct(游戏杆状态)
	char m_cKeyBoradBuffer[KEYBOARD_ARRAYSIZE]; //KeyBoard State Array(键盘状态)

	CRITICAL_SECTION m_cs;			//Thread Safe(CriticalSection)
	bool m_bThreadSafe;				//Thread Safe Status

public:
	DirectInput();	//DirectInput Constructor Function(构造函数)
	~DirectInput();	//DirectInput Destructor Function(析构函数)

	//DirectInput初始化
	HRESULT DIRECTINPUT_CALLMODE DirectInputInit(HWND hWnd, HINSTANCE hInstance);	//DirectInput Initialize(KeyBoard&Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)
	HRESULT DIRECTINPUT_CALLMODE DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DWORD dwDeviceCoopFlags);									//DirectInput Single Device Initialize
	HRESULT DIRECTINPUT_CALLMODE DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DWORD dwDeviceCoopFlags1, DWORD dwDeviceCoopFlags2);	//DirectInput Multiple Device Initialize
	HRESULT DIRECTINPUT_CALLMODE DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputDevice eDirectInputDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags);		//DirectInput Single Device Initialize
	HRESULT DIRECTINPUT_CALLMODE DirectInputInit(HWND hWnd, HINSTANCE hInstance, DirectInputMulDevice eDirectInputMulDevice_X, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags1, DirectInputDeviceCoopFlags eDirectInputDeviceCoopFlags2);	//DirectInput Multiple Device Initialize
	HRESULT DIRECTINPUT_CALLMODE DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance);	//DirectInput Initialize(KeyBoard)(dwDeviceCoopFlags:DISCL_FOREGROUND | DISCL_EXCLUSIVE)
	HRESULT DIRECTINPUT_CALLMODE DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);						//DirectInput Initialize(KeyBoard)
	HRESULT DIRECTINPUT_CALLMODE DirectInputKeyBoardInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags);	//DirectInput Initialize(KeyBoard)
	HRESULT DIRECTINPUT_CALLMODE DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance);													//DirectInput Initialize(Mouse)(dwDeviceCoopFlags:DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)
	HRESULT DIRECTINPUT_CALLMODE DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DWORD dwDeviceCoopFlags);							//DirectInput Initialize(Mouse)
	HRESULT DIRECTINPUT_CALLMODE DirectInputMouseInit(HWND hWnd, HINSTANCE hInstance, DirectInputDeviceCoopFlags eDeviceCoopFlags);		//DirectInput Initialize(Mouse)
	
	//DirectInput获取设备状态
	void DIRECTINPUT_CALLMODE DirectInputGetDeviceState(void) const;	//DirectInput Get Device State(KeyBoard&Mouse)
	void DIRECTINPUT_CALLMODE DirectInputGetDeviceState(DirectInputDevice eDirectInputDevice_X) const;	//DirectInput Get Device State
	
	//DirectInput检测(键盘/鼠标)按键状态
	bool DIRECTINPUT_CALLMODE DIKeyBoardIsDown(int nKeyValue) const;							//DirectInput KeyBoard Is KeyDown(键盘按键按下)
	bool DIRECTINPUT_CALLMODE DIKeyBoardIsUp(int nKeyValue) const;							//DirectInput KeyBoard Is KeyUp(键盘按键释放)
	bool DIRECTINPUT_CALLMODE DIMouseIsDown(DirectInputMouseState eDIMouse_XButton) const;	//DirectInput Mouse Is KeyDown(鼠标按键按下)
	bool DIRECTINPUT_CALLMODE DIMouseIsUp(DirectInputMouseState eDIMouse_XButton) const;		//DirectInput Mouse Is KeyUp(鼠标按键释放)
	
	//DirectInput获取鼠标坐标
	float DIRECTINPUT_CALLMODE DIMouseGetX(void) const;										//DirectInput Mouse Get X Axis Value(获取鼠标X轴坐标)
	float DIRECTINPUT_CALLMODE DIMouseGetY(void) const;										//DirectInput Mouse Get Y Axis Value(获取鼠标Y轴坐标)
	float DIRECTINPUT_CALLMODE DIMouseGetZ(void) const;										//DirectInput Mouse Get Z Axis Value(Mouse Wheel)(获取鼠标Z轴/滚轮坐标)
	
	//DirectInput(键盘/鼠标)回调函数
	void CALLBACK DIKeyDownProc(int nKeyValue, LPCALLBACKKEYDOWNPROCFUNC pCallBackKeyDownProc);									//DirectInput KeyDown Proc(键盘回调函数)
	void CALLBACK DIMouseDownProc(DirectInputMouseState eDIMouse_XButton, LPCALLBACKMOUSEDOWNPROCFUNC pCallBackMouseDownProc);	//DirectInput MouseDown Proc(鼠标回调函数)
};

#endif