#pragma once
#ifndef __BOSS_SKILL_H__
#define __BOSS_SKILL_H__

#include "CustomizeStruct.h"

class Boss;

class BossSkill : public Ref
{
public:
	static BossSkill * getInstance();

	void useSkill(SkillType skillType, Point playerPoint);

	void saveBoss(Boss* boss);

protected:
	BossSkill();
	virtual ~BossSkill();

	virtual bool init();

private:
	void closeCombet();
	void shootBeam(Point playerPoint);
	void launchingMissile(Point playerPoint);
	void summon();
	void debuff();
	void recovery();

private:
	static BossSkill* m_pBossSkill;

	Boss* m_pBoss;
};

#endif // !__BOSS_SKILL_H__
