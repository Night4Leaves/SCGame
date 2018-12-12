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
	Animation* animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_run", 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_run");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_attack", 0.1f, 1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_attack");
	animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_idle", 0.1f, -1);
	AnimationCache::getInstance()->addAnimation(animation, "player_01_idle");

	return true;
}

void Player::run()
{
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_run");
	Animate* animate = Animate::create(animation);
	animate->setTag(1);
	m_sprite->runAction(animate);

}

void Player::attack()
{
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_attack");
	Animate* animate = Animate::create(animation);
	m_sprite->runAction(animate);
	this->idle();
}

void Player::idle()
{
	Animation* animation = AnimationCache::getInstance()->getAnimation("player_01_idle");
	Animate* animate = Animate::create(animation);
	m_sprite->runAction(animate);
}
