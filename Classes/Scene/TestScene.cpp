#include "TestScene.h"

#include "Util/JsonUtil.h"
#include "Util/MenuItemUtil.h"

#include "Json/json.h"

#include "Layer/PaneLayer.h"
#include "Layer/ScoreCountLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/ShieldLayer.h"
#include "Layer/SceneItemLayer.h"

#include "CustomizeEnum.h"
#include "HeartCount.h"
#include "GameManager.h"
#include "PlayerInfo.h"
#include "CharacterSelector.h"

#include "Entity/Player.h"
#include "Entity/Monster.h"
#include "Entity/Boss.h"
#include "Entity/CombatEntity.h"


#include "Controller/PlayerController.h"

TestScene::TestScene()
	: dtCount(0)
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
		BossFlyingObjectInfo info = { "boss_beam", Point(700, 200), Point(200, 200), false, true };

		test = BossFlyingObject::create(info);
		this->addChild(test);
		test->scheduleUpdate();
		

		//JsonUtil::getInstance()->deleteSavedata(1554709236);

		/*std::vector<PlayerData> vec_SavedataList;
		JsonUtil::getInstance()->readSavedata(vec_SavedataList);
		vec_SavedataList[0].i_dataNumber = 12037;
		PlayerInfo::getInstance()->setPlayerData(vec_SavedataList[0]);
		PlayerInfo::getInstance()->setMoney(999);
		JsonUtil::getInstance()->writeSavedata();*/

		/*TMXTiledMap* map = TMXTiledMap::create("map/test_map.tmx");
		this->addChild(map);

		GameManager::getInstance()->setMap(map);*/

		//std::vector<MonsterData> monsterInfoList;
		//JsonUtil::getInstance()->readMonsterInfo(monsterInfoList);

		//monster = Monster::create(monsterInfoList[14]);
		//monster->setMonsterOriginPosition(Point(500, 300));
		//monster->idle();
		//monster->setScale(0.35);
		//this->addChild(monster);

		//this->scheduleUpdate();
		

		/*std::vector<PlayerData> m_vecCharacterList;
		JsonUtil::getInstance()->readPlayerInfo(m_vecCharacterList);

		auto gameLayer = GameLayer::create();
		this->addChild(gameLayer);
		gameLayer->setGameScene_1_1(m_vecCharacterList[0]);*/

		

		/*Player* player = Player::create(m_vecCharacterList[0]);
		this->addChild(player);
		player->setPosition(200, 300);
		player->idle();

		PlayerController* playerController = PlayerController::create();
		player->setController(playerController);
		this->addChild(playerController);*/

		/*std::vector<BossData> bossDataList;
		JsonUtil::getInstance()->readBossInfo(bossDataList);

		boss = BossTianzhao::create(bossDataList[5]);
		this->addChild(boss);
		boss->setBossPosition(Point(300, 300));
		boss->idle();
		boss->setScale(0.45);*/

		//auto test = Sprite::createWithSpriteFrameName("backpack.png");
		//this->addChild(test);
		//test->setPosition(400, 300);
		//test->setScale(0.5);

		/*auto test = GameMenuLayer::create();
		this->addChild(test);
		test->setInitialMenu();*/

		//auto panetest = PaneLayer::create();
		//this->addChild(panetest);

	} while (0);

	return true;
}

void TestScene::update(float dt)
{
	dtCount += dt;

	if (dtCount > 3)
	{
		test->scheduleUpdate();
	}

	/*if (dtCount > 6)
	{
		monster->attack();
	}
	else if (dtCount > 4)
	{
		monster->run();
	}
	else if (dtCount > 2)
	{
		monster->hurt();
	}*/
}

void TestScene::changeGameScene(Ref * pSender)
{
	log("ok");
}

void TestScene::readJson()
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile("json/test.json");

	if (reader.parse(data, root, false) == true)
	{
		
		log("name = %s", root["name"].asCString());
		
	}
}

void TestScene::readArrayJson()
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile("json/test.json");

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			log("name = %s", root[i]["name"].asCString());
			auto jsonTest = root[i]["array"];
			int ii = jsonTest.size();
			for (int iii = 0; iii < ii; ++iii)
			{
				log("%d", jsonTest[iii].asInt());
			}
			
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
