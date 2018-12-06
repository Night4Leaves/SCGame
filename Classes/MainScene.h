#pragma once
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer;
class GameMenuLayer;
class NPCLayer;

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	static Scene* createScene();
	CREATE_FUNC(MainScene);
	virtual bool init();

private:
	BackgroundLayer* m_pBackgroundLayer;
	GameMenuLayer* m_pGameMenuLayer;
	NPCLayer* m_pNPCLayer;
};

#endif // !__MAIN_SCENE_H__
