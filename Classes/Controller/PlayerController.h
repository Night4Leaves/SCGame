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

	//检查控制器记录的角色状态
	virtual void checkControllerStatus();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
protected:
	int m_iXSpeed;	//X轴移速
	int m_iYSpeed;	//Y速移速

	bool m_bIsRight;	//是否向右
	bool m_bIsLock;		//是否为锁死状态

	int m_iIsRun;	//是否为跑动状态(判断左右移动键按下几个)
};

#endif // !__PLAYER_CONTROLLER_H__
