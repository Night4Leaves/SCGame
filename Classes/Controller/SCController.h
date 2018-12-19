#pragma once
#ifndef __SC_CONTROLLER_H__
#define __SC_CONTROLLER_H__

#include "GeneralControllerListener.h"

class SCController : public Node
{
public:
	SCController();
	virtual ~SCController();

	//���ü�������
	void setControllerListner(GeneralControllerListener* controllerListener);

	//���������б���Ŀ��ƽ�ɫ��״̬
	virtual void checkControllerStatus() = 0;

protected:
	//��¼�����ƶ���
	GeneralControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
