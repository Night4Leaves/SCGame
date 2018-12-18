#pragma once
#ifndef __NPC_LAYER__
#define __NPC_LAYER__

#include "cocos2d.h"

USING_NS_CC;

/**
 *	NPC设置信息
 *	@name	NPC名字
 *	@point	NPC设置的位置
 *	@num	NPC动画帧数量
 *	@delay	NPC动画帧每帧间隔
 *	@loops	动画循环次数
 *	@scale	缩放倍数
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

	//设置主场景界面的NPC
	void setMainSceneNPC();

private:
	//添加NPC到层中
	void addNPC(const NPCSetInfo& npcSetInfo);
};

#endif // !__NPCLAYER__
