#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"

/**
 *	NPC种类
 */
enum NPCType
{
	store,	//商店
	skill,	//技能
	normal	//普通
};

/**
 *	NPC设置信息
 *	@name	NPC名字
 *	@npcType	NPC种类
 *	@num	NPC动画帧数量
 *	@delay	NPC动画帧每帧间隔
 *	@loops	动画循环次数
 *	@scale	缩放倍数
 */
struct NPCSetInfo
{
	const char* name;
	NPCType npcType = NPCType::normal;
	int num = 1;
	float delay = 0.1;
	int loops = -1;
	float scale = 1;
};

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
