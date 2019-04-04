#pragma once
#ifndef __CHEMISTRY_SCENE_ITEM_H__
#define __CHEMISTRY_SCENE_ITEM_H__

#include "SceneItem.h"

class ChemistrySceneItem : public SceneItem
{
public:
	static ChemistrySceneItem * cteate(const SceneItemInfomation & sceneItemInfo);

	virtual void startPause(Ref* pSender);
	virtual void endPause(Ref* pSender);

protected:
	ChemistrySceneItem();
	virtual ~ChemistrySceneItem();

	void checkItemType(Ref* pSender);
};

#endif // !__CHEMISTRY_SCENE_ITEM_H__
