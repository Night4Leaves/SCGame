#pragma once
#ifndef __BOSS_TIANZHAO_H__
#define __BOSS_TIANZHAO_H__

#include "Boss.h"

class BossTianzhao : public Boss
{
public:
	static BossTianzhao* create(const BossData & bossData);
	virtual bool init(const BossData & bossData);
	virtual void update(float dt);

	virtual void firstSkill();
	virtual void secondSkill();
	virtual void thirdSkill();

	virtual void checkAttckFlyingObjectPath(Ref* pSender);
	virtual void checkBeHit(Ref* pSender);
	virtual void checkDistanceWithPlayer(Ref* pSender);

private:
	BossTianzhao();
	virtual ~BossTianzhao();
};

#endif // !__BOSS_TIANZHAO_H__
