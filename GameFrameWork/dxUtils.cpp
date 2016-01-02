#include "dxUtils.h"
#include "GameMacro.h"

static const D3DXMATRIX s_UnitMatrix = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

#define DX_FAILED(result) \
if(FAILED(result)) return false;

const D3DXMATRIX* dxGetUnitMatrix()
{
	return &s_UnitMatrix;
}

bool dxInit(HWND hWnd)
{
	HRESULT result = S_OK;
	//创建渲染系统单例,并获得单例指针
	GRenderSystem* render = GRenderSystem::getInstance();
	
	//创建D3D接口
	render->m_pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//得到客户区大小
	RECT WindowRect = { 0 };
	::GetClientRect(hWnd, &WindowRect);
	long width = WindowRect.right - WindowRect.left;
	long height = WindowRect.bottom - WindowRect.top;

	//参数设置
	D3DPRESENT_PARAMETERS parameters = { 0 };
	parameters.hDeviceWindow = hWnd;
	parameters.Windowed = TRUE;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	parameters.BackBufferWidth = width;
	parameters.BackBufferHeight = height;
	parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	parameters.BackBufferCount = 1;
	parameters.EnableAutoDepthStencil = TRUE;
	parameters.AutoDepthStencilFormat = D3DFMT_D24S8;

	//创建设备
	result = render->m_pDirect3D9->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		nullptr,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&parameters,
		&render->m_pDevice
		);
	GASSERT(SUCCEEDED(result), "CreateDevice Fail!");

	//打开深度缓冲
	render->m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//保存参数
	render->m_PresentParameters = parameters;

	//创建延时渲染接口
	bool endCreate = dxCreateDeferredRender(
		&render->m_pDeferredRender,
		EFFECT_DEFERREDRENDER_PATH);

	GASSERT(endCreate, "dxCreateDeferredRender Fail!");

	D3DXMATRIX vMatrix;
	D3DXMATRIX pMatrix;
	D3DXMatrixLookAtLH(
		&vMatrix,
		&D3DXVECTOR3(0, 0, -10),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0)
		);
	D3DXMatrixPerspectiveFovLH(
		&pMatrix,
		D3DX_PI / 4,
		(float)width / height,
		1, 500
		);
	dxSetViewMatrix(&vMatrix);
	dxSetProjMatrix(&pMatrix);

	return SUCCEEDED(result);
}

D3DVIEWPORT9 dxGetViewport()
{
	return GRenderSystem::m_instance->m_Viewport;
}

void dxSetWorldMatrix(const D3DXMATRIX* pWorld)
{
	GRenderSystem::m_instance->m_pWorldMatrix = pWorld;
}

void dxSetViewMatrix(const D3DXMATRIX* pView)
{
	GRenderSystem::m_instance->m_mViewMatrix = *pView;
}

void dxSetProjMatrix(const D3DXMATRIX* pProj)
{
	GRenderSystem::m_instance->m_mProjMatrix = *pProj;
}

const D3DXMATRIX* dxGetWorldMatrix()
{
	return GRenderSystem::m_instance->m_pWorldMatrix;
}

const D3DXMATRIX* dxGetViewMatrix()
{
	return &GRenderSystem::m_instance->m_mViewMatrix;
}

const D3DXMATRIX* dxGetProjMatrix()
{
	return &GRenderSystem::m_instance->m_mProjMatrix;
}

const D3DXMATRIX* dxGetWVPMatrix()
{
	return &GRenderSystem::m_instance->m_mWVPMatrix;
}


void dxGetPresentParameters(D3DPRESENT_PARAMETERS* pParameters)
{
	*pParameters = GRenderSystem::m_instance->m_PresentParameters;
}

bool dxBeginScene()
{
	auto device = dxGetDevice();
	
	DX_FAILED(device->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f,
		0
		));
	DX_FAILED(device->BeginScene());
	return true;
}

bool dxEndScene()
{
	auto device = dxGetDevice();
	DX_FAILED(device->EndScene());
	DX_FAILED(device->Present(nullptr, nullptr, nullptr, nullptr));
	return true;
}

void dxLoadEffect(const char* path, ID3DXEffect** pNewEffect)
{
	ID3DXBuffer* errorBuf = nullptr;
	D3DXCreateEffectFromFileA(
		dxGetDevice(),
		path,
		nullptr, nullptr, EFFECT_FLAG, nullptr,
		pNewEffect, &errorBuf);
	if (errorBuf && errorBuf->GetBufferSize() > 1)
	{
		char* text = (char*)errorBuf->GetBufferPointer();
		OutputDebugStringA(text);
		OutputDebugStringA("\n");
		GASSERT(false, text);
	}
}
