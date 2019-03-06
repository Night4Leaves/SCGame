#pragma once
#ifndef __CUSTOMIZE_STRUCT_H__
#define __CUSTOMIZE_STRUCT_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 *	玩家信息
 *	@str_playerName	玩家名
 *	@str_characterName	角色名
 *	@i_hp	角色血量
 *	@i_attack	角色攻击力
 *	@i_money	角色分数/金钱
 *	@map_backpackItems	背包物品
 *	@map_skillList	技能列表
 *	@i_level	等级(解锁情况)
 */
struct PlayerData
{
	std::string str_playerName;
	std::string str_characterName;
	int i_HP;
	int i_attack;
	int i_money = 0;
	std::map<std::string, int> map_backpackItems;
	std::map<std::string, bool> map_skillList;
	int i_level = 1;
};

/**
 *	怪物信息
 *	@str_monsterName	怪物名
 *	@i_hp	怪物血量
 *	@i_attack	怪物攻击力
 *	@i_money	击败怪物后获得的分数/金钱
 *	@i_warningRange	怪物警戒范围
 *	@i_xSpeed	X轴移动速度
 *	@i_ySpeed	Y轴移动速度
 */
struct MonsterData
{
	std::string str_monsterName;
	int i_HP;
	int i_attack;
	int i_money = 0;
	int i_warningRange = 0;
	int i_xSpeed = 0;
	int i_ySpeed = 0;
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

