#pragma once
#ifndef __BOSS_H__
#define __BOSS_H__

#include "CombatEntity.h"
#include "GameManager.h"

enum SkillType
{
	en_st_closeCombet,
	en_st_beam,
	en_st_missile,
	en_st_summon,
	en_st_debuff,
	en_st_recovery
};

class Boss : public CombatEntity
{
public:
	virtual bool init(const BossData & bossData);
	virtual void update(float dt);

	void setBossPosition(Point pos);

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

	//怪物死亡
	void bossDeath();

	virtual void firstSkill() = 0;
	virtual void secondSkill() = 0;
	virtual void thirdSkill() = 0;

	virtual void checkBeHit(Ref* pSender);
	virtual void checkDistanceWithPlayer(Ref* pSender);
	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	Boss();
	virtual ~Boss();

	HpBar* m_pHPBar;	//血条

	int m_iMaxHP;		//最大血量
	int m_iXSpeed;	//X轴移速
	int m_iYSpeed;	//Y轴移速
	int m_iFirstSkillDamage;	//第一技能伤害
	int m_iFirstSkillCDTime;	//第一技能冷却时间
	int m_iSecondSkillDamage;	//第二技能伤害
	int m_iSecondSkillCDTime;	//第二技能冷却时间
	int m_iThirdSkillDamage;	//第三技能伤害
	int m_iThirdSkillCDTime;	//第三技能冷却时间

	bool m_bIsLock;		//是否为锁死状态
	bool m_bIsactivated;	//是否激活状态

	float m_fStateTime;
	float m_fFirstSkillTime;		//第一技能据上次使用间隔
	float m_fSecondSkillTime;		//第二技能据上次使用间隔
	float m_fThirdSkillTime;		//第三技能据上次使用间隔

	Point m_pointPlayerPos;		//玩家坐标
	SkillType m_enSkillType;	//使用第几种技能

};

#endif // !__BOSS_H__
