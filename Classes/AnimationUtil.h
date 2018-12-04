#pragma once
#ifndef __ANIMATION_UTIL_H__
#define __ANIMATION_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:
	//根据动画名字前缀创建动画对象
	static Animation* createAnimationWithSingleFrameName(const char* name, float delay, int loops);

	//根据动画名字前缀创建动画对象，并指定动画帧数量
	static Animation* createAnimationWithFrameNameAndNum(const char* name, float delay, int loops, int num);
};

#endif // !__ANIMATION_UTIL_H__
