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

	//�ڴ����ϵͳѭ��
	void Loop();
	//�õ���ǰ�ڴ�����
	const MemoryPool* getCurrentPool() const;
	//�õ���ǰ�ڴ�����
	MemoryPool* getCurrentPool();

	virtual bool Init() override;
	virtual void Destroy() override;
private:
	std::vector<MemoryPool*>		m_pPoolVector;			//�ڴ���б�
};
#endif