#pragma once
#ifndef __HEART_COUNT_H__
#define __HEART_COUNT_H__

#include "cocos2d.h"

USING_NS_CC;

class HeartCount : public Node
{
public:
	HeartCount();
	virtual ~HeartCount();

	static HeartCount* create(int digit);
	virtual bool init(int digit);

	void reduceHP();

protected:
	int m_iMaxHP;
	int m_iHP;

	Node* node_pPresenter;
};

#endif // !__HEART_COUNT_H__
