#include "GameScene.h"

#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"

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
