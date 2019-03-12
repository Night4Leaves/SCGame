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
	std::vector<NPCSetInfo> npcInfoVector;
	NPCSetInfo npc = { "NPC_01", NPCType::store, 0.15 };
	npcInfoVector.push_back(npc);
	npc.enum_npcType = skill;
	npc.str_npcName = "NPC_02";
	npcInfoVector.push_back(npc);
	npc.enum_npcType = normal;
	npc.str_npcName = "NPC_03";
	npcInfoVector.push_back(npc);
	npc.str_npcName = "NPC_04";
	npcInfoVector.push_back(npc);
	npc.str_npcName = "NPC_05";
	npcInfoVector.push_back(npc);

	for (int i = 1; i <= 5; i++)
	{
		float x = 0.0f;
		float y = 0.0f;
		std::string str_npcName = StringUtils::format("NPC_%02d", i);
		npc.str_npcName = str_npcName;
		ValueMap point = objGroup->getObject(str_npcName.c_str());
		x = point.at("x").asFloat();
		y = point.at("y").asFloat();
		log("%s", str_npcName.c_str());
		log("x:%f, y:%f", x, y);

		Vec2 npc_point = Vec2(x, y);
		addNPC(npcInfoVector[i-1], npc_point);
	}
	
}

void NPCLayer::addNPC(const NPCSetInfo& npcSetInfo, Point npcSetPosition)
{
	NPC* npc = NPC::create(npcSetInfo);
	this->addChild(npc);

	npc->setPosition(npcSetPosition);
}
