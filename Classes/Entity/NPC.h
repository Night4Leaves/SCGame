#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"

class NPC : public Entity
{
public:
	static NPC* create(const NPCSetInfo& npcSetInfo);
	virtual bool init(const NPCSetInfo& npcSetInfo);

private:
	NPC();
	~NPC();

	//NPC名字
	const char* m_strNPCName;
	//NPC种类
	NPCType m_NPCType;
};

#endif // !__NPC_H__
