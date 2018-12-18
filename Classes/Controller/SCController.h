#pragma once
#ifndef __SC_CONTROLLER_H__
#define __SC_CONTROLLER_H__

#include "PlayerControllerListener.h"

class SCController : public Node
{
public:
	SCController();
	virtual ~SCController();

	//���ü�������
	void setControllerListner(PlayerControllerListener* controllerListener);

	//���������б���Ŀ��ƽ�ɫ��״̬
	virtual void checkControllerStatus() = 0;

	/**
	 *	���ÿ������ٶ�
	 *	@i_xSpeed	x���ٶ�
	 *	@i_ySpeed	y���ٶ�
	 */
	/*virtual void setSpeed(int i_xSpeed, int i_ySpeed) = 0;*/
protected:
	//��¼�����ƶ���
	PlayerControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
