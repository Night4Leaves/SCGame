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

PaneLayer::PaneLayer()
	: m_isOpen(false)
	, m_isLoadSavedata(true)
{
	JsonUtil::getInstance()->readSavedata(m_vecSavedataList);
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
	case en_paneMsg_openBackpack:
		this->openBackpack();
		break;
	case en_paneMsg_openSkilllist:
		this->openSkilllist();
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
		this->openStore();
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

void PaneLayer::enterMainScene()
{
	MainScene* mainScene = MainScene::create();
	Director::getInstance()->replaceScene(mainScene);
}

void PaneLayer::changeMainScene(Ref * pSender)
{
	this->enterMainScene();
}

void PaneLayer::exitGameScene(Ref * pSender)
{
	NotificationCenter::getInstance()->postNotification("exit_game_scene", NULL);
}

void PaneLayer::menuCloseCallback(Ref * pSender)
{
	log("ok");
	this->removeAllChildren();
	m_isOpen = false;
	NotificationCenter::getInstance()->postNotification("end_pause", NULL);
}

void PaneLayer::createNewData()
{
}

void PaneLayer::selectCharacter()
{
	log("PaneLayer::selectCharacter");

	//创建点击屏蔽层
	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	//读取玩家角色数据
	JsonUtil::getInstance()->readPlayerInfo(m_vecCharacterList);

	auto menu = Menu::create();

	auto menuItem = this->createCharacterSelectItem(m_vecCharacterList, 0, menu_selector(PaneLayer::selectPlayer_1), false);
	menu->addChild(menuItem);

	menuItem = this->createCharacterSelectItem(m_vecCharacterList, 1, menu_selector(PaneLayer::selectPlayer_2), false);
	menu->addChild(menuItem);

	menu->setPosition(400, 300);
	menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);

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
}

