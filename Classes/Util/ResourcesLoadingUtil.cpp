#include "ResourcesLoadingUtil.h"

void ResourcesLoadingUtil::preloadResources()
{
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();

	spriteFrameCache->addSpriteFramesWithFile("UI_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("UI_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("TP.plist");
	spriteFrameCache->addSpriteFramesWithFile("Monster.plist");
	spriteFrameCache->addSpriteFramesWithFile("text.plist");
	spriteFrameCache->addSpriteFramesWithFile("sceneitem.plist");
	spriteFrameCache->addSpriteFramesWithFile("Number.plist");
	spriteFrameCache->addSpriteFramesWithFile("attack.plist");

	spriteFrameCache->addSpriteFramesWithFile("character/player_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("character/player_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("character/NPC.plist");
}
