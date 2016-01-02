#ifndef __GRESOURCE__
#define __GRESOURCE__
#include <d3d9.h>
#include <d3dx9.h>
#include "GResourceType.h"
#include "../../extersion/GExtersion.h"
#include "../MemorySystem/Ref.h"



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
protected:
	void setName(const GString& name) {
		m_strName = name;
	};
private:
	GString						m_strName;
	const GResourceType			m_eResourceType;
};
#endif