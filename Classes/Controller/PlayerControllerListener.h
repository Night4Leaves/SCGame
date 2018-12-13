#pragma once
#ifndef __PLAYER_CONTROLLER_LISTENER_H__
#define __PLAYER_CONTROLLER_LISTENER_H__

#include "GeneralControllerListener.h"

class PlayerControllerListener : public GeneralControllerListener
{
public:
	virtual void climb() = 0;
	virtual void jump() = 0;
};

#endif // !__PLAYER_CONTROLLER_LISTENER_H__
