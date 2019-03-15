#pragma once
#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer;
class GameMenuLayer;
class PaneLayer;

class InitialScene : public Scene
{
public:
	InitialScene();
	virtual ~InitialScene();

	static Scene* createScene();
	CREATE_FUNC(InitialScene);
	virtual bool init();

private:
	BackgroundLayer* m_pBackgroundLayer;	//背景层
	GameMenuLayer* m_pGameMenuLayer;	//游戏菜单层
	PaneLayer* m_pPaneLayer;	//显示层
};

#endif // !__INITIAL_SCENE_H__
