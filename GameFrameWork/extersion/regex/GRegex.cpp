#include "GRegex.h"
#include <windows.h>

#define REGEX_RESULT_MAX 1

#pragma warning(push)
#pragma warning(disable:4217 4018)

GRegex::GRegex( const char* patten )
	:m_pRegex(nullptr)
{
	PCRE2_SPTR pcrePatten = (PCRE2_SPTR)patten;

	int errNum = 0;
	size_t errOffset = 0;

	m_pRegex = pcre2_compile(
		pcrePatten,
		PCRE2_ZERO_TERMINATED,
		0,
		&errNum,
		&errOffset,
		nullptr
		);
	if (m_pRegex == NULL)
	{
		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(errNum, buffer, sizeof(buffer));
		char outText[1024] = { 0 };
		sprintf_s(outText, "PCRE2 compilation failed at offset %d: %s\n", (int)errOffset,
			buffer);
		OutputDebugStringA(outText);
		while(true)
			throw std::runtime_error(outText);
	}else
		m_pMatch_data = pcre2_match_data_create_from_pattern(m_pRegex, nullptr);
}

GRegex::~GRegex()
{
	pcre2_code_free(m_pRegex);
	pcre2_match_data_free(m_pMatch_data);
}

std::vector<GRegexData> GRegex::MatchAll( const char* inText )
{
	std::vector<GRegexData> outVector;
	GRegexString inStr = inText;
	PCRE2_SPTR matchText = (PCRE2_SPTR)inStr.c_str();

	size_t startOffset = 0;

	int result = pcre2_match(
		m_pRegex,
		matchText,
		PCRE2_ZERO_TERMINATED,
		startOffset,
		0,
		m_pMatch_data,
		nullptr
		);
	if(result <= 0)
		return std::move(outVector);
	PCRE2_SIZE* s_ovector = pcre2_get_ovector_pointer(m_pMatch_data);

	{
		GRegexData regexData;
		GetResult(
			result,
			&startOffset,
			inStr,
			&regexData
			);
		outVector.push_back(std::move(regexData));
	}

// 	for (size_t i = 0; i < result; ++i)
// 	{
// 		if (i >= REGEX_RESULT_MAX)
// 		{
// 			startOffset = s_ovector[i * 2 + 1];
// 			break;
// 		}
// 		size_t firstIndex = i * 2;
// 		size_t secondIndex = firstIndex + 1;
// 		GRegexData tmpData;
// 		tmpData.offset = s_ovector[firstIndex];
// 		tmpData.strData = inStr.substr(
// 			s_ovector[firstIndex], 
// 			s_ovector[secondIndex] - s_ovector[firstIndex]);
// 		startOffset = s_ovector[secondIndex];
// 		outVector.push_back(std::move(tmpData));
// 	}
	

	while (
		startOffset < inStr.size() &&
		(result = pcre2_match(
		m_pRegex,
		matchText,
		PCRE2_ZERO_TERMINATED,
		startOffset,
		0,
		m_pMatch_data,
		nullptr
		)) > 0)
	{
		GRegexData regexData;
		GetResult(
			result,
			&startOffset,
			inStr,
			&regexData
			);
		outVector.push_back(std::move(regexData));
	}

	return std::move(outVector);
}

GRegexData GRegex::MatchFirst(
	const char* inText, 
	size_t offset /*= 0*/, 
	size_t* endOffset /*= nullptr*/)
{
	GRegexData retData;
	retData.offset = UINT_MAX;

	PCRE2_SPTR matchText = (PCRE2_SPTR)inText;
	int result = pcre2_match(
		m_pRegex,
		matchText,
		PCRE2_ZERO_TERMINATED,
		offset,
		0,
		m_pMatch_data,
		nullptr
		);

	if (result <= 0)
		return std::move(retData);

	GetResult(
		result,
		&offset,
		inText,
		&retData
		);

	if (endOffset)
		*endOffset = offset;
	return std::move(retData);
}

bool GRegex::MatchCheck(const char* inText)
{
	size_t len = strlen(inText);
	PCRE2_SPTR matchText = (PCRE2_SPTR)inText;
	int result = pcre2_match(
		m_pRegex,
		matchText,
		PCRE2_ZERO_TERMINATED,
		0,
		0,
		m_pMatch_data,
		nullptr
		);
	if(result <= 0)
		return false;

	size_t startOffset = 0;
	GetResult(
		result,
		&startOffset,
		inText,
		nullptr
		);
	if(startOffset < len)
		return false;
	return true;
}

bool GRegex::GetResult(
	int numResult,						/*结果个数 */ 
	size_t* startOffset,				/*起始偏移 */ 
	const GRegexString& inText,			/*匹配的文本 */ 
	GRegexData* regexData				/*返回的结果 */
	)
{
	if (numResult <= 0)
	{
		if (regexData)
		{
			regexData->offset = UINT_MAX;
			regexData->strData.clear();
		}
		return false;
	}
	size_t* s_oVector = pcre2_get_ovector_pointer(m_pMatch_data);
	for (size_t i = 0; i < numResult; ++i)
	{
		if (i >= REGEX_RESULT_MAX)
		{
			*startOffset = s_oVector[i * 2 + 1];
			break;
		}
		size_t firstIndex = i * 2;
		size_t secondIndex = firstIndex + 1;
		*startOffset = s_oVector[secondIndex];

		if (regexData)
		{
			regexData->offset = s_oVector[firstIndex];
			regexData->strData = inText.substr(
				s_oVector[firstIndex],
				s_oVector[secondIndex] - s_oVector[firstIndex]);
		}
	}

	return true;
}

#pragma warning(pop)