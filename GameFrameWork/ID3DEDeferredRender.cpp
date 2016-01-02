#include "ID3DEDeferredRender.h"
#include "GameMacro.h"
#include "dxUtils.h"



ID3DEDeferredRender::ID3DEDeferredRender()
	:m_pPositionTexture(nullptr), m_pNormalTexture(nullptr), m_pTexcoordTexture(nullptr),
	m_pPositionSurface(nullptr), m_pNormalSurface(nullptr), m_pTexcoordSurface(nullptr),
	m_pDepthTexture(nullptr), m_pDepthSurface(nullptr),
	m_pDeferredEffect(nullptr),
	m_pOldSurface0(nullptr), m_pOldSurface1(nullptr), m_pOldSurface2(nullptr),
	m_pOldDepthSurface(nullptr)
{

}

ID3DEDeferredRender::~ID3DEDeferredRender()
{
	SAFE_RELEASE_COM(m_pPositionTexture);
	SAFE_RELEASE_COM(m_pNormalTexture);
	SAFE_RELEASE_COM(m_pTexcoordTexture);
	SAFE_RELEASE_COM(m_pDepthSurface);
	SAFE_RELEASE_COM(m_pDeferredEffect);
}

bool ID3DEDeferredRender::BeginScene()
{
	auto device = dxGetDevice();
	DX_FAILED(device->GetRenderTarget(0, &m_pOldSurface0));
	DX_FAILED(device->GetRenderTarget(1, &m_pOldSurface1));
	DX_FAILED(device->GetRenderTarget(2, &m_pOldSurface2));
	DX_FAILED(device->GetDepthStencilSurface(&m_pOldDepthSurface));
	
	DX_FAILED(device->SetRenderTarget(0, m_pPositionSurface));
	DX_FAILED(device->SetRenderTarget(1, m_pNormalSurface));
	DX_FAILED(device->SetRenderTarget(2, m_pTexcoordSurface));
	DX_FAILED(device->SetDepthStencilSurface(m_pDepthSurface));
	
	DX_FAILED(device->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		1.0f, 0));
	DX_FAILED(device->BeginScene());
	UINT numPass = 0;
	DX_FAILED(m_pDeferredEffect->Begin(&numPass, D3DXFX_DONOTSAVESTATE));
	DX_FAILED(m_pDeferredEffect->BeginPass(0));
	return true;
}

bool ID3DEDeferredRender::EndScene()
{
	auto device = dxGetDevice();

	DX_FAILED(m_pDeferredEffect->EndPass());
	DX_FAILED(m_pDeferredEffect->End());
	DX_FAILED(device->EndScene());
	DX_FAILED(device->SetRenderTarget(0, m_pOldSurface0));
	DX_FAILED(device->SetRenderTarget(1, m_pOldSurface1));
	DX_FAILED(device->SetRenderTarget(2, m_pOldSurface2));
	DX_FAILED(device->SetDepthStencilSurface(m_pOldDepthSurface));

	return true;
}

bool ID3DEDeferredRender::SaveToFile(
	const char* positionPath, 
	const char* normalPath, 
	const char* texcoordPath,
	const char* depthPath)
{
	DX_FAILED(D3DXSaveTextureToFileA(
		positionPath,
		D3DXIFF_PNG,
		m_pPositionTexture,
		nullptr
		));
	DX_FAILED(D3DXSaveTextureToFileA(
		normalPath,
		D3DXIFF_PNG,
		m_pNormalTexture,
		nullptr
		));
	DX_FAILED(D3DXSaveTextureToFileA(
		texcoordPath,
		D3DXIFF_PNG,
		m_pTexcoordTexture,
		nullptr
		));
	DX_FAILED(D3DXSaveTextureToFileA(
		depthPath,
		D3DXIFF_PNG,
		m_pDepthTexture,
		nullptr
		));

	return true;
}

bool dxCreateDeferredRender(
	ID3DEDeferredRender** pNewRender,
	const char* EffectPath,
	D3DFORMAT positionFormat /*= D3DFMT_A32B32G32R32F*/, 
	D3DFORMAT normalFormat /*= D3DFMT_A32B32G32R32F*/, 
	D3DFORMAT texcoordFormat /*= D3DFMT_A32B32G32R32F*/, 
	D3DFORMAT depthFormat /*= D3DFMT_R32F */)
{
	auto device = dxGetDevice();
	D3DVIEWPORT9 vp = dxGetViewport();
	ID3DEDeferredRender* pDeferredRender = new ID3DEDeferredRender();
	
	dxLoadEffect(EffectPath, &pDeferredRender->m_pDeferredEffect);

	DXCREATE_FAILED(D3DXCreateTexture(
		device,
		vp.Width, vp.Height,
		1,
		D3DUSAGE_RENDERTARGET,
		positionFormat,
		D3DPOOL_DEFAULT,
		&pDeferredRender->m_pPositionTexture
		), 
		pDeferredRender);

	DXCREATE_FAILED(D3DXCreateTexture(
		device,
		vp.Width, vp.Height,
		1,
		D3DUSAGE_RENDERTARGET,
		normalFormat,
		D3DPOOL_DEFAULT,
		&pDeferredRender->m_pNormalTexture
		),
		pDeferredRender);

	DXCREATE_FAILED(D3DXCreateTexture(
		device,
		vp.Width, vp.Height,
		1,
		D3DUSAGE_RENDERTARGET,
		texcoordFormat,
		D3DPOOL_DEFAULT,
		&pDeferredRender->m_pTexcoordTexture
		),
		pDeferredRender);

	DXCREATE_FAILED(D3DXCreateTexture(
		device,
		vp.Width, vp.Height,
		1,
		D3DUSAGE_RENDERTARGET,
		depthFormat,
		D3DPOOL_DEFAULT,
		&pDeferredRender->m_pDepthTexture
		),
		pDeferredRender);

	DXCREATE_FAILED(pDeferredRender->m_pPositionTexture->GetSurfaceLevel(0,
		&pDeferredRender->m_pPositionSurface), pDeferredRender);
	DXCREATE_FAILED(pDeferredRender->m_pNormalTexture->GetSurfaceLevel(0,
		&pDeferredRender->m_pNormalSurface), pDeferredRender);
	DXCREATE_FAILED(pDeferredRender->m_pTexcoordTexture->GetSurfaceLevel(0,
		&pDeferredRender->m_pTexcoordSurface), pDeferredRender);
	DXCREATE_FAILED(pDeferredRender->m_pDepthTexture->GetSurfaceLevel(0,
		&pDeferredRender->m_pDepthSurface), pDeferredRender);

	*pNewRender = pDeferredRender;

	return true;
}
