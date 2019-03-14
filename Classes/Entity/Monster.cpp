#include "Monster.h"
#include "Util/AnimationUtil.h"

Monster::Monster()
	: m_iXSpeed(0)
	, m_iYSpeed(0)
	, m_iWarningRange(0)
	, m_iAttackCDTime(0)
	, m_bIsDeath(false)
	, m_fStateTime(0.0)
	, m_fAttackTime(0.0)
{
	srand((unsigned)time(nullptr));
}

Monster::~Monster()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

void Monster::patrolLogic()
{
	if (m_fStateTime > 5)
	{
		m_fStateTime = 0;

		int r = rand() % 2;
		int j = rand() % 2;

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

		if (j == 1)
		{
			m_iYSpeed = m_iYMaxSpeed;
		}
		else
		{
			m_iYSpeed = -m_iYMaxSpeed;
		}

		m_pSprite->setFlipX(m_bIsRight);
		this->run();
	}
}

void Monster::warnLogic()
{
	Point monsterPoint = this->getPosition();

	if (abs(m_pointPlayerPos.y - monsterPoint.y) >= 8)
	{
		if (m_pointPlayerPos.y > monsterPoint.y)
		{
			m_iYSpeed = m_iYMaxSpeed;
		}
		else if (m_pointPlayerPos.y < monsterPoint.y)
		{
			m_iYSpeed = -m_iYMaxSpeed;
		}
	}
	else
	{
		m_iYSpeed = 0;
	}
	
	if (m_pointPlayerPos.x < monsterPoint.x - m_iAttackRange)
	{
		m_iXSpeed = -m_iXMaxSpeed;
		m_bIsRight = false;
	}
	else if (m_pointPlayerPos.x > monsterPoint.x + m_iAttackRange)
	{
		m_iXSpeed = m_iXMaxSpeed;
		m_bIsRight = true;
	}

	m_pSprite->setFlipX(m_bIsRight);
	this->run();

}

void Monster::attackLogic()
{
	if (m_fAttackTime > m_iAttackCDTime)
	{
		m_fAttackTime = 0;

		Point monsterPoint = this->getPosition();

		m_iXSpeed = 0;
		m_iYSpeed = 0;

		if (m_pointPlayerPos.x < monsterPoint.x)
		{
			m_bIsRight = false;

		}
		else if (m_pointPlayerPos.x > monsterPoint.x)
		{
			m_bIsRight = true;
		}

		m_pSprite->setFlipX(m_bIsRight);

		this->attack();
	}

}

void Monster::attackedLogic()
{
	m_iXSpeed = 0;
	m_iYSpeed = 0;

	m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);

	if (m_iHP == 0)
	{
		m_pHPBar->startFadeOut();
		this->monsterDeath();
		this->unscheduleUpdate();
	}
	else
	{
		this->hurt();
	}
}

void Monster::attackEndLogic()
{
	Point monsterPoint = this->getPosition();

	if (abs(m_pointPlayerPos.y - monsterPoint.y) < 8)
	{
		if ((!m_bIsRight
			&& m_pointPlayerPos.x < monsterPoint.x
			&& m_pointPlayerPos.x > monsterPoint.x - m_iAttackRange)
			|| 
			(m_bIsRight
			&& m_pointPlayerPos.x > monsterPoint.x
			&& m_pointPlayerPos.x < monsterPoint.x + m_iAttackRange)
			)
		{
			NotificationCenter::getInstance()->postNotification("monster_attack", NULL);
		}
	}
	m_enMonsterState = en_ms_warn;
	return;
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
	m_iAttackCDTime = monsterData.i_attackCDTime;
	m_iMaxHP = m_iHP;

	Size size = m_pSprite->getContentSize() * getScale();

	m_pHPBar = HpBar::create();
	m_pHPBar->setHpBarPosition(Point(20, size.height));
	m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);
	this->addChild(m_pHPBar);
	
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
	m_fStateTime += dt;
	m_fAttackTime += dt;

	switch (m_enMonsterState)
	{
	case en_ms_patrol:
		this->patrolLogic();
		break;
	case en_ms_warn:
		this->warnLogic();
		break;
	case en_ms_attack:
		this->attackLogic();
		break;
	case en_ms_attacked:
		this->attackedLogic();
		break;
	case en_ms_attack_end:
		this->attackEndLogic();
		break;
	default:
		break;
	}

	Point pos = this->getPosition();
	pos.x += m_iXSpeed;
	pos.y += m_iYSpeed;

	if (pos.y > m_pointOriginalPos.y + m_iWarningRange)
	{
		pos.y = m_pointOriginalPos.y + m_iWarningRange;
		m_iYSpeed = 0;
	}
	if (pos.y < m_pointOriginalPos.y - m_iWarningRange)
	{
		pos.y = m_pointOriginalPos.y - m_iWarningRange;
		m_iYSpeed = 0;
	}

	if (pos.x < m_pointOriginalPos.x - m_iWarningRange)
	{
		pos.x = m_pointOriginalPos.x - m_iWarningRange;
		m_iXSpeed = 0;
	}
	if (pos.x > m_pointOriginalPos.x + m_iWarningRange)
	{
		pos.x = m_pointOriginalPos.x + m_iWarningRange;
		m_iXSpeed = 0;
	}

	if (m_enMonsterState == en_ms_patrol && m_iXSpeed == 0 && m_iYSpeed == 0)
	{
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
	if (m_enMonsterState == en_as_attacked || m_bIsDeath)
	{
		return;
	}

	FlyingObjectCheckInformation* objectPoint = (FlyingObjectCheckInformation*)pSender;
	float objectX = objectPoint->point_checkPoint.x;
	float objectY = objectPoint->point_checkPoint.y;

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
		m_enMonsterState = en_ms_attacked;
		m_iHP -= objectPoint->i_attack;
		if (m_iHP < 0)
		{
			m_iHP = 0;
		}
	}
}

void Monster::checkDistanceWithPlayer(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;
	m_pointPlayerPos = Point(playerPoint->x, playerPoint->y);

	if (m_enMonsterState == en_ms_attack
		|| m_enMonsterState == en_ms_attacked)
	{
		return;
	}

	Point monsterPoint = this->getPosition();

	if (abs(m_pointPlayerPos.y - monsterPoint.y) < 8
		&& m_pointPlayerPos.x > monsterPoint.x - m_iAttackRange
		&& m_pointPlayerPos.x < monsterPoint.x + m_iAttackRange)
	{
		m_enMonsterState = en_ms_attack;
		return;
	}

	if (m_pointPlayerPos.x < m_pointOriginalPos.x - m_iWarningRange
		|| m_pointPlayerPos.x > m_pointOriginalPos.x + m_iWarningRange
		|| m_pointPlayerPos.y < m_pointOriginalPos.y - m_iWarningRange
		|| m_pointPlayerPos.y > m_pointOriginalPos.y + m_iWarningRange)
	{
		m_enMonsterState =  en_ms_patrol;
		return;
	}

	m_enMonsterState = en_ms_warn;
}
