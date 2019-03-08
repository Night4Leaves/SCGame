#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "CombatEntity.h"

class Boss : public CombatEntity
{
public:
	virtual bool init(const BossData & bossData);

	void setBossPosition(Point pos);

	virtual void firstSkill() = 0;
	virtual void secondSkill() = 0;
	virtual void thirdSkill() = 0;

	virtual void checkAttckFlyingObjectPath(Ref* pSender) = 0;
	virtual void checkBeHit(Ref* pSender) = 0;

protected:
	Boss();
	virtual ~Boss();

	int m_iXSpeed;	//X轴移速
	int m_iYspeed;	//Y轴移速
	int m_iFirstSkillDamage;	//第一技能伤害
	int m_iFirstSkillCDTime;	//第一技能冷却时间
	int m_iSecondSkillDamage;	//第二技能伤害
	int m_iSecondSkillCDTime;	//第二技能冷却时间
	int m_iThirdSkillDamage;	//第三技能伤害
	int m_iThirdSkillCDTime;	//第三技能伤害

	bool m_bIsRight;	//是否向右
	bool m_bIsLock;		//是否为锁死状态
	bool m_bIsAttack;	//攻击状态
	bool m_bIsAttacked;	//被攻击状态

	float m_fStateTime;
};

#endif // !__BOSS_H__
