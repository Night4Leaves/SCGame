#include "PlayerController.h"
#include "GameManager.h"
#include "CustomizeStruct.h"
#include "PlayerInfo.h"

PlayerController::PlayerController()
	: m_fMapWidth(0.0)
	, m_fMapHeight(0.0)
	, m_iXSpeed(0)
	, m_iYSpeed(0)
	, m_bIsRight(true)
	, m_bIsLock(false)
	, m_bIsBossBattle(false)
	, m_iHorizontalRun(0)
	, m_iVerticalRun(0)
{
}

PlayerController::~PlayerController()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
	m_pListener->release();
}

bool PlayerController::init()
{
	this->scheduleUpdate();

	checkPos = GameManager::getInstance()->getCheckPoint();
	poslog("test", checkPos.x, checkPos.y);

	//注册键盘监听事件
	m_pListener = EventListenerKeyboard::create();
	m_pListener->onKeyPressed = CC_CALLBACK_2(PlayerController::onKeyPressed, this);
	m_pListener->onKeyReleased = CC_CALLBACK_2(PlayerController::onKeyReleased, this);
	m_pListener->retain();
	setKeywordListenerEnabled(true);
	

	//接收“受到伤害”的消息
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PlayerController::getDamage),
		"monster_attack",
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PlayerController::checkBossObject),
		"boss_flying_object",
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PlayerController::stopAtDoor),
		"stop_at_door",
		NULL);

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
	Size mapTiledNum = p_map->getMapSize();	//获得地图中块的数量
	Size tiledSize = p_map->getTileSize();		//获得地图中块的尺寸

	m_fMapWidth = mapTiledNum.width * tiledSize.width;
	m_fMapHeight = mapTiledNum.height * tiledSize.height;
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
			m_iXSpeed = m_pControllerListener->getXMaxSpeed();
		}
		else
		{
			m_iXSpeed = -m_pControllerListener->getXMaxSpeed();
		}

		//设置角色朝向
		m_pControllerListener->turnAround(m_bIsRight);
		
		m_pControllerListener->run();
	}
	//如果左右移动计数器为0
	else
	{
		m_iXSpeed = 0;	//角色位移速度置0

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

		m_iYSpeed = m_pControllerListener->getYMaxSpeed();

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

		m_iYSpeed = -m_pControllerListener->getYMaxSpeed();

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

		m_iXSpeed = -m_pControllerListener->getXMaxSpeed();	//设置速度为-4（向左位移）

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

		m_iXSpeed = m_pControllerListener->getXMaxSpeed();

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
	case EventKeyboard::KeyCode::KEY_K:
		PlayerInfo::getInstance()->useItem();
		break;
	case EventKeyboard::KeyCode::KEY_L:
		//发送包含角色坐标的消息，让场景可互动对象判定自己是否被触发
		NotificationCenter::getInstance()->postNotification("keyword_l", (Ref*)&(m_pControllerListener->getTargetPosition()));
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
		else if (m_iYSpeed == m_pControllerListener->getYMaxSpeed())	//如果此时为向上移动
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
		else if (m_iYSpeed == -m_pControllerListener->getYMaxSpeed())
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

void PlayerController::startPause(Ref * pSender)
{
	log("PlayerController pause");
	setKeywordListenerEnabled(false);
	this->unscheduleUpdate();
}

void PlayerController::endPause(Ref * pSender)
{
	log("PlayerController end pause");
	setKeywordListenerEnabled(true);
	m_iHorizontalRun = 0;
	m_iVerticalRun = 0;
	m_iXSpeed = 0;
	m_iYSpeed = 0;
	m_pControllerListener->idle();
	this->scheduleUpdate();
}

void PlayerController::setViewPointByPlayer(Point pos)
{
	Node* parent = (Node*)getParent();
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
	float x = std::min(pos.x, m_fMapWidth - (contentSize.width / 2 - 10));
	//与左边界比较，防止跑到左边界外
	if (!m_bIsBossBattle)
	{
		if (x > m_fMapWidth - visibleSize.width)
		{
			m_bIsBossBattle = true;
		}
		x = std::max(x, contentSize.width / 2 - 10);
	}
	else
	{
		x = std::max(x, contentSize.width / 2 - 10 + m_fMapWidth - visibleSize.width);
	}
	
	//防止跑到下边界外
	float y = std::max(0.0f, pos.y);

	Point playerPos = Point(x, y);

	if (checkPos.x != -1
		&& checkPos.y != -1
		&& abs(playerPos.x - checkPos.x) < 10
		&& abs(playerPos.y - checkPos.y) < 10)
	{
		NotificationCenter::getInstance()->postNotification("show_welcome");
	}
	m_pControllerListener->setTargetPosition(playerPos);
	NotificationCenter::getInstance()->postNotification("player_point", (Ref*)&playerPos);

	//如果主角坐标位于屏幕中点的左下方，则取屏幕中点坐标，否则取主角坐标
	if (!m_bIsBossBattle)
	{
		x = std::max(pos.x, visibleSize.width / 2);
	}
	else
	{
		x = std::max(pos.x, m_fMapWidth - visibleSize.width / 2);
	}
	y = std::max(pos.y, visibleSize.height / 2);
	//如果X、Y的坐标大于右上角的极限值，则取极限值坐标
	x = std::min(x, m_fMapWidth - visibleSize.width / 2);
	y = std::min(y, m_fMapHeight - visibleSize.height / 2);

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

	//计算角色移动到该位置后形象边界坐标
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

	//获取坐标所在砖块在块地图中的坐标
	Point tiledPos = GameManager::getInstance()->tileCoordForPosition(destPos);

	bool notGo = GameManager::getInstance()->checkBoolAttribute(tiledPos, "Collidable");

	if (notGo)
	{
		pos.y -= m_iYSpeed;
		m_iYSpeed = 0;
	}

	this->setViewPointByPlayer(pos);
}

void PlayerController::getDamage(Ref* pSender)
{
	m_bIsLock = true;
	m_iXSpeed = 0;
	m_iYSpeed = 0;
	m_pControllerListener->hurt();

}

void PlayerController::setKeywordListenerEnabled(bool value)
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

void PlayerController::checkBossObject(Ref * pSender)
{
	BossFlyingObjectCheck*  check = (BossFlyingObjectCheck*)pSender;
	Point pos = check->point_pos;
	Point playerPos = m_pControllerListener->getTargetPosition();
	Size playerSize = m_pControllerListener->getCollisionSize();

	if (check->b_isBeam)
	{
		if (abs(pos.y - 20 - playerPos.y) < 10
			&& pos.x < playerPos.x + playerSize.width / 2
			&& pos.x > playerPos.x - playerSize.width / 2)
		{
			NotificationCenter::getInstance()->postNotification("monster_attack");
		}
	}
	else
	{
		if (abs(pos.x - playerPos.x) < 10
			&& abs(pos.y - playerPos.y) < 10)
		{
			NotificationCenter::getInstance()->postNotification("monster_attack");
		}
	}
}

void PlayerController::stopAtDoor(Ref * pSender)
{
	int check = (int)pSender;
	Point pos = m_pControllerListener->getTargetPosition();
	if (pos.x > check)
	{
		pos.x = check;
	}
	m_pControllerListener->setTargetPosition(pos);
}
