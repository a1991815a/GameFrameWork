#ifndef __ID3DERENDERTOTEXTURE__
#define __ID3DERENDERTOTEXTURE__
#include "ID3DEInterface.h"

class ID3DERenderToTexture: public ID3DEInterface {
	friend bool dxCreateRenderToTexture(
		ID3DERenderToTexture** pNewRtt,
		D3DFORMAT RenderFormat, 
		D3DFORMAT DepthFormat);
private:
	ID3DERenderToTexture();
	~ID3DERenderToTexture();
public:
	bool BeginTexture(IDirect3DTexture9* pRender, IDirect3DTexture9* pDepth = nullptr);
	bool EndTexture();
private:
	IDirect3DTexture9*			m_pRenderTexture;				//渲染纹理
	IDirect3DSurface9*			m_pRednerSurface;				//渲染表面
	IDirect3DSurface9*			m_pDepthSurface;				//深度表面

	IDirect3DSurface9*			m_pDestRenderSurface;			//目标渲染表面
	IDirect3DSurface9*			m_pDestDepthSurface;			//目标深度表面
	IDirect3DSurface9*			m_pOldRenderSurface;			//保存的原渲染表面
	IDirect3DSurface9*			m_pOldDepthSurface;				//保存的原深度表面
};

bool dxCreateRenderToTexture(
	ID3DERenderToTexture** pNewRtt,
	D3DFORMAT RenderFormat = D3DFMT_A32B32G32R32F, 
	D3DFORMAT DepthFormat = D3DFMT_R32F);
#endif