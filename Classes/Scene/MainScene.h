#pragma once
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer;
class GameMenuLayer;
class NPCLayer;
class PaneLayer;
class Player;
class Portal;

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	static Scene* createSceneWithPlayer(Player *p_player);
	static MainScene* create(Player *p_player);
	virtual bool init(Player *p_player);

private:
	BackgroundLayer* m_pBackgroundLayer;
	TMXTiledMap* m_pMap;
	GameMenuLayer* m_pGameMenuLayer;
	NPCLayer* m_pNPCLayer;
	PaneLayer* m_pPaneLayer;

};

#endif // !__MAIN_SCENE_H__
