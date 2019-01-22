#pragma once
#include "state.h"
class MutouT;
class StateRest : public State
{
public:
	StateRest();
	~StateRest();

	virtual void execute(MutouT* mutou, EnumMsgType enMsgType);
};