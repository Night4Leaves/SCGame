#include "ResourcesLoadingUtil.h"

void ResourcesLoadingUtil::preloadResources()
{
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();

	spriteFrameCache->addSpriteFramesWithFile("UI.plist");
	spriteFrameCache->addSpriteFramesWithFile("NPC.plist");

	spriteFrameCache->addSpriteFramesWithFile("player/player_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("player/player_02.plist");
}