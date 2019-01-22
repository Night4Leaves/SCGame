#include "StateRest.h"
#include "MutouT.h"
#include "MutouTFSM.h"
StateRest::StateRest()
{
}

StateRest::~StateRest()
{
}

void StateRest::execute(MutouT * mutou, EnumMsgType enMsgType)
{
	switch (enMsgType)
	{
	case en_Msg_WantToWriteCode:
		mutou->writeCode();
		mutou->getFSM()->changeState(new StateWriteCode());
		break;
	case en_Msg_WantToWriteArticle:
		mutou->writeArticle();
		mutou->getFSM()->changeState(new StateWriteArticle());
		break;
	default:
		break;
	}
}
