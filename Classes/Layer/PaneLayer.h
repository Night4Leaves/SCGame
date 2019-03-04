#pragma once
#ifndef __PANE_LAYER_H__
#define __PANE_LAYER_H__

#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class Player;

class PaneLayer : public Layer
{
public:
	PaneLayer();
	virtual ~PaneLayer();

	CREATE_FUNC(PaneLayer);
	virtual bool init();	

	void savePlayer(Player* player);

private:
	void showPaneLayer(Ref* pSender);

	void readPlayerJson(std::vector<PlayerInfomation> &vec_playerInfoList);

	void selectCharacter();
	void loadFile();
	void openStore();
	void startPause();
	void selectGameScene();

	void openBackpack();

	void changeGameScene(Ref* pSender);
	void changeMainScene();

	void menuCloseCallback(Ref* pSender);
	int checkSaveData();
	void createNewData();

	MenuItemSprite* createPlayerSelectItem(const std::vector<PlayerInfomation> &vec_playerInfoList, int i, const SEL_MenuHandler &selector);
	void selectPlayer_1(Ref* pSender);
	void selectPlayer_2(Ref* pSender);

private:
	const char* m_pPlayer;
	bool is_open;
};

#endif // !__PANE_LAYER_H__
