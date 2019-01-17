#pragma once
#ifndef __MOUSE_MONITOR_LAYER__
#define __MOUSE_MONITOR_LAYER__

#include "cocos2d.h"

USING_NS_CC;

class MouseMonitorLayer : public Layer
{
public:
	MouseMonitorLayer();
	virtual ~MouseMonitorLayer();

	CREATE_FUNC(MouseMonitorLayer);
	virtual bool init();
};

#endif // !__MOUSE_MONITOR_LAYER__
