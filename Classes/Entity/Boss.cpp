#include "Boss.h"

Boss::Boss()
	: m_iXSpeed(0)
	, m_iYspeed(0)
	, m_iFirstSkillDamage(0)
	, m_iFirstSkillCDTime(0)
	, m_iSecondSkillDamage(0)
	, m_iSecondSkillCDTime(0)
	, m_iThirdSkillDamage(0)
	, m_iThirdSkillCDTime(0)
	, m_bIsLock(false)
	, m_fStateTime(0.0)
{
}

Boss::~Boss()
{
}

bool Boss::init(const BossData & bossData)
{
	CombatEntity::saveCombatEntityData(bossData);

	m_iFirstSkillDamage = bossData.i_firstSkillDamage;
	m_iFirstSkillCDTime = bossData.i_firstSkillCDTime;
	m_iSecondSkillDamage = bossData.i_secondSkillDamage;
	m_iSecondSkillCDTime = bossData.i_secondSkillCDTime;
	m_iThirdSkillDamage = bossData.i_thirdSkillDamage;
	m_iThirdSkillCDTime = bossData.i_thirdSkillCDTime;

	return true;
}

void Boss::setBossPosition(Point pos)
{
	setPosition(pos);
}
