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

	//���������������NPC
	void setMainSceneNPC();

private:
	//���NPC������
	void addNPC(const NPCSetInfo& npcSetInfo, Point npcSetPosition);
};

#endif // !__NPCLAYER__
