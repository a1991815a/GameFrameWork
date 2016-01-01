#include "GDispatchSystem.h"

#pragma warning(push)
#pragma warning(disable: 4244)

GDispatchSystem::GDispatchSystem()
	:GSystem(1000, "DispatchSystem(消息分发系统)")
{}

void GDispatchSystem::addListener(GListener* listener)
{
	m_pListenerSet.insert(listener);
}

void GDispatchSystem::removeListener(GListener* listener)
{
	m_pListenerSet.erase(listener);
}

void GDispatchSystem::removeAllListener()
{
	m_pListenerSet.clear();
}

void GDispatchSystem::postEvent(GEventType type, DWORD dwData /*= 0*/, void* pData /*= nullptr*/)
{
	GEvent* e = m_pEventPool.allocate();
	e->m_eEventType = type;
	e->m_dwData = dwData;
	e->m_pData = pData;
	m_pEventVector.push_back(e);
}

void GDispatchSystem::postEvent(GEventType type, unsigned short dwData1, unsigned short dwData2, void* pData /*= nullptr*/)
{
	GEvent* e = m_pEventPool.allocate();
	e->m_eEventType = type;
	e->m_stData[0] = dwData1;
	e->m_stData[1] = dwData2;
	e->m_pData = pData;
	m_pEventVector.push_back(e);
}

void GDispatchSystem::postKeyEvent(GKeyEventType kType, unsigned short key)
{
	postEvent(ET_KEYBOARD, kType, key, nullptr);
}

void GDispatchSystem::postMoustEvent(GMouseEventType mType)
{
	postEvent(ET_MOUSE, mType);
}

void GDispatchSystem::Loop()
{
	auto event_itor = m_pEventVector.begin();
	for (; event_itor != m_pEventVector.end(); ++event_itor)
	{
		auto listener_itor = m_pListenerSet.begin();
		for (; listener_itor != m_pListenerSet.end(); ++listener_itor)
			if((*listener_itor)->trigger(*event_itor))
				break;
	}
	m_pEventVector.clear();
	m_pEventPool.freeAll();
}

bool GDispatchSystem::Init()
{
	m_pEventVector.reserve(160);
	m_pEventPool.reserve(160);

	POINT point = { 0 };
	::GetCursorPos(&point);
	ScreenToClient(dxGetApp()->getWindow(), &point);
	m_CurLocation = Point(point.x, point.y);

	return true;
}

void GDispatchSystem::Destroy()
{
	removeAllListener();
}


#pragma warning(pop)