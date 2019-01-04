#pragma once
#ifndef __CUSTOMIZE_STRUCT_H__
#define __CUSTOMIZE_STRUCT_H__

#include "cocos2d.h"

USING_NS_CC;

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
 *	@name	NPC名字
 *	@npcType	NPC种类
 *	@num	NPC动画帧数量
 *	@delay	NPC动画帧每帧间隔
 *	@loops	动画循环次数
 *	@scale	缩放倍数
 */
struct NPCSetInfo
{
	const char* name;
	NPCType npcType = NPCType::normal;
	int num = 1;
	float delay = 0.1;
	int loops = -1;
	float scale = 1;
};

/**
 *	飞行物位置信息
 *	@str_objectName	飞行物名称
 *	@vec2_changeDistance	飞行物飞行距离
 *	@vec2_speed	飞行物速度
 */
struct FlyingObjectInitialInformation
{
	const char* str_objectName;
	Point vec2_flightDistance;
	Point vec2_speed;
};

/**
 *	飞行物位置信息
 *	@vec2_currentPoint	飞行物起始位置
 *	@b_isRight	飞行物是否朝向右
 *	@vec2_launcherPoint	飞行物发射者位置
 */
struct FlyingObjectPositionInformation
{
	Point vec2_currentPoint;
	bool b_isRight;
	Point vec2_launcherPoint;
};

/**
 *	飞行物发送给怪物的信息结构
 *	@vec2_lanucherPoint	飞行物发射台
 *	@vec2_targetPoint	飞行物目标点
 */
struct FlyingOcjectToMonster
{
	Point vec2_lanucherPoint;
	Point vec2_targetPoint;
};

#define poslog(name, x, y) log("%s x:%f, y:%f", name, x, y);

#endif // !__CUSTOMIZE_STRUCT_H__

