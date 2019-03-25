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

	//设置怪物的位置
	void setMonsterOriginPosition(Point pos);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);
	
protected:
	Monster();
	virtual ~Monster();

	//巡逻行为
	void patrolLogic();
	//警戒行为
	void warnLogic();
	//攻击行为
	void attackLogic();
	//被攻击行为
	void attackedLogic();
	//攻击结束后的判定
	void attackEndLogic();

	//根据飞行物判定位置确认自己是否被击中
	void checkBeHit(Ref* pSender);
	//根据和玩家角色的距离变更自己的状态
	void checkDistanceWithPlayer(Ref* pSender);
	//设置位置
	void setMonsterPositon(Point pos);

protected:
	HpBar* m_pHPBar;	//血条

	int m_iXSpeed;	//X轴移速
	int m_iYSpeed;	//Y轴移速
	int m_iWarningRange;	//怪物巡逻警戒半径
	int m_iAttackCDTime;	//怪物攻击冷却时间
	int m_iMaxHP;		//最大血量

	bool m_bIsDeath;	//是否为死亡状态
	bool m_bIsFlying;	//是否为飞行系
	bool m_bIsAttackMove;	//攻击是否会移动

	float m_fStateTime;	//巡逻计时器
	float m_fAttackTime;	//攻击冷却计时器

	Point m_pointOriginalPos;	//初始坐标点
	Point m_pointPlayerPos;		//玩家坐标
};

#endif // !__MONSTER_H__
