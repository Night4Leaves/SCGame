#pragma once
#ifndef __RAILGUN_SCENE_ITEM_H__
#define __RAILGUN_SCENE_ITEM_H__

#include "SceneItem.h"

class RailgunSceneItem : public SceneItem
{
public:
	static RailgunSceneItem * create(const SceneItemInfomation & sceneItemInfo);
	virtual void update(float dt);

	void setRailgunPart(RailgunPart railgunPart);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	RailgunSceneItem();
	virtual ~RailgunSceneItem();

private:
	void checkEnd(Ref* pSender);
	void checkPlayerPoint(Ref* pSender);

	void changeBatteryPos(Point setPos);
	void changeBarrelStatus(Ref* pSender);

	void checkPowerBoxPos(Ref* pSender);
	void checkBatteryDirection(Ref* pSender);
	void checkShell(Ref* pSender);

private:
	RailgunPart m_enRailgunPart;

	float m_fStateTime;

	int m_iShellSpeed;	//炮弹飞行速度

	bool m_bBatteryRight;	//电池右边阳极
	bool m_bMagnetismRight;	//右端是N极(磁轨/炮弹)
	bool m_bMagnetismRightCondition;	//磁轨右端是N极的电池条件
};

#endif // !__RAILGUN_SCENE_ITEM_H__
