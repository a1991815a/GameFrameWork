#include "MemoryPool.h"
#include "MemorySystem.h"



MemoryPool::MemoryPool()
{
	MemorySystem::getInstance()->m_pPoolVector.push_back(this);
}

MemoryPool::~MemoryPool()
{
	clear();
	MemorySystem::getInstance()->m_pPoolVector.pop_back();
}

void MemoryPool::push(Ref* ref)
{
	for (size_t i = 0; i < m_pRefVector.size(); ++i)
		if (m_pRefVector.at(i) == ref)
			return;
	m_pRefVector.push_back(ref);
}

void MemoryPool::clear()
{
	for (size_t i = 0; i < m_pRefVector.size(); ++i)
		m_pRefVector.at(i)->release();
	m_pRefVector.clear();
}
