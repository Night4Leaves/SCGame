#pragma once
#ifndef __COMBAT_ENTITY_H__
#define __COMBAT_ENTITY_H__

#include "CustomizeStruct.h"

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
};

#endif // !__COMBAT_ENTITY_H__
