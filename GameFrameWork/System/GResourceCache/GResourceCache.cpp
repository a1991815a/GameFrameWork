#include "GResourceCache.h"



GResourceCache::GResourceCache()
	:GSystem(1, "GResourceCache: ×ÊÔ´»º³å³Ø")
{

}

GResourceCache::~GResourceCache()
{}

GResource* GResourceCache::getResource(const GString& key) const
{
	auto itor = m_mResourceMap.find(key);
	if (itor == m_mResourceMap.end())
		return nullptr;
	return itor->second;
}

GTexture* GResourceCache::getTexture(const GString& key) const
{
	auto itor = m_mResourceMap.find(key);
	if (itor == m_mResourceMap.end())
		return nullptr;
	GASSERT(itor->second->getType() == GRESTYPE_TEXTURE, "getTexture: The Type is not Texture");
	return (GTexture*)itor->second;
}

GEffect* GResourceCache::getEffect(const GString& key) const
{
	auto itor = m_mResourceMap.find(key);
	if (itor == m_mResourceMap.end())
		return nullptr;
	GASSERT(itor->second->getType() == GRESTYPE_EFFECT, "getTexture: The Type is not Texture");
	return (GEffect*)itor->second;
}

void GResourceCache::addResource(const GString& key, GResource* res)
{
	auto itor = m_mResourceMap.find(key);
	if (itor != m_mResourceMap.end())
		LOG_W("%s has existed!", key.c_str());
	m_mResourceMap.insert(key, res);
}

void GResourceCache::removeResource(const GString& key)
{
	auto itor = m_mResourceMap.find(key);
	if (itor != m_mResourceMap.end())
		m_mResourceMap.erase(itor);
}

void GResourceCache::removeResource(const GResource* res)
{
	removeResource(res->getName());
}

void GResourceCache::removeAll()
{
	m_mResourceMap.clear();
}

bool GResourceCache::isExistResource(const GString& key) const
{
	auto itor = m_mResourceMap.find(key);
	return itor != m_mResourceMap.end();
}

bool GResourceCache::Init()
{
	
	return true;
}

void GResourceCache::Destroy()
{
	m_mResourceMap.clear();
}
