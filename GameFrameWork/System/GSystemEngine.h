#ifndef __GSYSTEMENGINE__
#define __GSYSTEMENGINE__
#include "../GameHeader.h"
#include "GSystem.h"
#include <set>

//ϵͳ��������(���ڿ�����ϵͳ��ʼ������Դ�ͷ�˳��)
class GSystemEngine: public SingleInstance<GSystemEngine>{
public:
	GSystemEngine();
	~GSystemEngine();

	//��ʼ����ϵͳ(�����ϵͳ)
	void InitEngine();
	//��ʼ��
	void Init();
	//��������ϵͳ
	void Destroy();
	//�����ϵͳ
	void addSystem(GSystem* system);
	//�Ƴ���ϵͳ
	void removeSystem(GSystem* system);
private:
	std::set<GSystem*>		m_pSystemVector;		//��ϵͳ���ȼ��б�
};
#endif