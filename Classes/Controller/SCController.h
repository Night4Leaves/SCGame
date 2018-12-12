#pragma once
#ifndef __SC_CONTROLLER_H__
#define __SC_CONTROLLER_H__

#include "cocos2d.h"
#include "ControllerListener.h"

USING_NS_CC;

class SCController : public Node
{
public:
	SCController();
	virtual ~SCController();

	//…Ë÷√º‡Ã˝∂‘œÛ
	void setControllerListner(ControllerListener* controllerListener);

protected:
	ControllerListener* m_pControllerListener;
};

#endif // !__SC_CONTROLLER_H__
