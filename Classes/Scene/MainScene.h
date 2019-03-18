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

	//根据玩家数据创建主场景
	static MainScene* create(PlayerData &playerData);
	virtual bool init(PlayerData &player);

private:
	BackgroundLayer* m_pBackgroundLayer;	//背景层
	TMXTiledMap* m_pMap;	//地图
	NPCLayer* m_pNPCLayer;	//NPC层
	GameMenuLayer* m_pGameMenuLayer;	//游戏菜单层
	PaneLayer* m_pPaneLayer;	//显示层
	ScoreCountLayer* m_pScoreCountLayer;	//记分器层
	HeartCount* m_pHeartCount;	//玩家血量层
};

#endif // !__MAIN_SCENE_H__
