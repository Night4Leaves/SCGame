#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum EnumState {
	enStateWriteCode,
	enStateWriteArticle,
	enStateRest,
};

class Mutou : public Node {
public:
	CREATE_FUNC(Mutou);
	virtual bool init();

	EnumState enCurState;

	bool isTire();
	bool isWantToWriteArticle();
	void writeCode();
	void writeArticle();
	void rest();
	void changeState(EnumState enState);
	
	virtual void update(float dt);
};