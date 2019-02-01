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

	static ScoreCount* create(Array* presenters, int digit = 0);
	virtual bool init(Array* presenters, int digit);

	void animation(int digit);

	int getDigit();
	void setDigit(int digit);

protected:
	int i_digit;
	Node* node_pPresenter;

	void ScoreCountVisit();
};
#endif // !__SCORE_COUNT_H__
