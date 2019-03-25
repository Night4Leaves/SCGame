#pragma once
#ifndef __BOSS_TIANZHAO_H__
#define __BOSS_TIANZHAO_H__

#include "Boss.h"

class BossTianzhao : public Boss
{
public:
	static BossTianzhao* create(const BossData & bossData);
	virtual bool init(const BossData & bossData);

	virtual void firstSkill();
	virtual void secondSkill();
	virtual void thirdSkill();

private:
	BossTianzhao();
	virtual ~BossTianzhao();
};

#endif // !__BOSS_TIANZHAO_H__
