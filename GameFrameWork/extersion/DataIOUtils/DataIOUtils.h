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

//�������ͺ궨��
typedef GString DataString;

//�����б�(û�в�νṹ������)
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

//����IO����
class DataIOUtils{
public:
	static DataIOUtils* getInstance();
	static void destroyInstance();
private:
	static DataIOUtils* m_instance;
	DataIOUtils();
	~DataIOUtils();
public:
	//���ļ�
	FILE* openFile(const char* path, const char* _Mode) const;
	//�ر��ļ�
	void closeFile(FILE* f) const;
	//�õ��ı�����
	GString readString(FILE* f) const;
	//д���ı�����
	void writeString(FILE* f, const GString& data) const;

	//���������б�
	bool SaveDataList(const char* path, DataList* pData) const;
	//���������б�
	DataList* LoadDataList(const char* path) const;

	//����������ģ��
	bool SavePlist(const char* path, const GValue& pRoot) const;
	//���ز������ģ��: ���ظ��ڵ�
	GValue LoadPlist(const char* path) const;

	//����Xml�ļ�
	TiXmlDocument* LoadXml(const char* path) const;

private:
	//����һ��Plist���ڵ�
	TiXmlNode* ContructPlistRoot(
		TiXmlDocument** pDoc,
		const GString& Encoding = "UTF-8"
		) const;
	//����һ��PlistKey�ڵ�
	TiXmlNode* ContructPlistKey(const GString& _key, TiXmlNode* pParent) const;;
	//����һ��Plist�ֵ�ڵ�
	TiXmlNode* ContructPlistDict(const std::unordered_map<GString, GValue>& _dict, TiXmlNode* pParent) const;;
	//����һ��Plist����ڵ�
	TiXmlNode* ContructPlistArray(const std::vector<GValue>& _array, TiXmlNode* pParent) const;;
	//����һ��PlistInterger�ڵ�
	TiXmlNode* ContructPlistInterger(int _i, TiXmlNode* pParent) const;;
	//����һ��PlistString�ڵ�
	TiXmlNode* ContructPlistString(const GString& _str, TiXmlNode* pParent) const;;
	//����һ��PlistReal�ڵ�
	TiXmlNode* ContructPlistReal(float _f, TiXmlNode* pParent) const;;
	//����һ��Plist True/False�ڵ�
	TiXmlNode* ContructPlistBool(bool _b, TiXmlNode* pParent) const;;
	//����GValue����һ��Plist�ڵ�
	TiXmlNode* ContructPlistByGValue(const GValue& val, TiXmlNode* pParent) const;;

	GValue ParseXmlNode(TiXmlNode* node) const;;
private:
	GRegex* m_pRegex;
};
#endif