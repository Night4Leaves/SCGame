#include "PaneLayer.h"
#include "Scene/GameScene.h"
#include "Scene/MainScene.h"
#include "Util/MenuItemUtil.h"
#include "Util/AnimationUtil.h"
#include "Entity/Player.h"
#include "Json/json.h"
#include "CustomizeEnum.h"
#include "ShieldLayer.h"

PaneLayer::PaneLayer()
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

void PaneLayer::savePlayer(Player * player)
{
	m_pPlayer = player;
}


void PaneLayer::changeGameScene(Ref * pSender)
{
	GameScene* gameScene = GameScene::createScene();
	gameScene->setScene(Scene_1, m_pPlayer);
	Director::getInstance()->replaceScene(gameScene);
}

void PaneLayer::changeMainScene()
{
	log("PaneLayer::changeMainScene");
}

void PaneLayer::menuCloseCallback(Ref * pSender)
{
	log("ok");
	this->removeAllChildren();
}

int PaneLayer::checkSaveData()
{
	Json::Reader reader;
	Json::Value root;

	std::string saveData = FileUtils::getInstance()->getStringFromFile("json/savedata.json");

	if (reader.parse(saveData, root, false) == true)
	{
		log("save data num is %d", root.size());
		return root.size();
	}
	else
	{
		log("can't open save data file");
		return -1;
	}
	
}

void PaneLayer::createNewData()
{
}

MenuItemSprite * PaneLayer::createPlayerSelectItem(const std::vector<PlayerInfomation> &vec_playerList, int i, const SEL_MenuHandler &selector)
{
	log("name = %s", vec_playerList[i].str_name.c_str());
	log("%s", StringUtils::format("%s_wait.png", vec_playerList[i].str_name.c_str()).c_str());
	Sprite *sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_wait.png", vec_playerList[i].str_name.c_str()).c_str());
	auto animation = AnimationUtil::createAnimationWithSingleFrameName(StringUtils::format("%s_idle", vec_playerList[i].str_name.c_str()).c_str(), 0.25f, -1);
	auto animate = Animate::create(animation);

	sprite->setScale(1 / 0.3);
	sprite->setPosition(100, 80);
	sprite->runAction(animate);

	const char* cs_playerName = vec_playerList[i].str_name.c_str();
	auto nameLabel = Label::create(StringUtils::format("%s", cs_playerName), "fonts/arial.ttf", 20);
	nameLabel->setPosition(205, 360);
	nameLabel->setScale(1 / 0.3);
	nameLabel->setColor(Color3B::GRAY);

	auto atkLabel = Label::create(StringUtils::format("Atk:%d", vec_playerList[i].i_attack), "fonts/arial.ttf", 15);
	atkLabel->setPosition(275, 130);
	atkLabel->setScale(1 / 0.3);
	atkLabel->setColor(Color3B::GRAY);

	auto hpLabel = Label::create(StringUtils::format("HP:%d", vec_playerList[i].i_hp), "fonts/arial.ttf", 15);
	hpLabel->setPosition(275, 220);
	hpLabel->setScale(1 / 0.3);
	hpLabel->setColor(Color3B::GRAY);

	ButtonOnlyImageType menuItemInfo = { "charater_select.png", "charater_select.png", 0.3, this, selector };
	MenuItemSprite* menuItem = MenuItemUtil::createMenuItemSpriteByPicture(menuItemInfo);

	menuItem->addChild(sprite);
	menuItem->addChild(nameLabel);
	menuItem->addChild(atkLabel);
	menuItem->addChild(hpLabel);

	return menuItem;
}

void PaneLayer::selectPlayer_1(Ref * pSender)
{
	log("selectPlayer_1");
	int dataNum = checkSaveData();
	if (dataNum == 4)
	{
		return;
	}
	Player* player = Player::create("player_01");
	Scene* mainScene = MainScene::create(player);
	Director::getInstance()->replaceScene(mainScene);
}

void PaneLayer::selectPlayer_2(Ref * pSender)
{
	log("selectPlayer_2");
	int dataNum = checkSaveData();
	if (dataNum == 4)
	{
		return;
	}
	Player* player = Player::create("player_02");
	Scene* mainScene = MainScene::create(player);
	Director::getInstance()->replaceScene(mainScene);
}

void PaneLayer::selectCharacter()
{
	log("PaneLayer::selectCharacter");

	this->addChild(ShieldLayer::create());

	auto backColor = LayerColor::create(Color4B::BLACK);
	this->addChild(backColor);

	std::vector<PlayerInfomation> vec_playerList;
	this->readPlayerJson(vec_playerList);

	auto menu = Menu::create();

	auto menuItem = this->createPlayerSelectItem(vec_playerList, 0, menu_selector(PaneLayer::selectPlayer_1));
	menu->addChild(menuItem);

	menuItem = this->createPlayerSelectItem(vec_playerList, 1, menu_selector(PaneLayer::selectPlayer_2));
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

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PaneLayer::menuCloseCallback, this));

	auto menu = Menu::create(closeItem, NULL);
	this->addChild(menu);
	menu->setPosition(400, 300);

}

void PaneLayer::openStore()
{
	log("PaneLayer::openStore");
}

void PaneLayer::startPause()
{
	log("PaneLayer::startPause");
}

void PaneLayer::selectGameScene()
{
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

void PaneLayer::readPlayerJson(std::vector<PlayerInfomation>& vec_playerInfoList)
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile("json/player_info.json");

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			PlayerInfomation player = { root[i]["name"].asCString(),
										root[i]["hp"].asInt() ,
										root[i]["attack"].asInt() };

			log("name = %s", player.str_name.c_str());
			log("hp = %d", player.i_hp);
			log("attack = %d", player.i_attack);

			vec_playerInfoList.push_back(player);
		}
	}

}
