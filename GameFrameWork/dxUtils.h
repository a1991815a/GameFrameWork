#ifndef __DXUTILS__
#define __DXUTILS__
#include "GRenderSystem.h"

const D3DXMATRIX* dxGetUnitMatrix();


//������õĺ���
inline IDirect3DDevice9*	dxGetDevice() {
	return GRenderSystem::m_instance->m_pDevice;
};

//������غ���
bool				dxInit(HWND hWnd);
D3DVIEWPORT9		dxGetViewport();
void				dxGetPresentParameters(D3DPRESENT_PARAMETERS* pParameters);

//������غ���
void				dxSetWorldMatrix(const D3DXMATRIX* pWorld);
void				dxSetViewMatrix(const D3DXMATRIX* pView);
void				dxSetProjMatrix(const D3DXMATRIX* pProj);
const D3DXMATRIX*	dxGetWorldMatrix();
const D3DXMATRIX*	dxGetViewMatrix();
const D3DXMATRIX*	dxGetProjMatrix();
const D3DXMATRIX*	dxGetWVPMatrix();

//���ƺ���
bool				dxBeginScene();
bool				dxEndScene();

//��ȡ��Ч�ļ�
void				dxLoadEffect(const char* path, ID3DXEffect** pNewEffect);
//��ȡ�����ļ�
void				dxLoadMesh(const char* path, DWORD* numAttribute, ID3DXMesh** pNewMesh);
#endif