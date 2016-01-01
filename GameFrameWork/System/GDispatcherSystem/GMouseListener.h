#ifndef __GMOUSELISTENER__
#define __GMOUSELISTENER__
#include "GListener.h"


class GMouseListener: public GListener{
public:
	CREATEINIT_FUNC(GMouseListener);

	GMouseListener();
	virtual bool _trigger(GEvent* e) override;



	GListenerCall OnLButtonDown;					//����������
	GListenerCall OnLButtonUp;						//����������
	GListenerCall OnRButtonDown;					//����Ҽ�����
	GListenerCall OnRButtonUp;						//����Ҽ�����
	GListenerCall OnMouseMove;						//����ƶ�
};
#endif