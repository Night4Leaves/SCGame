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

void PaneLayer::savePlayerData(PlayerData & playerData)
{
	m_sctPlayerData = playerData;
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
	case en_paneMsg_selectGameScene:
		this->selectGameScene();
		break;
	case en_paneMsg_openStore:
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

void PaneLayer::changeGameScene(Ref * pSender)
{
	GameScene* gameScene = GameScene::create();
	gameScene->setScene(Scene_1, m_sctPlayerData);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::enterMainScene(PlayerData & playerData)
{
	MainScene* mainScene = MainScene::create(playerData);
	Director::getInstance()->replaceScene(mainScene);
}

void PaneLayer::changeMainScene(Ref * pSender)
{
	this->enterMainScene(m_sctPlayerData);
}

void PaneLayer::menuCloseCallback(Ref * pSender)
{
	log("ok");
	this->removeAllChildren();
	m_isOpen = false;
}

void PaneLayer::createNewData()
{
}

void PaneLayer::selectCharacter()
{
	log("PaneLayer::selectCharacter");

	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	JsonUtil::getInstance()->readPlayerInfo(m_vecCharacterList);

	auto menu = Menu::create();

	auto menuItem = this->createCharacterSelectItem(m_vecCharacterList, 0, menu_selector(PaneLayer::selectPlayer_1), false);
	menu->addChild(menuItem);

	menuItem = this->createCharacterSelectItem(m_vecCharacterList, 1, menu_selector(PaneLayer::selectPlayer_2), false);
	menu->addChild(menuItem);


	menu->setPosition(400, 300);
	menu->alignItemsHorizontallyWithPadding(50);
	this->addChild(menu);

	//测试按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PaneLayer::menuCloseCallback, this));

	Menu* closeMenu = Menu::create(closeItem, NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(400, 300);
}

void PaneLayer::loadFile()
{
	log("PaneLayer::loadFile");

	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	auto savedataNum = m_vecSavedataList.size();
	log("save data num is %d", m_vecSavedataList.size());

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PaneLayer::menuCloseCallback, this));

	Menu* menu = Menu::create(closeItem, NULL);
	this->addChild(menu);
	menu->setPosition(200, 450);

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
		savedataListMenu->setPosition(400, 280);
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

	log("PaneLayer::openStore");
}

void PaneLayer::startPause()
{
	log("PaneLayer::startPause");
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

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PaneLayer::menuCloseCallback, this));

	auto menu = Menu::create(closeItem, NULL);
	this->addChild(menu);
	menu->setPosition(400, 500);

	Sprite* normalButton = Sprite::create("background/game_scene_01_2048x1536.png");
	Sprite* selectButton = Sprite::create("background/game_scene_01_2048x1536.png");
	MenuItemSprite* aButtonSprite = MenuItemSprite::create(normalButton, selectButton, this, menu_selector(PaneLayer::changeGameScene));
	aButtonSprite->setScale(0.1);
	Sprite* normalButton_1 = Sprite::create("background/game_scene_02_2048x1536.png");
	Sprite* selectButton_1 = Sprite::create("background/game_scene_02_2048x1536.png");
	MenuItemSprite* bButtonSprite = MenuItemSprite::create(normalButton_1, selectButton_1, nullptr, nullptr);
	bButtonSprite->setScale(0.1);
	Sprite* normalButton_2 = Sprite::create("background/initial_scene_01_2048x1536.png");
	Sprite* selectButton_2 = Sprite::create("background/initial_scene_01_2048x1536.png");
	MenuItemSprite* cButtonSprite = MenuItemSprite::create(normalButton_2, selectButton_2, nullptr, nullptr);
	cButtonSprite->setScale(0.1);
	Sprite* normalButton_3 = Sprite::create("background/main_scene_01_2048x1536.png");
	Sprite* selectButton_3 = Sprite::create("background/main_scene_01_2048x1536.png");
	MenuItemSprite* dButtonSprite = MenuItemSprite::create(normalButton_3, selectButton_3, nullptr, nullptr);
	dButtonSprite->setScale(0.1);

	Menu* menu_1 = Menu::create(aButtonSprite, bButtonSprite, NULL);
	Menu* menu_2 = Menu::create(cButtonSprite, dButtonSprite, NULL);
	if (menu_1 == nullptr)
	{
		log("setInitialMenu set failed!");
		return;
	}
	else
	{
		this->addChild(menu_1);

		//设置菜单位置
		Size winSize = Director::getInstance()->getWinSize();
		menu_1->setPosition(winSize.width * 0.5, winSize.height * 0.5 + 90);
		menu_1->alignItemsHorizontallyWithPadding(20);

		this->addChild(menu_2);

		//设置菜单位置
		menu_2->setPosition(winSize.width * 0.5, winSize.height * 0.5 - 90);
		menu_2->alignItemsHorizontallyWithPadding(20);

	}
}

void PaneLayer::openBackpack()
{
	auto test = Sprite::createWithSpriteFrameName("backpack.png");
	this->addChild(test);
	test->setPosition(400, 300);
	test->setScale(0.5);
}

MenuItemSprite * PaneLayer::createCharacterSelectItem(const std::vector<PlayerData>& vec_characterInfoList, int i, const SEL_MenuHandler & selector, bool is_savedata)
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

	this->enterMainScene(m_vecCharacterList[0]);
}

void PaneLayer::selectPlayer_2(Ref * pSender)
{
	log("selectPlayer_2");
	int dataNum = m_vecSavedataList.size();
	if (dataNum == 4)
	{
		return;
	}

	this->enterMainScene(m_vecCharacterList[1]);
}

void PaneLayer::selectSavedata_1(Ref * pSender)
{
	log("selectSavedata_1");
	this->enterMainScene(m_vecSavedataList[0]);
}

void PaneLayer::selectSavedata_2(Ref * pSender)
{
	log("selectSavedata_2");
	this->enterMainScene(m_vecSavedataList[1]);
}

void PaneLayer::selectSavedata_3(Ref * pSender)
{
	log("selectSavedata_3");
	this->enterMainScene(m_vecSavedataList[2]);
}

void PaneLayer::selectSavedata_4(Ref * pSender)
{
	log("selectSavedata_4");
	this->enterMainScene(m_vecSavedataList[3]);
}
