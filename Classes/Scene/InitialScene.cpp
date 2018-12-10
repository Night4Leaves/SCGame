#include "InitialScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"

InitialScene::InitialScene()
{
}

InitialScene::~InitialScene()
{
}

Scene * InitialScene::createScene()
{
	return InitialScene::create();
}

bool InitialScene::init()
{
	do {
		CC_BREAK_IF(!Scene::init());

		//��ʼ�������㲢��ӵ�������
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//��ӱ���ͼƬ
		m_pBackgroundLayer->setBackgroundPicture("background/initial_scene_01_2048x1536.png");
		m_pBackgroundLayer->setGameTitle("SCGame", "fonts/Marker Felt.ttf", 30, Color3B::ORANGE);

		//��ʼ���˵��㲢��ӵ�������
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//������ʼ����˵�
		m_pGameMenuLayer->setInitialMenu();

		return true;
	} while (0);

	log("InitialScene initialize failed!");

	return false;
}
