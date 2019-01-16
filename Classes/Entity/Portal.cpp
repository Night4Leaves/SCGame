#include "Portal.h"

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
		"player_point",
		NULL);

	return true;
}

void Portal::checkPlayerPoint(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;
	Point portalPoint = this->getPosition();
	Size portalSize = m_sprite->getContentSize();
	float f_scale = this->getScale();
	
	float f_XPlayer = playerPoint->x;
	float f_YPlayer = playerPoint->y;
	poslog("player", f_XPlayer, f_YPlayer);

	float f_XPortal = portalPoint.x;
	float f_YPortal = portalPoint.y;
	poslog("portal pos", f_XPortal, f_YPortal);

	float f_portalWidth = portalSize.width;
	float f_portalHeight = portalSize.height;
	poslog("portal size", f_portalWidth * f_scale, f_portalHeight * f_scale);

	if ((f_XPlayer - (f_XPortal - f_portalWidth * 0.5 * f_scale)) > 0
		&& (f_XPlayer - (f_XPortal + f_portalWidth * 0.5 * f_scale)) < 0
		&& (f_YPlayer - (f_YPortal - f_portalHeight * 0.5 * f_scale - 20)) > 0)
	{
		log("ok");
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", NULL);
	}
	
}

Portal::Portal()
{
}

Portal::~Portal()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}
