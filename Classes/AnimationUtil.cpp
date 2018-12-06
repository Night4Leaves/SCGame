#include "AnimationUtil.h"

Animation * AnimationUtil::createAnimationWithSingleFrameName(const char * name, float delay, int loops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> frameList;
	SpriteFrame* frame = NULL;
	int index = 1;

	do {
		//���ϻ�ȡSpriteFrame����ֱ����ȡ��ֵΪ��
		frame = cache->getSpriteFrameByName(StringUtils::format("%s_%02d.png", name, index++));
		CC_BREAK_IF(frame == nullptr);

		frameList.pushBack(frame);
	} while (true);

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(loops);
	animation->setRestoreOriginalFrame(true);	//������������ָ���ʼ֡
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
		//���ϻ�ȡSpriteFrame����ֱ����ȡ��ֵΪ��
		frame = cache->getSpriteFrameByName(StringUtils::format("%s_%02d.png", name, index++));
		CC_BREAK_IF(frame == nullptr);

		frameList.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(loops);
	animation->setRestoreOriginalFrame(true);	//������������ָ���ʼ֡
	animation->setDelayPerUnit(delay);

	return animation;
}
