#include "PaneLayer.h"
#include "Scene/GameScene.h"
#include "Scene/MainScene.h"
#include "Scene/InitialScene.h"
#include "Util/MenuItemUtil.h"
#include "Util/AnimationUtil.h"
#include "Util/JsonUtil.h"
#include "Entity/Player.h"
#include "CustomizeEnum.h"
#include "ShieldLayer.h"
#include "ShopItemButton.h"
#include "PlayerInfo.h"
#include "CharacterSelector.h"

PaneLayer::PaneLayer()
	: m_isOpen(false)
	, m_isLoadSavedata(true)
{
}

PaneLayer::~PaneLayer()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool PaneLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(PaneLayer::showPaneLayer),
			"show_PaneLayer",
			NULL);

		return true;
	} while (0);
	return false;
}

void PaneLayer::showPaneLayer(Ref * pSender)
{
	switch ((int)pSender)
	{
	case en_paneMsg_pause:
		this->startPause();
		break;
	case en_paneMsg_openEasyOption:
		this->openEasyOption(NULL);
		break;
	case en_paneMsg_openNormalOption:
		this->openNormalOption();
		break;
	case en_paneMsg_openBackpack:
		this->openBackpack();
		break;
	case en_paneMsg_openSkilllist:
		//this->openSkilllist();
		break;
	case en_paneMsg_selectGameScene:
		this->selectGameScene();
		break;
	case en_paneMsg_gameClear:
		this->gameEnd(true);
		break;
	case en_paneMsg_gameOver:
		this->gameEnd(false);
		break;
	case en_paneMsg_openItemStore:
		this->openStore();
		break;
	case en_paneMsg_openSkillStore:
		//this->openStore();
		break;
	case en_paneMsg_loadFile:
		this->loadFile();
		break;
	case en_paneMsg_selectCharacter:
		this->selectCharacter();
		break;
	default:
		break;
	}

}

void PaneLayer::saveData(Ref * pSender)
{
	JsonUtil::getInstance()->writeSavedata();
}

void PaneLayer::readData(Ref * pSender)
{
	this->loadFile();
}

void PaneLayer::enterMainScene(Ref * pSender)
{
	MainScene* mainScene = MainScene::create();
	Director::getInstance()->replaceScene(mainScene);
}

void PaneLayer::enterInitialScene(Ref * pSender)
{
	InitialScene* initialScene = InitialScene::create();
	Director::getInstance()->replaceScene(initialScene);
}

void PaneLayer::menuCloseCallback(Ref * pSender)
{
	log("ok");
	this->removeAllChildren();
	m_isOpen = false;
	NotificationCenter::getInstance()->postNotification("end_pause", NULL);
}

void PaneLayer::selectCharacter()
{
	log("PaneLayer::selectCharacter");
	
	std::vector<PlayerData> playerData;
	JsonUtil::getInstance()->readSavedata(playerData);
	int num = playerData.size();
	if (num == 4)
	{
		return;
	}

	//创建点击屏蔽层
	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto backMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	backMenuItem->setScale(0.2);

	Menu* backMenu = Menu::create(backMenuItem, NULL);
	this->addChild(backMenu);
	backMenu->setPosition(400, 180);

	//读取玩家角色数据
	JsonUtil::getInstance()->readPlayerInfo(playerData);
	int infoNum = playerData.size();

	if (infoNum > 0)
	{
		while (infoNum != 0)
		{
			CharacterSelector* test = CharacterSelector::create(playerData[infoNum - 1]);
			test->setCreateNewDataVol();
			this->addChild(test);
			int x = (infoNum - 1) * 150 - 230;
			test->setPosition(x, 0);
			infoNum--;
		}
	}
}

