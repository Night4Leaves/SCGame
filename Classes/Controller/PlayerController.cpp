#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

bool PlayerController::init()
{
	m_iXSpeed = 0;
	m_iYSpeed = 0;
	m_bIsRight = true;
	m_bIsLock = false;
	m_iHorizontalRun = 0;
	m_iVerticalRun = 0;

	this->scheduleUpdate();

	//注册键盘监听事件
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void PlayerController::update(float dt)
{
	if (m_pControllerListener == nullptr)
	{
		return;
	}

	Vec2 pos = m_pControllerListener->getTargetPosition();
	pos.x += m_iXSpeed;
	pos.y += m_iYSpeed;

	this->setPlayerPosition(pos);
}

bool PlayerController::getIsRight()
{
	return this->m_bIsRight;
}

void PlayerController::setMap(TMXTiledMap * p_map)
{
	m_pMap = p_map;

	Size mapTiledNum = m_pMap->getMapSize();
	Size tiledSize = m_pMap->getTileSize();

	m_fMapWidth = mapTiledNum.width * tiledSize.width;
	m_fMapHeight = mapTiledNum.height * tiledSize.height;
	
	m_pMeta = p_map->getLayer("meta");

	m_pMeta->setVisible(false);

}

void PlayerController::checkControllerStatus()
{
	//如果为锁定状态，则解锁
	if (m_bIsLock)
	{
		m_bIsLock = false;
	}

	//如果左右移动计数器不为0
	if (m_iHorizontalRun != 0)
	{
		//根据角色朝向设置位移速度
		if (m_bIsRight)
		{
			m_iXSpeed = HORIZONTAL_SPPED;
		}
		else
		{
			m_iXSpeed = -HORIZONTAL_SPPED;
		}

		//设置角色朝向
		m_pControllerListener->turnAround(m_bIsRight);
		//设置角色跑动动画
		m_pControllerListener->run();
	}
	//如果左右移动计数器为0
	else
	{
		m_iXSpeed = 0;	//角色位移速度置0

		//设置角色待机动画
		m_pControllerListener->idle();
	}

}

void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		m_iVerticalRun++;

		if (m_bIsLock)
		{
			break;
		}

		m_iYSpeed = VERTICAL_SPEED;

		if (m_iHorizontalRun > 0)
		{
			break;
		}

		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_iVerticalRun++;

		if (m_bIsLock)
		{
			break;
		}

		m_iYSpeed = -VERTICAL_SPEED;

		if (m_iHorizontalRun > 0)
		{
			break;
		}

		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_A:	//向左移动

		m_iHorizontalRun++;	//左右移动按键计数器+1
		m_bIsRight = false;	//设置为向左

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		m_iXSpeed = -HORIZONTAL_SPPED;	//设置速度为-4（向左位移）

		//设置角色朝向
		m_pControllerListener->turnAround(m_bIsRight);
		//设置角色跑动动画
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_D:	//向右移动，参考上面向左移动代码注释

		m_iHorizontalRun++;
		m_bIsRight = true;

		if (m_bIsLock)
		{
			break;
		}

		m_iXSpeed = HORIZONTAL_SPPED;

		m_pControllerListener->turnAround(m_bIsRight);
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_J:	//攻击

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		m_bIsLock = true;	//设置为锁定状态
		m_iXSpeed = 0;	//停止移动
		m_iYSpeed = 0;
		m_pControllerListener->attack();	//调用角色攻击动画

		break;
	case EventKeyboard::KeyCode::KEY_K:	//跳跃

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		m_bIsLock = true;	//设置为锁定状态
		m_iYSpeed = 0;
		m_pControllerListener->jump();	//设置角色跳跃动画

		break;
	case EventKeyboard::KeyCode::KEY_L:
		NotificationCenter::getInstance()->postNotification("player_point", (Ref*)&(m_pControllerListener->getTargetPosition()));
		break;
	default:
		break;
	}
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:	//取消向上移动

		//上下移动按键计数器-1，如果小于0则置0
		m_iVerticalRun--;
		if (m_iVerticalRun < 0)
		{
			m_iVerticalRun = 0;
		}

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		//如果上下移动按键计数器归0（即没有控制上下移动的按键被按下）
		if (m_iVerticalRun == 0)
		{
			m_iYSpeed = 0;

			//如果左右移动按键计数器也归0
			if (m_iHorizontalRun == 0)
			{
				m_pControllerListener->idle();
			}
		}
		else if (m_iYSpeed == VERTICAL_SPEED)	//如果此时为向上移动
		{
			m_iYSpeed = -m_iYSpeed;	//则调整为向下移动
		}
		break;
	case EventKeyboard::KeyCode::KEY_S:	//取消向下移动，参考上面取消向下移动代码注释

		m_iVerticalRun--;
		if (m_iVerticalRun < 0)
		{
			m_iVerticalRun = 0;
		}

		if (m_bIsLock)
		{
			break;
		}

		if (m_iVerticalRun == 0)
		{
			m_iYSpeed = 0;

			if (m_iHorizontalRun == 0)
			{
				m_pControllerListener->idle();
			}
		}
		else if (m_iYSpeed == -VERTICAL_SPEED)
		{
			m_iYSpeed = -m_iYSpeed;
		}

		break;
	case EventKeyboard::KeyCode::KEY_A:	//取消向左移动

		//左右移动按键计数器-1，如果小于0则置0
		m_iHorizontalRun--;
		if (m_iHorizontalRun < 0)
		{
			m_iHorizontalRun = 0;
		}

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		//如果角色朝向左边
		if (!m_bIsRight)
		{
			//如果左右移动按键计数器归0（即没有控制左右移动的按键被按下）
			if (m_iHorizontalRun == 0)
			{
				m_iXSpeed = 0;	//速度置0
				//如果Y轴速度也为0
				if (m_iYSpeed == 0)
				{
					m_pControllerListener->idle();	//设置角色待机动画
				}
			}
			//如果左右移动按键计数器没有归0（即控制向右的按键依然按下）
			else
			{
				m_iXSpeed = -m_iXSpeed;	//速度设置为反向速度
				m_bIsRight = !m_bIsRight;	//角色朝向设置为相反朝向
				m_pControllerListener->turnAround(m_bIsRight);	//设置角色朝向
			}
		}

		break;
	case EventKeyboard::KeyCode::KEY_D:	//取消向右移动，参考上面取消向左移动代码注释

		m_iHorizontalRun--;
		if (m_iHorizontalRun < 0)
		{
			m_iHorizontalRun = 0;
		}

		if (m_bIsLock)
		{
			break;
		}

		if (m_bIsRight)
		{
			if (m_iHorizontalRun == 0)
			{
				m_iXSpeed = 0;
				if (m_iYSpeed == 0)
				{
					m_pControllerListener->idle();
				}
			}
			else
			{
				m_iXSpeed = -m_iXSpeed;
				m_bIsRight = !m_bIsRight;
				m_pControllerListener->turnAround(m_bIsRight);
			}
		}

		break;
	default:
		break;
	}
}

