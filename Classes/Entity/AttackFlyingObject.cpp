#include "AttackFlyingObject.h"

#include "Util/AnimationUtil.h"

AttackFlyingObject * AttackFlyingObject::create(const AtkFlyObjIniInfo & objectInfo)
{
	AttackFlyingObject *pRet = new(std::nothrow) AttackFlyingObject();
	if (pRet && pRet->init(objectInfo))
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

bool AttackFlyingObject::init(const AtkFlyObjIniInfo & objectInfo)
{
	m_strObjectName = objectInfo.str_objectName;
	m_vec2FlightDistance = objectInfo.vec2_flightDistance;
	m_vec2Speed = objectInfo.vec2_speed;
	m_bIsUserEffective = false;

	std::string waitAnimationName = StringUtils::format("%s_01.png", m_strObjectName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName(m_strObjectName, 0.1f, -1);
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
		m_fXSpeed = 0;
		m_sprite->setOpacity(0);
		m_bIsUserEffective = false;
		this->unscheduleUpdate();
	}
	this->setPosition(pos);
}

void AttackFlyingObject::setFlyingInformation(const AtkFlyObjPosInfo & objectFlyingInfo)
{
	m_vec2CurrentPoint = objectFlyingInfo.vec2_currentPoint;
	m_vec2LauncherPoint = objectFlyingInfo.vec2_launcherPoint;
	m_bIsRight = objectFlyingInfo.b_isRight;

	if (!m_bIsRight)
	{
		m_fXSpeed = -m_vec2Speed.x;
		m_fXFlightDistance = -m_vec2FlightDistance.x;
	}
	else
	{
		m_fXSpeed = m_vec2Speed.x;
		m_fXFlightDistance = m_vec2FlightDistance.x;
	}

	float x = m_vec2CurrentPoint.x + m_fXFlightDistance;
	float y = m_vec2CurrentPoint.y + m_fYFlightDistance;
	m_vec2TargetPoint = Point(x, y);

	FlyingOcjectToMonster message = { m_vec2LauncherPoint, m_vec2TargetPoint };

	NotificationCenter::getInstance()->postNotification("attack_flying_object_point", (Ref*)&message);

	m_sprite->setFlipX(!m_bIsRight);
	m_sprite->setOpacity(255);
	m_bIsUserEffective = true;
	this->setPosition(m_vec2CurrentPoint);

	this->scheduleUpdate();
}

AttackFlyingObject::AttackFlyingObject()
{
}

AttackFlyingObject::~AttackFlyingObject()
{
}
