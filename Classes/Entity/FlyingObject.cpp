#include "FlyingObject.h"
#include "Util/AnimationUtil.h"

FlyingObject::FlyingObject()
{
	m_fXSpeed = 0.0f;
	m_fYSpeed = 0.0f;
	m_fXFlightDistance = 0.0f;
	m_fYFlightDistance = 0.0f;
	m_bIsRight = true;
	m_vec2CurrentPoint = Point();
	m_vec2TargetPoint = Point();
	m_vec2LauncherPoint = Point();
}

FlyingObject::~FlyingObject()
{
}