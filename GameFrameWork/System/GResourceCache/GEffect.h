#ifndef __GEFFECT__
#define __GEFFECT__
#include "GResource.h"

class GEffect: public GResource{
public:
	GEffect();
	~GEffect();


	static GEffect* createFromFile(const char* path);
	bool init(const char* path);
	
	void Attach(ID3DXEffect* pEffect);
	void Deattach();

	void setTechnique(const GString& technique);
	const GString& getTechnique() const;

	bool InitMatrix();
	bool BeginEffect(UINT* numPass);
	bool EndEffect();

	bool BeginPass(UINT pass);
	bool EndPass();

	ID3DXEffect* getEffect() const;
private:
	ID3DXEffect*			m_pEffect;			//特效文件接口
	GString					m_strTechnique;		//当前特效名字
};


#endif