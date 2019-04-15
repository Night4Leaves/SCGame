#pragma once
#ifndef __SCENE_ITEM_LAYER_H__
#define __SCENE_ITEM_LAYER_H__

#include "Entity/LeverSceneItem.h"
#include "Entity/ChemistrySceneItem.h"

#include "cocos2d.h"
USING_NS_CC;

class SceneItemLayer : public Layer
{
public:
	CREATE_FUNC(SceneItemLayer);

	void setSceneitem(SceneItem * sceneItem);
	void setChemistryItem(ChemistrySceneItem * sceneItem);

private:
	SceneItemLayer();
	virtual ~SceneItemLayer();

	virtual bool init();

private:
	EventListenerTouchOneByOne* m_pListener;	//点击事件监听器
};

#endif // !__SCENE_ITEM_LAYER_H__
