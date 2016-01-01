#ifndef __GEVENT__
#define __GEVENT__
#include "../../GameHeader.h"
#include "GEventType.h"

//事件模型
class GEvent{
	friend class GDispatchSystem;
public:
	GEvent();
	virtual ~GEvent();

	//得到事件类型
	virtual GEventType getEventType() const;
	//得到当前鼠标位置
	const Point& getLocation() const;
	//得到鼠标位移
	const Point& getMouseMove() const;
	//得到当前输入内容
	const GString& getInput() const;
	//得到当前指针附加数据
	void* getPData() const;
	//得到当前DWORD附加数据
	DWORD getDwData() const;
	//得到高位数据
	unsigned short getHIData() const;
	//得到低位数据
	unsigned short getLOData() const;
private:
	GEventType					m_eEventType;			//事件
	void*						m_pData;				//void*型附加数据
	union {
		struct {
			unsigned short		m_stData[2];			//高低位附加数据
		};
		DWORD					m_dwData;				//DWORD型附加数据
	};
};
#endif