#include  "NPC.h"
#include "Util/AnimationUtil.h"
#include "CustomizeEnum.h"

NPC::NPC()
{
}

NPC::~NPC()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
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
	m_strNPCName = npcSetInfo.str_npcName;
	m_enumNPCType = npcSetInfo.enum_npcType;

	//根据传入的角色名生成静态动画帧名称
	std::string wait = StringUtils::format("%s_wait.png", m_strNPCName.c_str());
	
	int num = npcSetInfo.i_num;
	float delay = npcSetInfo.f_delay;
	int loops = npcSetInfo.i_loops;
	float scale = npcSetInfo.f_scale;

	//创建精灵对象
	m_pSprite = Sprite::createWithSpriteFrameName(wait.c_str());
	
	m_pSprite->setScale(scale);

	//如果待机动画帧数量不为1，意味NPC采用动态待机动画
	if (num > 1)
	{
		std::string idle = StringUtils::format("%s_idle", npcSetInfo.str_npcName.c_str());
		
		Animation* animation = AnimationUtil::createAnimationWithFrameNameAndNum(idle.c_str(), delay, loops, num);
		Animate* animate = Animate::create(animation);
		m_pSprite->runAction(animate);
	}

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(NPC::checkPlayerPoint),
		"player_check_point",
		NULL);

	return true;
}

void NPC::checkPlayerPoint(Ref * pSender)
{
	Point* playerPoint = (Point*)pSender;
	Point npcPoint = this->getPosition();
	Size npcSize = m_pSprite->getContentSize();
	float scale = m_pSprite->getScale();

	float xPlayer = playerPoint->x;
	float yPlayer = playerPoint->y;

	float xNPC = npcPoint.x;
	float yNPC = npcPoint.y;

	float npcWidth = npcSize.width * scale;
	float npcHeight = npcSize.height * scale;

	if ((xPlayer - (xNPC - npcWidth * 0.5)) > 0
		&& (xPlayer - (xNPC + npcWidth * 0.5)) < 0
		&& (yPlayer - (yNPC - 24)) > 0)
	{
		log("open NPC UI");
		switch (m_enumNPCType)
		{
		case store:
			log("open NPC normal store");
			NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref*)en_paneMsg_openItemStore);
			break;
		case skill:
			log("open NPC skill store");
			NotificationCenter::getInstance()->postNotification("show_PaneLayer", (Ref*)en_paneMsg_openSkillStore);
			break;
		case normal:
			break;
		default:
			break;
		}
	}
}
