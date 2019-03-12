#pragma once
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class BackgroundLayer;
class GameMenuLayer;
class NPCLayer;
class PaneLayer;
class Portal;
class ScoreCountLayer;
class HeartCount;

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	static MainScene* create(PlayerData &playerData);
	virtual bool init(PlayerData &player);

private:
	BackgroundLayer* m_pBackgroundLayer;
	TMXTiledMap* m_pMap;
	NPCLayer* m_pNPCLayer;
	GameMenuLayer* m_pGameMenuLayer;
	PaneLayer* m_pPaneLayer;
	ScoreCountLayer* m_pScoreCountLayer;
	HeartCount* m_pHeartCount;
};

#endif // !__MAIN_SCENE_H__
