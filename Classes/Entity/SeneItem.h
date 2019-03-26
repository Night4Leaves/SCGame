#pragma once
#ifndef __SCENE_ITEM_H__
#define __SCENE_ITEM_H__

#include "CustomizeStruct.h"

#include "cocos2d.h"
USING_NS_CC;

class SceneItem : public Node
{
public:
	static SceneItem * create(const SceneItemInfomation & sceneItemInfo);
	virtual bool init(const SceneItemInfomation & sceneItemInfo);

private:
	SceneItem();
	virtual ~SceneItem();

	void checkPlayerPoint(Ref* pSender);

	void mouseClick(Ref* pSender);
	void mouseMove(Ref* pSender);
	void mouseEnd(Ref* pSender);

private:
	Sprite* m_pSprite;	//保存形象的精灵
	
	bool m_bIsMoveable;	//是否可移动

	SceneItemType m_enSceneItemType;	//场景道具种类
	PH m_enPH;	//PH值（化学系道具使用的属性）
};

#endif // !__SCENE_ITEM_H__
