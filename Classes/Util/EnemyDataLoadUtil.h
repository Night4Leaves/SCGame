#pragma once
#ifndef __ENEMY_DATA_LOAD_UTIL_H__
#define __ENEMY_DATA_LOAD_UTIL_H__

#include "Util/JsonUtil.h"

class EnemyDataLoadUtil : public Ref
{
public:
	static EnemyDataLoadUtil * getInstance();
	virtual bool init();

	void getMonsterInfo(int key, MonsterData & monsterData);
	void getBossInfo(int key, BossData & bossData);

private:
	EnemyDataLoadUtil();
	~EnemyDataLoadUtil();

private:
	static EnemyDataLoadUtil* m_pEnemyDataLoadUtil;

	std::vector<MonsterData> monsterInfoList;
	std::vector<BossData> bossDataList;
};

#endif // !__ENEMY_DATA_LOAD_UTIL_H__
