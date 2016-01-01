#include "GTimerSystem.h"
#include <time.h>

#pragma warning(push)
#pragma warning(disable: 4244)

GTimerSystem::GTimerSystem()
	:GSystem(1, "GTimerSystem"),
	m_dwPreTime(0), m_dwCurTime(0), m_fTimerFactor(1.0f)
{

}

bool GTimerSystem::Init()
{
	m_dwPreTime = m_dwCurTime = GetTickCount();
	return true;
}

void GTimerSystem::Destroy()
{
	
}

float GTimerSystem::GetElapse() const
{
	return (float)(m_dwCurTime - m_dwPreTime) / CLOCKS_PER_SEC;
}

void GTimerSystem::Loop()
{
	m_dwPreTime = m_dwCurTime;
	m_dwCurTime = GetTickCount();
	DWORD delta = (m_dwCurTime - m_dwPreTime) * m_fTimerFactor;

	auto itor = m_pTimerSet.begin();
	for(; itor != m_pTimerSet.end(); ++itor)
		(*itor)->m_dwElapse += delta;
}

#pragma warning(pop)