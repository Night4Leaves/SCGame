#pragma once
#ifndef __PROP_BANK_H__
#define __PROP_BANK_H__

#include "cocos2d.h"
USING_NS_CC;

class PropBank : public Ref
{
public:
	static PropBank * getInstance();
	virtual bool init();

	void getItem1Num();
	void getItem2Num();

private:
	PropBank();
	~PropBank();

private:
	static PropBank* m_pPropBank;

	int m_iItemNum;	//道具数
};

#endif // !__PROP_BANK_H__
