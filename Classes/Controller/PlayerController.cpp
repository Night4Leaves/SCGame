#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

bool PlayerController::init()
{
	this->m_iXSpeed = 0;
	this->m_iYSpeed = 0;
	this->m_bIsRight = true;
	this->m_iIsRun = 0;
	this->m_bIsJump = false;
	this->m_bIsclimb = false;

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
	pos.x += this->m_iXSpeed;
	m_pControllerListener->setTargetPosition(pos);

}

void PlayerController::checkControllerStatus()
{
	//如果是跳跃状态
	if (this->m_bIsJump)
	{
		this->m_bIsJump = false;	//取消跳跃状态

		//如果左右移动计数器不为0
		if (this->m_iIsRun != 0)
		{
			//根据角色朝向设置位移速度
			if (this->m_bIsRight)
			{
				this->m_iXSpeed = 4;
			}
			else
			{
				this->m_iXSpeed = -4;
			}

			//设置角色朝向
			m_pControllerListener->turnAround(this->m_bIsRight);
			//设置角色跑动动画
			m_pControllerListener->run();
		}
		//如果左右移动计数器为0
		else
		{
			this->m_iXSpeed = 0;	//角色位移速度置0

			//设置角色待机动画
			m_pControllerListener->idle();
		}
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

		this->m_iIsRun++;	//左右移动按键计数器+1
		this->m_bIsRight = false;	//设置为向左

		//如果是跳跃状态则不执行后续代码
		if (this->m_bIsJump)
		{
			break;
		}

		this->m_iXSpeed = -4;	//设置速度为-4（向左位移）

		//设置角色朝向
		m_pControllerListener->turnAround(this->m_bIsRight);
		//设置角色跑动动画
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_D:	//向右移动，参考上面向左移动代码注释

		this->m_iIsRun++;
		this->m_bIsRight = true;

		if (this->m_bIsJump)
		{
			break;
		}

		this->m_iXSpeed = 4;

		m_pControllerListener->turnAround(this->m_bIsRight);
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_J:
		//this->m_iXSpeed = 0;
		//m_pControllerListener->attack();
		break;
	case EventKeyboard::KeyCode::KEY_K:

		//如果已经是跳跃状态则不执行后续代码
		if (this->m_bIsJump)
		{
			break;
		}

		this->m_bIsJump = true;	//设置为跳跃状态
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

		this->m_iIsRun--;	//左右移动按键计数器-1

		//如果是跳跃状态则不执行后续代码
		if (this->m_bIsJump)
		{
			break;
		}

		//如果角色朝向左边
		if (!this->m_bIsRight)
		{
			//如果左右移动按键计数器归0（即没有控制左右移动的按键被按下）
			if (this->m_iIsRun == 0)
			{
				this->m_iXSpeed = 0;	//速度置0
				m_pControllerListener->idle();	//设置角色待机动画
			}
			//如果左右移动按键计数器没有归0（即控制向右的按键依然按下）
			else
			{
				this->m_iXSpeed = -this->m_iXSpeed;	//速度设置为反向速度
				this->m_bIsRight = !this->m_bIsRight;	//角色朝向设置为相反朝向
				m_pControllerListener->turnAround(this->m_bIsRight);	//设置角色朝向
			}
		}	

		break;
	case EventKeyboard::KeyCode::KEY_D:	//取消向右移动，参考上面取消向左移动代码注释

		this->m_iIsRun--;

		if (this->m_bIsJump)
		{
			break;
		}

		if (this->m_bIsRight)
		{
			if (this->m_iIsRun == 0)
			{
				this->m_iXSpeed = 0;
				m_pControllerListener->idle();
			}
			else
			{
				this->m_iXSpeed = -this->m_iXSpeed;
				this->m_bIsRight = !this->m_bIsRight;
				m_pControllerListener->turnAround(this->m_bIsRight);
			}
		}

		break;
	default:
		break;
	}
}
