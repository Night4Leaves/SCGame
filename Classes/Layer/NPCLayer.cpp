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
	//TODO:����Tiled��ͼ�ĵ�λ����NPCλ��
	//TMXObjectGroup* objects = map->getObjectGroup("objects");

	//ValueMap point = objects->getObject("npc_2");
	//float x = point.at("x").asFloat();
	//float y = point.at("y").asFloat();

	//NPCλ��
	Vec2 npc_1_point = Vec2(100, 150);
	Vec2 npc_2_point = Vec2(265, 150);
	Vec2 npc_3_point = Vec2(350, 150);
	Vec2 npc_4_point = Vec2(550, 150);
	Vec2 npc_5_point = Vec2(650, 150);

	//NPC����
	NPCSetInfo npc_1 = { "npc_1", npc_1_point, 4 , 0.3f};
	NPCSetInfo npc_2 = { "npc_2", npc_2_point, 4 , 0.3f };
	NPCSetInfo npc_3 = { "npc_3", npc_3_point, 4 , 0.3f };

	//���NPC
	addNPC(npc_1);
	addNPC(npc_2);
	addNPC(npc_3);
}

void NPCLayer::addNPC(const NPCSetInfo& npcSetInfo)
{
	//���ݴ���Ľ�ɫ�����ɾ�̬����֡����
	std::string wait = StringUtils::format("%s_wait.png", npcSetInfo.name);

	log("Picture name is: %s", wait.c_str());

	int num = npcSetInfo.num;
	float delay = npcSetInfo.delay;
	int loops = npcSetInfo.loops;
	Vec2 point = npcSetInfo.point;

	//�����������
	Sprite* sprite = Sprite::createWithSpriteFrameName(wait);
	this->addChild(sprite);
	sprite->setPosition(point);

	//�����������֡������Ϊ1����ζNPC���ö�̬��������
	if (num > 1)
	{
		std::string idle = StringUtils::format("%s_idle", npcSetInfo.name);

		log("Picture name is: %s", idle.c_str());

		Animation* animation = AnimationUtil::createAnimationWithFrameNameAndNum(idle.c_str(), delay, loops, num);
		Animate* animate = Animate::create(animation);
		sprite->runAction(animate);
	}
}
