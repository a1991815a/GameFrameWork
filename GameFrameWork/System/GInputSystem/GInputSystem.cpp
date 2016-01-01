#include "GInputSystem.h"
#include "../GDispatcherSystem/GDispatchSystem.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#pragma warning(push)
#pragma warning(disable: 4407)
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)

#define FAILED_THORW(cond, msg) \
while(FAILED(cond)) throw std::runtime_error(msg)

GInputSystem::GInputSystem()
	:GSystem(10, "GInputSystem(输入系统)"),
	m_pDInput(nullptr), m_pKeyboardDevice(nullptr), m_pMouseDevice(nullptr)
{

}

bool GInputSystem::Acquire()
{
	if (FAILED(m_pMouseDevice->Acquire()))
		return false;
	if (FAILED(m_pKeyboardDevice->Acquire()))
		return false;
	return true;
}

bool GInputSystem::UnAcquire()
{
	if (!m_pMouseDevice->Unacquire())
		return false;
	if (!m_pKeyboardDevice->Unacquire())
		return false;
	return true;
}

bool GInputSystem::Init()
{
	HRESULT result = S_OK;
	//DInput8接口创建
	{
		result = DirectInput8Create(
			GetModuleHandleA(nullptr),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8A,
			(void**)&m_pDInput,
			nullptr
			);
		FAILED_THORW(result, "DirectInput8Create");
	}
	
	//键盘设备创建
	{
		result = m_pDInput->CreateDevice(
			GUID_SysKeyboard,
			&m_pKeyboardDevice,
			nullptr
			);
		FAILED_THORW(result, "CreateDevice: Keyboard");
		result = m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		FAILED_THORW(result, "SetDataFormat: Keyboard");
		result = m_pKeyboardDevice->SetCooperativeLevel(
			dxGetApp()->getWindow(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
		FAILED_THORW(result, "SetCooperativeLevel: Keyboard");
	};

	//鼠标设备接口创建
	{
		result = m_pDInput->CreateDevice(
			GUID_SysMouse,
			&m_pMouseDevice,
			nullptr
			);
		FAILED_THORW(result, "CreateDevice: Mouse");
		result = m_pMouseDevice->SetDataFormat(&c_dfDIMouse2);
		FAILED_THORW(result, "SetDataFormat: Mouse");
		result = m_pMouseDevice->SetCooperativeLevel(
			dxGetApp()->getWindow(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
			);
		FAILED_THORW(result, "SetCooperativeLevel: Mouse");
	};

	//缓冲区创建
	{
		m_pPreKeyBuf = new char[GINPUT_KEYSIZE];
		m_pCurKeyBuf = new char[GINPUT_KEYSIZE];
		m_pPreMoustState = new DIMOUSESTATE2();
		m_pCurMouseState = new DIMOUSESTATE2();
		memset(m_pPreKeyBuf, 0, GINPUT_KEYSIZE);
		memset(m_pCurKeyBuf, 0, GINPUT_KEYSIZE);
		memset(m_pPreMoustState, 0, sizeof(DIMOUSESTATE2));
		memset(m_pCurMouseState, 0, sizeof(DIMOUSESTATE2));
	}

	//注册Windows消息例程
	dxGetApp()->RegisterProcess(this, GPROC_CALLBACK(GInputSystem::InputProcess));
// 	//获得权限
// 	Acquire();


	return true;
}

bool GInputSystem::ReadyData()
{
	HRESULT result = 0;
	
	result = m_pKeyboardDevice->GetDeviceState(GINPUT_KEYSIZE, (void*)m_pPreKeyBuf);
	if (FAILED(result))
		return false;
	SwapKeyBuf();
	result = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), (void*)m_pPreMoustState);
	if (FAILED(result))
		return false;
	SwapMouseBuf();

	return true;
}

void GInputSystem::Loop()
{
	if(!ReadyData())
		return;

	for (size_t i = 0; i < GINPUT_KEYSIZE; ++i)
	{
		if (m_pCurKeyBuf[i] & 0x80)								//本次按下 则发送按下信息
			_dispatchSystem->postKeyEvent(KET_KEYDOWN, i);
		else if (m_pPreKeyBuf[i] & 0x80)						//上次按下但本次弹起 则发送弹起信息
			_dispatchSystem->postKeyEvent(KET_KEYUP, i);
	}

	if (m_pCurMouseState->rgbButtons[0] & 0x80)						//左键
		_dispatchSystem->postMoustEvent(MET_LBDOWN);
	else if(m_pPreMoustState->rgbButtons[0] & 0x80)
		_dispatchSystem->postMoustEvent(MET_LBUP);

	if (m_pCurMouseState->rgbButtons[1] & 0x80)						//右键
		_dispatchSystem->postMoustEvent(MET_RBDOWN);
	else if (m_pPreMoustState->rgbButtons[1] & 0x80)
		_dispatchSystem->postMoustEvent(MET_RBUP);
	
	if (m_pCurMouseState->lX != 0 ||
		m_pCurMouseState->lY != 0)				//鼠标移动
	{
		_dispatchSystem->postMoustEvent(MET_MOVE);
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(dxGetApp()->getWindow(), &point);
		_dispatchSystem->m_CurLocation = Point(
			point.x,
			point.y
			);															//刷新消息分发的鼠标位置
	}

	_dispatchSystem->m_MoveLocation = Point(
		m_pCurMouseState->lX,
		m_pCurMouseState->lY
		);															//刷新消息分发的鼠标位移
}

void GInputSystem::Destroy()
{
	if (m_pKeyboardDevice)
		m_pKeyboardDevice->Unacquire();
	if (m_pMouseDevice)
		m_pMouseDevice->Unacquire();
	SAFE_RELEASE_COM(m_pMouseDevice);
	SAFE_RELEASE_COM(m_pKeyboardDevice);
	SAFE_RELEASE_COM(m_pDInput);

	SAFE_DELETE_ARRAY(m_pPreKeyBuf);
	SAFE_DELETE_ARRAY(m_pCurKeyBuf);
	SAFE_DELETE(m_pPreMoustState);
	SAFE_DELETE(m_pCurMouseState);
}

bool GInputSystem::InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_ACTIVATE && wParam == WA_ACTIVE)
	{
		bool result = Acquire();
		if (result)
		{
			LOG_D("Acquire: true");
			ReadyData();
		}
		else
			LOG_D("Acquire: false");
	}

	return false;
}

void GInputSystem::SwapKeyBuf()
{
	char* tmp_buf = m_pPreKeyBuf;
	m_pPreKeyBuf = m_pCurKeyBuf;
	m_pCurKeyBuf = tmp_buf;
}

void GInputSystem::SwapMouseBuf()
{
	DIMOUSESTATE2* tmp_mbuf = m_pPreMoustState;
	m_pPreMoustState = m_pCurMouseState;
	m_pCurMouseState = tmp_mbuf;
}



#pragma warning(pop)