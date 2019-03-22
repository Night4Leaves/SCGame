#include "EnemyDataLoadUtil.h"

EnemyDataLoadUtil* EnemyDataLoadUtil::m_pEnemyDataLoadUtil = NULL;

EnemyDataLoadUtil * EnemyDataLoadUtil::getInstance()
{
	if (m_pEnemyDataLoadUtil == NULL)
	{
		m_pEnemyDataLoadUtil = new EnemyDataLoadUtil();
		if (m_pEnemyDataLoadUtil && m_pEnemyDataLoadUtil->init())
		{
			m_pEnemyDataLoadUtil->autorelease();
			m_pEnemyDataLoadUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pEnemyDataLoadUtil);
			m_pEnemyDataLoadUtil = NULL;
		}
	}
	return m_pEnemyDataLoadUtil;
}

bool EnemyDataLoadUtil::init()
{
	JsonUtil::getInstance()->readMonsterInfo(monsterInfoList);
	JsonUtil::getInstance()->readBossInfo(bossDataList);
	return true;
}

void EnemyDataLoadUtil::getMonsterInfo(int key, MonsterData & monsterData)
{
	monsterData = monsterInfoList.at(key);
}

void EnemyDataLoadUtil::getBossInfo(int key, BossData & bossData)
{
	bossData = bossDataList.at(key);
}

EnemyDataLoadUtil::EnemyDataLoadUtil()
{
}

EnemyDataLoadUtil::~EnemyDataLoadUtil()
{
}
