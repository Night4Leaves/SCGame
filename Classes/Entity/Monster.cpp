#include "Monster.h"
#include "Util/AnimationUtil.h"
#include "GameManager.h"

Monster::Monster()
	: m_iXSpeed(0)
	, m_iYSpeed(0)
	, m_iWarningRange(0)
	, m_iAttackCDTime(0)
	, m_bIsDeath(false)
	, m_bIsFlying(false)
	, m_bIsAttackMove(false)
	, m_fStateTime(0.0)
	, m_fAttackTime(0.0)
{
	srand((unsigned)time(nullptr));	//更新随机数种子
}

Monster::~Monster()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

void Monster::patrolLogic()
{
	//5秒左右更新一次状态
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

void Monster::warnLogic()
{
	Point monsterPoint = this->getPosition();

	//如果玩家与怪物在Y轴上的距离相差大于等于8,怪物会向玩家移动
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
	
	//如果玩家不在怪物的攻击距离内,怪物会向玩家移动
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
	//攻击间隔大于冷却时间才会进行攻击动作
	if (m_fAttackTime > m_iAttackCDTime)
	{
		m_fAttackTime = 0;	//攻击间隔清0

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
	m_bIsFlying = monsterData.b_isFlying;
	m_bIsAttackMove = monsterData.b_isAttackMove;
	m_iMaxHP = m_iHP;

	Size size = m_pSprite->getContentSize();

	m_pHPBar = HpBar::create();
	m_pHPBar->setHpBarPosition(Point(20, size.height));
	m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);
	this->addChild(m_pHPBar);
	
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Monster::checkBeHit),
		"attack_flying_object_check_point",
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

	this->setMonsterPositon(pos);

}

void Monster::setMonsterOriginPosition(Point pos)
{
	if (!m_bIsFlying)
	{
		m_pointOriginalPos = pos;
	}
	else
	{
		pos.y -= 50;
	}
	setPosition(pos);
}

void Monster::startPause(Ref * pSender)
{
}

void Monster::endPause(Ref * pSender)
{
}

//根据飞行物发来的数据，判定自己是否会被击中
void Monster::checkBeHit(Ref * pSender)
{
	if (m_enMonsterState == en_as_attacked || m_bIsDeath)
	{
		return;
	}

	//飞行物坐标
	FlyingObjectCheckInformation* objectPoint = (FlyingObjectCheckInformation*)pSender;
	float objectX = objectPoint->point_checkPoint.x;
	float objectY = objectPoint->point_checkPoint.y;

	//怪物坐标与尺寸
	Point monsterPoint = this->getPosition();
	Size monsterSize = m_pSprite->getContentSize() * this->getScale();

	//Y轴碰撞检测范围
	float monsterYCheckDown = monsterPoint.y + monsterSize.height * 0.5;
	float monsterYCheckUp = monsterPoint.y + monsterSize.height * 0.7;

	if (objectY < monsterYCheckDown || objectY > monsterYCheckUp)
	{
		return;
	}

	//X轴碰撞检测范围
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

//根据玩家角色发送的数据，切换自己的行动状态
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

void Monster::setMonsterPositon(Point pos)
{
	//防止跑到下边界外
	pos.y = std::max(0.0f, pos.y);

	//获取坐标所在砖块在块地图中的坐标
	Point tiledPos = GameManager::getInstance()->tileCoordForPosition(pos);

	bool notGo = GameManager::getInstance()->checkBoolAttribute(tiledPos, "Collidable");

	if (notGo)
	{
		pos.y -= m_iYSpeed;
		m_iYSpeed = 0;
	}

	this->setPosition(pos);
}
