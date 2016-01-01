#ifndef __GTIMERSYSTEM__
#define __GTIMERSYSTEM__
#include "../GSystem.h"
#include "GTimer.h"
#include <unordered_set>

#define _timerSystem		GTimerSystem::getInstance()

class GTimerSystem: public SingleInstance<GTimerSystem>, public GSystem{
	friend class GTimer;
public:
	GTimerSystem();
	virtual bool Init();

	virtual void Destroy();

	float GetElapse() const;
	void Loop();


	
private:
	DWORD m_dwPreTime;
	DWORD m_dwCurTime;
	std::unordered_set<GTimer*>	m_pTimerSet;			//计时器集合
	float m_fTimerFactor;								//计时器因子
};
#endif