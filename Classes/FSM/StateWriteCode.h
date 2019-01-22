#pragma once
#include "state.h"
class MutouT;
class StateWriteCode : public State
{
public:
	StateWriteCode();
	~StateWriteCode();

	virtual void execute(MutouT* mutou, EnumMsgType enMsgType);
};

