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

		//��ʼ��NPC�㲢��ӵ�������
		m_pNPCLayer = NPCLayer::create();
		CC_BREAK_IF(m_pNPCLayer == nullptr);
		this->addChild(m_pNPCLayer);
		//����NPC
		m_pNPCLayer->setMainSceneNPC();

		Monster* monster = Monster::create("boss_01");
		monster->setPosition(600, 100);
		monster->idle();
		this->addChild(monster);

		MonsterController* monsterController = MonsterController::create();
		monster->setController(monsterController);
		this->addChild(monsterController);

		//�����ҽ�ɫ
		Player* player = Player::create("player_01");
		player->setPosition(100, 100);
		player->idle();
		this->addChild(player);

		//��ʼ���˵��㲢��ӵ�������
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//����������˵�
		m_pGameMenuLayer->setMainMenu();

		//�����ҿ�����
		PlayerController* playerController = PlayerController::create();
		player->setController(playerController);
		this->addChild(playerController);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}
