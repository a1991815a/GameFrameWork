#ifndef __ID3DEINTERFACE__
#define __ID3DEINTERFACE__
#include <d3d9.h>
#include <d3dx9.h>
#include "GameMacro.h"



/**
*	D3DX9仿真接口(非COM组件)
*/
class ID3DEInterface{
protected:
	ID3DEInterface()
		:m_iReferenceCount(1)
	{};
	virtual ~ID3DEInterface() {};
public:
	size_t AddRef() {
		return ++m_iReferenceCount;
	};
	size_t Release() {
		if (--m_iReferenceCount == 0)
		{
			delete this;
			return 0;
		}
		return m_iReferenceCount;
	};
private:
	size_t m_iReferenceCount;
};
#endif