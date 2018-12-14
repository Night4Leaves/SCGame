#pragma once
#ifndef __GENERAL_CONTROLLER_LISTENER_H__
#define __GENERAL_CONTROLLER_LISTENER_H__

#include "cocos2d.h"

USING_NS_CC;

class GeneralControllerListener
{
public:
	virtual Vec2 getTargetPosition() = 0;
	virtual void setTargetPosition(Vec2 pos) = 0;

	virtual void setAction(Action* action) = 0;

	virtual void run() = 0;
	virtual void attack() = 0;
	virtual void idle() = 0;
	virtual void hurt() = 0;
	virtual void death() = 0;
	virtual void turnAround(bool isRight) = 0;
};


#endif // !__GENERAL_CONTROLLER_LISTENER_H__
