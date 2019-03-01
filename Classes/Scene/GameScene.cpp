#include "GameScene.h"

#include "Layer/BackgroundLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"
#include "Layer/ScoreCountLayer.h"

#include "Entity/Player.h"

#include "Util/MapUtil.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

GameScene * GameScene::createScene()
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
		m_pBackgroundLayer->setPosition(Vec2(0, 200));
		
		m_pGameLayer = GameLayer::create();
		CC_BREAK_IF(m_pGameLayer == nullptr);
		this->addChild(m_pGameLayer);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		//初始化分数显示层并添加到场景中
		m_pScoreCountLayer = ScoreCountLayer::create(0);
		CC_BREAK_IF(m_pScoreCountLayer == nullptr);
		this->addChild(m_pScoreCountLayer);

		m_pPaneLayer = PaneLayer::create();
		CC_BREAK_IF(m_pPaneLayer == nullptr);
		this->addChild(m_pPaneLayer);

		return true;
	} while (0);

	log("GameScene initialize failed!");

	return false;
}

void GameScene::setScene(SceneType sign, Player* player)
{
	switch (sign)
	{
	case Scene_1:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		m_pGameLayer->setGameScene_1_1(player);
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
