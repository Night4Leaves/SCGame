#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "Util/JsonUtil.h"
#include "cocos2d.h"

USING_NS_CC;

class Player;
class PlayerController;
class FlyingObject;
class Monster;
class Boss;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);
	virtual bool init();

	void addAttackFlyingObject(Ref* pSender);

	/**
	 *	设置第一关场景
	 *	@playerData	玩家数据结构体
	 */
	void setGameScene_1_1(PlayerData &playerData);

private:
	TMXTiledMap* m_pMap;	//地图
	Player* m_pPlayer;	//玩家
	PlayerData m_sctPlayerData;	//玩家数据
	PlayerController* m_pPlayerController;	//玩家控制器
	Vector<FlyingObject*> vector_pAttackFlyingObject;	//飞行物
	Vector<Monster*> vector_pMonster;	//怪物
	Boss* m_pBoss;	//Boss

	int m_iFlyingObjectFlag;	//飞行物计数器

};

#endif // !__GAME_LAYER_H__
