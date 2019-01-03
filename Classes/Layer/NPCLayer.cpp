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
	

	////NPC位置
	//Vec2 npc_1_point = Vec2(x, y);
	//Vec2 npc_2_point = Vec2(265, 150);
	//Vec2 npc_3_point = Vec2(350, 150);
	//Vec2 npc_4_point = Vec2(550, 150);
	//Vec2 npc_5_point = Vec2(650, 150);

	////NPC动画
	//NPCSetInfo npc_1 = { "npc_1", NPCType::normal, 4 , 0.25f };
	//NPCSetInfo npc_2 = { "npc_2", NPCType::normal, 4 , 0.3f };
	//NPCSetInfo npc_3 = { "npc_3", NPCType::normal, 4 , 0.28f };

	////添加NPC
	//addNPC(npc_1, npc_1_point);
	//addNPC(npc_2, npc_2_point);
	//addNPC(npc_3, npc_3_point);
}

void NPCLayer::addNPC(const NPCSetInfo& npcSetInfo, Point npcSetPosition)
{
	
	NPC* npc = NPC::create(npcSetInfo);
	this->addChild(npc);

	npc->setPosition(npcSetPosition);

	//NPC设置的位置
	/*Point pos = npc->getPosition();
	log("x:%f ,y:%f", pos.x, pos.y);*/
}
