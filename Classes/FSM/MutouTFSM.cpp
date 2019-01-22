#include "MutouTFSM.h"



MutouTFSM::~MutouTFSM()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

MutouTFSM * MutouTFSM::createWithMutouT(MutouT * mutou)
{
	MutouTFSM* fsm = new MutouTFSM();

	if (fsm && fsm->initWithMutouT(mutou))
	{
		fsm->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(fsm);
		fsm = NULL;
	}
	return fsm;
}

bool MutouTFSM::initWithMutouT(MutouT * mutou)
{
	this->mCurState = NULL;
	this->mMutou = mutou;

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MutouTFSM::onRecvWantToRest),
													StringUtils::toString(en_Msg_WantToRest), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MutouTFSM::onRecvWantToWriteArticle),
													StringUtils::toString(en_Msg_WantToWriteArticle), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MutouTFSM::onRecvWantToWriteCode),
													StringUtils::toString(en_Msg_WantToWriteCode), NULL);
	return true;
}

void MutouTFSM::changeState(State * state)
{
	CC_SAFE_DELETE(mCurState);
	this->mCurState = state;
}

void MutouTFSM::onRecvWantToRest(Ref * obj)
{
	this->mCurState->execute(mMutou, en_Msg_WantToRest);
}

void MutouTFSM::onRecvWantToWriteCode(Ref * obj)
{
	this->mCurState->execute(mMutou, en_Msg_WantToWriteCode);
}

void MutouTFSM::onRecvWantToWriteArticle(Ref * obj)
{
	this->mCurState->execute(mMutou, en_Msg_WantToWriteArticle);
}
