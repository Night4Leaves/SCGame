#pragma once
#ifndef __CONTROLLER_LISTENER_H__
#define __CONTROLLER_LISTENER_H__

#include "cocos2d.h"

USING_NS_CC;

class ControllerListener
{
public:
	virtual void run() = 0;

	virtual void attack() = 0;

	virtual void idle() = 0;
};

#endif // !__CONTROLLER_LISTENER_H__
