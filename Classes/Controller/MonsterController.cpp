#include "MonsterController.h"
#include "Entity/AttackFlyingObject.h"

MonsterController::MonsterController()
{
}

MonsterController::~MonsterController()
{
}

bool MonsterController::init()
{
	m_iXSpeed = 0;
	m_iYspeed = 0;
	m_bIsRight = false;
	m_bIsLock = false;
	m_bIsAttack = false;
	m_bIsAttacked = false;
	m_fStateTime = 0;


	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(MonsterController::checkAttckFlyingObjectPath),
		"attack_flying_object_point",
		NULL);

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

	/*if (m_bIsLock)
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
		
	}*/

	if (m_bIsAttacked)
	{


		m_iXSpeed = 0;
		m_iYspeed = 0;

		m_pControllerListener->hurt();
	}

	m_fStateTime += dt;

	Vec2 pos = m_pControllerListener->getTargetPosition();
	pos.x += m_iXSpeed;
	m_pControllerListener->setTargetPosition(pos);

}

void MonsterController::checkControllerStatus()
{
	
}

void MonsterController::checkAttckFlyingObjectPath(Ref * pSender)
{
	FlyingOcjectToMonster* test = (FlyingOcjectToMonster*)pSender;
	Point vec2_currentPoint = test->vec2_currentPoint;
	Point vec2_flightDistance = test->vec2_flightDistance;
	Point vec2_monsterPoing = m_pControllerListener->getTargetPosition();


	float f_xObject = vec2_currentPoint.x;
	float f_yObject = vec2_currentPoint.y;

	float f_xFlight = vec2_flightDistance.x;
	float f_yFlight = vec2_flightDistance.y;

	float f_xCurrent = m_pControllerListener->getTargetPosition().x;
	float f_yCurrent = m_pControllerListener->getTargetPosition().y;
	
	if (abs(f_xFlight + f_xCurrent - vec2_monsterPoing.x) <= 5)
	{
		log("hit");
	}	
	
	//m_bIsAttacked = true;

	return;
}