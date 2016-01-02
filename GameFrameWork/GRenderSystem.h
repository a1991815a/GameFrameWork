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

	//矩阵相关函数
	friend void					dxSetWorldMatrix(const D3DXMATRIX* pWorld);
	friend void					dxSetViewMatrix(const D3DXMATRIX* pView);
	friend void					dxSetProjMatrix(const D3DXMATRIX* pProj);
	friend const D3DXMATRIX*	dxGetWorldMatrix();
	friend const D3DXMATRIX*	dxGetViewMatrix();
	friend const D3DXMATRIX*	dxGetProjMatrix();
	friend const D3DXMATRIX*	dxGetWVPMatrix();

private:
	//设备接口
	IDirect3D9*				m_pDirect3D9;				//d3d9接口(仅一次初始化)
	IDirect3DDevice9*		m_pDevice;					//设备接口(仅一次初始化)

	D3DVIEWPORT9			m_Viewport;					//视口属性

	//矩阵
	D3DXMATRIX				m_mWVPMatrix;				//WVP矩阵
	const D3DXMATRIX*		m_pWorldMatrix;				//世界矩阵(指针引用)
	D3DXMATRIX				m_mViewMatrix;				//摄像机矩阵
	D3DXMATRIX				m_mProjMatrix;				//投影矩阵

	D3DPRESENT_PARAMETERS	m_PresentParameters;		//设置参数


	ID3DEDeferredRender*	m_pDeferredRender;			//延时渲染器
};
#endif