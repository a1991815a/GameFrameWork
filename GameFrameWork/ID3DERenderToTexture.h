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
	IDirect3DTexture9*			m_pRenderTexture;				//��Ⱦ����
	IDirect3DSurface9*			m_pRednerSurface;				//��Ⱦ����
	IDirect3DSurface9*			m_pDepthSurface;				//��ȱ���

	IDirect3DSurface9*			m_pDestRenderSurface;			//Ŀ����Ⱦ����
	IDirect3DSurface9*			m_pDestDepthSurface;			//Ŀ����ȱ���
	IDirect3DSurface9*			m_pOldRenderSurface;			//�����ԭ��Ⱦ����
	IDirect3DSurface9*			m_pOldDepthSurface;				//�����ԭ��ȱ���
};

bool dxCreateRenderToTexture(
	ID3DERenderToTexture** pNewRtt,
	D3DFORMAT RenderFormat = D3DFMT_A32B32G32R32F, 
	D3DFORMAT DepthFormat = D3DFMT_R32F);
#endif