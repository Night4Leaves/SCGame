#pragma once
#ifndef __NPC_LAYER__
#define __NPC_LAYER__

#include "cocos2d.h"

USING_NS_CC;

/**
 *	NPC������Ϣ
 *	@name	NPC����
 *	@point	NPC���õ�λ��
 *	@num	NPC����֡����
 *	@delay	NPC����֡ÿ֡���
 *	@loops	����ѭ������
 *	@scale	���ű���
 */
struct NPCSetInfo
{
	const char* name;
	Vec2 point;
	int num = 1;
	float delay = 0.1;
	int loops = -1;
	float scale = 1;
};

class NPCLayer : public Layer
{
public:
	NPCLayer();
	~NPCLayer();

	CREATE_FUNC(NPCLayer);
	virtual bool init();

	//���������������NPC
	void setMainSceneNPC();

private:
	//���NPC������
	void addNPC(const NPCSetInfo& npcSetInfo);
};

#endif // !__NPCLAYER__
