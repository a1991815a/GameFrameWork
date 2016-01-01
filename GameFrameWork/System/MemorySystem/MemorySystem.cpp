#include "MemorySystem.h"



MemorySystem::MemorySystem()
	:GSystem(99999, "MemorySystem(内存管理系统)")
{

}

void MemorySystem::Loop()
{
	m_pPoolVector.back()->clear();
}

const MemoryPool* MemorySystem::getCurrentPool() const
{
	return m_pPoolVector.back();
}

MemoryPool* MemorySystem::getCurrentPool()
{
	return m_pPoolVector.back();
}

bool MemorySystem::Init()
{
	m_pPoolVector.reserve(10);
	new MemoryPool();
	m_pPoolVector.back()->m_pRefVector.reserve(160);
	return true;
}

void MemorySystem::Destroy()
{
	for (size_t i = 0; i < m_pPoolVector.size(); ++i)
		m_pPoolVector.at(i)->clear();
	delete m_pPoolVector.front();
}
