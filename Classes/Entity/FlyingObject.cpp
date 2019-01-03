#include "FlyingObject.h"
#include "Util/AnimationUtil.h"

void FlyingObject::setXSpeed(float i_speed)
{
	m_fXSpeed = i_speed;
}

int FlyingObject::getXSpeed()
{
	return m_fXSpeed;
}

void FlyingObject::setYSpeed(float i_speed)
{
	m_fYSpeed = i_speed;
}

int FlyingObject::getYSpeed()
{
	return m_fYSpeed;
}

void FlyingObject::setCurrentPoint(Point vec2_currentPoint)
{
	m_vec2CurrentPoint = vec2_currentPoint;
}

void FlyingObject::setTargetPoint(Point vec2_targetPoint)
{
	m_vec2TargetPoint = vec2_targetPoint;
}

void FlyingObject::setFlightDistance(Point vec2_changeDistance)
{
	m_vec2FlightDistance = vec2_changeDistance;
}

FlyingObject::FlyingObject()
{
	Point m_vec2FlightDistance = Point();
	bool m_bIsRight = true;
	float m_fXSpeed = 0.0f;
	float m_fYSpeed = 0.0f;
	Point m_vec2CurrentPoint = Point();
	Point m_vec2TargetPoint = Point();
}

FlyingObject::~FlyingObject()
{
}