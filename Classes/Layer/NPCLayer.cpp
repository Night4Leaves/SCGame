#include "NPCLayer.h"

NPCLayer::NPCLayer()
{
}

NPCLayer::~NPCLayer()
{
}

bool NPCLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);

	log("NPCLayer initialize failed!");

	return false;
}

void NPCLayer::setMainSceneNPC(const TMXObjectGroup* objGroup)
{
	//TODO:根据Tiled地图的点位设置NPC位置
	float x = 0.0f;
	float y = 0.0f;

	NPCSetInfo npc_1 = { "npc_1", NPCType::normal, 4 , 0.25f };

	for (int i = 1; i <= 5; i++)
	{
		std::string str_npcName = StringUtils::format("NPC_%02d", i);
		ValueMap point = objGroup->getObject(str_npcName.c_str());
		x = point.at("x").asFloat();
		y = point.at("y").asFloat();
		log("%s", str_npcName.c_str());
		log("x:%f, y:%f", x, y);

		Vec2 npc_1_point = Vec2(x, y);
		addNPC(npc_1, npc_1_point);
	}
	
}

void NPCLayer::addNPC(const NPCSetInfo& npcSetInfo, Point npcSetPosition)
{
	NPC* npc = NPC::create(npcSetInfo);
	this->addChild(npc);

	npc->setPosition(npcSetPosition);
}
