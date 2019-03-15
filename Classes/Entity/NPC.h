#pragma once
#ifndef __NPC_H__
#define __NPC_H__

//#include "Entity.h"
#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class NPC : public Node
{
public:
	static NPC* create(const NPCSetInfo& npcSetInfo);
	virtual bool init(const NPCSetInfo& npcSetInfo);

	/*根据角色坐标判定哪位NPC响应*/
	void checkPlayerPoint(Ref* pSender);

private:
	NPC();
	~NPC();

private:
	
	std::string m_strNPCName;	//NPC名字
	
	NPCType m_enumNPCType;	//NPC种类

	Sprite* m_pSprite;	//绑定NPC形象
};

#endif // !__NPC_H__
