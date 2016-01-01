#ifndef __GINPUTSYSTEM__
#define __GINPUTSYSTEM__
#include "../GSystem.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "../../GApplication/GApplication.h"


#define GINPUT_KEYSIZE 256

#define _inputSystem		GInputSystem::getInstance()

class GInputSystem :
	public GWinProcessor,
	public GSystem, 
	public SingleInstance<GInputSystem>
{
public:
	GInputSystem();

	//获得键盘和鼠标控制权
	bool Acquire();
	//解除键盘和鼠标控制权
	bool UnAcquire();
	//准备数据 (获取当前键盘鼠标数据)
	bool ReadyData();
	//执行循环
	void Loop();


	virtual bool Init() override;
	virtual void Destroy() override;

	//Windows消息例程(回调函数)
	bool InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	//交换键盘缓冲指针
	void SwapKeyBuf();
	//交换鼠标缓冲指针
	void SwapMouseBuf();
private:
	IDirectInput8*				m_pDInput;
	IDirectInputDevice8*		m_pKeyboardDevice;
	IDirectInputDevice8*		m_pMouseDevice;
	char*						m_pPreKeyBuf;				//上一次鼠标按键状态
	char*						m_pCurKeyBuf;				//本次鼠标按键状态
	DIMOUSESTATE2*				m_pPreMoustState;			//上一次鼠标状态
	DIMOUSESTATE2*				m_pCurMouseState;			//本次鼠标状态
};
#endif