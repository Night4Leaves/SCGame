#include "MutouT.h"
#include "MutouTFSM.h"

bool MutouT::init()
{
	mFSM = MutouTFSM::createWithMutouT(this);
	mFSM->retain();
	this->scheduleUpdate();
	return true;
}

bool MutouT::isTire()
{
	return true;
}

bool MutouT::isWantToWriteArticle()
{
	float ran = CCRANDOM_0_1();
	if (ran < 0.1f)
	{
		return true;
	}
	return false;
}

void MutouT::writeCode()
{
	log("mutou is write code");
}

void MutouT::writeArticle()
{
	log("mutou is write article");
}

void MutouT::rest()
{
	log("mutou is rest");
}

MutouTFSM * MutouT::getFSM()
{
	return this->mFSM;
}



void MutouT::update(float dt)
{
	this->mFSM->update(dt);
}
