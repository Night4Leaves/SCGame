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

	//ע����̼����¼�
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
	//�������Ծ״̬
	if (this->m_bIsJump)
	{
		this->m_bIsJump = false;	//ȡ����Ծ״̬

		//��������ƶ���������Ϊ0
		if (this->m_iIsRun != 0)
		{
			//���ݽ�ɫ��������λ���ٶ�
			if (this->m_bIsRight)
			{
				this->m_iXSpeed = 4;
			}
			else
			{
				this->m_iXSpeed = -4;
			}

			//���ý�ɫ����
			m_pControllerListener->turnAround(this->m_bIsRight);
			//���ý�ɫ�ܶ�����
			m_pControllerListener->run();
		}
		//��������ƶ�������Ϊ0
		else
		{
			this->m_iXSpeed = 0;	//��ɫλ���ٶ���0

			//���ý�ɫ��������
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
	case EventKeyboard::KeyCode::KEY_A:	//�����ƶ�

		this->m_iIsRun++;	//�����ƶ�����������+1
		this->m_bIsRight = false;	//����Ϊ����

		//�������Ծ״̬��ִ�к�������
		if (this->m_bIsJump)
		{
			break;
		}

		this->m_iXSpeed = -4;	//�����ٶ�Ϊ-4������λ�ƣ�

		//���ý�ɫ����
		m_pControllerListener->turnAround(this->m_bIsRight);
		//���ý�ɫ�ܶ�����
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_D:	//�����ƶ����ο����������ƶ�����ע��

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

		//����Ѿ�����Ծ״̬��ִ�к�������
		if (this->m_bIsJump)
		{
			break;
		}

		this->m_bIsJump = true;	//����Ϊ��Ծ״̬
		m_pControllerListener->jump();	//���ý�ɫ��Ծ����

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
	case EventKeyboard::KeyCode::KEY_A:	//ȡ�������ƶ�

		this->m_iIsRun--;	//�����ƶ�����������-1

		//�������Ծ״̬��ִ�к�������
		if (this->m_bIsJump)
		{
			break;
		}

		//�����ɫ�������
		if (!this->m_bIsRight)
		{
			//��������ƶ�������������0����û�п��������ƶ��İ��������£�
			if (this->m_iIsRun == 0)
			{
				this->m_iXSpeed = 0;	//�ٶ���0
				m_pControllerListener->idle();	//���ý�ɫ��������
			}
			//��������ƶ�����������û�й�0�����������ҵİ�����Ȼ���£�
			else
			{
				this->m_iXSpeed = -this->m_iXSpeed;	//�ٶ�����Ϊ�����ٶ�
				this->m_bIsRight = !this->m_bIsRight;	//��ɫ��������Ϊ�෴����
				m_pControllerListener->turnAround(this->m_bIsRight);	//���ý�ɫ����
			}
		}	

		break;
	case EventKeyboard::KeyCode::KEY_D:	//ȡ�������ƶ����ο�����ȡ�������ƶ�����ע��

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
