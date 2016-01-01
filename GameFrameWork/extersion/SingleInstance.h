#ifndef __SINGLEINSTANCE__
#define __SINGLEINSTANCE__


//µ¥ÀýÄ£°å
template<typename _Class>
class SingleInstance{
public:
	static _Class* getInstance(){
		if(m_instance == nullptr)
			m_instance = new _Class();
		return m_instance;
	};
	static void destroyInstance(){
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	};
private:
	static _Class* m_instance;
};

template<typename _Class>
_Class* SingleInstance<_Class>::m_instance = nullptr;

#endif