Point PlayerController::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_pMap->getMapSize();
	Size tiledSize = m_pMap->getTileSize();

	float x = pos.x / tiledSize.width * 1.0;

	float y = (m_fMapHeight - pos.y) / tiledSize.height * 1.0;

	if (x - mapTiledNum.width >= 0)
	{
		x = mapTiledNum.width - 1;
	}
	else if (x < 0)
	{
		x = 0;
	}

	if (y - mapTiledNum.height >= 0)
	{
		y = mapTiledNum.height - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}

	return Point(x, y);
}

void PlayerController::setViewPointByPlayer(Point pos)
{
	Node* parent = (Node*)getParent();
	//获得地图中图块的数量和尺寸，并计算出地图尺寸
	Size mapTiledNum = m_pMap->getMapSize();
	Size tiledSize = m_pMap->getTileSize();
	Size mapSize = Size(mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	//获取屏幕显示尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取被控制角色精灵大小尺寸
	Size contentSize = m_pControllerListener->getCollisionSize();
	if (contentSize.width == -1)
	{
		log("Player no sprite!");
		return;
	}

	//与右边界比较，防止跑到右边界外
	float x = std::min(pos.x, mapSize.width - (contentSize.width / 2 - 10));
	//与左边界比较，防止跑到左边界外
	x = std::max(x, contentSize.width / 2 - 10);
	//防止跑到下边界外
	float y = std::max(0.0f, pos.y);

	Point playerPos = Point(x, y);

	m_pControllerListener->setTargetPosition(playerPos);

	//如果主角坐标位于屏幕中点的左下方，则取屏幕中点坐标，否则取主角坐标
	x = std::max(pos.x, visibleSize.width / 2);
	y = std::max(pos.y, visibleSize.height / 2);
	//如果X、Y的坐标大于右上角的极限值，则取极限值坐标
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//目标点
	Point destPosition = Point(x, y);
	//屏幕中点
	Point centerPosition = Point(visibleSize.width / 2, visibleSize.height / 2);
	//屏幕中点和所要移动的目的点之间的距离
	Point viewPos = centerPosition - destPosition;

	parent->setPosition(viewPos);
}

void PlayerController::setPlayerPosition(Point pos)
{
	Size playerSize = m_pControllerListener->getCollisionSize();

	Point destPos = Point();

	if (m_iXSpeed > 0)
	{
		destPos = Point(pos.x + playerSize.width / 2, pos.y);
	}
	else if (m_iXSpeed < 0)
	{
		destPos = Point(pos.x - playerSize.width / 2, pos.y);
	}
	else
	{
		destPos = pos;
	}

	Point tiledPos = tileCoordForPosition(destPos);
	
	int tiledGid = m_pMeta->getTileGIDAt(tiledPos);

	if (tiledGid != 0)
	{
		Value properties = m_pMap->getPropertiesForGID(tiledGid);

		auto collidableProp = properties.asValueMap().at("Collidable");

		if (collidableProp.asBool())
		{
			return;
		}
	}

	this->setViewPointByPlayer(pos);
}
