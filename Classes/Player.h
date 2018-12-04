#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Player : public Node
{
public:
	Player();
	virtual ~Player();
	virtual bool init();

private:
	
	void move();
	void jump();
	void climb();
	void attack();
	void death();
	
protected:
	Sprite* p_cSprite;

	//Vector<String> action = { "idle", "attack", "jump", "climb", "run", "hurt", "death" };
};

