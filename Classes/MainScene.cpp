#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameMenuLayer.h"

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

		//��ʼ�������㲢���ӵ�������
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//���ӱ���ͼƬ
		m_pBackgroundLayer->setBackgroundPicture("village_004_2048x1536.png");

		//��ʼ���˵��㲢���ӵ�������
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}