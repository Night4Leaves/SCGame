#include "GameScene.h"

#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"
#include "Entity/Monster.h"
#include "Controller/MonsterController.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

Scene * GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	do {
		CC_BREAK_IF(!Scene::init());

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		//m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");

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

		PlayerController* playerController = PlayerController::create();
		player->setController(playerController);
		this->addChild(playerController);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		return true;
	} while (0);

	log("GameScene initialize failed!");

	return false;
}

void GameScene::setScene(SceneType sign)
{
	switch (sign)
	{
	case Scene_1:
		break;
	case Scene_2:
		break;
	case Scene_3:
		break;
	case Scene_4:
		break;
	case Scene_5:
		break;
	case Scene_6:
		break;
	case Scene_7:
		break;
	default:
		break;
	}
}
