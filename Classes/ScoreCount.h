#pragma once
#ifndef __SCORE_COUNT_H__
#define __SCORE_COUNT_H__

#include "cocos2d.h"

USING_NS_CC;

class ScoreCount : public Node
{
public:
	ScoreCount();
	virtual ~ScoreCount();

	/*创建计分器*/
	static ScoreCount* create(Array* presenters, int digit = 0);
	virtual bool init(Array* presenters, int digit);

	/*数字滚动动画*/
	void animation(int digit);

	/*获取分数*/
	int getDigit();
	/*设置分数*/
	void setDigit(int digit);

protected:
	int i_digit;	//分数
	Node* node_pPresenter;	//计分器各位上的数字图片

};
#endif // !__SCORE_COUNT_H__
