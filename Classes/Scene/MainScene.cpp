#include "MainScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/NPCLayer.h"
#include "Layer/PaneLayer.h"
#include "Entity/Player.h"
#include "Entity/Portal.h"
#include "Controller/PlayerController.h"
#include "Util/AnimationUtil.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

Scene * MainScene::create(Player *player)
{
	MainScene *pRet = new(std::nothrow) MainScene();
	if (pRet && pRet->init(player))
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

bool MainScene::init(Player *player)
{
	do {
		CC_BREAK_IF(!Scene::init());

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");

		//地图层(记录了各物品位置信息)
		m_pMap = TMXTiledMap::create("map/scene_main.tmx");
		CC_BREAK_IF(m_pMap == nullptr);
		this->addChild(m_pMap);

		TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

		//场景物品传送门
		Portal* portal = Portal::create();
		CC_BREAK_IF(portal == nullptr);
		this->addChild(portal);

		ValueMap portalPoint = objGroup->getObject("portal");

		float portalX = portalPoint.at("x").asFloat();
		float portalY = portalPoint.at("y").asFloat();

		portal->setPosition(Vec2(portalX, portalY));
		portal->setScale(0.2);
		portal->setOpacity(150);	

		//初始化NPC层并添加到场景中
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//设置NPC
		m_pNPCLayer->setMainSceneNPC(objGroup);

		//添加玩家角色
		m_pPlayer = player;

		ValueMap playerPoint = objGroup->getObject("player");

		float playerX = playerPoint.at("x").asFloat();
		float playerY = playerPoint.at("y").asFloat();

		m_pPlayer->setPosition(Vec2(playerX, playerY));
		m_pPlayer->idle();
		this->addChild(m_pPlayer);

		//添加玩家控制器
		PlayerController* playerController = PlayerController::create();
		m_pPlayer->setController(playerController);
		this->addChild(playerController);

		playerController->setMap(m_pMap);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//创建主界面菜单
		m_pGameMenuLayer->setMainMenu();

		//特殊层(商店、技能、关卡选择等)
		m_pPaneLayer = PaneLayer::create();
		CC_BREAK_IF(m_pPaneLayer == nullptr);
		this->addChild(m_pPaneLayer);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}

