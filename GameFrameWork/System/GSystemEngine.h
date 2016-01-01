#ifndef __GSYSTEMENGINE__
#define __GSYSTEMENGINE__
#include "../GameHeader.h"
#include "GSystem.h"
#include <set>

//系统管理引擎(用于控制子系统初始化和资源释放顺序)
class GSystemEngine: public SingleInstance<GSystemEngine>{
public:
	GSystemEngine();
	~GSystemEngine();

	//初始化子系统(添加子系统)
	void InitEngine();
	//初始化
	void Init();
	//销毁所有系统
	void Destroy();
	//添加子系统
	void addSystem(GSystem* system);
	//移除子系统
	void removeSystem(GSystem* system);
private:
	std::set<GSystem*>		m_pSystemVector;		//子系统优先级列表
};
#endif