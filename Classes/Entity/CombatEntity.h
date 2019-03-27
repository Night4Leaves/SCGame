#pragma once
#ifndef __COMBAT_ENTITY_H__
#define __COMBAT_ENTITY_H__

#include "CustomizeStruct.h"
#include "HpBar.h"
#include "PauseDevice.h"

//怪物状态
enum MonsterState
{
	en_ms_patrol,	//巡逻
	en_ms_warn,		//警戒
	en_ms_attack,	//攻击
	en_ms_attack_end,	//攻击结束
	en_ms_attacked	//被攻击
};

//动作状态
enum ActionState
{
	en_as_null,	//空
	en_as_idle,	//待机
	en_as_move,	//移动
	en_as_attack,	//攻击
	en_as_attacked	//被攻击
};

class CombatEntity :public PauseDevice
{
public:
	/**
	 *	战斗实体初始化函数
	 *	@actionName	动作帧名字
	 *	@actionTime	动作帧间隔时间
	 *	@actionPlayTime	动作播放时间
	 */
	virtual bool init(const std::vector<std::string> & actionName, const std::vector<double> & actionTime, const std::vector<int> & actionPlayTime);

	/**
	 *	保存作战实体数据
	 *	@combatEntityData	作战实体数据结构体
	 */
	void saveCombatEntityData(const CombatEntityData & combatEntityData);

	//待机
	void idle();
	//移动
	void run();
	//攻击
	virtual void attack();
	//受伤
	virtual void hurt();
	//怪物死亡
	void monsterDeath();
	//玩家死亡
	void playerDeath();

	//改变怪物状态
	void changeMonsterState(MonsterState monsterState);

protected:
	CombatEntity();
	virtual ~CombatEntity();

protected:
	Sprite* m_pSprite;	//绑定的角色形象

	std::string m_strCharacterName;	//角色名

	int m_iHP;	//血量
	int m_iAttack;	//普通攻击力
	int m_iMoney;	//分数/金钱
	int m_iXMaxSpeed;	//X轴设定速度
	int m_iYMaxSpeed;	//Y轴设定速度
	int m_iAttackRange;	//攻击距离

	bool m_bIsMonster;	//是否是怪物
	bool m_bIsRight;	//是否向右

	MonsterState m_enMonsterState;	//怪物初始状态
	ActionState m_enActionState;	//动作初始状态
};

#endif // !__COMBAT_ENTITY_H__
