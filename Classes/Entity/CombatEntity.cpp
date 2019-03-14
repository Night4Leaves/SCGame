#include "CombatEntity.h"
#include "Util/AnimationUtil.h"

CombatEntity::CombatEntity()
	: m_strCharacterName("")
	, m_iHP(0)
	, m_iAttack(0)
	, m_iMoney(0)
	, m_iXMaxSpeed(0)
	, m_iYMaxSpeed(0)
	, m_bIsMonster(true)
	//, m_bIsWait(true)
	//, m_bIsMove(false)
	//, m_bIsAttack(false)
	//, m_bIsAttacked(false)
	, m_bIsRight(false)
	, m_enMonsterState(en_ms_patrol)
	, m_enActionState(en_as_null)
{
}

CombatEntity::~CombatEntity()
{
}

bool CombatEntity::init(const std::vector<std::string> & actionName, const std::vector<double> & actionTime, const std::vector<int> & actionPlayTime)
{
	const char* characterName = m_strCharacterName.c_str();
	std::string animationName = "";	//动画全称
	Animation* animation = NULL;	//动画对象
	auto num = actionName.size();	//动作数量

	//生成静态待机图对应的精灵
	std::string waitAnimationName = StringUtils::format("%s_wait.png", characterName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	m_pSprite = sprite;
	this->addChild(sprite);

	//生成角色动画并存储到动画缓存中
	for (int i = 0; i < num; i++)
	{
		animationName = StringUtils::format("%s_%s", characterName, actionName.at(i).c_str());
		log("%s, %f, %d", animationName.c_str(), actionTime[i], actionPlayTime[i]);
		animation = AnimationUtil::createAnimationWithSingleFrameName(animationName.c_str(), actionTime[i], actionPlayTime[i]);
		AnimationCache::getInstance()->addAnimation(animation, animationName.c_str());
	}

	return true;
}

void CombatEntity::saveCombatEntityData(const CombatEntityData & combatEntityData)
{
	m_strCharacterName = combatEntityData.str_characterName;
	m_iHP = combatEntityData.i_HP;
	m_iAttack = combatEntityData.i_attack;
	m_iMoney = combatEntityData.i_money;
	m_iXMaxSpeed = combatEntityData.i_xSpeed;
	m_iYMaxSpeed = combatEntityData.i_ySpeed;
	m_iAttackRange = combatEntityData.i_attackRange;
	m_bIsMonster = combatEntityData.b_isMonster;

	this->init(combatEntityData.vec_csActionName, combatEntityData.vec_dActionTime, combatEntityData.vec_iActionPlayTime);
}

void CombatEntity::idle()
{
	if (m_enActionState == en_as_idle)
	{
		return;
	}
	m_enActionState = en_as_idle;

	//停止当前的动作
	m_pSprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_pSprite->runAction(animate);
}

void CombatEntity::run()
{
	if (m_enActionState == en_as_move)
	{
		return;
	}
	m_enActionState = en_as_move;

	//停止当前的动作
	m_pSprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_pSprite->runAction(animate);
}

void CombatEntity::attack()
{
	if (m_enActionState == en_as_attack)
	{
		return;
	}
	m_enActionState = en_as_attack;

	//停止当前的动作
	m_pSprite->stopAllActions();
	//获取已经做好的动画
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* attackAnimate = Animate::create(attackAnimation);

	auto callfuncIdle = CallFunc::create(CC_CALLBACK_0(CombatEntity::idle, this));
	auto callfuncAttackEnd = CallFunc::create(CC_CALLBACK_0(CombatEntity::changeMonsterState, this, en_ms_attack_end));

	Sequence* actionSequnence = Sequence::create(attackAnimate, callfuncAttackEnd, callfuncIdle, nullptr);
	m_pSprite->runAction(actionSequnence);
}

void CombatEntity::hurt()
{
	if (m_enActionState == en_as_attacked)
	{
		return;
	}
	m_enActionState = en_as_attacked;

	m_pSprite->stopAllActions();

	--m_iHP;
	if (m_iHP == 0)
	{
		if (m_bIsMonster)
		{
			this->monsterDeath();
		}
		else
		{
			this->playerDeath();
		}
		return;
	}

	//获取已经做好的动画
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* hurtAnimate = Animate::create(hurtAnimation);

	auto callfunc = CallFunc::create(CC_CALLBACK_0(CombatEntity::idle, this));

	Sequence* actionSequnence = Sequence::create(hurtAnimate, callfunc, NULL);
	m_pSprite->runAction(actionSequnence);
}

void CombatEntity::monsterDeath()
{
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_strCharacterName.c_str()).c_str());
	Animate* hurtAnimate = Animate::create(hurtAnimation);
	Blink* blinkAction = Blink::create(1.5f, 3);

	auto sendScoreMsg = CallFunc::create([&]() { NotificationCenter::getInstance()->postNotification("update_score", (Ref*)m_iMoney); });

	Spawn* actionList = Spawn::create(hurtAnimate, blinkAction, nullptr);
	Sequence* actionSequnence = Sequence::create(sendScoreMsg, actionList, nullptr);

	m_pSprite->runAction(actionSequnence);
}

void CombatEntity::playerDeath()
{
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_death", m_strCharacterName.c_str()).c_str());
	Animate* hurtAnimate = Animate::create(hurtAnimation);
	Blink* blinkAction = Blink::create(1.5f, 3);

	auto sendScoreMsg = CallFunc::create([&]() { NotificationCenter::getInstance()->postNotification("game_over", NULL); });

	Spawn* actionList = Spawn::create(hurtAnimate, blinkAction, nullptr);
	Sequence* actionSequnence = Sequence::create(sendScoreMsg, actionList, nullptr);

	m_pSprite->runAction(actionSequnence);
}

void CombatEntity::changeMonsterState(MonsterState monsterState)
{
	m_enMonsterState = monsterState;
}