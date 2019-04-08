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

	/**
	 *	设置游戏场景
	 *	@sign	关卡
	 *	@player	玩家数据结构体
	 */
	void setScene(SceneType sign);

	//玩家损失血量
	void playerReduceHeart(Ref* pSender);
	//玩家恢复血量
	void playerRecoverHeart(Ref* pSender);

protected:
	BackgroundLayer* m_pBackgroundLayer;	//背景层
	GameLayer* m_pGameLayer;	//游戏层
	GameMenuLayer* m_pGameMenuLayer;	//游戏菜单层
	PaneLayer* m_pPaneLayer;	//显示层
	ScoreCountLayer* m_pScoreCountLayer;	//记分器层
	HeartCount* m_pHeartCount;	//玩家血量层
};

#endif // !__GAME_SCENE_H__
