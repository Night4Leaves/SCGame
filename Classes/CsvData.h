#pragma once
#ifndef __CSV_DATA_H__
#define __CSV_DATA_H__

#include "cocos2d.h"
USING_NS_CC;

class CsvData : public Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();

	/**
	 *	添加一行数据
	 *	@lineData
	 */
	void addLineData(ValueVector lineData);

	/**
	 *	获取某行数据
	 *	@i_line
	 */
	ValueVector getSingleLineData(int i_line);

	/**
	 *	获取行列大小
	 */
	Size getRowColNum();

private:
	ValueVector m_allLinesVec;
};

#endif // !__CSV_DATA_H__
