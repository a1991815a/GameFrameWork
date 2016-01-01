#ifndef __GSYSTEM__
#define __GSYSTEM__
#include "../GameHeader.h"

class GSystem: nocopy
{
public:
	/**系统构造函数()
	*	priority:	优先级
	*	name:		系统名字(用于调试)
	*/
	GSystem(int priority, const GString& name)
		:m_iPriority(priority), m_strSysName(name)
	{};
	//虚析构函数
	virtual ~GSystem() {};
	//启动子系统，初始化资源
	virtual bool Init() = 0;
	//停止子系统,并释放资源
	virtual void Destroy() = 0;

	//得到优先级(优先级)
	inline int getPriority() const{
		return m_iPriority;
	};

	//用于std::Set的比较函数, 优先级越大越排在前面
	bool operator<(const GSystem& system){
		return m_iPriority > system.m_iPriority;
	};

	//得到系统名字
	const GString& getSysName() const {
		return m_strSysName;
	}
private:
	const int			m_iPriority;			//渲染优先级(也是在主模块中引用的位置)
	const GString		m_strSysName;			//子系统名称(用于调试)
};
#endif