#include "TestScene.h"
#include "Util/CsvAnalyzeUtil.h"
#include "Util/CsvLoadUtil.h"
#include "Json/json.h"
#include "FSM/mutou.h"
#include "FSM/MutouT.h"
#include "FSM/MutouTFSM.h"
#include "Layer/PaneLayer.h"
#include "CustomizeEnum.h"

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
		
		auto test = PaneLayer::create();
		CC_BREAK_IF(test == nullptr);
		this->addChild(test);

		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref *)en_paneMsg_selectCharacter);
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref *)en_paneMsg_loadFile);
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref *)en_paneMsg_openStore);
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref *)en_paneMsg_pause);
		NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref *)en_paneMsg_selectGameScene);

	} while (0);

	return true;
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
