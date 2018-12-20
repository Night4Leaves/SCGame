#include "MainScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/NPCLayer.h"
#include "Layer/PaneLayer.h"
#include "Entity/Player.h"
#include "Entity/Monster.h"
#include "Controller/PlayerController.h"
#include "Controller/MonsterController.h"

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

		Sprite* tpBackSprite = Sprite::createWithSpriteFrameName("tp_back.png");
		Sprite* tpfrontSprite = Sprite::createWithSpriteFrameName("tp_front.png");

		this->addChild(tpBackSprite);
		tpBackSprite->addChild(tpfrontSprite);

		Size tpBackSize = tpBackSprite->getContentSize();
		tpfrontSprite->setPosition(tpBackSize.width * 0.5, tpBackSize.height * 0.5);

		tpBackSprite->setPosition(Vec2(450, 150));
		//tpfrontSprite->setPosition(Vec2(450, 150));

		tpBackSprite->setScale(0.2);
		//tpfrontSprite->setScale(0.2);

		tpBackSprite->setOpacity(150);
		//tpfrontSprite->setOpacity(200);

		auto test1 = RotateBy::create(5.0f, -90.0f);
		auto test2 = RotateBy::create(5.0f, 180.0f);

		tpBackSprite->runAction(RepeatForever::create(test1));
		tpfrontSprite->runAction(RepeatForever::create(test2));

		//初始化NPC层并添加到场景中
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//设置NPC
		m_pNPCLayer->setMainSceneNPC();

		Monster* monster = Monster::create("boss_01");
		monster->setPosition(600, 100);
		monster->idle();
		this->addChild(monster);

		MonsterController* monsterController = MonsterController::create();
		monster->setController(monsterController);
		this->addChild(monsterController);

		//添加玩家角色
		Player* player = Player::create("player_01");
		player->setPosition(100, 100);
		player->idle();
		this->addChild(player);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//创建主界面菜单
		m_pGameMenuLayer->setMainMenu();

		//添加玩家控制器
		PlayerController* playerController = PlayerController::create();
		player->setController(playerController);
		this->addChild(playerController);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}
