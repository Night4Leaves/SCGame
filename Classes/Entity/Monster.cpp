#include "Monster.h"
#include "Util/AnimationUtil.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

Monster * Monster::create(const char * str_monsterName)
{
	Monster *pRet = new(std::nothrow) Monster();
	if (pRet && pRet->init(str_monsterName))
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

bool Monster::init(const char* str_monsterName)
{
	m_strMonsterName = str_monsterName;
	std::string animationName = "";	//动画全称
	Animation* animation = NULL;	//动画对象
	auto num = m_strActionName.size();	//动作数量

	//生成静态待机图对应的精灵
	std::string waitAnimationName = StringUtils::format("%s_wait.png", str_monsterName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	sprite->setScale(0.35);
	this->bindSprite(sprite);

	//生成角色动画并存储到动画缓存中
	for (int i = 0; i < num; i++)
	{
		animationName = StringUtils::format("%s_%s", str_monsterName, m_strActionName.at(i));
		log("%s, %f, %d", animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		animation = AnimationUtil::createAnimationWithSingleFrameName(animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		AnimationCache::getInstance()->addAnimation(animation, animationName.c_str());
	}

	return true;
}

void Monster::setController(SCController * controller)
{
	m_pMonsterController = controller;
	controller->setControllerListner(this);
}

Vec2 Monster::getTargetPosition()
{
	return this->getPosition();
}

void Monster::setTargetPosition(Vec2 pos)
{
	this->setPosition(pos);
}

void Monster::checkControllerStatus()
{
	m_pMonsterController->checkControllerStatus();
}

void Monster::turnAround(bool b_isRight)
{
	m_sprite->setFlipX(b_isRight);
}

void Monster::idle()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_strMonsterName).c_str());
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
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_strMonsterName).c_str());
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
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_strMonsterName).c_str());
	//生成动画动作
	Animate* attackAnimate = Animate::create(attackAnimation);
	//回调检查控制器状态函数
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Monster::checkControllerStatus, this));
	Sequence* actionSequnence = Sequence::create(attackAnimate, callfunc, nullptr);
	m_sprite->runAction(actionSequnence);
}

void Monster::jump()
{
	return;
}

void Monster::climb()
{
	return;
}

void Monster::hurt()
{
	return;
}

void Monster::death()
{
	return;
}
