#include "PropBank.h"

PropBank* PropBank::m_pPropBank = NULL;

PropBank * PropBank::getInstance()
{
	if (m_pPropBank == NULL)
	{
		m_pPropBank = new PropBank();
		if (m_pPropBank && m_pPropBank->init())
		{
			m_pPropBank->autorelease();
			m_pPropBank->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pPropBank);
			m_pPropBank = NULL;
		}
	}
	return m_pPropBank;
}

bool PropBank::init()
{
	return false;
}

PropBank::PropBank()
{
}

PropBank::~PropBank()
{
}
