#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

bool PlayerController::init()
{
	this->m_iSpeed = 0;
	this->m_bIsRight = true;

	this->scheduleUpdate();

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
	pos.x += this->m_iSpeed;
	m_pControllerListener->setTargetPosition(pos);
	
}

void PlayerController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		this->m_iSpeed = -4;
		this->m_bIsRight = false;
		m_pControllerListener->turnAround(this->m_bIsRight);
		m_pControllerListener->run();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		this->m_iSpeed = 4;
		this->m_bIsRight = true;
		m_pControllerListener->turnAround(this->m_bIsRight);
		m_pControllerListener->run();
		break;
	case EventKeyboard::KeyCode::KEY_J:
		this->m_iSpeed = 0;
		m_pControllerListener->attack();
		break;
	case EventKeyboard::KeyCode::KEY_K:
		m_pControllerListener->jump();
		break;
	default:
		break;
	}
}

void PlayerController::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		this->m_iSpeed = 0;
		m_pControllerListener->idle();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		this->m_iSpeed = 0;
		m_pControllerListener->idle();
		break;
	default:
		break;
	}
}
