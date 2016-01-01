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
	//Ĭ�Ϲ���Ϊ��
	GValue();
	//��������
	GValue(const GValue& val);
	//�ƶ�����
	GValue(GValue&& val);
	//����Ϊchar����
	explicit GValue(char _ch);
	//����Ϊbool����
	explicit GValue(bool _b);
	//����Ϊ����
	explicit GValue(int _i);
	//����Ϊ�����ȸ�������
	explicit GValue(float _f);
	//����Ϊָ������
	explicit GValue(void* _p);
	//����Ϊ�ַ�������
	explicit GValue(const char* _cstr);
	//����Ϊ�ַ�������
	explicit GValue(const GString& _str);
	//�ƶ�����Ϊ�ַ�������
	explicit GValue(GString&& _str);
	//����Ϊ�䳤����
	explicit GValue(const GValueVector& _vec);
	//�ƶ�����䳤����
	explicit GValue(GValueVector&& _vec);
	//����Ϊ��ϵ������
	explicit GValue(const GValueMap& _map);
	//�ƶ������ϵ������
	explicit GValue(GValueMap&& _map);
	//��������
	~GValue();

	//��ֵ�����
	const GValue& operator=(const GValue& val);
	//��ֵ�����
	const GValue& operator=(GValue&& val);

	//��������Ϊ��
	void reset();
	//������������
	GValueType getType() const;
	//�Ƿ�Ϊ��
	bool isNone() const;

	//��Ϊ�ַ����
	char& asChar();
	//��Ϊ����ֵ���
	bool& asBool();
	//��Ϊ�������
	int& asInt();
	//��Ϊ�������
	float& asFloat();
	//��Ϊָ�����
	void*& asPointer();
	//��Ϊ�ַ������
	GString& asString();
	//��Ϊ�����������
	GValueVector& asValueVector();
	//��ΪMap�������
	GValueMap& asValueMap();

	//��Ϊ�ַ����
	char asChar() const;
	//��Ϊ�������
	int asInt() const;
	//��Ϊ����ֵ���
	bool asBool() const;
	//��Ϊ�������
	float asFloat() const;
	//��Ϊָ�����
	void* asPointer() const;
	//��Ϊ�ַ������
	const GString& asString() const;
	//��Ϊ�����������
	const GValueVector& asValueVector() const;
	//��ΪMap�������
	const GValueMap& asValueMap() const;

	GString getTypeString() const;
	friend std::ostream& operator<<(std::ostream& os, const GValue& val);
private:
	union {
		char				m_char;				//�ַ�
		bool				m_bool;				//����ֵ
		int					m_int;				//����
		float				m_float;			//�����ȸ�����
		void*				m_pointer;			//ָ��
		GString*			m_string;			//�ַ���
		GValueVector*		m_vector;			//����
		GValueMap*			m_map;				//��ϵ������
	};
	GValueType m_eType;
};

//����������
std::ostream& operator<<(std::ostream& os, const GValue& val);

#endif