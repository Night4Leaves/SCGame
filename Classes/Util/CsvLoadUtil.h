#pragma once
#ifndef __CSV_LOAD_UTIL_H__
#define __CSV_LOAD_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;
#include "CsvData.h"

class CsvLoadUtil : public Ref
{
public:
	static CsvLoadUtil* getInstance();
	virtual bool init();

	/**
	 *	加载配置文件
	 *	@ch_path
	 */
	void loadFile(const char* ch_path);

	/**
	 *	获取某行某列的值
	 *	@i_row
	 *	@i_col
	 *	@ch_csvFilePath
	 */
	Value getValue(int i_row, int i_col, const char* ch_csvFilePath);

	/**
	 *	获取某行某列的值并转化为字符串
	 *	@i_row
	 *	@i_col
	 *	@ch_csvFilePath
	 */
	const std::string getString(int i_row, int i_col, const char* ch_csvFilePath);

	/**
	 *	获取某行某列的值并转化为整形
	 *	@i_row
	 *	@i_col
	 *	@ch_csvFilePath
	 */
	const int getInt(int i_row, int i_col, const char* ch_csvFilePath);

	/**
	 *	获取某行某列的值并转化为整形
	 *	@i_row
	 *	@i_col
	 *	@ch_csvFilePath
	 */
	const float getFloat(int i_row, int i_col, const char* ch_csvFilePath);

	/**
	 *	获取某行某列的值并转化为整形
	 *	@i_row
	 *	@i_col
	 *	@ch_csvFilePath
	 */
	const bool getBool(int i_row, int i_col, const char* ch_csvFilePath);

	/**
	 *	获取文件的行和列数量
	 *	@ch_csvFilePath
	 */
	const Size getFileRowColNum(const char* ch_csvFilePath);

	/**
	 *	根据某个列的值，查找该值所在的行
	 *	@ch_value
	 *	@i_valueCol
	 *	@ch_csvFilePath
	 */
	const int findValueInWithLine(const char* ch_value, int i_valueCol, const char* ch_csvFilePath);

private:
	static CsvLoadUtil* m_pCsvLoadUtil;
	//存放mCsvStrList-filePath的字典
	Map<std::string, CsvData*> map_csvMap;
};

#endif // !__CSV_LOAD_UTIL_H__
