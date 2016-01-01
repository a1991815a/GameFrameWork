#include "DataIOUtils.h"

#define CONFIG_CHECK_REGEX "([\\d\\D]+?=[\\d\\D]+?(?=((\\r\\n)|\\r|\\n)))*"
#define CONFIG_MATCH_REGEX "[^\\r\\n]+?=[^\\r\\n]+?(?=((\\r\\n)|\\r|\\n))"

DataIOUtils* DataIOUtils::m_instance = nullptr;

DataIOUtils::DataIOUtils()
	:m_pRegex(nullptr)
{
	m_pRegex = new GRegex(CONFIG_MATCH_REGEX);
}

DataIOUtils::~DataIOUtils()
{
	if(m_pRegex)
		delete m_pRegex;
}

DataIOUtils* DataIOUtils::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new DataIOUtils();
	return m_instance;
}

void DataIOUtils::destroyInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}


FILE* DataIOUtils::openFile(const char* path, const char* _Mode) const
{
	FILE* f = nullptr;
	errno_t err = fopen_s(&f, path, _Mode);
	
	while (err != F_OK)
		throw std::runtime_error("openFile fail!");

	return f;
}

void DataIOUtils::closeFile(FILE* f) const
{
	if (f == nullptr)
		return;
	fclose(f);
}

GString DataIOUtils::readString(FILE* f) const
{
	GString strData;
	char ch = EOF;
	while ((ch = fgetc(f)) != EOF)
		strData += ch;
	return std::move(strData);
}

void DataIOUtils::writeString(FILE* f, const GString& data) const
{
	if (f == nullptr)
		return;
	fwrite(data.c_str(), sizeof(GString::value_type), data.size(), f);
}

bool DataIOUtils::SaveDataList(const char* path, DataList* pData) const
{
	FILE* f = openFile(path, "wb+");

	DataList::_MyContainer& container = pData->m_mValueMap;
	auto itor = container.begin();
	for (; itor != container.end(); ++itor)
	{
		const GString& key = itor->first;
		const GString& val = itor->second;
		//格式: key=val 回车提行
		writeString(f, key);
		writeString(f, "=");
		writeString(f, val);
		writeString(f, "\r\n");
	}
	closeFile(f);

	return true;
}

DataList* DataIOUtils::LoadDataList(const char* path) const
{
	FILE* f = openFile(path, "rb+");
	GString data = readString(f);
	closeFile(f);
	DataList* dataList = new DataList();

	auto matchList = m_pRegex->MatchAll(data.c_str());
	for (size_t i = 0; i < matchList.size(); ++i)
	{
		GRegexData& rd = matchList.at(i);
		size_t midIndex = rd.strData.find('=');
		GString key = rd.strData.substr(0, midIndex);
		key.emplace(' ', 0);
		GString val = rd.strData.substr(midIndex + 1, rd.strData.size() - midIndex - 1);
		val.emplace(' ', 0);
		if(key.empty())
			continue;
		dataList->setData(
			std::move(key),
			std::move(val)
			);
	}


	return dataList;
}

bool DataIOUtils::SavePlist(const char* path, const GValue& pRoot) const
{
	TiXmlDocument* doc = nullptr;
	TiXmlNode* root = ContructPlistRoot(&doc);
	ContructPlistByGValue(pRoot, root);
	bool result = doc->SaveFile(path);
	delete doc;
	return result;
}

GValue DataIOUtils::LoadPlist(const char* path) const
{
	TiXmlDocument* doc = LoadXml(path);
	GValue val = ParseXmlNode(doc);
	delete doc;
	return std::move(val);
}

TiXmlDocument* DataIOUtils::LoadXml(const char* path) const
{
	TiXmlDocument* doc = new TiXmlDocument();
	doc->LoadFile(path);
	return doc;
}





TiXmlNode* DataIOUtils::ContructPlistRoot(
	TiXmlDocument** pDoc, 
	const GString& Encoding /*= "UTF-8" */) const
{
	*pDoc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", Encoding.c_str(), "true");
	(*pDoc)->LinkEndChild(decl);
	TiXmlElement* plistRoot = new TiXmlElement("plist");
	(*pDoc)->LinkEndChild(plistRoot);
	return plistRoot;
}


TiXmlNode* DataIOUtils::ContructPlistKey(const GString& _key, TiXmlNode* pParent) const
{
	TiXmlElement* keyElement = new TiXmlElement("key");
	TiXmlText* keyText = new TiXmlText(_key.c_str());
	keyElement->LinkEndChild(keyText);
	pParent->LinkEndChild(keyElement);
	return keyElement;
}

TiXmlNode* DataIOUtils::ContructPlistDict(
	const std::unordered_map<GString, GValue>& _dict, 
	TiXmlNode* pParent) const
{
	TiXmlElement* dictElement = new TiXmlElement("dict");

	auto itor = _dict.begin();
	for (; itor != _dict.end(); ++itor)
	{
		const GString& key = itor->first;
		const GValue& val = itor->second;
		ContructPlistKey(key, dictElement);
		ContructPlistByGValue(val, dictElement);
	}

	pParent->LinkEndChild(dictElement);
	return dictElement;
}

