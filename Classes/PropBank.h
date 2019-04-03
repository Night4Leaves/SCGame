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

private:
	PropBank();
	~PropBank();

private:
	static PropBank* m_pPropBank;

	int m_iConsumableItemMaxNum;	//消耗型道具最大数目
	int m_iPlacementProp;	//放置型道具最大数目

	std::map<std::string, int> m_mapConsumableProp;	//消耗型道具数量
	std::map<std::string, int> m_mapPlacementProp;	//放置型道具数量
};

#endif // !__PROP_BANK_H__
