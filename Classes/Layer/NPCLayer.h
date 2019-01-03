#pragma once
#ifndef __NPC_LAYER__
#define __NPC_LAYER__

#include "cocos2d.h"
#include "Entity/NPC.h"

USING_NS_CC;

class NPCLayer : public Layer
{
public:
	NPCLayer();
	~NPCLayer();

	CREATE_FUNC(NPCLayer);
	virtual bool init();

	/**
	 *	设置主场景界面的NPC
	 *	@objGroup	Tiled地图的对象层
	 */
	void setMainSceneNPC(const TMXObjectGroup* objGroup);

private:
	//添加NPC到层中
	void addNPC(const NPCSetInfo& npcSetInfo, Point npcSetPosition);
};

#endif // !__NPCLAYER__
