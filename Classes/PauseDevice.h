#pragma once
#ifndef __PAUSE_DEVICE_H__
#define __PAUSE_DEVICE_H__

#include "cocos2d.h"
USING_NS_CC;

class PauseDevice : public Node
{
public:
	PauseDevice();
	virtual ~PauseDevice();

	virtual void startPause(Ref* pSender) = 0;
	virtual void endPause(Ref* pSender) = 0;
};

#endif // !__PAUSE_DEVICE_H__
