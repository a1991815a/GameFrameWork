#ifndef __GRESOURCECACHE__
#define __GRESOURCECACHE__
#include "../../extersion/GExtersion.h"
#include "../GSystem.h"
#include "GResource.h"
#include "GTexture.h"
#include "GEffect.h"

#define _resourceCache			GResourceCache::getInstance()

class GResourceCache: public GSystem, public SingleInstance<GResourceCache>{
public:
	GResourceCache();
	~GResourceCache();
	GResource* getResource(const GString& key) const;
	GTexture* getTexture(const GString& key) const;
	GEffect* getEffect(const GString& key) const;

	void addResource(const GString& key, GResource* res);
	void removeResource(const GString& key);
	void removeResource(const GResource* res);
	void removeAll();

	bool isExistResource(const GString& key) const;

	virtual bool Init() override;

	virtual void Destroy() override;

private:
	Map<GString, GResource*> m_mResourceMap;			//×ÊÔ´ÈÝÆ÷
};
#endif