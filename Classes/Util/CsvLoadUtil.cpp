#include "CsvLoadUtil.h"
#include "CsvAnalyzeUtil.h"

CsvLoadUtil* CsvLoadUtil::m_pCsvLoadUtil = NULL;

CsvLoadUtil * CsvLoadUtil::getInstance()
{
	if (m_pCsvLoadUtil == nullptr)
	{
		m_pCsvLoadUtil = new CsvLoadUtil();
		if (m_pCsvLoadUtil && m_pCsvLoadUtil->init())
		{
			m_pCsvLoadUtil->autorelease();
			m_pCsvLoadUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pCsvLoadUtil);
			m_pCsvLoadUtil = nullptr;
		}
	}

	return m_pCsvLoadUtil;
}

bool CsvLoadUtil::init()
{
	return true;
}

void CsvLoadUtil::loadFile(const char * ch_path)
{
	//存放一个Csv文件的对象
	CsvData* csvData = CsvData::create();

	//读取数据，按行保存到列表中
	std::string str = FileUtils::getInstance()->getStringFromFile(ch_path);
	ValueVector linesList = CsvAnalyzeUtil::getInstance()->split(str.c_str(), "\n");

	//把每一行的字符串拆分出来(按逗号分隔)
	for (auto value : linesList)
	{
		ValueVector tArr = CsvAnalyzeUtil::getInstance()->split(value.asString().c_str(), ",");
		csvData->addLineData(tArr);
	}

	//添加列表到字典里
	map_csvMap.insert(ch_path, csvData);
}

Value CsvLoadUtil::getValue(int i_row, int i_col, const char * ch_csvFilePath)
{
	//取出Csv文件对象
	auto csvData = map_csvMap.at(ch_csvFilePath);

	//如果配置文件的数据不存在，则加载配置文件
	if (csvData == nullptr)
	{
		loadFile(ch_csvFilePath);
		csvData = map_csvMap.at(ch_csvFilePath);
	}

	//获取i_row行数据
	ValueVector rowVector = csvData->getSingleLineData(i_row);
	//获取i_col列数据
	Value colValue = rowVector.at(i_col);

	return colValue;
}

const std::string CsvLoadUtil::getString(int i_row, int i_col, const char * ch_csvFilePath)
{
	Value colValue = getValue(i_row, i_col, ch_csvFilePath);

	return colValue.asString();
}

const int CsvLoadUtil::getInt(int i_row, int i_col, const char * ch_csvFilePath)
{
	Value colValue = getValue(i_row, i_col, ch_csvFilePath);

	return colValue.asInt();
}

const float CsvLoadUtil::getFloat(int i_row, int i_col, const char * ch_csvFilePath)
{
	Value colValue = getValue(i_row, i_col, ch_csvFilePath);

	return colValue.asFloat();
}

const bool CsvLoadUtil::getBool(int i_row, int i_col, const char * ch_csvFilePath)
{
	Value colValue = getValue(i_row, i_col, ch_csvFilePath);

	return colValue.asBool();
}

const Size CsvLoadUtil::getFileRowColNum(const char * ch_csvFilePath)
{
	//取出配置文件的二维表格
	auto csvData = map_csvMap.at(ch_csvFilePath);

	//如果配置文件的数据不存在，则加载配置文件
	if (csvData == nullptr)
	{
		loadFile(ch_csvFilePath);
		csvData = map_csvMap.at(ch_csvFilePath);
	}

	Size size = csvData->getRowColNum();

	return size;
}

const int CsvLoadUtil::findValueInWithLine(const char * ch_value, int i_valueCol, const char * ch_csvFilePath)
{
	return 0;
}
