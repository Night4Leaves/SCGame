#pragma once
#ifndef __SC_CONTROLLER_H__
#define __SC_CONTROLLER_H__

#include "GeneralControllerListener.h"

class SCController : public Node
{
public:
	SCController();
	virtual ~SCController();

	//设置监听对象
	void setControllerListner(GeneralControllerListener* controllerListener);

	//检查控制器中保存的控制角色的状态
	virtual void checkControllerStatus() = 0;

protected:
	//记录被控制对象
	GeneralControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
