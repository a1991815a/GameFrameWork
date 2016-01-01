#ifndef __GSTRING__
#define __GSTRING__
#include <string>
#include <unordered_map>
#include <stdarg.h>

#define FORMAT_ONCE(DST, FORMAT, VAL) \
char text[36] = { 0 }; \
sprintf_s(text, FORMAT, VAL); \
(DST).operator+=(text)


template<typename _Elem>
class GBasic_String:
	public std::basic_string<_Elem>
{

public:
	typedef	std::basic_string<_Elem>							_Mybase;
	typedef GBasic_String<_Elem>								_Myt;
	typedef _Elem												value_type;
	typedef typename _Mybase::difference_type					difference_type;
	typedef typename _Mybase::traits_type						traits_type;
	typedef typename _Mybase::allocator_type					allocator_type;
	typedef typename _Mybase::size_type							size_type;
	typedef typename _Mybase::pointer							pointer;
	typedef typename _Mybase::const_pointer						const_pointer;
	typedef typename _Mybase::reference							reference;
	typedef typename _Mybase::const_reference					const_reference;
	typedef typename _Mybase::iterator							iterator;
	typedef typename _Mybase::const_iterator					const_iterator;
	typedef typename _Mybase::reverse_iterator					reverse_iterator;
	typedef typename _Mybase::const_reverse_iterator			const_reverse_iterator;
	typedef std::hash<_Mybase>									hasher;
public:
	GBasic_String()
		:_Mybase()
	{};

	GBasic_String(const _Mybase& baseStr)
		:_Mybase(baseStr)
	{};

	GBasic_String(_Mybase&& baseStr)
		:_Mybase(std::move(baseStr))
	{};

	GBasic_String(const _Myt& str)
		:_Mybase(str)
	{};
	GBasic_String(_Myt&& str)
		:_Mybase(std::move(str))
	{};
	GBasic_String(const _Elem* str)
		:_Mybase(str)
	{};
	GBasic_String(const _Elem *_Ptr, size_t _Count)
		: _Mybase(_Ptr, _Count)
	{};
	GBasic_String(size_t _Count, _Elem _Ch)
		: _Mybase(_Count, _Ch)
	{};
	~GBasic_String()
	{};

	static GBasic_String number(int _Val) {
		GBasic_String str;
		FORMAT_ONCE(str, "%d", _Val);
		return std::move(str);
	};
	static GBasic_String number(size_t _Val) {
		GBasic_String str;
		FORMAT_ONCE(str, "%d", _Val);
		return std::move(str);
	};
	static GBasic_String number(float _Val) {
		GBasic_String str;
		FORMAT_ONCE(str, "%f", _Val);
		return std::move(str);
	};
	static GBasic_String number(double _Val) {
		GBasic_String str;
		FORMAT_ONCE(str, "%lf", _Val);
		return std::move(str);
	};

	const GBasic_String operator=(const GBasic_String<_Elem>& _val) {
		this->_Mybase::operator=(_val);
		return *this;
	};

	GBasic_String operator+(const GBasic_String<_Elem>& _Val) const{
		GBasic_String str = *this;
		str._Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+=(const GBasic_String<_Elem>& _Val){
		this->_Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+(const _Elem* _Val) const {
		GBasic_String str = *this;
		str._Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+=(const _Elem* _Val) {
		this->_Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+(_Elem _Val) const {
		GBasic_String str = *this;
		str._Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+=(_Elem _Val) {
		this->_Mybase::operator+=(_Val);
		return *this;
	};

	GBasic_String operator+(int _Val) const{
		GBasic_String str = *this;
		FORMAT_ONCE(str, "%d", _Val);
		return std::move(str);
	};
	GBasic_String operator+(size_t _Val) const{
		GBasic_String str = *this;
		FORMAT_ONCE(str, "%d", _Val);
		return std::move(str);
	};
	GBasic_String operator+(float _Val) const{
		GBasic_String str = *this;
		FORMAT_ONCE(str, "%f", _Val);
		return std::move(str);
	};;
	GBasic_String operator+(double _Val) const{
		GBasic_String str = *this;
		FORMAT_ONCE(str, "%lf", _Val);
		return std::move(str);
	};;
	const GBasic_String& operator+=(int _Val){
		FORMAT_ONCE(*this, "%d", _Val);
		return *this;
	};

	const GBasic_String& operator+=(size_t _Val) const{
		FORMAT_ONCE(*this, "%u", _Val);
		return *this;
	};

	const GBasic_String& operator+=(float _Val){
		FORMAT_ONCE(*this, "%f", _Val);
		return *this;
	};
	const GBasic_String& operator+=(double _Val){
		FORMAT_ONCE(*this, "%lf", _Val);
		return *this;
	};

	

	int to_int(int _Radix = 10) const {
		return strtol(this->c_str(), nullptr, _Radix);
	};
	unsigned int to_uint(int _Radix = 10) const {
		return strtoul(this->c_str(), nullptr, _Radix);
	};
	float to_float() const {
		return strtof(this->c_str(), nullptr);
	};
	double to_double() const {
		return strtod(this->c_str(), nullptr);
	};

	const GBasic_String& emplace(char emplaced, char ch) {
		for (iterator itor = begin(); itor != end(); )
		{
			if (*itor == emplaced)
			{
				if (ch == 0)
				{
					itor = erase(itor);
					continue;
				}
				else
					*itor = ch;
			}
			++itor;
		}


		return *this;
	};


};

//哈希散列函数
namespace std{
	template<typename _Elem>
	struct hash<GBasic_String<_Elem>>{
		typedef GBasic_String<_Elem>	_Kty;					//散列对象
		typedef GBasic_String<_Elem>	argument_type;			//参数类型
		typedef size_t					result_type;			//返回值类型

		inline size_t operator()(const _Kty& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
			return (_Hash_seq((const unsigned char *)_Keyval.c_str(),
				_Keyval.size() * sizeof (_Elem)));
		}
	};
};

typedef GBasic_String<char>			GString;
typedef GBasic_String<wchar_t>		GWString;

#if defined(_UNICODE)
typedef GWString					GTString;
#else
typedef GString						GTString;
#endif

#endif