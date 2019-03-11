#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "CombatEntity.h"

class Monster : public CombatEntity
{
public:
	static Monster* create(const MonsterData & monsterData);
	virtual bool init(const MonsterData & monsterData);
	virtual void update(float dt);

	void setMonsterPosition(Point pos);

private:
	Monster();
	virtual ~Monster();

	void checkAttckFlyingObjectPath(Ref* pSender);
	void checkBeHit(Ref* pSender);
	void checkDistanceWithPlayer(Ref* pSender);

private:
	int m_iXSpeed;	//X轴移速
	int m_iYspeed;	//Y轴移速
	int m_iWarningRange;	//怪物巡逻警戒半径

	bool m_bIsRight;	//是否向右
	bool m_bIsAttack;	//攻击状态
	bool m_bIsAttacked;	//被攻击状态
	bool m_bIsDeath;	//是否为死亡状态
	bool m_bIsBattle;	//战斗状态

	float m_fStateTime;	//计时器

	Point m_pointOriginalPos;	//初始坐标点
};

#endif // !__MONSTER_H__
