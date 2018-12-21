#include "MonsterController.h"

MonsterController::MonsterController()
{
}

MonsterController::~MonsterController()
{
}

bool MonsterController::init()
{
	m_iXSpeed = 0;
	m_bIsRight = false;
	m_bIsLock = false;
	m_bIsAttack = false;
	m_fStateTime = 0;

	this->scheduleUpdate();

	return true;
}

void MonsterController::update(float dt)
{
	if (m_pControllerListener == nullptr)
	{
		return;
	}

	//log("%f", m_fStateTime);

	if (m_bIsLock)
	{
		if (m_fStateTime > 6)
		{
			m_iXSpeed = 0;
			m_fStateTime = 0;
			m_bIsLock = false;
			m_bIsRight = !m_bIsRight;
			m_pControllerListener->idle();
		}
	}
	else
	{
		if (m_fStateTime > 5)
		{
			if (m_bIsRight)
			{
				m_iXSpeed = 4;
			}
			else
			{
				m_iXSpeed = -4;
			}
			m_bIsLock = true;
			m_pControllerListener->turnAround(m_bIsRight);
			m_pControllerListener->run();
		}
		
	}

	m_fStateTime += dt;

	Vec2 pos = m_pControllerListener->getTargetPosition();
	pos.x += m_iXSpeed;
	m_pControllerListener->setTargetPosition(pos);

}

void MonsterController::checkControllerStatus()
{
	
}