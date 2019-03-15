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

	/**
	 *	保存玩家数据
	 *	@playerData	玩家数据结构体
	 */
	void savePlayerData(PlayerData &playerData);

private:
	/*显示层*/
	void showPaneLayer(Ref* pSender);

	/*打开商店*/
	void openStore();
	/*暂停*/
	void startPause();
	/*显示选择游戏关卡界面*/
	void selectGameScene();

	/*打开背包*/
	void openBackpack();
	/*打开技能列表*/
	void openSkilllist();

	/*创建选择的关卡场景*/
	void changeGameScene(Ref* pSender);
	/*进入主场景*/
	void enterMainScene(PlayerData &playerData);
	/*切换到主场景*/
	void changeMainScene(Ref* pSender);;

	/*关闭当前显示的界面*/
	void menuCloseCallback(Ref* pSender);
	/*创建新存档数据*/
	void createNewData();

	/*选择玩家角色*/
	void selectCharacter();
	void selectPlayer_1(Ref* pSender);
	void selectPlayer_2(Ref* pSender);

	/*选择载入的存档*/
	void loadFile();
	void selectSavedata_1(Ref* pSender);
	void selectSavedata_2(Ref* pSender);
	void selectSavedata_3(Ref* pSender);
	void selectSavedata_4(Ref* pSender);

	/**
	 *	创建角色选择按钮
	 *	@vec_characterInfoList	玩家角色数据列表
	 *	@i	列表中的第几个数据
	 *	@selector	选择后调用的函数
	 *	@is_savedata	是否为存档数据
	 */
	MenuItemSprite* createCharacterSelectItem(const std::vector<PlayerData> &vec_characterInfoList, int i, const SEL_MenuHandler &selector, bool is_savedata);

private:
	bool m_isOpen;	//层中是否显示内容
	bool m_isLoadSavedata;	//是否为存档数据

	std::vector<PlayerData> m_vecCharacterList;	//玩家角色数据列表
	std::vector<PlayerData> m_vecSavedataList;	//存档数据列表
	PlayerData m_sctPlayerData;	//玩家数据结构
};

#endif // !__PANE_LAYER_H__
