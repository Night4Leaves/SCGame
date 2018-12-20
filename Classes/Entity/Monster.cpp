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
	std::string animationName = "";	//����ȫ��
	Animation* animation = NULL;	//��������
	auto num = m_strActionName.size();	//��������

	//���ɾ�̬����ͼ��Ӧ�ľ���
	std::string waitAnimationName = StringUtils::format("%s_wait.png", str_monsterName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	sprite->setScale(0.35);
	this->bindSprite(sprite);

	//���ɽ�ɫ�������洢������������
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
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_strMonsterName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//ִ�ж�������
	m_sprite->runAction(animate);
}

void Monster::run()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_strMonsterName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//ִ�ж�������
	m_sprite->runAction(animate);
}

void Monster::attack()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_strMonsterName).c_str());
	//���ɶ�������
	Animate* attackAnimate = Animate::create(attackAnimation);
	//�ص���������״̬����
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
