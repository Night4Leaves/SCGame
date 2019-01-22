#include "StateWriteArticle.h"
#include "MutouT.h"
#include "MutouTFSM.h"
StateWriteArticle::StateWriteArticle()
{
}

StateWriteArticle::~StateWriteArticle()
{
}

void StateWriteArticle::execute(MutouT * mutou, EnumMsgType enMsgType)
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
