#include "Player.h"

Player::Player()
{
}


Player::~Player()
{
}

bool Player::init()
{
	do{
		CC_BREAK_IF(!Node::init());

		//加载精灵动画资源
		SpriteFrameCache* p_cSpriteCache = SpriteFrameCache::getInstance();
		p_cSpriteCache->addSpriteFramesWithFile("player01.plist");
		CC_BREAK_IF(p_cSpriteCache == nullptr);

/*		int length = action.size();
		for (int i = 0; i < length; i++)
		{
			log("%s", action.at(i));
		 }*/

		char str[20];
		Vector< SpriteFrame*>p_animeFrames;
		for (int i = 1; i < 6; i++)
		{
			sprintf(str, "idle%02d.png", i);
			SpriteFrame* frame = p_cSpriteCache->spriteFrameByName(str);
			if (frame == nullptr)
			{
				log("no pictrue");
				continue;
			}
			else
			{
				log("pictrue %02d", i);
			}
			p_animeFrames.pushBack(frame);
		}

		Animation* p_cAnimation = Animation::createWithSpriteFrames(p_animeFrames, 0.25f);
		if (p_cAnimation == nullptr)
		{
			log("idle01.png");
		}

		AnimationCache* p_cAnimationCache = AnimationCache::getInstance();
		p_cAnimationCache->addAnimation(p_cAnimation, "idle");

		Animate* p_cAnimate = Animate::create(p_cAnimation);
		if (p_cAnimate == nullptr)
		{
			log("create Animate is fail");
		}

		SpriteFrame* p_cSpriteFrame = p_cSpriteCache->getSpriteFrameByName("idle01.png");
		p_cSprite = Sprite::createWithSpriteFrame(p_cSpriteFrame);
		if (p_cSprite == nullptr)
		{
			log("idle01.png");
		}
		else
		{
			p_cSprite->runAction(RepeatForever::create(p_cAnimate));
		}
	} while (0);
	return false;
}

void Player::move()
{
}

void Player::jump()
{
}

void Player::climb()
{
}

void Player::attack()
{
}

void Player::death()
{
}
