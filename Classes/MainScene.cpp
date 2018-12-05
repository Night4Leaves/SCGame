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

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("village_004_2048x1536.png");

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		return true;
	} while (0);

	log("MainScene initialize failed!");

	return false;
}
