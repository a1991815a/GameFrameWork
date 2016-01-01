#include "GMouseListener.h"



GMouseListener::GMouseListener()
	:GListener(ET_MOUSE),
	OnLButtonDown(nullptr), OnLButtonUp(nullptr), 
	OnRButtonDown(nullptr), OnRButtonUp(nullptr),
	OnMouseMove(nullptr)
{

}

bool GMouseListener::_trigger(GEvent* e)
{
	switch (e->getHIData())
	{
	case MET_LBDOWN:
		LISTENER_TRIGGER(OnLButtonDown, e);
		break;
	case MET_LBUP:
		LISTENER_TRIGGER(OnLButtonUp, e);
		break;
	case MET_RBDOWN:
		LISTENER_TRIGGER(OnRButtonDown, e);
		break;
	case MET_RBUP:
		LISTENER_TRIGGER(OnRButtonUp, e);
		break;
	case MET_MOVE:
		LISTENER_TRIGGER(OnMouseMove, e);
		break;
	default:
		break;
	}

	return false;
}