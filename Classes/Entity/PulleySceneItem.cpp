#include "PulleySceneItem.h"

PulleySceneItem * PulleySceneItem::create(const SceneItemInfomation & sceneItemInfo)
{
	PulleySceneItem *pRet = new(std::nothrow) PulleySceneItem();
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

void PulleySceneItem::update(float dt)
{
}

void PulleySceneItem::setPulleyPart(PulleyPart pulleyPart)
{
	m_enPulleyPart = pulleyPart;

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PulleySceneItem::runPulley),
		"pulley_run",
		NULL);

	switch (pulleyPart)
	{
	case en_pulleyPart_pulley:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::checkFulcrumPoint),
			"pulley_fulcrum_point",
			NULL);
		break;
	case en_pulleyPart_fulcrum:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::checkEnd),
			"scene_item_move_end",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::changePulleyGroupStatus),
			"pulley_run",
			NULL);
		break;
	case en_pulleyPart_bracket:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::changePulleyGroupStatus),
			"pulley_trigger",
			NULL);
		break;
	case en_pulleyPart_rope:
		break;
	default:
		break;
	}
}

void PulleySceneItem::startPause(Ref * pSender)
{
}

void PulleySceneItem::endPause(Ref * pSender)
{
}

PulleySceneItem::PulleySceneItem()
{
}

PulleySceneItem::~PulleySceneItem()
{
}

void PulleySceneItem::checkEnd(Ref * pSender)
{
	int msg = (int)pSender;
	if (msg != m_enPSIG)
	{
		return;
	}

	Point currentPos = getPosition();
	Size spriteSize = m_pSprite->getContentSize();
	Vec2 checkPoint = Vec2(currentPos.x, currentPos.y - spriteSize.height / 2);

	NotificationCenter::getInstance()->postNotification("pulley_fulcrum_point", (Ref*)&checkPoint);

}

void PulleySceneItem::checkFulcrumPoint(Ref * pSender)
{
	Vec2* checkPoint = (Vec2*)pSender;
	Point currentPos = getPosition();
	Size spriteSize = m_pSprite->getContentSize();

	if (checkPoint->x - spriteSize.width / 2 < currentPos.x
		&& checkPoint->x + spriteSize.width / 2 > currentPos.x
		&& checkPoint->y - 20 < currentPos.y + spriteSize.height / 2
		&& checkPoint->y > currentPos.y + spriteSize.height / 2)
	{
		NotificationCenter::getInstance()->removeObserver(this, "mouse_click_point");
		Point setPos = Point(checkPoint->x, checkPoint->y - 20 - spriteSize.height / 2);

		FadeOut* fadeOut = FadeOut::create(0.5);

		auto statusChange = CallFunc::create(CC_CALLBACK_0(PulleySceneItem::changePulleyStatus, this, setPos));

		FadeIn* fadeIn = FadeIn::create(0.5);

		Sequence* sequence = Sequence::create(fadeOut, statusChange, fadeIn, nullptr);
		m_pSprite->runAction(sequence);

		m_bIsTrigger = true;

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::changePulleyGroupStatus),
			"pulley_run",
			NULL);

		NotificationCenter::getInstance()->postNotification("pulley_trigger");
	}
}

void PulleySceneItem::checkPlayerPoint(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;
	Point currentPoint = getPosition();
	
	if (fabs(playerPoint->x - currentPoint.x) < 50
		&& fabs(playerPoint->y - currentPoint.y) < 50
		&& !m_bIsUsed && m_bIsTrigger)
	{
		NotificationCenter::getInstance()->removeAllObservers(this);
		m_bIsUsed = true;
		NotificationCenter::getInstance()->postNotification("pulley_run");
	}
}

void PulleySceneItem::runPulley(Ref * pSender)
{
	if (m_enPulleyPart == en_pulleyPart_pulley
		|| m_enPulleyPart == en_pulleyPart_fulcrum)
	{
		RotateBy* rotateBy = RotateBy::create(1.0, -90);
		m_pSprite->runAction(RepeatForever::create(rotateBy));
	}
}

void PulleySceneItem::changePulleyStatus(Point setPos)
{
	this->setPosition(setPos);
}

void PulleySceneItem::changePulleyGroupStatus(Ref * pSender)
{
	m_bIsTrigger = true;
	if (m_enPulleyPart == en_pulleyPart_bracket)
	{
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PulleySceneItem::checkPlayerPoint),
			"keyword_l",
			NULL);
	}
}
