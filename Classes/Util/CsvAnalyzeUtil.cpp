#include "CsvAnalyzeUtil.h"

CsvAnalyzeUtil* CsvAnalyzeUtil::m_pCsvAnalyzeUtil = NULL;

CsvAnalyzeUtil * CsvAnalyzeUtil::getInstance()
{
	if (m_pCsvAnalyzeUtil == nullptr)
	{
		m_pCsvAnalyzeUtil = new CsvAnalyzeUtil();
		if (m_pCsvAnalyzeUtil && m_pCsvAnalyzeUtil->init())
		{
			m_pCsvAnalyzeUtil->autorelease();
			m_pCsvAnalyzeUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pCsvAnalyzeUtil);
			m_pCsvAnalyzeUtil = nullptr;
		}
	}

	return m_pCsvAnalyzeUtil;
}

bool CsvAnalyzeUtil::init()
{
	return true;
}

ValueVector CsvAnalyzeUtil::split(const char * srcStr, const char * sSep)
{
	ValueVector stringList;

	int size = strlen(srcStr);

	Value str = Value(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str.asString().find(sSep);

	std::string lineStr;
	while (endIndex > 0)
	{
		lineStr = str.asString().substr(startIndex, endIndex);
		stringList.push_back(Value(lineStr));
		str = Value(str.asString().substr(endIndex + 1, size));
		endIndex = str.asString().find(sSep);
	}

	if (str.asString().compare("") != 0)
	{
		stringList.push_back(Value(str.asString()));
	}

	return stringList;
}
