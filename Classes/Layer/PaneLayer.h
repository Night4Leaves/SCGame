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

	void savePlayerData(PlayerData &playerData);

private:
	void showPaneLayer(Ref* pSender);

	void openStore();
	void startPause();
	void selectGameScene();

	void openBackpack();
	void openSkilllist();

	void changeGameScene(Ref* pSender);
	void enterMainScene(PlayerData &playerData);
	void changeMainScene(Ref* pSender);;

	void menuCloseCallback(Ref* pSender);
	void createNewData();

	void selectCharacter();
	void selectPlayer_1(Ref* pSender);
	void selectPlayer_2(Ref* pSender);

	void loadFile();
	void selectSavedata_1(Ref* pSender);
	void selectSavedata_2(Ref* pSender);
	void selectSavedata_3(Ref* pSender);
	void selectSavedata_4(Ref* pSender);

	MenuItemSprite* createCharacterSelectItem(const std::vector<PlayerData> &vec_characterInfoList, int i, const SEL_MenuHandler &selector, bool is_savedata);

private:
	bool m_isOpen;
	bool m_isLoadSavedata;

	std::vector<PlayerData> m_vecCharacterList;
	std::vector<PlayerData> m_vecSavedataList;
	PlayerData m_sctPlayerData;
};

#endif // !__PANE_LAYER_H__
