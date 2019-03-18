#pragma once
#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

#include "SCController.h"

class PlayerController : public SCController
{
public:
	PlayerController();
	virtual ~PlayerController();

	CREATE_FUNC(PlayerController);
	virtual bool init();
	virtual void update(float dt);

	//获取玩家是否朝右
	bool getIsRight();
	//保存块地图
	void setMap(TMXTiledMap* p_map);

	//检查控制器记录的角色状态
	virtual void checkControllerStatus();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
	//根据玩家设置显示地图
	void setViewPointByPlayer(Point pos);
	//设置玩家角色位置
	void setPlayerPosition(Point pos);
	//受到伤害
	void getDamage(Ref* pSender);

private:
	TMXTiledMap* m_pMap;	//记录地图
	TMXLayer* m_pMeta;		//障碍判定层

	float m_fMapWidth;	//地图宽度
	float m_fMapHeight;	//地图高度

	float m_iXSpeed;	//X轴移速
	float m_iYSpeed;	//Y速移速

	bool m_bIsRight;	//是否向右
	bool m_bIsLock;		//是否为锁死状态
	bool m_bIsBossBattle;	//是否进入Boss战

	int m_iHorizontalRun;	//是否为左右跑动状态(判断左右移动键按下几个)
	int m_iVerticalRun;		//是否为上下跑动状态(判断上下移动键按下几个)

};

#endif // !__PLAYER_CONTROLLER_H__
