#pragma once
#include "EnumMsgType.h"
class MutouT;
class State {
public:
	virtual void execute(MutouT* mutou, EnumMsgType enMsgType) = 0;
};