void PaneLayer::loadFile()
{
	log("PaneLayer::loadFile");

	std::vector<PlayerData> playerData;
	JsonUtil::getInstance()->readSavedata(playerData);
	int savedataNum = playerData.size();

	if (savedataNum == 0)
	{
		return;
	}

	//创建点击屏蔽层
	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto backMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	backMenuItem->setScale(0.2);

	Menu* backMenu = Menu::create(backMenuItem, NULL);
	this->addChild(backMenu);
	backMenu->setPosition(400, 180);

	if (savedataNum > 0)
	{
		while (savedataNum != 0)
		{
			CharacterSelector* test = CharacterSelector::create(playerData[savedataNum - 1]);
			test->setLoadSaveDataVol();
			this->addChild(test);
			int x = (savedataNum - 1) * 150 - 230;
			test->setPosition(x, 0);
			savedataNum--;
		}
	}
}

void PaneLayer::openStore()
{
	if (m_isOpen)
	{
		return;
	}

	m_isOpen = true;

	log("PaneLayer::openStore");

	this->addChild(ShieldLayer::create());

	Sprite* storeBG = Sprite::createWithSpriteFrameName("backpack.png");
	storeBG->setScale(0.5);
	storeBG->setPosition(400, 300);
	this->addChild(storeBG);

	ShopItemInfo itemInfo = { "bandaid", 1, 20, en_consumableItemType_bandaid };
	ShopItemButton* item = ShopItemButton::create(itemInfo);
	item->setStoreVol();
	this->addChild(item);
	item->setPosition(400, 400);

	itemInfo = { "mirror", 1, 50, en_consumableItemType_mirror };
	item = ShopItemButton::create(itemInfo);
	item->setStoreVol();
	this->addChild(item);
	item->setPosition(400, 300);

	itemInfo = { "sword", 1, 200, en_consumableItemType_sword };
	item = ShopItemButton::create(itemInfo);
	item->setStoreVol();
	this->addChild(item);
	item->setPosition(400, 200);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Close_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Close_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	closeMenuItem->setScale(0.2);

	Menu* closeMenu = Menu::create(closeMenuItem, NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(400, 110);
}

void PaneLayer::startPause()
{
	m_isOpen = true;

	log("PaneLayer::startPause");

	this->addChild(ShieldLayer::create());

	Menu* menu = Menu::create();
	
	//ButtonWithTextPicture buttonType = { "Button", "option", 0.5, this, menu_selector(PaneLayer::openEasyOption) };
	//menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	ButtonWithTextPicture buttonType = { "Button", "exit_game_scene", 0.5, this, menu_selector(PaneLayer::enterMainScene) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback));

	closeMenuItem->setScale(0.2);
	menu->addChild(closeMenuItem);

	this->addChild(menu);
	menu->setPosition(400, 300);
	menu->alignItemsVerticallyWithPadding(10);
}

void PaneLayer::openEasyOption(Ref * pSender)
{
	NotificationCenter::getInstance()->postNotification("start_pause", NULL);

	m_isOpen = true;

	log("PaneLayer::openEasyOption");

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	this->addChild(ShieldLayer::create());

	Menu* menu = Menu::create();

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback));

	closeMenuItem->setScale(0.2);
	menu->addChild(closeMenuItem);

	this->addChild(menu);
	menu->setPosition(400, 300);
	menu->alignItemsVerticallyWithPadding(10);
}

