#include "GKeyboardListener.h"



GKeyboardListener::GKeyboardListener()
	:GListener(ET_KEYBOARD),
	OnKeyDown(nullptr), OnKeyUp(nullptr)
{

}

bool GKeyboardListener::_trigger(GEvent* e)
{
	switch (e->getHIData())
	{
	case KET_KEYDOWN:
		LISTENER_TRIGGER(OnKeyDown, e);
		break;
	case KET_KEYUP:
		LISTENER_TRIGGER(OnKeyUp, e);
		break;
	default:
		break;
	}
	return false;
}
