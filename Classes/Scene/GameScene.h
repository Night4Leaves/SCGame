#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMenuLayer;
class PaneLayer;

enum SceneType
{
	Scene_1,
	Scene_2,
	Scene_3,
	Scene_4,
	Scene_5,
	Scene_6,
	Scene_7
};

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	static Scene* createScene();
	CREATE_FUNC(GameScene);
	virtual bool init();

	void setScene(SceneType sign);

protected:
	TMXTiledMap* m_pMap;
	GameMenuLayer* m_pGameMenuLayer;
	PaneLayer* m_pPaneLayer;
};

#endif // !__GAME_SCENE_H__
