#pragma once
#ifndef __CUSTOMIZE_STRUCT_H__
#define __CUSTOMIZE_STRUCT_H__

#include "cocos2d.h"

USING_NS_CC;

/**
 *	玩家信息
 *	@str_name	角色名
 *	@i_hp	角色血量
 *	@i_attack	角色攻击力
 */
struct PlayerInfomation
{
	std::string str_name;
	int i_hp;
	int i_attack;
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

