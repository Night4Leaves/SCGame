#pragma once
#ifndef __CUSTOMIZE_STRUCT_H__
#define __CUSTOMIZE_STRUCT_H__

#include "CustomizeEnum.h"
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
	int i_attackRange = 0;
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
	int i_dataNumber;
	std::map<std::string, int> map_backpackItems;
	std::map<std::string, bool> map_skillList;
	int i_level = 1;
};

/**
 *	怪物信息
 *	@i_warningRange	怪物警戒范围
 *	@i_attackCDTime	攻击间隔
 *	@b_isFlying	是否为飞行
 *	@b_isAttackMove	攻击是否会移动
 */
struct MonsterData : CombatEntityData
{
	int i_warningRange = 0;
	int i_attackCDTime = 0;
	bool b_isFlying = false;
	bool b_isAttackMove = false;
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
 *	@str_npcName	NPC名字
 *	@enum_npcTypes	NPC种类
 *	@f_scale	缩放倍数
 *	@i_num	NPC动画帧数量
 *	@f_delay	NPC动画帧每帧间隔
 *	@i_loops	动画循环次数
 */
struct NPCSetInfo
{
	std::string str_npcName;
	NPCType enum_npcType = NPCType::normal;
	float f_scale = 1;
	int i_num = 1;
	float f_delay = 0.1;
	int i_loops = -1;
	
};

/**
 *	飞行物位置信息
 *	@cs_objectName	飞行物名称
 *	@vec2_changeDistance	飞行物飞行距离
 *	@vec2_speed	飞行物速度
 *	@i_attack	飞行物攻击力
 */
struct FlyingObjectInitialInformation
{
	const char* cs_objectName;
	Point vec2_flightDistance;
	Point vec2_speed;
	int i_attack;
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

/**
 *	飞行物检查信息
 *	@point_checkPoint	飞行物判定位置
 *	@i_attack	飞行物攻击力
 */
struct FlyingObjectCheckInformation
{
	Point point_checkPoint;
	int i_attack;
};

/**
 *	Boss飞行物信息
 *	@str_name	飞行物名称
 *	@point_currentPoint	飞行物起始位置
 *	@point_targtPoint	飞行物目标位置
 *	@b_isRight	飞行物是否朝右
 *	@b_isRight	飞行物是否为光束
 */
struct BossFlyingObjectInfo
{
	std::string str_name;
	Point point_currentPoint;
	Point point_targtPoint;
	bool b_isRight;
	bool b_isBeam;
};

/**
 *	Boss飞行物检查信息
 *	@point_pos	飞行物位置
 *	@b_isBeam	飞行物种类
 */
struct BossFlyingObjectCheck
{
	Point point_pos;
	bool b_isBeam;
};

/**
 *	场景道具信息
 *	@str_itemName	道具名称
 *	@point_setPosition	道具位置
 *	@b_isMoveable	道具是否可移动
 *	@enum_type	道具种类（物理/化学/特殊）
 *	@enum_ph	道具酸碱值（默认中性，化学道具专用）
 *	@enum_psig	道具所属组别(默认无，物理道具专用)
 */
struct SceneItemInfomation
{
	std::string str_itemName;
	Point point_setPosition;
	bool b_isMoveable;
	SceneItemType enum_type;
	PH enum_ph = en_ph_neutral;
	PhysicsSceneItemGroup enum_psig = en_psig_null;
};

/**
 *	携带型道具信息
 *	@str_name	道具名称
 *	@i_num	道具数量
 *	@i_price	道具价格
 *	@en_shopItemType	道具种类
 */
struct ShopItemInfo
{
	std::string str_name;
	int i_num;
	int i_price;
	ShopItemType en_shopItemType;
};

#define poslog(name, x, y) log("%s x:%f, y:%f", name, x, y);

#endif // !__CUSTOMIZE_STRUCT_H__

