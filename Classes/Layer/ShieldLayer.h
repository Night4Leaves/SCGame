#pragma once
#ifndef __SHIELD_LAYER_H__
#define __SHIELD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

/*点击屏蔽层，可以用来防止当前层的点击传递到上一层中*/
class ShieldLayer : public Layer
{
public:
	CREATE_FUNC(ShieldLayer);

	void setTouchEnabled(bool value);
private:
	ShieldLayer();
	virtual ~ShieldLayer();

	virtual bool init();

private:
	EventListenerTouchOneByOne* m_pListener;
};

#endif // !__SHIELD_LAYER_H__
