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
protected:
	PlayerControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
