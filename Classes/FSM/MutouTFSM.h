#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "MutouT.h"

class MutouTFSM : public Node
{
public:
	~MutouTFSM();
	static MutouTFSM* createWithMutouT(MutouT* mutou);
	bool initWithMutouT(MutouT* mutou);

	void changeState(State* state);

private:
	void onRecvWantToRest(Ref* obj);
	void onRecvWantToWriteCode(Ref* obj);
	void onRecvWantToWriteArticle(Ref* obj);

	State* mCurState;
	MutouT* mMutou;
};