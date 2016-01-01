#ifndef __REF__
#define __REF__
#include "../../GameHeader.h"

#define AUTORELEASE_FLAG 0x80000000

#define SAFE_RELEASE(p) do{if(p) p->release(); p = nullptr;} while(0)
#define SAFE_RETAIN(p) do{if(p) p->retain();} while (0)

#define CREATE_FUNC(TYPE) \
static TYPE* create(){ \
	TYPE* ret = new TYPE();	\
	if(ret && ret->init())	\
	{	\
		ret->autorelease();	\
		return ret;	\
	}	\
	delete ret;	\
	return nullptr;	\
}

#define CREATEINIT_FUNC(TYPE) \
CREATE_FUNC(TYPE); \
bool init(){ \
	return true; \
}

class Ref{
public:
	Ref() 
		:m_uReferenceCount(0)
	{};
	virtual ~Ref() {
		m_uReferenceCount &= ~AUTORELEASE_FLAG;
		GASSERT(m_uReferenceCount == 0, "m_uReferenceCount != 0");
	};

	//�õ����ü���
	size_t getReferenceCount() const {
		return m_uReferenceCount;
	};
	//�����ڴ��Զ�����
	void autorelease();
	//�ͷ�����
	void release() {
		if (m_uReferenceCount & AUTORELEASE_FLAG && --m_uReferenceCount <= AUTORELEASE_FLAG)
			delete this;
	};
	//����+1
	void retain() {
		if(m_uReferenceCount & AUTORELEASE_FLAG)
			++m_uReferenceCount;
	};

private:
	size_t			m_uReferenceCount;
};
#endif