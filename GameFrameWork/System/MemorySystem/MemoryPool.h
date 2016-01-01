#ifndef __MEMORYPOOL__
#define __MEMORYPOOL__
#include "Ref.h"

class MemoryPool{
	friend class MemorySystem;
public:
	MemoryPool();
	~MemoryPool();

	//添加到内存管理池
	void push(Ref* ref);
	//清空管理池
	void clear();
private:
	std::vector<Ref*>		m_pRefVector;		//引用列表
};
#endif