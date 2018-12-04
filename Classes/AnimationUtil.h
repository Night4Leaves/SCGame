#pragma once
#ifndef __ANIMATION_UTIL_H__
#define __ANIMATION_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:
	//���ݶ�������ǰ׺������������
	static Animation* createAnimationWithSingleFrameName(const char* name, float delay, int loops);

	//���ݶ�������ǰ׺�����������󣬲�ָ������֡����
	static Animation* createAnimationWithFrameNameAndNum(const char* name, float delay, int loops, int num);
};

#endif // !__ANIMATION_UTIL_H__
