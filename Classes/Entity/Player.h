#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "CombatEntity.h"
#include "Controller/SCController.h"
#include "PauseDevice.h"

class Player : public CombatEntity, public GeneralControllerListener
{
public:
	static Player* create(const PlayerData & playerData);
	virtual bool init(const PlayerData & playerData);

	void setController(SCController * controller);

	//获取角色尺寸
	virtual Size getCollisionSize();
	//获取角色位置坐标
	virtual Vec2 getTargetPosition();
	//获取角色的速度属性(X轴)
	virtual int getXMaxSpeed();
	//获取角色的速度属性(Y轴)
	virtual int getYMaxSpeed();
	//设置角色位置
	virtual void setTargetPosition(Vec2 pos);
	//角色转身
	virtual void turnAround(bool b_isRight);

	//检查控制器状态
	void checkControllerStatus();

	//待机
	virtual void idle();
	//移动
	virtual void run();
	//攻击
	virtual void attack();
	//跳跃
	virtual void jump();
	//受伤
	virtual void hurt();

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

	virtual void noHP(Ref* pSender);

private:
	Player();
	virtual ~Player();

private:
	SCController* m_pPlayerController;	//记录控制器
};

#endif // !__PLAYER_H__
