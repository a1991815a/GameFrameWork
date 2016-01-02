#include "GEffect.h"
#include "..\..\dxUtils.h"
#include "GResourceCache.h"
#include "..\..\GameMacro.h"



GEffect::GEffect()
	:GResource(GRESTYPE_EFFECT),
	m_pEffect(nullptr)
{
	
}

GEffect::~GEffect()
{
	SAFE_RELEASE_COM(m_pEffect);
}

GEffect* GEffect::createFromFile(const char* path)
{
	GEffect* ret = _resourceCache->getEffect(path);
	if (ret)
		return ret;
	ret = new GEffect();
	if (ret && ret->init(path))
	{
		ret->autorelease();
		_resourceCache->addResource(path, ret);
		return ret;
	}

	delete ret;
	return nullptr;
}

bool GEffect::init(const char* path)
{
	Deattach();
	dxLoadEffect(path, &m_pEffect);
	setName(path);
	return true;
}

void GEffect::Attach(ID3DXEffect* pEffect)
{
	Deattach();
	m_pEffect = pEffect;
}

void GEffect::Deattach()
{
	SAFE_RELEASE_COM(m_pEffect);
	m_strTechnique.clear();
	setName("");
}

void GEffect::setTechnique(const GString& technique)
{
	m_strTechnique = technique;
}

const GString& GEffect::getTechnique() const
{
	return m_strTechnique;
}

bool GEffect::InitMatrix()
{
	DX_FAILED(m_pEffect->SetTechnique(m_strTechnique.c_str()));
	DX_FAILED(m_pEffect->SetMatrix("WMatrix", dxGetWorldMatrix()));
	DX_FAILED(m_pEffect->SetMatrix("VMatrix", dxGetViewMatrix()));
	DX_FAILED(m_pEffect->SetMatrix("PMatrix", dxGetProjMatrix()));

	return true;
}

bool GEffect::BeginEffect(UINT* numPass)
{
	return SUCCEEDED(m_pEffect->Begin(numPass, D3DXFX_DONOTSAVESTATE));
}

bool GEffect::EndEffect()
{
	return SUCCEEDED(m_pEffect->End());
}

bool GEffect::BeginPass(UINT pass)
{
	return SUCCEEDED(m_pEffect->BeginPass(pass));
}

bool GEffect::EndPass()
{
	return SUCCEEDED(m_pEffect->EndPass());
}

ID3DXEffect* GEffect::getEffect() const
{
	if (this == nullptr)
		return nullptr;
	return m_pEffect;
}
