#include "Monster.h"
#include "Util/AnimationUtil.h"

Monster::Monster()
	: m_iXSpeed(0)
	, m_iYspeed(0)
	, m_bIsRight(false)
	, m_bIsLock(false)
	, m_bIsAttack(false)
	, m_bIsAttacked(false)
	, m_bIsDeath(false)
	, m_fStateTime(0.0)
{
	srand((unsigned)time(nullptr));
}

Monster::~Monster()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

Monster * Monster::create(MonsterData monsterData)
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

bool Monster::init(MonsterData monsterData)
{
	m_sctMonsterData = monsterData;
	std::string animationName = "";	//动画全称
	Animation* animation = NULL;	//动画对象
	auto num = m_strActionName.size();	//动作数量

	//生成静态待机图对应的精灵
	std::string waitAnimationName = StringUtils::format("%s_idle_01.png", m_sctMonsterData.str_monsterName.c_str());
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	//生成角色动画并存储到动画缓存中
	for (int i = 0; i < num; i++)
	{
		animationName = StringUtils::format("%s_%s", m_sctMonsterData.str_monsterName.c_str(), m_strActionName.at(i));
		log("%s, %f, %d", animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		animation = AnimationUtil::createAnimationWithSingleFrameName(animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		AnimationCache::getInstance()->addAnimation(animation, animationName.c_str());
	}

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(Monster::checkAttckFlyingObjectPath),
		"attack_flying_object_point",
		NULL);

	this->scheduleUpdate();

	return true;
}

void Monster::update(float dt)
{
	m_fStateTime += dt;
	
	if (m_fStateTime > 5)
	{
		m_fStateTime = 0;

		int r = rand() % 2;
		log("rand : %d", r);

		if (r == 1)
		{
			m_iXSpeed = m_sctMonsterData.i_xSpeed;
			m_bIsRight = true;
		}
		else
		{
			m_iXSpeed = -m_sctMonsterData.i_xSpeed;
			m_bIsRight = false;
		}

		m_sprite->setFlipX(m_bIsRight);
		this->run();
	}

	Point pos = this->getPosition();
	pos.x += m_iXSpeed;

	if (pos.x < m_pointOriginalPos.x - m_sctMonsterData.i_warningRange)
	{
		pos.x = m_pointOriginalPos.x - m_sctMonsterData.i_warningRange;
		m_iXSpeed = 0;
		this->idle();
	}
	if (pos.x > m_pointOriginalPos.x + m_sctMonsterData.i_warningRange)
	{
		pos.x = m_pointOriginalPos.x + m_sctMonsterData.i_warningRange;
		m_iXSpeed = 0;
		this->idle();
	}

	this->setPosition(pos);

	/*if (m_bIsAttacked)
	{
		m_iXSpeed = 0;
		m_iYspeed = 0;

		this->hurt();
	}	*/
}

void Monster::setMonsterPosition(Point pos)
{
	m_pointOriginalPos = pos;
	setPosition(pos);
}

void Monster::idle()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_sctMonsterData.str_monsterName.c_str()).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_sprite->runAction(animate);
}

void Monster::run()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_sctMonsterData.str_monsterName.c_str()).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_sprite->runAction(animate);
}

void Monster::attack()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_sctMonsterData.str_monsterName.c_str()).c_str());
	//生成动画动作
	Animate* attackAnimate = Animate::create(attackAnimation);

	auto callfunc = CallFunc::create(CC_CALLBACK_0(Monster::idle, this));
	Sequence* actionSequnence = Sequence::create(attackAnimate, callfunc, nullptr);
	m_sprite->runAction(actionSequnence);
}

void Monster::hurt()
{
	//停止当前的动作
	m_sprite->stopAllActions();

	//计算血量
	--m_sctMonsterData.i_HP;
	if (m_sctMonsterData.i_HP == 0)
	{
		this->death();
		return;
	}

	//获取已经做好的动画
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_sctMonsterData.str_monsterName.c_str()).c_str());
	//生成动画动作
	Animate* hurtAnimate = Animate::create(hurtAnimation);
	
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Monster::idle, this));
	Sequence* actionSequnence = Sequence::create(hurtAnimate, callfunc, NULL);
	m_sprite->runAction(actionSequnence);
	return;
}

void Monster::death()
{
	//获取已经做好的动画
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_sctMonsterData.str_monsterName.c_str()).c_str());
	//生成动画动作
	Animate* hurtAnimate = Animate::create(hurtAnimation);

	Blink* blinkAction = Blink::create(1.5f, 3);
	
	auto sendScoreMsg = CallFunc::create([&]() { NotificationCenter::getInstance()->postNotification("update_score", (Ref*)m_sctMonsterData.i_money); });
	
	Spawn* actionList = Spawn::create(hurtAnimate, blinkAction, nullptr);
	Sequence* actionSequnence = Sequence::create(sendScoreMsg, actionList, nullptr);

	m_sprite->runAction(actionSequnence);

	return;
}

void Monster::checkAttckFlyingObjectPath(Ref * pSender)
{
	if (m_bIsDeath)
	{
		return;
	}

	FlyingObjectPositionInformation* flyingObjectInfo = (FlyingObjectPositionInformation*)pSender;
	Point vec2_monsterPoint = m_sprite->getPosition();

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

	Size size_monsterSize = this->getCollisionSize();

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

	return;
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

	Point monsterPoint = m_sprite->getPosition();
	Size monsterSize = m_sprite->getContentSize() * m_sprite->getScale();

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
