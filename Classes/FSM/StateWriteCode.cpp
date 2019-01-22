#include "StateWriteCode.h"
#include "MutouT.h"
#include "MutouTFSM.h"
StateWriteCode::StateWriteCode()
{
}


StateWriteCode::~StateWriteCode()
{
}

void StateWriteCode::execute(MutouT * mutou, EnumMsgType enMsgType)
{
	switch (enMsgType)
	{
	case en_Msg_WantToRest:
		mutou->rest();
		mutou->getFSM()->changeState(new StateRest());
		break;
	default:
		break;
	}

}
