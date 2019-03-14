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

	void setGameScene_1_1(PlayerData &playerData);

private:
	TMXTiledMap* m_pMap;
	Player* m_pPlayer;
	PlayerData m_sctPlayerData;
	PlayerController* m_pPlayerController;
	Vector<FlyingObject*> vector_pAttackFlyingObject;
	Vector<Monster*> vector_pMonster;
	Boss* m_pBoss;

	int m_iFlyingObjectFlag;
	int m_iMonsterWarningRange;

};

#endif // !__GAME_LAYER_H__
