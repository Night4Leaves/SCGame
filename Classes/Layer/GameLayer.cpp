#include "GameLayer.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"
#include "Entity/Monster.h"
#include "Controller/MonsterController.h"
#include "Entity/FlyingObject.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::addFlyingObject),
			"attack",
			NULL);

		m_pMap = TMXTiledMap::create("map/map_1-1.tmx");
		CC_BREAK_IF(m_pMap == nullptr);
		this->addChild(m_pMap);

		TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

		ValueMap monsterPoint = objGroup->getObject("monster");

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		Monster* monster = Monster::create("boss_01");
		monster->setPosition(Vec2(monsterX, monsterY));
		monster->idle();
		this->addChild(monster);

		MonsterController* monsterController = MonsterController::create();
		monster->setController(monsterController);
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
		player->setController(playerController);
		this->addChild(playerController);

		return true;
	} while (0);

	log("GameLayer initialize failed!");

	return false;
}

void GameLayer::addFlyingObject(Ref * pSender)
{
	Point playerPoint = m_pPlayer->getPosition();
	Size playerSize = m_pPlayer->getCollisionSize();

	float x = playerPoint.x + playerSize.width / 2;
	float y = playerPoint.y + playerSize.height / 2;

	FlyingObject* flyingObject = FlyingObject::create("fireball", Vec2(150, 0));
	flyingObject->setCurrentPoint(Vec2(x, y));
	flyingObject->setXSpeed(HORIZONTAL_SPPED + 1);
	this->addChild(flyingObject);
}
