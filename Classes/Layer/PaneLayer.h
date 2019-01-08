#pragma once
#ifndef __PANE_LAYER_H__
#define __PANE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PaneLayer : public Layer
{
public:
	PaneLayer();
	virtual ~PaneLayer();

	CREATE_FUNC(PaneLayer);
	virtual bool init();

	void showPaneLayer(Ref* pSender);

	void startGame(Ref* pSender);

private:
	bool m_bIsEffective;
	Sprite* m_pMap;

	LayerColor* a_color;
	Menu* a_1;
	Menu* a_2;
};

#endif // !__PANE_LAYER_H__
