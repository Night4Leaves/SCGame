#include "RailgunSceneItem.h"

RailgunSceneItem * RailgunSceneItem::create(const SceneItemInfomation & sceneItemInfo)
{
	RailgunSceneItem *pRet = new(std::nothrow) RailgunSceneItem();
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

void RailgunSceneItem::update(float dt)
{
	m_fStateTime += dt;
	if (m_fStateTime > 3)
	{
		m_iShellSpeed = 0;
		m_pSprite->setOpacity(0);
		this->unscheduleUpdate();
		NotificationCenter::getInstance()->postNotification("open_door");
		NotificationCenter::getInstance()->removeAllObservers(this);
	}

	Point pos = getPosition();
	pos.x += m_iShellSpeed;
	setPosition(pos);
}

void RailgunSceneItem::setRailgunPart(RailgunPart railgunPart)
{
	m_enRailgunPart = railgunPart;
	switch (railgunPart)
	{
	case en_railgunPart_battery:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::checkPowerBoxPos),
			"railgun_power_box_point",
			NULL);
		break;
	case en_railgunPart_powerBox:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::checkEnd),
			"scene_item_move_end",
			NULL);
		break;
	case en_railgunPart_barrel:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::checkBatteryDirection),
			"railgun_battery_right",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::changeBarrelStatus),
			"railgun_cant_run",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::checkPlayerPoint),
			"keyword_l",
			NULL);
		break;
	case en_railgunPart_shell:
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(RailgunSceneItem::checkShell),
			"railgun_fire",
			NULL);
		break;
	default:
		break;
	}

}

void RailgunSceneItem::startPause(Ref * pSender)
{
	if (m_enRailgunPart == en_railgunPart_shell
		&& m_bIsUsed)
	{
		m_iShellSpeed = 0;
		this->unscheduleUpdate();
	}
}

void RailgunSceneItem::endPause(Ref * pSender)
{
	if (m_enRailgunPart == en_railgunPart_shell
		&& m_bIsUsed)
	{
		m_iShellSpeed = 10;
		this->scheduleUpdate();
	}
}

RailgunSceneItem::RailgunSceneItem()
	: m_fStateTime(0.0)
{
}

RailgunSceneItem::~RailgunSceneItem()
{
}

void RailgunSceneItem::checkEnd(Ref * pSender)
{
	int msg = (int)pSender;
	if (msg != m_enPSIG)
	{
		return;
	}

	Point currentPos = getPosition();

	NotificationCenter::getInstance()->postNotification("railgun_power_box_point", (Ref*)&currentPos);
}

void RailgunSceneItem::checkPlayerPoint(Ref * pSender)
{
	Point* playerPos = (Point*)pSender;
	Point currentPos = getPosition();

	if(fabs(playerPos->x - currentPos.x) < 50
		&& fabs(playerPos->y - currentPos.y) < 50
		&& m_bIsTrigger)
	{
		NotificationCenter::getInstance()->postNotification("railgun_fire", (Ref*)m_bMagnetismRight);
	}
}

void RailgunSceneItem::changeBatteryPos(Point setPos)
{
	this->setPosition(setPos);
}

void RailgunSceneItem::checkPowerBoxPos(Ref * pSender)
{
	Point* powerBoxPos = (Point*)pSender;
	Point currentPos = getPosition();

	if (fabs(powerBoxPos->x - currentPos.x) < 20
		&& fabs(powerBoxPos->y - currentPos.y) < 20)
	{
		Point setPos = Point(powerBoxPos->x, powerBoxPos->y);

		FadeOut* fadeOut = FadeOut::create(0.5);

		auto statusChange = CallFunc::create(CC_CALLBACK_0(RailgunSceneItem::changeBatteryPos, this, setPos));

		FadeIn* fadeIn = FadeIn::create(0.5);

		Sequence* sequence = Sequence::create(fadeOut, statusChange, fadeIn, nullptr);
		m_pSprite->runAction(sequence);

		m_bIsTrigger = true;
		NotificationCenter::getInstance()->postNotification("railgun_battery_right", (Ref*)m_bBatteryRight);
	}
	else
	{
		NotificationCenter::getInstance()->postNotification("railgun_cant_run");
	}
}

void RailgunSceneItem::checkBatteryDirection(Ref * pSender)
{
	bool batteryRight = (bool)pSender;
	if (m_bMagnetismRightCondition == batteryRight)
	{
		m_bMagnetismRight = true;
	}
	else
	{
		m_bMagnetismRight = false;
	}
	m_bIsTrigger = true;
}

void RailgunSceneItem::checkShell(Ref * pSender)
{
	bool barrel = (bool)pSender;
	if (barrel == m_bMagnetismRight)
	{
		return;
	}

	m_iShellSpeed = 10;
	this->scheduleUpdate();
	m_bIsUsed = true;
}

void RailgunSceneItem::changeBarrelStatus(Ref * pSender)
{
	m_bIsTrigger = false;
}
