#ifndef __GREGEX__
#define __GREGEX__
#include "pcre2/pcre2.h"
#include "../DataStruct/GString.h"
#include <vector>

typedef GString GRegexString;

//单个匹配数据
struct GRegexData{
	GRegexData()
		:offset(0)
	{};
	GRegexData(const GRegexData& data)
		:offset(data.offset), strData(data.strData)
	{};
	GRegexData(GRegexData&& data)
		:offset(data.offset), strData(std::move(data.strData))
	{};
	size_t offset;						//匹配的偏移
	GRegexString strData;				//匹配的字符串
};

class GRegex{
public:
	GRegex(const char* patten);
	~GRegex();

	std::vector<GRegexData> MatchAll(const char* inText);
	GRegexData MatchFirst(const char* inText, size_t offset = 0, size_t* endOffset = nullptr);

	bool MatchCheck(const char* inText);

	//返回 函数执行状态(是否执行成功)
	bool GetResult(
		int numResult,						//结果个数 
		size_t* startOffset,				//起始偏移
		const GRegexString& inText,			//匹配的文本
		GRegexData* regexData				//返回的结果
		);									

private:
	pcre2_code*			m_pRegex;					//被编译的正则表达式匹配器
	pcre2_match_data*	m_pMatch_data;				//匹配的数据
};

#endif