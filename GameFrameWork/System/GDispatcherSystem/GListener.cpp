#include "GListener.h"



GListener::GListener(GEventType type)
	:m_eEventType(type)
{

}

GListener::~GListener()
{

}

bool GListener::trigger(GEvent* e)
{
	if (e->getEventType() == m_eEventType)
		return this->_trigger(e);
	return false;
}
