#include "GameMenuLayer.h"
#include "MenuItemUtil.h"

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

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("UI.plist");

		TTFConfig fontConfig = { "fonts/arial.ttf", 40 };

		ButtonType gameStartButtonType = { "Button", "Game Start", fontConfig, this, menu_selector(GameMenuLayer::startGame) };
		MenuItemSprite* aButtonSprite = MenuItemUtil::createMenuItemSprite(gameStartButtonType);

		ButtonType continueButtonType = { "Button", "Continue", fontConfig, this, menu_selector(GameMenuLayer::continueGame) };
		MenuItemSprite* bButtonSprite = MenuItemUtil::createMenuItemSprite(continueButtonType);

		ButtonType optionButtonType = { "Button", "Option", fontConfig, this, menu_selector(GameMenuLayer::openOptionWin) };
		MenuItemSprite* cButtonSprite = MenuItemUtil::createMenuItemSprite(optionButtonType);

		ButtonType exitButtonType = { "Button", "Exit", fontConfig, this, menu_selector(GameMenuLayer::exitGame) };
		MenuItemSprite* dButtonSprite = MenuItemUtil::createMenuItemSprite(exitButtonType);

		Menu* menu = Menu::create(aButtonSprite, bButtonSprite, cButtonSprite, dButtonSprite, NULL);
		this->addChild(menu);

		Size winSize = Director::getInstance()->getWinSize();
		menu->setPosition(winSize.width * 0.5, winSize.height * 0.4);
		menu->alignItemsVerticallyWithPadding(20);

		return true;
	} while (0);

	log("GameMenuLayer initialize failed!");

	return false;
}

void GameMenuLayer::startGame(CCObject * sender)
{
	log("Game Start");
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
