#include "GTexture.h"
#include "..\..\dxUtils.h"
#include "GResourceCache.h"



GTexture::GTexture()
	:GResource(GRESTYPE_TEXTURE),
	m_pTexture(nullptr), m_uWidth(0), m_uHeight(0), m_eFormat(D3DFMT_UNKNOWN)
{

}

GTexture::~GTexture()
{
	Deattach();
}

GTexture* GTexture::create(
	UINT width, 
	UINT height, 
	D3DFORMAT format /*= D3DFMT_A8R8G8B8*/, 
	DWORD usage /*= D3DUSAGE_RENDERTARGET*/, 
	D3DPOOL pool /*= D3DPOOL_DEFAULT*/)
{
	GTexture* ret = new GTexture();
	if (ret && ret->init(width, height, format, usage, pool))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

GTexture* GTexture::createFromFile(const char* path)
{
	GTexture* ret = _resourceCache->getTexture(path);
	if (ret)
		return ret;
	ret = new GTexture();
	if (ret && ret->init(path)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool GTexture::init(
	UINT width, UINT height, 
	D3DFORMAT format /*= D3DFMT_A8R8G8B8*/, 
	DWORD usage /*= D3DUSAGE_RENDERTARGET*/, 
	D3DPOOL pool /*= D3DPOOL_DEFAULT */)
{
	Deattach();
	D3DXCreateTexture(
		dxGetDevice(),
		width, height,
		1, usage,
		format,
		D3DPOOL_DEFAULT,
		&m_pTexture
		);

	m_uWidth = width;
	m_uHeight = height;
	m_eFormat = format;
	return true;
}

bool GTexture::init(const char* path)
{
	Deattach();
	D3DXIMAGE_INFO info = { 0 };
	D3DXCreateTextureFromFileExA(
		dxGetDevice(),
		path,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		nullptr,
		&m_pTexture
		);

	GASSERT(m_pTexture, "LoadTexture fail: %s", path);

	m_uWidth = info.Width;
	m_uHeight = info.Height;
	m_eFormat = D3DFMT_A8R8G8B8;

	setName(path);
	return true;
}

void GTexture::Attach(IDirect3DTexture9* texture)
{
	Deattach();
	if (texture == nullptr)
		return;

	m_pTexture = texture;
	D3DSURFACE_DESC desc;
	memset(&desc, 0, sizeof(D3DSURFACE_DESC));
	texture->GetLevelDesc(0, &desc);
	m_uWidth = desc.Width;
	m_uHeight = desc.Height;
	m_eFormat = desc.Format;
}

void GTexture::Deattach()
{
	SAFE_RELEASE_COM(m_pTexture);
	m_uWidth = m_uHeight = 0;
	m_eFormat = D3DFMT_UNKNOWN;
	setName("");
}

bool GTexture::SaveToFile(const char* path, D3DXIMAGE_FILEFORMAT imageFormat /*= D3DXIFF_PNG */)
{
	if (m_pTexture == nullptr)
		return false;
	return SUCCEEDED(
		D3DXSaveTextureToFileA(
			path,
			imageFormat,
			m_pTexture,
			nullptr
			)
		);
}

IDirect3DTexture9* GTexture::getTexture() const
{
	if (this == nullptr)
		return nullptr;
	return m_pTexture;
}
