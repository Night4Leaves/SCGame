#pragma once
#include "state.h"
class MutouT;
class StateWriteArticle : public State
{
public:
	StateWriteArticle();
	~StateWriteArticle();

	virtual void execute(MutouT* mutou, EnumMsgType enMsgType);
};