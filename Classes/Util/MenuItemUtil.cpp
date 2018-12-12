#include "MenuItemUtil.h"

Sprite * MenuItemUtil::createMenuButton(const char * picAddress, const char * text, TTFConfig fontConfig, Color3B color)
{
	//������ť����
	Sprite* buttonBg = Sprite::createWithSpriteFrameName(picAddress);
	if (buttonBg == nullptr)
	{
		log("MenuItemUtil::createMenuButton : Sprite* buttonBg create failed!");
		return false;
	}
	//���ñ���͸����
	buttonBg->setOpacity(220);

	//������ť����
	Label* buttonText = Label::createWithTTF(fontConfig, text);
	//����������ɫ
	buttonText->setColor(color);

	//��ϰ�ť
	buttonBg->addChild(buttonText);

	//��ð�ť������С
	Size buttonSize = buttonBg->getContentSize();
	//���ð�ť����λ��
	buttonText->setPosition(buttonSize.width * 0.5, buttonSize.height * 0.5 + 5);

	return buttonBg;
}

MenuItemSprite * MenuItemUtil::createMenuItemSprite(const ButtonWithFontType & buttontype)
{
	//��ͨ״̬����
	std::string normalPic = StringUtils::format("%s_Normal.png", buttontype.picName);
	//����״̬����
	std::string selectPic = StringUtils::format("%s_Selected.png", buttontype.picName);
	//��ť����
	const char* text = buttontype.text;
	//��������
	TTFConfig fontConfig = buttontype.fontConfig;

	//������ͨ״̬�Ͱ���״̬��ť�������
	Sprite* normalButton = MenuItemUtil::createMenuButton(normalPic.c_str(), text, fontConfig, Color3B::WHITE);
	Sprite* selectButton = MenuItemUtil::createMenuButton(selectPic.c_str(), text, fontConfig, Color3B::BLACK);

	//�����˵�ѡ������
	MenuItemSprite* buttonSprite = MenuItemSprite::create(normalButton, selectButton, buttontype.target, buttontype.selector);
	if (buttonSprite == nullptr)
	{
		log("MenuItemSprite create failed!");
		return false;
	}

	//�˵�ѡ������
	buttonSprite->setScale(buttontype.scale);

	return buttonSprite;
}

MenuItemSprite * MenuItemUtil::createMenuItemSpriteByPicture(const ButtonOnlyImageType & buttontype)
{
	//������ͨ״̬��ѡ��״̬��ť�������
	Sprite* normalButton = Sprite::createWithSpriteFrameName(buttontype.normalPicName);
	Sprite* selectButton = Sprite::createWithSpriteFrameName(buttontype.selectedPicName);

	//�����˵�ѡ������
	MenuItemSprite* buttonSprite = MenuItemSprite::create(normalButton, selectButton, buttontype.target, buttontype.selector);
	if (buttonSprite == nullptr)
	{
		log("MenuItemSprite create failed!");
		return false;
	}

	//�˵�ѡ������
	buttonSprite->setScale(buttontype.scale);

	return buttonSprite;
}
