#include "CharacterSelector.h"
#include "PlayerInfo.h"
#include "Util/AnimationUtil.h"
#include "Util/MenuItemUtil.h"
#include "Util/JsonUtil.h"
#include "Scene/MainScene.h"
#include "Layer/ShieldLayer.h"

CharacterSelector * CharacterSelector::create(PlayerData playerData)
{
	CharacterSelector *pRet = new(std::nothrow) CharacterSelector();
	if (pRet && pRet->init(playerData))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void CharacterSelector::setCreateNewDataVol()
{
	Sprite *sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_wait.png", m_sctPlayerData.str_characterName.c_str()).c_str());
	auto animation = AnimationUtil::createAnimationWithSingleFrameName(StringUtils::format("%s_idle", m_sctPlayerData.str_characterName.c_str()).c_str(), 0.25f, -1);
	auto animate = Animate::create(animation);

	sprite->setPosition(100, 80);
	sprite->setScale(1 / 0.35);
	sprite->runAction(animate);

	Label* nameLabel = Label::create(StringUtils::format("%s", m_sctPlayerData.str_characterName.c_str()), "fonts/arial.ttf", 20);
	Label* firstLabel = Label::create(StringUtils::format("HP:%d", m_sctPlayerData.i_HP), "fonts/arial.ttf", 15);
	Label* secondLabel = Label::create(StringUtils::format("atk:%d", m_sctPlayerData.i_attack), "fonts/arial.ttf", 15);
	
	nameLabel->setPosition(205, 360);
	nameLabel->setScale(1 / 0.35);
	nameLabel->setColor(Color3B::GRAY);

	firstLabel->setPosition(275, 220);
	firstLabel->setScale(1 / 0.35);
	firstLabel->setColor(Color3B::GRAY);

	secondLabel->setPosition(275, 130);
	secondLabel->setScale(1 / 0.35);
	secondLabel->setColor(Color3B::GRAY);

	ButtonOnlyImageType menuItemInfo = { "charater_select.png", "charater_select.png", 0.35, this, menu_selector(CharacterSelector::startGame) };
	MenuItemSprite* menuItem = MenuItemUtil::createMenuItemSpriteByPicture(menuItemInfo);

	menuItem->addChild(sprite);
	menuItem->addChild(nameLabel);
	menuItem->addChild(firstLabel);
	menuItem->addChild(secondLabel);

	Menu* menu = Menu::create(menuItem, nullptr);
	this->addChild(menu);
}

void CharacterSelector::setLoadSaveDataVol()
{
	Sprite *sprite = Sprite::createWithSpriteFrameName(StringUtils::format("%s_wait.png", m_sctPlayerData.str_characterName.c_str()).c_str());
	auto animation = AnimationUtil::createAnimationWithSingleFrameName(StringUtils::format("%s_idle", m_sctPlayerData.str_characterName.c_str()).c_str(), 0.25f, -1);
	auto animate = Animate::create(animation);

	sprite->setPosition(100, 80);
	sprite->setScale(1 / 0.35);
	sprite->runAction(animate);

	Label* nameLabel = Label::create(StringUtils::format("%d", m_sctPlayerData.i_dataNumber), "fonts/arial.ttf", 20);
	Label* firstLabel = Label::create(StringUtils::format("money:%d", m_sctPlayerData.i_money), "fonts/arial.ttf", 15);
	Label* secondLabel = Label::create(StringUtils::format("level:%d", m_sctPlayerData.i_level), "fonts/arial.ttf", 15);

	nameLabel->setPosition(205, 360);
	nameLabel->setScale(1 / 0.35);
	nameLabel->setColor(Color3B::GRAY);

	firstLabel->setPosition(275, 220);
	firstLabel->setScale(1 / 0.35);
	firstLabel->setColor(Color3B::GRAY);

	secondLabel->setPosition(275, 130);
	secondLabel->setScale(1 / 0.35);
	secondLabel->setColor(Color3B::GRAY);

	ButtonOnlyImageType menuItemInfo = { "charater_select.png", "charater_select.png", 0.35, this, menu_selector(CharacterSelector::startGame) };
	MenuItemSprite* menuItem = MenuItemUtil::createMenuItemSpriteByPicture(menuItemInfo);

	menuItem->addChild(sprite);
	menuItem->addChild(nameLabel);
	menuItem->addChild(firstLabel);
	menuItem->addChild(secondLabel);

	Menu* menu = Menu::create(menuItem, nullptr);
	this->addChild(menu);

	ButtonOnlyImageType deleteItemInfo = { "Button_Delete.png", "Button_Delete.png", 0.15, this, menu_selector(CharacterSelector::deleteSavedata) };
	MenuItemSprite* deleteItem = MenuItemUtil::createMenuItemSpriteByPicture(deleteItemInfo);
	Menu* deleteMenu = Menu::create(deleteItem, nullptr);
	this->addChild(deleteMenu);
	deleteMenu->setPosition(400, 240);
}

void CharacterSelector::startGame(Ref * pSender)
{
	PlayerInfo::getInstance()->setPlayerData(m_sctPlayerData);
	MainScene* mainScene = MainScene::create();
	Director::getInstance()->replaceScene(mainScene);
}

void CharacterSelector::deleteSavedata(Ref * pSender)
{
	log("delete savedata");
	JsonUtil::getInstance()->deleteSavedata(m_sctPlayerData.i_dataNumber);
	this->removeAllChildren();
}

CharacterSelector::CharacterSelector()
{
}

CharacterSelector::~CharacterSelector()
{
}

bool CharacterSelector::init(PlayerData playerData)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_sctPlayerData = playerData;

		return true;
	} while (0);

	return false;
}
