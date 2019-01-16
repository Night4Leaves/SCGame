#include "GameLayer.h"
#include "Scene/MainScene.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"
#include "Entity/Monster.h"
#include "Controller/MonsterController.h"
#include "Entity/AttackFlyingObject.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool GameLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		i_flyingObjectFlag = 0;

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::addAttackFlyingObject),
			"set_attack_flying_object",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::stoneRush),
			"player_point",
			NULL);

		m_pMap = TMXTiledMap::create("map/map_1-1.tmx");
		CC_BREAK_IF(m_pMap == nullptr);
		this->addChild(m_pMap);

		TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");
		
		int i = 1;
		while (true)
		{
			std::string monsterPointID = StringUtils::format("monster_%02d", i++);
			ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
			CC_BREAK_IF(monsterPoint.empty());

			float monsterX = monsterPoint.at("x").asFloat();
			float monsterY = monsterPoint.at("y").asFloat();

			Monster* monster = Monster::create("boss_01");
			monster->setPosition(Vec2(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);

			MonsterController* monsterController = MonsterController::create();
			monster->setController(monsterController);
			this->addChild(monsterController);
		}

		this->setSceneItem();

		ValueMap bossPoint = objGroup->getObject("boss");

		float bossX = bossPoint.at("x").asFloat();
		float bossY = bossPoint.at("y").asFloat();

		Monster* boss = Monster::create("boss_01");
		boss->setPosition(Vec2(bossX, bossY));
		boss->idle();
		this->addChild(boss);

		MonsterController* monsterController = MonsterController::create();
		boss->setController(monsterController);
		this->addChild(monsterController);

		ValueMap playerPoint = objGroup->getObject("player");

		float playerX = playerPoint.at("x").asFloat();
		float playerY = playerPoint.at("y").asFloat();

		Player* player = Player::create("player_01");
		player->setMap(m_pMap);
		player->setPosition(Vec2(playerX, playerY));
		player->idle();
		this->addChild(player);
		m_pPlayer = player;

		PlayerController* playerController = PlayerController::create();
		CC_BREAK_IF(playerController == nullptr);
		m_pPlayerController = playerController;
		player->setController(playerController);
		this->addChild(playerController);

		AtkFlyObjIniInfo fireballInfo = { "fireball", Vec2(HORIZONTAL_DISTANCE, 0), Vec2(HORIZONTAL_SPPED + 1, 0) };
		for (int i = 0; i < 3; i++)
		{
			AttackFlyingObject* flyingObject = AttackFlyingObject::create(fireballInfo);
			CC_BREAK_IF(flyingObject == nullptr);
			vector_pAttackFlyingObject.pushBack(flyingObject);
			this->addChild(flyingObject);
		}

		return true;
	} while (0);

	log("GameLayer initialize failed!");

	return false;
}

void GameLayer::update(float dt)
{
	Point stonePoint = m_stone->getPosition();
	stonePoint.x += stoneSpeed;
	m_stone->setPosition(stonePoint);
}

void GameLayer::addAttackFlyingObject(Ref * pSender)
{
	Point point_playerPoint = m_pPlayer->getPosition();		//玩家坐标
	Size size_playerSize = m_pPlayer->getCollisionSize();	//玩家形象大小
	bool b_isRight = m_pPlayerController->getIsRight();		//玩家是否朝右

	float f_x = 0.0f;	//飞行物X轴起始位置
	float f_y = point_playerPoint.y + size_playerSize.height / 2;	//飞行物Y轴起始位置

	//根据飞行方向设置数值
	if (b_isRight)
	{
		f_x = point_playerPoint.x + size_playerSize.width / 2;	//飞行物X轴起始位置
	}
	else
	{
		f_x = point_playerPoint.x - size_playerSize.width / 2;
	}

	AtkFlyObjPosInfo temp = { Point(f_x, f_y), b_isRight, point_playerPoint, Point() };

	AttackFlyingObject* p_flyingObject = (AttackFlyingObject*)vector_pAttackFlyingObject.at(i_flyingObjectFlag);
	p_flyingObject->setFlyingInformation(temp);

	i_flyingObjectFlag++;
	if (i_flyingObjectFlag == 3)
	{
		i_flyingObjectFlag = 0;
	}
}

void GameLayer::stoneRush(Ref * pSender)
{
	auto leverAction = RotateBy::create(1.0f, -30);
	auto stoneAction = RotateBy::create(1.0f, 90);

	m_lever->runAction(leverAction);
	m_stone->runAction(RepeatForever::create(stoneAction));

	stoneSpeed = 4;

	this->scheduleUpdate();
}

void GameLayer::setSceneItem()
{
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	ValueMap monsterPoint = objGroup->getObject("sceneitem_01");

	float monsterX = monsterPoint.at("x").asFloat();
	float monsterY = monsterPoint.at("y").asFloat();

	Sprite* monster_01 = Sprite::createWithSpriteFrameName("sceneitem_01.png");
	monster_01->setPosition(Vec2(monsterX, monsterY));
	this->addChild(monster_01);

	monsterPoint = objGroup->getObject("sceneitem_02");

	monsterX = monsterPoint.at("x").asFloat();
	monsterY = monsterPoint.at("y").asFloat();

	Sprite* monster = Sprite::createWithSpriteFrameName("sceneitem_02.png"); m_stone = monster;
	monster->setPosition(Vec2(monsterX, monsterY));
	this->addChild(monster);

	monster = Sprite::createWithSpriteFrameName("sceneitem_03.png"); m_lever = monster;
	monster->setPosition(Vec2(0, 20));
	monster->setRotation(15);
	monster_01->addChild(monster);

	poslog("lever", monster->getPosition().x, monster->getPosition().y);
}
