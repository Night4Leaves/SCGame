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

	//���ݴ����ͼƬ���ֽ�ͼƬ����Ϊ���������ӵ���������
	bool setBackgroundPicture(const char* pictureName);
};

#endif // !__BACKGROUND_LAYER_H__

