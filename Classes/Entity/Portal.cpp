#include "Portal.h"
#include "CustomizeEnum.h"

bool Portal::init()
{

	Sprite* tpBackSprite = Sprite::createWithSpriteFrameName("tp_back.png");
	Sprite* tpfrontSprite = Sprite::createWithSpriteFrameName("tp_front.png");

	this->bindSprite(tpBackSprite);

	tpBackSprite->addChild(tpfrontSprite);

	Size tpBackSize = tpBackSprite->getContentSize();
	tpfrontSprite->setPosition(tpBackSize.width * 0.5, tpBackSize.height * 0.5);

	auto test1 = RotateBy::create(5.0f, -90.0f);
	auto test2 = RotateBy::create(5.0f, 180.0f);

	tpBackSprite->runAction(RepeatForever::create(test1));
	tpfrontSprite->runAction(RepeatForever::create(test2));

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Portal::checkPlayerPoint),
		"player_check_point",
		NULL);

	return true;
}

void Portal::checkPlayerPoint(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;
	Point portalPoint = this->getPosition();
	Size portalSize = m_pSprite->getContentSize();
	float scale = this->getScale();
	
	float xPlayer = playerPoint->x;
	float yPlayer = playerPoint->y;
	poslog("player", xPlayer, yPlayer);

	float xPortal = portalPoint.x;
	float yPortal = portalPoint.y;
	poslog("portal pos", xPortal, yPortal);

	float portalWidth = portalSize.width * scale;
	float portalHeight = portalSize.height * scale;
	poslog("portal size", portalWidth, portalHeight);

	if ((xPlayer - (xPortal - portalWidth * 0.5)) > 0
		&& (xPlayer - (xPortal + portalWidth * 0.5)) < 0
		&& (yPlayer - (yPortal - portalHeight * 0.5 - 20)) > 0)
	{
		log("activate select game scene");
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref*)en_paneMsg_selectGameScene);
	}
	
}

Portal::Portal()
{
}

Portal::~Portal()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}
