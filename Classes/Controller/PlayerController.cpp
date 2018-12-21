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
	pos.x += m_iXSpeed;
	m_pControllerListener->setTargetPosition(pos);


	/*log("x: %f, y: %f", pos.x, pos.y);*/

}

void PlayerController::checkControllerStatus()
{
	//���Ϊ����״̬�������
	if (m_bIsLock)
	{
		m_bIsLock = false;
	}

	//��������ƶ���������Ϊ0
	if (m_iIsRun != 0)
	{
		//���ݽ�ɫ��������λ���ٶ�
		if (m_bIsRight)
		{
			m_iXSpeed = 4;
		}
		else
		{
			m_iXSpeed = -4;
		}

		//���ý�ɫ����
		m_pControllerListener->turnAround(m_bIsRight);
		//���ý�ɫ�ܶ�����
		m_pControllerListener->run();
	}
	//��������ƶ�������Ϊ0
	else
	{
		m_iXSpeed = 0;	//��ɫλ���ٶ���0

		//���ý�ɫ��������
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
	case EventKeyboard::KeyCode::KEY_A:	//�����ƶ�

		m_iIsRun++;	//�����ƶ�����������+1
		m_bIsRight = false;	//����Ϊ����

		//���������״̬��ִ�к�������
		if (m_bIsLock)
		{
			break;
		}

		m_iXSpeed = -4;	//�����ٶ�Ϊ-4������λ�ƣ�

		//���ý�ɫ����
		m_pControllerListener->turnAround(m_bIsRight);
		//���ý�ɫ�ܶ�����
		m_pControllerListener->run();

		break;
	case EventKeyboard::KeyCode::KEY_D:	//�����ƶ����ο����������ƶ�����ע��

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
	case EventKeyboard::KeyCode::KEY_J:	//����

		//���������״̬��ִ�к�������
		if (m_bIsLock)
		{
			break;
		}

		m_bIsLock = true;	//����Ϊ����״̬
		m_iXSpeed = 0;	//ֹͣ�ƶ�
		m_pControllerListener->attack();	//���ý�ɫ��������

		break;
	case EventKeyboard::KeyCode::KEY_K:	//��Ծ

		//���������״̬��ִ�к�������
		if (m_bIsLock)
		{
			break;
		}

		m_bIsLock = true;	//����Ϊ����״̬
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

		//�����ƶ�����������-1�����С��0����0
		m_iIsRun--;
		if (m_iIsRun < 0)
		{
			m_iIsRun = 0;
		}

		//���������״̬��ִ�к�������
		if (m_bIsLock)
		{
			break;
		}

		//�����ɫ�������
		if (!m_bIsRight)
		{
			//��������ƶ�������������0����û�п��������ƶ��İ��������£�
			if (m_iIsRun == 0)
			{
				m_iXSpeed = 0;	//�ٶ���0
				m_pControllerListener->idle();	//���ý�ɫ��������
			}
			//��������ƶ�����������û�й�0�����������ҵİ�����Ȼ���£�
			else
			{
				m_iXSpeed = -m_iXSpeed;	//�ٶ�����Ϊ�����ٶ�
				m_bIsRight = !m_bIsRight;	//��ɫ��������Ϊ�෴����
				m_pControllerListener->turnAround(m_bIsRight);	//���ý�ɫ����
			}
		}	

		break;
	case EventKeyboard::KeyCode::KEY_D:	//ȡ�������ƶ����ο�����ȡ�������ƶ�����ע��

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
