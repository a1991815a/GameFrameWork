#ifndef __GRENDERSYSTEM__
#define __GRENDERSYSTEM__
#include <d3d9.h>
#include <d3dx9.h>
#include "System\GSystem.h"
#include "extersion\GExtersion.h"
#include "ID3DEDeferredRender.h"

class GRenderSystem: public GSystem{
public:
	static GRenderSystem* getInstance();
	static void destroyInstance();
private:
	static GRenderSystem* m_instance;
public:
	GRenderSystem();

	virtual bool Init() override;
	virtual void Destroy() override;

	friend	bool				dxInit(HWND hWnd);
	friend IDirect3DDevice9*	dxGetDevice();
	friend ID3DXEffect*			dxGetEffect();
	friend void					dxSetEffect(ID3DXEffect* pEffect);
	friend D3DVIEWPORT9			dxGetViewport();

	friend void					dxGetPresentParameters(D3DPRESENT_PARAMETERS* pParameters);

	//������غ���
	friend void					dxSetWorldMatrix(const D3DXMATRIX* pWorld);
	friend void					dxSetViewMatrix(const D3DXMATRIX* pView);
	friend void					dxSetProjMatrix(const D3DXMATRIX* pProj);
	friend const D3DXMATRIX*	dxGetWorldMatrix();
	friend const D3DXMATRIX*	dxGetViewMatrix();
	friend const D3DXMATRIX*	dxGetProjMatrix();
	friend const D3DXMATRIX*	dxGetWVPMatrix();

private:
	//�豸�ӿ�
	IDirect3D9*				m_pDirect3D9;				//d3d9�ӿ�(��һ�γ�ʼ��)
	IDirect3DDevice9*		m_pDevice;					//�豸�ӿ�(��һ�γ�ʼ��)

	D3DVIEWPORT9			m_Viewport;					//�ӿ�����

	//����
	D3DXMATRIX				m_mWVPMatrix;				//WVP����
	const D3DXMATRIX*		m_pWorldMatrix;				//�������(ָ������)
	D3DXMATRIX				m_mViewMatrix;				//���������
	D3DXMATRIX				m_mProjMatrix;				//ͶӰ����

	D3DPRESENT_PARAMETERS	m_PresentParameters;		//���ò���


	ID3DEDeferredRender*	m_pDeferredRender;			//��ʱ��Ⱦ��
};
#endif