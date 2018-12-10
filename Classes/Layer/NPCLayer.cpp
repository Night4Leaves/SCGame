#include "NPCLayer.h"
#include "Util/AnimationUtil.h"

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
	NPCSetInfo npc_1 = { "npc_1", npc_1_point, 4 , 0.3f};
	NPCSetInfo npc_2 = { "npc_2", npc_2_point, 4 , 0.3f };
	NPCSetInfo npc_3 = { "npc_3", npc_3_point, 4 , 0.3f };

	//添加NPC
	addNPC(npc_1);
	addNPC(npc_2);
	addNPC(npc_3);
}

void NPCLayer::addNPC(const NPCSetInfo& npcSetInfo)
{
	//根据传入的角色名生成静态动画帧名称
	std::string wait = StringUtils::format("%s_wait.png", npcSetInfo.name);

	log("Picture name is: %s", wait.c_str());

	int num = npcSetInfo.num;
	float delay = npcSetInfo.delay;
	int loops = npcSetInfo.loops;
	Vec2 point = npcSetInfo.point;

	//创建精灵对象
	Sprite* sprite = Sprite::createWithSpriteFrameName(wait);
	this->addChild(sprite);
	sprite->setPosition(point);

	//如果待机动画帧数量不为1，意味NPC采用动态待机动画
	if (num > 1)
	{
		std::string idle = StringUtils::format("%s_idle", npcSetInfo.name);

		log("Picture name is: %s", idle.c_str());

		Animation* animation = AnimationUtil::createAnimationWithFrameNameAndNum(idle.c_str(), delay, loops, num);
		Animate* animate = Animate::create(animation);
		sprite->runAction(animate);
	}
}
