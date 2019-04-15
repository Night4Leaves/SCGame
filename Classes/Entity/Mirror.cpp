#include "Mirror.h"

bool Mirror::init()
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_pSprite = Sprite::createWithSpriteFrameName("scene_item_mirror.png");
		this->addChild(m_pSprite);

		dtCount = 0;

		return true;
	} while (0);
	return false;
}

void Mirror::update(float dt)
{
	dtCount += dt;

	if (dtCount > 5)
	{
		auto fadeOut = FadeOut::create(0.1);
		m_pSprite->runAction(fadeOut);
		this->unscheduleUpdate();
		return;
	}

	Point pos = getPosition();
	NotificationCenter::getInstance()->postNotification("mirror_pos", (Ref*)&pos);
}

Mirror::Mirror()
{
}

Mirror::~Mirror()
{
}

void Mirror::setMirrorPos(Point pos)
{
	setPosition(pos);
	this->scheduleUpdate();
}
