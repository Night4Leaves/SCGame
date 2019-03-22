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
	//获取飞行物的各属性
	m_iAttack = objectInfo.i_attack;
	m_strObjectName = objectInfo.cs_objectName;
	m_vec2FlightDistance = objectInfo.vec2_flightDistance;
	m_vec2Speed = objectInfo.vec2_speed;
	m_bIsUserEffective = false;

	//创建飞行物对象
	std::string waitAnimationName = StringUtils::format("%s_01.png", m_strObjectName);
	m_pSprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());

	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName(m_strObjectName, 0.1f, -1);
	Animate* animate = Animate::create(animation);
	m_pSprite->runAction(animate);
	m_pSprite->setOpacity(0);
	this->addChild(m_pSprite);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(AttackFlyingObject::stopFlying),
		"stop_flying",
		NULL);

	return true;
}

void AttackFlyingObject::update(float dt)
{
	Vec2 pos = this->getPosition();
	pos.x += m_fXSpeed;

	//到达预定目标，调用停止飞行函数
	if ((m_fXSpeed > 0 && pos.x >= m_vec2TargetPoint.x) || (m_fXSpeed < 0 && pos.x <= m_vec2TargetPoint.x))
	{
		this->stopFlying(NULL);
	}

	float spriteWidth = m_pSprite->getContentSize().width;

	this->setPosition(pos);

	//还在飞行则把坐标发送给怪物
	if (m_fXSpeed > 0)
	{
		Point checkPoint = Point(pos.x + spriteWidth, pos.y);
		AtkFlyObjChkInfo checkInfo = { checkPoint, m_iAttack };
		NotificationCenter::getInstance()->postNotification("attack_flying_object_check_point", (Ref*)&checkInfo);
	}
	else if (m_fXSpeed < 0)
	{
		Point checkPoint = Point(pos.x - spriteWidth, pos.y);
		AtkFlyObjChkInfo checkInfo = { checkPoint, m_iAttack };
		NotificationCenter::getInstance()->postNotification("attack_flying_object_check_point", (Ref*)&checkInfo);
	}
}

void AttackFlyingObject::setFlyingInformation(AtkFlyObjPosInfo & objectFlyingInfo)
{
	m_vec2CurrentPoint = objectFlyingInfo.vec2_currentPoint;
	m_vec2LauncherPoint = objectFlyingInfo.vec2_launcherPoint;
	m_bIsRight = objectFlyingInfo.b_isRight;

	//根据飞行方向设置速度
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

	//把预定飞行轨迹发送给怪物
	objectFlyingInfo.vec2_flightDistance = Point(m_fXFlightDistance, m_fYFlightDistance);
	NotificationCenter::getInstance()->postNotification("attack_flying_object_point", (Ref*)&objectFlyingInfo);

	m_pSprite->setFlipX(!m_bIsRight);
	m_pSprite->setOpacity(255);
	m_bIsUserEffective = true;
	this->setPosition(m_vec2CurrentPoint);

	this->scheduleUpdate();
}

void AttackFlyingObject::stopFlying(Ref * pSender)
{
	m_fXSpeed = 0;
	m_pSprite->setOpacity(0);
	m_bIsUserEffective = false;
	this->unscheduleUpdate();
	return;
}

AttackFlyingObject::AttackFlyingObject()
{
}

AttackFlyingObject::~AttackFlyingObject()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}
