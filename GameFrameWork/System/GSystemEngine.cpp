#include "GSystemEngine.h"
#include "GTimerSystem/GTimerSystem.h"
#include "GInputSystem/GInputSystem.h"
#include "GDispatcherSystem/GDispatchSystem.h"
#include "MemorySystem/MemorySystem.h"



GSystemEngine::GSystemEngine()
{}

GSystemEngine::~GSystemEngine()
{}

void GSystemEngine::InitEngine()
{
	addSystem(GTimerSystem::getInstance());
	addSystem(GInputSystem::getInstance());
	addSystem(GDispatchSystem::getInstance());
	addSystem(MemorySystem::getInstance());
}

void GSystemEngine::Init()
{
	auto itor = m_pSystemVector.begin();
	for (; itor != m_pSystemVector.end(); ++itor)
	{
		GSystem* system = *itor;
		system->Init();
		LOG_D("启动子系统: %s, 优先级: %d", system->getSysName().c_str(), system->getPriority());
	}
}

void GSystemEngine::Destroy()
{
	auto itor = m_pSystemVector.rbegin();
	for (; itor != m_pSystemVector.rend(); ++itor)
	{
		GSystem* system = *itor;
		system->Destroy();
		LOG_D("销毁子系统: %s, 优先级: %d", system->getSysName().c_str(), system->getPriority());
	}
	m_pSystemVector.clear();
}

void GSystemEngine::addSystem( GSystem* system )
{
	m_pSystemVector.insert(system);
}

void GSystemEngine::removeSystem( GSystem* system )
{
	auto itor = m_pSystemVector.find(system);
	if(itor != m_pSystemVector.end())
	{
		(*itor)->Destroy();
		m_pSystemVector.erase(itor);
	}
}
