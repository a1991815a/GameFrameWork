#ifndef __GLISTENER__
#define __GLISTENER__
#include <functional>
#include "GEvent.h"
#include "../MemorySystem/Ref.h"

//�������ص�����
typedef std::function<bool(GEvent*)> GListenerCall;

#define LISTENER_TRIGGER(FUNC, EVENT) if(FUNC != nullptr) return FUNC(EVENT)

//������ģ��
class GListener: public Ref{
public:
	GListener(GEventType type);
	virtual ~GListener();

	//�õ��������¼�����
	GEventType getListenType() const;
	//����д�Ĵ�������
	bool trigger(GEvent* e);
protected:
	//����д�Ĵ�������
	virtual bool _trigger(GEvent* e) = 0;
private:
	const GEventType			m_eEventType;			//�������¼�����
};
#endif