#include "MonsterController.h"
#include "Entity/AttackFlyingObject.h"

MonsterController::MonsterController()
{
}

MonsterController::~MonsterController()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
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
	m_bIsDeath = false;
	m_iMonConFlag = monConFlag;
	++monConFlag;

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(MonsterController::checkAttckFlyingObjectPath),
		"attack_flying_object_point",
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(MonsterController::updateStatus),
		"set_death",
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
	if (m_bIsDeath)
	{
		return;
	}

	FlyingObjectPositionInformation* flyingObjectInfo = (FlyingObjectPositionInformation*)pSender;
	Point vec2_monsterPoint = m_pControllerListener->getTargetPosition();

	float f_xMonster = vec2_monsterPoint.x;
	float f_yMonster = vec2_monsterPoint.y;

	Point vec2_launcherPoint = flyingObjectInfo->vec2_launcherPoint;
	float f_yLauncher = vec2_launcherPoint.y;

	//玩家坐标Y轴和怪物坐标Y轴判断双方是不是一直线
	if (abs(f_yLauncher - f_yMonster) > 7)
	{
		return;
	}

	Point vec2_currentPoint = flyingObjectInfo->vec2_currentPoint;
	float f_xObject = vec2_currentPoint.x;

	Size size_monsterSize = m_pControllerListener->getCollisionSize();

	//飞行物向右，初始位置在怪物右边；或者飞行物向左，初始位置在怪物左边
	if ((flyingObjectInfo->b_isRight && f_xObject - (f_xMonster + size_monsterSize.width / 2) > 0)
		|| (!(flyingObjectInfo->b_isRight) && f_xObject - (f_xMonster - size_monsterSize.width / 2) < 0))
	{
		return;
	}

	Point vec2_flightDistance = flyingObjectInfo->vec2_flightDistance;
	float f_xFlight = vec2_flightDistance.x;

	//玩家怪物一直线的情况下用飞行物的初始位置加飞行距离判断能不能打到怪
	if ((flyingObjectInfo->b_isRight && (f_xObject + f_xFlight) - (f_xMonster - size_monsterSize.width / 2) > 0)
		|| (!(flyingObjectInfo->b_isRight) && (f_xObject + f_xFlight) - (f_xMonster + size_monsterSize.width / 2) < 0))
	{
		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(MonsterController::checkBeHit),
			"attack_flying_object_check_point",
			NULL);
	}

	return;
}

void MonsterController::checkBeHit(Ref * pSender)
{
	if (m_bIsDeath)
	{
		return;
	}

	Point* objectPoint = (Point*)pSender;
	float objectX = objectPoint->x;
	float objectY = objectPoint->y;

	Point monsterPoint = m_pControllerListener->getTargetPosition();
	Size monsterSize = m_pControllerListener->getCollisionSize();

	float monsterYCheck = monsterPoint.y + monsterSize.height / 2;

	if (abs(monsterYCheck - objectY) > 7)
	{
		return;
	}

	float monsterLeftXCheck = monsterPoint.x - monsterSize.width / 2;
	float monsterRightXCheck = monsterPoint.x + monsterSize.width / 2;

	if (objectX > monsterLeftXCheck && objectX < monsterRightXCheck)
	{
		NotificationCenter::getInstance()->postNotification("stop_flying", NULL);
		m_pControllerListener->hurt();
	}
}

void MonsterController::updateStatus(Ref * pSender)
{
	if ((int)pSender == m_iMonConFlag)
	{
		m_bIsDeath = true;
	}
}
