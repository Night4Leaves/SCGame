#include "mutou.h"

bool Mutou::init()
{
	this->scheduleUpdate();
	return true;
}

bool Mutou::isTire()
{
	return true;
}

bool Mutou::isWantToWriteArticle()
{
	float ran = CCRANDOM_0_1();
	if (ran < 0.1f){
		return true;
	}
	return false;
}

void Mutou::writeCode()
{
	log("mutou is write code");
}

void Mutou::writeArticle()
{
	log("mutou is write article");
}

void Mutou::rest()
{
	log("mutou is rest");
}

void Mutou::changeState(EnumState enState)
{
	this->enCurState = enState;
}

void Mutou::update(float dt)
{
	switch (enCurState)
	{
	case enStateWriteCode:
		if (isTire()) {
			rest();
			changeState(enStateRest);
		}
		break;
	case enStateWriteArticle:
		if (isTire())
		{
			rest();
			changeState(enStateRest);
		}
		break;
	case enStateRest:
		if (isWantToWriteArticle()) {
			writeArticle();
			changeState(enStateWriteArticle);
		}
		else {
			writeCode();
			changeState(enStateWriteCode);
		}
		break;
	default:
		break;
	}
}
