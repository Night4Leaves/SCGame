#include "Player.h"
#include "Util/AnimationUtil.h"

Player::Player()
{
}

Player::~Player()
{
}

Player * Player::create(const PlayerData & playerData)
{
	Player *pRet = new(std::nothrow) Player();
	if (pRet && pRet->init(playerData))
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

bool Player::init(const PlayerData & playerData)
{
	CombatEntity::saveCombatEntityData(playerData);

	return true;
}

void Player::setController(SCController * controller)
{
	m_pPlayerController = controller;
	controller->setControllerListner(this);
}

Size Player::getCollisionSize()
{
	if (m_pSprite == nullptr)
	{
		return Size(-1, -1);
	}

	return m_pSprite->getContentSize();
}

Vec2 Player::getTargetPosition()
{
	return this->getPosition();
}

int Player::getXMaxSpeed()
{
	return m_iXMaxSpeed;
}

int Player::getYMaxSpeed()
{
	return m_iYMaxSpeed;
}

void Player::setTargetPosition(Vec2 pos)
{
	this->setPosition(pos);
}

void Player::turnAround(bool isRight)
{
	m_pSprite->setFlipX(!isRight);
}

void Player::checkControllerStatus()
{
	m_pPlayerController->checkControllerStatus();
}

void Player::idle()
{
	CombatEntity::idle();
}

void Player::run()
{
	CombatEntity::run();
}

void Player::attack()
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
	//发出产生火球的消息
	auto sendAttackMsg = CallFunc::create([]() {NotificationCenter::getInstance()->postNotification("set_attack_flying_object", NULL); });
	//回调检查控制器状态函数
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	Sequence* actionSequnence = Sequence::create(attackAnimate, sendAttackMsg, callfunc, nullptr);
	m_pSprite->runAction(actionSequnence);
}

void Player::jump()
{
	//停止当前的动作
	m_pSprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_jump", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//设置跳跃动作需要的坐标(此坐标值保证原地跳跃的可能)
	Vec2 jumpHeight = Vec2(0.0f, 0.0f);
	//生成跳跃位移动作
	Action* jump = JumpBy::create(1.75f, jumpHeight, 75, 1);
	//将跳跃动画和跳跃位移动作结合
	Spawn* spawn = Spawn::create(animate, jump, nullptr);
	//回调检查控制器状态函数
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	//顺序动作，先执行跳跃行为，再执行回调
	Sequence* sequence = Sequence::create(spawn, callfunc, nullptr);
	//执行动作
	m_pSprite->runAction(sequence);
}

void Player::hurt()
{
	if (m_enActionState == en_as_attacked)
	{
		return;
	}
	m_enActionState = en_as_attacked;

	m_pSprite->stopAllActions();

	--m_iHP;
	if (m_iHP <= 0)
	{
		m_iHP = 0;
		this->playerDeath();
		return;
	}

	//获取已经做好的动画
	Animation* hurtAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_strCharacterName.c_str()).c_str());
	//生成动画动作
	Animate* hurtAnimate = Animate::create(hurtAnimation);

	auto checkControllerStatus = CallFunc::create([&]() {m_pPlayerController->checkControllerStatus(); });
	
	Sequence* actionSequnence = Sequence::create(hurtAnimate, checkControllerStatus, NULL);
	m_pSprite->runAction(actionSequnence);
}

void Player::startPause(Ref * pSender)
{
	log("Player pause");
	m_pSprite->pause();
}

void Player::endPause(Ref * pSender)
{
	log("Player end pause");
	m_pSprite->resume();
}
