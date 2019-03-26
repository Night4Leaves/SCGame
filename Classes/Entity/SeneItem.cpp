#include "SeneItem.h"

SceneItem * SceneItem::create(const SceneItemInfomation & sceneItemInfo)
{
	SceneItem *pRet = new(std::nothrow) SceneItem();
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

bool SceneItem::init(const SceneItemInfomation & sceneItemInfo)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_enSceneItemType = sceneItemInfo.enum_type;
		m_enPH = sceneItemInfo.enum_ph;
		m_bIsMoveable = sceneItemInfo.b_isMoveable;

		std::string spriteName = StringUtils::format("%s.png", sceneItemInfo.str_itemName.c_str());
		m_pSprite = Sprite::createWithSpriteFrameName(spriteName.c_str());
		this->addChild(m_pSprite);
		this->setPosition(sceneItemInfo.point_setPosition);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(SceneItem::checkPlayerPoint),
			"keyword_l",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(SceneItem::checkPlayerPoint),
			"keyword_k",
			NULL);

		if (m_bIsMoveable)
		{
			NotificationCenter::getInstance()->addObserver(
				this,
				callfuncO_selector(SceneItem::mouseClick),
				"mouse_click_point",
				NULL);
		}
		
		return true;
	} while (0);
	return false;
}

SceneItem::SceneItem()
{
}

SceneItem::~SceneItem()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

void SceneItem::checkPlayerPoint(Ref * pSender)
{
}

void SceneItem::mouseClick(Ref * pSender)
{
	Node* parent = (Node*)getParent();	//场景道具层
	parent = (Node*)parent->getParent();	//游戏层
	Point parentPos = parent->getPosition();

	Point* temp = (Point*)pSender;
	Point clickPos = Point(temp->x - parentPos.x, temp->y);
	Point itemPos = getPosition();
	Size itemSize = m_pSprite->getContentSize();

	poslog("clickPos", clickPos.x - parentPos.x, clickPos.y);
	poslog("item", itemPos.x, itemPos.y);

	if (clickPos.x > itemPos.x - itemSize.width / 2
		&& clickPos.x < itemPos.x + itemSize.width / 2
		&& clickPos.y > itemPos.y - itemSize.height / 2
		&& clickPos.y < itemPos.y + itemSize.height / 2)
	{
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(SceneItem::mouseMove),
			"mouse_move_point",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(SceneItem::mouseEnd),
			"mouse_end_point",
			NULL);
	}
}

void SceneItem::mouseMove(Ref * pSender)
{
	Node* parent = (Node*)getParent();	//场景道具层
	parent = (Node*)parent->getParent();	//游戏层
	Point parentPos = parent->getPosition();

	Point* temp = (Point*)pSender;
	Point clickPos = Point(temp->x - parentPos.x, temp->y);
	setPosition(Point(clickPos.x, clickPos.y));
}

void SceneItem::mouseEnd(Ref * pSender)
{
	Node* parent = (Node*)getParent();	//场景道具层
	parent = (Node*)parent->getParent();	//游戏层
	Point parentPos = parent->getPosition();

	Point* temp = (Point*)pSender;
	Point clickPos = Point(temp->x - parentPos.x, temp->y);
	setPosition(Point(clickPos.x, clickPos.y));

	NotificationCenter::getInstance()->removeObserver(this, "mouse_move_point");
	NotificationCenter::getInstance()->removeObserver(this, "mouse_end_point");
}
