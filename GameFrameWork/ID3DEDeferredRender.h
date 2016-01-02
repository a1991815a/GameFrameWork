#ifndef __ID3DEDEFERREDRENDER__
#define __ID3DEDEFERREDRENDER__
#include "ID3DEInterface.h"

/**
*	��ʱ��Ⱦ�ӿ�
*		����:	�������ɵ�ǰ������ ��������, ��������, ������������, �������
*		�Ż�:	�ɼ��ٹ���ģ�ͼ������
*/
class ID3DEDeferredRender: public ID3DEInterface{
	friend bool dxCreateDeferredRender(
		ID3DEDeferredRender** pNewRender,
		const char* EffectPath,
		D3DFORMAT positionFormat,
		D3DFORMAT normalFormat,
		D3DFORMAT texcoordFormat,
		D3DFORMAT depthFormat
		);
private:
	ID3DEDeferredRender();
	~ID3DEDeferredRender();
public:
	//��ʼ�ӳ���Ⱦ
	bool BeginScene();
	//�����ӳ���Ⱦ
	bool EndScene();

	//�õ���������
	inline IDirect3DTexture9* getPositionTexture() const {
		return m_pPositionTexture;
	};
	//�õ���������
	inline IDirect3DTexture9* getNormalTexture() const {
		return m_pNormalTexture;
	};
	//�õ�������������
	inline IDirect3DTexture9* getTexcoordTexture() const {
		return m_pTexcoordTexture;
	};
	//�õ��������
	inline IDirect3DTexture9* getDepthTexture() const {
		return m_pDepthTexture;
	}

	//���浽�ļ�
	bool SaveToFile(
		const char* positionPath,
		const char* normalPath,
		const char* texcoordPath,
		const char* depthPath
		);
private:
	IDirect3DTexture9*			m_pPositionTexture;			//��������
	IDirect3DTexture9*			m_pNormalTexture;			//��������(float4 ����λ���õ���ָ��)
	IDirect3DTexture9*			m_pTexcoordTexture;			//�������� ����, �ɴ洢2����������
	IDirect3DSurface9*			m_pPositionSurface;			//�������
	IDirect3DSurface9*			m_pNormalSurface;			//���߱���
	IDirect3DSurface9*			m_pTexcoordSurface;			//�����������

	IDirect3DTexture9*			m_pDepthTexture;			//�������
	IDirect3DSurface9*			m_pDepthSurface;			//��ȱ���

	ID3DXEffect*				m_pDeferredEffect;			//�����ӳ���Ⱦ����ɫ��

	IDirect3DSurface9*			m_pOldSurface0;				//0��Ⱦ����
	IDirect3DSurface9*			m_pOldSurface1;				//1��Ⱦ����
	IDirect3DSurface9*			m_pOldSurface2;				//2��Ⱦ����
	IDirect3DSurface9*			m_pOldDepthSurface;			//�������ȱ���
};

//����һ���ӳ���Ⱦ�ӿ�
bool dxCreateDeferredRender(
	ID3DEDeferredRender** pNewRender,						//����ӿ�
	const char* EffectPath,								//��Ч�ļ�·��
	D3DFORMAT positionFormat = D3DFMT_A32B32G32R32F,		//���������ʽ
	D3DFORMAT normalFormat = D3DFMT_A32B32G32R32F,			//���������ʽ
	D3DFORMAT texcoordFormat = D3DFMT_A32B32G32R32F,		//�������������ʽ
	D3DFORMAT depthFormat = D3DFMT_R32F					//��������ʽ
	);
#endif