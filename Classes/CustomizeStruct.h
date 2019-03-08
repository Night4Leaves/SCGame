#pragma once
#ifndef __CUSTOMIZE_STRUCT_H__
#define __CUSTOMIZE_STRUCT_H__

#include "cocos2d.h"

USING_NS_CC;

/**
*	作战实体信息
*	@str_characterName角色名
*	@i_hp	角色血量
*	@i_attack	角色攻击力
*	@i_money	角色分数/金钱
*	@i_xSpeed	X轴移动速度
*	@i_ySpeed	Y轴移动速度
*	@vec_csActionName	角色动作名
*	@p_fActionTime		动画帧间隔时间
*	@p_iActionPlayTime	动画重复次数
*	@b_isMonster	这个角色是否为怪物
*/
struct CombatEntityData
{
	std::string str_characterName;
	int i_HP;
	int i_attack;
	int i_money = 0;
	int i_xSpeed = 0;
	int i_ySpeed = 0;
	std::vector<std::string> vec_csActionName;
	std::vector<double> vec_dActionTime;
	std::vector<int> vec_iActionPlayTime;
	bool b_isMonster = true;
};

/**
 *	玩家信息
 *	@str_playerName	玩家名
 *	@map_backpackItems	背包物品
 *	@map_skillList	技能列表
 *	@i_level	等级(解锁情况)
 */
struct PlayerData : CombatEntityData
{
	std::string str_playerName;
	std::map<std::string, int> map_backpackItems;
	std::map<std::string, bool> map_skillList;
	int i_level = 1;
};

/**
 *	怪物信息
 *	@i_warningRange	怪物警戒范围
 */
struct MonsterData : CombatEntityData
{
	int i_warningRange = 0;
};

/**
*	Boss信息
*	@i_firstSkill	第一技能伤害
*	@i_firstSkillCDTime		第一技能冷却时间
*	@i_secondSkill	第二技能伤害
*	@i_secondSkillCDTime	第二技能冷却时间
*	@i_thirdSkill	第三技能伤害
*	@i_thirdSkillCDTime		第三技能冷却时间
*/
struct BossData : CombatEntityData
{
	int i_firstSkillDamage = 0;
	int i_firstSkillCDTime = 0;
	int i_secondSkillDamage = 0;
	int i_secondSkillCDTime = 0;
	int i_thirdSkillDamage = 0;
	int i_thirdSkillCDTime = 0;
};

/**
 *	NPC种类
 */
enum NPCType
{
	store,	//商店
	skill,	//技能
	normal	//普通
};

/**
 *	NPC设置信息
 *	@cs_name	NPC名字
 *	@npcType	NPC种类
 *	@i_num	NPC动画帧数量
 *	@f_delay	NPC动画帧每帧间隔
 *	@i_loops	动画循环次数
 *	@f_scale	缩放倍数
 */
struct NPCSetInfo
{
	const char* cs_name;
	NPCType npcType = NPCType::normal;
	int i_num = 1;
	float f_delay = 0.1;
	int i_loops = -1;
	float f_scale = 1;
};

/**
 *	飞行物位置信息
 *	@cs_objectName	飞行物名称
 *	@vec2_changeDistance	飞行物飞行距离
 *	@vec2_speed	飞行物速度
 */
struct FlyingObjectInitialInformation
{
	const char* cs_objectName;
	Point vec2_flightDistance;
	Point vec2_speed;
};

/**
 *	飞行物位置信息
 *	@vec2_currentPoint	飞行物起始位置
 *	@b_isRight	飞行物是否朝向右
 *	@vec2_launcherPoint	飞行物发射者位置
 *	@vec2_flightDistance	飞行物飞行距离
 */
struct FlyingObjectPositionInformation
{
	Point vec2_currentPoint;
	bool b_isRight;
	Point vec2_launcherPoint;
	Point vec2_flightDistance;
};

#define poslog(name, x, y) log("%s x:%f, y:%f", name, x, y);

#endif // !__CUSTOMIZE_STRUCT_H__

