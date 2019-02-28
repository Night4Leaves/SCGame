#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player;
class PlayerController;
class FlyingObject;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);
	virtual bool init();
	virtual void update(float dt);

	void addAttackFlyingObject(Ref* pSender);
	void stoneRush(Ref* pSender);

	void setSceneItem();

	void setTestGameScene();

	void setGameScene_1_1();

private:
	TMXTiledMap* m_pMap;
	Player* m_pPlayer;
	PlayerController* m_pPlayerController;
	Vector<FlyingObject*> vector_pAttackFlyingObject;
	int i_flyingObjectFlag;

	Sprite* m_lever;
	Sprite* m_stone;
	int stoneSpeed;
};

#endif // !__GAME_LAYER_H__
