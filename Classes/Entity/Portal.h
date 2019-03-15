#pragma once
#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "cocos2d.h"

USING_NS_CC;

class Portal : public Node
{
public:
	CREATE_FUNC(Portal);
	virtual bool init();

	/*根据玩家坐标判定是否打开关卡选择界面*/
	void checkPlayerPoint(Ref* pSender);

private:
	Portal();
	virtual ~Portal();

private:
	Sprite* m_pSprite;	//绑定传送门对象
};

#endif // !__PORTAL_H__
