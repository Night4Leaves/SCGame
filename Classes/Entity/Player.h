#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Player : public Entity, public PlayerControllerListener
{
public:
	Player();
	~Player();

	CREATE_FUNC(Player);
	virtual bool init();

	void setController(SCController* controller);
	virtual Vec2 getTargetPosition();
	virtual void setTargetPosition(Vec2 pos);

	//¼ì²é¿ØÖÆÆ÷×´Ì¬
	void checkControllerStatus();

	void setViewPointByPlayer();

	virtual void run();
	virtual void jump();

	virtual void attack();
	virtual void idle();
	virtual void hurt();
	virtual void death();
	virtual void climb();
	virtual void turnAround(bool b_isRight);

private:
	//¼ÇÂ¼¿ØÖÆÆ÷
	SCController* m_pPlayerController;
};

#endif // !__PLAYER_H__
