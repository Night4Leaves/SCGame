#pragma once
#ifndef __GAME_MENU_LAYER_H__
#define __GAME_MENU_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMenuLayer : public Layer
{
public:
	GameMenuLayer();
	virtual ~GameMenuLayer();

	CREATE_FUNC(GameMenuLayer);
	virtual bool init();

	//设置初始界面的菜单选项
	void setInitialMenu();

	//设置主界面的菜单选项
	void setMainMenu();

private:
	//初始界面功能
	void startGame(CCObject *sender);
	void continueGame(CCObject *sender);
	void openOptionWin(CCObject *sender);
	void exitGame(CCObject *sender);

	//主界面功能
	void selectGameScene(CCObject *sender);
	void openBackpack(CCObject *sender);
	void openSkillList(CCObject *sender);
	void openOption(CCObject *sender);
};

#endif // !1
