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

void NPCLayer::setMainSceneNPC()
{
	//TODO:根据Tiled地图的点位设置NPC位置
	//TMXObjectGroup* objects = map->getObjectGroup("objects");

	//ValueMap point = objects->getObject("npc_2");
	//float x = point.at("x").asFloat();
	//float y = point.at("y").asFloat();

	//NPC位置
	Vec2 npc_1_point = Vec2(100, 150);
	Vec2 npc_2_point = Vec2(265, 150);
	Vec2 npc_3_point = Vec2(350, 150);
	Vec2 npc_4_point = Vec2(550, 150);
	Vec2 npc_5_point = Vec2(650, 150);

	//NPC动画
	NPCSetInfo npc_1 = { "npc_1", NPCType::normal, 4 , 0.25f };
	NPCSetInfo npc_2 = { "npc_2", NPCType::normal, 4 , 0.3f };
	NPCSetInfo npc_3 = { "npc_3", NPCType::normal, 4 , 0.28f };

	//添加NPC
	addNPC(npc_1, npc_1_point);
	addNPC(npc_2, npc_2_point);
	addNPC(npc_3, npc_3_point);
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
