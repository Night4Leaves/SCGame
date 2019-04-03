#pragma once
#ifndef __RAILGUN_SCENE_ITEM_H__
#define __RAILGUN_SCENE_ITEM_H__

#include "SceneItem.h"

class RailgunSceneItem : public SceneItem
{
public:
	static RailgunSceneItem * create(const SceneItemInfomation & sceneItemInfo);

	void setRailgunPart(RailgunPart railgunPart);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	RailgunSceneItem();
	virtual ~RailgunSceneItem();

private:
	void checkEnd(Ref* pSender);
	void checkPlayerPoint(Ref* pSender);

	void changeBatteryStatus(Point setPos);

private:
	RailgunPart m_enRailgunPart;
};

#endif // !__RAILGUN_SCENE_ITEM_H__
