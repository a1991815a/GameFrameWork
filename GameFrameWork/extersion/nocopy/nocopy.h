#ifndef __NOCOPY__
#define __NOCOPY__

class nocopy{
public:
	nocopy(){};
private:
	nocopy(const nocopy&);
	nocopy(nocopy&&);
};
#endif