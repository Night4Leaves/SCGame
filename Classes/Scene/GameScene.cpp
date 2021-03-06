#include "GameScene.h"

#include "Layer/BackgroundLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"
#include "Layer/ScoreCountLayer.h"

#include "Entity/BossSkill.h"

#include "HeartCount.h"
#include "PlayerInfo.h"


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
		BossSkill::getInstance()->setGameLayer(m_pGameLayer);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		m_pGameMenuLayer->setGameMenu();

		//初始化分数显示层并添加到场景中
		m_pScoreCountLayer = ScoreCountLayer::create(0);
		CC_BREAK_IF(m_pScoreCountLayer == nullptr);
		this->addChild(m_pScoreCountLayer);

		PlayerData player = PlayerInfo::getInstance()->getPlayerData();

		m_pHeartCount = HeartCount::create(player.i_HP);
		this->addChild(m_pHeartCount);
		m_pHeartCount->setPosition(0, 570);

		//初始化显示层并添加到场景中
		m_pPaneLayer = PaneLayer::create();
		CC_BREAK_IF(m_pPaneLayer == nullptr);
		this->addChild(m_pPaneLayer);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameScene::playerReduceHeart),
			"monster_attack",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameScene::playerRecoverHeart),
			"revocer_HP",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameScene::gameClear),
			"scene_game_clear",
			NULL);

		return true;
	} while (0);

	log("GameScene initialize failed!");

	return false;
}

void GameScene::setScene(SceneType sign)
{
	PlayerData player = PlayerInfo::getInstance()->getPlayerData();
	m_enSceneType = sign;

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
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_02_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_2_1(player);
		break;
	case Scene_4:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/game_scene_02_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_2_2(player);
		break;
	case Scene_5:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/initial_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_3_1(player);
		break;
	case Scene_6:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_3_2(player);
		break;
	case Scene_7:
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");
		//设置场景中的角色
		m_pGameLayer->setGameScene_4_1(player);
		break;
	default:
		break;
	}
}

void GameScene::playerReduceHeart(Ref * pSender)
{
	m_pHeartCount->reduceHP();
}

void GameScene::playerRecoverHeart(Ref * pSender)
{
	m_pHeartCount->recoverHP();
}

void GameScene::gameClear(Ref * pSender)
{
	PlayerInfo::getInstance()->setLevel(m_enSceneType + 1);
	int attack = PlayerInfo::getInstance()->getAttack();

	switch (m_enSceneType)
	{
	case Scene_1:
		if (attack == 10 || attack == 15)
		{
			attack += 3;
		}
		break;
	case Scene_2:
		if (attack == 13 || attack == 18)
		{
			attack += 2;
		}
		break;
	case Scene_3:
		if (attack == 15 || attack == 20)
		{
			attack += 3;
		}
		break;
	case Scene_4:
		if (attack == 18 || attack == 23)
		{
			attack += 2;
		}
		break;
	case Scene_5:
		if (attack == 20 || attack == 25)
		{
			attack += 5;
		}
		break;
	case Scene_6:
		if (attack == 25 || attack == 30)
		{
			attack += 5;
		}
		break;
	case Scene_7:
		break;
	default:
		break;
	}

	PlayerInfo::getInstance()->setAttack(attack);
	JsonUtil::getInstance()->writeSavedata();
}
