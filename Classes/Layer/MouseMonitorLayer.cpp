#include "MouseMonitorLayer.h"
#include "CustomizeStruct.h"

MouseMonitorLayer::MouseMonitorLayer()
{
}

MouseMonitorLayer::~MouseMonitorLayer()
{
}

bool MouseMonitorLayer::init()
{
	auto test = EventListenerTouchOneByOne::create();

	test->onTouchBegan = [](Touch *touch, Event *event)
	{
		return true;
	};

	//test->onTouchMoved = [&](Touch *touch, Event *event)
	//{
	//};

	test->onTouchEnded = [&](Touch *touch, Event *event)
	{
		Point touchPos = Director::getInstance()->convertToGL(touch->getLocationInView());

		poslog("touchPos", touchPos.x, touchPos.y);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(test, this);

	return true;
}
