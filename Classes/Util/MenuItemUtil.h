#pragma once
#ifndef __MENU_ITEM_UTIL_H__
#define __MENU_ITEM_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

/**
 *	��ť������Ϣ
 *	@picName ��ť����ͼ
 *	@text	��ť��ʾ����
 *	@fontConfig	��ť��������
 *	@scale	���ű���
 *	@target	��ť����������(����)
 *	@selector	�ص�����
 */
struct ButtonWithFontType
{
	const char* picName;
	const char* text;
	TTFConfig fontConfig;
	float scale = 1;
	Ref* target = nullptr;
	SEL_MenuHandler selector = nullptr;
};

/**
 *	��ť������Ϣ
 *	@normalPicName ����״̬��ťͼ
 *	@selectedPicName	ѡ��״̬��ťͼ
 *	@target	��ť����������(����)
 *	@selector	�ص�����
 */
struct ButtonOnlyImageType
{
	const char* normalPicName;
	const char* selectedPicName;
	float scale = 1;
	Ref* target = nullptr;
	SEL_MenuHandler selector = nullptr;
};

class MenuItemUtil
{
public:
	/**
	 *	�����˵���ť
	 *	@picAddress	��ť����ͼƬ
	 *	@text	��ť����
	 *	@fontConfig	��ť��������
	 *	@color	��ť������ɫ
	 */
	static Sprite* createMenuButton(const char* picAddress, const char* text, TTFConfig fontConfig, Color3B color = Color3B::WHITE);

	//���������ֵĲ˵�ѡ�����(��ͨ:����, ����:��ɫ)
	static MenuItemSprite* createMenuItemSprite(const ButtonWithFontType& buttontype);

	//����û�����ֵĲ˵�ѡ�����
	static MenuItemSprite* createMenuItemSpriteByPicture(const ButtonOnlyImageType& buttontype);
};

#endif // !__MENU_ITEM_UTIL_H__
