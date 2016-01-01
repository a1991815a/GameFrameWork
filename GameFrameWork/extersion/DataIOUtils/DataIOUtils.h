#ifndef __DATAIOUTILS__
#define __DATAIOUTILS__
#include <string>
#include <unordered_map>
#include "../DataStruct/GString.h"
#include "../DataStruct/GValue.h"
#include "../regex/GRegex.h"
#include "../tinyxml/tinyxml.h"

#define F_OK 0

#define _dataIOUtils DataIOUtils::getInstance()

//数据类型宏定义
typedef GString DataString;

//数据列表(没有层次结构的数据)
class DataList{
	friend class DataIOUtils;
public:
	typedef std::unordered_map<DataString, DataString> _MyContainer;

	void setData(const DataString& key, const DataString& data);
	const DataString& getData(const DataString& key) const;

	_MyContainer::iterator begin();
	_MyContainer::iterator end();

	_MyContainer::const_iterator begin() const;
	_MyContainer::const_iterator end() const;
private:
	std::unordered_map<DataString, DataString>
		m_mValueMap;
};

//数据IO工具
class DataIOUtils{
public:
	static DataIOUtils* getInstance();
	static void destroyInstance();
private:
	static DataIOUtils* m_instance;
	DataIOUtils();
	~DataIOUtils();
public:
	//打开文件
	FILE* openFile(const char* path, const char* _Mode) const;
	//关闭文件
	void closeFile(FILE* f) const;
	//得到文本数据
	GString readString(FILE* f) const;
	//写入文本数据
	void writeString(FILE* f, const GString& data) const;

	//保存数据列表
	bool SaveDataList(const char* path, DataList* pData) const;
	//加载数据列表
	DataList* LoadDataList(const char* path) const;

	//保存层次数据模型
	bool SavePlist(const char* path, const GValue& pRoot) const;
	//加载层次数据模型: 返回根节点
	GValue LoadPlist(const char* path) const;

	//加载Xml文件
	TiXmlDocument* LoadXml(const char* path) const;

private:
	//构造一个Plist根节点
	TiXmlNode* ContructPlistRoot(
		TiXmlDocument** pDoc,
		const GString& Encoding = "UTF-8"
		) const;
	//构造一个PlistKey节点
	TiXmlNode* ContructPlistKey(const GString& _key, TiXmlNode* pParent) const;;
	//构造一个Plist字典节点
	TiXmlNode* ContructPlistDict(const std::unordered_map<GString, GValue>& _dict, TiXmlNode* pParent) const;;
	//构造一个Plist数组节点
	TiXmlNode* ContructPlistArray(const std::vector<GValue>& _array, TiXmlNode* pParent) const;;
	//构造一个PlistInterger节点
	TiXmlNode* ContructPlistInterger(int _i, TiXmlNode* pParent) const;;
	//构造一个PlistString节点
	TiXmlNode* ContructPlistString(const GString& _str, TiXmlNode* pParent) const;;
	//构造一个PlistReal节点
	TiXmlNode* ContructPlistReal(float _f, TiXmlNode* pParent) const;;
	//构造一个Plist True/False节点
	TiXmlNode* ContructPlistBool(bool _b, TiXmlNode* pParent) const;;
	//根据GValue构造一个Plist节点
	TiXmlNode* ContructPlistByGValue(const GValue& val, TiXmlNode* pParent) const;;

	GValue ParseXmlNode(TiXmlNode* node) const;;
private:
	GRegex* m_pRegex;
};
#endif