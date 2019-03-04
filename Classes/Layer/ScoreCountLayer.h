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

	static ScoreCountLayer* create(int number);
	virtual bool init(int number);

	void setNumber(int number, int ceiling = 999999);
	int getNumber();

private:
	int i_number;
};

#endif // !__SCORE_COUNT_LAYRE_H__
