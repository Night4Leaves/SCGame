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

	virtual void checkControllerStatus();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
protected:
	int m_iXSpeed;	//X轴移速
	int m_iYSpeed;	//Y速移速

	bool m_bIsRight;	//是否向右

	int m_iIsRun;	//是否为跑动状态(判断左右移动键按下几个)
	bool m_bIsJump;	//是否为跳跃状态
	bool m_bIsclimb;	//是否为攀爬状态
};

#endif // !__PLAYER_CONTROLLER_H__
