#include "CsvData.h"

bool CsvData::init()
{
	return true;
}

void CsvData::addLineData(ValueVector lineData)
{
	m_allLinesVec.push_back(Value(lineData));
}

ValueVector CsvData::getSingleLineData(int i_line)
{
	return m_allLinesVec.at(i_line).asValueVector();
}

Size CsvData::getRowColNum()
{
	Size size = Size();

	size.width = m_allLinesVec.size();
	if (size.width > 0)
	{
		size.height = m_allLinesVec.at(0).asValueVector().size();
	}

	return size;
}
