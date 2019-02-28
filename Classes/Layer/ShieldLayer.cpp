#include "ShieldLayer.h"

void ShieldLayer::setTouchEnabled(bool value)
{
	if (value)
	{
		_eventDispatcher->removeEventListener(m_pListener);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pListener, this);
	}
	else
	{
		_eventDispatcher->removeEventListener(m_pListener);
	}
}

ShieldLayer::ShieldLayer()
{
}

ShieldLayer::~ShieldLayer()
{
	m_pListener->release();
}

bool ShieldLayer::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());

		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = [](Touch* touch, Event* event) {
			log("ShieldLayer");
			return true;
		};

		m_pListener->setSwallowTouches(true);
		m_pListener->retain();
		setTouchEnabled(true);

		return true;
	} while (0);
	return false;
}
