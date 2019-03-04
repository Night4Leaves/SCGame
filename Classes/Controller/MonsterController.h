#pragma once
#ifndef __MONSTER_CONTROLLER_H__
#define __MONSTER_CONTROLLER_H__

#include "SCController.h"

class MonsterController : public SCController
{
public:
	MonsterController();
	virtual ~MonsterController();

	CREATE_FUNC(MonsterController);
	virtual bool init();
	virtual void update(float dt);

	//检查控制器记录的角色状态
	virtual void checkControllerStatus();

	void checkAttckFlyingObjectPath(Ref* pSender);
	void checkBeHit(Ref* pSender);

private:
	int m_iXSpeed;	//X轴移速
	int m_iYspeed;	//Y轴移速

	bool m_bIsRight;	//是否向右
	bool m_bIsLock;		//是否为锁死状态
	bool m_bIsAttack;	//攻击状态
	bool m_bIsAttacked;	//被攻击状态

	float m_fStateTime;
};

#endif // !__MONSTER_CONTROLLER_H__
