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
	//添加监听者
	void addListener(GListener* listener);
	//移除监听者
	void removeListener(GListener* listener);
	//移除所有监听者
	void removeAllListener();
	//发送消息
	void postEvent(GEventType type, DWORD dwData = 0, void* pData = nullptr);
	//发送消息
	void postEvent(GEventType type, unsigned short dwData1, unsigned short dwData2, void* pData = nullptr);

	//发送按键信息
	void postKeyEvent(GKeyEventType kType, unsigned short key);

	//发送鼠标信息
	void postMoustEvent(GMouseEventType mType);

	//分发消息
	void Loop();


	virtual bool Init() override;
	virtual void Destroy() override;

private:
	std::vector<GEvent*>	m_pEventVector;				//事件队列
	ObjectPool<GEvent*>		m_pEventPool;				//事件分配池
	Set<GListener*>
							m_pListenerSet;				//监听者集
	Point					m_CurLocation;				//当前鼠标位置
	Point					m_MoveLocation;				//本次鼠标偏移
	GString					m_strInput;					//本次循环输入的信息
};
#endif