#ifndef __DXUTILS__
#define __DXUTILS__
#include "GRenderSystem.h"

const D3DXMATRIX* dxGetUnitMatrix();


//内联最常用的函数
inline IDirect3DDevice9*	dxGetDevice() {
	return GRenderSystem::m_instance->m_pDevice;
};

//设置相关函数
bool				dxInit(HWND hWnd);
D3DVIEWPORT9		dxGetViewport();
void				dxGetPresentParameters(D3DPRESENT_PARAMETERS* pParameters);

//矩阵相关函数
void				dxSetWorldMatrix(const D3DXMATRIX* pWorld);
void				dxSetViewMatrix(const D3DXMATRIX* pView);
void				dxSetProjMatrix(const D3DXMATRIX* pProj);
const D3DXMATRIX*	dxGetWorldMatrix();
const D3DXMATRIX*	dxGetViewMatrix();
const D3DXMATRIX*	dxGetProjMatrix();
const D3DXMATRIX*	dxGetWVPMatrix();

//绘制函数
bool				dxBeginScene();
bool				dxEndScene();

//读取特效文件
void				dxLoadEffect(const char* path, ID3DXEffect** pNewEffect);
//读取网格文件
void				dxLoadMesh(const char* path, DWORD* numAttribute, ID3DXMesh** pNewMesh);
#endif