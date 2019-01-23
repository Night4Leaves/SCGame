#pragma once
#ifndef __PANE_LAYER_H__
#define __PANE_LAYER_H__

#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class PaneLayer : public Layer
{
public:
	PaneLayer();
	virtual ~PaneLayer();

	CREATE_FUNC(PaneLayer);
	virtual bool init();

	

private:
	bool m_bIsEffective;

	void readPlayerJson(std::vector<PlayerInfomation> &vec_playerInfoList);

	void showPaneLayer(Ref* pSender);

	void selectCharacter();
	void loadFile();
	void openStore();
	void startPause();
	void selectGameScene();

	void changeGameScene(Ref* pSender);
	void changeMainScene(Ref* pSender);
};

#endif // !__PANE_LAYER_H__
