#include "GameMenuLayer.h"
#include "Util/MenuItemUtil.h"
#include "Scene/MainScene.h"
#include "PaneLayer.h"
#include "CustomizeEnum.h"

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

	Menu* menu = Menu::create();

	//创建菜单选项
	ButtonWithTextPicture buttonType = { "Button", "gamestart", 0.5, this, menu_selector(GameMenuLayer::startGame) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "continue", 0.5, this, menu_selector(GameMenuLayer::continueGame) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "option", 0.5, this, menu_selector(GameMenuLayer::openOptionWin) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "exit", 0.5, this, menu_selector(GameMenuLayer::exitGame) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	this->addChild(menu);

	//设置菜单位置
	Size winSize = Director::getInstance()->getWinSize();
	menu->setPosition(winSize.width * 0.5, winSize.height * 0.4);
	menu->alignItemsVerticallyWithPadding(20);

}

void GameMenuLayer::setMainMenu()
{
	TTFConfig fontConfig = { "fonts/arial.ttf", 40 };

	Menu* menu = Menu::create();

	ButtonOnlyImageType buttonInfo = { "menubar_01.png", "menubar_01.png", 0.5, this, menu_selector(GameMenuLayer::openBackpack) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonInfo));

	buttonInfo = { "menubar_02.png", "menubar_02.png", 0.5, this, menu_selector(GameMenuLayer::openSkillList) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonInfo));

	buttonInfo = { "menubar_03.png", "menubar_03.png", 0.5, this, menu_selector(GameMenuLayer::openSkillList) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonInfo));

	Size winSize = Director::getInstance()->getWinSize();
	menu->setPosition(winSize.width * 0.87, winSize.height * 0.06);
	menu->alignItemsHorizontallyWithPadding(8);
	this->addChild(menu);
}

void GameMenuLayer::startGame(CCObject * sender)
{
	log("startGame");
	NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref*)en_paneMsg_selectCharacter);
}

void GameMenuLayer::continueGame(CCObject * sender)
{
	log("continueGame");
	NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref*)en_paneMsg_loadFile);
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

void GameMenuLayer::openBackpack(CCObject * sender)
{
	log("openBackpack");
}

void GameMenuLayer::openSkillList(CCObject * sender)
{
	log("openSkillList");
}

void GameMenuLayer::openOption(CCObject * sender)
{
	log("openOption");
}
