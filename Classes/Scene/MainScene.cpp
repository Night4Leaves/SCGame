#include "MainScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/NPCLayer.h"
#include "Layer/PaneLayer.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"

#include "Util/ResourcesLoadingUtil.h"
#include "Util/AnimationUtil.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

Scene * MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	do {
		CC_BREAK_IF(!Scene::init());

		ResourcesLoadingUtil::preloadResources();

		//TODO:用Tiled制作的地图加载主界面
		//TMXTiledMap* map = TMXTiledMap::create("map/scene_main.tmx");
		//this -> addChild(map);

		////获取精灵对象内容大小，即图片大小
		//Size size = map->getContentSize();
		////获取OpenGL视图规格
		//Size winSize = Director::getInstance()->getWinSize();

		////根据图片大小与视图规格比例，对背景图片进行缩放，确保背景没有黑条
		//map->setScale(MAX(winSize.width / size.width, winSize.height / size.height));

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");

		//初始化NPC层并添加到场景中
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//设置NPC
		m_pNPCLayer->setMainSceneNPC();

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//创建主界面菜单
		m_pGameMenuLayer->setMainMenu();

		Sprite* sprite = Sprite::createWithSpriteFrameName("player_01_wait.png");

		Player* player = Player::create();
		player->bindSprite(sprite);
		player->setPosition(400, 300);
		this->addChild(player);

		PlayerController* playerController = PlayerController::create();
		playerController->setControllerListner(player);

		this->addChild(playerController);

		//this->addChild(sprite);

		//sprite->setPosition(400, 300);

		//Animation* animation = AnimationUtil::createAnimationWithSingleFrameName("player_01_idle", 0.25f, -1);
		//Animate* animate = Animate::create(animation);
		//sprite->runAction(animate);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}
