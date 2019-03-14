#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class BackgroundLayer;
class GameLayer;
class GameMenuLayer;
class PaneLayer;
class ScoreCountLayer;
class Player;
class HeartCount;

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

	static GameScene* createScene();
	CREATE_FUNC(GameScene);
	virtual bool init();

	void setScene(SceneType sign, PlayerData &player);

	void updateScore(Ref* pSender);
	void playerReduceHeart(Ref* pSender);

protected:
	BackgroundLayer* m_pBackgroundLayer;
	GameLayer* m_pGameLayer;
	GameMenuLayer* m_pGameMenuLayer;
	PaneLayer* m_pPaneLayer;
	ScoreCountLayer* m_pScoreCountLayer;
	HeartCount* m_pHeartCount;
};

#endif // !__GAME_SCENE_H__
