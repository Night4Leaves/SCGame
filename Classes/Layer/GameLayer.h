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

	void addAttackFlyingObject(Ref* pSender);

private:
	TMXTiledMap* m_pMap;
	Player* m_pPlayer;
	PlayerController* m_pPlayerController;
	Vector<FlyingObject*> vector_pAttackFlyingObject;
	int i_flyingObjectFlag;
};

#endif // !__GAME_LAYER_H__