#pragma once
#ifndef __GENERAL_CONTROLLER_LISTENER_H__
#define __GENERAL_CONTROLLER_LISTENER_H__

#include "cocos2d.h"

USING_NS_CC;

class GeneralControllerListener
{
public:
	//获取角色坐标
	virtual Vec2 getTargetPosition() = 0;
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

	virtual void run() = 0;
	virtual void attack() = 0;
	virtual void idle() = 0;
	virtual void hurt() = 0;
	virtual void death() = 0;
	virtual void climb() = 0;
	virtual void jump() = 0;
	
};


#endif // !__GENERAL_CONTROLLER_LISTENER_H__
