#include "Ref.h"
#include "MemorySystem.h"


void Ref::autorelease()
{
	if (m_uReferenceCount & AUTORELEASE_FLAG)
		return;
	m_uReferenceCount |= AUTORELEASE_FLAG + 1;
	MemorySystem::getInstance()->getCurrentPool()->push(this);
};
