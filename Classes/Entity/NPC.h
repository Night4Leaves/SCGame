#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"

class NPC : public Entity
{
public:
	static NPC* create(const NPCSetInfo& npcSetInfo);
	virtual bool init(const NPCSetInfo& npcSetInfo);

	void checkPlayerPoint(Ref* pSender);

private:
	NPC();
	~NPC();

	//NPC名字
	std::string m_strNPCName;
	//NPC种类
	NPCType m_enumNPCType;
};

#endif // !__NPC_H__
