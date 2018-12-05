#pragma once
#ifndef __MENU_ITEM_UTIL_H__
#define __MENU_ITEM_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

struct ButtonType {
	const char* picName;
	const char* text;
	TTFConfig fontConfig;
	Ref* target = nullptr;
	SEL_MenuHandler selector = nullptr;
};

class MenuItemUtil
{
public:
	//�����˵���ť
	static Sprite* createMenuButton(std::string picAddress, const char* text, TTFConfig fontConfig, Color3B color = Color3B::WHITE);

	//�����˵�ѡ�����(��ͨ:����, ����:��ɫ)
	static MenuItemSprite* createMenuItemSprite(const ButtonType& buttontype);
};

#endif // !__MENU_ITEM_UTIL_H__
