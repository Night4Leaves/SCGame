#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "state.h"
#include "StateRest.h"
#include "StateWriteArticle.h"
#include "StateWriteCode.h"
//#include "MutouTFSM.h"
class MutouTFSM;
class MutouT : public Node
{
public:
	CREATE_FUNC(MutouT);
	virtual bool init();

	bool isTire();
	bool isWantToWriteArticle();
	void writeCode();
	void writeArticle();
	void rest();
	MutouTFSM* getFSM();

	virtual void update(float dt);
	
private:
	MutouTFSM* mFSM;
};