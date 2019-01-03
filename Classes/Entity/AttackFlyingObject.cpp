#include "AttackFlyingObject.h"

#include "Util/AnimationUtil.h"

AttackFlyingObject * AttackFlyingObject::create(const char * str_objectName)
{
	AttackFlyingObject *pRet = new(std::nothrow) AttackFlyingObject();
	if (pRet && pRet->init(str_objectName))
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

bool AttackFlyingObject::init(const char * str_objectName)
{
	m_strObjectName = str_objectName;
	m_bIsUserEffective = false;

	std::string waitAnimationName = StringUtils::format("%s_01.png", str_objectName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName(str_objectName, 0.1f, -1);
	Animate* animate = Animate::create(animation);
	sprite->runAction(animate);
	sprite->setOpacity(0);

	return true;
}

void AttackFlyingObject::update(float dt)
{
	Vec2 pos = this->getPosition();
	pos.x += m_fXSpeed;
	if ((m_fXSpeed > 0 && pos.x >= m_vec2TargetPoint.x) || (m_fXSpeed < 0 && pos.x <= m_vec2TargetPoint.x))
	{
		this->setXSpeed(0);
		m_sprite->setOpacity(0);
		m_bIsUserEffective = false;
		this->unscheduleUpdate();
	}
	this->setPosition(pos);
}

void AttackFlyingObject::setFlyingInformation(Point vec2_currentPoint, Point vec2_changeDistance, Point vec2_speed, bool b_isRight)
{
	this->setXSpeed(vec2_speed.x);
	this->setYSpeed(vec2_speed.y);
	this->setCurrentPoint(vec2_currentPoint);
	this->setFlightDistance(vec2_changeDistance);
	
	float x = vec2_currentPoint.x + vec2_changeDistance.x;
	float y = vec2_currentPoint.y + vec2_changeDistance.y;

	Point targetPoint = Point(x, y);
	this->setTargetPoint(targetPoint);

	m_sprite->setFlipX(!b_isRight);
	m_sprite->setOpacity(255);
	m_bIsUserEffective = true;
	this->setPosition(vec2_currentPoint);

	this->scheduleUpdate();
}

AttackFlyingObject::AttackFlyingObject()
{
}

AttackFlyingObject::~AttackFlyingObject()
{
}
