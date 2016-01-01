#ifndef __MEMORYPOOL__
#define __MEMORYPOOL__
#include "Ref.h"

class MemoryPool{
	friend class MemorySystem;
public:
	MemoryPool();
	~MemoryPool();

	//��ӵ��ڴ�����
	void push(Ref* ref);
	//��չ����
	void clear();
private:
	std::vector<Ref*>		m_pRefVector;		//�����б�
};
#endif