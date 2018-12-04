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
};

#endif // !__TEXT_DISPLAY_LAYER_H__
