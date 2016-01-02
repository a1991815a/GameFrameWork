#include "dxUtils.h"
#include "System\GResourceCache\GEffect.h"
#include "System\GResourceCache\GTexture.h"

GEffect* pEffect = nullptr;
ID3DXMesh* pMesh = nullptr;
DWORD numAttribute = 0;
GTexture* pTexture = nullptr;


bool WinCreate(HWND hwnd) {
	dxInit(hwnd);
	pEffect = GEffect::createFromFile("Normal.fx");
	pTexture = GTexture::createFromFile("ILLIDAN.tga");
	D3DXLoadMeshFromXA(
		"illidan.X",
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		dxGetDevice(),
		nullptr, nullptr, nullptr,
		&numAttribute,
		&pMesh
		);


	return true;
};

void WinLoop() {
	bool result = true;
	result = dxBeginScene();
	pEffect->setTechnique("NormalShader");
	result = pEffect->InitMatrix();
	UINT numPass = 0;
	result = pEffect->BeginEffect(&numPass);
	pEffect->getEffect()->SetTexture("texture0", pTexture->getTexture());
	result = pEffect->BeginPass(0);
	{
		for (size_t i = 0; i < numAttribute; ++i)
			pMesh->DrawSubset(i);
	}
	result = pEffect->EndPass();
	result = pEffect->EndEffect();
	result = dxEndScene();
};