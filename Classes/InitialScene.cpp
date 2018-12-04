#include "InitialScene.h"
#include "BackgroundLayer.h"
#include "TextDisplayLayer.h"
#include "GameMenuLayer.h"

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
		m_pBackgroundLayer->setBackgroundPicture("fantasy_001_2048x1536.png");

		//初始化文字显示层并添加到场景中
		m_pTextDisplayLayer = TextDisplayLayer::create();
		CC_BREAK_IF(m_pTextDisplayLayer == nullptr);
		this->addChild(m_pTextDisplayLayer);
		//添加标题
		m_pTextDisplayLayer->setGameTitle("SCGame", "fonts/Marker Felt.ttf", 30, Color3B::ORANGE);

		//初始化菜单层并添加到场景中
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		return true;
	} while (0);

	log("InitialScene initialize failed!");

	return false;
}
