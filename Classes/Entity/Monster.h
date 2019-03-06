#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"
#include "CustomizeStruct.h"

class Monster : public Entity
{
public:
	static Monster* create(MonsterData monsterData);
	virtual bool init(MonsterData monsterData);
	virtual void update(float dt);

	void setMonsterPosition(Point pos);

	void idle();
	void run();
	void attack();
	void hurt();
	void death();

private:
	Monster();
	virtual ~Monster();

	void checkAttckFlyingObjectPath(Ref* pSender);
	void checkBeHit(Ref* pSender);

private:
	MonsterData m_sctMonsterData;
	//角色动作名
	std::vector<const char*> m_strActionName = { "idle","run","attack","hurt" };
	//动画帧间隔时间
	float m_fActionTime[7] = { 0.25f, 0.2f, 0.15f, 0.1f };
	//动画重复次数
	int m_iActionPlayTime[7] = { -1, -1, 1, 1 };

	int m_iXSpeed;	//X轴移速
	int m_iYspeed;	//Y轴移速

	bool m_bIsRight;	//是否向右
	bool m_bIsLock;		//是否为锁死状态
	bool m_bIsAttack;	//攻击状态
	bool m_bIsAttacked;	//被攻击状态
	bool m_bIsDeath;	//是否为死亡状态

	float m_fStateTime;

	Point m_pointOriginalPos;
};

#endif // !__MONSTER_H__
