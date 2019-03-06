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
	void startGame(Ref* sender);
	void continueGame(Ref* sender);
	void openOptionWin(Ref* sender);
	void exitGame(Ref* sender);

	//主界面功能
	void openBackpack(Ref* sender);
	void openSkillList(Ref* sender);
	void openOption(Ref* sender);
};

#endif // !1
