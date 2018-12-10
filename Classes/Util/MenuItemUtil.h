#pragma once
#ifndef __MENU_ITEM_UTIL_H__
#define __MENU_ITEM_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

/**
 *	按钮设置信息
 *	@picName 按钮背景图
 *	@text	按钮显示文字
 *	@fontConfig	按钮文字字体
 *	@target	按钮所在上下文(存疑)
 *	@selector	回调函数
 */
struct ButtonType
{
	const char* picName;
	const char* text;
	TTFConfig fontConfig;
	Ref* target = nullptr;
	SEL_MenuHandler selector = nullptr;
};

class MenuItemUtil
{
public:
	/**
	 *	创建菜单按钮
	 *	@picAddress	按钮背景图片
	 *	@text	按钮文字
	 *	@fontConfig	按钮文字字体
	 *	@color	按钮文字颜色
	 */
	static Sprite* createMenuButton(const char* picAddress, const char* text, TTFConfig fontConfig, Color3B color = Color3B::WHITE);

	//创建菜单选项对象(普通:白字, 按下:黑色)
	static MenuItemSprite* createMenuItemSprite(const ButtonType& buttontype);
};

#endif // !__MENU_ITEM_UTIL_H__
