#include "ResourcesLoadingUtil.h"

void ResourcesLoadingUtil::preloadResources()
{
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();

	spriteFrameCache->addSpriteFramesWithFile("UI_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("UI_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("TP.plist");
	spriteFrameCache->addSpriteFramesWithFile("text.plist");
	spriteFrameCache->addSpriteFramesWithFile("Scene_Item.plist");
	spriteFrameCache->addSpriteFramesWithFile("Scene_Item_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("Number.plist");
	spriteFrameCache->addSpriteFramesWithFile("attack.plist");
	spriteFrameCache->addSpriteFramesWithFile("Shop_Item.plist");

	spriteFrameCache->addSpriteFramesWithFile("character/player_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("character/player_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("character/NPC.plist");

	//加载Boss图片资源
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_03.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_04.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_05.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_06.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_07.plist");
	spriteFrameCache->addSpriteFramesWithFile("boss/Boss_Skill.plist");

	//加载普通怪物图片资源
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_01.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_02.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_03.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_04.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_05.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_06.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_07.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_08.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_09.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_10.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_11.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_12.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_13.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_14.plist");
	spriteFrameCache->addSpriteFramesWithFile("monster/Monster_15.plist");
}
