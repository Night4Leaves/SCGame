#include "PaneLayer.h"
#include "Scene/GameScene.h"
#include "Util/MenuItemUtil.h"

PaneLayer::PaneLayer()
{
}

PaneLayer::~PaneLayer()
{
}

bool PaneLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		m_bIsEffective = false;
		m_pMap = nullptr;

		LayerColor* color = LayerColor::create(Color4B::BLACK, 800, 600);
		this->addChild(color);
		color->setOpacity(0);
		a_color = color;

		Sprite* normalButton = Sprite::create("background/game_scene_01_2048x1536.png");
		Sprite* selectButton = Sprite::create("background/game_scene_01_2048x1536.png");
		MenuItemSprite* aButtonSprite = MenuItemSprite::create(normalButton, selectButton, this, menu_selector(PaneLayer::startGame));
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
			return false;
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

		menu_1->setOpacity(0);
		menu_2->setOpacity(0);

		a_1 = menu_1;
		a_2 = menu_2;

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
	m_bIsEffective = !m_bIsEffective;
	if (m_bIsEffective)
	{
		a_color->setOpacity(200);
		a_1->setOpacity(255);
		a_2->setOpacity(255);
	}
	else
	{
		a_color->setOpacity(0);
		a_1->setOpacity(0);
		a_2->setOpacity(0);
	}
	
}

void PaneLayer::startGame(Ref * pSender)
{
	Scene* gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}
