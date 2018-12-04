#pragma once
#ifndef __TEXT_DISPLAY_LAYER_H__
#define __TEXT_DISPLAY_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class TextDisplayLayer : public Layer
{
public:
	TextDisplayLayer();
	virtual ~TextDisplayLayer();

	CREATE_FUNC(TextDisplayLayer);
	virtual bool init();

	//设置游戏标题
	bool setGameTitle(const char* title, const char* fontType, float fontSize, Color3B color = Color3B::WHITE);
};

#endif // !__TEXT_DISPLAY_LAYER_H__
