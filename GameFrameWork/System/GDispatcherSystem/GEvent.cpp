#include "GEvent.h"
#include "GDispatchSystem.h"



GEvent::GEvent()
	:m_eEventType(ET_NONE), m_dwData(0), m_pData(nullptr)
{

}

GEvent::~GEvent()
{}

GEventType GEvent::getEventType() const
{
	return m_eEventType;
}

const Point& GEvent::getLocation() const
{
	return GDispatchSystem::getInstance()->m_CurLocation;
}

const Point& GEvent::getMouseMove() const
{
	return GDispatchSystem::getInstance()->m_MoveLocation;
}

const GString& GEvent::getInput() const
{
	return GDispatchSystem::getInstance()->m_strInput;
}

void* GEvent::getPData() const
{
	return m_pData;
}

DWORD GEvent::getDwData() const
{
	return m_dwData;
}

unsigned short GEvent::getHIData() const
{
	return m_stData[0];
}

unsigned short GEvent::getLOData() const
{
	return m_stData[1];
}

