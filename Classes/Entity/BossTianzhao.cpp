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

	m_iMaxHP = bossData.i_HP;

	Size size = m_pSprite->getContentSize();

	m_pHPBar = HpBar::create();
	m_pHPBar->setHpBarPosition(Point(0, size.height + 5));
	m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);
	this->addChild(m_pHPBar);

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

void BossTianzhao::checkDistanceWithPlayer(Ref * pSender)
{
	Point* playerPos = (Point*)pSender;
	Point bossPos = this->getPosition();
}
