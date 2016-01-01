#ifndef __GKEYBOARDLISTENER__
#define __GKEYBOARDLISTENER__
#include "GListener.h"

class GKeyboardListener: public GListener{
public:
	CREATEINIT_FUNC(GKeyboardListener);

	GKeyboardListener();
	virtual bool _trigger(GEvent* e) override;


	GListenerCall		OnKeyDown;
	GListenerCall		OnKeyUp;
};
#endif