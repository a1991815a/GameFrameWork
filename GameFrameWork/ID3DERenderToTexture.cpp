#include "ID3DERenderToTexture.h"
#include "dxUtils.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


ID3DERenderToTexture::ID3DERenderToTexture()
	:m_pRenderTexture(nullptr), m_pRednerSurface(nullptr), m_pDepthSurface(nullptr),
	m_pDestRenderSurface(nullptr), m_pDestDepthSurface(nullptr),
	m_pOldRenderSurface(nullptr), m_pOldDepthSurface(nullptr)
{

}

ID3DERenderToTexture::~ID3DERenderToTexture()
{
	if (m_pRenderTexture)
		m_pRenderTexture->Release();
	if (m_pDepthSurface)
		m_pDepthSurface->Release();
}

bool ID3DERenderToTexture::BeginTexture(IDirect3DTexture9* pRender, IDirect3DTexture9* pDepth /*= nullptr*/)
{
	auto device = dxGetDevice();
	if (pRender)
		pRender->GetSurfaceLevel(0, &m_pDestRenderSurface);
	if (pDepth)
		pDepth->GetSurfaceLevel(0, &m_pDestDepthSurface);
	DX_FAILED(device->GetRenderTarget(0, &m_pOldRenderSurface));
	DX_FAILED(device->GetDepthStencilSurface(&m_pOldDepthSurface));
	DX_FAILED(device->SetRenderTarget(0, m_pRednerSurface));
	DX_FAILED(device->SetDepthStencilSurface(m_pDepthSurface));
	DX_FAILED(device->Clear(0, nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));
	DX_FAILED(device->BeginScene());

	return true;
}

bool ID3DERenderToTexture::EndTexture()
{
	auto device = dxGetDevice();

	DX_FAILED(device->EndScene());
	DX_FAILED(device->SetRenderTarget(0, m_pOldRenderSurface));
	DX_FAILED(device->SetDepthStencilSurface(m_pOldDepthSurface));

	if (m_pDestRenderSurface)
	{
		DX_FAILED(D3DXLoadSurfaceFromSurface(
			m_pDestRenderSurface, nullptr, nullptr,
			m_pRednerSurface, nullptr, nullptr,
			D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 0, 0)
			));
		m_pDestRenderSurface = nullptr;
	}

	if (m_pDestDepthSurface)
	{
		DX_FAILED(D3DXLoadSurfaceFromSurface(
			m_pDestDepthSurface, nullptr, nullptr,
			m_pDepthSurface, nullptr, nullptr,
			D3DX_DEFAULT, D3DCOLOR_ARGB(0, 0, 0, 0)
			));
		m_pDestDepthSurface = nullptr;
	}

	return true;
}

bool dxCreateRenderToTexture(
	ID3DERenderToTexture** pNewRtt,
	D3DFORMAT RenderFormat /*= D3DFMT_A32B32G32R32F*/, 
	D3DFORMAT DepthFormat /*= D3DFMT_R32F*/)
{
	ID3DERenderToTexture* pRtt = new ID3DERenderToTexture();
	D3DVIEWPORT9 vp = dxGetViewport();
	HRESULT result = S_OK;
	result = D3DXCreateTexture(
		dxGetDevice(),
		vp.Width, vp.Height,
		1,
		D3DUSAGE_RENDERTARGET,
		RenderFormat,
		D3DPOOL_DEFAULT,
		&pRtt->m_pRenderTexture
		);
	
	DXCREATE_FAILED(result, pRtt);

	result = dxGetDevice()->CreateDepthStencilSurface(
		vp.Width, vp.Height,
		DepthFormat,
		D3DMULTISAMPLE_NONE,
		0,
		FALSE,
		&pRtt->m_pDepthSurface,
		nullptr
		);
	DXCREATE_FAILED(result, pRtt);

	*pNewRtt = pRtt;

	return true;
}
