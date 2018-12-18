#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Player : public Entity, public GeneralControllerListener
{
public:
	Player();
	~Player();

	CREATE_FUNC(Player);
	virtual bool init();

	void setController(SCController* controller);
	virtual Vec2 getTargetPosition();
	virtual void setTargetPosition(Vec2 pos);

	//��������״̬
	void checkControllerStatus();

	void setViewPointByPlayer();

	virtual void idle();
	virtual void run();
	virtual void jump();
	virtual void climb();
	virtual void attack();
	virtual void hurt();
	virtual void death();
	virtual void turnAround(bool b_isRight);

private:
	//��¼������
	SCController* m_pPlayerController;
	//��¼��ɫ�����������ɽ�ɫ����
	const char* m_strPlayerName;
};

#endif // !__PLAYER_H__
