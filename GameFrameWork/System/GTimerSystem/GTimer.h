#ifndef __GTIMER__
#define __GTIMER__
#include "../../GameHeader.h"

class GTimer{
	friend class GTimerSystem;
public:
	GTimer();
	~GTimer();

	float getElapse() const;
	void Reset();
private:
	DWORD m_dwElapse;
};
#endif