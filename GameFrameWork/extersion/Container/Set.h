#ifndef __SET__
#define __SET__
#include <unordered_set>
#include <type_traits>

template<typename _Ty>
class Set{
public:
	typedef typename std::unordered_set<_Ty>		container_type;
	typedef typename std::remove_pointer<_Ty>::type value_type;
	typedef typename value_type*					pointer;
	typedef typename const value_type*				const_pointer;
	typedef typename value_type&					reference;
	typedef typename const value_type&				const_reference;
	typedef typename container_type::iterator		iterator;
	typedef typename container_type::const_iterator	const_iterator;

public:
	Set() {};
	Set(const Set& _set) {
		auto itor = _set.m_sRefSet.begin();
		for (; itor != _set.m_sRefSet.end(); ++itor)
		{
			(*itor)->retain();
			m_sRefSet.insert(*itor);
		}
	};
	Set(Set&& _set) 
		:m_sRefSet(std::move(_set.m_sRefSet))
	{};
	~Set() {
		clear();
	};

	void reserve(size_t _size) {
		m_sRefSet.reserve(_size);
	};
	void insert(const _Ty& _obj) {
		_obj->retain();
		m_sRefSet.insert(_obj);
	};
	void erase(const _Ty& _obj) {
		_obj->release();
		m_sRefSet.erase(_obj);
	};
	typename iterator erase(typename iterator itor) {
		(*itor)->release();
		return m_sRefSet.erase(itor);
	};
	void clear() {
		auto itor = m_sRefSet.begin();
		for (; itor != m_sRefSet.end(); ++itor)
			(*itor)->release();
		m_sRefSet.clear();
	};

	void swap(Set& _set) {
		m_sRefSet.swap(_set.m_sRefSet);
	};
	size_t size() const {
		return m_sRefSet.size();
	};

	typename iterator find(const _Ty& _obj) {
		return m_sRefSet.find(_obj);
	};
	typename const_iterator find(const _Ty& _obj) const {
		return m_sRefSet.find(_obj);
	};

	typename iterator begin() {
		return m_sRefSet.begin();
	};
	typename const_iterator begin() const {
		return m_sRefSet.begin();
	};
	typename iterator end() {
		return m_sRefSet.end();
	};
	typename const_iterator end() const {
		return m_sRefSet.end();
	};


private:
	std::unordered_set<_Ty>	m_sRefSet;
};
#endif