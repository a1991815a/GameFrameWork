#ifndef __GSYSTEM__
#define __GSYSTEM__
#include "../GameHeader.h"

class GSystem: nocopy
{
public:
	/**ϵͳ���캯��()
	*	priority:	���ȼ�
	*	name:		ϵͳ����(���ڵ���)
	*/
	GSystem(int priority, const GString& name)
		:m_iPriority(priority), m_strSysName(name)
	{};
	//����������
	virtual ~GSystem() {};
	//������ϵͳ����ʼ����Դ
	virtual bool Init() = 0;
	//ֹͣ��ϵͳ,���ͷ���Դ
	virtual void Destroy() = 0;

	//�õ����ȼ�(���ȼ�)
	inline int getPriority() const{
		return m_iPriority;
	};

	//����std::Set�ıȽϺ���, ���ȼ�Խ��Խ����ǰ��
	bool operator<(const GSystem& system){
		return m_iPriority > system.m_iPriority;
	};

	//�õ�ϵͳ����
	const GString& getSysName() const {
		return m_strSysName;
	}
private:
	const int			m_iPriority;			//��Ⱦ���ȼ�(Ҳ������ģ�������õ�λ��)
	const GString		m_strSysName;			//��ϵͳ����(���ڵ���)
};
#endif