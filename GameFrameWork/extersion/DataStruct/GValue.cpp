#include "GValue.h"



GValue::GValue()
	:m_int(0), m_eType(GTYPE_NONE)
{

}

GValue::GValue(const GValue& val)
	:m_int(0), m_eType(val.m_eType)
{
	switch (m_eType)
	{
	case GTYPE_NONE:
	case GTYPE_CHAR:
	case GTYPE_BOOL:
	case GTYPE_INT:
	case GTYPE_FLOAT:
	case GTYPE_POINTER:
		m_int = val.m_int;
		break;
	case GTYPE_STRING:
		m_string = new GString(*val.m_string);
		break;
	case GTYPE_VALUEVECTOR:
		m_vector = new GValueVector(*val.m_vector);
		break;
	case GTYPE_VALUEMAP:
		m_map = new GValueMap(*val.m_map);
		break;
	default:
		break;
	}
}

GValue::GValue(GValue&& val)
	:m_int(0), m_eType(val.m_eType)
{
	switch (m_eType)
	{
	case GTYPE_NONE:
	case GTYPE_CHAR:
	case GTYPE_BOOL:
	case GTYPE_INT:
	case GTYPE_FLOAT:
	case GTYPE_POINTER:
		m_int = val.m_int;
		break;
	case GTYPE_STRING:
		m_string = new GString(std::move(*val.m_string));
		break;
	case GTYPE_VALUEVECTOR:
		m_vector = new GValueVector(std::move(*val.m_vector));
		break;
	case GTYPE_VALUEMAP:
		m_map = new GValueMap(std::move(*val.m_map));
		break;
	default:
		break;
	}
	val.reset();
}

GValue::GValue(char _ch)
	:m_char(_ch), m_eType(GTYPE_CHAR)
{

}

GValue::GValue(bool _b)
	: m_bool(_b), m_eType(GTYPE_BOOL)
{

}

GValue::GValue(int _i)
	:m_int(_i), m_eType(GTYPE_INT)
{

}

GValue::GValue(float _f)
	:m_float(_f), m_eType(GTYPE_FLOAT)
{

}

GValue::GValue(void* _p)
	:m_pointer(_p), m_eType(GTYPE_POINTER)
{

}

GValue::GValue(const char* _cstr)
	: m_string(new GString(_cstr)), m_eType(GTYPE_STRING)
{

}

GValue::GValue(const GString& _str)
	:m_string(new GString(_str)), m_eType(GTYPE_STRING)
{

}

GValue::GValue(GString&& _str)
	: m_string(new GString(std::move(_str))), m_eType(GTYPE_STRING)
{

}

GValue::GValue(const GValueVector& _vec)
	:m_vector(new GValueVector(_vec)), m_eType(GTYPE_VALUEVECTOR)
{}

GValue::GValue(GValueVector&& _vec)
	: m_vector(new GValueVector(std::move(_vec))), m_eType(GTYPE_VALUEVECTOR)
{

}

GValue::GValue(const GValueMap& _map)
	: m_map(new GValueMap(_map)), m_eType(GTYPE_VALUEMAP)
{

}

GValue::GValue(GValueMap&& _map)
	: m_map(new GValueMap(std::move(_map))), m_eType(GTYPE_VALUEMAP)
{

}

GValue::~GValue()
{
	reset();
}

void GValue::reset()
{
	switch (m_eType)
	{
	case GTYPE_NONE:
	case GTYPE_CHAR:
	case GTYPE_BOOL:
	case GTYPE_INT:
	case GTYPE_FLOAT:
	case GTYPE_POINTER:
		m_int = 0;
		break;
	case GTYPE_STRING:
		delete m_string;
		break;
	case GTYPE_VALUEVECTOR:
		delete m_vector;
		break;
	case GTYPE_VALUEMAP:
		delete m_map;
		break;
	default:
		break;
	}
	m_eType = GTYPE_NONE;
}

GValueType GValue::getType() const
{
	return m_eType;
}

bool GValue::isNone() const
{
	return m_eType == GTYPE_NONE;
}

char& GValue::asChar()
{
	return m_char;
}

char GValue::asChar() const
{
	return m_char;
}

bool& GValue::asBool()
{
	return m_bool;
}

bool GValue::asBool() const
{
	return m_bool;
}

int& GValue::asInt()
{
	return m_int;
}

int GValue::asInt() const
{
	return m_int;
}

float& GValue::asFloat()
{
	return m_float;
}

