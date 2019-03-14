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
	 *	@str_objectName	飞行物体名称
	 */
	static AttackFlyingObject* create(const AtkFlyObjIniInfo &objectInfo);
	virtual bool init(const AtkFlyObjIniInfo &objectInfo);
	virtual void update(float dt);

	/**
	 *	设置飞行物体飞行信息，会根据初始坐标和改变坐标自行计算出目标坐标
	 *	@vec2_currentPoint	飞行物体初始坐标
	 *	@vec2_changeDistance	飞行物体飞行距离，会累加在出事坐标上得出目标坐标
	 *	@vec2_speed	飞行物体飞行速度，X轴与Y轴分开计算
	 *	@b_isRight	飞行物体是否朝向右
	 */
	void setFlyingInformation(AtkFlyObjPosInfo &objectFlyingInfo);

	void stopFlying(Ref* pSender);

private:
	AttackFlyingObject();
	virtual ~AttackFlyingObject();
};

#endif // !__ATTACK_FLYING_OBJECT_H__
