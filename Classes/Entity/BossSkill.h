#pragma once
#ifndef __BOSS_SKILL_H__
#define __BOSS_SKILL_H__

#include "CustomizeStruct.h"

class GameLayer;

class BossSkill : public Ref
{
public:
	static BossSkill * getInstance();

	void useSkill(SkillType skillType, Point playerPoint);

	void setGameLayer(GameLayer* gameLayer);

protected:
	BossSkill();
	virtual ~BossSkill();

	virtual bool init();

private:
	void shootBeam(Point playerPoint);
	void launchingMissile(Point playerPoint);
	void summon();
	void debuff();

private:
	static BossSkill* m_pBossSkill;

	GameLayer* m_pGameLayer;
};

#endif // !__BOSS_SKILL_H__
