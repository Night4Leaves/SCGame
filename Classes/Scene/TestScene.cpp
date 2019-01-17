#include "TestScene.h"
#include "Util/CsvAnalyzeUtil.h"
#include "Util/CsvLoadUtil.h"

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
		CC_BREAK_IF(!Scene::create());

		const char* sPath = "csv/test.csv";

		CsvLoadUtil::getInstance()->loadFile(sPath);

		Value firstPlayer = CsvLoadUtil::getInstance()->getValue(2, 1, sPath);

		log("value = %s", firstPlayer.asString().c_str());
	} while (0);

	return true;
}
