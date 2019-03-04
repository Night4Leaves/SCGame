#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Player : public Entity, public GeneralControllerListener
{
public:
	static Player* create(const char* str_playerName);
	virtual bool init(const char* str_playerName);

	const char* getSpriteName();
	void setController(SCController* controller);
	virtual Size getCollisionSize();
	virtual Vec2 getTargetPosition();
	virtual void setTargetPosition(Vec2 pos);

	//检查控制器状态
	void checkControllerStatus();

	virtual void turnAround(bool b_isRight);

	virtual void idle();
	virtual void run();
	virtual void attack();
	virtual void jump();
	virtual void climb();
	virtual void hurt();
	virtual void death();

private:
	Player();
	virtual ~Player();

	//记录控制器
	SCController* m_pPlayerController;
	//记录角色名，用于生成角色动画
	const char* m_strPlayerName;
	//角色动作名
	std::vector<const char*> m_strActionName = { "idle","run","attack","jump","climb","hurt","death" };
	//动画帧间隔时间
	float m_fActionTime[7] = { 0.25f, 0.04f, 0.1f, 0.25f, 0.1f, 0.1f, 0.25f };
	//动画重复次数
	int m_iActionPlayTime[7] = { -1, -1, 1, 1, -1, 1, 1 };

};

#endif // !__PLAYER_H__
