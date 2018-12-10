#include "ResourcesLoadingUtil.h"

void ResourcesLoadingUtil::preloadResources()
{
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();

	spriteFrameCache->addSpriteFramesWithFile("UI.plist");
	spriteFrameCache->addSpriteFramesWithFile("NPC.plist");
}
