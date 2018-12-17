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
	int m_iXSpeed;	//X������
	int m_iYSpeed;	//Y������

	bool m_bIsRight;	//�Ƿ�����

	int m_iIsRun;	//�Ƿ�Ϊ�ܶ�״̬(�ж������ƶ������¼���)
	bool m_bIsJump;	//�Ƿ�Ϊ��Ծ״̬
	bool m_bIsclimb;	//�Ƿ�Ϊ����״̬
};

#endif // !__PLAYER_CONTROLLER_H__
