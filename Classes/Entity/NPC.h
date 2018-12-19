#pragma once
#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"

/**
 *	NPC����
 */
enum NPCType
{
	store,	//�̵�
	skill,	//����
	normal	//��ͨ
};

/**
 *	NPC������Ϣ
 *	@name	NPC����
 *	@npcType	NPC����
 *	@num	NPC����֡����
 *	@delay	NPC����֡ÿ֡���
 *	@loops	����ѭ������
 *	@scale	���ű���
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

	//NPC����
	const char* m_strNPCName;
	//NPC����
	NPCType m_NPCType;
};

#endif // !__NPC_H__
