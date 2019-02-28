#pragma once
#ifndef __FLYING_OBJECT_H__
#define __FLYING_OBJECT_H__

#include "Entity.h"

#define HORIZONTAL_DISTANCE 150
#define VERTICAL_DISTANCE 0

class FlyingObject : public Entity
{
public:
	FlyingObject();
	~FlyingObject();

protected:
	const char* m_strObjectName;	//飞行物名称
	Vec2 m_vec2Speed;	//飞行物速度
	Point m_vec2FlightDistance;		//飞行距离

	float m_fXSpeed;	//X轴速度
	float m_fYSpeed;	//Y轴速度

	float m_fXFlightDistance;	//X轴飞行距离
	float m_fYFlightDistance;	//Y轴飞行距离

	Point m_vec2CurrentPoint;	//初始坐标
	Point m_vec2TargetPoint;	//目标坐标，视情况可理解为消失坐标
	Point m_vec2LauncherPoint;	//发射台发射时坐标

	bool m_bIsRight;	//飞行方向是否向右
	bool m_bIsUserEffective;	//是否为有效状态

};

#endif // !__FLYING_OBJECT_H__
