#include "MainScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/NPCLayer.h"
#include "Layer/PaneLayer.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"
#include "Entity/Portal.h"

#include "Util/AnimationUtil.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

Scene * MainScene::createSceneWithPlayer(Player *p_player)
{
	return MainScene::create(p_player);
}

MainScene * MainScene::create(Player *p_player)
{
	MainScene *pRet = new(std::nothrow) MainScene();
	if (pRet && pRet->init(p_player))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool MainScene::init(Player *p_player)
{
	do {
		CC_BREAK_IF(!Scene::init());

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");

		m_pMap = TMXTiledMap::create("map/scene_main.tmx");
		CC_BREAK_IF(m_pMap == nullptr);
		this->addChild(m_pMap);

		TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

		Portal* portal = Portal::create();
		CC_BREAK_IF(portal == nullptr);
		this->addChild(portal);

		ValueMap portalPoint = objGroup->getObject("portal");

		float portalX = portalPoint.at("x").asFloat();
		float portalY = portalPoint.at("y").asFloat();

		portal->setPosition(Vec2(portalX, portalY));
		//tpfrontSprite->setPosition(Vec2(450, 150));

		portal->setScale(0.2);
		//tpfrontSprite->setScale(0.2);

		portal->setOpacity(150);
		//tpfrontSprite->setOpacity(200);		

		//初始化NPC层并添加到场景中
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//设置NPC
		m_pNPCLayer->setMainSceneNPC(objGroup);

		//添加玩家角色
		//Player* player = Player::create("player_01");
		p_player->setMap(m_pMap);

		ValueMap playerPoint = objGroup->getObject("player");

		float playerX = playerPoint.at("x").asFloat();
		float playerY = playerPoint.at("y").asFloat();

		p_player->setPosition(Vec2(playerX, playerY));
		p_player->idle();
		this->addChild(p_player);
		Point pos = p_player->getPosition();
		log("x:%f, y:%f", pos.x, pos.y);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//创建主界面菜单
		m_pGameMenuLayer->setMainMenu();

		//添加玩家控制器
		PlayerController* playerController = PlayerController::create();
		p_player->setController(playerController);
		this->addChild(playerController);

		m_pPaneLayer = PaneLayer::create();
		this->addChild(m_pPaneLayer);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}