void PaneLayer::openNormalOption()
{
	NotificationCenter::getInstance()->postNotification("start_pause", NULL);

	m_isOpen = true;

	log("PaneLayer::openNormalOption");

	this->addChild(ShieldLayer::create());

	Menu* menu = Menu::create();

	ButtonWithTextPicture buttonType = { "Button", "savedata", 0.5, this, menu_selector(PaneLayer::saveData) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "readdata", 0.5, this, menu_selector(PaneLayer::readData) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	//buttonType = { "Button", "option", 0.5, this, menu_selector(PaneLayer::openEasyOption) };
	//menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "exit", 0.5, this, menu_selector(PaneLayer::enterInitialScene) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback));

	closeMenuItem->setScale(0.2);
	menu->addChild(closeMenuItem);

	this->addChild(menu);
	menu->setPosition(400, 300);
	menu->alignItemsVerticallyWithPadding(10);

}

void PaneLayer::selectGameScene()
{
	if (m_isOpen)
	{
		return;
	}

	m_isOpen = true;

	log("PaneLayer::selectGameScene");

	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Back_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Back_Selected.png");

	auto backMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	backMenuItem->setScale(0.2);

	Menu* backMenu = Menu::create(backMenuItem, NULL);
	this->addChild(backMenu);
	backMenu->setPosition(400, 110);

	TTFConfig ttf = { "fonts/arial.ttf", 40 };
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//第一组
	Point pos = Point(visibleSize.width / 4 + 60, visibleSize.height / 4 * 3 - 30);

	Sprite* buttonBG = Sprite::create("background/game_scene_01_2048x1536.png");
	buttonBG->setScale(0.1);
	buttonBG->setPosition(pos);

	this->addChild(buttonBG);

	ButtonWithFontType aButtonInfo = { "Button_Select_Game_Scene", "1-1", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_1_1) };
	MenuItemSprite* aButtonSprite = MenuItemUtil::createMenuItemSprite(aButtonInfo);
	ButtonWithFontType bButtonInfo = { "Button_Select_Game_Scene", "1-2", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_1_2) };
	MenuItemSprite* bButtonSprite = MenuItemUtil::createMenuItemSprite(bButtonInfo);

	Menu* menu = Menu::create(aButtonSprite, bButtonSprite, NULL);

	this->addChild(menu);

	menu->alignItemsVerticallyWithPadding(0);
	menu->setOpacity(100);
	menu->setPosition(pos);

	//第二组
	pos = Point(visibleSize .width / 4 * 3 - 60, visibleSize.height / 4 * 3 - 30);

	buttonBG = Sprite::create("background/game_scene_02_2048x1536.png");
	buttonBG->setScale(0.1);
	buttonBG->setPosition(pos);

	this->addChild(buttonBG);

	aButtonInfo = { "Button_Select_Game_Scene", "2-1", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_2_1) };
	aButtonSprite = MenuItemUtil::createMenuItemSprite(aButtonInfo);
	bButtonInfo = { "Button_Select_Game_Scene", "2-2", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_2_2) };
	bButtonSprite = MenuItemUtil::createMenuItemSprite(bButtonInfo);

	menu = Menu::create(aButtonSprite, bButtonSprite, NULL);

	this->addChild(menu);

	menu->alignItemsVerticallyWithPadding(0);
	menu->setOpacity(100);
	menu->setPosition(pos);

	//第三组
	pos = Point(visibleSize.width / 4 + 60, visibleSize.height / 4 + 70);

	buttonBG = Sprite::create("background/initial_scene_01_2048x1536.png");
	buttonBG->setScale(0.1);
	buttonBG->setPosition(pos);

	this->addChild(buttonBG);

	aButtonInfo = { "Button_Select_Game_Scene", "3-1", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_3_1) };
	aButtonSprite = MenuItemUtil::createMenuItemSprite(aButtonInfo);
	bButtonInfo = { "Button_Select_Game_Scene", "3-2", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_3_2) };
	bButtonSprite = MenuItemUtil::createMenuItemSprite(bButtonInfo);

	menu = Menu::create(aButtonSprite, bButtonSprite, NULL);

	this->addChild(menu);

	menu->alignItemsVerticallyWithPadding(0);
	menu->setOpacity(100);
	menu->setPosition(pos);

	//第四组
	pos = Point(visibleSize.width / 4 * 3 - 60, visibleSize.height / 4 + 70);

	buttonBG = Sprite::create("background/main_scene_01_2048x1536.png");
	buttonBG->setScale(0.1);
	buttonBG->setPosition(pos);

	this->addChild(buttonBG);

	aButtonInfo = { "Button_Select_Game_Scene", "4-1", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_4_1) };
	aButtonSprite = MenuItemUtil::createMenuItemSprite(aButtonInfo);
	bButtonInfo = { "Button_Select_Game_Scene", "", ttf, 1, this, menu_selector(PaneLayer::selectGameScene_4_1) };
	bButtonSprite = MenuItemUtil::createMenuItemSprite(bButtonInfo);

	menu = Menu::create(aButtonSprite, bButtonSprite, NULL);

	this->addChild(menu);

	menu->alignItemsVerticallyWithPadding(0);
	menu->setOpacity(100);
	menu->setPosition(pos);
}