void PaneLayer::loadFile()
{
	log("PaneLayer::loadFile");

	//创建点击屏蔽层
	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	auto savedataNum = m_vecSavedataList.size();
	log("save data num is %d", m_vecSavedataList.size());

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

	Menu* savedataListMenu = Menu::create();
	MenuItemSprite* menuItem;

	switch (savedataNum)
	{
	case 0:
		log("no save data");
		return;
	case 4:
		menuItem = this->createCharacterSelectItem(m_vecSavedataList, 3, menu_selector(PaneLayer::selectSavedata_4), true);
		savedataListMenu->addChild(menuItem);
	case 3:
		menuItem = this->createCharacterSelectItem(m_vecSavedataList, 2, menu_selector(PaneLayer::selectSavedata_3), true);
		savedataListMenu->addChild(menuItem);
	case 2:
		menuItem = this->createCharacterSelectItem(m_vecSavedataList, 1, menu_selector(PaneLayer::selectSavedata_2), true);
		savedataListMenu->addChild(menuItem);
	case 1:
		menuItem = this->createCharacterSelectItem(m_vecSavedataList, 0, menu_selector(PaneLayer::selectSavedata_1), true);
		savedataListMenu->addChild(menuItem);
	default:
		savedataListMenu->setPosition(400, 300);
		savedataListMenu->alignItemsHorizontallyWithPadding(45);
		this->addChild(savedataListMenu);
		break;
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

	ShopItemInfo itemInfo = { "bandaid", 1, 20 };
	ShopItemButton* item = ShopItemButton::create(itemInfo);
	item->setStoreVol();
	this->addChild(item);
	item->setPosition(400, 400);

	itemInfo = { "mirror", 1, 50 };
	item = ShopItemButton::create(itemInfo);
	item->setStoreVol();
	this->addChild(item);
	item->setPosition(400, 300);

	itemInfo = { "sword", 1, 200 };
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
	
	ButtonWithTextPicture buttonType = { "Button", "option", 0.5, this, nullptr };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	buttonType = { "Button", "exit_game_scene", 0.5, this, menu_selector(PaneLayer::exitGameScene) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));

	Sprite* buttonNormal = Sprite::createWithSpriteFrameName("Button_Close_Normal.png");
	Sprite* buttonSelected = Sprite::createWithSpriteFrameName("Button_Close_Selected.png");

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
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_2);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_2_1(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_3);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_2_2(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_4);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_3_1(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_5);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_3_2(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_6);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::selectGameScene_4_1(Ref * pSender)
{
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

	ShopItemInfo itemInfo = { "bandaid", 1, 20 };
	ShopItemButton* item = ShopItemButton::create(itemInfo);
	item->setBackpackVol();
	this->addChild(item);
	item->setPosition(400, 400);

	itemInfo = { "mirror", 1, 50 };
	item = ShopItemButton::create(itemInfo);
	item->setBackpackVol();
	this->addChild(item);
	item->setPosition(400, 300);

	itemInfo = { "sword", 1, 200 };
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

MenuItemSprite * PaneLayer::createCharacterSelectItem(
	const std::vector<PlayerData>& vec_characterInfoList,
	int i, const SEL_MenuHandler & selector, bool is_savedata)
{
	log("name = %s", vec_characterInfoList[i].str_characterName.c_str());
	log("%s", StringUtils::format("%s_wait.png", vec_characterInfoList[i].str_characterName.c_str()).c_str());
	Sprite *sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_wait.png", vec_characterInfoList[i].str_characterName.c_str()).c_str());
	auto animation = AnimationUtil::createAnimationWithSingleFrameName(StringUtils::format("%s_idle", vec_characterInfoList[i].str_characterName.c_str()).c_str(), 0.25f, -1);
	auto animate = Animate::create(animation);

	sprite->setPosition(100, 80);
	sprite->setScale(1 / 0.35);
	sprite->runAction(animate);

	std::string displayName = "";
	Label* firstLabel = NULL;
	Label* secondLabel = NULL;

	if (is_savedata)
	{
		displayName = vec_characterInfoList[i].str_playerName;
		firstLabel = Label::create(StringUtils::format("money:%d", vec_characterInfoList[i].i_money), "fonts/arial.ttf", 15);
		secondLabel = Label::create(StringUtils::format("level:%d", vec_characterInfoList[i].i_level), "fonts/arial.ttf", 15);
	}
	else
	{
		displayName = vec_characterInfoList[i].str_characterName;
		firstLabel = Label::create(StringUtils::format("HP:%d", vec_characterInfoList[i].i_HP), "fonts/arial.ttf", 15);
		secondLabel = Label::create(StringUtils::format("atk:%d", vec_characterInfoList[i].i_attack), "fonts/arial.ttf", 15);
	}

	auto nameLabel = Label::create(StringUtils::format("%s", displayName.c_str()), "fonts/arial.ttf", 20);
	nameLabel->setPosition(205, 360);
	nameLabel->setScale(1 / 0.35);
	nameLabel->setColor(Color3B::GRAY);

	firstLabel->setPosition(275, 220);
	firstLabel->setScale(1 / 0.35);
	firstLabel->setColor(Color3B::GRAY);

	secondLabel->setPosition(275, 130);
	secondLabel->setScale(1 / 0.35);
	secondLabel->setColor(Color3B::GRAY);

	ButtonOnlyImageType menuItemInfo = { "charater_select.png", "charater_select.png", 0.35, this, selector };
	MenuItemSprite* menuItem = MenuItemUtil::createMenuItemSpriteByPicture(menuItemInfo);

	menuItem->addChild(sprite);
	menuItem->addChild(nameLabel);
	menuItem->addChild(firstLabel);
	menuItem->addChild(secondLabel);

	return menuItem;
}

void PaneLayer::selectPlayer_1(Ref * pSender)
{
	log("selectPlayer_1");
	int dataNum = m_vecSavedataList.size();
	if (dataNum == 4)
	{
		return;
	}

	PlayerInfo::getInstance()->setPlayerData(m_vecCharacterList[0]);
	this->enterMainScene();
}

void PaneLayer::selectPlayer_2(Ref * pSender)
{
	log("selectPlayer_2");
	int dataNum = m_vecSavedataList.size();
	if (dataNum == 4)
	{
		return;
	}

	PlayerInfo::getInstance()->setPlayerData(m_vecCharacterList[1]);
	this->enterMainScene();
}

void PaneLayer::selectSavedata_1(Ref * pSender)
{
	log("selectSavedata_1");
	PlayerInfo::getInstance()->setPlayerData(m_vecSavedataList[0]);
	this->enterMainScene();
}

void PaneLayer::selectSavedata_2(Ref * pSender)
{
	log("selectSavedata_2");
	PlayerInfo::getInstance()->setPlayerData(m_vecSavedataList[1]);
	this->enterMainScene();
}

void PaneLayer::selectSavedata_3(Ref * pSender)
{
	log("selectSavedata_3");
	PlayerInfo::getInstance()->setPlayerData(m_vecSavedataList[2]);
	this->enterMainScene();
}

void PaneLayer::selectSavedata_4(Ref * pSender)
{
	log("selectSavedata_4");
	PlayerInfo::getInstance()->setPlayerData(m_vecSavedataList[3]);
	this->enterMainScene();
}

void PaneLayer::gameEnd(bool isSuccess)
{
	this->addChild(ShieldLayer::create());

	if (isSuccess)
	{
		auto myLabel = Label::createWithTTF("Game Clear", "fonts/Marker Felt.ttf", 50);
		this->addChild(myLabel);
		myLabel->setPosition(400, 300);
	}
	else
	{
		auto myLabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 50);
		this->addChild(myLabel);
		myLabel->setPosition(400, 300);
	}

	Menu* menu = Menu::create();
	ButtonWithTextPicture buttonType = { "Button", "exit_game_scene", 0.5, this, menu_selector(PaneLayer::exitGameScene) };
	menu->addChild(MenuItemUtil::createMenuItemSpriteByPicture(buttonType));
	this->addChild(menu);
	menu->setPosition(400, 200);
}
