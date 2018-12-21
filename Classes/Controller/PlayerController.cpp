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
	m_iIsRun = 0;

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
	m_pControllerListener->setTargetPosition(pos);


	/*log("x: %f, y: %f", pos.x, pos.y);*/

}

void PlayerController::checkControllerStatus()
{
	//如果为锁定状态，则解锁
	if (m_bIsLock)
	{
		m_bIsLock = false;
	}

	//如果左右移动计数器不为0
	if (m_iIsRun != 0)
	{
		//根据角色朝向设置位移速度
		if (m_bIsRight)
		{
			m_iXSpeed = 4;
		}
		else
		{
			m_iXSpeed = -4;
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
		//m_pControllerListener->climb();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		//m_pControllerListener->climb();
		break;
	case EventKeyboard::KeyCode::KEY_A:	//向左移动

		m_iIsRun++;	//左右移动按键计数器+1
		m_bIsRight = false;	//设置为向左

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		m_iXSpeed = -4;	//设置速度为-4（向左位移）

		//设置角色朝向
		m_pControllerListener->turnAround(m_bIsRight);
		//设置角色跑动动画
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_D:	//向右移动，参考上面向左移动代码注释

		m_iIsRun++;
		m_bIsRight = true;

		if (m_bIsLock)
		{
			break;
		}

		m_iXSpeed = 4;

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
		m_pControllerListener->attack();	//调用角色攻击动画

		break;
	case EventKeyboard::KeyCode::KEY_K:	//跳跃

		//如果是锁定状态则不执行后续代码
		if (m_bIsLock)
		{
			break;
		}

		m_bIsLock = true;	//设置为锁定状态
		m_pControllerListener->jump();	//设置角色跳跃动画

		break;
	default:
		break;
	}
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_A:	//取消向左移动

		//左右移动按键计数器-1，如果小于0则置0
		m_iIsRun--;
		if (m_iIsRun < 0)
		{
			m_iIsRun = 0;
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
			if (m_iIsRun == 0)
			{
				m_iXSpeed = 0;	//速度置0
				m_pControllerListener->idle();	//设置角色待机动画
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

		m_iIsRun--;
		if (m_iIsRun < 0)
		{
			m_iIsRun = 0;
		}

		if (m_bIsLock)
		{
			break;
		}

		if (m_bIsRight)
		{
			if (m_iIsRun == 0)
			{
				m_iXSpeed = 0;
				m_pControllerListener->idle();
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
