#include "Player.h"
#include "Util/AnimationUtil.h"

Player::Player()
{
}

Player::~Player()
{
}

Player * Player::create(const char* str_playerName)
{
	Player *pRet = new(std::nothrow) Player();
	if (pRet && pRet->init(str_playerName))
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

bool Player::init(const char* str_playerName)
{
	m_strPlayerName = str_playerName;	//��ɫ����
	std::string animationName = "";	//����ȫ��
	Animation* animation = NULL;	//��������
	auto num = m_strActionName.size();	//��������

	//���ɾ�̬����ͼ��Ӧ�ľ���
	std::string waitAnimationName = StringUtils::format("%s_wait.png", str_playerName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	//���ɽ�ɫ�������洢������������
	for (int i = 0; i < num; i++)
	{
		animationName = StringUtils::format("%s_%s", m_strPlayerName, m_strActionName.at(i));
		log("%s, %f, %d", animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		animation = AnimationUtil::createAnimationWithSingleFrameName(animationName.c_str(), m_fActionTime[i], m_iActionPlayTime[i]);
		AnimationCache::getInstance()->addAnimation(animation, animationName.c_str());
	}

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

	this->setViewPointByPlayer();
}

void Player::checkControllerStatus()
{
	m_pPlayerController->checkControllerStatus();
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == nullptr)
	{
		return;
	}

	//��ȡ��Ļ��ʾ�ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ����λ��
	Point spritePosition = getPosition();
	//��ȡ�����С�ߴ�
	Size contentSize = m_sprite->getContentSize();
	//����߽�Ƚϣ���ֹ�ܵ���߽���
	float x = std::min(spritePosition.x, visibleSize.width - (contentSize.width / 2 - 10));
	//���ұ߽�Ƚϣ���ֹ�ܵ��ұ߽���
	x = std::max(x, contentSize.width / 2 - 10);

	Point destPos = Point(x, 100);

	this->setPosition(destPos);

	/*log("x: %f, y: %f", spritePosition.x, spritePosition.y);*/

	//float x = std::max(spritePosition.x + (contentSize.width / 2), visibleSize.width / 2);
	//float y = std::max(spritePosition.y + (contentSize.height / 2), visibleSize.height / 2);

	//Point destPosition = Point(x, y);

	//Point centerPosition = Point(visibleSize.width / 2, visibleSize.height / 2);

}

void Player::turnAround(bool isRight)
{
	m_sprite->setFlipX(!isRight);
}


void Player::idle()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_strPlayerName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//ִ�ж�������
	m_sprite->runAction(animate);
}

void Player::run()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_strPlayerName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//ִ�ж�������
	m_sprite->runAction(animate);
}

void Player::attack()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_strPlayerName).c_str());
	//���ɶ�������
	Animate* attackAnimate = Animate::create(attackAnimation);
	//Animate* idleAnimate = Animate::create(idleAnimation);
	//�ص���������״̬����
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	Sequence* actionSequnence = Sequence::create(attackAnimate, callfunc, nullptr);
	m_sprite->runAction(actionSequnence);
}

void Player::jump()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_jump", m_strPlayerName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//������Ծ������Ҫ������(������ֵ��֤ԭ����Ծ�Ŀ���)
	Vec2 jumpHeight = Vec2(0.0f, 0.0f);
	//������Ծλ�ƶ���
	Action* jump = JumpBy::create(1.4f, jumpHeight, 50, 1);
	//����Ծ��������Ծλ�ƶ������
	Spawn* spawn = Spawn::create(animate, jump, nullptr);
	//�ص���������״̬����
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	//˳��������ִ����Ծ��Ϊ����ִ�лص�
	Sequence* sequence = Sequence::create(spawn, callfunc, nullptr);
	//ִ�ж���
	m_sprite->runAction(sequence);
}

void Player::climb()
{
	//ֹͣ��ǰ�Ķ���
	m_sprite->stopAllActions();
	//��ȡ�Ѿ����õĶ���
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_climb", m_strPlayerName).c_str());
	//���ɶ�������
	Animate* animate = Animate::create(animation);
	//ִ�ж�������
	m_sprite->runAction(animate);
}

void Player::hurt()
{
	m_sprite->stopAllActions();
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_hurt", m_strPlayerName).c_str());
	Animate* animate = Animate::create(animation);
	Blink* blink = Blink::create(0.8f, 5);
	Spawn* spawn = Spawn::create(animate, blink, nullptr);
	m_sprite->runAction(spawn);
}

void Player::death()
{
}
