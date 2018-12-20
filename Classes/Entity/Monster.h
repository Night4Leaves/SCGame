#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"
#include "Controller/SCController.h"

class Monster : public Entity, public GeneralControllerListener
{
public:
	static Monster* create(const char* str_monsterName);
	virtual bool init(const char* str_monsterName);

	void setController(SCController* controller);

	//��ȡ��ɫ����
	virtual Vec2 getTargetPosition();
	/**
	 *	���ý�ɫ����
	 *	@pos Ŀ��λ��
	 */
	virtual void setTargetPosition(Vec2 pos);
	//��������״̬
	void checkControllerStatus();

	/**
	 *	���ƽ�ɫ�Ƿ���
	 *	@b_isRight trueΪ���ң�false����
	 */
	virtual void turnAround(bool b_isRight);

	virtual void idle();
	virtual void run();
	virtual void attack();
	virtual void jump();
	virtual void climb();
	virtual void hurt();
	virtual void death();

private:
	Monster();
	virtual ~Monster();

	//��¼������
	SCController* m_pMonsterController;
	//��¼��ɫ�����������ɽ�ɫ����
	const char* m_strMonsterName;
	//��ɫ������
	std::vector<const char*> m_strActionName = { "idle","run","attack","hurt","death" };
	//����֡���ʱ��
	float m_fActionTime[7] = { 0.25f, 0.2f, 0.15f, 0.1f, 0.25f };
	//�����ظ�����
	int m_iActionPlayTime[7] = { -1, -1, 1, 1, 1 };
	//int m_iActionPlayTime[7] = { -1, -1, -1, -1, -1 };
};

#endif // !__MONSTER_H__
