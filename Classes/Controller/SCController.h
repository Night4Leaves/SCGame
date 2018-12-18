#pragma once
#ifndef __SC_CONTROLLER_H__
#define __SC_CONTROLLER_H__

#include "PlayerControllerListener.h"

class SCController : public Node
{
public:
	SCController();
	virtual ~SCController();

	//设置监听对象
	void setControllerListner(PlayerControllerListener* controllerListener);

	//检查控制器中保存的控制角色的状态
	virtual void checkControllerStatus() = 0;

	/**
	 *	设置控制器速度
	 *	@i_xSpeed	x轴速度
	 *	@i_ySpeed	y轴速度
	 */
	/*virtual void setSpeed(int i_xSpeed, int i_ySpeed) = 0;*/
protected:
	//记录被控制对象
	PlayerControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
