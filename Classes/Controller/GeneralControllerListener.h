#pragma once
#ifndef __GENERAL_CONTROLLER_LISTENER_H__
#define __GENERAL_CONTROLLER_LISTENER_H__

#include "cocos2d.h"

USING_NS_CC;

class GeneralControllerListener
{
public:
	/*获取角色坐标*/
	virtual Vec2 getTargetPosition() = 0;
	/*获取角色碰撞体积*/
	virtual Size getCollisionSize() = 0;
	/*获取角色X轴设定速度*/
	virtual int getXMaxSpeed() = 0;
	/*获取角色Y轴设定速度*/
	virtual int getYMaxSpeed() = 0;

	/**
	 *	设置角色坐标
	 *	@pos 目标位置
	 */
	virtual void setTargetPosition(Vec2 pos) = 0;
	/**
	 *	控制角色是否朝右
	 *	@b_isRight true为向右，false向左
	 */
	virtual void turnAround(bool b_isRight) = 0;


	/*待机*/
	virtual void idle() = 0;
	/*移动*/
	virtual void run() = 0;
	/*攻击*/
	virtual void attack() = 0;
	/*跳跃*/
	virtual void jump() = 0;
	/*受伤*/
	virtual void hurt() = 0;

};


#endif // !__GENERAL_CONTROLLER_LISTENER_H__
