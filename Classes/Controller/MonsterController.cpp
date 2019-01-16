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
	FlyingObjectPositionInformation* test = (FlyingObjectPositionInformation*)pSender;
	Point vec2_monsterPoint = m_pControllerListener->getTargetPosition();

	float f_xMonster = vec2_monsterPoint.x;
	float f_yMonster = vec2_monsterPoint.y;

	Point vec2_launcherPoint = test->vec2_launcherPoint;
	float f_yLauncher = vec2_launcherPoint.y;

	//玩家坐标Y轴和怪物坐标Y轴判断双方是不是一直线
	if (abs(f_yLauncher - f_yMonster) > 7)
	{
		return;
	}

	Point vec2_currentPoint = test->vec2_currentPoint;
	float f_xObject = vec2_currentPoint.x;

	Size size_monsterSize = m_pControllerListener->getCollisionSize();

	//飞行物向右，初始位置在怪物右边；或者飞行物向左，初始位置在怪物左边
	if ((test->b_isRight && f_xObject - (f_xMonster + size_monsterSize.width / 2) > 0)
		|| (!(test->b_isRight) && f_xObject - (f_xMonster - size_monsterSize.width / 2) < 0))
	{
		return;
	}

	Point vec2_flightDistance = test->vec2_flightDistance;
	float f_xFlight = vec2_flightDistance.x;

	//玩家怪物一直线的情况下用飞行物的初始位置加飞行距离判断能不能打到怪
	if ((test->b_isRight && (f_xObject + f_xFlight) - (f_xMonster - size_monsterSize.width / 2) > 0)
		|| (!(test->b_isRight) && (f_xObject + f_xFlight) - (f_xMonster + size_monsterSize.width / 2) < 0))
	{
		m_pControllerListener->hurt();
	}

	return;
}