#include "SceneItemLayer.h"

SceneItemLayer::SceneItemLayer()
{
}

SceneItemLayer::~SceneItemLayer()
{
	m_pListener->release();
}

bool SceneItemLayer::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());

		SceneItemInfomation itemInfo = { "scene_item_rod", Point(400, 300), true, en_sceneItem_physics };
		SceneItem* sceneItem = SceneItem::create(itemInfo);
		this->addChild(sceneItem);

		m_pListener = EventListenerTouchOneByOne::create();
		m_pListener->onTouchBegan = [&](Touch* touch, Event* event) {
			log("touch begin");
			Point clickPos = touch->getLocation();
			NotificationCenter::getInstance()->postNotification("mouse_click_point", (Ref*)&clickPos);
			return true;
		};

		m_pListener->onTouchMoved = [](Touch* touch, Event* event) {
			//log("touch move");
			Point clickPos = touch->getLocation();
			NotificationCenter::getInstance()->postNotification("mouse_move_point", (Ref*)&clickPos);
			return true;
		};

		m_pListener->onTouchEnded = [](Touch* touch, Event* event) {
			log("touch end");
			Point clickPos = touch->getLocation();
			NotificationCenter::getInstance()->postNotification("mouse_end_point", (Ref*)&clickPos);
			return true;
		};

		//NotificationCenter::getInstance()->addObserver(
		//	this,
		//	nullptr,
		//	"keyword_k",
		//	NULL);

		m_pListener->setSwallowTouches(true);
		m_pListener->retain();
		_eventDispatcher->removeEventListener(m_pListener);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_pListener, this);

		return true;
	} while (0);
	return false;
}
