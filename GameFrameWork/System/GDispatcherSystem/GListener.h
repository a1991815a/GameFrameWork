#ifndef __GLISTENER__
#define __GLISTENER__
#include <functional>
#include "GEvent.h"
#include "../MemorySystem/Ref.h"

//监听器回调函数
typedef std::function<bool(GEvent*)> GListenerCall;

#define LISTENER_TRIGGER(FUNC, EVENT) if(FUNC != nullptr) return FUNC(EVENT)

//监听器模型
class GListener: public Ref{
public:
	GListener(GEventType type);
	virtual ~GListener();

	//得到监听的事件类型
	GEventType getListenType() const;
	//可重写的触发函数
	bool trigger(GEvent* e);
protected:
	//可重写的触发函数
	virtual bool _trigger(GEvent* e) = 0;
private:
	const GEventType			m_eEventType;			//监听的事件类型
};
#endif