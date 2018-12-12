#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Controller/ControllerListener.h"

class Player : public Entity, public ControllerListener
{
public:
	Player();
	~Player();

	CREATE_FUNC(Player);
	virtual bool init();

	virtual void run();
	virtual void attack();
	virtual void idle();
};

#endif // !__PLAYER_H__
