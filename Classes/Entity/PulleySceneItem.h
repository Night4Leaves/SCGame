#pragma once
#ifndef __PULLEY_SCENE_ITEM_H__
#define __PULLEY_SCENE_ITEM_H__

#include "SceneItem.h"

class PulleySceneItem : public SceneItem
{
public:
	static PulleySceneItem * create(const SceneItemInfomation & sceneItemInfo);
	virtual void update(float dt);

	void setPulleyPart(PulleyPart pulleyPart);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	PulleySceneItem();
	virtual ~PulleySceneItem();

private:
	void checkEnd(Ref* pSender);
	void checkFulcrumPoint(Ref* pSender);
	void checkPlayerPoint(Ref* pSender);
	void runPulley(Ref* pSender);

	void changePulleyStatus(Point setPos);
	void changePulleyGroupStatus(Ref* pSender);

private:
	PulleyPart m_enPulleyPart;	//滑轮部件
};

#endif // !__PULLEY_SCENE_ITEM_H__
