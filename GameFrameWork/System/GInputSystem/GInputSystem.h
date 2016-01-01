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

	//��ü��̺�������Ȩ
	bool Acquire();
	//������̺�������Ȩ
	bool UnAcquire();
	//׼������ (��ȡ��ǰ�����������)
	bool ReadyData();
	//ִ��ѭ��
	void Loop();


	virtual bool Init() override;
	virtual void Destroy() override;

	//Windows��Ϣ����(�ص�����)
	bool InputProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	//�������̻���ָ��
	void SwapKeyBuf();
	//������껺��ָ��
	void SwapMouseBuf();
private:
	IDirectInput8*				m_pDInput;
	IDirectInputDevice8*		m_pKeyboardDevice;
	IDirectInputDevice8*		m_pMouseDevice;
	char*						m_pPreKeyBuf;				//��һ����갴��״̬
	char*						m_pCurKeyBuf;				//������갴��״̬
	DIMOUSESTATE2*				m_pPreMoustState;			//��һ�����״̬
	DIMOUSESTATE2*				m_pCurMouseState;			//�������״̬
};
#endif