TiXmlNode* DataIOUtils::ContructPlistArray(
	const std::vector<GValue>& _array, 
TiXmlNode* pParent) const
{
	TiXmlElement* arrayElement = new TiXmlElement("array");

	auto itor = _array.begin();
	for (; itor != _array.end(); ++itor)
	{
		const GValue& val = *itor;
		ContructPlistByGValue(val, arrayElement);
	}

	pParent->LinkEndChild(arrayElement);
	return arrayElement;
}

TiXmlNode* DataIOUtils::ContructPlistInterger(int _i, TiXmlNode* pParent) const
{
	TiXmlElement* intergerElement = new TiXmlElement("integer");
	TiXmlText* valText = new TiXmlText(GString::number(_i).c_str());
	intergerElement->LinkEndChild(valText);

	pParent->LinkEndChild(pParent);
	return intergerElement;
}

TiXmlNode* DataIOUtils::ContructPlistString(const GString& _str, TiXmlNode* pParent) const
{
	TiXmlElement* stringElement = new TiXmlElement("string");
	TiXmlText* valText = new TiXmlText(_str.c_str());
	stringElement->LinkEndChild(valText);

	pParent->LinkEndChild(stringElement);
	return stringElement;
}

TiXmlNode* DataIOUtils::ContructPlistReal(float _f, TiXmlNode* pParent) const
{
	TiXmlElement* realElement = new TiXmlElement("real");
	TiXmlText* valText = new TiXmlText(GString::number(_f).c_str());
	realElement->LinkEndChild(valText);

	pParent->LinkEndChild(pParent);
	return realElement;
}

TiXmlNode* DataIOUtils::ContructPlistBool(bool _b, TiXmlNode* pParent) const
{
	TiXmlElement* boolElement = nullptr;
	if (_b)
		boolElement = new TiXmlElement("true");
	else
		boolElement = new TiXmlElement("false");

	pParent->LinkEndChild(boolElement);
	return pParent;
}

TiXmlNode* DataIOUtils::ContructPlistByGValue(const GValue& val, TiXmlNode* pParent) const
{
	switch (val.getType())
	{
	case GTYPE_NONE:
		return nullptr;
	case GTYPE_CHAR:
	{
		GString str = GString(1, val.asChar());
		ContructPlistString(str, pParent);
	}
		break;
	case GTYPE_STRING:
		ContructPlistString(val.asString(), pParent);
		break;
	case GTYPE_INT:
		ContructPlistInterger(val.asInt(), pParent);
		break;
	case GTYPE_POINTER:
		ContructPlistInterger(val.asInt(), pParent);
		break;
	case GTYPE_FLOAT:
		ContructPlistReal(val.asFloat(), pParent);
		break;
	case GTYPE_VALUEVECTOR:
		ContructPlistArray(val.asValueVector(), pParent);
		break;
	case GTYPE_VALUEMAP:
		ContructPlistDict(val.asValueMap(), pParent);
		break;
	default:
		break;
	}
	return nullptr;
}

GValue DataIOUtils::ParseXmlNode(TiXmlNode* node) const
{
	if (node == nullptr)
		return GValue();
	switch (node->Type())
	{
	case TiXmlNode::NodeType::TINYXML_DOCUMENT:
		return ParseXmlNode(node->FirstChild());
	case TiXmlNode::NodeType::TINYXML_ELEMENT:
		break;
	default:
		return ParseXmlNode(node->NextSibling());
	}

	GString nodeTag = node->Value();

	if (nodeTag == "plist")
	{
		return ParseXmlNode(node->FirstChild());
	}
	else if (nodeTag == "key")
	{
		return GValue(node->FirstChild()->ToText()->Value());
	}
	else if (nodeTag == "dict")
	{
		GValueMap vm;
		TiXmlElement* childNode = node->FirstChildElement();
		for (;childNode != nullptr; childNode = childNode->NextSiblingElement())
		{
			GValue keyStr = ParseXmlNode(childNode);
			childNode = childNode->NextSiblingElement();
			vm[keyStr.asString()] = ParseXmlNode(childNode);
		}
		return GValue(std::move(vm));
	}
	else if (nodeTag == "array")
	{
		GValueVector vv;
		TiXmlElement* childNode = node->FirstChildElement();
		for (;childNode != nullptr; childNode = childNode->NextSiblingElement())
			vv.push_back(ParseXmlNode(childNode));
		return GValue(std::move(vv));
	}
	else if (nodeTag == "interger")
	{
		GString str = node->FirstChild()->ToText()->Value();
		return GValue(str.to_int());
	}
	else if (nodeTag == "real")
	{
		GString str = node->FirstChild()->ToText()->Value();
		return GValue(str.to_float());
	}
	else if (nodeTag == "string")
	{
		GString str = node->FirstChild()->ToText()->Value();
		return GValue(str);
	}
	else if (nodeTag == "true")
	{
		return GValue(true);
	}
	else if (nodeTag == "false")
	{
		return GValue(false);
	}

	return GValue();
}

void DataList::setData(const DataString& key, const DataString& data)
{
	m_mValueMap[key] = data;
}

const DataString& DataList::getData(const DataString& key) const
{
	return m_mValueMap.at(key);
}

 DataList::_MyContainer::iterator DataList::begin()
{
	return m_mValueMap.begin();
}

 DataList::_MyContainer::const_iterator DataList::begin() const
{
	return m_mValueMap.begin();
}

 DataList::_MyContainer::iterator DataList::end()
{
	return m_mValueMap.end();
}

 DataList::_MyContainer::const_iterator DataList::end() const
{
	return m_mValueMap.end();
}
