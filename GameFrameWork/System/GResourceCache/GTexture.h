#ifndef __GTEXTURE__
#define __GTEXTURE__
#include "GResource.h"

class GTexture: public GResource{
public:
	GTexture();
	~GTexture();
	
	static GTexture* create(
		UINT width,
		UINT height,
		D3DFORMAT format = D3DFMT_A8R8G8B8,
		DWORD usage = D3DUSAGE_RENDERTARGET,
		D3DPOOL pool = D3DPOOL_DEFAULT);

	static GTexture* createFromFile(const char* path);

	//����һ��������
	bool init(
		UINT width,
		UINT height, 
		D3DFORMAT format = D3DFMT_A8R8G8B8,
		DWORD usage = D3DUSAGE_RENDERTARGET, 
		D3DPOOL pool = D3DPOOL_DEFAULT
		);
	//���ļ���ȡһ������
	bool init(const char* path);

	//��������
	void Attach(IDirect3DTexture9* texture);
	//ж������
	void Deattach();

	//���������ļ�
	bool SaveToFile(const char* path, 
		D3DXIMAGE_FILEFORMAT imageFormat = D3DXIFF_PNG	);

	//�õ�����
	IDirect3DTexture9* getTexture() const;
private:
	IDirect3DTexture9*				m_pTexture;				//����ָ��ӿ�
	UINT							m_uWidth;				//�����
	UINT							m_uHeight;				//�����
	D3DFORMAT						m_eFormat;				//�����ʽ
};
#endif