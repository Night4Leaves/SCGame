#pragma once
#ifndef __INITIAL_SCENE_H__
#define __INITIAL_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer;
class TextDisplayLayer;
class GameMenuLayer;

class InitialScene : public Scene
{
public:
	InitialScene();
	virtual ~InitialScene();

	static Scene* createScene();
	CREATE_FUNC(InitialScene);
	virtual bool init();

private:
	BackgroundLayer* m_pBackgroundLayer;
	TextDisplayLayer* m_pTextDisplayLayer;
	GameMenuLayer* m_pGameMenuLayer;
};

#endif // !__INITIAL_SCENE_H__
