#ifndef __GRESOURCE__
#define __GRESOURCE__
#include "GResourceType.h"
#include "System/GSystemHeader.h"
#include "extersion/GExtersion.h"

class GResource: nocopy, public Ref{
public:
	GResource(GResourceType type)
		:m_eResourceType(type)
	{};

	inline const GString& getName() const{
		return m_strName;
	};

	GResourceType getType() const{
		return m_eResourceType;
	};

private:
	GString						m_strName;
	const GResourceType			m_eResourceType;
};
#endif