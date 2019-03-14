#pragma once
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;

class HeartCount;

/*测试用场景类，最后要删除*/
class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	static TestScene* createScene();
	CREATE_FUNC(TestScene);
	virtual bool init();
	virtual void update(float dt);

	void readJson();
	void readArrayJson();
	void writeJson();

private:
	int hp;
	float dtCount;
	LoadingBar* hpBar;
	HeartCount* test;

};
#endif // !__TEST_SCENE_H__
