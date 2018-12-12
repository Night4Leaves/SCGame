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

		//TODO:��Tiled�����ĵ�ͼ����������
		//TMXTiledMap* map = TMXTiledMap::create("map/scene_main.tmx");
		//this -> addChild(map);

		////��ȡ����������ݴ�С����ͼƬ��С
		//Size size = map->getContentSize();
		////��ȡOpenGL��ͼ���
		//Size winSize = Director::getInstance()->getWinSize();

		////����ͼƬ��С����ͼ���������Ա���ͼƬ�������ţ�ȷ������û�к���
		//map->setScale(MAX(winSize.width / size.width, winSize.height / size.height));

		//��ʼ�������㲢��ӵ�������
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//��ӱ���ͼƬ
		m_pBackgroundLayer->setBackgroundPicture("background/main_scene_01_2048x1536.png");

		//��ʼ��NPC�㲢��ӵ�������
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//����NPC
		m_pNPCLayer->setMainSceneNPC();

		//��ʼ���˵��㲢��ӵ�������
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//����������˵�
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
