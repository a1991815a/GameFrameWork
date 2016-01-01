#ifndef __GMOUSELISTENER__
#define __GMOUSELISTENER__
#include "GListener.h"


class GMouseListener: public GListener{
public:
	CREATEINIT_FUNC(GMouseListener);

	GMouseListener();
	virtual bool _trigger(GEvent* e) override;



	GListenerCall OnLButtonDown;					//鼠标左键按下
	GListenerCall OnLButtonUp;						//鼠标左键弹起
	GListenerCall OnRButtonDown;					//鼠标右键按下
	GListenerCall OnRButtonUp;						//鼠标右键弹起
	GListenerCall OnMouseMove;						//鼠标移动
};
#endif