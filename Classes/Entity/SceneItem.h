#pragma once
#ifndef __SCENE_ITEM_H__
#define __SCENE_ITEM_H__

#include "CustomizeStruct.h"
#include "PauseDevice.h"

#include "cocos2d.h"
USING_NS_CC;

class SceneItem : public PauseDevice
{
protected:
	virtual bool init(const SceneItemInfomation & sceneItemInfo);

	SceneItem();
	virtual ~SceneItem();

	void mouseClick(Ref* pSender);
	void mouseMove(Ref* pSender);
	void mouseEnd(Ref* pSender);

protected:
	Sprite* m_pSprite;	//保存形象的精灵
	
	bool m_bIsMoveable;	//是否可移动
	bool m_bIsTrigger;	//是否激活
	bool m_bIsUsed;	//是否被使用

	SceneItemType m_enSceneItemType;	//场景道具种类
	PH m_enPH;	//PH值（化学系道具使用的属性）
	PhysicsSceneItemGroup m_enPSIG;	//场景道具组别（物理系道具专用）
};

#endif // !__SCENE_ITEM_H__
