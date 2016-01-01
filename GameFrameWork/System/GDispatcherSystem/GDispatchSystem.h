#ifndef __DISPATCHSYSTEM__
#define __DISPATCHSYSTEM__
#include "../GSystem.h"
#include "GListener.h"

#define _dispatchSystem			GDispatchSystem::getInstance()

class GDispatchSystem: public GSystem, public SingleInstance<GDispatchSystem>{
	friend class GEvent;
	friend class GInputSystem;
public:
	GDispatchSystem();
	//��Ӽ�����
	void addListener(GListener* listener);
	//�Ƴ�������
	void removeListener(GListener* listener);
	//�Ƴ����м�����
	void removeAllListener();
	//������Ϣ
	void postEvent(GEventType type, DWORD dwData = 0, void* pData = nullptr);
	//������Ϣ
	void postEvent(GEventType type, unsigned short dwData1, unsigned short dwData2, void* pData = nullptr);

	//���Ͱ�����Ϣ
	void postKeyEvent(GKeyEventType kType, unsigned short key);

	//���������Ϣ
	void postMoustEvent(GMouseEventType mType);

	//�ַ���Ϣ
	void Loop();


	virtual bool Init() override;
	virtual void Destroy() override;

private:
	std::vector<GEvent*>	m_pEventVector;				//�¼�����
	ObjectPool<GEvent*>		m_pEventPool;				//�¼������
	Set<GListener*>
							m_pListenerSet;				//�����߼�
	Point					m_CurLocation;				//��ǰ���λ��
	Point					m_MoveLocation;				//�������ƫ��
	GString					m_strInput;					//����ѭ���������Ϣ
};
#endif