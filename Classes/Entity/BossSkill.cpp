#include "BossSkill.h"
#include "Boss.h"

BossSkill* BossSkill::m_pBossSkill = NULL;

BossSkill * BossSkill::getInstance()
{
	if (m_pBossSkill == NULL)
	{
		m_pBossSkill = new BossSkill();
		if (m_pBossSkill && m_pBossSkill->init())
		{
			m_pBossSkill->autorelease();
			m_pBossSkill->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pBossSkill);
			m_pBossSkill = NULL;
		}
	}
	return m_pBossSkill;
}

void BossSkill::useSkill(SkillType skillType, Point playerPoint)
{
	switch (skillType)
	{
	case en_st_closeCombet:
		this->closeCombet();
		break;
	case en_st_beam:
		this->shootBeam(playerPoint);
		break;
	case en_st_missile:
		this->launchingMissile(playerPoint);
		break;
	case en_st_summon:
		this->summon();
		break;
	case en_st_debuff:
		this->debuff();
		break;
	case en_st_recovery:
		this->recovery();
		break;
	default:
		break;
	}
}

void BossSkill::saveBoss(Boss * boss)
{
	m_pBoss = boss;
}

BossSkill::BossSkill()
{
}

BossSkill::~BossSkill()
{
}

bool BossSkill::init()
{
	return true;
}

void BossSkill::closeCombet()
{
	m_pBoss->attack();
}

void BossSkill::shootBeam(Point playerPoint)
{
}

void BossSkill::launchingMissile(Point playerPoint)
{
}

void BossSkill::summon()
{
}

void BossSkill::debuff()
{
}

void BossSkill::recovery()
{
}
