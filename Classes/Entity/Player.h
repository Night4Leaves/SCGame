#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "CombatEntity.h"
#include "Controller/SCController.h"

class Player : public CombatEntity, public GeneralControllerListener
{
public:
	static Player* create(const PlayerData & playerData);
	virtual bool init(const PlayerData & playerData);

	std::string getSpriteName();
	void setController(SCController * controller);

	virtual Size getCollisionSize();
	virtual Vec2 getTargetPosition();
	virtual int getXMaxSpeed();
	virtual int getYMaxSpeed();
	virtual void setTargetPosition(Vec2 pos);
	virtual void turnAround(bool b_isRight);

	//检查控制器状态
	void checkControllerStatus();

	virtual void idle();
	virtual void run();
	virtual void attack();
	virtual void jump();
	virtual void hurt();

private:
	Player();
	virtual ~Player();

	//记录控制器
	SCController* m_pPlayerController;
	//记录玩家名
	std::string m_strPlayerName;
	//记录玩家背包
	std::map<std::string, int> m_mapBackpackItems;
	//记录玩家技能
	std::map<std::string, bool> m_mapSkillList;
	//记录玩家等级(地图解锁情况)
	int m_iLevel;
};

#endif // !__PLAYER_H__
