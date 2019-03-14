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

	void patrolLogic();
	void warnLogic();
	void attackLogic();
	void attackedLogic();
	void attackEndLogic();

	void checkAttckFlyingObjectPath(Ref* pSender);
	void checkBeHit(Ref* pSender);
	void checkDistanceWithPlayer(Ref* pSender);

private:
	LoadingBar* m_pHPBar;

	int m_iXSpeed;	//X轴移速
	int m_iYSpeed;	//Y轴移速
	int m_iWarningRange;	//怪物巡逻警戒半径
	int m_iAttackCDTime;	//怪物攻击冷却时间
	int m_iMaxHP;		//当前血量

	bool m_bIsDeath;	//是否为死亡状态

	float m_fStateTime;	//巡逻计时器
	float m_fAttackTime;	//攻击冷却计时器

	Point m_pointOriginalPos;	//初始坐标点
	Point m_pointPlayerPos;		//玩家坐标
};

#endif // !__MONSTER_H__
