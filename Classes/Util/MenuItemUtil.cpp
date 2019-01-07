#include "MenuItemUtil.h"

Sprite * MenuItemUtil::createMenuButton(const char * picAddress, const char * text, TTFConfig fontConfig, Color3B color)
{
	//创建按钮背景
	Sprite* buttonBg = Sprite::createWithSpriteFrameName(picAddress);
	if (buttonBg == nullptr)
	{
		log("MenuItemUtil::createMenuButton : Sprite* buttonBg create failed!");
		return false;
	}
	//设置背景透明度
	buttonBg->setOpacity(220);

	//创建按钮文字
	Label* buttonText = Label::createWithTTF(fontConfig, text);
	//设置文字颜色
	buttonText->setColor(color);

	//组合按钮
	buttonBg->addChild(buttonText);

	//获得按钮背景大小
	Size buttonSize = buttonBg->getContentSize();
	//设置按钮文字位置
	buttonText->setPosition(buttonSize.width * 0.5, buttonSize.height * 0.5 + 5);

	return buttonBg;
}

MenuItemSprite * MenuItemUtil::createMenuItemSprite(const ButtonWithFontType & buttontype)
{
	//普通状态背景
	std::string normalPic = StringUtils::format("%s_Normal.png", buttontype.picName);
	//按下状态背景
	std::string selectPic = StringUtils::format("%s_Selected.png", buttontype.picName);
	//按钮文字
	const char* text = buttontype.text;
	//字体设置
	TTFConfig fontConfig = buttontype.fontConfig;

	//创建普通状态和按下状态按钮精灵对象
	Sprite* normalButton = MenuItemUtil::createMenuButton(normalPic.c_str(), text, fontConfig, Color3B::WHITE);
	Sprite* selectButton = MenuItemUtil::createMenuButton(selectPic.c_str(), text, fontConfig, Color3B::BLACK);

	//创建菜单选项精灵对象
	MenuItemSprite* buttonSprite = MenuItemSprite::create(normalButton, selectButton, buttontype.target, buttontype.selector);
	if (buttonSprite == nullptr)
	{
		log("MenuItemSprite create failed!");
		return false;
	}

	//菜单选项缩放
	buttonSprite->setScale(buttontype.scale);

	return buttonSprite;
}

MenuItemSprite * MenuItemUtil::createMenuItemSpriteByPicture(const ButtonOnlyImageType & buttontype)
{
	//创建普通状态和选中状态按钮精灵对象
	Sprite* normalButton = Sprite::createWithSpriteFrameName(buttontype.normalPicName);
	Sprite* selectButton = Sprite::createWithSpriteFrameName(buttontype.selectedPicName);

	//创建菜单选项精灵对象
	MenuItemSprite* buttonSprite = MenuItemSprite::create(normalButton, selectButton, buttontype.target, buttontype.selector);
	if (buttonSprite == nullptr)
	{
		log("MenuItemSprite create failed!");
		return false;
	}

	//菜单选项缩放
	buttonSprite->setScale(buttontype.scale);

	return buttonSprite;
}

MenuItemSprite * MenuItemUtil::createMenuItemSpriteByPicture(const ButtonWithTextPicture & buttontype)
{
	//普通状态和按下状态背景
	std::string normalBgPic = StringUtils::format("%s_Normal.png", buttontype.picName);
	std::string selectBgPic = StringUtils::format("%s_Selected.png", buttontype.picName);

	//普通状态和按下状态文字
	std::string normalTextPic = StringUtils::format("%s_normal.png", buttontype.textPicName);
	std::string selectTextPic = StringUtils::format("%s_selected.png", buttontype.textPicName);

	//创建普通状态和选中状态按钮精灵对象
	Sprite* normalButton = Sprite::createWithSpriteFrameName(normalBgPic.c_str());
	Sprite* selectButton = Sprite::createWithSpriteFrameName(selectBgPic.c_str());

	//创建普通状态和选中状态文字精灵
	Sprite* normalTextSprite = Sprite::createWithSpriteFrameName(normalTextPic.c_str());
	Sprite* selectTextSprite = Sprite::createWithSpriteFrameName(selectTextPic.c_str());

	//背景图与文字图拼合
	normalButton->addChild(normalTextSprite);
	selectButton->addChild(selectTextSprite);
	
	//获取背景图大小
	Size buttonSize = normalButton->getContentSize();

	//根据背景图大小设置文字图位置
	normalTextSprite->setPosition(buttonSize.width * 0.5, buttonSize.height * 0.5 + 5);
	selectTextSprite->setPosition(buttonSize.width * 0.5, buttonSize.height * 0.5 + 5);

	//文字缩放，临时方式
	normalTextSprite->setScale(1.5f);
	selectTextSprite->setScale(1.5f);

	//创建菜单选项精灵对象
	MenuItemSprite* buttonSprite = MenuItemSprite::create(normalButton, selectButton, buttontype.target, buttontype.selector);
	if (buttonSprite == nullptr)
	{
		log("MenuItemSprite create failed!");
		return false;
	}

	//菜单选项缩放
	buttonSprite->setScale(buttontype.scale);

	return buttonSprite;
}
