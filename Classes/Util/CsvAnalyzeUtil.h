#pragma once
#ifndef __CSV_ANALYZE_UTIL_H__
#define __CSV_ANALYZE_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

class CsvAnalyzeUtil : public Ref
{
public:
	static CsvAnalyzeUtil* getInstance();
	virtual bool init();

	/**
	 *	用分隔符分割字符串，结果存放到一个列表中，列表中的对象为Value
	 *	@srcStr
	 *	@sSep
	 */
	ValueVector split(const char* srcStr, const char* sSep);

private:
	static CsvAnalyzeUtil* m_pCsvAnalyzeUtil;
};

#endif // !__CSV_ANALYZE_UTIL_H__
