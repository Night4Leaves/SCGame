#include "BossTianzhao.h"

BossTianzhao::BossTianzhao()
{
}

BossTianzhao::~BossTianzhao()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

BossTianzhao * BossTianzhao::create(const BossData & bossData)
{
	BossTianzhao *pRet = new(std::nothrow) BossTianzhao();
	if (pRet && pRet->init(bossData))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool BossTianzhao::init(const BossData & bossData)
{
	Boss::init(bossData);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(BossTianzhao::checkAttckFlyingObjectPath),
		"attack_flying_object_point",
		NULL);

	return true;
}

void BossTianzhao::update(float dt)
{
}

void BossTianzhao::firstSkill()
{
}

void BossTianzhao::secondSkill()
{
}

void BossTianzhao::thirdSkill()
{
}

void BossTianzhao::checkAttckFlyingObjectPath(Ref * pSender)
{
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(BossTianzhao::checkBeHit),
		"attack_flying_object_check_point",
		NULL);
}

void BossTianzhao::checkBeHit(Ref * pSender)
{
}
