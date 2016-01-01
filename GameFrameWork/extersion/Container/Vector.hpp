#ifndef __VECTOR__
#define __VECTOR__
#include <vector>

template<typename _Ty>
class Vector {
public:
	typedef std::vector<_Ty> container_type;
	typedef _Ty value_type;
	typedef _Ty* pointer;
	typedef const _Ty* const_pointer;
	typedef _Ty& reference;
	typedef const _Ty& const_reference;
	typedef size_t size_type;
	typedef typename container_type::iterator iterator;
	typedef typename container_type::const_iterator const_iterator;

public:
	Vector() {};
	Vector(const Vector& _vector)
		:m_vRefVector(_vector.m_vRefVector)
	{
		auto itor = m_vRefVector.begin();
		for (; itor != m_vRefVector.end(); ++itor)
			(*itor)->retain();
	};
	Vector(Vector&& _vector)
		:m_vRefVector(std::move(_vector.m_vRefVector))
	{};
	~Vector() {
		clear();
	};

	void resize(size_t _size) {
		m_vRefVector.resize(_size);
	};
	void resize(size_t _size, const _Ty& val) {
		m_vRefVector.resize(_size, val);
	};
	void reserve(size_t _size) {
		m_vRefVector.reserve(_size);
	};
	void swap(Vector& _vector) {
		m_vRefVector.swap(_vector.m_vRefVector);
	};

	size_t size() const {
		return m_vRefVector.size();
	};
	size_t capacity() const {
		return m_vRefVector.capacity();
	};
	bool empty() const {
		return m_vRefVector.empty();
	}

	_Ty& front() {
		return m_vRefVector.front();
	};
	const _Ty& front() const {
		return m_vRefVector.front();
	};
	_Ty& back() {
		return m_vRefVector.back();
	};
	const _Ty& back() const {
		return m_vRefVector.back();
	};
	_Ty& at(size_t index) {
		return m_vRefVector.at(index);
	};
	const _Ty& at(size_t index) const {
		return m_vRefVector.at(index);
	};
	size_t find(const _Ty& val) const {
		for (size_t i = 0; i < m_vRefVector.size(); ++i)
			if (val == m_vRefVector.at(i))
				return i;
		return size_t(-1);
	};

	void push_back(const _Ty& val) {
		((_Ty)val)->retain();
		m_vRefVector.push_back(val);
	};
	void push_front(const _Ty& val) {
		((_Ty)val)->retain();
		m_vRefVector.push_back(m_vRefVector.begin());
	};
	void insert(size_t offset, const _Ty& val) {
		((_Ty)val)->retain();
		m_vRefVector.insert(m_vRefVector.begin() + offset, val);
	};
	void erase(size_t offset) {
		_Ty& val = m_vRefVector.at(offset);
		if (val)
			val->release();
		m_vRefVector.erase(m_vRefVector.begin() + offset);
	};
	void erase(const _Ty& val) {
		size_t er_index = find(val);
		if (er_index == -1)
			return;
		((_Ty)val)->release();
		m_vRefVector.erase(m_vRefVector.begin() + er_index);
	};

	void insert(typename const_iterator itor, const _Ty& val) {
		((_Ty)val)->retain();
		m_vRefVector.push_back(itor);
	};
	void erase(typename iterator itor) {
		if (*itor)
			(*itor)->release();
		m_vRefVector.erase(itor);
	};
	void clear() {
		auto itor = m_vRefVector.begin();
		for (; itor != m_vRefVector.end(); ++itor)
			if(*itor)
				(*itor)->release();
		m_vRefVector.clear();
	};

	typename iterator begin() {
		return m_vRefVector.begin();
	};
	typename const_iterator begin() const {
		return m_vRefVector.begin();
	};
	typename iterator end() {
		return m_vRefVector.end();
	};
	typename const_iterator end() const {
		return m_vRefVector.end();
	};

private:
	std::vector<_Ty> m_vRefVector;
};
#endif