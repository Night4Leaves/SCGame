#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);
	virtual bool init();

	void addFlyingObject(Ref* pSender);

private:
	TMXTiledMap* m_pMap;
	Player* m_pPlayer;
};

#endif // !__GAME_LAYER_H__
