#pragma once
#ifndef __MONSTER_CONTROLLER_H__
#define __MONSTER_CONTROLLER_H__

#include "SCController.h"

class MonsterController : public SCController
{
public:
	MonsterController();
	virtual ~MonsterController();

	CREATE_FUNC(MonsterController);
	virtual bool init();
	virtual void update(float dt);

	//����������¼�Ľ�ɫ״̬
	virtual void checkControllerStatus();

private:
	int m_iXSpeed;	//X������

	bool m_bIsRight;	//�Ƿ�����
	bool m_bIsLock;		//�Ƿ�Ϊ����״̬
	bool m_bIsAttack;

	float m_fStateTime;
};

#endif // !__MONSTER_CONTROLLER_H__
