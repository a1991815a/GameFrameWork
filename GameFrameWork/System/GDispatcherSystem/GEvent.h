#ifndef __GEVENT__
#define __GEVENT__
#include "../../GameHeader.h"
#include "GEventType.h"

//�¼�ģ��
class GEvent{
	friend class GDispatchSystem;
public:
	GEvent();
	virtual ~GEvent();

	//�õ��¼�����
	virtual GEventType getEventType() const;
	//�õ���ǰ���λ��
	const Point& getLocation() const;
	//�õ����λ��
	const Point& getMouseMove() const;
	//�õ���ǰ��������
	const GString& getInput() const;
	//�õ���ǰָ�븽������
	void* getPData() const;
	//�õ���ǰDWORD��������
	DWORD getDwData() const;
	//�õ���λ����
	unsigned short getHIData() const;
	//�õ���λ����
	unsigned short getLOData() const;
private:
	GEventType					m_eEventType;			//�¼�
	void*						m_pData;				//void*�͸�������
	union {
		struct {
			unsigned short		m_stData[2];			//�ߵ�λ��������
		};
		DWORD					m_dwData;				//DWORD�͸�������
	};
};
#endif