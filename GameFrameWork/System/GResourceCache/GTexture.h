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

	//创建一个空纹理
	bool init(
		UINT width,
		UINT height, 
		D3DFORMAT format = D3DFMT_A8R8G8B8,
		DWORD usage = D3DUSAGE_RENDERTARGET, 
		D3DPOOL pool = D3DPOOL_DEFAULT
		);
	//从文件读取一个纹理
	bool init(const char* path);

	//挂载纹理
	void Attach(IDirect3DTexture9* texture);
	//卸载纹理
	void Deattach();

	//保存纹理到文件
	bool SaveToFile(const char* path, 
		D3DXIMAGE_FILEFORMAT imageFormat = D3DXIFF_PNG	);

	//得到纹理
	IDirect3DTexture9* getTexture() const;
private:
	IDirect3DTexture9*				m_pTexture;				//纹理指针接口
	UINT							m_uWidth;				//纹理宽
	UINT							m_uHeight;				//纹理高
	D3DFORMAT						m_eFormat;				//纹理格式
};
#endif