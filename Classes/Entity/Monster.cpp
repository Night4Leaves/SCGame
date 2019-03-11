#include "Monster.h"
#include "Util/AnimationUtil.h"

Monster::Monster()
	: m_iXSpeed(0)
	, m_iYspeed(0)
	, m_iWarningRange(0)
	, m_bIsRight(false)
	, m_bIsAttack(false)
	, m_bIsAttacked(false)
	, m_bIsDeath(false)
	, m_bIsBattle(false)
	, m_fStateTime(0.0)
{
	srand((unsigned)time(nullptr));
}

Monster::~Monster()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

Monster * Monster::create(const MonsterData & monsterData)
{
	Monster *pRet = new(std::nothrow) Monster();
	if (pRet && pRet->init(monsterData))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Monster::init(const MonsterData & monsterData)
{
	CombatEntity::saveCombatEntityData(monsterData);

	m_iWarningRange = monsterData.i_warningRange;
	
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Monster::checkAttckFlyingObjectPath),
		"attack_flying_object_point",
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Monster::checkDistanceWithPlayer),
		"player_point",
		NULL);

	this->scheduleUpdate();

	return true;
}

void Monster::update(float dt)
{
	if (!m_bIsBattle)
	{
		m_fStateTime += dt;

		if (m_fStateTime > 5)
		{
			m_fStateTime = 0;

			int r = rand() % 2;

			if (r == 1)
			{
				m_iXSpeed = m_iXMaxSpeed;
				m_bIsRight = true;
			}
			else
			{
				m_iXSpeed = -m_iXMaxSpeed;
				m_bIsRight = false;
			}

			m_pSprite->setFlipX(m_bIsRight);
			this->run();
		}
	}

	Point pos = this->getPosition();
	pos.x += m_iXSpeed;

	if (pos.x < m_pointOriginalPos.x - m_iWarningRange)
	{
		pos.x = m_pointOriginalPos.x - m_iWarningRange;
		m_iXSpeed = 0;
		this->idle();
	}
	if (pos.x > m_pointOriginalPos.x + m_iWarningRange)
	{
		pos.x = m_pointOriginalPos.x + m_iWarningRange;
		m_iXSpeed = 0;
		this->idle();
	}

	this->setPosition(pos);
}

void Monster::setMonsterPosition(Point pos)
{
	m_pointOriginalPos = pos;
	setPosition(pos);
}

void Monster::checkAttckFlyingObjectPath(Ref * pSender)
{
	if (m_bIsDeath)
	{
		return;
	}

	FlyingObjectPositionInformation* flyingObjectInfo = (FlyingObjectPositionInformation*)pSender;
	Point vec2_monsterPoint = this->getPosition();

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

	Size size_monsterSize = m_pSprite->getContentSize();

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
			callfuncO_selector(Monster::checkBeHit),
			"attack_flying_object_check_point",
			NULL);
	}
}

void Monster::checkBeHit(Ref * pSender)
{
	if (m_bIsDeath)
	{
		return;
	}

	Point* objectPoint = (Point*)pSender;
	float objectX = objectPoint->x;
	float objectY = objectPoint->y;

	Point monsterPoint = this->getPosition();
	Size monsterSize = m_pSprite->getContentSize() * this->getScale();

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
		this->hurt();
	}
}

void Monster::checkDistanceWithPlayer(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;

	if (playerPoint->x < m_pointOriginalPos.x - m_iWarningRange
		|| playerPoint->x > m_pointOriginalPos.x + m_iWarningRange)
	{
		m_bIsBattle = false;
		return;
	}

	//if (playerPoint->y < m_pointOriginalPos.y - m_iWarningRange
	//	|| playerPoint->y > m_pointOriginalPos.y + m_iWarningRange)
	//{
	//	m_bIsBattle = false;
	//	return;
	//}

	Point monsterPoint = this->getPosition();

	if (playerPoint->x < monsterPoint.x)
	{
		m_iXSpeed = -m_iXMaxSpeed;
		m_bIsRight = false;
	}
	else if(playerPoint->x > monsterPoint.x)
	{
		m_iXSpeed = m_iXMaxSpeed;
		m_bIsRight = true;
	}

	//if (playerPoint->y > monsterPoint.y)
	//{
	//	m_iYspeed = m_iYMaxSpeed;
	//}
	//else if (playerPoint->y < monsterPoint.y)
	//{
	//	m_iYspeed = -m_iYMaxSpeed;
	//}

	m_bIsBattle = true;
}