float GValue::asFloat() const
{
	return m_float;
}

void*& GValue::asPointer()
{
	return m_pointer;
}

void* GValue::asPointer() const
{
	return m_pointer;
}

GString& GValue::asString()
{
	return *m_string;
}

const GString& GValue::asString() const
{
	return *m_string;
}

GValueVector& GValue::asValueVector()
{
	return *m_vector;
}

const GValueVector& GValue::asValueVector() const
{
	return *m_vector;
}

GValueMap& GValue::asValueMap()
{
	return *m_map;
}

const GValueMap& GValue::asValueMap() const
{
	return *m_map;
}

GString GValue::getTypeString() const
{
	switch (m_eType)
	{
	case GTYPE_NONE:
		return "NONE";
	case GTYPE_CHAR:
		return "CHAR";
	case GTYPE_BOOL:
		return "BOOL";
	case GTYPE_INT:
		return "INT";
	case GTYPE_FLOAT:
		return "FLOAT";
	case GTYPE_STRING:
		return "STRING";
	case GTYPE_POINTER:
		return "POINTER";
	case GTYPE_VALUEVECTOR:
		return "ValueVector";
	case GTYPE_VALUEMAP:
		return "ValueMap";
	default:
		break;
	}

	return "";
}

const GValue& GValue::operator=(GValue&& val)
{
	reset();
	m_eType = val.m_eType;
	switch (m_eType)
	{
	case GTYPE_NONE:
	case GTYPE_CHAR:
	case GTYPE_BOOL:
	case GTYPE_INT:
	case GTYPE_FLOAT:
	case GTYPE_POINTER:
		m_int = val.m_int;
		break;
	case GTYPE_STRING:
		m_string = new GString(std::move(*val.m_string));
		break;
	case GTYPE_VALUEVECTOR:
		m_vector = new GValueVector(std::move(*val.m_vector));
		break;
	case GTYPE_VALUEMAP:
		m_map = new GValueMap(std::move(*val.m_map));
		break;
	default:
		break;
	}
	val.reset();
	return *this;
}

const GValue& GValue::operator=(const GValue& val)
{
	reset();
	m_eType = val.m_eType;
	switch (m_eType)
	{
	case GTYPE_NONE:
	case GTYPE_CHAR:
	case GTYPE_BOOL:
	case GTYPE_INT:
	case GTYPE_FLOAT:
	case GTYPE_POINTER:
		m_int = val.m_int;
		break;
	case GTYPE_STRING:
		m_string = new GString(*val.m_string);
		break;
	case GTYPE_VALUEVECTOR:
		m_vector = new GValueVector(*val.m_vector);
		break;
	case GTYPE_VALUEMAP:
		m_map = new GValueMap(*val.m_map);
		break;
	default:
		break;
	}
	return *this;
}


std::ostream& operator<<(std::ostream& os, const GValue& val) {
	static int RecursiveDepth = 0;
	++RecursiveDepth;
	
#define FILL_SPACE() \
for (int i = 0; i < RecursiveDepth; ++i) \
	os << " "; \
	os << val.getTypeString().c_str() << ":";

	FILL_SPACE();

	switch (val.m_eType)
	{
	case GTYPE_NONE:
		os<< "NONE" << std::endl;
		break;
	case GTYPE_CHAR:
		os<< val.asChar() << std::endl;
		break;
	case GTYPE_BOOL:
		if(val.asBool())
			os<< "true" << std::endl;
		else
			os << "false" << std::endl;
		break;
	case GTYPE_INT:
		os<< val.asInt() << std::endl;
		break;
	case GTYPE_FLOAT:
		os << val.asFloat() << std::endl;
		break;
	case GTYPE_POINTER:
		os << val.asPointer() << std::endl;
		break;
	case GTYPE_STRING:
		os << val.asString().c_str() << std::endl;
		break;
	case GTYPE_VALUEVECTOR:
	{
		auto itor = val.asValueVector().begin();
		os << std::endl;
		for (; itor != val.asValueVector().end(); ++itor)
			os << *itor;
	}
		break;
	case GTYPE_VALUEMAP:
	{
		auto itor = val.asValueMap().begin();
		os << std::endl;
		for (; itor != val.asValueMap().end(); ++itor)
		{
			for (int i = 0; i < RecursiveDepth + 1; ++i)
				os << " ";
			os << "key:" << itor->first.c_str() << std::endl;
			os << itor->second;
		}
	}
		break;
	default:
		break;
	}
	--RecursiveDepth;

	return os;
};