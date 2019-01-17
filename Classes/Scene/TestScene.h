#pragma once
#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

/*测试用场景类，最后要删除*/
class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	static TestScene* createScene();
	CREATE_FUNC(TestScene);
	virtual bool init();
};
#endif // !__TEST_SCENE_H__
