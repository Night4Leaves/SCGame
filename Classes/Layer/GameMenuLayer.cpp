#include "GameMenuLayer.h"
#include "Util/MenuItemUtil.h"
#include "Scene/MainScene.h"

GameMenuLayer::GameMenuLayer()
{
}

GameMenuLayer::~GameMenuLayer()
{
}

bool GameMenuLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);

	log("GameMenuLayer initialize failed!");

	return false;
}

void GameMenuLayer::setInitialMenu()
{
	TTFConfig fontConfig = { "fonts/arial.ttf", 40 };

	//创建菜单选项
	ButtonWithFontType gameStartButtonType = { "Button", "Game Start", fontConfig, 0.5, this, menu_selector(GameMenuLayer::startGame) };
	MenuItemSprite* aButtonSprite = MenuItemUtil::createMenuItemSprite(gameStartButtonType);

	ButtonWithFontType continueButtonType = { "Button", "Continue", fontConfig, 0.5, this, menu_selector(GameMenuLayer::continueGame) };
	MenuItemSprite* bButtonSprite = MenuItemUtil::createMenuItemSprite(continueButtonType);

	ButtonWithFontType optionButtonType = { "Button", "Option", fontConfig, 0.5, this, menu_selector(GameMenuLayer::openOptionWin) };
	MenuItemSprite* cButtonSprite = MenuItemUtil::createMenuItemSprite(optionButtonType);

	ButtonWithFontType exitButtonType = { "Button", "Exit", fontConfig, 0.5, this, menu_selector(GameMenuLayer::exitGame) };
	MenuItemSprite* dButtonSprite = MenuItemUtil::createMenuItemSprite(exitButtonType);

	//创建菜单
	Menu* menu = Menu::create(aButtonSprite, bButtonSprite, cButtonSprite, dButtonSprite, NULL);
	if (menu == nullptr)
	{
		log("setInitialMenu set failed!");
		return;
	}
	else
	{
		this->addChild(menu);

		//设置菜单位置
		Size winSize = Director::getInstance()->getWinSize();
		menu->setPosition(winSize.width * 0.5, winSize.height * 0.4);
		menu->alignItemsVerticallyWithPadding(20);
		
	}
	
}

void GameMenuLayer::setMainMenu()
{

}

void GameMenuLayer::startGame(CCObject * sender)
{
	Scene* mainScene = MainScene::createScene();
	Director::getInstance()->replaceScene(mainScene);
}

void GameMenuLayer::continueGame(CCObject * sender)
{
	log("continueGame");
}

void GameMenuLayer::openOptionWin(CCObject * sender)
{
	log("openOptionWin");
}

void GameMenuLayer::exitGame(CCObject * sender)
{
	Director::getInstance()->end();
}

void GameMenuLayer::selectGameScene(CCObject * sender)
{
	log("selectGameScene");
}
