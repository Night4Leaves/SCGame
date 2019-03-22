#include "GameScene.h"

#include "Layer/BackgroundLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"
#include "Layer/ScoreCountLayer.h"

#include "Entity/Player.h"

#include "HeartCount.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
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
		
		//初始化游戏层并添加到场景中
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

		//初始化现实层并添加到场景中
		m_pPaneLayer = PaneLayer::create();
		CC_BREAK_IF(m_pPaneLayer == nullptr);
		this->addChild(m_pPaneLayer);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameScene::updateScore),
			"update_score",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameScene::playerReduceHeart),
			"monster_attack",
			NULL);

		return true;
	} while (0);

	log("GameScene initialize failed!");

	return false;
}

void GameScene::setScene(SceneType sign, PlayerData & player)
{
	m_pPaneLayer->savePlayerData(player);

	m_pHeartCount = HeartCount::create(player.i_HP);
	this->addChild(m_pHeartCount);
	m_pHeartCount->setPosition(0, 570);

	m_pScoreCountLayer->setNumber(player.i_money);

	switch (sign)
	{
	case Scene_1:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_1_1(player);
		break;
	case Scene_2:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_1_2(player);
		break;
	case Scene_3:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_2_1(player);
		break;
	case Scene_4:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_2_2(player);
		break;
	case Scene_5:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_3_1(player);
		break;
	case Scene_6:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_3_2(player);
		break;
	case Scene_7:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_4_1(player);
		break;
	default:
		break;
	}
}

void GameScene::updateScore(Ref * pSender)
{
	int number = m_pScoreCountLayer->getNumber();
	number += (int)pSender;
	m_pScoreCountLayer->setNumber(number);
}

void GameScene::playerReduceHeart(Ref * pSender)
{
	m_pHeartCount->reduceHP();
}
