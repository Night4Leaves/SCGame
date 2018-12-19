#include  "NPC.h"
#include "Util/AnimationUtil.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

NPC * NPC::create(const NPCSetInfo& npcSetInfo)
{
	NPC *pRet = new(std::nothrow) NPC();
	if (pRet && pRet->init(npcSetInfo))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool NPC::init(const NPCSetInfo& npcSetInfo)
{
	m_strNPCName = npcSetInfo.name;
	m_NPCType = npcSetInfo.npcType;

	//根据传入的角色名生成静态动画帧名称
	std::string wait = StringUtils::format("%s_wait.png", m_strNPCName);

	log("Picture name is: %s", wait.c_str());

	int num = npcSetInfo.num;
	float delay = npcSetInfo.delay;
	int loops = npcSetInfo.loops;
	float scale = npcSetInfo.scale;

	//创建精灵对象
	Sprite* sprite = Sprite::createWithSpriteFrameName(wait.c_str());

	this->bindSprite(sprite);

	sprite->setScale(scale);

	//如果待机动画帧数量不为1，意味NPC采用动态待机动画
	if (num > 1)
	{
		std::string idle = StringUtils::format("%s_idle", npcSetInfo.name);

		log("Picture name is: %s", idle.c_str());

		Animation* animation = AnimationUtil::createAnimationWithFrameNameAndNum(idle.c_str(), delay, loops, num);
		Animate* animate = Animate::create(animation);
		sprite->runAction(animate);
	}

	return true;
}
