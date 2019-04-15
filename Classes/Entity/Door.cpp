#include "Door.h"

bool Door::init()
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_pSprite = Sprite::createWithSpriteFrameName("door.png");
		this->addChild(m_pSprite);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(Door::openDoor),
			"open_door",
			NULL);

		this->scheduleUpdate();

		return true;
	} while (0);
	return false;
}

void Door::update(float dt)
{
	Point pos = getPosition();
	Size size = m_pSprite->getContentSize();
	int num = pos.x - size.width / 2;
	NotificationCenter::getInstance()->postNotification("stop_at_door", (Ref*)num);
}

Door::Door()
{
}

Door::~Door()
{
}

void Door::openDoor(Ref * pSender)
{
	this->unscheduleUpdate();
	auto fadeOut = FadeOut::create(0.1);
	m_pSprite -> runAction(fadeOut);
	NotificationCenter::getInstance()->removeAllObservers(this);
}
