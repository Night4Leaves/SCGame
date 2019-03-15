#pragma once
#ifndef __ATTACK_FLYING_OBJECT_H__
#define __ATTACK_FLYING_OBJECT_H__

#include "FlyingObject.h"

typedef FlyingObjectInitialInformation AtkFlyObjIniInfo;
typedef FlyingObjectPositionInformation AtkFlyObjPosInfo;
typedef FlyingObjectCheckInformation AtkFlyObjChkInfo;

class AttackFlyingObject : public FlyingObject
{
public:
	/**
	 *	创建飞行物体
	 *	@objectInfo	飞行物体初始信息
	 */
	static AttackFlyingObject* create(const AtkFlyObjIniInfo &objectInfo);
	virtual bool init(const AtkFlyObjIniInfo &objectInfo);
	virtual void update(float dt);

	/**
	 *	设置飞行物体飞行信息，会根据初始坐标和改变坐标自行计算出目标坐标
	 *	@objectFlyingInfo	飞行物体位置信息
	 */
	void setFlyingInformation(AtkFlyObjPosInfo &objectFlyingInfo);

	void stopFlying(Ref* pSender);

private:
	AttackFlyingObject();
	virtual ~AttackFlyingObject();
};

#endif // !__ATTACK_FLYING_OBJECT_H__
