#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Monster : public Entity, public GeneralControllerListener
{
public:
	static Monster* create(const char* str_monsterName);
	virtual bool init(const char* str_monsterName);

	void setController(SCController* controller);

	//获取角色坐标
	virtual Vec2 getTargetPosition();
	/**
	 *	设置角色坐标
	 *	@pos 目标位置
	 */
	virtual void setTargetPosition(Vec2 pos);
	//检查控制器状态
	void checkControllerStatus();

	/**
	 *	控制角色是否朝右
	 *	@b_isRight true为向右，false向左
	 */
	virtual void turnAround(bool b_isRight);

	virtual void idle();
	virtual void run();
	virtual void attack();
	virtual void jump();
	virtual void climb();
	virtual void hurt();
	virtual void death();

private:
	Monster();
	virtual ~Monster();

	//记录控制器
	SCController* m_pMonsterController;
	//记录角色名，用于生成角色动画
	const char* m_strMonsterName;
	//角色动作名
	std::vector<const char*> m_strActionName = { "idle","run","attack","hurt","death" };
	//动画帧间隔时间
	float m_fActionTime[7] = { 0.25f, 0.2f, 0.15f, 0.1f, 0.25f };
	//动画重复次数
	int m_iActionPlayTime[7] = { -1, -1, 1, 1, 1 };
	//int m_iActionPlayTime[7] = { -1, -1, -1, -1, -1 };
};

#endif // !__MONSTER_H__