void PaneLayer::selectGameScene_1_1(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_1);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_1_2(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_2)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_2);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_2_1(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_3)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_3);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_2_2(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_4)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_4);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_3_1(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_5)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_5);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_3_2(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_6)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_6);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_4_1(Ref * pSender)
{
	int level = PlayerInfo::getInstance()->getLevel();
	if (level <= Scene_7)
	{
		return;
	}
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_7);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::openBackpack()
{
	if (m_isOpen)
	{
		return;
	}

	m_isOpen = true;

	log("PaneLayer::openStore");

	this->addChild(ShieldLayer::create());

	Sprite* test = Sprite::createWithSpriteFrameName("backpack.png");
	test->setScale(0.5);
	test->setPosition(400, 300);
	this->addChild(test);

	ShopItemInfo itemInfo = { "bandaid", 1, 20,en_consumableItemType_bandaid };
	ShopItemButton* item = ShopItemButton::create(itemInfo);
	item->setBackpackVol();
	this->addChild(item);
	item->setPosition(400, 400);

	itemInfo = { "mirror", 1, 50, en_consumableItemType_mirror };
	item = ShopItemButton::create(itemInfo);
	item->setBackpackVol();
	this->addChild(item);
	item->setPosition(400, 300);

	itemInfo = { "sword", 1, 200, en_consumableItemType_sword };
	item = ShopItemButton::create(itemInfo);
	item->setBackpackVol();
	this->addChild(item);
	item->setPosition(400, 200);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Close_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Close_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	closeMenuItem->setScale(0.2);

	Menu* closeMenu = Menu::create(closeMenuItem, NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(400, 110);
}

void PaneLayer::openSkilllist()
{
	if (m_isOpen)
	{
		return;
	}

	m_isOpen = true;

	log("PaneLayer::openSkilllist");

	this->addChild(ShieldLayer::create());

	Sprite* test = Sprite::createWithSpriteFrameName("skill_list.png");
	test->setScale(0.4);
	test->setPosition(400, 300);
	this->addChild(test);

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Close_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Close_Selected.png");

	auto closeMenuItem = MenuItemSprite::create(
		buttonNormal,
		buttonSelected,
		this,
		menu_selector(PaneLayer::menuCloseCallback)
	);
	closeMenuItem->setScale(0.2);

	Menu* closeMenu = Menu::create(closeMenuItem, NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(400, 70);
}

void PaneLayer::gameEnd(bool isSuccess)
{
	this->addChild(ShieldLayer::create());

	if (isSuccess)
	{
		auto myLabel = Label::createWithTTF("Game Clear", "fonts/Marker Felt.ttf", 50);
		this->addChild(myLabel);
		myLabel->setPosition(400, 300);
		NotificationCenter::getInstance()->postNotification("scene_game_clear");
	}
	else
	{
		auto myLabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 50);
		this->addChild(myLabel);
		myLabel->setPosition(400, 300);
	}

	Menu* menu = Menu::create();
	ButtonWithTextPicture buttonType = { "Button", "exit_game_scene", 0.5, this, menu_selector(PaneLayer::enterMainScene) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));
	this->addChild(menu);
	menu->setPosition(400, 200);
}
