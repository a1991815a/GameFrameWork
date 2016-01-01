#ifndef __GVALUE__
#define __GVALUE__
#include "GString.h"
#include <vector>
#include <unordered_map>

class GValue;
typedef std::vector<GValue>						GValueVector;
typedef std::unordered_map<GString, GValue>		GValueMap;

enum GValueType {
	GTYPE_NONE = 0,
	GTYPE_CHAR,
	GTYPE_BOOL,
	GTYPE_INT,
	GTYPE_FLOAT,
	GTYPE_STRING,
	GTYPE_POINTER,
	GTYPE_VALUEVECTOR,
	GTYPE_VALUEMAP
};

class GValue{
public:
	//默认构造为空
	GValue();
	//拷贝构造
	GValue(const GValue& val);
	//移动构造
	GValue(GValue&& val);
	//构造为char类型
	explicit GValue(char _ch);
	//构造为bool类型
	explicit GValue(bool _b);
	//构造为整形
	explicit GValue(int _i);
	//构造为单精度浮点类型
	explicit GValue(float _f);
	//构造为指针类型
	explicit GValue(void* _p);
	//构造为字符串类型
	explicit GValue(const char* _cstr);
	//构造为字符串类型
	explicit GValue(const GString& _str);
	//移动构造为字符串类型
	explicit GValue(GString&& _str);
	//构造为变长数组
	explicit GValue(const GValueVector& _vec);
	//移动构造变长数组
	explicit GValue(GValueVector&& _vec);
	//构造为关系型容器
	explicit GValue(const GValueMap& _map);
	//移动构造关系型容器
	explicit GValue(GValueMap&& _map);
	//析构函数
	~GValue();

	//赋值运算符
	const GValue& operator=(const GValue& val);
	//赋值运算符
	const GValue& operator=(GValue&& val);

	//重置容器为空
	void reset();
	//返回数据类型
	GValueType getType() const;
	//是否为空
	bool isNone() const;

	//作为字符输出
	char& asChar();
	//作为布尔值输出
	bool& asBool();
	//作为整形输出
	int& asInt();
	//作为浮点输出
	float& asFloat();
	//作为指针输出
	void*& asPointer();
	//作为字符串输出
	GString& asString();
	//作为数组容器输出
	GValueVector& asValueVector();
	//作为Map容器输出
	GValueMap& asValueMap();

	//作为字符输出
	char asChar() const;
	//作为整形输出
	int asInt() const;
	//作为布尔值输出
	bool asBool() const;
	//作为浮点输出
	float asFloat() const;
	//作为指针输出
	void* asPointer() const;
	//作为字符串输出
	const GString& asString() const;
	//作为数组容器输出
	const GValueVector& asValueVector() const;
	//作为Map容器输出
	const GValueMap& asValueMap() const;

	GString getTypeString() const;
	friend std::ostream& operator<<(std::ostream& os, const GValue& val);
private:
	union {
		char				m_char;				//字符
		bool				m_bool;				//布尔值
		int					m_int;				//整形
		float				m_float;			//单精度浮点型
		void*				m_pointer;			//指针
		GString*			m_string;			//字符串
		GValueVector*		m_vector;			//数组
		GValueMap*			m_map;				//关系型容器
	};
	GValueType m_eType;
};

//流输出运算符
std::ostream& operator<<(std::ostream& os, const GValue& val);

#endif