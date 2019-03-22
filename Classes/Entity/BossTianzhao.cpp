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
		callfuncO_selector(BossTianzhao::checkDistanceWithPlayer),
		"player_point",
		NULL);

	return true;
}

void BossTianzhao::update(float dt)
{
	Point pos = getPosition();
	pos.x += m_iXSpeed;
	setBossPosition(pos);
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

}

void BossTianzhao::checkBeHit(Ref * pSender)
{
}

void BossTianzhao::checkDistanceWithPlayer(Ref * pSender)
{
	Point* playerPos = (Point*)pSender;
	Point bossPos = this->getPosition();
	if (bossPos.x - playerPos->x < 655)
	{
		this->scheduleUpdate();
		NotificationCenter::getInstance()->removeObserver(this, "player_point");
	}
}
