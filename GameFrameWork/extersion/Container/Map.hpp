#ifndef __MAP__
#define __MAP__
#include <string>
#include <unordered_map>

template<typename _kTy, typename _vTy>
class Map{
public:
	typedef std::unordered_map<_kTy, _vTy> container_type;
	typedef typename container_type::value_type value_type;
	typedef typename container_type::key_type key_type;
	typedef typename container_type::mapped_type mapped_type;
	typedef _vTy* pointer;
	typedef const _vTy* const_pointer;
	typedef _vTy& reference;
	typedef const _vTy& const_reference;
	typedef size_t size_type;
	typedef typename std::unordered_map<_kTy, _vTy>::iterator iterator;
	typedef typename std::unordered_map<_kTy, _vTy>::const_iterator const_iterator;
public:
	Map() {};
	Map(const Map& _map) 
		:m_mRefMap(_map.m_mRefMap)
	{
		auto itor = m_mRefMap.begin();
		for (; itor != m_mRefMap.end(); ++itor)
			itor->second->retain();
	};
	Map(Map&& _map) 
		:m_mRefMap(std::move(_map.m_mRefMap))
	{};
	~Map() {
		clear();
	};

	void swap(Map& _map) {
		m_mRefMap.swap(_map.m_mRefMap);
	};

	size_t size() const {
		return m_mRefMap.size();
	};
	void empty() const {
		return m_mRefMap.empty();
	}

	_vTy& at(const _kTy& key) {
		return m_mRefMap.at(key);
	};
	const _vTy& at(const _kTy& key) const {
		return m_mRefMap.at(key);
	};
	typename iterator find(const _kTy& key) {
		return m_mRefMap.find(key);
	};
	typename const_iterator find(const _kTy& key) const {
		return m_mRefMap.find(key);
	}

	void insert(const _kTy& key, const _vTy& val) {
		_vTy ins_val = val;
		ins_val->retain();
		m_mRefMap.insert(std::unordered_map<_kTy, _vTy>::value_type(key, ins_val));
	};
	typename iterator erase(const _kTy& key) {
		auto itor = m_mRefMap.find(key);
		return m_mRefMap.erase(itor);
	};
	void insert(typename const_iterator itor, const _vTy& val) {
		_vTy ins_val = val;
		ins_val->retain();
		m_mRefMap.insert(itor, ins_val);
	};
	typename iterator erase(typename iterator itor) {
		itor->second->release();
		return m_mRefMap.erase(itor);
	};
	void clear() {
		auto itor = m_mRefMap.begin();
		for (; itor != m_mRefMap.end(); ++itor)
			itor->second->release();
		m_mRefMap.clear();
	};


	typename iterator begin() {
		return m_mRefMap.begin();
	};
	typename const_iterator begin() const {
		return m_mRefMap.begin();
	};
	typename iterator end() {
		return m_mRefMap.end();
	};
	typename const_iterator end() const {
		return m_mRefMap.end();
	};

	typename iterator emplace(
		typename const_iterator itor,
		const _kTy& _key, const _vTy& _val) {
		m_mRefMap.emplace(itor, std::unordered_map<_kTy, _vTy>::value_type(_key, _val));
	};

private:
	std::unordered_map<_kTy, _vTy> m_mRefMap;
};
#endif