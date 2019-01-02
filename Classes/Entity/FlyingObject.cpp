#include "FlyingObject.h"
#include "Util/AnimationUtil.h"

FlyingObject * FlyingObject::create(const char * str_objectName, Point vec2_flightDistance)
{
	FlyingObject *pRet = new(std::nothrow) FlyingObject();
	if (pRet && pRet->init(str_objectName, vec2_flightDistance))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool FlyingObject::init(const char * str_objectName, Point vec2_flightDistance)
{
	m_strObjectName = str_objectName;
	m_vec2FlightDistance = vec2_flightDistance;

	std::string waitAnimationName = StringUtils::format("%s_01.png", str_objectName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName(str_objectName, 0.1f, -1);
	Animate* animate = Animate::create(animation);
	sprite->runAction(animate);

	return true;
}

void FlyingObject::update(float dt)
{
	Vec2 pos = this->getPosition();
	pos.x += m_fXSpeed;
	if (pos.x >= m_vec2TargetPoint.x)
	{
		this->setXSpeed(0);
		m_sprite->setOpacity(0);
		m_bIsUserEffective = false;
		this->unscheduleUpdate();
	}
	this->setPosition(pos);
}

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
	m_sprite->setOpacity(255);
	m_bIsUserEffective = true;
	this->scheduleUpdate();

	this->setPosition(vec2_currentPoint);
	m_vec2CurrentPoint = vec2_currentPoint;
	vec2_currentPoint += m_vec2FlightDistance;
	m_vec2TargetPoint = vec2_currentPoint;
	log("current x:%f", m_vec2CurrentPoint.x);
	log("target x:%f", m_vec2TargetPoint.x);
}

FlyingObject::FlyingObject()
{
}

FlyingObject::~FlyingObject()
{
}