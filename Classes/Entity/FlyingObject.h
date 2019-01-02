#pragma once
#ifndef __FLYING_OBJECT_H__
#define __FLYING_OBJECT_H__

#include "Entity.h"

class FlyingObject : public Entity
{
public:
	/**
	 *	创建飞行物体
	 *	@str_objectName	飞行物体名称
	 *	@vec2_flightDistance	飞行物体飞行距离，包括X轴和Y轴的飞行距离
	 */
	static FlyingObject* create(const char* str_objectName, Point vec2_flightDistance);
	virtual bool init(const char* str_objectName, Point vec2_flightDistance);
	virtual void update(float dt);


	void setXSpeed(float i_speed);
	int getXSpeed();
	void setYSpeed(float i_speed);
	int getYSpeed();
	void setCurrentPoint(Point vec2_currentPoint);

private:
	FlyingObject();
	~FlyingObject();

	const char* m_strObjectName;	//飞行物名称
	Point m_vec2FlightDistance;		//飞行距离
	float m_fXSpeed = 0;	//X轴速度
	float m_fYSpeed = 0;	//Y轴速度
	Point m_vec2CurrentPoint;	//初始坐标
	Point m_vec2TargetPoint;	//目标坐标，视情况可理解为消失坐标
	bool m_bIsUserEffective;	//是否为有效状态
};

#endif // !__FLYING_OBJECT_H__
