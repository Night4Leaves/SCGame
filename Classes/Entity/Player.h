#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Player : public Entity, public GeneralControllerListener
{
public:
	static Player* create(const char* str_playerName);
	virtual bool init(const char* str_playerName);

	void setController(SCController* controller);
	virtual Vec2 getTargetPosition();
	virtual void setTargetPosition(Vec2 pos);

	//��������״̬
	void checkControllerStatus();
	//�������������ʾ��ͼ
	void setViewPointByPlayer();

	virtual void turnAround(bool b_isRight);

	virtual void idle();
	virtual void run();
	virtual void attack();
	virtual void jump();
	virtual void climb();
	virtual void hurt();
	virtual void death();

private:
	Player();
	~Player();

	//��¼������
	SCController* m_pPlayerController;
	//��¼��ɫ�����������ɽ�ɫ����
	const char* m_strPlayerName;
	//��ɫ������
	std::vector<const char*> m_strActionName = { "idle","run","attack","jump","climb","hurt","death" };
	//����֡���ʱ��
	float m_fActionTime[7] = { 0.25f, 0.04f, 0.1f, 0.2f, 0.1f, 0.1f, 0.25f };
	//�����ظ�����
	int m_iActionPlayTime[7] = { -1, -1, 1, 1, -1, 1, 1 };
};

#endif // !__PLAYER_H__
