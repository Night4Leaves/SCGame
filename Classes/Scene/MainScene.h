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

	static Scene* create(Player *player);
	virtual bool init(Player *player);
	
private:
	BackgroundLayer* m_pBackgroundLayer;
	TMXTiledMap* m_pMap;
	NPCLayer* m_pNPCLayer;
	Player* m_pPlayer;
	GameMenuLayer* m_pGameMenuLayer;
	PaneLayer* m_pPaneLayer;
};

#endif // !__MAIN_SCENE_H__
