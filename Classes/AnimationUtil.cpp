#include "AnimationUtil.h"

Animation * AnimationUtil::createAnimationWithSingleFrameName(const char * name, float delay, int loops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameList;
	SpriteFrame* frame = NULL;
	int index = 1;

	do {
		//不断获取SpriteFrame对象直到获取的值为空
		frame = cache->getSpriteFrameByName(StringUtils::format("%s_%02d.png", name, index++));
		CC_BREAK_IF(frame == nullptr);

		frameList.pushBack(frame);
	} while (true);

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(loops);
	animation->setRestoreOriginalFrame(true);	//当动画结束后恢复初始帧
	animation->setDelayPerUnit(delay);

	return animation;
}

Animation * AnimationUtil::createAnimationWithFrameNameAndNum(const char * name, float delay, int loops, int num)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameList;
	SpriteFrame* frame = NULL;
	int index = 1;

	while(index <= num)
	{
		//不断获取SpriteFrame对象直到获取的值为空
		frame = cache->getSpriteFrameByName(StringUtils::format("%s_%02d.png", name, index++));
		CC_BREAK_IF(frame == nullptr);

		frameList.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(loops);
	animation->setRestoreOriginalFrame(true);	//当动画结束后恢复初始帧
	animation->setDelayPerUnit(delay);

	return animation;
}
