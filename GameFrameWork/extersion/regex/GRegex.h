#ifndef __GREGEX__
#define __GREGEX__
#include "pcre2/pcre2.h"
#include "../DataStruct/GString.h"
#include <vector>

typedef GString GRegexString;

//����ƥ������
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
	size_t offset;						//ƥ���ƫ��
	GRegexString strData;				//ƥ����ַ���
};

class GRegex{
public:
	GRegex(const char* patten);
	~GRegex();

	std::vector<GRegexData> MatchAll(const char* inText);
	GRegexData MatchFirst(const char* inText, size_t offset = 0, size_t* endOffset = nullptr);

	bool MatchCheck(const char* inText);

	//���� ����ִ��״̬(�Ƿ�ִ�гɹ�)
	bool GetResult(
		int numResult,						//������� 
		size_t* startOffset,				//��ʼƫ��
		const GRegexString& inText,			//ƥ����ı�
		GRegexData* regexData				//���صĽ��
		);									

private:
	pcre2_code*			m_pRegex;					//�������������ʽƥ����
	pcre2_match_data*	m_pMatch_data;				//ƥ�������
};

#endif