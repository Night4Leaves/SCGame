#include "NPCLayer.h"
#include "AnimationUtil.h"

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
}

void NPCLayer::addNPC(NPCSetInfo npcSetInfo)
{
	//根据传入的角色名生成静态动画帧名称
	std::string wait = StringUtils::format("%s_wait.png", npcSetInfo.name);
	int num = npcSetInfo.num;
	float delay = npcSetInfo.delay;
	int loops = npcSetInfo.loops;
	Vec2 point = npcSetInfo.point;

	//创建精灵对象
	Sprite* sprite = Sprite::create(wait);
	this->addChild(sprite);
	sprite->setPosition(point);

	//如果待机动画帧数量不为1，意味NPC采用动态待机动画
	if (num > 1)
	{
		std::string idle = StringUtils::format("%s_idle.png", npcSetInfo.name);
		Animation* animation = AnimationUtil::createAnimationWithFrameNameAndNum(idle.c_str(), delay, loops, num);
		Animate* animate = Animate::create(animation);
		sprite->runAction(animate);
	}
}
