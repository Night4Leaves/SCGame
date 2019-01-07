#include "InitialScene.h"
#include "Layer/BackgroundLayer.h"
#include "Layer/GameMenuLayer.h"
#include "Layer/PaneLayer.h"

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

		//初始化背景层并添加到场景中
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//添加背景图片
		m_pBackgroundLayer->setBackgroundPicture("background/initial_scene_01_2048x1536.png");
		m_pBackgroundLayer->setGameTitleByPicture("title.png");

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);
		//创建开始界面菜单
		m_pGameMenuLayer->setInitialMenu();

		return true;
	} while (0);

	log("InitialScene initialize failed!");

	return false;
}
