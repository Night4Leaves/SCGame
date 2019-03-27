#include "Boss.h"

void Boss::checkBeHit(Ref * pSender)
{
	if (m_enMonsterState == en_as_attacked)
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
	float monsterYCheckDown = monsterPoint.y + monsterSize.height * 0.25;
	float monsterYCheckUp = monsterPoint.y + monsterSize.height * 0.55;

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

void Boss::checkDistanceWithPlayer(Ref * pSender)
{
	Point* playerPos = (Point*)pSender;
	Point bossPos = this->getPosition();
	m_pointPlayerPos = Point(playerPos->x, playerPos->y);
	
	if (bossPos.x - m_pointPlayerPos.x < 655 && !m_bIsactivated)
	{
		this->scheduleUpdate();
		m_bIsactivated = true;

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(Boss::checkBeHit),
			"attack_flying_object_check_point",
			NULL);
	}
}

void Boss::startPause(Ref * pSender)
{
	if (m_bIsactivated)
	{
		log("Boss pause");
		this->unscheduleUpdate();
		m_pSprite->pause();
	}
}

void Boss::endPause(Ref * pSender)
{
	if (m_bIsactivated)
	{
		log("Boss end pause");
		this->scheduleUpdate();
		m_pSprite->resume();
	}
}

Boss::Boss()
	: m_iXSpeed(0)
	, m_iYSpeed(0)
	, m_iFirstSkillDamage(0)
	, m_iFirstSkillCDTime(0)
	, m_fFirstSkillTime(0)
	, m_iSecondSkillDamage(0)
	, m_iSecondSkillCDTime(0)
	, m_fSecondSkillTime(0)
	, m_iThirdSkillDamage(0)
	, m_iThirdSkillCDTime(0)
	, m_fThirdSkillTime(0)
	, m_bIsLock(false)
	, m_bIsactivated(false)
	, m_fStateTime(0.0)
{
}

Boss::~Boss()
{
}

bool Boss::init(const BossData & bossData)
{
	CombatEntity::saveCombatEntityData(bossData);

	m_iFirstSkillDamage = bossData.i_firstSkillDamage;
	m_iFirstSkillCDTime = bossData.i_firstSkillCDTime;
	m_iSecondSkillDamage = bossData.i_secondSkillDamage;
	m_iSecondSkillCDTime = bossData.i_secondSkillCDTime;
	m_iThirdSkillDamage = bossData.i_thirdSkillDamage;
	m_iThirdSkillCDTime = bossData.i_thirdSkillCDTime;

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Boss::checkDistanceWithPlayer),
		"player_point",
		NULL);

	return true;
}

void Boss::update(float dt)
{
	m_fStateTime += dt;
	m_fFirstSkillTime += dt;
	m_fSecondSkillTime += dt;
	m_fThirdSkillTime += dt;

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
	case en_ms_attack_end:
		this->attackEndLogic();
		break;
	case en_ms_attacked:
		this->attackedLogic();
		break;
	default:
		break;
	}

	Point pos = getPosition();
	pos.x += m_iXSpeed;
	pos.y += m_iYSpeed;
	setBossPosition(pos);
}

void Boss::setBossPosition(Point pos)
{
	Size mapSize = GameManager::getInstance()->getMapSize();
	Size spriteSize = m_pSprite->getContentSize();
	Size visible = Director::getInstance()->getVisibleSize();

	pos.x = std::max(pos.x, mapSize.width - visible.width + spriteSize.width / 2);
	pos.x = std::min(pos.x, mapSize.width - spriteSize.width / 2);
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
	setPosition(pos);
}

void Boss::patrolLogic()
{
	Point monsterPos = getPosition();
	if (abs(monsterPos.y - m_pointPlayerPos.y) > 10)
	{
		if (monsterPos.y > m_pointPlayerPos.y)
		{
			m_iYSpeed = -m_iYMaxSpeed;
		}
		else
		{
			m_iYSpeed = m_iYMaxSpeed;
		}
	}
	else
	{
		m_iYSpeed = 0;
		m_enMonsterState = en_ms_warn;
	}
	
	if (abs(monsterPos.x - m_pointPlayerPos.x) > 50)
	{
		if (monsterPos.x > m_pointPlayerPos.x)
		{
			m_iXSpeed = -m_iXMaxSpeed;
			m_bIsRight = false;
		}
		else
		{
			m_iXSpeed = m_iXMaxSpeed;
			m_bIsRight = true;
		}
		m_pSprite->setFlipX(m_bIsRight);
	}
	else
	{
		m_iXSpeed = 0;
	}

	if (m_iYSpeed == 0 && m_iXSpeed == 0)
	{
		this->idle();
	}
	else
	{
		this->run();
	}
}

void Boss::warnLogic()
{
	if (m_fStateTime > 5)
	{
		m_fStateTime = 0;
		m_enMonsterState = en_ms_attack;
	}
	else
	{
		m_enMonsterState = en_ms_patrol;
	}
}

void Boss::attackLogic()
{
	if (m_bIsLock)
	{
		return;
	}
	m_bIsLock = true;

	Point monsterPos = getPosition();
	if (abs(monsterPos.x - m_pointPlayerPos.x) > m_iAttackRange && m_fSecondSkillTime > m_iSecondSkillCDTime)
	{
		m_iXSpeed = 0;
		m_fSecondSkillTime = 0;
		this->secondSkill();
		return;
	}
	if (abs(monsterPos.x - m_pointPlayerPos.x) < m_iAttackRange && m_fFirstSkillTime > m_iFirstSkillCDTime)
	{
		m_iXSpeed = 0;
		m_fFirstSkillTime = 0;
		this->firstSkill();
		return;
	}
	if (m_fThirdSkillTime > m_iThirdSkillCDTime)
	{
		m_iXSpeed = 0;
		m_fThirdSkillTime = 0;
		this->thirdSkill();
		return;
	}
}

void Boss::attackedLogic()
{
	m_iXSpeed = 0;
	m_iYSpeed = 0;

	m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);

	if (m_iHP == 0)
	{
		m_pHPBar->startFadeOut();
		//此处为死亡时的处理函数
		this->unscheduleUpdate();
	}
	else
	{
		this->hurt();
	}
	m_enMonsterState = en_ms_patrol;
}

void Boss::attackEndLogic()
{
	Point monsterPoint = this->getPosition();

	switch (m_enSkillType)
	{
	case en_st_closeCombet:
		if (abs(m_pointPlayerPos.y - monsterPoint.y) < 10)
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
		break;
	case en_st_beam:
		break;
	case en_st_missile:
		break;
	case en_st_summon:
		break;
	case en_st_debuff:
		break;
	case en_st_recovery:
		m_iHP += m_iThirdSkillDamage;
		if (m_iHP > m_iMaxHP)
		{
			m_iHP = m_iMaxHP;
		}
		m_pHPBar->setResidueHp(m_iHP / (float)m_iMaxHP * 100);
		break;
	default:
		break;
	}

	m_enMonsterState = en_ms_patrol;
	m_bIsLock = false;
}
