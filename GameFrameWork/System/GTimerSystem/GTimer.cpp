#include "GTimer.h"
#include <time.h>
#include "GTimerSystem.h"



GTimer::GTimer()
	:m_dwElapse(0)
{
	GTimerSystem::getInstance()->m_pTimerSet.insert(this);
}

GTimer::~GTimer()
{
	GTimerSystem::getInstance()->m_pTimerSet.erase(this);
}

float GTimer::getElapse() const
{
	return (float)m_dwElapse / CLOCKS_PER_SEC;
}

void GTimer::Reset()
{
	m_dwElapse = 0;
}
