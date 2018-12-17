#include "Player.h"
#include "Util/AnimationUtil.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init()
{
	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_run", 0.04f, -1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_run");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_attack", 0.1f, 1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_attack");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_idle", 0.25f, -1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_idle");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_climb", 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_climb");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_death", 0.25f, 1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_death");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_hurt", 0.1f, 1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_hurt");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_jump", 0.2f, 1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_jump");

	return true;
}

void Player::setController(SCController * controller)
{
	m_pPlayerController = controller;
	controller->setControllerListner(this);
}

Vec2 Player::getTargetPosition()
{
	return this->getPosition();
}

void Player::setTargetPosition(Vec2 pos)
{
	this->setPosition(pos);
}

void Player::setAction(Action * action)
{
	m_sprite->runAction(action);
}

void Player::checkControllerStatus()
{
	m_pPlayerController->checkControllerStatus();
}

void Player::run()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_run");
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_sprite->runAction(animate);
}

void Player::jump()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_jump");
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//设置跳跃动作需要的坐标(此坐标值保证原地跳跃的可能)
	Vec2 jumpHeight = Vec2(0.0f, 0.0f);
	//生成跳跃位移动作
	Action* jump = JumpBy::create(1.4f, jumpHeight, 50, 1);
	//将跳跃动画和跳跃位移动作结合
	Spawn* spawn = Spawn::create(animate, jump, nullptr);
	//回调检查控制器状态函数
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	//顺序动作，先执行跳跃行为，再执行回调
	Sequence* sequence = Sequence::create(spawn, callfunc, nullptr);
	//执行动作
	m_sprite->runAction(sequence);
}

void Player::attack()
{
	m_sprite->stopAllActions();
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation("player_01_attack");
	Animation* idleAnimation = AnimationCache::getInstance()->getAnimation("player_01_idle");
	Animate* attackAnimate = Animate::create(attackAnimation);
	Animate* idleAnimate = Animate::create(idleAnimation);
	Sequence* actionSequnence = Sequence::create(attackAnimate, idleAnimate, nullptr);
	m_sprite->runAction(actionSequnence);
}

void Player::idle()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_idle");
	Animate* animate = Animate::create(animation);
	m_sprite->runAction(animate);
}

void Player::hurt()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_hurt");
	Animate* animate = Animate::create(animation);
	Blink* blink = Blink::create(0.8f, 5);
	Spawn* spawn = Spawn::create(animate, blink, nullptr);
	m_sprite->runAction(spawn);
}

void Player::death()
{
}

void Player::climb()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_climb");
	Animate* animate = Animate::create(animation);
	m_sprite->runAction(animate);
}

void Player::turnAround(bool isRight)
{
	m_sprite->setFlipX(!isRight);
}
