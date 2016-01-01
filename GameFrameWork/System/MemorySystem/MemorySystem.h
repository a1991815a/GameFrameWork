#ifndef __MEMORYSYSTEM__
#define __MEMORYSYSTEM__
#include "MemoryPool.h"
#include "../GSystem.h"

#define _memorySystem			MemorySystem::getInstance()

class MemorySystem: public GSystem, public SingleInstance<MemorySystem>{
	friend class Ref;
	friend class MemoryPool;
public:
	MemorySystem();

	//内存管理系统循环
	void Loop();
	//得到当前内存管理池
	const MemoryPool* getCurrentPool() const;
	//得到当前内存管理池
	MemoryPool* getCurrentPool();

	virtual bool Init() override;
	virtual void Destroy() override;
private:
	std::vector<MemoryPool*>		m_pPoolVector;			//内存池列表
};
#endif