#pragma once
#ifndef __LEVER_SCENE_ITEM_H__
#define __LEVER_SCENE_ITEM_H__

#include "SceneItem.h"

class LeverSceneItem : public SceneItem
{
public:
	static LeverSceneItem * create(const SceneItemInfomation & sceneItemInfo);
	virtual void update(float dt);

	void setLeverPart(LeverPart leverPart);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	LeverSceneItem();
	virtual ~LeverSceneItem();

private:
	void checkEnd(Ref* pSender);
	void checkFulcrumPoint(Ref* pSender);
	void checkPlayerPoint(Ref* pSender);

	void changeRodStatus(Point setPos);
	void changeStoneStatus(Ref* pSender);
	
private:
	LeverPart m_enLeverPart;	//杠杆部件

	int m_iStoneSpeed;	//石头滚动速度

	float m_fStateTime;

	bool m_bIsSaveLabor;	//是否省力
};

#endif // !__LEVER_SCENE_ITEM_H__
