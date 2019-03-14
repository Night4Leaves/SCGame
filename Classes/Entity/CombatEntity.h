#pragma once
#ifndef __COMBAT_ENTITY_H__
#define __COMBAT_ENTITY_H__

#include "CustomizeStruct.h"

enum MonsterState
{
	en_ms_patrol,
	en_ms_warn,
	en_ms_attack,
	en_ms_attack_end,
	en_ms_attacked
};

enum ActionState
{
	en_as_null,
	en_as_idle,
	en_as_move,
	en_as_attack,
	en_as_attacked
};

class CombatEntity : public Node
{
public:
	virtual bool init(const std::vector<std::string> & actionName, const std::vector<double> & actionTime, const std::vector<int> & actionPlayTime);

	void saveCombatEntityData(const CombatEntityData & combatEntityData);

	void idle();
	void run();
	virtual void attack();
	virtual void hurt();
	void monsterDeath();
	void playerDeath();

	void changeMonsterState(MonsterState monsterState);

protected:
	CombatEntity();
	virtual ~CombatEntity();

protected:
	Sprite* m_pSprite;

	std::string m_strCharacterName;	//角色名

	int m_iHP;	//血量
	int m_iAttack;	//普通攻击力
	int m_iMoney;	//分数/金钱
	int m_iXMaxSpeed;	//X轴设定速度
	int m_iYMaxSpeed;	//Y轴设定速度

	bool m_bIsMonster;	//是否是怪物
	bool m_bIsRight;	//是否向右

	//bool m_bIsWait;		//待机状态
	//bool m_bIsMove;		//移动移动
	//bool m_bIsAttack;	//攻击状态
	//bool m_bIsAttacked;	//被攻击状态

	MonsterState m_enMonsterState;	//初始状态
	ActionState m_enActionState;
};

#endif // !__COMBAT_ENTITY_H__
