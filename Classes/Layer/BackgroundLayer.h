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
	 *	���ݴ����ͼƬ���ֽ�ͼƬ����Ϊ���������ӵ���������
	 *	@pictureName	����ͼƬ����
	 */
	void setBackgroundPicture(const char* pictureName);

	/**
	 *	������Ϸ����
	 *	@title	��������
	 *	@fontType	��������
	 *	@fontSize	�����С
	 *	@color	������ɫ
	 */
	void setGameTitle(const char* title, const char* fontType, float fontSize, Color3B color = Color3B::WHITE);
};

#endif // !__BACKGROUND_LAYER_H__

