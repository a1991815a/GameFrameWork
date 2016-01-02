#ifndef __ID3DEDEFERREDRENDER__
#define __ID3DEDEFERREDRENDER__
#include "ID3DEInterface.h"

/**
*	延时渲染接口
*		功能:	用于生成当前场景的 坐标纹理, 法线纹理, 纹理坐标纹理, 深度纹理
*		优化:	可减少光照模型计算次数
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
	//开始延迟渲染
	bool BeginScene();
	//结束延迟渲染
	bool EndScene();

	//得到坐标纹理
	inline IDirect3DTexture9* getPositionTexture() const {
		return m_pPositionTexture;
	};
	//得到法线纹理
	inline IDirect3DTexture9* getNormalTexture() const {
		return m_pNormalTexture;
	};
	//得到纹理坐标纹理
	inline IDirect3DTexture9* getTexcoordTexture() const {
		return m_pTexcoordTexture;
	};
	//得到深度纹理
	inline IDirect3DTexture9* getDepthTexture() const {
		return m_pDepthTexture;
	}

	//保存到文件
	bool SaveToFile(
		const char* positionPath,
		const char* normalPath,
		const char* texcoordPath,
		const char* depthPath
		);
private:
	IDirect3DTexture9*			m_pPositionTexture;			//坐标纹理
	IDirect3DTexture9*			m_pNormalTexture;			//法线纹理(float4 第四位放置的是指针)
	IDirect3DTexture9*			m_pTexcoordTexture;			//纹理坐标 纹理, 可存储2组纹理坐标
	IDirect3DSurface9*			m_pPositionSurface;			//坐标表面
	IDirect3DSurface9*			m_pNormalSurface;			//法线表面
	IDirect3DSurface9*			m_pTexcoordSurface;			//纹理坐标表面

	IDirect3DTexture9*			m_pDepthTexture;			//深度纹理
	IDirect3DSurface9*			m_pDepthSurface;			//深度表面

	ID3DXEffect*				m_pDeferredEffect;			//用于延迟渲染的着色器

	IDirect3DSurface9*			m_pOldSurface0;				//0渲染表面
	IDirect3DSurface9*			m_pOldSurface1;				//1渲染表面
	IDirect3DSurface9*			m_pOldSurface2;				//2渲染表面
	IDirect3DSurface9*			m_pOldDepthSurface;			//保存的深度表面
};

//创建一个延迟渲染接口
bool dxCreateDeferredRender(
	ID3DEDeferredRender** pNewRender,						//输出接口
	const char* EffectPath,								//特效文件路径
	D3DFORMAT positionFormat = D3DFMT_A32B32G32R32F,		//坐标纹理格式
	D3DFORMAT normalFormat = D3DFMT_A32B32G32R32F,			//法线纹理格式
	D3DFORMAT texcoordFormat = D3DFMT_A32B32G32R32F,		//纹理坐标纹理格式
	D3DFORMAT depthFormat = D3DFMT_R32F					//深度纹理格式
	);
#endif