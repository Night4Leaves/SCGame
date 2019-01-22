#include "GameMenuLayer.h"
#include "Util/MenuItemUtil.h"
#include "Scene/MainScene.h"
#include "PaneLayer.h"

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
	ButtonWithTextPicture gameStartButtonType = { "Button", "gamestart", 0.5, this, menu_selector(GameMenuLayer::startGame) };
	MenuItemSprite* aButtonSprite = MenuItemUtil::createMenuItemSpriteByPicture(gameStartButtonType);

	ButtonWithTextPicture continueButtonType = { "Button", "continue", 0.5, this, menu_selector(GameMenuLayer::continueGame) };
	MenuItemSprite* bButtonSprite = MenuItemUtil::createMenuItemSpriteByPicture(continueButtonType);

	ButtonWithTextPicture optionButtonType = { "Button", "option", 0.5, this, menu_selector(GameMenuLayer::openOptionWin) };
	MenuItemSprite* cButtonSprite = MenuItemUtil::createMenuItemSpriteByPicture(optionButtonType);

	ButtonWithTextPicture exitButtonType = { "Button", "exit", 0.5, this, menu_selector(GameMenuLayer::exitGame) };
	MenuItemSprite* dButtonSprite = MenuItemUtil::createMenuItemSpriteByPicture(exitButtonType);

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
	log("startGame");
	NotificationCenter::getInstance()->postNotification("selectCharacter", NULL);

	/*Scene* mainScene = MainScene::createScene();
	Director::getInstance()->replaceScene(mainScene);*/
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
