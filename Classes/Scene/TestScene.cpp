#include "TestScene.h"

#include "Util/CsvAnalyzeUtil.h"
#include "Util/CsvLoadUtil.h"

#include "Json/json.h"

#include "Layer/PaneLayer.h"
#include "Layer/ScoreCountLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/GameLayer.h"

#include "CustomizeEnum.h"

#include "Entity/Player.h"
#include "Entity/Monster.h"

#include "Controller/PlayerController.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

TestScene * TestScene::createScene()
{
	return TestScene::create();
}

bool TestScene::init()
{
	do 
	{
		//TMXTiledMap* map = TMXTiledMap::create("map/test_map.tmx");
		//this->addChild(map);

		//Player* player = Player::create("player_01");
		//this->addChild(player);
		//player->setPosition(400, 300);
		//player->idle();
		////player->setMap(map);

		//PlayerController* playerController = PlayerController::create();
		//player->setController(playerController);
		//this->addChild(playerController);
		//playerController->setMap(map);

		//this->scheduleUpdate();

		//auto test = Sprite::createWithSpriteFrameName("backpack.png");
		//this->addChild(test);
		//test->setPosition(400, 300);
		//test->setScale(0.5);

		/*auto gameLayer = GameLayer::create();
		this->addChild(gameLayer);
		gameLayer->setTestGameScene();*/

		/*auto test = GameMenuLayer::create();
		this->addChild(test);
		test->setInitialMenu();

		auto panetest = PaneLayer::create();
		this->addChild(panetest);*/

		//HelloLua::create();

		MonsterData monsterData = { "boss_01", 100, 10, 10, 100, 5, 5 };
		Monster* monster = Monster::create(monsterData);
		monster->setMonsterPosition(Point(400,300));
		monster->idle();
		monster->setScale(0.35);
		this->addChild(monster);

	} while (0);

	return true;
}

void TestScene::update(float dt)
{
	
}

void TestScene::readJson()
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile("json/test.json");

	if (reader.parse(data, root, false) == true)
	{
		log("id = %d", root["id"].asInt());
		log("name = %s", root["name"].asCString());
		log("HP = %f", root["hp"].asDouble());
		log("money = %d", root["item"]["money"].asInt());
		log("HP medice = %d", root["item"]["hpmedice"].asInt());
		log("sword fire = %d", root["item"]["sword"]["fire"].asInt());
		log("sword water = %d", root["item"]["sword"]["water"].asInt());
	}
}

void TestScene::readArrayJson()
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile("json/player_info.json");

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			log("name = %s", root[i]["name"].asCString());
			log("hp = %d", root[i]["hp"].asInt());
			log("attack = %d", root[i]["attack"].asInt());
		}
	}
}

void TestScene::writeJson()
{
	Json::Value root;
	Json::FastWriter writer;

	for (int i = 0; i < 3; i++)
	{
		root[i]["name"] = "a";
		root[i]["hp"] = i;
		root[i]["item"]["sord"] = 6;
		root[i]["item"]["hpme"] = 10;
		root[i]["item"]["sword"]["none"] = 1;
		root[i]["item"]["sword"]["fire"] = 6;
	}

	std::string json_file = writer.write(root);

	FILE* file = fopen("json/test1.json", "w");
	fprintf(file, json_file.c_str());
	fclose(file);
}
