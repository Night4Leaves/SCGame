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

	/**
	 *	根据传入的图片名字将图片创建为精灵对象并添加到背景层中
	 *	@pictureName	背景图片名字
	 */
	void setBackgroundPicture(const char* pictureName);

	/**
	 *	设置游戏标题
	 *	@title	标题内容
	 *	@fontType	字体种类
	 *	@fontSize	字体大小
	 *	@color	字体颜色
	 */
	void setGameTitle(const char* title, const char* fontType, float fontSize, Color3B color = Color3B::WHITE);
};

#endif // !__BACKGROUND_LAYER_H__

