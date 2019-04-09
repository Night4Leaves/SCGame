#include "BossFlyingObject.h"

BossFlyingObject * BossFlyingObject::create(BossFlyingObjectInfo info)
{
	BossFlyingObject *pRet = new(std::nothrow) BossFlyingObject();
	if (pRet && pRet->init(info))
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

bool BossFlyingObject::init(BossFlyingObjectInfo info)
{
	m_strObjectName = info.str_name.c_str();
	m_vec2CurrentPoint = info.point_currentPoint;
	m_vec2TargetPoint = info.point_targtPoint;
	m_bIsBeam = info.b_isBeam;
	m_bIsRight = info.b_isRight;

	//创建飞行物对象
	std::string waitAnimationName = StringUtils::format("%s.png", m_strObjectName);
	m_pSprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	m_pSprite->setFlipX(m_bIsRight);

	this->addChild(m_pSprite);
	this->setPosition(m_vec2CurrentPoint);
	
	return true;
}

void BossFlyingObject::update(float dt)
{
	Point pos = this->getPosition();
	
	if (m_bIsBeam)
	{
		if (m_bIsRight)
		{
			pos.x += 8;
			if (pos.x > m_vec2TargetPoint.x)
			{
				pos.x = m_vec2TargetPoint.x;
			}
		}
		else
		{
			pos.x -= 8;
			if (pos.x < m_vec2TargetPoint.x)
			{
				pos.x = m_vec2TargetPoint.x;				
			}
		}
	}
	else
	{
		pos.y -= 10;
		if (pos.y < m_vec2TargetPoint.y)
		{
			pos.y = m_vec2TargetPoint.y;			
		}
	}

	this->setPosition(pos);

	if ((m_bIsBeam && pos.x == m_vec2TargetPoint.x)
		|| (!m_bIsBeam && pos.y == m_vec2TargetPoint.y))
	{
		this->unscheduleUpdate();
		this->stopFlying(NULL);
	}
	
}

void BossFlyingObject::stopFlying(Ref * pSender)
{
	FadeOut* fadeOut = FadeOut::create(0.2);
	m_pSprite->runAction(fadeOut);
}

BossFlyingObject::BossFlyingObject()
{
}

BossFlyingObject::~BossFlyingObject()
{
}
