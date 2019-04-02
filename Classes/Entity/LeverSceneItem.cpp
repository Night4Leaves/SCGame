#include "LeverSceneItem.h"

LeverSceneItem * LeverSceneItem::create(const SceneItemInfomation & sceneItemInfo)
{
	LeverSceneItem *pRet = new(std::nothrow) LeverSceneItem();
	if (pRet && pRet->init(sceneItemInfo))
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

void LeverSceneItem::update(float dt)
{
	m_fStateTime += dt;
	if (m_fStateTime > 7)
	{
		NotificationCenter::getInstance()->removeAllObservers(this);
		m_pSprite->stopAllActions();
		m_pSprite->setOpacity(0);
		this->unscheduleUpdate();
		return;
	}

	Point pos = getPosition();
	pos.x += m_iStoneSpeed;
	setPosition(pos);
}

bool LeverSceneItem::init(const SceneItemInfomation & sceneItemInfo)
{
	do
	{
		CC_BREAK_IF(!SceneItem::init(sceneItemInfo));

		return true;
	} while (0);

	return false;
}

LeverSceneItem::LeverSceneItem()
	: m_fStateTime(0.0)
{
}

LeverSceneItem::~LeverSceneItem()
{
}

void LeverSceneItem::checkEnd(Ref * pSender)
{
	int msg = (int)pSender;
	if (msg != m_enPSIG)
	{
		return;
	}
	Point currentPos = getPosition();
	if (m_enLeverPart == en_leverPart_fulcrum)
	{
		Size spriteSize = m_pSprite->getContentSize();
		Vec2 checkPoint = Vec2(currentPos.x, currentPos.y + spriteSize.height / 2);

		NotificationCenter::getInstance()->postNotification("fulcrum_point", (Ref*)&checkPoint);
	}
}

void LeverSceneItem::checkFulcrumPoint(Ref * pSender)
{
	Vec2* checkPoint = (Vec2*)pSender;
	Point currentPos = getPosition();
	Size spriteSize = m_pSprite->getContentSize();
	
	if (checkPoint->x > currentPos.x
		&& checkPoint->x < currentPos.x + spriteSize.width / 2
		&& checkPoint->y + 15 > currentPos.y + spriteSize.height / 2
		&& checkPoint->y < currentPos.y - spriteSize.height / 2)
	{
		NotificationCenter::getInstance()->removeObserver(this, "mouse_click_point");
		Point setPos = Point(checkPoint->x, checkPoint->y);

		FadeOut* fadeOut = FadeOut::create(0.5);

		auto statusChange = CallFunc::create(CC_CALLBACK_0(LeverSceneItem::changeRodStatus, this, setPos));

		FadeIn* fadeIn = FadeIn::create(0.5);

		Sequence* sequence = Sequence::create(fadeOut, statusChange, fadeIn, nullptr);
		m_pSprite->runAction(sequence);
		
		m_bIsTrigger = true;
	}
}

void LeverSceneItem::changeRodStatus(Point setPos)
{
	m_pSprite->setAnchorPoint(Vec2(0.75, 0));
	this->setPosition(setPos);
	this->setRotation(25.0f);
}

void LeverSceneItem::changeStoneStatus(Ref * pSender)
{
	if (!m_bIsUsed)
	{
		m_bIsUsed = true;
		this->scheduleUpdate();
		m_iStoneSpeed = 9;
		RotateBy* rotateBy = RotateBy::create(0.5, 90.0);
		m_pSprite->runAction(RepeatForever::create(rotateBy));
		NotificationCenter::getInstance()->removeObserver(this, "stone_rush");
	}
	
}

void LeverSceneItem::setLeverPart(LeverPart leverPart)
{
	m_enLeverPart = leverPart;
	switch (leverPart)
	{
	case en_leverPart_fulcrum:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(LeverSceneItem::checkEnd),
			"scene_item_move_end",
			NULL);
		break;
	case en_leverPart_rod:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(LeverSceneItem::checkPlayerPoint),
			"keyword_l",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(LeverSceneItem::checkFulcrumPoint),
			"fulcrum_point",
			NULL);
		break;
	case en_leverPart_stone:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(LeverSceneItem::changeStoneStatus),
			"stone_rush",
			NULL);
		break;
	default:
		break;
	}
}

void LeverSceneItem::startPause(Ref * pSender)
{
	m_pSprite->pause();
	if (m_enLeverPart == en_leverPart_stone && m_bIsUsed)
	{
		this->unscheduleUpdate();
	}
}

void LeverSceneItem::endPause(Ref * pSender)
{
	m_pSprite->resume();
	if (m_enLeverPart == en_leverPart_stone && m_bIsUsed)
	{
		this->scheduleUpdate();
	}
}

void LeverSceneItem::checkPlayerPoint(Ref * pSender)
{
	Point* temp = (Point*)pSender;
	Point playerPos = Point(temp->x, temp->y);
	Point itemPos = getPosition();

	if (fabs(playerPos.x - itemPos.x) < 50
		&& fabs(playerPos.y - itemPos.y) < 50
		&& !m_bIsUsed && m_bIsTrigger)
	{
		m_bIsUsed = true;
		RotateBy* rotateBy = RotateBy::create(1.0, -40.0);
		m_pSprite->runAction(rotateBy);
		NotificationCenter::getInstance()->postNotification("stone_rush");
		NotificationCenter::getInstance()->removeObserver(this, "keyword_l");
	}
}