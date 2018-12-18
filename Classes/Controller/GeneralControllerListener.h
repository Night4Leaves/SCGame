#pragma once
#ifndef __GENERAL_CONTROLLER_LISTENER_H__
#define __GENERAL_CONTROLLER_LISTENER_H__

#include "cocos2d.h"

USING_NS_CC;

class GeneralControllerListener
{
public:
	//��ȡ��ɫ����
	virtual Vec2 getTargetPosition() = 0;
	/**
	 *	���ý�ɫ����
	 *	@pos Ŀ��λ��
	 */
	virtual void setTargetPosition(Vec2 pos) = 0;
	/**
	 *	���ƽ�ɫ�Ƿ���
	 *	@b_isRight trueΪ���ң�false����
	 */
	virtual void turnAround(bool b_isRight) = 0;

	virtual void run() = 0;
	virtual void attack() = 0;
	virtual void idle() = 0;
	virtual void hurt() = 0;
	virtual void death() = 0;
	virtual void climb() = 0;
	virtual void jump() = 0;
	
};


#endif // !__GENERAL_CONTROLLER_LISTENER_H__
