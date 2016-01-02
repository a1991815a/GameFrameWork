#include "GRenderSystem.h"
#include "dxUtils.h"

GRenderSystem* GRenderSystem::m_instance = nullptr;

GRenderSystem* GRenderSystem::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new GRenderSystem();
	return m_instance;
}

void GRenderSystem::destroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

GRenderSystem::GRenderSystem()
	:GSystem(99999, "GRenderSystem: ‰÷»æœµÕ≥"),
	m_pDirect3D9(nullptr), m_pDevice(nullptr),
	m_Viewport( { 0 } ),
	m_mWVPMatrix(*dxGetUnitMatrix()),
	m_pWorldMatrix(dxGetUnitMatrix()),
	m_mViewMatrix(*dxGetUnitMatrix()),
	m_mProjMatrix(*dxGetUnitMatrix()),
	m_pDeferredRender(nullptr)
{}

bool GRenderSystem::Init()
{
	return true;
}

void GRenderSystem::Destroy()
{
	SAFE_RELEASE_COM(m_pDevice);
	SAFE_RELEASE_COM(m_pDirect3D9);
}
