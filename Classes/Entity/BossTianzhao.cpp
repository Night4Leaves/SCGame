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

	return true;
}

void BossTianzhao::firstSkill()
{
	log("skill-1");
	this->attack();
}

void BossTianzhao::secondSkill()
{
	log("skill-2");
	this->attack();
}

void BossTianzhao::thirdSkill()
{
	log("skill-3");
	this->attack();
}
