#pragma once
#ifndef __SCORE_COUNT_LAYRE_H__
#define __SCORE_COUNT_LAYRE_H__

#include "cocos2d.h"

USING_NS_CC;

class ScoreCountLayer : public Layer
{
public:
	ScoreCountLayer();
	~ScoreCountLayer();

	//创建记分器显示层
	static ScoreCountLayer* create(int number);
	virtual bool init(int number);

	/**
	 *	设置分数
	 *	@number	分数
	 *	@ceiling	分数上限
	 */
	void setNumber(int number, int ceiling = 999);
	//获取分数
	int getNumber();

	//更新分数
	void updateScore(Ref* pSender);

private:
	int i_number;	//分数
};

#endif // !__SCORE_COUNT_LAYRE_H__
