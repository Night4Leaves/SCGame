#pragma once
#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	virtual ~BackgroundLayer();

	CREATE_FUNC(BackgroundLayer);
	virtual bool init();

	//根据传入的图片名字将图片创建为精灵对象并添加到背景层中
	bool setBackgroundPicture(const char* pictureName);
};

#endif // !__BACKGROUND_LAYER_H__

