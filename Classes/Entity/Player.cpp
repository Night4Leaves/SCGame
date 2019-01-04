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
	m_strPlayerName = str_playerName;	//角色名称
	std::string animationName = "";	//动画全称
	Animation* animation = NULL;	//动画对象
	auto num = m_strActionName.size();	//动作数量

	//生成静态待机图对应的精灵
	std::string waitAnimationName = StringUtils::format("%s_wait.png", str_playerName);
	Sprite* sprite = Sprite::createWithSpriteFrameName(waitAnimationName.c_str());
	this->bindSprite(sprite);

	//生成角色动画并存储到动画缓存中
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

void Player::setMap(TMXTiledMap * p_map)
{
	m_pMap = p_map;
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

	Node* parent = (Node*)getParent();
	//获得地图中图块的数量和尺寸，并计算出地图尺寸
	Size mapTiledNum = m_pMap->getMapSize();
	Size tiledSize = m_pMap->getTileSize();
	Size mapSize = Size(mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);
	//获取屏幕显示尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取精灵位置
	Point spritePosition = getPosition();
	//获取精灵大小尺寸
	Size contentSize = m_sprite->getContentSize();

	//与右边界比较，防止跑到右边界外
	float x = std::min(spritePosition.x, mapSize.width - (contentSize.width / 2 - 10));
	//与左边界比较，防止跑到左边界外
	x = std::max(x, contentSize.width / 2 - 10);
	//防止跑到下边界外
	float y = std::max(0.0f, spritePosition.y);

	Point playerPos = Point(x, y);

	this->setPosition(playerPos);

	/*log("x: %f, y: %f", spritePosition.x, spritePosition.y);*/

	//如果主角坐标位于屏幕中点的左下方，则取屏幕中点坐标，否则取主角坐标
	x = std::max(spritePosition.x, visibleSize.width / 2);
	y = std::max(spritePosition.y, visibleSize.height / 2);
	//如果X、Y的坐标大于右上角的极限值，则取极限值坐标
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//目标点
	Point destPosition = Point(x, y);
	//屏幕中点
	Point centerPosition = Point(visibleSize.width / 2, visibleSize.height / 2);
	//屏幕中点和所要移动的目的点之间的距离
	Point viewPos = centerPosition - destPosition;

	parent->setPosition(viewPos);

}

void Player::turnAround(bool isRight)
{
	m_sprite->setFlipX(!isRight);
}


void Player::idle()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_idle", m_strPlayerName).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_sprite->runAction(animate);
}

void Player::run()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_run", m_strPlayerName).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
	m_sprite->runAction(animate);
}

void Player::attack()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* attackAnimation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_attack", m_strPlayerName).c_str());
	//生成动画动作
	Animate* attackAnimate = Animate::create(attackAnimation); 
	//发出产生火球的消息
	auto sendAttackMsg = CallFunc::create([]() {NotificationCenter::getInstance()->postNotification("set_attack_flying_object", NULL); });
	//回调检查控制器状态函数
	auto callfunc = CallFunc::create(CC_CALLBACK_0(Player::checkControllerStatus, this));
	Sequence* actionSequnence = Sequence::create(attackAnimate, sendAttackMsg, callfunc, nullptr);
	m_sprite->runAction(actionSequnence);
}

void Player::jump()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_jump", m_strPlayerName).c_str());
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
	m_sprite->runAction(sequence);
}

void Player::climb()
{
	//停止当前的动作
	m_sprite->stopAllActions();
	//获取已经做好的动画
	Animation* animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("%s_climb", m_strPlayerName).c_str());
	//生成动画动作
	Animate* animate = Animate::create(animation);
	//执行动画动作
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
