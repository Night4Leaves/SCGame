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

void Player::run()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_run");
	Animate* animate = Animate::create(animation);
	m_sprite->runAction(animate);
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

void Player::jump()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_jump");
	Animate* animate = Animate::create(animation);
	Vec2 jumpHeight = Vec2(0.0f, 0.0f);
	Action* jump = JumpBy::create(1.4f, jumpHeight, 50, 1);
	Spawn* spawn = Spawn::create(animate, jump, nullptr);
	m_sprite->runAction(spawn);
}

void Player::turnAround(bool isRight)
{
	m_sprite->setFlipX(!isRight);
}
