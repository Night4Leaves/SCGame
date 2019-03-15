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

	/*创建玩家血量*/
	static HeartCount* create(int digit);
	virtual bool init(int digit);

	/*玩家血量下降*/
	void reduceHP();

protected:
	int m_iMaxHP;	//玩家最高血量
	int m_iHP;	//玩家目前血量

	Node* node_pPresenter;	//表示血量的图片对象
};

#endif // !__HEART_COUNT_H__
